#ifndef TCP_HTTP_MAIN_H
#define TCP_HTTP_MAIN_H

#include <sys/epoll.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
using namespace  std;
typedef char* Str;


///*节点类型*/
//#define RW      2
//#define EXECUTE 1

#define P    pthread_mutex_lock
#define V    pthread_mutex_unlock
#define IN
#define OUT
#define CHECK_CALL(val)                     \
    do {                                    \
        if ((val) < 0) {                    \
            ErrorPrint(__FILE__, __LINE__); \
            exit(1);                        \
        }                                   \
    } while (0)

class Http{
public:
    string m_First;
    string m_Head;
    string m_Enter;
    string m_Body;
    long long GetSize();
};

long long Http::GetSize() {
    return m_First.length()+m_Head.length()+m_Enter.length()+ m_Body.length();
}

//struct QNode{
//    int m_type;
//    int m_clientSocket;
//    union{
//        //执行队列
//        struct{
//            Http m_Http;
//        };
//        //读写队列
//        struct{
//            Str m_FilName;
//            Str m_Data;
//        };
//    };
//};

//struct Queue{
//    QNode m_Front;
//    QNode* m_Rear;
//};
//
//class QueueMgt {
//public:
//    QueueMgt();
//    //读写队列
//    Queue m_RWQueue;
//    pthread_mutex_t m_RWQueuePV;
//    //执行队列
//    Queue m_ExecutQueue;
//    pthread_mutex_t m_ExecuteQueuePV;
//};

struct Thread{
    void*(*function)(void* param);
    void* param;
};

class ThreadMgt {
public:
    ThreadMgt();
    Thread  m_AcceptThread;
    pthread_t m_AcceptThreadFd;
//    Thread  m_RWThread;
//    pthread_t m_RWThreadFd;
    Thread  m_ExecuteThread;
    pthread_t m_ExecuteThreadFd;
};

class InitInfo{
public:
    InitInfo();

    int   m_ListenProt;
    int   m_MaxClientNumber;
    int   m_HttpSize;
    Str   m_WWWRoot;
};

class Control{
public:
    Control();

    ThreadMgt  m_ThreadMgt;
   // QueueMgt   m_QueueMgt;
    InitInfo   m_InitInfo;

    pthread_mutex_t    m_printPv;
    int     m_SocketListen; //初始化后 开始监听
    int     m_ListenEpoll;
    int     m_ClientEpoll;


}g_Control;


void SetFlashMode();
void ErrorPrint(const Str file , int line);
void* AcceptThread(void * param);
void* ExecuteThread(void *param);
void* RWThread(void *param);

#endif //TCP_HTTP_MAIN_H



