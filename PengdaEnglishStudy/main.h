//
// Created by zhangyuqing on 23-5-23.
//
#ifndef PENGDAENGLISHSTUDY_MAIN_H
#define PENGDAENGLISHSTUDY_MAIN_H
#include<sys/socket.h>
#include<netinet/in.h>
#include<mbedtls/md5.h>
#include<string.h>
#include<netdb.h>
#include"md5.h"
#include"include/Http.h"
#include"errno.h"
#include<unistd.h>
using namespace std;
#define CHECK_CALL(val)                     \
    do {                                    \
        if ((val) < 0) {                    \
            ErrorPrint(__FILE__, __LINE__); \
            exit(1);                        \
        }                                   \
    } while (0)
void ErrorPrint(const Str file , int line);
char *UrlEncode_malloc(char *str);
void MD5StringToString(char ** str,int len);
//在str字符串找到key子字符串，在子字符串后插入value
bool InsertString(char* &str,const char *key,const char* value);
#endif //PENGDAENGLISHSTUDY_MAIN_H
