#include <iostream>

using namespace std;

class Tree {
    public:
        int age;
        float radius;
        float height;
        bool isAlive;
        long numLeaves;
};

int main()
{
    
    int x[] = {1,2,3,4,5,6,7,8,9,0};
    long xl = 100;
    float xf = 1.2f;
    double xd = 3.456;
    
    long * xlp;
    float * xfp;
    xlp = &xl;
    xfp = &xf;
    
    cout << sizeof(xl) << sizeof(xf) << sizeof(xd) << endl;
    cout << sizeof(xlp) << sizeof(xfp) << endl;


    Tree t;
    cout << sizeof(t) << endl;

    return 0;
}