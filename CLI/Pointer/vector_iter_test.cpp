#include <iostream>
#include <vector>

using namespace std;

// 전역 변수
// raw data
double data[2][5] = {
    {1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10}
};
double * sig[5];

vector<int> vint1(10, 1);
vector<int> vint2(10, -1);

vector< vector<int> > current_;

// 함수 정의
void init() {
    current_.push_back(vint1);
    current_.push_back(vint2);
    current_.push_back(vint1);
    current_.push_back(vint2);
    current_.push_back(vint1);
    current_.push_back(vint2);

    vector< vector<int> >::iterator iter;
    vector<int>::iterator jter;
    for (iter = current_.begin() + 1; iter != current_.end() - 1; iter++) {
        // for (jter = (*(iter)).begin(); jter != (*(iter)).end(); jter++) {
        for (jter = iter->begin() + 1; jter != iter->end() - 1; jter++) {
            cout << *(jter) << endl;
        }
        cout << "==================" << endl;
    }
}

// 아규먼트로 이중 포인터를 받아, 2D 배열의 원소들을 모두 출력하기 위한 함수
void print2DArr(double ** arr) {
    cout << "----Begin----" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            // 아래 셋은 모두 동일한 결과 
            // cout << arr[i][j] << endl; // 배열의 index
            // cout << *(arr[i] + j) << endl; // 배열의 index, 포인터 연산
            cout << *(*(arr + i) + j) << endl; // 포인터 연산
        }
        cout << "---" << endl;
    }
    cout << "----End----" << endl;
}

// mult 함수 1
// 2D 배열 타입을 첫 번째 아규먼트로 받는다
void mult(double ins[][5], float mult = 1.0) {
    double * inL = ins[0];
    double * inR = ins[1];

    for (int i = 0; i < 5; i++) {
        inL[i] = inL[i] * mult; // 배열의 index 사용
        inR[i] = inR[i] * mult;
        // *(inL + i) = *(inL + i) * mult; // 포인터 연산 사용
        // *(inR + i) = *(inR + i) * mult;
    }
}

// mult 함수 2
// 이중 포인터 타입을 첫 번째 아규먼트로 받는다
void mult(double ** ins, float mult = 1.0) {
    double * inL = ins[0];
    double * inR = ins[1];

    for (int i = 0; i < 5; i++) {
        *(inL + i) = *(inL + i) * mult; // 포인터 연산 사용
        *(inR + i) = *(inR + i) * mult;
        // inL[i] = inL[i] * mult; // 배열의 index 사용
        // inR[i] = inR[i] * mult;
    }
}


int main(int argc, char* argv[]) {

    init();
    
    return 0;
}