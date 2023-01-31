//
//  main.cpp
//  Game Of Life 
//
//  Created by Gang il Lee on 2022/08/25.
//
// build command on mac
// g++ -o run main.cpp -std=c++14 -Wall

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals; // ms

// random 을 위한 준비
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dis(0.0, 1.0);
//normal_distribution<float> dis(0.0, 1.0);
//exponential_distribution<float> dis(1.0);
//extreme_value_distribution<float> dis(0.0, 1.0);

// 변수
size_t numFrames = 0;
float thresholdTrue = 0.8;
int WIDTH = 160;
int HEIGHT = 40;
vector< vector<bool> > current_;
vector< vector<bool> > next_;
bool autoMode = false;

// 함수 선언
bool randBool();
void init();
void generate();
void display(vector< vector<bool> >);


// 함수 정의
bool randBool() {
    bool result;
    float r = dis(gen);
    if (r > thresholdTrue) {
        result = true;
    } else {
        result = false;
    }
    return result;
}


void init() {
    for (int i = 0; i < HEIGHT; i++) {
        vector<bool> v(WIDTH, false);
        current_.push_back(v);
        next_.push_back(v);
        for (int j = 0; j < WIDTH; j++) {
            current_[i][j] = randBool();
            next_[i][j] = current_[i][j];
        }
    }

    display(current_);
}


void generate() {
    // current부터 display 할 것
    for (size_t y = 1; y < HEIGHT - 1; y++) {
        for (size_t x = 1; x < WIDTH - 1; x++) {
            size_t neighborsLife = 
                current_[y - 1][x - 1] + current_[y - 1][x] + current_[y - 1][x + 1] + 
                current_[y][x - 1] + current_[y][x + 1] + 
                current_[y + 1][x - 1] + current_[y + 1][x] + current_[y + 1][x + 1]; 
            //cout << "neighborsLife: " << neighborsLife << endl;

            if (neighborsLife == 3) {
                if (current_[y][x] == false) {
                    next_[y][x] = true; 
                }
            } else if (neighborsLife <= 1 || 4 <= neighborsLife ) {
                if (current_[y][x] == true) {
                    next_[y][x] = false; 
                }
            } else {
                next_[y][x] = current_[y][x]; 
            }
        }
    }

    current_ = next_;

    // current_를 다음번의 next로 만드는 것은 generate가 모두 끝난 후에 할 것
    // for (size_t y = 1; y < HEIGHT - 1; y++) {
    //     for (size_t x = 1; x < WIDTH - 1; x++) {
    //         current_[y][x] = next_[y][x];
    //     }
    // }

}


void display(vector< vector<bool> > v) {
    for (vector<bool> vb : v) {
        for (bool b : vb) {
            char c;
            if (b == false) c = ' ';
            else c = '*';
            cout << c;
        }
        cout << endl;
    }
}

 
int main(int argc, const char * argv[]) {

    cout << "Game Of Life!!\n";
    init();

    size_t frameCount =  0;
    if (argc == 2) {
        numFrames = atoi(argv[1]);
        size_t i = numFrames;
        while(i > 0) {
            display(current_);
            system("clear");
            generate();
            --i;
            cout << "frame: " << frameCount++ << endl;
            cout << "\'Ctrl + c\' to Stop" << endl; 
            this_thread::sleep_for(50ms); // 20 fps
        }
    } else if (argc == 1) {
        while(true) {
            system("clear");
            display(current_);
            generate();
            cout << "frame: " << frameCount++ << endl;
            cout << "\'Ctrl + c\' to Stop" << endl; 
            this_thread::sleep_for(50ms); // 20 fps
        }
    }
  
    return 0;
}




