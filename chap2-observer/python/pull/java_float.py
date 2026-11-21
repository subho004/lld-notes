"""Helpers that mimic Java's 32-bit `float` arithmetic and Float.toString().

Simulation shim: Python floats are 64-bit, so this keeps output identical to Java.
"""
import math
import struct


def f32(x: float) -> float:
    """Round a Python float (double) to the nearest 32-bit float, like a Java cast."""
    return struct.unpack("f", struct.pack("f", x))[0]


def java_str(x: float) -> str:
    """Format like Java's String.valueOf(float): shortest repr that round-trips."""
    x = f32(x)
    if math.isnan(x):
        return "NaN"
    if math.isinf(x):
        return "Infinity" if x > 0 else "-Infinity"
    if x == 0:
        return "-0.0" if math.copysign(1.0, x) < 0 else "0.0"
    sign = "-" if x < 0 else ""
    ax = abs(x)
    # Find the fewest significant digits (1..9) that still round-trip to the same float32.
    for prec in range(1, 10):
        s = "%.*e" % (prec - 1, ax)
        if f32(float(s)) == ax:
            break
    mant, exp_s = s.split("e")
    digits = mant.replace(".", "").rstrip("0") or "0"
    exp = int(exp_s)
    # Java uses plain decimal for 1e-3 <= |x| < 1e7 and scientific notation otherwise.
    if -3 <= exp < 7:
        if exp >= 0:
            int_part = digits[: exp + 1].ljust(exp + 1, "0")
            frac = digits[exp + 1:] or "0"
        else:
            int_part = "0"
            frac = "0" * (-exp - 1) + digits
        return f"{sign}{int_part}.{frac}"
    frac = digits[1:] or "0"
    return f"{sign}{digits[0]}.{frac}E{exp}"
