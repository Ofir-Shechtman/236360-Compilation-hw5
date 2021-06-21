#include "global.hpp"

void load_global(){
    std::istringstream file("declare i32 @printf(i8*, ...)\n"
                       "declare void @exit(i32)\n"
                       "@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"\n"
                       "@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"\n"
                       "\n"
                       "define void @printi(i32) {\n"
                       "    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0\n"
                       "    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)\n"
                       "    ret void\n"
                       "}\n"
                       "\n"
                       "define void @print(i8*) {\n"
                       "    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0\n"
                       "    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)\n"
                       "    ret void\n"
                       "}");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        CodeBuffer::instance().emitGlobal((iss.str()));
    }
}

