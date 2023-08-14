/* program_b_child.c是程序program_b的子进程，
这是一个使用动态链接库的子进程程序
通过调用名为print_file_info.so的共享库中的print_file_info函数来打印文件的信息。
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "return_error.h"

//定义一个函数指针类型，用于指向 print_file_info 函数。
typedef int (*print_file_info_ptr)(const char *, const char *);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s options\n", argv[0]);
        return WNP;
    }

    void *handle = dlopen("./print_file_info.so", RTLD_LAZY);
    if (handle == NULL) {
        perror("Failed to open library");
        return FOL;
    }

    print_file_info_ptr print_file_info = (print_file_info_ptr)dlsym(handle, "print_file_info");
    if (print_file_info == NULL) {
        perror("Failed to get symbol");
        return FGS;
    }

    char *options = argv[1];
    char dir[100], file_name[100];
    sscanf(options, "-d %s -f %s", dir, file_name);

    print_file_info(dir, file_name);

    dlclose(handle);

    return 0;
}