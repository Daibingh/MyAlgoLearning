#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <bits/stdc++.h>
#include <sys/mman.h>
 
#define MAX_DATA_LEN   256
#define DELAY_TIME 1

using namespace std;

// 进程间管道通信
void test1()
{
    pid_t pid;
    int pipe_fd[2];
    char buf[MAX_DATA_LEN];
    const char data[] = "Pipe Test Program";
    int real_read, real_write;
    memset((void*)buf, 0, sizeof(buf));
    /* 创建管道 */
    if (pipe(pipe_fd) < 0)
    {
        printf("pipe create error\n");
        exit(1);
    }
    if ((pid = fork()) == 0)
    {
        /* 子进程关闭写描述符，并通过使子进程暂停3s等待父进程已关闭相应的读描述符 */
        close(pipe_fd[1]);
        sleep(DELAY_TIME * 3);        
        /* 子进程读取管道内容 */
        if ((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
        {
            printf("%d bytes read from the pipe is '%s'\n", real_read, buf);
        }
        	
       /* 关闭子进程读描述符 */
        close(pipe_fd[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        /* 父进程关闭读描述符，并通过使父进程暂停1s等待子进程已关闭相应的写描述符 */
      close(pipe_fd[0]);
      sleep(DELAY_TIME);
 
      if((real_write = write(pipe_fd[1], data, strlen(data))) !=  -1)
	{
		printf("Parent wrote %d bytes : '%s'\n", real_write, data);
	}
		
      close(pipe_fd[1]);     /*关闭父进程写描述符*/
      waitpid(pid, NULL, 0); /*收集子进程退出信息*/
      exit(0);
     }   
}


int var = 100;

// 共享内存通信, 借助文件, 也可以借助 伪文件 /dev/zero
void test2() {

    int fd = open("CS_C++_Linux/IPC/tmp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd<0) {
        cerr<<"open error"<<endl;
        exit(1);
    }
    unlink("CS_C++_Linux/IPC/tmp");  // 删除临时目录项,使之具备释放条件
    ftruncate(fd, 4);                // 拓展文件大小

    int * p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p==MAP_FAILED) {
        cerr<<"map error"<<endl;
        exit(1);
    }
    close(fd);            // 映射完,关闭文件

    pid_t pid = fork();   // 创建子进程

    if (pid<0) {
        cerr<<"fork error"<<endl;
        exit(1);
    }
    else if (pid==0) {
        var = 200;
        *p = 500;
        cout<<"child, var="<<var<<", *p="<<*p<<endl;
    }
    else {
        sleep(1);
        cout<<"parent, var="<<var<<", *p="<<*p<<endl;
        wait(NULL);
        if(munmap(p, 4)==-1) { // 释放映射区
            cerr<<"unmap error"<<endl;
            exit(1);
        }
    }

}


// 共享内存通信, 匿名映射区, 不借助文件
void test3() {

    int * p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);  // 大小不限制，fd=-1
    if (p==MAP_FAILED) {
        cerr<<"map error"<<endl;
        exit(1);
    }

    pid_t pid = fork();   // 创建子进程

    if (pid<0) {
        cerr<<"fork error"<<endl;
        exit(1);
    }
    else if (pid==0) {
        var = 200;
        *p = 500;
        cout<<"child, var="<<var<<", *p="<<*p<<endl;
    }
    else {
        sleep(1);
        cout<<"parent, var="<<var<<", *p="<<*p<<endl;
        wait(NULL);
        if(munmap(p, 4)==-1) { // 释放映射区
            cerr<<"unmap error"<<endl;
            exit(1);
        }
    }

}


int main() {
    test3();
}