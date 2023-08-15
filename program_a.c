/* 程序program_a读取命令参数，如progrm_a -d . -f file_name; */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "return_error.h"

int main(int argc, char *argv[]) {//argc表示参数的个数,argv[]是一个包含参数字符串的数组
    if (argc != 5) {
        printf("Usage: %s -d <dir> -f <file_name>\n", argv[0]);
        return WNP;
    }

    char *dir = argv[2];
    char *file_name = argv[4];

    // 创建命名管道
    mkfifo("/tmp/pipe", 0666);
    
    int fd = open("/tmp/pipe", O_WRONLY);// 以只读方式打开管道
    if (fd < 0) {
        perror("Failed to open pipe");// 打开管道失败时，输出错误信息
        return FOP;
    }

    // 将选项参数传递给程序progam_b
    char options[100];
    snprintf(options, sizeof(options), "-d %s -f %s", dir, file_name);
    write(fd, options, strlen(options) + 1);//会有一个"\0"终止符

    close(fd);

    return 0;
}
