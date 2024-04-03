# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall

# 定义源文件和目标文件
SRCDIR = src
INCDIR = include
LIBDIR = lib
BINDIR = bin

# 将源文件列表映射到目标文件列表
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(LIBDIR)/%.o,$(SRCS))

# 定义目标文件
TARGET = $(BINDIR)/main
ENTRY = main.c
LIBRARY = $(LIBDIR)/libcal.so

# 默认目标
all: $(LIBRARY) $(TARGET)

# 生成目标文件
$(LIBDIR)/%.o: $(SRCDIR)/%.c | $(LIBDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -fPIC -c $< -o $@

# 生成动态库
$(LIBRARY): $(OBJS) | $(LIBDIR)
	$(CC) -shared -o $@ $^

# 生成可执行文件
$(TARGET): $(LIBRARY) | $(BINDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -L$(LIBDIR) $(ENTRY) -lcal -o $@


# 创建目标文件夹
$(BINDIR):
	mkdir -p $(BINDIR)
$(LIBDIR):
	mkdir -p $(LIBDIR)

# 清理生成的文件
clean:
	rm -rf $(BINDIR) $(LIBDIR) $(TARGET)

.PHONY: all clean
