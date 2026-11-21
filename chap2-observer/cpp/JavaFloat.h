#pragma once
// Simulation shim: iostream would print 80 / 80.755 where Java prints 80.0 / 80.755.
// Formats a float the way Java's String.valueOf(float) does
// (shortest digits that round-trip, always at least one decimal place).
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

// `inline` keeps this header-only function ODR-safe across translation units.
inline std::string javaStr(float x) {
    if (std::isnan(x)) return "NaN";
    if (std::isinf(x)) return x > 0 ? "Infinity" : "-Infinity";
    if (x == 0.0f) return std::signbit(x) ? "-0.0" : "0.0";
    const std::string sign = x < 0 ? "-" : "";
    const float ax = std::fabs(x);
    char buf[64];
    // Find the fewest significant digits (1..9) that round-trip to the same float.
    for (int prec = 1; prec <= 9; ++prec) {
        std::snprintf(buf, sizeof buf, "%.*e", prec - 1, static_cast<double>(ax));
        if (std::strtof(buf, nullptr) == ax) break;
    }
    const std::string s = buf;
    const std::size_t e = s.find('e');
    std::string digits;
    for (std::size_t i = 0; i < e; ++i)
        if (s[i] != '.') digits += s[i];
    while (digits.size() > 1 && digits.back() == '0') digits.pop_back();
    const int exp = std::atoi(s.c_str() + e + 1);
    // Java uses plain decimal for 1e-3 <= |x| < 1e7 and scientific notation otherwise.
    if (exp >= -3 && exp < 7) {
        std::string intPart, frac;
        if (exp >= 0) {
            intPart = digits.substr(0, static_cast<std::size_t>(exp) + 1);
            while (intPart.size() < static_cast<std::size_t>(exp) + 1) intPart += '0';
            frac = digits.size() > static_cast<std::size_t>(exp) + 1
                       ? digits.substr(static_cast<std::size_t>(exp) + 1) : "0";
        } else {
            intPart = "0";
            frac = std::string(static_cast<std::size_t>(-exp - 1), '0') + digits;
        }
        return sign + intPart + "." + frac;
    }
    return sign + digits.substr(0, 1) + "." +
           (digits.size() > 1 ? digits.substr(1) : "0") + "E" + std::to_string(exp);
}
