#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 8192
#define SERV_PORT 6666

struct s_info {
    struct sockaddr_in cliaddr;
    int fd;
};

void *do_work(void *arg) {
    int n, i;
    struct s_info* ts = (struct s_info*)arg;
    char buf[MAXLINE];
    char str_ip[16];
    inet_ntop(AF_INET, &ts->cliaddr.sin_addr.s_addr, str_ip, sizeof(str_ip));
    int port = ntohs(ts->cliaddr.sin_port);
    while (1)
    {
        n = read(ts->fd, buf, sizeof(buf));
        if (n==0) {
            printf("client %s:%d close.\n", str_ip, port);
            break;
        }
        printf("received from %s:%d %d bytes.\n", str_ip, port, n);
        for (int i=0;i<n;++i) {
            buf[i] = toupper(buf[i]);
        }
        write(ts->fd, buf, n);
        write(STDOUT_FILENO, buf, n);
    }
    close(ts->fd);
    return (void*)0;
}


int main() {
    sockaddr_in servaddr, cliaddr;
    int sfd, cfd;
    pthread_t tid;
    s_info ts[256];
    int i = 0;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind( sfd, (sockaddr*)&servaddr, sizeof(servaddr) );

    listen(sfd, 128);

    socklen_t clia_socklen = sizeof(cliaddr);
    while (1) {
        cfd = accept(sfd, (sockaddr*)&cliaddr, &clia_socklen);
        ts[i].fd = cfd;
        ts[i].cliaddr = cliaddr;

        pthread_create(&tid, NULL, do_work, &ts[i]);
        pthread_detach(tid);   // 子线程分离，防止僵尸线程
        ++i;
    }
    return 0;
}