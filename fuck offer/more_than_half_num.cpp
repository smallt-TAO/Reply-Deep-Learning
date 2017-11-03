#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void moreThanHalfNum(vector<int> vec) {
        int counter = 1;
        int flag = vec[0];

        for (int i = 1; i < vec.size(); ++i) {
            if (vec[i] == flag) {
                counter++;
            }
            else {
                counter--;
            }

            if (counter == 0) {
                flag = vec[i];
                counter = 1;
            }
        }

        counter = 0;
        for (auto v : vec) {
            if (v == flag) {
                counter++;
            }

            if (counter > vec.size() / 2) {
                cout << "early stop:More than half num" << endl;
                break;
            }
        }

        if (counter > vec.size() / 2) {
            cout << "More than half num" << endl;
        }
        else {
            cout << "Fuck the num" << endl;
        }
    }

};

int main() {
    int arr1[] = { 5, 5, 2, 2, 3, 3, 5, 5, 5};
    vector<int> vec1(arr1, arr1 + 9);

    Solution solu;
    solu.moreThanHalfNum(vec1);

    int arr2[] = { 1, 2 };
    vector<int> vec2(arr2, arr2 + 2);
    solu.moreThanHalfNum(vec2);

    return 0;
}

