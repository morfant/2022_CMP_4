//
//  main.cpp
//  CA
//
//  Created by Gang il Lee on 2022/08/23.
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
int numLines = 30;
int WIDTH = 160;
bool current[160];
bool next_[160];
bool ruleSet[8] = {0, 1, 0, 1, 1, 1, 1, 1};
bool autoMode = false;
size_t ruleNumMax = 2;

// 함수 선언
void generate();
void display(bool* arr, size_t len);
void printArr(bool* arr, size_t len);
bitset<3> strToBitSet(string& str);
bool randBool();
void init(size_t);


// 함수 정의
bitset<3> strToBitSet(string& str) {
    //cout << "str: " << str << endl;
    bitset<3> bs;
    for (size_t i = 0; i <= 2; i++) {
        if (str[i] == '0') {
            bs.set(2 - i, false);
            //cout << "0" << endl;
        } else if (str[i] == '1') {
            bs.set(2 - i, true);
            //cout << "1" << endl;
        }

        //cout << "bitset in for: " << bs << endl;
    }

    return bs;
}

void generate() {

    // current부터 display 할 것
    display(current, WIDTH);

    for (int i = 1; i < WIDTH - 1; i++) {
        int left = current[i - 1];
        int me = current[i];
        int right = current[i + 1];
        string l = to_string(left);
        string m = to_string(me);
        string r = to_string(right);
        //cout << "str: " << l + m + r << endl;

        string str = l + m + r;
        bitset<3> bs = strToBitSet(str);

        //cout << "bs:" << bs << " bs.to_ulong():" << bs.to_ulong() << endl;
        next_[i] = ruleSet[bs.to_ulong()];

        //cout << "next_[" << i << "]:" << next_[i] << endl;
        //cout << "bitset: " << bs << endl;

    }

    // current를 다음번의 next로 만드는 것은 generate가 모두 끝난 후에 할 것
    for (int i = 1; i < WIDTH - 1; i++) {
        current[i] = next_[i];
    }
}


void printArr(bool* arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        cout << arr[i] << "";
    }
    cout << "" << endl;
}


void display(bool* arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char c;
        if (arr[i] == 0) c = ' ';
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

void init(size_t n) {
    cout << "RULE : ";
    printArr(ruleSet, 8);
    cout << endl;

    for (int i = 0; i < WIDTH; i++) {
        //current[i] = randBool();
        current[i] = false;
        //cout << current[i];
        next_[i] = false;
    }
    current[n] = true;
    //cout << " " << endl;
    printArr(current, WIDTH);
}
 
int main(int argc, const char * argv[]) {
    
    // insert code here...
    cout << "CA!!\n";

    if (argc == 4) {
        string bin = bitset<8>(atoi(argv[3])).to_string(); // as binary string
        // cout << "bin: " << bin << endl;
        for (size_t i = 0; i < 8; i++) {
            ruleSet[7 - i] = bin[i] - '0'; // char to int, atoi() 는 char * 를 int 로 바꾸는 것
            //ruleSet[i] = bin[i] - '0'; // char to int, atoi() 는 char * 를 int 로 바꾸는 것
        }
        // printArr(ruleSet, 8);
        init(atoi(argv[1])); // set index of true value
        numLines = atoi(argv[2]); // set vertical line length
    } else if (argc == 1) {
        init(WIDTH/2);
    } else if (argc == 5) {
        if (atoi(argv[4]) >= 1) {
            autoMode = true;
            ruleNumMax = atoi(argv[4]);
            cout << "autoMode: " << autoMode << endl;
        }

        init(atoi(argv[1])); // set index of true value
        numLines = atoi(argv[2]); // set vertical line length
    } else {
        cout << "Arguments must be 0 or 3! (run initPos numLines ruleSet) (" << argc << ")" << endl;
        return 0;
    }


    size_t i = numLines;
    size_t ruleNum = 0;
    if (autoMode == true) {
        while(ruleNum <= ruleNumMax) {
            cout << "RuleSet: " << ruleNum << endl;
            string bin = bitset<8>(ruleNum).to_string(); // as binary string
            for (size_t i = 0; i < 8; i++) {
                ruleSet[7 - i] = bin[i] - '0'; // char to int, atoi() 는 char * 를 int 로 바꾸는 것
                //ruleSet[i] = bin[i] - '0'; // char to int, atoi() 는 char * 를 int 로 바꾸는 것
            }
            printArr(ruleSet, 8);
            i = numLines;
            while(i > 0) {
                generate();
                --i;
            }
            ruleNum++;

            using namespace std::chrono_literals;
            this_thread::sleep_for(500ms);
            // system("clear");
        }
        
    } else {
        while(i > 0) {
            generate();
            --i;
        }
    }
  
    return 0;
}
