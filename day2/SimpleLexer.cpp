#include "SimpleLexer.h"
ASTNode* SimpleLexer::parse(string script)
{
    TokenReader reader(script);
    return program(reader);
}
/**
 * 统一入口
*/
ASTNode* SimpleLexer::program(TokenReader &reader)
{
    ASTNode* node = new ASTNode("root", ASTNodeType::Program);
    while(reader.peek().type != ""){
        ASTNode* child = intDeclaration(reader);
        if(child == NULL){
            child = additive(reader);
        }
        if(child == NULL){
            throw "unknown statement";
        }else{
            node->addChild(child);
        }
    }
    return node;
}
/**
 * 解析加法表达式
 * additive -> multiplicative | multiplicative + additive
*/
ASTNode* SimpleLexer::additive(TokenReader& reader)
{
    ASTNode* child1 = multiplicative(reader); //应用add规则
    if(child1 == NULL){
        return NULL;
    }
    ASTNode* node = child1;  
    //为什么初始化node为child1?
    //什么情况会直接return child1? 
    while(true){ //通过循环替代右递归
        Token token = reader.peek(); // 预读
        if(token.type == "Plus"){// 读出加号
            token = reader.read(); 
            ASTNode* child2 = multiplicative(reader);
            if(child2 != NULL){ 
                node = new ASTNode("+", ASTNodeType::Additive);
                node->addChild(child1);
                node->addChild(child2);
                child1 = node; 
            }
        }else{
            break;
        }
    }
    return node;
}
/**
 * 解析乘法表达式
 * multiplicative -> primary | primary * multiplicative
*/
ASTNode* SimpleLexer::multiplicative(TokenReader& reader)
{
    Token token = reader.peek();// 预读
    if(token.type == "Digit") // 读出数字
    {
        token = reader.read();// 消耗
        ASTNode* child1 = new ASTNode(token.text, ASTNodeType::IntLiteral);// 创建数字节点
        ASTNode* node = child1; 
        while(true)
        {
            Token token = reader.peek(); //预读
            if(token.type == "Star") //读出乘号
            {
                Token token = reader.read();//消耗乘号
                ASTNode *child2 = NULL;
                if(reader.peek().type =="Digit") //读出数字
                {
                    token = reader.read(); //消耗
                    child2 = new ASTNode(token.text, ASTNodeType::IntLiteral);
                } 
                if(child2 != NULL) //如果成功读出右侧乘法因子
                {
                    node = new ASTNode("*", ASTNodeType::Multiplicative);
                    node->addChild(child1);
                    node->addChild(child2);
                    child1 = node;
                }else{
                    throw "invalid multiplicative expression, expecting the right part.";
                }
            }
            else break;
        }
        return node;
    }
    return NULL;
}
/**
 * 解析整型变量声明语句
 * intDeclaration -> int Identifier ( = additive )? ;
*/
ASTNode* SimpleLexer::intDeclaration(TokenReader& reader)
{
    ASTNode *node = NULL;
    Token token = reader.peek(); //预读
    if(token.type == "int"){
       token = reader.read(); //消耗int
       if(reader.peek().type == "ID"){
            token = reader.read(); //消耗标识符
            node = new ASTNode(token.text, ASTNodeType::IntDeclaration);
            token = reader.peek(); //预读
            if(token.type == "EQ"){
                reader.read(); //消耗等号
                ASTNode* child = additive(reader); //解析表达式
                if(child == NULL){
                    throw "invalide variable initialization, expecting an expression";
                }
                else{
                    node->addChild(child);
                }
            }
       } else{
            throw "variable name expected";
       }
    }
    return node;
}