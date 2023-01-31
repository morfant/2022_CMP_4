//
//  main_bitset.cpp
//  CA
//
//  Created by Gang il Lee on 2022/09/23.
//
// build command on mac
// clang++ -o run main.cpp -std=c++1z

#include <iostream>
#include <random>
#include <string>
#include <bitset>
#include <chrono>
#include <thread>


using namespace std;

// random 을 위한 준비
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dis(0.0, 1.0);

// 변수
int numLines = 60;
int WIDTH = 160;
bitset<160> current_;
bitset<160> next_;
bitset<8> ruleSet;

// 함수 선언
void init();
void generate();
void display();
bool randBool();


// 함수 정의
void init() {
    current_.reset(); // set as 0 all bits
    current_.set(WIDTH/2); // set as 1 at 'WIDTH/2'
    cout << "current_: " << current_.to_string() << endl;
}

void generate() {
    for (int i = 1; i < WIDTH - 1; i++) {
        int left = current_[(i - 1)];
        int me = current_[i];
        int right = current_[(i + 1)];
        string l = to_string(left);
        string m = to_string(me);
        string r = to_string(right);
        // cout << "str: " << l + m + r << endl;

        string str = r + m + l; // bitset은 2진수의 오른쪽부터 읽는다 ?
        bitset<3> bs = bitset<3>(str); // str(ex. 010) -> bitset<3>
        next_[i] = ruleSet[bs.to_ulong()]; // 2진수를 10진수 ulong 으로 변환해서 idx로 사용 (ex. 010 -> 2)
        // cout << "bs:" << bs << " bs.to_ulong():" << bs.to_ulong() << endl;
        // cout << "next_[" << i << "]:" << next_[i] << endl;
        //cout << "bitset: " << bs << endl;
    }

    // current_를 다음번의 next로 만드는 것은 generate가 모두 끝난 후에 할 것
    for (int i = 1; i < WIDTH - 1; i++) {
        current_[i] = next_[i];
    }
}

void display() {
    for (size_t i = WIDTH - 1; i > 0; i--) {
        char c;
        if (current_[i] == 0) c = ' ';
        else c = '*';
        cout << c;
    }
    cout << endl;
}

bool randBool() {
    bool result;
    float r = dis(gen);
    if (r > 0.5) {
        result = true;
    } else {
        result = false;
    }
    return result;
}


int main(int argc, const char * argv[]) {
    cout << "Cellular Automata is starting...\n";

    if (argc <= 2) {
        if (argc == 2) {
            int n = atoi(argv[1]);
            ruleSet = bitset<8>(n);
        } else {
            for (size_t i = 0; i < 8; i++) {
                if (randBool()) ruleSet.set(i);
                else ruleSet.reset(i);
            }
        }
        cout << "RULESET : " << ruleSet.to_string() << "(" << ruleSet.to_ulong() << ")" << endl;
    } else {
        // 두 번째 아규먼트부터는 무시
    }

    init();
    size_t i = numLines;
    while(i > 0) {
        // current_부터 display 할 것
        display();
        generate();
        --i;
    }

    return 0;
}
