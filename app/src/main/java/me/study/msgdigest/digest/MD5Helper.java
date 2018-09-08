package me.study.msgdigest.digest;

/**
 * Created by admin on 2018/9/7.
 */

public class MD5Helper {


    static {

        System.loadLibrary("digest");

    }

    /**
     * 获取apk的md5,注意不是签名文件的
     *
     * @param filePath
     * @return
     */
    public native static String getFileMd5(String filePath);

    /**
     * 获取apk的sha1,注意不是签名文件的
     *
     * @param filePath
     * @return
     */
    public native static String getShaOne(String filePath);

    /**
     * 获取签名文件
     * @return
     */
    public native static String getSignature();


    public native static String getSignMd5();


    public native static String getSignSha1();


}
