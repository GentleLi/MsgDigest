//
// Created by admin on 2018/9/8.
//
#include <malloc.h>
#include "jni.h"


#ifndef MSGDIGEST_SIGNATURE_H
#define MSGDIGEST_SIGNATURE_H


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


JNIEXPORT jstring JNICALL
Java_com_hengbao_util_DecodeUtil_test(JNIEnv *env, jobject thiz, jobject context) {
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
    tem_class = env->GetObjectClass( obj_package_manager);
    tem_method = env->GetMethodID(tem_class, "getPackageInfo",
                                     "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject obj_package_info = env->CallObjectMethod(obj_package_manager, tem_method,
                                                        obj_package_name, 64);

    // Signature[] arrayOfSignature = localPackageInfo.signatures;
    // Signature localSignature = arrayOfSignature[0];
    tem_class = env->GetObjectClass( obj_package_info);
    jfieldID fieldID_signatures = env->GetFieldID(tem_class, "signatures",
                                                     "[Landroid/content/pm/Signature;");
    jobjectArray signatures = env->GetObjectField(context, fieldID_signatures);
    jobject signature = (*env)->GetObjectArrayElement(env, signatures, 0);
    // localSignature.toByteArray()
    tem_class = (*env)->GetObjectClass(env, signature);
    tem_method = (*env)->GetMethodID(env, tem_class, "toByteArray", "()[B");
    jobject obj_sign_byte_array = (*env)->CallObjectMethod(env, signature,
                                                           tem_method);// 这个就是拿到的签名byte数组

    //      MessageDigest localMessageDigest = MessageDigest.getInstance("MD5");
    jclass class_MessageDigest = (*env)->FindClass(env, "java/security/MessageDigest");
    tem_method = (*env)->GetStaticMethodID(env, class_MessageDigest, "getInstance",
                                           "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jobject obj_md5 = (*env)->CallStaticObjectMethod(env, class_MessageDigest, tem_method,
                                                     (*env)->NewStringUTF(env, "md5"));
    //      localMessageDigest.update(localSignature.toByteArray());
    //tem_class = (*env)->GetObjectClass(env, obj_md5);
    tem_method = (*env)->GetMethodID(env, class_MessageDigest, "update",
                                     "([B)V");// 这个函数的返回值是void，写V
    (*env)->CallVoidMethod(env, obj_md5, tem_method, obj_sign_byte_array);
    // localMessageDigest.digest()
    tem_method = (*env)->GetMethodID(env, class_MessageDigest, "digest", "()[B");
    // 这个是md5以后的byte数组，现在只要将它转换成16进制字符串，就可以和之前的比较了
    jobject obj_array_sign = (*env)->CallObjectMethod(env, obj_md5, tem_method);// jni中有强转类型的概念吗
    //      // 这个就是签名的md5值
    //      String str2 = toHex(localMessageDigest.digest());

    // 尝试用c写一下：http://blog.csdn.net/pingd/article/details/41945417
    jsize int_array_length = (*env)->GetArrayLength(env, obj_array_sign);
    jbyte *byte_array_elements = (*env)->GetByteArrayElements(env, obj_array_sign, JNI_FALSE);
    char *char_result = (char *) malloc(
            int_array_length * 2 + 1);// 开始没有+1，在有的情况下会越界产生问题，还是在后面补上\0比较好
    // 将byte数组转换成16进制字符串，发现这里不用强转，jbyte和unsigned char应该字节数是一样的
    ByteToHexStr(byte_array_elements, char_result, int_array_length);
    *(char_result + int_array_length * 2) = '\0';// 在末尾补\0
    jstring string_result = (*env)->NewStringUTF(env, char_result);
    // release
    (*env)->ReleaseByteArrayElements(env, obj_array_sign, byte_array_elements, JNI_ABORT);
    // 释放指针使用free
    free(char_result);
    return string_result;

    // 如果使用java的16进制转换的话，应该也可以的，用c写16进制转换太麻烦
    //jclass class_HandleData = (*env)->FindClass(env, "com/hengbao/util/HandleData");
    //tem_method = (*env)->GetStaticMethodID(env, class_HandleData, "bytesToHexString1", "([B)Ljava/lang/String;");
    //jobject obj_result = (*env)->CallStaticObjectMethod(env, class_HandleData, tem_method, obj_array_sign);
    //return obj_result;
}


#endif //MSGDIGEST_SIGNATURE_H
