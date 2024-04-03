
## 动态库的使用

### 1. 生成动态库

```bash
$ cd build
$ gcc -fpic -c ../src/add.c ../src/sub.c ../src/mult.c ../src/div.c -I../include
$ gcc -shared -o libcal.so add.o sub.o mult.o div.o
```

### 2. 使用动态库

```bash
$ gcc ../main.c -I../include -o app
/usr/bin/ld: /tmp/ccLtppeN.o: in function `main':
main.c:(.text+0x3e): undefined reference to `add'
/usr/bin/ld: main.c:(.text+0x60): undefined reference to `subtract'
/usr/bin/ld: main.c:(.text+0x82): undefined reference to `multiply'
/usr/bin/ld: main.c:(.text+0xa4): undefined reference to `divide'
collect2: error: ld returned 1 exit status
```

```bash
$ gcc main.c -I../include -L./ -lcal -o app
```

### 3. 执行程序

```bash
$ ./app
./app: error while loading shared libraries: libcal.so: cannot open shared object file: No such file or directory
```

### 错误分析

* 静态库加载

静态库会在程序链接阶段将代码整合到可执行程序中，当可执行程序被加载，静态库中的代码也会被加载到内存。

* 动态库加载
1. 在gcc命令中虽然指定了库路径(使用参数`-L`), 但是这个路径并没有记录到可执行程序中，只是检查了这个路径下的库文件是否存在。
2. 同样对应的动态库文件也没有被打包到可执行程序中，只是在可执行程序中记录了库的名字。


### 两个重要的环境变量

`LIBRARY_PATH`: 在**编译期间**查找动态链接库时指定查找共享库的路径，例如 gcc 在编译期间用到动态链接库目录LIB1, 则设置为
```bash
$ export LIBRARY_PATH=LIB1:$LIBRARY_PATH
```

`LD_LIBRARY_PATH`: 在**加载运行期间**查找动态链接库时指定查找共享库的路径（这里指除系统默认路径之外的其他路径），`LD_LIBRARY_PATH` 中指定的路径会在系统默认路径之前进行查找, 通常缺省的目录为: `/usr/lib` 和 `/usr/local/lib`.
```bash
$ export LD_LIBRARY_PATH=LIB1:$LD_LIBRARY_PATH
```

Linux 运行时候是通过 `ld.so` 来寻找和加载动态链接库的，`ld.so` 在标准路径下 `/lib` 和 `/usr/lib` 寻找应用程序的共享库。

在非标准路径下 (`/lib` 和 `/usr/lib`)，Linux 通用的做法是将非标准路经加入 `/etc/ld.so.conf`，然后运行 `ldconfig` 生成 `/etc/ld.so.cache`。 `ld.so` 加载共享库的时会从 `ld.so.cache` 查找。`LD_LIBRARY_PATH` 是 Unix 遗留的方案，`ld.so` 加载时也会查找该路径。

比如安装了一个mysql到 `/usr/local/mysql`，mysql有一大堆library在 `/usr/local/mysql/lib` 下面，这时就需要在 `/etc/ld.so.conf` 下面加一行 `/usr/local/mysql/lib`，保存过后 `ldconfig` 一下，新的library才能在程序运行时被找到。

库搜索路径的确定有很多方法，还有如编译命令行 `rpath`参数。连接时的 `LD_RUN_PATH` 环境变量

