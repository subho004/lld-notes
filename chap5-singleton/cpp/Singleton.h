// Singleton.h: classic Singleton (Meyers) and CallOnceSingleton (std::call_once variant).
#pragma once
#include <mutex>

// Classic Singleton. The C++11 "Meyers singleton": a function-local static
// is initialised exactly once, thread-safely, by the language itself.
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton uniqueInstance;
        return uniqueInstance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;
};

// Variant using std::call_once (lazy, explicit, leaks nothing: unique_ptr).
// unique_ptr owns the object and deletes it at exit; reset(new ...) because the ctor is private.
#include <memory>
class CallOnceSingleton {
public:
    static CallOnceSingleton& getInstance() {
        std::call_once(flag(), [] { instance().reset(new CallOnceSingleton()); });
        return *instance();
    }
    CallOnceSingleton(const CallOnceSingleton&) = delete;
    CallOnceSingleton& operator=(const CallOnceSingleton&) = delete;

private:
    CallOnceSingleton() = default;
    static std::once_flag& flag() { static std::once_flag f; return f; }
    static std::unique_ptr<CallOnceSingleton>& instance() {
        static std::unique_ptr<CallOnceSingleton> p;
        return p;
    }
};
