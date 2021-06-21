#ifndef HW5_REGISTERMANAGER_H
#define HW5_REGISTERMANAGER_H

using namespace std;

class Register{
public:
    unsigned int id;
    int bit_num;
    bool is_arg;
    string type() const;
    string name() const;
    string full_name() const;
    explicit Register(unsigned int id, int bit_num, bool is_arg=false):id(id), bit_num(bit_num), is_arg(is_arg){}
};

class RegisterManager {
    RegisterManager(): register_count(0){};
    int register_count;
public:
    RegisterManager(RegisterManager const &) = delete;
    void operator=(RegisterManager const &) = delete;
    static RegisterManager &instance();
    Register* alloc(int bit_num, bool is_arg=false);
    void reset();

};

#endif //HW5_REGISTERMANAGER_H