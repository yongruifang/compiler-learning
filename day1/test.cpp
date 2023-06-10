#include "TokenReader.h"

int main(){
    string str[3] = {
        "age >= 45",
        "int age = 45",
        "2 + 3 * 5"
    };
    TokenReader reader(str[2]);
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
/**
 * str[2]
PS D:\Temp\compiler-front\day1> g++ test.cpp TokenReader.cpp -o test
PS D:\Temp\compiler-front\day1> ./test
"2" "+" "3" "*" "5" 
*/