# 项目介绍

## 任务说明

1. 封装一个函数`int print_file_info(con1 char *dir, const char *file_name)`并编译为动态链接库file_info.so，实现要求如下：

    - 1.1 函数功能：将目录dir下所有文件大小和文件类型输出到指定文件file_name中；

    - 1.2 输出格式：含路径的文件名-->文件大小-->文件类型标识（参考ls命令）。

2. 编写程序program_a和program_b，程序program_a通过命令行获取选项参数，然后通过命名管道将选项参数传递给程序program_b，实现要求如下：

    - 2.1 程序program_a读取命令参数，如program_a -d . -f file_name；

    - 2.2 程序program_b收到选项参数后，启动子进程执行file_info.so的print_file_info函数。

3. 综合要求：

    - 3.1 题目1和题目2必须采用makefile文件一次性编译，即调用make命令后生成file_info.so、program_a和program_b；

    - 3.2 采用脚本启动和停止程序program_a和program_b，写在一个脚本内；

    - 3.3 程序program_a和program_b（及其子进程）需要在执行停止脚本时再退出，并且创建的资源须在退出时销毁。

## 文件与项目结构说明

### print_file_info

这是一个动态链接库 包含函数print_file_info

### program_a

选项参数发送端

### program_b

选项参数接收端

### program_b_child

program_b的子进程，通过调用名为print_file_info.so的共享库中的print_file_info函数来打印文件的信息。

### makefile

编译，make命令后生成file_info.so、program_a、program_b和program_b_child

### script.sh

运行/终止脚本

### return_error

返回错误码定义

## 使用说明

### 运行示例

```bash
make 
```

```bash
./script.sh start #输入下一个参数前注意换行
. #目录地址
output.txt #输出文件
```

```bash
./script.sh stop
```

```bash
./script.sh restart
```

### 输出结果

在.目录下可以看到多出了一个output.txt文件
