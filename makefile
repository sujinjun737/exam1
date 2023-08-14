.PHONY: all clean

#编译参数
CC := gcc
CFLAGS := -Wall -o
LDFLAGS := -ldl
SHARE := -fPIC -shared -o

#共享库
SOURCE_LIB:= print_file_info.c
LIB := print_file_info.so

#发送端A
SOURCE_A := program_a.c 
OBJ_A := program_a 

#接收端B
SOURCE_B := program_b.c 
OBJ_B := program_b

#program_b的子进程
SOURCE_C := program_b_child.c 
OBJ_C := program_b_child

#管道
MY_PIPE := /tmp/pipe


all: $(LIB) $(OBJ_A) $(OBJ_B) $(OBJ_C)

$(LIB): $(SOURCE_LIB)
	$(CC) $(SHARE) $(LIB) $(SOURCE_LIB)

$(OBJ_A): $(SOURCE_A) 
	$(CC) $(CFLAGS) $(OBJ_A) $(SOURCE_A)

$(OBJ_B): $(SOURCE_B) 
	$(CC) $(CFLAGS) $(OBJ_B) $(SOURCE_B)

$(OBJ_C): $(SOURCE_C)
	$(CC) $(CFLAGS) $(OBJ_C) $(SOURCE_C) $(LDFLAGS)

clean:
	-rm -f $(LIB) $(OBJ_A) $(OBJ_B) $(OBJ_C) $(MY_PIPE)

