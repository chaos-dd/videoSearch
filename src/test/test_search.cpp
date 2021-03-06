
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <sstream>

#include <opencv2/opencv.hpp>

#include <boost/filesystem.hpp>
//#include <boost/property_tree/json_parser.hpp>

#include "../video_search/VideoReader.h"
#include "../video_search//VideoIndexEngine.h"

using namespace std;
using namespace cv;
//using namespace boost;
//using namespace boost::filesystem;

using boost::filesystem::directory_iterator;
using boost::filesystem::path;
//using boost::property_tree::write_json;
int main()
{
    string dataDir = "d:/videoSearchServer/data";
    string logDir = "d:/videoSearchServer/log";
    string algoConf = "D:\\videoSearchServer\\conf\\algo.conf";

    string videoDir = "D:/videos/tar";

    vector<path> vec_path;

    path p(videoDir);

    copy_if(directory_iterator(p), directory_iterator(), back_inserter(vec_path),
            [](path  pp)
            { return is_regular_file(pp); }
            );

    vector<string> tar_videoNames;
    transform(vec_path.begin(), vec_path.end(), back_inserter(tar_videoNames), [](path &p){ return p.string(); });

    vs::VideoIndexEngine indexEngine(dataDir, logDir, algoConf);

    clock_t beg;
    
    beg = clock();
    indexEngine.addVideo(tar_videoNames);
    double addTime = (double)(clock() - beg) / CLOCKS_PER_SEC;


    printf("\n\n");
    string det_videoName = "d:/videos/det/det.mp4";

    beg = clock();
    string jsonResult;
    indexEngine.searchVideo(det_videoName, jsonResult);
    double searTime = (double)(clock() - beg) / CLOCKS_PER_SEC;


    FILE *fout = fopen("result.json", "w");

    fprintf(fout, "%s", jsonResult.c_str());


    printf("add video time=%lf\n", addTime);
    printf("search time = %lf\n", searTime);

    return 0;

}