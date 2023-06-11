
# 重构脚本语言
- 过渡到java
# ep1：如何使用g4描述 形如{1,2,{3,4..}...}的数组，并在listener中print
```bash
D:\Temp\compiler-front\day4\ep1>antlr4 ArrayInit.g4
D:\Temp\compiler-front\day4\ep1>java org.antlr.v4.Tool ArrayInit.g4
```
生成包含ArrayListener接口和一个ArrayBaseListener基类。
需要编写一个Listener类，实现ArrayListener接口，并覆盖enterArray方法，以在解析数组时进行打印
