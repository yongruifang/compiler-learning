#include "SimpleLexer.h"
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
                Token tmpToken = reader.read();//消耗乘号
                ASTNode *child2 = NULL;
                token = reader.peek(); //预读
                if(token.type =="Digit") //读出数字
                {
                    token = reader.read(); //消耗
                    child2 = new ASTNode(token.text, ASTNodeType::IntLiteral);
                } 
                if(child2 != NULL) //如果成功读出右侧乘法因子
                {
                    node = new ASTNode(tmpToken.text, ASTNodeType::Multiplicative);
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