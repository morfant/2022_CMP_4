#include <iostream>
#include <bitset>

using namespace std;

bitset<8> ruleSet;
bitset<81> current_;
bitset<81> next_;


void init() {
    current_.reset();
    current_.set(41);
}

void generate() {
    for (size_t i = 1; i < 81 - 1; i++) {
        int left = current_[i - 1]; // 0
        int me = current_[i]; // 1
        int right = current_[i + 1]; // 0

        char v[4];
        sprintf(v, "%d%d%d", left, me, right);
        bitset<3> bs = bitset<3>(v);

        next_[i] = ruleSet[bs.to_ulong()];
    }

    for (size_t i = 0; i < 81; i++) {
        current_[i] = next_[i];
    }
}

void display() {
    for (size_t i = 0; i < 81; i++) {
        if (current_[i] == 1) {
            cout << "U";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    int rule = 0;
    cout << "Rule?" << endl;
    scanf("%d", &rule);

    init();
    ruleSet = bitset<8>(rule);
    cout << ruleSet.to_string() << endl;
    cout << current_.to_string() << endl;

    generate();
    display();

    return 0;
}