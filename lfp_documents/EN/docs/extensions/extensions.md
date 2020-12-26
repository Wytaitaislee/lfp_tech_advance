---
typora-copy-images-to: ..\res
---

### 通用知识积累过程

#### UNIX 体系结构


#### 文件I/O

 - 不带缓冲的I/O文件操作接口：open、read、write、lseek、close

 - int open(const char* pathname, int oflag, ... /* mode_t mode */);
 
 - 文件描述符 fd >=0 (非负整数)

 - POSIX标准输入、输出、错误   
    1. 头文件<apue.h>包含头文件<unistd.h>
    2. 幻数STDIN_FILENO、STDOUT_FILENO、STDERR_FILENO在<unistd.h>中定义， 对应POSIX的0，1，2;
    3. 尝试使用read从STDIN_FILENO读取数据，并使用write写入到STDOUT_FILENO;

</br\n>

 - lseek 三种定位方式lseek(int fd, off_t offset, int whence), whence -- > offset
  
    1. SEEK_SET, 从文件*开始*位置，偏移offset字节；
    2. SEEK_CUR，从文件*当前*位置，偏移offset个字节，offset**可正可负**；
    3. SEEK_END，从文件*末尾*(文件长度)位置，偏移offset个字节，offset**可正可负**；

</br\n>

 - dup(int fd) 和 dup2(int fd, int fd2) : 复制一个现有文件描述符

    1. dup返回系统中可分配的最小fd；
    2. dup2 使用指定的fd2的值，替换fd的值；   --- > fd搬移可以用到

</br\n>

 - sync、fsync、fdatasync ： 将缓冲区数据写入到磁盘上；   
    
    1. sync();   fsync(fd); fdatasync(fd);
    2. delayed write -- 延迟写，提高效率；
    3. sync - 将所有修改过的缓冲区**排入写队列，立刻返回，并不等待实际写磁盘操作完成**，系统守护进程(update)周期性（一般每隔30s）调用一次sync，保证定期冲刷数据；
    4. fsync - 只对fd关联的文件起作用，并**等待写磁盘操作结束才返回**;
    5. fdatasync - 和fsync类似，只写入文件相关，fsync还会同步更新文件属性；

</br\n>

 - fcntl : 改变已经打开文件的属性
    1. <fcntl.h>;
    
    2. int fnctl(int fd, int cmd, ... /* int arg */);
    
        ![fcntl](C:%5Cwytaitai%5Cwytaitaislee%5Cmy_program%5Cc%5Clfp_documents%5CCN%5Cdocs%5Cres%5Cfcntl-1589096140366.jpg)
    
        <center> fcntl函数的5种功能 < /center >
    
</br\n>

 - ioctl : I/O操作杂物箱, 不能用其他函数表示的I/O操作通常都是用ioctl表示
        
#### 标准I/O库
 - FILE *fopen(const char *restrict pathname, const char *restrict type);
 
 - int getc(FILE *fp);  int fgetc(FILE *fp);  int getchar(FILE *fp);都可以实现每次一个字符I/O;
 
 - fgets(char *restrict buf, int n, FILE *restrict fp); 每次一行I/O;
 
 - fputs(const char *restrict str, FILE *restrict fp);

 - 二进制I/O ：size 为数据结构的长度，nobj为要写入的对象个数；
    
    1. size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
    2. size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
    3.  int fseek(FILE *fp, long offset, int whence);

 - 格式化I/O
   1. printf、fprintf、dprintf、sprintf、snprintf等；


</br\n>

#### 文件I/O和标准I/O比较
 - open & fopen:
    1. open的flag使用形如O_RDONLY, O_WRONLY, O_RDWR;
    2. fopen的type使用形如"r"、"r+"、"w+"等； 


#### 文件和目录

 - 读取目录 : 访问、遍历目录
    1. DIR *opendir(char *pathname);
    2. DIR *fdopendir(int fd, char *pathname);
    3. struct dirent *readdir(DIR *dp);
    4. int closedir(DIR *dp); 
    5. struct dirent 数据结构:
        
        ```
        struct dirent
        {
            ino_t d_ino;        /* i-node number */
            char d_name[];      /* null-terminated filename */
        };
        ```

#### 进程控制
 - 进程通过***fork***、***exec***函数簇(共7个)以及***waitpid***三个主要函数实现
    1. fork, ret = 0 ---> child process ---->  exec_x(...);
    2. fork, ret > 0 ---> parent process --->  ifwait? ---> waitpid(forkpid, ...), 等待指定子进程退出;
    3. fork, ret < 0 ---> error occurs.

 - excel家族
   1. 后缀"l"代表list也就是参数列表的意思，第一参数pathname字符指针所指向要执行的文件路径， 接下来的参数代表执行该文件时传递的参数列表：argv[0],argv[1]... 最后一个参数须用空指针NULL作结束(char *)0。

#### 信号的使用
- 通知进程发生了某种情况。进程处理信号的方式有三种：
    1. 忽略信号；---不推荐;
    2. 按系统默认方式处理； --- 例如对于除0， 默认为终止该进程;
    3. 提供一个函数，信号发生时调用该函数，这被称为捕捉该信号;

- signal 函数
  1. <signal.h>
   ```
   void (*signal(int signo, void (*func)(int)))(int); 
  ``` 
  2. 简化模型
    ```
    typedef void Sigfunc(int);
    Sigfunc *signal(int, Sigfunc *);
    ```