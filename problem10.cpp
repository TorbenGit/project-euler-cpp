#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <math.h>

void prime_sieve_thread(unsigned int id, std::vector<int> v, std::promise<std::vector<int>> && ret) {
    std::cout << "Starting Thread " << id << "\n";

    for (size_t i=0; i<v.size(); i++) {
        for (int j=2; j<=std::ceil(std::sqrt(v[i])); j++) {
            if (!(v[i]%j) && j != v[i]) {
                v[i] = 0;
                break;
            }
        }
    }

    std::cout << "Finished Thread " << id << "\n";

    ret.set_value(v);
}

std::vector<int> prime_sieve(unsigned int n) {
    const auto proc_count = std::thread::hardware_concurrency();
    std::pair<std::thread, std::future<std::vector<int>>> threads[proc_count];

    std::vector<int> vec_arr[proc_count];

    for (unsigned int i=0; i<proc_count; i++) {
        vec_arr[i] = std::vector<int>();
    }

    for (unsigned int i=2, pc=0; i<=n; i++, pc++) {
        if (pc == proc_count) {
            pc = 0;
        }

        vec_arr[pc].push_back(i);
    }

    for (unsigned int i=0; i<proc_count; i++) {
        std::promise<std::vector<int>> vp;
        auto f = vp.get_future();
        std::thread t(prime_sieve_thread, i+1, vec_arr[i], std::move(vp));

        std::pair<std::thread, std::future<std::vector<int>>> p;
        p.first = std::move(t);
        p.second = std::move(f);
        threads[i] = std::move(p);
    }

    std::vector<int> filtered_primes;

    for (size_t i=0; i<proc_count; i++) {
        threads[i].first.join();
        std::vector<int> v = threads[i].second.get();

        for (size_t j=0; j<v.size(); j++) {
            if (v[j] != 0) {
                filtered_primes.push_back(v[j]);
            }
        }
    }

    return filtered_primes;
}

int main() {
    std::vector<int> p = prime_sieve(2000000-1);

    long int sum = 0;

    for (size_t i=0; i<p.size(); i++) {
        sum += p[i];
    }

    std::cout << "The sum is " << sum << "\n";

    return 0;
}
