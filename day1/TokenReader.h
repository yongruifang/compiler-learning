/**
 * Token流
*/
#ifndef TOKENREADER_H
#define TOKENREADER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ctype.h"
using namespace std;
// 通过枚举量 定义 自动机状态

enum STATE
{
    INIT = 0, // 初始状态
    ID, ID_i, ID_in, ID_int,// 标识符状态
    GT, // 大于
    GE, // 大于等于
    EQ, // 等于
    Digit, // 数字字面量
    Plus, Minus, Star, Slash, // 四则运算符
    SemiColon, // 分号
};    


// 
typedef struct {
    string text =  "";
    STATE state = INIT; 
    string type = "";
}Token;
class TokenReader{
private:
    string str;
    Token token;
    vector<Token> tokens;
    int currentTokenIndex = 0;
    STATE initToken(char ch);// 开始解析的时候，进入初始状态；某个Token解析完毕，也进入初始状态
    void parse();  //状态转移的逻辑函数
    
public:
    static map<STATE, string> tokenTypeMap;
    TokenReader(string str_);//初始化
    ~TokenReader(){}
    void dump(); // 打印token列表
    // token流的功能函数
    Token read(); // 读取一个token
	Token peek(); // 预读一个token
	void unread(); // 撤销读取
	int GetCurrentToken(); // 获取当前token的位置
};
#endif