#include <iostream>

class SealedClass {
public:
    static SealedClass* getInstance() {
        return new SealedClass();
    }

private:
    SealedClass();
    ~SealedClass();
};

class Base : public SealedClass {

};


int main() {
    SealedClass* pd = Base::getInstance();
    Base base;

    return 0;
}

