#ifndef HW5_REGISTERMANAGER_H
#define HW5_REGISTERMANAGER_H

using namespace std;

class Register{
public:
    unsigned int id;
    string name() const;
    explicit Register(unsigned int id):id(id){}
};

class RegisterManager {
    RegisterManager(): register_count(0){};
    int register_count;
public:
    RegisterManager(RegisterManager const &) = delete;
    void operator=(RegisterManager const &) = delete;
    static RegisterManager &instance();
    Register* alloc();

};

#endif //HW5_REGISTERMANAGER_H