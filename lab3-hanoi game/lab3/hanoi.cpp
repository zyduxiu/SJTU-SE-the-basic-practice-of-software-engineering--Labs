#include <iostream>
#include <string>
#include <climits>
#include "board.h"
#include <sstream>
using namespace std;

int main() {
    while(true) {
        string num;
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        getline(cin,num);
        if (num[0] == 'Q') { break; }
        else {
            if (num[0] - '0' <= 0 || num[0] - '0' > 5) { continue; }
            else {
                Board hanoi(num[0] - '0');
                hanoi.draw();
                while (true) {
                    string input;
                    cout << "Move a disk. Format: x y" << endl;
                    getline(cin, input);
                    if (input[0] - '0' == 0 && input[2] - '0' == 0) {
                        hanoi.autoplay();
                    } else {
                        try { hanoi.move(input[0] - '0', input[2] - '0', true); }
                        catch (const char *a) { hanoi.draw(); }
                    }
                    if (hanoi.win()) {
                        cout << "Congratulations! You win!" << endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
