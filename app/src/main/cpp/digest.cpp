//
// Created by admin on 2018/9/7.
//

#include "digest.h"
#include "verify.h"


#include <string.h>


const char hexcode[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
                        'F'};


/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getFileMd5
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */


JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getFileMd5
        (JNIEnv *env, jclass clz, jstring file_path) {

    char info[33] = {0};
    char input_str[500] = {0};
    sprintf(input_str, "%s", env->GetStringUTFChars(file_path, NULL));
    GetFileMD5(input_str, info);

    return env->NewStringUTF(info);
}


/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getShaOne
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getShaOne
        (JNIEnv *env, jclass clz, jstring file_path) {

    char input_str[500] = {0};
    sprintf(input_str, "%s", env->GetStringUTFChars(file_path, NULL));
    std::string sha = getSha1(input_str);
    return env->NewStringUTF(sha.c_str());

}


/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignature
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignature
        (JNIEnv *env, jclass) {
    jobject contextObject = getApplication(env);

    jclass native_class = env->GetObjectClass(contextObject);
    jmethodID pm_id = env->GetMethodID(native_class, "getPackageManager",
                                       "()Landroid/content/pm/PackageManager;");
    jobject pm_obj = env->CallObjectMethod(contextObject, pm_id);
    jclass pm_clazz = env->GetObjectClass(pm_obj);
// 得到 getPackageInfo 方法的 ID
    jmethodID package_info_id = env->GetMethodID(pm_clazz, "getPackageInfo",
                                                 "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jclass native_classs = env->GetObjectClass(contextObject);
    jmethodID mId = env->GetMethodID(native_classs, "getPackageName", "()Ljava/lang/String;");
    jstring pkg_str = static_cast<jstring>(env->CallObjectMethod(contextObject, mId));
// 获得应用包的信息
    jobject pi_obj = env->CallObjectMethod(pm_obj, package_info_id, pkg_str, 64);
// 获得 PackageInfo 类
    jclass pi_clazz = env->GetObjectClass(pi_obj);
// 获得签名数组属性的 ID
    jfieldID signatures_fieldId = env->GetFieldID(pi_clazz, "signatures",
                                                  "[Landroid/content/pm/Signature;");
    jobject signatures_obj = env->GetObjectField(pi_obj, signatures_fieldId);
    jobjectArray signaturesArray = (jobjectArray) signatures_obj;
    jsize size = env->GetArrayLength(signaturesArray);
    jobject signature_obj = env->GetObjectArrayElement(signaturesArray, 0);

    jclass signature_clazz = env->GetObjectClass(signature_obj);
    jmethodID string_id = env->GetMethodID(signature_clazz, "toCharsString",
                                           "()Ljava/lang/String;");
    jstring str = static_cast<jstring>(env->CallObjectMethod(signature_obj, string_id));
    char *c_msg = (char *) env->GetStringUTFChars(str, 0);

    //调试 获取bytearray
//    jmethodID array_method_id = env->GetMethodID(signature_clazz, "toByteArray", "()[B");
//    env->DeleteLocalRef(signature_clazz);
//    jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_clazz,
//                                                                   array_method_id);


    jstring signature = (env)->NewStringUTF(c_msg);
    //getMD5(env, signature)
    return signature;
//    //return str;
//    if(strcmp(c_msg,RELEASE_SIGN)==0)//签名一致  返回合法的 api key，否则返回错误
//    {
//        return (env)->NewStringUTF(AUTH_KEY);
//    }else
//    {
//        return (env)->NewStringUTF("error");
//    }



}


/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignMd5
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignMd5
        (JNIEnv *env, jclass) {

    //java code=======================================================
    //      PackageInfo localPackageInfo = context.getPackageManager()
    //              .getPackageInfo(context.getPackageName(), 64);
    //      StringBuilder localStringBuilder = new StringBuilder();
    //      Signature[] arrayOfSignature = localPackageInfo.signatures;
    //      Signature localSignature = arrayOfSignature[0];
    //      MessageDigest localMessageDigest = MessageDigest.getInstance("MD5");
    //      localMessageDigest.update(localSignature.toByteArray());
    //      // 这个就是签名的md5值
    //      String str2 = toHex(localMessageDigest.digest());
    //      localStringBuilder.append("Signature of ")
    //              .append(localPackageInfo.packageName).append('\n').append(str2);
    //      System.out.println(localStringBuilder.toString());
    //      TextView tv = (TextView) findViewById(R.id.tv);
    //      tv.setText(localStringBuilder.toString());


    //  private String toHex(byte[] paramArrayOfByte) {
    //      StringBuffer localStringBuffer = new StringBuffer();
    //      for (int i = 0; i < paramArrayOfByte.length; i++) {
    //          Object[] arrayOfObject = new Object[1];
    //          arrayOfObject[0] = Byte.valueOf(paramArrayOfByte[i]);
    //          localStringBuffer.append(String.format("%02x", arrayOfObject));
    //      }
    //      return localStringBuffer.toString();
    //  }
    //java code======================================================
    jobject context = getApplication(env);

    jclass tem_class;
    jmethodID tem_method;
    jclass class_context = env->GetObjectClass(context);
    //      PackageInfo localPackageInfo = context.getPackageManager()
    //              .getPackageInfo(context.getPackageName(), 64);
    tem_method = env->GetMethodID(class_context, "getPackageManager",
                                  "()Landroid/content/pm/PackageManager;");
    jobject obj_package_manager = env->CallObjectMethod(context, tem_method);
    // getPackageName
    tem_method = env->GetMethodID(class_context, "getPackageName", "()Ljava/lang/String;");
    jobject obj_package_name = env->CallObjectMethod(context, tem_method);
    // getPackageInfo
    tem_class = env->GetObjectClass(obj_package_manager);
    tem_method = env->GetMethodID(tem_class, "getPackageInfo",
                                  "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject obj_package_info = env->CallObjectMethod(obj_package_manager, tem_method,
                                                     obj_package_name, 64);

    // Signature[] arrayOfSignature = localPackageInfo.signatures;
    // Signature localSignature = arrayOfSignature[0];
    tem_class = env->GetObjectClass(obj_package_info);
    jfieldID fieldID_signatures = env->GetFieldID(tem_class, "signatures",
                                                  "[Landroid/content/pm/Signature;");
    jobjectArray signatures = (jobjectArray) env->GetObjectField(obj_package_info,
                                                                 fieldID_signatures);
    jobject signature = env->GetObjectArrayElement(signatures, 0);
    // localSignature.toByteArray()
    tem_class = env->GetObjectClass(signature);
    tem_method = env->GetMethodID(tem_class, "toByteArray", "()[B");
    jobject obj_sign_byte_array = env->CallObjectMethod(signature, tem_method);// 这个就是拿到的签名byte数组

    //      MessageDigest localMessageDigest = MessageDigest.getInstance("MD5");
    jclass class_MessageDigest = env->FindClass("java/security/MessageDigest");
    tem_method = env->GetStaticMethodID(class_MessageDigest, "getInstance",
                                        "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jobject obj_md5 = env->CallStaticObjectMethod(class_MessageDigest, tem_method,
                                                  env->NewStringUTF("md5"));
    //      localMessageDigest.update(localSignature.toByteArray());
    //tem_class = (*env)->GetObjectClass(env, obj_md5);
    tem_method = env->GetMethodID(class_MessageDigest, "update",
                                  "([B)V");// 这个函数的返回值是void，写V
    env->CallVoidMethod(obj_md5, tem_method, obj_sign_byte_array);
    // localMessageDigest.digest()
    tem_method = env->GetMethodID(class_MessageDigest, "digest", "()[B");
    // 这个是md5以后的byte数组，现在只要将它转换成16进制字符串，就可以和之前的比较了  需要强转为jbyteArray
    jbyteArray obj_array_sign = (jbyteArray) env->CallObjectMethod(obj_md5,
                                                                   tem_method);// jni中有强转类型的概念吗
    //      // 这个就是签名的md5值
    //      String str2 = toHex(localMessageDigest.digest());

    // 尝试用c写一下：http://blog.csdn.net/pingd/article/details/41945417
    jsize int_array_length = env->GetArrayLength(obj_array_sign);
    jbyte *byte_array_elements = env->GetByteArrayElements(obj_array_sign, JNI_FALSE);
    char *char_result = (char *) malloc(
            int_array_length * 2 + 1);// 开始没有+1，在有的情况下会越界产生问题，还是在后面补上\0比较好
    // 将byte数组转换成16进制字符串，发现这里不用强转，jbyte和unsigned char应该字节数是一样的
    //在此需要强转
    ByteToHexStr((const unsigned char *) byte_array_elements, char_result, int_array_length);
    *(char_result + int_array_length * 2) = '\0';// 在末尾补\0
    jstring string_result = env->NewStringUTF(char_result);
    // release
    env->ReleaseByteArrayElements(obj_array_sign, byte_array_elements, JNI_ABORT);
    // 释放指针使用free
    free(char_result);
    return string_result;

    // 如果使用java的16进制转换的话，应该也可以的，用c写16进制转换太麻烦
    //jclass class_HandleData = (*env)->FindClass(env, "com/hengbao/util/HandleData");
    //tem_method = (*env)->GetStaticMethodID(env, class_HandleData, "bytesToHexString1", "([B)Ljava/lang/String;");
    //jobject obj_result = (*env)->CallStaticObjectMethod(env, class_HandleData, tem_method, obj_array_sign);
    //return obj_result;
}



/*
 * Class:     me_study_msgdigest_digest_MD5Helper
 * Method:    getSignSha1
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_study_msgdigest_digest_MD5Helper_getSignSha1
        (JNIEnv *env, jclass) {
    jobject context = getApplication(env);
    char *sha1 = getSha1(env, context);
    return env->NewStringUTF(sha1);
}


JNIEXPORT jobject getApplication(JNIEnv *env) {
    jclass localClass = env->FindClass("android/app/ActivityThread");
    if (localClass != NULL) {

        jmethodID getapplication = env->GetStaticMethodID(localClass, "currentApplication",
                                                          "()Landroid/app/Application;");
        if (getapplication != NULL) {
            jobject application = env->CallStaticObjectMethod(localClass, getapplication);
            return application;
        }
        return NULL;
    }
    return NULL;
}


jbyteArray getDigestedBytes(JNIEnv *env, jbyteArray complex_bytes) {
    static jobject satic_message_digest_obj = __null;
    jclass message_digest_cls = env->FindClass("java/security/MessageDigest");
    jmethodID get_instance_mid = env->GetStaticMethodID(message_digest_cls,
                                                        "getInstance",
                                                        "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    if (satic_message_digest_obj == __null) {
        jobject local_message_digest_obj = env->CallStaticObjectMethod(
                message_digest_cls, get_instance_mid, env->NewStringUTF("MD5"));
        satic_message_digest_obj = env->NewGlobalRef(local_message_digest_obj);
        env->DeleteLocalRef(local_message_digest_obj);
    }
    jmethodID digest_mid = env->GetMethodID(message_digest_cls, "digest",
                                            "([B)[B");
    env->DeleteLocalRef(message_digest_cls);
    return reinterpret_cast<jbyteArray>(env->CallObjectMethod(
            satic_message_digest_obj, digest_mid, complex_bytes));
}


jstring getMD5(JNIEnv *env, jstring jInfo) {
    jbyteArray digested_bytes = getDigestedBytes(env, toBytes(env, jInfo));
    return toHex(env, digested_bytes);
}


jstring toHex(JNIEnv *env, jbyteArray digested_bytes) {
    jclass big_integer_cls = env->FindClass("java/math/BigInteger");
    jmethodID new_big_integer_mid = env->GetMethodID(big_integer_cls, "<init>",
                                                     "(I[B)V");
    jobject big_integer_obj = env->NewObject(big_integer_cls,
                                             new_big_integer_mid, 1, digested_bytes);
    env->DeleteLocalRef(digested_bytes);
    jmethodID to_String_mid = env->GetMethodID(big_integer_cls, "toString",
                                               "(I)Ljava/lang/String;");
    env->DeleteLocalRef(big_integer_cls);
    return reinterpret_cast<jstring>(env->CallObjectMethod(big_integer_obj,
                                                           to_String_mid, 16));
}

jbyteArray toBytes(JNIEnv *env, jstring string) {
    jclass string_cls = env->FindClass("java/lang/String");
    jmethodID get_bytes_mid = env->GetMethodID(string_cls, "getBytes",
                                               "(Ljava/lang/String;)[B");
    return reinterpret_cast<jbyteArray>(env->CallObjectMethod(string,
                                                              get_bytes_mid,
                                                              env->NewStringUTF(UTF_8)));
}


// 字节流转换为十六进制字符串
//http://blog.csdn.net/pingd/article/details/41945417
void ByteToHexStr(const unsigned char *source, char *dest, int sourceLen) {
    short i;
    unsigned char highByte, lowByte;

    for (i = 0; i < sourceLen; i++) {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;

        highByte += 0x30;

        if (highByte > 0x39)
            dest[i * 2] = highByte + 0x07;
        else
            dest[i * 2] = highByte;

        lowByte += 0x30;
        if (lowByte > 0x39)
            dest[i * 2 + 1] = lowByte + 0x07;
        else
            dest[i * 2 + 1] = lowByte;
    }
    return;
}


char *getSha1(JNIEnv *env, jobject context_object) {
    //上下文对象
    jclass context_class = env->GetObjectClass(context_object);

    //反射获取PackageManager
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager",
                                          "()Landroid/content/pm/PackageManager;");
    jobject package_manager = env->CallObjectMethod(context_object, methodId);
    if (package_manager == NULL) {
//        LOGD("package_manager is NULL!!!");
        return NULL;
    }

    //反射获取包名
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name = (jstring) env->CallObjectMethod(context_object, methodId);
    if (package_name == NULL) {
//        LOGD("package_name is NULL!!!");
        return NULL;
    }
    env->DeleteLocalRef(context_class);

    //获取PackageInfo对象
    jclass pack_manager_class = env->GetObjectClass(package_manager);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo",
                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info = env->CallObjectMethod(package_manager, methodId, package_name, 0x40);
    if (package_info == NULL) {
//        LOGD("getPackageInfo() is NULL!!!");
        return NULL;
    }
    env->DeleteLocalRef(package_manager);

    //获取签名信息
    jclass package_info_class = env->GetObjectClass(package_info);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures",
                                       "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray) env->GetObjectField(package_info, fieldId);
    if (signature_object_array == NULL) {
//        LOGD("signature is NULL!!!");
        return NULL;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info);

    //签名信息转换成sha1值
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_class);
    jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_object, methodId);
    jclass byte_array_input_class = env->FindClass("java/io/ByteArrayInputStream");
    methodId = env->GetMethodID(byte_array_input_class, "<init>", "([B)V");
    jobject byte_array_input = env->NewObject(byte_array_input_class, methodId, signature_byte);
    jclass certificate_factory_class = env->FindClass("java/security/cert/CertificateFactory");
    methodId = env->GetStaticMethodID(certificate_factory_class, "getInstance",
                                      "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring = env->NewStringUTF("X.509");
    jobject cert_factory = env->CallStaticObjectMethod(certificate_factory_class, methodId,
                                                       x_509_jstring);
    methodId = env->GetMethodID(certificate_factory_class, "generateCertificate",
                                ("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert = env->CallObjectMethod(cert_factory, methodId, byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    jclass x509_cert_class = env->GetObjectClass(x509_cert);
    methodId = env->GetMethodID(x509_cert_class, "getEncoded", "()[B");
    jbyteArray cert_byte = (jbyteArray) env->CallObjectMethod(x509_cert, methodId);
    env->DeleteLocalRef(x509_cert_class);
    jclass message_digest_class = env->FindClass("java/security/MessageDigest");
    methodId = env->GetStaticMethodID(message_digest_class, "getInstance",
                                      "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring = env->NewStringUTF("SHA1");
    jobject sha1_digest = env->CallStaticObjectMethod(message_digest_class, methodId, sha1_jstring);
    methodId = env->GetMethodID(message_digest_class, "digest", "([B)[B");
    jbyteArray sha1_byte = (jbyteArray) env->CallObjectMethod(sha1_digest, methodId, cert_byte);
    env->DeleteLocalRef(message_digest_class);

    //转换成char
    jsize array_size = env->GetArrayLength(sha1_byte);
    jbyte *sha1 = env->GetByteArrayElements(sha1_byte, NULL);
    char *hex_sha = new char[array_size * 2 + 1];
    for (int i = 0; i < array_size; ++i) {
        hex_sha[2 * i] = hexcode[((unsigned char) sha1[i]) / 16];
        hex_sha[2 * i + 1] = hexcode[((unsigned char) sha1[i]) % 16];
    }
    hex_sha[array_size * 2] = '\0';

//    LOGD("hex_sha %s ", hex_sha);
    return hex_sha;
}