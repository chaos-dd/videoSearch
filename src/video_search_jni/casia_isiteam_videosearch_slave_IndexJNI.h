/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class casia_isiteam_videosearch_slave_IndexJNI */

#ifndef _Included_casia_isiteam_videosearch_slave_IndexJNI
#define _Included_casia_isiteam_videosearch_slave_IndexJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     casia_isiteam_videosearch_slave_IndexJNI
 * Method:    initIndex
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_casia_isiteam_videosearch_slave_IndexJNI_initIndex
  (JNIEnv *, jobject, jstring, jstring, jstring);

/*
 * Class:     casia_isiteam_videosearch_slave_IndexJNI
 * Method:    addVideo
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_casia_isiteam_videosearch_slave_IndexJNI_addVideo
  (JNIEnv *, jobject, jstring);

/*
 * Class:     casia_isiteam_videosearch_slave_IndexJNI
 * Method:    searchVideo
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_casia_isiteam_videosearch_slave_IndexJNI_searchVideo
  (JNIEnv *, jobject, jstring);

/*
 * Class:     casia_isiteam_videosearch_slave_IndexJNI
 * Method:    deleteVideo
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_casia_isiteam_videosearch_slave_IndexJNI_deleteVideo
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
