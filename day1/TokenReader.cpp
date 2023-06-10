#include "TokenReader.h"

TokenReader::TokenReader(string str_)
{
    str = str_;
    parse();
}
map<STATE, string> TokenReader::tokenTypeMap = {
    {ID, "ID"},
    {ID_int, "int"},
    {GT, "GT"},
    {GE, "GE"},
    {EQ, "EQ"},
    {Digit, "Digit"},
    {Plus, "Plus"},
    {Minus, "Minus"},
    {Star, "Star"},
    {Slash, "Slash"},
    {SemiColon, "SemiColon"}
};

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
                    newState = ID_in;
                }else if(isdigit(ch) || isalpha(ch)){
                    token.text += ch;
                    token.state = ID;
                    newState = ID;
                }else{
                    newState = initToken(ch);
                }
                break;
            case ID_in:
                if(ch == 't'){
                    token.text += ch;
                    token.state = ID_int;
                    newState = ID_int;
                }else if(isdigit(ch) || isalpha(ch)){
                    token.text += ch;
                    token.state = ID;
                    newState = ID;
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
            case SemiColon:
                newState = initToken(ch);
                break;
            case Digit:
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
    if(token.text.length()>0){ //最后一个token
        token.type = tokenTypeMap[token.state];
        tokens.push_back(token);
    }
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
        token.state = Digit;
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
    }else if(ch == ';'){
        token.state = SemiColon;
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
/**
 * 预读一个Token, 不移动指针
*/
Token TokenReader::peek()
{
	if (currentTokenIndex < tokens.size())
		return tokens[currentTokenIndex]; 
	return Token();
}
/**
 * 读取一个Token, 移动指针
*/
Token TokenReader::read() // next unit
{
	if (currentTokenIndex < tokens.size())
		return tokens[currentTokenIndex++];
	return Token();
}
/**
 * 撤销读取，回到上一个Token
*/
void TokenReader::unread()
{
	if (currentTokenIndex > 0)
		currentTokenIndex--;
}
/**
 * 获取当前Token的位置
*/
int TokenReader::GetCurrentToken()
{
	return currentTokenIndex;
}