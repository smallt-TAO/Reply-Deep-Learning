#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

class stackMin {
public:
    void push(int value) {
        this -> mStack.push(value);

        if (this -> minStack.size() == 0 || 
                this -> minStack.top() > value) {
            this -> minStack.push(value);
        }
        else {
            int temp = minStack.top();
            this -> minStack.push(temp);
        }
    }

    void pop() {
        assert(this -> mStack.size() > 0 && this -> minStack.size() > 0);

        this -> mStack.pop();
        this -> minStack.pop();
    }

    void top() {
        assert(this -> mStack.size() > 0 && this -> minStack.size() > 0);

        this -> mStack.top();
    }

    int min() {
        if (minStack.size() == 0) {
            return 0;
        }

        return this -> minStack.top();
    }

private:
    stack<int> mStack;
    stack<int> minStack;
};

int main() {
    return 0;
}

