#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666


// 实现 客户端代码, 没有 错误处理

int main() {

    int cfd, sfd;
    int n;
    char buf[BUFSIZ];

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);  // 大小端转换
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

    connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

   while (1) {
        fgets(buf, sizeof(buf), stdin);  // 最多读 sizeof(buf) 知道遇到 eof or \n (包括\n) , 最后加一个 \0
        write(cfd, buf, strlen(buf));
        n = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, n);
   }

    close(cfd);
    return 0;
}