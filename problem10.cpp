#include <iostream>
#include <vector>
#include <thread>
#include <future>

void prime_sieve_thread(std::vector<int> v, std::promise<std::vector<int>> && ret) {
    int start = v.front();
    int end = v.back();

    std::cout << "Starting Thread " << start << " - " << end << "\n";

    for (size_t i=0; i<v.size(); i++) {
        for (int j=2; j<v[i]; j++) {
            if (v[i] != 0 && !(v[i]%j)) {
                v[i] = 0;
                break;
            }
        }
    }

    std::cout << "Finished Thread " << start << " - " << end << "\n";

    ret.set_value(v);
}

std::vector<int> primeSieve(int n) {
    const auto proc_count = std::thread::hardware_concurrency();
    std::vector<int> primes[proc_count];

    int remaining = n;
    int before = 2;
    int d = std::div(remaining,proc_count).quot;

    std::pair<std::thread, std::future<std::vector<int>>> threads[proc_count];

    for (unsigned int i=0; i<proc_count; i++) {
        std::vector<int> v;

        if (i != proc_count-1) {
            int end = d*(i+1);

            for (int j=before; j<end; j++) {
                v.push_back(j);
            }

            remaining -= (end-before);
            before = end;
        } else {
            int end = n;

            for (int j=before; j<=end; j++) {
                v.push_back(j);
            }
        }

        std::promise<std::vector<int>> vp;
        auto f = vp.get_future();
        std::thread t(prime_sieve_thread, v, std::move(vp));

        std::pair<std::thread, std::future<std::vector<int>>> p;
        p.first = std::move(t);
        p.second = std::move(f);
        threads[i] = std::move(p);
    }

    std::vector<int> filteredPrimes;

    for (size_t i=0; i<proc_count; i++) {
        threads[i].first.join();
        std::vector<int> v = threads[i].second.get();

        for (size_t j=0; j<v.size(); j++) {
            if (v[j] != 0) {
                filteredPrimes.push_back(v[j]);
            }
        }
    }

    return filteredPrimes;
}

int main() {
    std::vector<int> p = primeSieve(2000000-1);

    long long int sum = 0;

    for (size_t i=0; i<p.size(); i++) {
        sum += p[i];
    }

    std::cout << "The sum is " << sum << "\n";

    return 0;
}
