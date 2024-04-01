# 定义编译器和编译选项
CXX = g++
CFLAGS = -Wall -std=c++11

# 源文件和目标文件的列表
SRC_FILES = $(wildcard *.cpp)
EXE_FILES = $(patsubst %.c,%,$(SRC_FILES))

# 默认目标：编译所有可执行文件
all: $(EXE_FILES)

# 编译每个可执行文件
%: %.cpp
	$(CXX) $(CFLAGS) -o $@ $<

# 运行可执行文件
# run: all
# 	@for exe in $(EXE_FILES); do \
# 		./$$exe; \
# 	done

run:
	./$(filter-out $@,$(MAKECMDGOALS))

# 清理生成的文件
clean:
	rm -f $(EXE_FILES)

%: Makefile

# 防止make误解文件名为clean
.PHONY: clean run

