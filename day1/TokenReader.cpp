#include "TokenReader.h"

TokenReader::TokenReader(string str_)
{
    str = str_;
    parse();
}
//============编写状态迁移的逻辑========================
void TokenReader::parse()
{
    STATE newState = INIT;
    for(size_t i = 0; i < str.length(); i ++)
    {
        char ch = str[i];
        switch(newState)
        {
            case INIT:
                newState = initToken(ch); //开局
                break;
            case ID:
                if(isalpha(ch) || isdigit(ch)){
                    token.text += ch;
                }else{
                    newState = initToken(ch);
                }
                break;
            case GT:
                if(ch == '='){
                    token.state = GE;
                    token.text += ch;
                    newState = GE;
                }else{
                    newState = initToken(ch);
                }
                break;
            case GE:
                newState = initToken(ch);
                break;
            case IntLiteral:
                if(isdigit(ch)){
                    token.text += ch;
                }else{
                    newState = initToken(ch);
                }
                break;
            default:
                break;
        }
    }
    initToken(' ');
}
STATE TokenReader::initToken(char ch)
{
    if(token.text.length()>0){ 
        tokens.push_back(token);
        token = Token();
    }
    token.state = INIT;
    //INIT状态的迁移逻辑
    if(isalpha(ch)){
        token.state = ID;
        token.text = ch;
    }else if(isdigit(ch)){
        token.state = IntLiteral;
        token.text = ch;
    }else if(ch == '>'){
        token.state = GT;
        token.text = ch;
    }else{
        token.state = INIT; //忽视规则之外的字符
    }
    return token.state;
}
//==========状态迁移的逻辑完成=======================
void TokenReader::dump(){
    for (auto token: tokens){
        cout << "\"" << token.text << "\" ";
    }
    cout << endl;
}