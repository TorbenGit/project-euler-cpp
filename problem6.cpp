#include <iostream>

int main() {
    int sumOfSquares = 0;
    for (unsigned int i=1; i<101; i++) {
        sumOfSquares += (i*i);
    }

    int squareOfSum = 0;
    for (unsigned int i=1; i<101; i++) {
        squareOfSum += i;
    }
    squareOfSum = squareOfSum*squareOfSum;

    std::cout << "Sum of squares: " << sumOfSquares << "\n";
    std::cout << "Square of sum: " << squareOfSum << "\n";
    std::cout << "Difference: " << squareOfSum-sumOfSquares << "\n";

    return 0;
}
