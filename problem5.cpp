#include <iostream>

int main() {
    for (unsigned int i=1; true; i++) {
        if (!(i%1) && !(i%2) && !(i%3) && !(i%4) && !(i%5) && !(i%6) && !(i%7) && !(i%8) && !(i%9) && !(i%10) && !(i%11) && !(i%12) && !(i%13) && !(i%14) && !(i%15) && !(i%16) && !(i%17) && !(i%18) && !(i%19) && !(i%20)) {
            std::cout << "The number is: " << i << "\n";
            return 0;
        }
    }

    return 0;
}
