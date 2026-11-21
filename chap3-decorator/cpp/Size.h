// Size enum shared by beverages and decorators (supporting type, not a pattern role).
#pragma once

#include <string>

// Scoped enum: no implicit int conversion or name leakage; Decorators forward it inward.
enum class Size { TALL, GRANDE, VENTI };

// inline so this header-only helper can be included in many translation units.
inline std::string toString(Size size) {
    switch (size) {
        case Size::TALL: return "TALL";
        case Size::GRANDE: return "GRANDE";
        case Size::VENTI: return "VENTI";
    }
    return "";  // unreachable for valid values; satisfies the compiler
}
