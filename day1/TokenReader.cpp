#include "TokenReader.h"

TokenReader::TokenReader(string str_)
{
    str = str_;
    initMap();
    parse();
}
void TokenReader::initMap()
{
    tokenTypeMap[ID] = "ID";
    tokenTypeMap[ID_int] = "int";
    tokenTypeMap[GT] = "GT";
    tokenTypeMap[GE] = "GE";
    tokenTypeMap[EQ] = "EQ";
    tokenTypeMap[IntLiteral] = "IntLiteral";
    tokenTypeMap[Plus] = "Plus";
    tokenTypeMap[Minus] = "Minus";
    tokenTypeMap[Star] = "Star";
    tokenTypeMap[Slash] = "Slash";
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
            case ID_i:
                if(ch == 'n'){
                    token.text += ch;
                    token.state = ID_in;
                }else if(isdigit(ch) || isalpha(ch)){
                    token.text += ch;
                    token.state = ID;
                }else{
                    newState = initToken(ch);
                }
                break;
            case ID_in:
                if(ch == 't'){
                    token.text += ch;
                    token.state = ID_int;
                }else if(isdigit(ch) || isalpha(ch)){
                    token.text += ch;
                    token.state = ID;
                }else{
                    newState = initToken(ch);
                }
                break;
            case ID_int:
                if(isblank(ch)){
                    newState = initToken(ch);
                }else{
                    token.state = ID;
                    token.text += ch;
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
            case EQ:
                newState = initToken(ch);
                break;  
            case Plus:
            case Minus:
            case Star:
            case Slash:
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
        token.type = tokenTypeMap[token.state];
        tokens.push_back(token);
        token = Token();
    }
    token.state = INIT;
    //INIT状态的迁移逻辑
    if(isalpha(ch)){
        if(ch == 'i'){
            token.state = ID_i; //对字符i特殊处理
        }else{
            token.state = ID;
        }
        token.text = ch;
    }else if(isdigit(ch)){
        token.state = IntLiteral;
        token.text = ch;
    }else if(ch == '>'){
        token.state = GT;
        token.text = ch;
    }else if(ch == '='){
        token.state = EQ;
        token.text = ch;
    }else if(ch == '+'){
        token.state = Plus;
        token.text = ch;
    }else if(ch == '-'){
        token.state = Minus;
        token.text = ch;
    }else if(ch == '*'){
        token.state = Star;
        token.text = ch;
    }else if(ch == '/'){
        token.state = Slash;
        token.text = ch;
    }else{
        token.state = INIT; //忽视规则之外的字符
    }
    return token.state;
}
//==========状态迁移的逻辑完成=======================
void TokenReader::dump(){
    for (auto token: tokens){
        cout << token.type << ": " << token.text <<  endl;
    }
    cout << endl;
}