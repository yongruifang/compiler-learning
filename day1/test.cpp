#include "TokenReader.h"

int main(){
    string str = "age >= 45";
    TokenReader reader(str);
    reader.dump();
    return 0;
}
/**
 * 编译执行
PS D:\Temp\compiler-front\day1> g++ test.cpp TokenReader.cpp -o test
PS D:\Temp\compiler-front\day1> ./test
"age" ">=" "45" 
*/