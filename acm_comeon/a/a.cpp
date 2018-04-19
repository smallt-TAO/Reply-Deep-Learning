#include <iostream>

using namespace std;

int fibonace(int a) {
    if (a == 0 || a == 1) {
        return 1;
    }

    else {
        return fibonace(a - 1) + fibonace(a - 2);
    }
}

int main() {
    int n;
    while (true) {
    cin >> n;
    cout << fibonace(n) << endl;
}
    return 0;
}

