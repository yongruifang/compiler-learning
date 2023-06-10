# 手工打造公式计算器
## 解析算术表达式
2 + 3 * 5
- 目标 输出AST
Additive +
  IntLiteral 2
  Multicative *
    IntLiteral 3
    IntLiteral 5

## 解析变量声明语句
int age = 45
- 目标，输出AST
Programm Calculator
    IntDeclaration age
        AssignmentExp =
            IntLiteral 45

- 递归下降
intDeclaration ::= Int Identifier ('=' additiveExpression)?;
```c

//伪代码
MatchIntDeclare(){
  MatchToken(Int)；        //匹配Int关键字
  MatchIdentifier();       //匹配标识符
  MatchToken(equal);       //匹配等号
  MatchExpression();       //匹配表达式
}
```

# 支持赋值语句
age = 45

# 在表达式中可以使用变量
age + 10 * 2
- 为了给变量赋值，以及在表达式中引用变量，需要存储

# 实现一个CLI
- 简单的REPL
输入、执行、打印的循环过程
Read-Eval-Print Loop


