//
// Created by admin on 2018/9/7.
//
#include "jni.h"
#include <android/log.h>

#ifndef MSGDIGEST_DIGEST_H
#define MSGDIGEST_DIGEST_H
#define UTF_8 "UTF-8"
#define TAG    "jni-log"

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "hahahahaha", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "xiaobai", __VA_ARGS__))

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


/**
 *
 * 获取context
 * @param env
 * @return
 */
jobject getApplication(JNIEnv *env) ;

void ByteToHexStr(const unsigned char *source, char *dest, int sourceLen);


jstring toHex(JNIEnv *env, jbyteArray digested_bytes);

jstring getMD5(JNIEnv *env, jstring jInfo);

jbyteArray toBytes(JNIEnv *env, jstring string);

char *getSha1(JNIEnv *env, jobject context_object);

#ifdef __cplusplus
}
#endif
#endif //MSGDIGEST_DIGEST_H
