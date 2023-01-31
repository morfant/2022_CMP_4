#include <iostream>
#include <random>


using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> dis(0.0, 1.0);


int main(int argc, char * argv[])
{
    int width = 0;
    int height = 0;
    cout<< "Hello World!" << endl;
    cout<< "width height ?" << endl;
    scanf("%d %d", &width, &height);


    cout<< "Width / Height : " << width << "/" << height << endl;

    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; i++) {
            float a = dis(gen);
            // cout << "random value: " << a << endl;
            if (a < 0.5) {
                cout << '/';
            } else {
                cout << '\\';
            }
        }
        cout << endl;
    }


    return 0;
}

