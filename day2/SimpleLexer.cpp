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
            child = assignmentStatement(reader);
        }
        if(child == NULL){
            throw std::runtime_error("unknown statement");
        }else{
            node->addChild(child);
        }
    }
    return node;
}
/**
 * 解析赋值语句
 * assignmentStatement -> Identifier = additive ;
*/
ASTNode* SimpleLexer::assignmentStatement(TokenReader& reader)
{
    ASTNode* node = NULL;
    Token token = reader.peek(); //预读
    if(token.type == "ID"){
        token = reader.read(); //消耗标识符
        node = new ASTNode(token.text, ASTNodeType::AssignmentStmt);
        token = reader.peek(); //预读
        if(token.type == "EQ"){
            reader.read(); //消耗等号
            ASTNode* child = additive(reader); //解析表达式
            if(child == NULL){
                throw std::runtime_error("invalide assignment statement, expecting an expression");
            }
            else{
                node->addChild(child);
                if(reader.peek().type == "SemiColon"){
                    reader.read(); //消耗分号
                }else{ // 报错，缺少分号
                    throw std::runtime_error("invalid statement, expecting semicolon");
                }
            }
        }else{
            reader.unread(); //回溯
            node = NULL;
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
        if(token.type == "Plus" || token.type == "Minus"){// 读出加减号
            token = reader.read(); 
            ASTNode* child2 = multiplicative(reader);
            if(child2 != NULL){ 
                node = new ASTNode(token.type, ASTNodeType::Additive);
                node->addChild(child1);
                node->addChild(child2);
                child1 = node; 
            }
        }
        else{
            break;
        }
    }
    if(reader.peek().text != "" && reader.peek().type != "SemiColon"){
        reader.unread();
        return NULL;
    }
    return node;
}
/**
 * 解析乘法表达式
 * multiplicative -> primary | primary * multiplicative
*/
ASTNode* SimpleLexer::multiplicative(TokenReader& reader)
{
    ASTNode* child1 = primary(reader); //应用primary规则
    ASTNode* node = child1;
    while(true)
    {
        Token token = reader.peek(); //预读
        if(token.type == "Star" || token.type == "Slash") //读出乘除号
        {
            Token token = reader.read();//消耗
            ASTNode *child2 = NULL;
            child2 = primary(reader); //解析右侧乘法因子
            if(child2 != NULL) //如果成功读出右侧乘法因子
            {
                node = new ASTNode(token.type, ASTNodeType::Multiplicative);
                node->addChild(child1);
                node->addChild(child2);
                child1 = node;
            }else{
                throw std::runtime_error("invalid multiplicative expression, expecting the right part.");
            }
        }
        else break;
    }
    return node;
}
/**
 * 解析基础表达式
*/
ASTNode* SimpleLexer::primary(TokenReader& reader)
{
    Token token = reader.peek(); //预读
    ASTNode* node = NULL;
    if(token.type == "Digit"){
        token = reader.read(); //消耗
        node = new ASTNode(token.text, ASTNodeType::IntLiteral);
    }else if(token.type == "ID"){
        token = reader.read(); //消耗
        node = new ASTNode(token.text, ASTNodeType::Identifier);
    }
    return node;
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
                    throw std::runtime_error("invalide variable initialization, expecting an expression");
                }
                else{
                    node->addChild(child);
                }
            }
       } else{
            throw std::runtime_error("variable name expected");
       }
       if(node != NULL){
            if(reader.peek().type == "SemiColon"){
            reader.read(); //消耗分号
            }else{ // 报错，缺少分号
            throw std::runtime_error("invalid statement, expecting semicolon");
            }
       }
    }
    return node;
}