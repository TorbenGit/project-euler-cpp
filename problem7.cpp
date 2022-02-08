#include <iostream>
#include <vector>

std::vector<int> primeSieve(int n) {
    std::vector<int> primes;

    for (int i=2; i<n+1; i++) {
        primes.push_back(i);
    }

    for (size_t i=0; i<primes.size(); i++) {
        for (size_t j=i+1; j<primes.size(); j++) {
            if (primes[j] != 0 && primes[i] != 0 && !(primes[j]%primes[i])) {
                primes[j] = 0;
            }
        }
    }

    return primes;
}

int main() {
    std::vector<int> primes;

    int start = 100000;

    while (primes.size() < 10001) {
        std::vector<int> p = primeSieve(start);
        primes.clear();

        for (size_t i=0; i<p.size(); i++) {
            if (p[i] != 0) {
                primes.push_back(p[i]);
            }
        }
        start += 100;
    }

    std::cout << "Size: " << primes.size() << "\n";
    std::cout << "10001th Prime: " << primes[10000] << "\n";

    return 0;
}
