#include<stdio.h>

#define INPUT_FILE "inputfile.dat"
#define OUTPUT_FILE "outputfile.dat"

#define FILE_NAME "./testio.dat"
#define NON_EXIST_FILE "./non_exist_file"


// argc 表示参数的数量
// argv 表示参数的字符串数组
    // argv[argc] = NULL
    // 重定向的操作不算参数，所谓神不知鬼不觉
int main(int argc, char* argv[]){

// 流是任意输出的源和任意输出的目的地
    // 其中标准流有 stdin stdout stderr
        // 默认是
            // stdin 键盘输入
            // stdout stderr 屏幕输出
        // 可以通过重定向改变
// 流在c语言中是文件指针
FILE *stream;

// 一般的文件有两种，文本文件和二进制文件
    // 文本文件
        // 每一行以一到两个特殊字符结尾
        // 文本文件可能包含一个特殊的文本结尾标记，也可能不包含
    // 二进制文件中所有字节都是被平等对待的，但是有时候实现方式和系统有关

// 文件打开有模式
    // 模式: 是以什么方式打开，打开的是什么类型的文件
        // 打开方式：读 写 追加

stream = fopen(FILE_NAME, "w+");
// fopen()函数将流与文件相关联，等于接通了一个管道
// 打不开文件时返回值为空
fclose(stream);

if((stream = fopen(NON_EXIST_FILE, "r")) == NULL){
    printf("Can't open file %s\n", NON_EXIST_FILE);
}

// 程序结束文件会自动关闭，但是调用abort结束程序时不会自动关闭
// 此外，还有打开文件数量的问题
// 所以一般都会关闭文件
fclose(stream);
stream = fopen(FILE_NAME, "a+");
fclose(stream);

freopen(FILE_NAME, "a+", stream);
// 换一种形式写法的fopen函数，返回值为第三个参数，无法打开文件时候返回值为NULL

// 关于临时文件的两个函数
// tmpfile
    // 返回临时文件的文件指针，以"wb+"的形式打开
FILE *tempstream = tmpfile();

// tmpfile无法知道文件名字，且无法永久保存
// 所以使用fopen代替，为了方便生成文件名，我们有函数tmpnam

char *filename;
filename = tmpnam(NULL); 
printf("%s\n", filename);
// 参数为空指针时候的用法

char filenamechar[L_tmpnam];
tmpnam(filenamechar);
printf("%s\n", filenamechar);
// 参数为字符数组时候的用法





return 0;

}