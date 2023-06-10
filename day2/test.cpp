#include "SimpleLexer.h"
#include "../day1/TokenReader.h"
int main()
{
    string str[2] = {
        "2+3*5",
        "2+3+4+5*6+7*8"
    };
    TokenReader reader(str[0]);
    //reader.dump();
    SimpleLexer lexer;
    ASTNode *root = lexer.additive(reader);
    root->dump(root,"");
    return 0;
}
/**
PS D:\Temp\compiler-front\day2> g++ .\test.cpp .\SimpleLexer.cpp .\ASTNode.cpp ..\day1\TokenReader.cpp -o test
PS D:\Temp\compiler-front\day2> .\test    
Additive +
        IntLiteral 2
        Multiplicative *
                IntLiteral 3
                IntLiteral 5 
*/
