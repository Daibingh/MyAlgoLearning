#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>

using namespace std;


void test1() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        cerr<<"error"<<endl;
        exit(1);
    }
    else if ( pid == 0 ) {
        cout<<"child, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }
    else {
        cout<<"parent, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }

    cout<<"=============end=============="<<endl;
}
    

// 循环创建子进程
void test2() {
    
    int n = 5;
    pid_t pid;
    int k = 0;
    for (int i=0;i<n;++i) {
        pid = fork();
        if (pid==0) {
            k = i;
            break;
        }
    }
    if (pid==0) {
        cout<<k<<" child, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }
    else {
        cout<<"parent, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }
    cout<<"=============end=============="<<endl;
}


// 进程回收

void test3() {
    int n = 5;
    pid_t pid;
    int k = 0;
    for (int i=0;i<n;++i) {
        pid = fork();
        if (pid==0) {
            k = i;
            break;
        }
    }
    if (pid==0) {
        cout<<k<<" child, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }
    else {
        while(wait(NULL)>0);  // 阻塞式回收, 成功返回 pid, 失败返回 -1
        cout<<"parent, pid="<<getpid()<<", ppid="<<getppid()<<endl;
    }
    cout<<"=============end=============="<<endl;

}


int main() {
    
    // test1();
    test3();

}