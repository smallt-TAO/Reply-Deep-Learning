#include <iostream>
#include <stack>

using namespace std;

class Queue {
public:
    void push(int node) {
        stackIn.push(node);
    }

    void pop() {
        int node = -1;
        while (!stackIn.empty()) {
            node = stackIn.top();
            stackIn.pop();
            stackOut.push(node);
        }

        if (!stackOut.empty()) {
            cout << stackOut.top() << endl;
            stackOut.pop();
        }

    }

    bool empty() {
        return (stackIn.empty() == true && stackOut.empty() == true);
    }

private:
    stack<int> stackIn;
    stack<int> stackOut;
};

int main() {
    Queue queue;
    queue.push(1);
    queue.push(0);
    queue.push(2);
    queue.push(4);

    while (!queue.empty()) {
        queue.pop();
    }
}
