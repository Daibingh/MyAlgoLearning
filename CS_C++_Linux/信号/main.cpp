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


// alarm 定时
void catch_alarm(int signo) {}

void my_sleep(int n) {
    signal(SIGALRM, catch_alarm);
    alarm(n);
    pause();  // 挂起，等待某一信号
    printf("sleep %d\n", n);
}

void test2() {
    while (1) {
        my_sleep(3);
    }
}


int main() {

    test2();
    return 0;
}