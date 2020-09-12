#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6666


// 实现 服务器端代码, 没有 错误处理

int main() {

    int sfd, cfd;
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    char buf[BUFSIZ];
    int n, i;

    sfd = socket(AF_INET, SOCK_STREAM, 0);  // 创建 服务器 socket 文件

    serv_addr.sin_family = AF_INET;   // 初始化
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));  // socket 与 IP 端口绑定

    listen(sfd, 128);   // 设置同时最大连接数

    bzero(&clie_addr, sizeof(clie_addr));
    clie_addr_len = sizeof(clie_addr);
    cfd = accept(sfd, (struct sockaddr*)&clie_addr, &clie_addr_len);  // 阻塞等待连接

    char clie_ip[256];
    memset(clie_ip, 0, sizeof(clie_ip));
    printf("client IP: %s, client port: %d\n", 
                inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)), 
                ntohs(clie_addr.sin_port));

    while (1) {
        n = read(cfd, buf, sizeof(buf));  // 从客户socket文件读取数据
        for (i=0;i<n;++i) {
            buf[i] = toupper(buf[i]); 
        }
        write(cfd, buf, n);   // 向客户socket文件写数据
    }

    close(sfd);
    close(cfd);
    return 0;
}

// nc 0.0.0.0  6666 测试连接
