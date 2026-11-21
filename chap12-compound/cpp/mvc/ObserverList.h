// Shared helper: ObserverList, a template so Beat and BPM observers reuse one list.
#pragma once
#include <algorithm>
#include <memory>
#include <vector>

// Non-owning observer list: models keep weak_ptrs so that view <-> model
// never forms an ownership cycle.  Expired observers are skipped.
template <typename T>
class ObserverList {
    std::vector<std::weak_ptr<T>> items;

public:
    void add(const std::shared_ptr<T>& o) { items.push_back(o); }

    void remove(const std::shared_ptr<T>& o) {
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [&](const std::weak_ptr<T>& w) {
                                       auto s = w.lock();
                                       return !s || s == o;
                                   }),
                    items.end());
    }

    template <typename F>
    void notify(F call) {
        auto snapshot = items;  // observers may (un)register while notified
        for (auto& w : snapshot) {
            if (auto s = w.lock()) call(*s);
        }
    }
};
