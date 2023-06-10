#include "SimpleLexer.h"
int main()
{
    string str[4] = {
        "2+3*5",
        "2+3+4+5*6+7*8",
        "int a = 2+3*5",
        "a=2+3+5"
    };
    SimpleLexer lexer;
    ASTNode *root = lexer.parse(str[3]);
    root->dump(root,"");
    //root->evaluate(root,"");
    return 0;
}
/** str[0] : 2+3*5
PS D:\Temp\compiler-front\day2> g++ .\test.cpp .\SimpleLexer.cpp .\ASTNode.cpp ..\day1\TokenReader.cpp -o test
PS D:\Temp\compiler-front\day2> .\test    
Additive +
        IntLiteral 2
        Multiplicative *
                IntLiteral 3
                IntLiteral 5 
*/
/** str[1] : 2+3+4+5*6+7*8
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
/** str[2] : int a = 2+3*5
(base) PS D:\Temp\compiler-front\day2> .\test                                      
IntDeclaration a
        Additive +
                IntLiteral 2
                Multiplicative *
                        IntLiteral 3
                        IntLiteral 5
*/
/** 计算 str[1] : 2+3+4+5*6+7*8 
Compute: Program
        Compute: Additive
                Compute: Additive
                        Compute: Additive
                                Compute: Additive
                                        Compute: IntLiteral
                                        Result: 2
                                        Compute: IntLiteral
                                        Result: 3
                                Result: 5
                                Compute: IntLiteral
                                Result: 4
                        Result: 9
                        Compute: Multiplicative
                                Compute: IntLiteral
                                Result: 5
                                Compute: IntLiteral
                                Result: 6
                        Result: 30
                Result: 39
                Compute: Multiplicative
                        Compute: IntLiteral
                        Result: 7
                        Compute: IntLiteral
                        Result: 8
                Result: 56
        Result: 95
Result: 95
*/
/**
 * str[3]: a=2+3+5
(base) PS D:\Temp\compiler-front\day2> ./test                                      
Program root
        AssignmentStmt a
                Additive +
                        Additive +
                                IntLiteral 2
                                IntLiteral 3
                        IntLiteral 5
*/
