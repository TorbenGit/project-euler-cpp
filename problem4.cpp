#include <iostream>
#include <vector>
#include <utility>

bool isPalindrome(int n) {
    std::string s = std::to_string(n);
    unsigned int index = s.length()/2;

    for (unsigned int i=0; i<index; i++) {
        unsigned int sec = s.length()-1-i;
        if (!(s[i] == s[sec])) {
            return false;
        }
    }

    return true;
}

std::string findFactors(int n) {
    std::string f;

    for (unsigned int i=999; i>99; i--) {
        if (!(n%i) && n/i < 1000) {
            f.append(std::to_string(i));
            f.append("*");
            f.append(std::to_string(n/i));
            return f;
        }
    }

    f.append("-1");
    return f;
}

int main() {
    /*int num;

    std::cout << "Gebe eine Nummer ein: ";
    std::cin >> num;
    std::cout << "Is Palindrome: " << isPalindrome(num) << "\n";*/

    for (int i=999*999; i>-1; i--) {
        if (isPalindrome(i)) {
            std::cout << "Found: " << i << "\n";
            std::string r = findFactors(i);

            if (r == "-1") {
                std::cout << "Skipping found no 3-digit factors\n";
                continue;
            } else {
                std::cout << "Operation: " << r << "\n";
                return 0;
            }
        }
    }

    return 0;
}
