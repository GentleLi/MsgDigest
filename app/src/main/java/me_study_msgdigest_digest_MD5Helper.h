/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class me_study_msgdigest_digest_MD5Helper */

#ifndef _Included_me_study_msgdigest_digest_MD5Helper
#define _Included_me_study_msgdigest_digest_MD5Helper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getFileMd5
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getFileMd5
  (JNIEnv *, jclass, jstring);

/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getShaOne
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getShaOne
  (JNIEnv *, jclass, jstring);

/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignature
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignature
  (JNIEnv *, jclass);

/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignMd5
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignMd5
  (JNIEnv *, jclass);

/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignSha1
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignSha1
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
