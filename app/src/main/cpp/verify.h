//
// Created by admin on 2018/9/7.
//
#include <fcntl.h>
#include <stdio.h>
#include "MD5.h"
#include <stdlib.h>
#include <string>
#include "unistd.h"

#ifndef MSGDIGEST_VERIFY_H
#define MSGDIGEST_VERIFY_H

const int READ_DATA_SIZE = 8192;
const int MD5_SIZE = 16;
const int MD5_STR_LEN = 33;

char *GetFileMD5(const char *filePath, char *strMD5);

std::string getSha1(char *filepath);

#endif //MSGDIGEST_VERIFY_H
