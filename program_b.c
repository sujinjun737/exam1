/* program_b 接收端；收到选项参数后，启动子进程执行file_info.so的print_file_info函数。*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "return_error.h"

int main() {
    // 创建命名管道
    mkfifo("/tmp/pipe", 0666);

    int fd = open("/tmp/pipe", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open pipe");
        return FOP;
    }

    // 读取选项参数
    char options[100];
    read(fd, options, sizeof(options));//没有了"\0"终止符
    close(fd);

    // 启动子进程执行file_info.so的print_file_info函数
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return FF;
    } 
    else if (pid == 0) {
        // 子进程
        execl("./program_b_child", "program_b_child", options, NULL);// 启动子进程执行file_info.so的print_file_info函数
        perror("Exec failed");
        return EF;
    }

    return 0;
}
