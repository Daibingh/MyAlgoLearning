#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void fun(int signo) {
    printf("catch %d\n", signo);
}


// 信号捕捉
void test1() {
    signal(SIGINT, fun);
    while (1);
}


int main() {

    test1();
    return 0;
}