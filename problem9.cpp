#include <iostream>

bool isPythagorean(int a, int b, int c) {
    return (a*a) + (b*b) == (c*c) && a < b && b < c;
}

bool isValid(int a, int b, int c) {
    return a+b+c == 1000;
}

int main() {
    int a,b,c;

    for (a=0; a<1001; a++) {
        for (b=0; b<1001; b++) {
            for (c=0; c<1001; c++) {
                if (isPythagorean(a,b,c) && isValid(a,b,c)) {
                    std::cout << "a: " << a << " b: " << b << " c: " << c << "\n";
                    std::cout << "Product: " << a*b*c << "\n";
                    return 0;
                }
            }
        }
    }

    std::cout << "No solution found!\n";

    return 0;
}
