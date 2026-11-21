// Extra (no Java counterpart): many threads race for the singletons.
#include <atomic>
#include <iostream>
#include <set>
#include <thread>
#include <vector>
#include "ChocolateBoiler.h"
#include "Singleton.h"

// Spin on an atomic flag below so all threads start together.
static constexpr int THREADS = 8;

// True when all threads saw one address (a set collapses duplicates).
template <typename T>
static bool allSame(const std::vector<T*>& v) {
    return std::set<T*>(v.begin(), v.end()).size() == 1;
}

int main() {
    std::atomic<bool> go{false};
    std::vector<Singleton*> classic(THREADS);
    std::vector<CallOnceSingleton*> once(THREADS);
    std::vector<ChocolateBoiler*> boilers(THREADS);

    std::vector<std::thread> ts;
    for (int i = 0; i < THREADS; ++i)
        ts.emplace_back([&, i] {
            while (!go) std::this_thread::yield();
            classic[i] = &Singleton::getInstance();
            once[i] = &CallOnceSingleton::getInstance();
            boilers[i] = &ChocolateBoiler::getInstance();
        });
    go = true;
    for (auto& t : ts) t.join();

    std::cout << std::boolalpha;
    std::cout << "Singleton, " << THREADS << " threads, one instance? " << allSame(classic) << "\n";
    std::cout << "CallOnceSingleton, " << THREADS << " threads, one instance? " << allSame(once) << "\n";
    std::cout << "ChocolateBoiler, " << THREADS << " threads, one instance? " << allSame(boilers) << "\n";

    ChocolateBoiler& boiler = ChocolateBoiler::getInstance();
    std::vector<int> cycles(THREADS, 0);
    ts.clear();
    for (int i = 0; i < THREADS; ++i)
        ts.emplace_back([&, i] {
            for (int n = 0; n < 100; ++n) {
                // Hold the boiler's mutex across the whole cycle; inner calls re-lock (recursive).
                std::lock_guard<std::recursive_mutex> g(boiler.mutex());
                boiler.fill();
                boiler.boil();
                boiler.drain();
                if (boiler.isEmpty()) ++cycles[i];
            }
        });
    for (auto& t : ts) t.join();
    int total = 0;
    for (int c : cycles) total += c;
    std::cout << "Completed cycles: " << total << "\n";
    std::cout << "Boiler empty at end? " << boiler.isEmpty() << "\n";
}
