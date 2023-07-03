//
// Created by zhangyuqing on 23-5-22.
//

#include "Http.h"
int SubStrFind(char *str,const char *sub){
    char *temp =strstr(str,sub);
    if(temp == NULL)
        return -1;
    return temp - str;
}
char *MallocStr(int len){
    char *temp = (char*)malloc(len+1);
    *temp = '\0';
    //memset(temp,0,len+1);
    return temp;
}
void StrNCpy(char* dest ,char* source , int n){
    int i;
    for( i =0;i<n;i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
}
void InsertString(char *&destStr ,const char* insertStr,int pos){//后插
    long long length = strlen(destStr)+strlen(insertStr);
    Str newStr = (Str)MallocStr(length+1);
    destStr = (Str)realloc(destStr,length+1);
    *(destStr+length) = '\0';
    StrNCpy(newStr,destStr,pos+1);
    strcat(newStr,insertStr);
    strcat(newStr,destStr+pos+1);
    strcpy(destStr,newStr);

    free(newStr);
}
char* IntToString_malloc(int value){
    Str IntToString  = MallocStr(21);
    MemClear(IntToString, 21);
    sprintf(IntToString, "%ld", value);
    return IntToString;
}

long long Http::GetSize() {
    return strlen(m_First)+ strlen(m_Enter)+ strlen(m_Head)+m_BodyLength;
}
Http::Http(char*first,char*head) {
    if(first !=NULL) {
        m_First = MallocStr(strlen(first));
        strcpy(m_First, first);
    }
    else
        m_First = "\n";
    if(head!=NULL){
        m_Head = MallocStr(strlen(head));
        ::strcpy(m_Head,head);
    }
    else
        m_Head = "\n";
    m_Enter = "\n";
    m_Body = NULL;
    m_BodyLength = 0;
}
Http::~Http() {
    free(m_First);
    m_First = NULL;
    free(m_Head);
    m_Head = NULL;
    free(m_Body);
    m_Body = NULL;
    m_BodyLength = 0;
}
bool Http::SetHeadValue(const char *key,const char* value){
    int pos = SubStrFind(m_Head,key);
    if(pos == -1)
        return false;
    InsertString(m_Head,value,pos+ strlen(key));
    return true;
}
void Http::SetBody(char *buf ,int n){
    m_Body = MallocStr(n);
    for(int i=0;i<n;i++){
        m_Body[i] = buf[i];
    }
    m_BodyLength = n;
};
char* Http::GetHttpMassage_malloc(){
    Str msg = MallocStr(GetSize());
    strcat(msg,m_First);
    if(m_Head != NULL)
        strcat(msg,m_Head);
    strcat(msg,m_Enter);
    for(int i= GetSize()-m_BodyLength,j =0 ;j<m_BodyLength;i++,j++){
        msg[i] = m_Body[j];
    }
    return msg;
}
void Http::SetContentType(Str fileType) {
    if(strcasecmp(fileType,"png") == 0){
        SetHeadValue("Content-Type:", "image/png");
    }else if(strcasecmp(fileType,"html") == 0) {
        SetHeadValue("Content-Type:", "text/html");
    }else if(strcasecmp(fileType,"css") == 0){
        SetHeadValue("Content-Type:", "text/css");
    }
}