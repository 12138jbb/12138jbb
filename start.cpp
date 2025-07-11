//我认识C语言开始


/*
#include语句是C预处理器指令(preprocessor directive)的一个例子，这些是编译器在编译代码之前要做的准备工作，称之为预处理(preprocessing)


/
/

再来说说stdio.h这个文件，不用觉得奇怪，它和我们平常见到的123.txt并无差别，只是后缀名不同而已，
这个名字表示：标准输入输出头文件，正如英文：standard input/output header，它包含了与输入输出相关的函数(比如printf)的信息
在C语言的世界中，人们称出现在文件顶部的信息集合为头(header)，C实现通常都带有多个头文件。
*/
#include<stdio.h>     

/*
引入头文件

意思是：本行代码将告诉编译器引入一个stdio.h的文件(就像我们电脑中的123.txt一样)的全部内容。
stdio.h文件是所有C语言编译器的标准部分，用来提供输入和输出的支持。


*/


int main(void)     /*一个简单的C程序*/

/*C程序规定一个程序中有一个或多个函数，他们是C程序的基本模块。但必须有且只有一个main函数。因为C程序的执行将从main函数开始，到main函数结束而停止。*/ 
{
    int number;     /*定义个名字叫做number的变量*/
    number=2024;     /*给number赋一个值*/
    printf("Hello ! I am 景彬彬\n");     /*调用printf()函数，为函数调用语句*/
    printf("This year is %d\n",number);
    return 0;
} 






