# 使用前端工具Antlr
- 支持广泛的目标语言
- 语法简单
[官方文档](https://github.com/antlr/antlr4/blob/master/doc/getting-started.md)
```bash
D:\component\antlr\test>grun Hello r -tree
D:\component\antlr\test>java org.antlr.v4.gui.TestRig Hello r -tree
hello fangyron
^Z
(r hello fangyron)

D:\component\antlr\test>java org.antlr.v4.gui.TestRig Hello r -gui
hello fangyron
^Z

```
## Test
```bash
D:\Temp\compiler-front\day3>antlr4 Test.g4

D:\Temp\compiler-front\day3>java org.antlr.v4.Tool Test.g4

D:\Temp\compiler-front\day3>javac Test*.java
```
- 脚本文件 test.play
int age = 45;
if (age >= 17+8+20){
  printf("Hello old man!");
}
```bash
D:\Temp\compiler-front\day3>grun Test tokens -tokens test.play

D:\Temp\compiler-front\day3>java org.antlr.v4.gui.TestRig Test tokens -tokens test.play
[@0,0:2='int',<'int'>,1:0]
[@1,4:6='age',<Id>,1:4]
[@2,8:8='=',<'='>,1:8]
[@3,10:11='45',<IntLiteral>,1:10]
[@4,12:12=';',<';'>,1:12]
[@5,15:16='if',<'if'>,2:0]
[@6,18:18='(',<'('>,2:3]
[@7,19:21='age',<Id>,2:4]
[@8,23:24='>=',<RelationalOP>,2:8]
[@9,26:27='17',<IntLiteral>,2:11]
[@10,28:28='+',<'+'>,2:13]
[@11,29:29='8',<IntLiteral>,2:14]
[@12,30:30='+',<'+'>,2:15]
[@13,31:32='20',<IntLiteral>,2:16]
[@14,33:33=')',<')'>,2:18]
[@15,34:34='{',<'{'>,2:19]
[@16,39:44='printf',<Id>,3:2]
[@17,45:45='(',<'('>,3:8]
[@18,46:61='"Hello old man!"',<StringLiteral>,3:9]
[@19,62:62=')',<')'>,3:25]
[@20,63:63=';',<';'>,3:26]
[@21,66:66='}',<'}'>,4:0]
[@22,67:66='<EOF>',<EOF>,4:1]
```

# 生成语法分析器
```bash
D:\Temp\compiler-front\day3>cd antlrtest

D:\Temp\compiler-front\day3\antlrtest>antlr4 PlayScript.g4

D:\Temp\compiler-front\day3\antlrtest>java org.antlr.v4.Tool PlayScript.g4

D:\Temp\compiler-front\day3\antlrtest>cd ..

D:\Temp\compiler-front\day3>javac antlrtest/*.java

D:\Temp\compiler-front\day3>grun antlrtest.PlayScript expression -gui

D:\Temp\compiler-front\day3>java org.antlr.v4.gui.TestRig antlrtest.PlayScript expression -gui
age+10*2+10
^Z

D:\Temp\compiler-front\day3>
```