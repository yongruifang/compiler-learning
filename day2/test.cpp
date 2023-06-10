#include "SimpleLexer.h"
#include "../day1/TokenReader.h"
int main()
{
    string str[3] = {
        "2+3*5",
        "2+3+4+5*6+7*8",
        "int a = 2+3*5"
    };
    TokenReader reader(str[2]);
    //reader.dump();
    SimpleLexer lexer;
    ASTNode *root = lexer.program(reader);
    root->dump(root,"");
    return 0;
}
/** str[0]
PS D:\Temp\compiler-front\day2> g++ .\test.cpp .\SimpleLexer.cpp .\ASTNode.cpp ..\day1\TokenReader.cpp -o test
PS D:\Temp\compiler-front\day2> .\test    
Additive +
        IntLiteral 2
        Multiplicative *
                IntLiteral 3
                IntLiteral 5 
*/
/** str[1]
Additive +
        Additive +
                Additive +
                        Additive +
                                IntLiteral 2
                                IntLiteral 3
                        IntLiteral 4
                Multiplicative *
                        IntLiteral 5
                        IntLiteral 6
        Multiplicative *
                IntLiteral 7
                IntLiteral 8
*/
/** str[2]
(base) PS D:\Temp\compiler-front\day2> .\test                                      
IntDeclaration a
        Additive +
                IntLiteral 2
                Multiplicative *
                        IntLiteral 3
                        IntLiteral 5
*/

