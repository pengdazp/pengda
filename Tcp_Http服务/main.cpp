#include"head/main.h"

void StrnCpy(Str dest ,Str source , int n){
    int i;
    for( i =0;i<n;i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
}
void InsertString(Str&destStr ,const Str insertStr,int pos){//后插
    long long length = strlen(destStr)+strlen(insertStr);

    destStr = (Str)realloc(destStr,length+1);
    *(destStr+length+1) = '\0';
    Str newStr = (Str)malloc(strlen(destStr)+strlen(insertStr)+1);
    memset(newStr,0,strlen(destStr)+strlen(insertStr)+1);

    StrnCpy(newStr,destStr,pos+1);
    strcat(newStr,insertStr);
    strcat(newStr,destStr+pos+1);
    strcpy(destStr,newStr);

    free(newStr);
}
ThreadMgt::ThreadMgt(){
    m_AcceptThread.function =  &AcceptThread;
    m_AcceptThread.param = NULL;
    m_ExecuteThread.function = &ExecuteThread;
    m_ExecuteThread.param=NULL;
//    m_RWThread.function = &RWThread;
//    m_RWThread.param = NULL;
}

//QueueMgt::QueueMgt(){
//    m_ExecutQueue.m_Rear = &m_ExecutQueue.m_Front;
//    m_ExecuteQueuePV = PTHREAD_MUTEX_INITIALIZER;
//    m_RWQueue.m_Rear = &m_RWQueue.m_Front;
//    m_RWQueuePV = PTHREAD_MUTEX_INITIALIZER;
//}

InitInfo::InitInfo() {
    m_ListenProt = 2039;
    m_MaxClientNumber = 128;
    m_HttpSize = 5*1024*1024;
    m_WWWRoot = (Str)malloc(strlen("/wwwroot"));
    strcpy(m_WWWRoot,"/wwwroot");
}

Control::Control() {
    struct sockaddr_in local;
    int result ;
    int prama = 1;
    memset( &local, 0, sizeof(local) );


    m_printPv = PTHREAD_MUTEX_INITIALIZER;
    m_ListenEpoll = epoll_create(m_InitInfo.m_MaxClientNumber);
    CHECK_CALL(m_ListenEpoll);
    m_ClientEpoll = epoll_create(m_InitInfo.m_MaxClientNumber);
    CHECK_CALL(m_ClientEpoll);
    m_SocketListen = socket(AF_INET,SOCK_STREAM,NULL);
    CHECK_CALL(m_SocketListen);
    result = ioctl(m_SocketListen, FIONBIO, &prama);   // 将套接字设置为非阻塞模式
    CHECK_CALL(result);
    local.sin_family		= AF_INET;
    local.sin_addr.s_addr	= htonl(INADDR_ANY);
    local.sin_port			= htons(m_InitInfo.m_ListenProt);

    result=setsockopt( m_SocketListen, SOL_SOCKET, SO_REUSEADDR, (char *)&prama, sizeof(prama) );
    CHECK_CALL(result);
    result = bind(m_SocketListen, (struct sockaddr*)&local, sizeof(local));
    CHECK_CALL(result);
    result = listen(m_SocketListen,m_InitInfo.m_MaxClientNumber);

}

void SetFlashMode() {
    fflush(stdout);
    setvbuf(stdout,NULL,_IONBF,0);//设置标准输出为无缓冲模式，立即显示数据
}

void ErrorPrint(const Str file , int line){
    Str err = strerror(errno); //暂时并发量不够高，没必要使用线程独享errno数据
    Str tempFile = strrchr(file,'/');
    P(&g_Control.m_printPv);
    printf("[%s:%d]%s",tempFile+1,line,err);
    V(&g_Control.m_printPv);
}
void* AcceptThread(void * param){
    sockaddr_in addr;
    socklen_t  len = sizeof(addr);
    int result;
    epoll_event ev;
    int ClientSocket;
    epoll_event clientEv;
    int temp =1;

    memset(&clientEv,0,sizeof(clientEv));

    while(1){
        result = epoll_wait(g_Control.m_ListenEpoll, &ev, g_Control.m_InitInfo.m_MaxClientNumber, -1);
        if(result <0 && errno == EINTR){
            continue;
        }
        while(1) {
            ClientSocket = accept(g_Control.m_SocketListen, (sockaddr *) &addr, (socklen_t *) &len);
            if(ClientSocket<0)
                break;
            result = ioctl(ClientSocket, FIONBIO, &temp);
            CHECK_CALL(result);
            clientEv.events =EPOLLIN | EPOLLET | EPOLLERR | EPOLLHUP  | EPOLLRDHUP;
            clientEv.data.fd = ClientSocket;
            result = epoll_ctl(g_Control.m_ClientEpoll,EPOLL_CTL_ADD,ClientSocket,&clientEv);
            CHECK_CALL(result);
        }
    }
    free(&clientEv);
}
void* ExecuteThread(void *param) {
    epoll_event *ev = (epoll_event *) malloc(sizeof(epoll_event) * g_Control.m_InitInfo.m_MaxClientNumber);
    while (1) {
        int epollNumber = epoll_wait(g_Control.m_ClientEpoll, ev, g_Control.m_InitInfo.m_MaxClientNumber, -1);
        if (errno == EINTR) {
            continue;
        } else
            CHECK_CALL(epollNumber);

        for (int i = 0; i < epollNumber; i++) {
            if (ev[i].events == EPOLLIN) {
                char buffer[g_Control.m_InitInfo.m_HttpSize];
                int clientSocket = ev[i].data.fd;
                int result = recv(clientSocket, buffer, g_Control.m_InitInfo.m_HttpSize, NULL);
                CHECK_CALL(result);
                string  strBuffer;
                strBuffer.append(buffer);
                int start = strBuffer.find('/');
                int end = strBuffer.find(" HTTP/1.1");
                string fileName = strBuffer.substr(start,end-start);
                start = strBuffer.find(".");
                end = strBuffer.find(" HTTP/1.1");
                string fileType = strBuffer.substr(start+1,end-start-1);
                fileName = g_Control.m_InitInfo.m_WWWRoot +fileName;
                FILE  *fd = fopen(fileName.c_str(), "r");
                if (fd == NULL) {
                    ErrorPrint(__FILE__, __LINE__);
                    exit(1);
                }
                fseek(fd, 0, SEEK_END);
                int fileSize = ftell(fd);
                fseek(fd, 0, SEEK_SET);
                memset(buffer,'\0',g_Control.m_InitInfo.m_HttpSize);
                if (fread(buffer, 1, fileSize, fd) != fileSize) {
                    ErrorPrint(__FILE__, __LINE__);
                    exit(1);
                }
                strBuffer.clear();
                strBuffer.append(buffer);
                Http http;
                http.m_First = "HTTP/1.1 200 OK\n";
                http.m_Head = "Content-Type:\n"
                              "Content-Length:\n"
                              "Server: PengdaTcpHttp\n";
                http.m_Enter = "\n";
                http.m_Body =  strBuffer;
                start = http.m_Head.find("Length:");
                http.m_Head.insert(start+7, to_string(strBuffer.length()));
                start = http.m_Head.find("Content-Type:");
                if(fileType == "png"){
                    http.m_Head.insert(start+13, " image/png");
                }else if(fileType == "css"){
                    http.m_Head.insert(start+13, " text/css");
                }
                else if(fileType == "html"){
                    http.m_Head.insert(start+13, " text/html");
                }
                else if(fileType == "ico"){
                    http.m_Head.insert(start+13, " image/ico");
                }
                else if(fileType == "pdf"){
                    http.m_Head.insert(start+13, " application/pdf");
                }
                string sendHttpMessage;
                sendHttpMessage = sendHttpMessage+http.m_First+http.m_Head+http.m_Enter+http.m_Body;
                result = send(clientSocket, sendHttpMessage.c_str(), (size_t) sendHttpMessage.length(), NULL);
                CHECK_CALL(result);
                if(result != sendHttpMessage.length())
                    printf("need:%d  send%d\n",sendHttpMessage.length(),result);
                close(clientSocket);
            }
        }
    }
}


int main() {
    epoll_event ev;
    int result;

    memset(&ev,0,sizeof(epoll_event));
    SetFlashMode();
    ev.data.fd = g_Control.m_SocketListen;
    ev.events =EPOLLIN|EPOLLET;
    result = epoll_ctl(g_Control.m_ListenEpoll,EPOLL_CTL_ADD,g_Control.m_SocketListen,&ev);
    CHECK_CALL(result);
    result = pthread_create(&g_Control.m_ThreadMgt.m_AcceptThreadFd,NULL,g_Control.m_ThreadMgt.m_AcceptThread.function,NULL);
    CHECK_CALL(result);
    result = pthread_create(&g_Control.m_ThreadMgt.m_ExecuteThreadFd,NULL,g_Control.m_ThreadMgt.m_ExecuteThread.function,NULL);
    CHECK_CALL(result);

    pthread_join(g_Control.m_ThreadMgt.m_AcceptThreadFd,NULL);
    pthread_join(g_Control.m_ThreadMgt.m_ExecuteThreadFd,NULL);

    return 0;
}
