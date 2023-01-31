//
//  main.cpp
//  10_print
//
//  Created by Gang il Lee on 2022/08/23.
//

#include <iostream>
#include <random>

int WIDTH = 20;
int HEIGHT = 10;

int main(int argc, const char * argv[]) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    
    // insert code here...
    std::cout << "10 print!!\n";
    
    if (argc == 2) {
        WIDTH = atoi(argv[1]);
    } else if (argc == 3) {
        WIDTH = atoi(argv[1]);
        HEIGHT = atoi(argv[2]);
    }
    
    for (int i = 0; i < HEIGHT; i++) {
        std::cout << ' ' << std::endl;
        for (int j = 0; j < WIDTH; j++) {
            float r = dis(gen);
            if (r > 0.5) {
                std::cout << '/';
            } else {
                std::cout << '\\';
            }
        }
    }
    std::cout << '\n' << '\n' << std::endl;
    
    return 0;
}
