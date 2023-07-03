//
// Created by zhangyuqing on 23-5-22.
//
#ifndef PENGDAENGLISHSTUDY_HTTP_H
#define PENGDAENGLISHSTUDY_HTTP_H
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef char* Str;
#define MemClear(str,len)  memset(str,0,len)


int SubStrFind(char *str,const char *sub);
char *MallocStr(int len);
void StrNCpy(char* dest ,char* source , int n);
void InsertString(char *&destStr ,const char* insertStr,int pos);
char* IntToString_malloc(int value);
class Http{
public:
    Str m_First;
    Str m_Head;
    Str m_Enter;

    long m_BodyLength;

    char* GetHttpMassage_malloc();
    long long GetSize();
    bool SetHeadValue(const char *key, const char *value);
    void SetBody(char *buf ,int n);
    void SetContentType(Str fileType);
    //void AddHeadField(char *  field);
    Http(char*first = NULL,char*head=NULL);
    ~Http();
private:
    Str m_Body;
};
#endif //PENGDAENGLISHSTUDY_HTTP_H
