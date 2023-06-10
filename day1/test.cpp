#include "TokenReader.h"

int main(){
    string str[2] = {
        "age >= 45",
        "int age = 45"
    };
    TokenReader reader(str[1]);
    reader.dump();
    return 0;
}
/**
 * 编译执行
 * str[0]
PS D:\Temp\compiler-front\day1> g++ test.cpp TokenReader.cpp -o test
PS D:\Temp\compiler-front\day1> ./test
"age" ">=" "45" 
*/
/**
 * str[1]
PS D:\Temp\compiler-front\day1> g++ test.cpp TokenReader.cpp -o test
PS D:\Temp\compiler-front\day1> ./test
"int" "age" "=" "45" 
*/