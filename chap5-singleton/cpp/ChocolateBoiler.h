// ChocolateBoiler: Singleton (call_once instead of double-checked locking) with synchronized methods.
#pragma once
#include <memory>
#include <mutex>

// Singleton; the recursive_mutex plays the role of Java's synchronized methods.
class ChocolateBoiler {
public:
    // std::call_once replaces Java's volatile + double-checked locking.
    static ChocolateBoiler& getInstance() {
        std::call_once(onceFlag(), [] { holder().reset(new ChocolateBoiler()); });
        return *holder();
    }
    ChocolateBoiler(const ChocolateBoiler&) = delete;
    ChocolateBoiler& operator=(const ChocolateBoiler&) = delete;

    // recursive_mutex so fill() can call isEmpty(), which locks again on the same thread.
    void fill() {
        std::lock_guard<std::recursive_mutex> g(mutex_);
        if (isEmpty()) { empty_ = false; boiled_ = false; }
    }
    void drain() {
        std::lock_guard<std::recursive_mutex> g(mutex_);
        if (!isEmpty() && isBoiled()) empty_ = true;
    }
    void boil() {
        std::lock_guard<std::recursive_mutex> g(mutex_);
        if (!isEmpty() && !isBoiled()) boiled_ = true;
    }
    bool isEmpty() {
        std::lock_guard<std::recursive_mutex> g(mutex_);
        return empty_;
    }
    bool isBoiled() {
        std::lock_guard<std::recursive_mutex> g(mutex_);
        return boiled_;
    }
    // exposed so a caller can make a multi-step sequence atomic
    std::recursive_mutex& mutex() { return mutex_; }

private:
    // Private ctor: only getInstance() can create the boiler.
    ChocolateBoiler() = default;
    // Function-local statics avoid needing a separate .cpp file (header-only).
    // unique_ptr owns the instance and frees it at exit; plain new is needed as the ctor is private.
    static std::once_flag& onceFlag() { static std::once_flag f; return f; }
    static std::unique_ptr<ChocolateBoiler>& holder() {
        static std::unique_ptr<ChocolateBoiler> p;
        return p;
    }

    std::recursive_mutex mutex_;
    bool empty_ = true;
    bool boiled_ = false;
};
