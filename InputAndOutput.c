#include<stdio.h>
#include<string.h>


#define FILE_NAME "./testio.dat"
#define NEW_FILE_NAME "./newfilename.dat"
#define NON_EXIST_FILE "./non_exist_file"
#define BUFF_SIZE 10


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


// 程序结束文件会自动关闭，但是调用abort结束程序时不会自动关闭
// 此外，还有打开文件数量的问题
// 所以一般都会关闭文件
fclose(stream);

if((stream = fopen(NON_EXIST_FILE, "r")) == NULL){
    printf("Can't open file %s\n", NON_EXIST_FILE);
}else{
    fclose(stream);
}
// 为什么要加这一行，不然会出错
// 因为上一行中stream被设置为了NULL
printf("stream is %p \n", stream);


stream = fopen(FILE_NAME, "a+");
fclose(stream);

printf("stream is %p \n", stream);

freopen(FILE_NAME, "w", stream);
// 换一种形式写法的fopen函数，返回值为第三个参数，无法打开文件时候返回值为NULL

// 关于临时文件的两个函数
// tmpfile
    // 返回临时文件的文件指针，以"wb+"的形式打开
FILE *tempstream = tmpfile();
// tmpfile无法知道文件名字，且无法永久保存
// 所以使用fopen代替，为了方便生成文件名，我们有函数tmpnam
fclose(tempstream);



char *filename;
filename = tmpnam(NULL); 
printf("%s\n", filename);
// 参数为空指针时候的用法

char filenamechar[L_tmpnam];
tmpnam(filenamechar);
printf("%s\n", filenamechar);


// 参数为字符数组时候的用法

// 为了计算机的性能，读和写的操作一般通过缓冲来实现
// 有一些用来控制缓冲的函数，一般很少使用

char buffer[BUFF_SIZE];
setvbuf(stream, buffer, _IOFBF, BUFF_SIZE);
// 第一个参数：与缓冲相关的流
// 第二个参数：缓冲区的地址，可以是任何储存期限的类型
// 第三个参数：缓冲类型
    // _IOFBF: 空时从流读入数据，满时向流写入数据
    // _IOLBF: 每次从流读入一行数据或者向流写入一行数据
    // _IONBF: 没有缓冲区
// 第四个参数：缓冲区字节数的大小
fprintf(stream, "test for setvbuf function\n");


// 控制清洗数据的频率
// 空指针时全部清洗，成功返回0，失败返回EOF
fflush(stream); 
fflush(NULL);

fclose(stream);

// 改名之前要关闭文件

rename(FILE_NAME, NEW_FILE_NAME);
if(argc > 1){
    remove(NEW_FILE_NAME);
}

/* 下面一部分改写格式化输入输出了 */



return 0;

}