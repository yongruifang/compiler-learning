#include "SimpleLexer.h"
#include "SimpleScript.h"
int main()
{
    string str[5] = {
        "2+3*5",
        "2+3+4+5*6+7*8",
        "int a = 2+3*5",
        "a=2+3+5;",
        "100+2-3*50/2"
    };
//     SimpleLexer lexer;
//     ASTNode *root = lexer.parse(str[4]);
//     root->dump(root,"");
//     root->evaluate(root,"");
        SimpleScript script;
        script.start(true);
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
/**
 * str[4]: 100+2-3*50/2
Program root
        Additive Minus
                Additive Plus
                        IntLiteral 100
                        IntLiteral 2
                Multiplicative Slash
                        Multiplicative Star
                                IntLiteral 3
                                IntLiteral 50
                        IntLiteral 2
Compute: Program
        Compute: Additive
                Compute: Additive
                        Compute: IntLiteral
                        Result: 100
                        Compute: IntLiteral
                        Result: 2
                Result: 102
                Compute: Multiplicative
                        Compute: Multiplicative
                                Compute: IntLiteral
                                Result: 3
                                Compute: IntLiteral
                                Result: 50
                        Result: 150
                        Compute: IntLiteral
                        Result: 2
                Result: 75
        Result: 27
Result: 27
*/

/**
 *  脚本
(base) PS D:\Temp\compiler-front\day2> test
Simple Script Language!
Type 'exit();' to quit
verbse mode
>2+3
2+3
Compute: Program
        Compute: Additive
                Compute: IntLiteral
                Result: 2
                Compute: IntLiteral
                Result: 3
        Result: 5
Result: 5

>int a = 2+3;
int a = 2+3;
Compute: Program
        Compute: IntDeclaration
                Compute: Additive
                        Compute: IntLiteral
                        Result: 2
                        Compute: IntLiteral
                        Result: 3
                Result: 5
        Result: 5
Result: 5

>a = a + 3;
a = a + 3;
Compute: Program
        Compute: AssignmentStmt
                Compute: Additive
                        Compute: Identifier
                        Result: 5
                        Compute: IntLiteral
                        Result: 3
                Result: 8
        Result: 8
Result: 8
*/
