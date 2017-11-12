#include <iostream>

class SealedClass {
private:
    SealedClass(){}
    ~SealedClass(){}

public:
    friend SealedClass* getInstance();

};

SealedClass* getInstance() {
    return new SealedClass();
}


class Base : public SealedClass {

};

int main() {
    SealedClass* p = getInstance();
    // Base base;    error

    return 0;
}
    
