#ifndef PRINT_FILE_INFO_H
#define PRINT_FILE_INFO_H
/*
 * 函数名print_file_info(con1 char *dir, const char *file_name)
 * 函数功能：将目录dir下所有文件大小和文件类型输出到指定文件file_name中;
 * 输出格式：含路径的文件名-->文件大小-->文件类型标识
 */
int print_file_info(const char *dir, const char *file_name);

#endif