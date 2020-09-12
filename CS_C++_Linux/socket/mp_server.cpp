#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define SERV_PORT 6666

/*
多进程并发服务器
父进程等待连接
子进程和客户端交互
关键：僵尸进程处理，使用 信号
*/

// SIGCHLD(17) 回调函数
void wait_child(int signo) {
    // while ( waitpid(0, NULL, WNOHANG) );
    wait(NULL);
}

int main() {

    int sfd, cfd;
    sockaddr_in server_addr, clie_addr;
    socklen_t clie_socklen;
    
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sfd, (sockaddr*)&server_addr, sizeof(server_addr));

    listen(sfd, 128);

    while (1) {

        clie_socklen = sizeof(clie_addr);
        bzero(&clie_addr, sizeof(clie_addr));
        cfd = accept(sfd, (sockaddr*)&clie_addr, &clie_socklen);   // 父进程负责 等待 客户连接
        char clie_ip[100];
        inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_ip, sizeof(clie_ip));
        printf("client %s connected\n", clie_ip);
        pid_t pid = fork();
        if (pid<0) {
            perror("fork error");
            exit(-1);
        }
        else if (pid==0) {  // 子进程 负责读写 client socket 数据
            close(sfd);  // 子进程关闭 sfd
            char buf[1024];
            while (1) { 
                int n = read(cfd, buf, sizeof(buf));
                if (n==0) {  // client 关闭
                    printf("client %s close.\n", clie_ip);
                    exit(0);
                }
                else if (n==-1) {
                    perror("read error");
                    exit(-1);
                }
                for (int i=0;i<n;++i) {
                    buf[i] = toupper(buf[i]);
                }
                write(cfd, buf, n);
            }
            
        }
        else {
            close(cfd);  // 父进程关闭 已经连接的 cfd
            signal(SIGCHLD, wait_child);   // 注册信号回调函数
        }
    }
    return 0;
}
