#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    std::vector<int> x;
    x.push_back(100);
    x.push_back(200);
    x.push_back(300);

    // std::cout << x[3] << std::endl;
    std::cout << x.at(3) << std::endl;

    return 0;
}