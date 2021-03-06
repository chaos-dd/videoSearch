
#include "KeyFrameExactor.h"

#include <vector>
#include <numeric>
#include <iostream>

#include "Preprocessor.h"
#include "VideoReader.h"
using namespace std;
using namespace cv;

namespace vs
{
    int KeyFrameExactor::exact(string videoName, Mat &mask, vector<KeyFrame> & keyFrames)
    {
        VideoReader videoReader(videoName,usedFps_);

        if (!videoReader.isOpened())
        {
            cout << "failed to open video" << videoName << endl;
            return -1;
        }

        keyFrames.clear();


        Mat feat;
        vector<int> frame_index;

        Mat cur_frame, next_frame;
        Mat cur_feat, next_feat;
        
        int abs_frame_index;
        abs_frame_index = videoReader.getFrame(cur_frame);
       
        VideoReader::scaleFrame(cur_frame, cur_frame, std::max(mask.rows,mask.cols));

        featExactor.computeFeat(cur_frame, mask,cur_feat, COLOR_SPACE_BGR, cv::NORM_L1);
        feat.push_back(cur_feat);
        frame_index.push_back(abs_frame_index);

        while (true)
        {            
            if ((abs_frame_index = videoReader.getFrame(next_frame)) == -1)
                break;
            VideoReader::scaleFrame(next_frame, next_frame, std::max(mask.rows, mask.cols));

            featExactor.computeFeat(next_frame, mask, next_feat, COLOR_SPACE_BGR, cv::NORM_L1);

            double dist = cv::norm(cur_feat, next_feat, cv::NORM_L1);
            float similarity = 1 - dist / 2;

            if (similarity < colorThres_)
            {//keyframe detection
                kfDetection(feat, frame_index, keyFrames);

                feat.release();
                frame_index.clear();  //already moved away!
            }
            //debug code
            //cur_frame = next_frame.clone();
            //debug code over

            cur_feat = next_feat;
            feat.push_back(next_feat);
            frame_index.push_back(abs_frame_index);

        }//end while true

        if (feat.rows >= 0)
        {
            kfDetection(feat, frame_index, keyFrames);
        }

        return 0;
    }

    void KeyFrameExactor::kfDetection(Mat &feat, vector<int> &frame_index, vector<KeyFrame> & keyFrames)
    {
        //curIndices.clear();
        if (feat.rows >= MINIMUM_FRAME_IN_SHOT)
        {
            vector<int> indices;
            PCAExact(feat, indices);

            for (size_t i = 0; i != indices.size();++i)
            {
                keyFrames.emplace_back(frame_index[indices[i]], frame_index[0], frame_index[frame_index.size() - 1]);
            }

        }
        else
        {
            for (size_t i = 0; i != frame_index.size(); ++i)
            {
                keyFrames.emplace_back(frame_index[i], frame_index[i], frame_index[i]);
            }
        }
    }
    int KeyFrameExactor::PCAExact(cv::Mat &src, std::vector<int> &indices)
    {
        cv::Mat covar;
        cv::Mat mean;

        cv::calcCovarMatrix(src, covar, mean, CV_COVAR_NORMAL | CV_COVAR_COLS, CV_32F);

        std::vector<float> eigenvalues;
        cv::Mat eigenvectors;
        cv::eigen(covar, eigenvalues, eigenvectors);


        std::vector<int> index;
        index_sort(eigenvalues, 0, eigenvalues.size() - 1, index, [](float v1, float v2){return v1 > v2; });

        std::vector<float> cum_sum;
        std::partial_sum(eigenvalues.begin(), eigenvalues.end(), std::back_inserter(cum_sum));

        float sum = std::accumulate(eigenvalues.begin(), eigenvalues.end(), 0.0f);

        float threshold = sum*retainedVariance_;
        auto iter = std::find_if(cum_sum.begin(), cum_sum.end(), [threshold](float v){return v >= threshold; });

        for (auto it = cum_sum.begin(); it <= iter; ++it)
        {
            indices.push_back(index[it - cum_sum.begin()]);
        }

        //printf("kf ratio %d/%d \n ", indices.size(),src.rows);
        return 0;
    }
}