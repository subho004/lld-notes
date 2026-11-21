#pragma once
// Reproduces java.util.HashMap iteration order for String keys, so CafeMenu
// prints in the same order as the Java program (std::unordered_map order is
// implementation-defined and std::map would sort alphabetically).
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <string>
#include <vector>

// Java's String.hashCode(); uint32_t wraps on overflow like Java's int.
inline std::uint32_t javaStringHash(const std::string& s) {
    std::uint32_t h = 0;
    for (unsigned char c : s) h = 31u * h + c;  // ASCII keys: one UTF-16 unit per byte
    return h;
}

// Returns key indexes in Java HashMap iteration order (bucket order, ties by insertion).
inline std::vector<std::size_t> javaHashMapOrder(const std::vector<std::string>& keys) {
    // Default capacity 16; doubles while size exceeds the 0.75 load factor.
    std::size_t table = 16;
    while (static_cast<double>(keys.size()) > static_cast<double>(table) * 0.75) table *= 2;
    auto bucket = [&](const std::string& k) {
        std::uint32_t h = javaStringHash(k);
        return static_cast<std::size_t>((h ^ (h >> 16)) & (table - 1));
    };
    std::vector<std::size_t> idx(keys.size());
    std::iota(idx.begin(), idx.end(), 0);
    // stable_sort keeps insertion order within a bucket.
    std::stable_sort(idx.begin(), idx.end(),
                     [&](std::size_t a, std::size_t b) { return bucket(keys[a]) < bucket(keys[b]); });
    return idx;
}
