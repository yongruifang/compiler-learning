/**
 * Token流
*/
#ifndef TOKENREADER_H
#define TOKENREADER_H
#include <iostream>
#include <string>
#include <vector>
#include "ctype.h"
using namespace std;
// 通过枚举量 定义 状态
enum STATE
{
	INIT = 0, // 初始状态
	ID, ID_i, ID_in, ID_int,// 标识符状态
	GT, // 大于
	GE, // 大于等于
    EQ, // 等于
    IntLiteral // 数字字面量
};
// 
typedef struct {
    string text =  "";
    STATE state = INIT;
}Token;
class TokenReader{
private:
    string str;
    Token token;
    vector<Token> tokens;
    STATE initToken(char ch);// 开始解析的时候，进入初始状态；某个Token解析完毕，也进入初始状态
    void parse();  //状态转移的逻辑函数
public:
    TokenReader(string str_);//初始化
    ~TokenReader(){}
    void dump(); // 打印token列表
};
#endif