# Learning Apue

## UNIX apue配置

deepin 环境下

> apt-get install libbsd-dev

**如果不执行上面步骤可能会出现如下问题**

``` c++
barrier.c:(.text+0x6e): undefined reference to `heapsort’
collect2: ld
make[1]: *** [barrier] 
make[1]: Leaving directory `/home/albert/Documents/progs/apue.3e/threads’
make: *** [all] 
```
**复制相关头文件到/usr/include等**

>  cp ./include/apue.h /usr/include

> cp ./lib/libapue.a /usr/local/lib

**搭建成功，测试**
```c++
gcc 1-3.c -o 1-3 -lapue
# 编译连接后
./1-3 /lib 
# 查看是否正常执行程序
```

**over**