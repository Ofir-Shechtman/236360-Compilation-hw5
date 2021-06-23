#include "global.hpp"


void load_s(const string& s){
    std::istringstream file(s);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        CodeBuffer::instance().emitGlobal((iss.str()));
    }
}


void load_const(){
    load_s("declare i32 @printf(i8*, ...)\n"
                                "declare void @exit(i32)\n"
                                "@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"\n"
                                "@.DivisionByZero = constant [24 x i8] c\"Error division by zero\\0A\\00\"\n"
                                );
}

void load_funcs(){
    load_s("\n"
           "define void @printi(i32) {\n"
           "    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0\n"
           "    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)\n"
           "    ret void\n"
           "}\n"
           "\n"
           "define void @print(i8*) {\n"
           "    call i32 (i8*, ...) @printf( i8* %0)\n"
           "    ret void\n"
           "}\n"
           "define void @errorDivisionByZero() {\n"
           "    %spec_ptr = getelementptr [24 x i8], [24 x i8]* @.DivisionByZero, i32 0, i32 0\n"
           "    call void @print( i8* %spec_ptr)\n"
           "    call void @exit(i32 1)\n"
           "    ret void\n"
           "}"
           "\n");
}
