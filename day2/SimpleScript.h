#ifndef SIMPLESCRIPT_H
#define SIMPLESCRIPT_H
#include "SimpleLexer.h"
#include<iostream>
#include<string>
#include<map>
using namespace std;
/**
 * 一个简单的脚本解释器。
 * 你可以依次敲入命令。比如：
 * > 2+3;
 * > int age = 10;
 * > int b;
 * > b = 10*2;
 * > age = age + b;
 * > exit();  //退出REPL界面。
 * 你还可以使用一个参数 -v，让每次执行脚本的时候，都输出AST和整个计算过程。
 */
class SimpleScript
{
private:
    map<string, int> variables;
    bool verbose = false;
public:
    /**
     * 启动
    */
    void start(bool verbose_);
    /**
     * 遍历AST，计算值
    */
    int evaluate(ASTNode* node, string indent);
};
#endif