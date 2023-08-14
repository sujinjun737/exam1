#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "print_file_info.h"
#include "return_error.h"
/*
 * 函数名print_file_info(con1 char *dir, const char *file_name)
 * 函数功能：将目录dir下所有文件大小和文件类型输出到指定文件file_name中;
 * 输出格式：含路径的文件名-->文件大小-->文件类型标识
 */

int print_file_info(const char *dir, const char *file_name) {
    FILE *output = fopen(file_name, "w");
    if (output == NULL) {
        perror("Failed to open output file");
        return FOF;
    }
    
    DIR *dirp = opendir(dir);
    if (dirp == NULL) {
        perror("Failed to open directory");
        fclose(output);
        return FOD;
    }
    
    struct dirent *entry;
    struct stat file_stat;
    char file_path[PATH_MAX];
    
    while ((entry = readdir(dirp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        snprintf(file_path, sizeof(file_path), "%s/%s", dir, entry->d_name);//目录路径和条目名称拼接	
        if (lstat(file_path, &file_stat) < 0)//获取文件的元数据消息
            continue;
        
        fprintf(output, "%s --> %ld --> ", file_path, file_stat.st_size);//输出文件路径和文件大小
        
        if (S_ISREG(file_stat.st_mode))
            fprintf(output, "Regular File\n");
        else if (S_ISDIR(file_stat.st_mode))
            fprintf(output, "Directory\n");
        else if (S_ISLNK(file_stat.st_mode))
            fprintf(output, "Symbolic Link\n");
        else if (S_ISCHR(file_stat.st_mode))
            fprintf(output, "Character Device\n");
        else if (S_ISBLK(file_stat.st_mode))
            fprintf(output, "Block Device\n");
        else if (S_ISFIFO(file_stat.st_mode))
            fprintf(output, "FIFO/Named Pipe\n");
        else if (S_ISSOCK(file_stat.st_mode))
            fprintf(output, "Socket\n");
        else
            fprintf(output, "Unknown File Type\n");
    }
    
    closedir(dirp);
    fclose(output);
    
    return 0;
}
