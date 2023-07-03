#include"main.h"
void ErrorPrint(const Str file , int line){
    Str err = strerror(errno); //暂时并发量不够高，没必要使用线程独享errno数据
    Str tempFile = strrchr(file,'/');
    printf("[%s:%d]%s",tempFile+1,line,err);
}

char *UrlEncode_malloc(char *str)
{
    char *pstr = str;
    char *buf = (char *) malloc(strlen(str) * 3 + 1);
    char *pbuf = buf;
    char hex[] = "0123456789ABCDEF";
    while (*pstr) {
        if ((*pstr >= 'A' && *pstr <= 'Z') || (*pstr >= 'a' && *pstr <= 'z') || (*pstr >= '0' && *pstr <= '9')) {
            *pbuf++ = *pstr++;
        } else if (*pstr == ' ') {
            *pbuf++ = '+';
            pstr++;
        } else {
            *pbuf++ = '%';
            *pbuf++ = hex[*pstr >> 4];
            *pbuf++ = hex[*pstr & 15];
            pstr++;
        }
    }
    *pbuf = '\0';
    return buf;
}

void MD5StringToString(char ** str,int len){
    char strTemp[33] = {};
    uint8_t mt [16]={};
    md5String(*str,mt);
    for (int i = 0; i < 16; i++) {
        sprintf(strTemp + i * 2, "%02x", mt[i]);
    }
    if(strlen(*str)<16) {
        *str = (char *) realloc(*str, strlen(*str) + 16);
    }
    strcpy(*str,strTemp);
}
//在str字符串找到key子字符串，在子字符串后插入value
bool InsertString(char* &str,const char *key,const char* value){
    int pos = SubStrFind(str,key);
    if(pos == -1)
        return false;
    InsertString(str,value,pos+ strlen(key)-1);
    return true;
}
int main() {
    char *zh = (char *) malloc(4800);
    const char *appid = "20230509001671586";
    const char *password = "2GUt9pdvqh5ih8PfnF7p";
    char *salt =(char*)malloc(21);
    char *signature = (char *) malloc(5000);
    sprintf(salt, "%d", rand());
    //初始化翻译文本
    MemClear(zh,4800);
    strcpy(zh,"hello world");
    char *urlEncode = UrlEncode_malloc(zh);
    Http *http = new Http("GET http://api.fanyi.baidu.com/api/trans/vip/translate?q=&from=en&to=zh&appid=&salt=&sign= HTTP/1.1\n");
    InsertString(http->m_First,"q=", urlEncode);
    InsertString(http->m_First,"appid=", appid );
    InsertString(http->m_First,"salt=", salt);
    MemClear(signature,5000);
    strcpy(signature, appid);
    strcat(signature, zh);
    strcat(signature, salt);
    strcat(signature, password);
    MD5StringToString(&signature, strlen(signature));
    InsertString(http->m_First,"sign=", signature);

    //printf("%s      %d\n",http->m_First,strlen(http->m_First));

    int fd;
    struct sockaddr_in servAddr;
    socklen_t len;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("create socket error! ");
        return 0;
    }
    struct addrinfo  *addr;
    int result = getaddrinfo("fanyi-api.baidu.com", NULL, NULL, &addr);
    CHECK_CALL(result);

    struct addrinfo *res = addr;
    struct sockaddr_in ipv4[5];
    int i;
    for (  i = 0; res!= NULL&&i<5; res = res->ai_next) {
        if (res->ai_family == AF_INET) {
            memcpy(&ipv4[i],res->ai_addr,sizeof(sockaddr_in));
            i++;
        }
    }
    if(i==0)
        exit(1);
    bzero(&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(80);
    servAddr.sin_addr.s_addr = ipv4[0].sin_addr.s_addr;
    sockaddr_in clientAddr;
    len = sizeof(sockaddr_in);
    result = connect(fd,(sockaddr*)&servAddr,len);
    CHECK_CALL(result);
    Str buf = http->GetHttpMassage_malloc();
    result =send(fd,buf,http->GetSize(),0);
    CHECK_CALL(result);
    buf = (Str)realloc(buf,5000);
    MemClear(buf,http->GetSize());
    int total = 0;
    do {
        result = recv(fd, buf+total, http->GetSize(), 0);
        if (result == 0 && result < 0) {
            ErrorPrint(__FILE__, __LINE__);
            break;
        }
        total += result;
    }while(result > 0);
    printf("%s",buf);

    

    close(fd);
    free(urlEncode);
    urlEncode = NULL;
    free(buf);
    buf =NULL;
    free(zh);
    zh = NULL;
    free(salt);
    salt = NULL;
    free(signature);
    signature =NULL;
    return 0;
}