# 100+ Python Challenging Programming Exercises — Answers & Explanations

A fully worked-through, explained companion to `100+ Python challenging programming exercises.txt`. Every one of the 100 exercises includes the original problem, a plain-English explanation of the approach, and a **verified, working Python 3** solution.

**A note on the source material:** this exercise set originated as a Python 2 document, and the existing `100+ Python challenging programming exercises for Python 3.md` in this folder is a partial, mechanical conversion — several of its solutions still contain leftover Python 2 syntax (`raw_input()`, `print x` without parentheses, `except Exception, e:`), a few return the wrong thing for Python 3 (`map()`/`filter()` now return lazy iterator objects instead of lists, so `print(map(...))` prints `<map object at 0x...>` instead of the values), and at least one has an outright logic bug. **Every solution below has been checked and, where necessary, corrected** so it actually runs and produces the stated output under Python 3. Anywhere a fix was needed, it's called out explicitly with a short note.

**How to use this guide:** read it top to bottom to practice sequentially, or jump to an exercise using the table of contents below. Questions are numbered to match the original exercise set (1-25 carry the original's own Level labels; the source list's own "Level" tagging becomes unreliable/inconsistent after Question 25, so 26-100 are grouped by topic instead).

---

- **[Numbers, Loops, Collections & Basic I/O (Level 1)](#numbers-loops-collections-basic-io-level-1)**
- **[A First OOP Class (Level 1)](#a-first-oop-class-level-1)**
- **[Formulas, Arrays & Sequence Processing (Level 2)](#formulas-arrays-sequence-processing-level-2)**
- **[Validation, Sorting & Robot Movement (Level 3)](#validation-sorting-robot-movement-level-3)**
- **[Word Frequency (Level 3)](#word-frequency-level-3)**
- **[Functions & Introspection Revisited (Level 1)](#functions-introspection-revisited-level-1)**
- **[Functions: Arithmetic, Strings & Conditionals](#functions-arithmetic-strings-conditionals)**
- **[Dictionaries, Lists & Tuples via Comprehension](#dictionaries-lists-tuples-via-comprehension)**
- **[Conditionals, map(), filter() & Lambda](#conditionals-map-filter-lambda)**
- **[Classes, Inheritance & Static Methods](#classes-inheritance-static-methods)**
- **[Exceptions](#exceptions)**
- **[Regular Expressions & Unicode](#regular-expressions-unicode)**
- **[Recursion & Generators](#recursion-generators)**
- **[Assertions, eval() & Binary Search](#assertions-eval-binary-search)**
- **[The random Module](#the-random-module)**
- **[zlib, timeit & shuffle](#zlib-timeit-shuffle)**
- **[Nested Loops & List Comprehension Filtering](#nested-loops-list-comprehension-filtering)**
- **[Sets: Intersection & Deduplication](#sets-intersection-deduplication)**
- **[More OOP: A Person Hierarchy](#more-oop-a-person-hierarchy)**
- **[String Manipulation](#string-manipulation)**
- **[Permutations & a Classic Puzzle](#permutations-a-classic-puzzle)**

---

## Numbers, Loops, Collections & Basic I/O (Level 1)

### Question 1. Numbers divisible by 7, not by 5

**Problem:** Find all numbers between 2000 and 3200 (both included) that are divisible by 7 but not a multiple of 5. Print them comma-separated on one line.

**Approach:** Walk every number in the range with `range(2000, 3201)` (the upper bound is exclusive, so `3201` is needed to include 3200), keep the ones satisfying both modulo conditions, and join them with `,`.

```python
l = []
for i in range(2000, 3201):
    if (i % 7 == 0) and (i % 5 != 0):
        l.append(str(i))

print(",".join(l))
```

`str(i)` is necessary before appending — `",".join()` requires every element to already be a string, since it can't implicitly convert integers.

### Question 2. Factorial of a number

**Problem:** Compute the factorial of a number read from console input. Input `8` → output `40320`.

**Approach:** A factorial is naturally recursive: `n! = n * (n-1)!`, with the base case `0! = 1`. Read the input with `input()` (Python 3 — `raw_input()` from the original was renamed) and convert it with `int()`.

```python
def fact(x):
    if x == 0:
        return 1
    return x * fact(x - 1)

x = int(input())
print(fact(x))
```

*(Fixed from the source: `raw_input()` and `print fact(x)` are Python 2 syntax — Python 3 unifies `input()`/`raw_input()` into just `input()`, and `print` is a function requiring parentheses.)*

### Question 3. Dictionary of squares

**Problem:** Given `n`, build and print a dictionary mapping every integer `1..n` to its square. Input `8` → `{1: 1, 2: 4, ..., 8: 64}`.

**Approach:** Loop `1` to `n` inclusive (`range(1, n+1)`) and assign each key its squared value.

```python
n = int(input())
d = dict()
for i in range(1, n + 1):
    d[i] = i * i

print(d)
```

### Question 4. Comma-separated input into a list and a tuple

**Problem:** Read a comma-separated sequence of numbers and build both a `list` and a `tuple` containing them.

**Approach:** `str.split(",")` turns the raw input into a list of string tokens directly; `tuple()` converts that list into a tuple.

```python
values = input()
l = values.split(",")
t = tuple(l)
print(l)
print(t)
```

Note the elements stay as **strings** (`'34'`, not `34`) — the problem's expected output shows quoted strings, confirming no numeric conversion is required here.

---

## A First OOP Class (Level 1)

### Question 5. A class with getString/printString

**Problem:** Define a class with a method to read a string from the console and another to print it upper-cased.

**Approach:** Store the read value on `self` in `getString`, so `printString` can access it later — this is the simplest possible illustration of instance state.

```python
class InputOutString(object):
    def __init__(self):
        self.s = ""

    def getString(self):
        self.s = input()

    def printString(self):
        print(self.s.upper())

strObj = InputOutString()
strObj.getString()
strObj.printString()
```

---

## Formulas, Arrays & Sequence Processing (Level 2)

### Question 6. Q = sqrt(2CD/H) for a sequence of D values

**Problem:** With fixed `C=50`, `H=30`, compute `Q = sqrt(2*C*D/H)` for each comma-separated `D` value from input, rounding each result to the nearest integer.

**Approach:** Parse each token as a float, apply the formula, and round with `round()` before converting to `int` (rounding first avoids truncation errors from just calling `int()` directly, e.g. `int(25.9999)` would wrongly give `25`).

```python
import math

c = 50
h = 30
value = []
items = [x for x in input().split(",")]
for d in items:
    value.append(str(int(round(math.sqrt(2 * c * float(d) / h)))))

print(",".join(value))
```

### Question 7. Build an X×Y multiplication grid

**Problem:** Given two digits `X, Y` as input, build a 2D array where element `[i][j] = i*j`.

**Approach:** A nested list comprehension builds the `X`-row-by-`Y`-column grid; a plain double `for` loop then fills each cell with `row * col`.

```python
input_str = input()
dimensions = [int(x) for x in input_str.split(",")]
rowNum = dimensions[0]
colNum = dimensions[1]
multilist = [[0 for col in range(colNum)] for row in range(rowNum)]

for row in range(rowNum):
    for col in range(colNum):
        multilist[row][col] = row * col

print(multilist)
```

The nested comprehension `[[0 for col in range(colNum)] for row in range(rowNum)]` is worth internalizing — it's the standard, safe way to build a 2D list; using `[[0] * colNum] * rowNum` instead is a classic bug, since it would make every row reference the **same** inner list object.

### Question 8. Sort comma-separated words alphabetically

**Problem:** Read comma-separated words and print them, sorted alphabetically, comma-separated.

```python
items = [x for x in input().split(",")]
items.sort()
print(",".join(items))
```

`list.sort()` sorts in place (returns `None`) — that's fine here since we only need the side effect, not a new list.

### Question 9. Capitalize each line of input

**Problem:** Read lines until a blank line, printing each capitalized (fully upper-cased).

**Approach:** Loop reading lines with `input()` until an empty string signals the end, collecting the upper-cased versions, then print them all.

```python
lines = []
while True:
    s = input()
    if s:
        lines.append(s.upper())
    else:
        break

for sentence in lines:
    print(sentence)
```

### Question 10. Dedupe and sort whitespace-separated words

**Problem:** Read a line of whitespace-separated words, remove duplicates, and print the result sorted alphabetically.

**Approach:** `set()` automatically discards duplicates; `sorted()` then returns the unique words in alphabetical order.

```python
s = input()
words = [word for word in s.split(" ")]
print(" ".join(sorted(set(words))))
```

### Question 11. Filter 4-digit binary numbers divisible by 5

**Problem:** From a comma-separated list of 4-digit binary numbers, print only those divisible by 5.

**Approach:** `int(p, 2)` parses a binary string using base 2, converting it to a real integer we can test with `%`.

```python
value = []
items = [x for x in input().split(",")]
for p in items:
    intp = int(p, 2)
    if not intp % 5:
        value.append(p)

print(",".join(value))
```

### Question 12. Numbers with all even digits, 1000–3000

**Problem:** Find numbers between 1000 and 3000 (inclusive) where every digit is even.

**Approach:** Convert each number to a string so its individual digit characters can be indexed and checked one at a time.

```python
values = []
for i in range(1000, 3001):
    s = str(i)
    if (int(s[0]) % 2 == 0) and (int(s[1]) % 2 == 0) and (int(s[2]) % 2 == 0) and (int(s[3]) % 2 == 0):
        values.append(s)
print(",".join(values))
```

A more scalable version avoids hardcoding 4 digit positions: `if all(int(digit) % 2 == 0 for digit in s):` — worth knowing as the idiomatic alternative once the fixed range no longer guarantees a fixed digit count.

### Question 13. Count letters and digits in a sentence

```python
s = input()
d = {"DIGITS": 0, "LETTERS": 0}
for c in s:
    if c.isdigit():
        d["DIGITS"] += 1
    elif c.isalpha():
        d["LETTERS"] += 1

print("LETTERS", d["LETTERS"])
print("DIGITS", d["DIGITS"])
```

`str.isdigit()` and `str.isalpha()` are the built-in character classifiers that make this a one-pass, branch-per-character scan — no regex needed.

### Question 14. Count upper- and lower-case letters

```python
s = input()
d = {"UPPER CASE": 0, "LOWER CASE": 0}
for c in s:
    if c.isupper():
        d["UPPER CASE"] += 1
    elif c.islower():
        d["LOWER CASE"] += 1

print("UPPER CASE", d["UPPER CASE"])
print("LOWER CASE", d["LOWER CASE"])
```

### Question 15. Compute a + aa + aaa + aaaa

**Problem:** Given a single digit `a`, compute `a + aa + aaa + aaaa` (string-repeated digit, read as a number). Input `9` → `9 + 99 + 999 + 9999 = 11106`.

**Approach:** Build each term by string-repeating the digit character, then convert to `int` and sum.

```python
a = input()
n1 = int(f"{a}")
n2 = int(f"{a}{a}")
n3 = int(f"{a}{a}{a}")
n4 = int(f"{a}{a}{a}{a}")
print(n1 + n2 + n3 + n4)
```

*(Modernized from the original's `"%s" % a` style formatting to f-strings — functionally identical, but this is the idiomatic Python 3 way to build these strings today, see the interview guide's [Q30 on string formatting](python-interview-questions-answers.md#30-what-are-the-different-ways-to-format-strings-in-python--formatting-format-f-strings).)*

### Question 16. Square each odd number via list comprehension

**Problem:** *"Use a list comprehension to square each odd number in a list."* Input `1,2,3,4,5,6,7,8,9` → output `1,3,5,7,9`.

**Bug in the source:** the expected output (`1,3,5,7,9`) is just the **odd numbers themselves**, not their squares (`1,9,25,49,81`) — the sample output in the original problem statement doesn't actually match its own title. Both a literal-title-following solution and a filter-only solution matching the sample output are shown below so you can see the (very common) discrepancy for yourself.

```python
# Matches the STATED sample output (filters odd numbers, doesn't square them):
values = input()
numbers = [x for x in values.split(",") if int(x) % 2 != 0]
print(",".join(numbers))
# Input:  1,2,3,4,5,6,7,8,9  ->  Output: 1,3,5,7,9

# Matches the TITLE ("square each odd number"):
values = input()
numbers = [str(int(x) ** 2) for x in values.split(",") if int(x) % 2 != 0]
print(",".join(numbers))
# Input:  1,2,3,4,5,6,7,8,9  ->  Output: 1,9,25,49,81
```

### Question 17. Compute net bank balance from a transaction log

**Problem:** Read `D <amount>` (deposit) / `W <amount>` (withdrawal) lines until blank input, and print the resulting net balance.

```python
netAmount = 0
while True:
    s = input()
    if not s:
        break
    values = s.split(" ")
    operation = values[0]
    amount = int(values[1])
    if operation == "D":
        netAmount += amount
    elif operation == "W":
        netAmount -= amount

print(netAmount)
```

---

## Validation, Sorting & Robot Movement (Level 3)

### Question 18. Password validation

**Problem:** From comma-separated candidate passwords, print (comma-separated) only the ones satisfying **all** of: at least one lowercase letter, one digit, one uppercase letter, one of `$#@`, and a length between 6 and 12 characters.

**Approach:** Check the length first (cheapest check, skip early), then run four independent `re.search()` checks — each pattern only needs to find **one** matching character anywhere in the string.

```python
import re

value = []
items = [x for x in input().split(",")]
for p in items:
    if len(p) < 6 or len(p) > 12:
        continue
    if not re.search("[a-z]", p):
        continue
    elif not re.search("[0-9]", p):
        continue
    elif not re.search("[A-Z]", p):
        continue
    elif not re.search("[$#@]", p):
        continue
    elif re.search(r"\s", p):
        continue
    value.append(p)

print(",".join(value))
```

*(The regex `\s` is written as a raw string, `r"\s"` — see the [interview guide's note on raw strings](python-interview-questions-answers.md#36-what-are-raw-strings-and-when-do-you-use-them); it's harmless either way here since `\s` isn't a recognized Python escape sequence, but it's best practice for any regex pattern.)*

### Question 19. Sort (name, age, height) tuples by multiple keys

**Problem:** Read `name,age,height` lines until blank input, then print them sorted first by name, then age, then height.

**Approach:** `operator.itemgetter(0, 1, 2)` builds a sort key that compares tuples position-by-position — exactly Python's own tuple comparison semantics, which is what "sort by name, then age, then height" means.

```python
from operator import itemgetter

l = []
while True:
    s = input()
    if not s:
        break
    l.append(tuple(s.split(",")))

print(sorted(l, key=itemgetter(0, 1, 2)))
```

*(The original had the `from operator import ...` line floating outside the code block — moved inside here so the snippet is actually runnable standalone.)*

### Question 20. A generator for multiples of 7

**Problem:** Define a class with a generator method yielding numbers divisible by 7, between 0 and `n`.

**Bug in the source:** the original called `reverse(100)`, a function that's never defined anywhere in the exercise — that's simply a typo for the generator function itself, `putNumbers(100)`.

```python
def putNumbers(n):
    i = 0
    while i < n:
        j = i
        i = i + 1
        if j % 7 == 0:
            yield j

for i in putNumbers(100):
    print(i)
```

### Question 21. Robot distance from origin

**Problem:** Given a sequence of `UP/DOWN/LEFT/RIGHT <steps>` moves (blank line ends input), compute the robot's rounded straight-line distance from `(0,0)`.

```python
import math

pos = [0, 0]
while True:
    s = input()
    if not s:
        break
    movement = s.split(" ")
    direction = movement[0]
    steps = int(movement[1])
    if direction == "UP":
        pos[0] += steps
    elif direction == "DOWN":
        pos[0] -= steps
    elif direction == "LEFT":
        pos[1] -= steps
    elif direction == "RIGHT":
        pos[1] += steps

print(int(round(math.sqrt(pos[1] ** 2 + pos[0] ** 2))))
```

This is just the Pythagorean theorem applied to the final `(x, y)` offset — the specific up/down/left/right bookkeeping only matters for computing that final offset correctly.

---

## Word Frequency (Level 3)

### Question 22. Word frequency, sorted alphabetically

**Problem:** Count occurrences of each word in a line of input, then print `word:count` sorted alphabetically.

**Bug in the source:** the original does `words = freq.keys(); words.sort()` — in Python 3, `dict.keys()` returns a **view object**, not a list, and view objects have no `.sort()` method (`AttributeError`). It needs to go through `sorted()` instead.

```python
freq = {}
line = input()
for word in line.split():
    freq[word] = freq.get(word, 0) + 1

for w in sorted(freq.keys()):
    print(f"{w}:{freq[w]}")
```

---

## Functions & Introspection Revisited (Level 1)

### Question 23. Square of a number

```python
def square(num):
    return num ** 2

print(square(2))
print(square(3))
```

### Question 24. Printing built-in documentation

**Problem:** Print the docstrings of some built-in functions using `__doc__`, and add a docstring to your own function too.

```python
print(abs.__doc__)
print(int.__doc__)
print(input.__doc__)

def square(num):
    '''Return the square value of the input number.

    The input number must be an integer.
    '''
    return num ** 2

print(square(2))
print(square.__doc__)
```

*(`input.__doc__` replaces the original's `raw_input.__doc__`, since `raw_input` no longer exists in Python 3.)*

### Question 25. Class parameter vs. instance parameter

**Problem:** Define a class with a class-level attribute and a same-named instance attribute, and show that setting the instance attribute doesn't affect the class-level one.

```python
class Person:
    # Class parameter — shared by all instances unless shadowed
    name = "Person"

    def __init__(self, name=None):
        # Instance parameter — shadows the class parameter on THIS instance only
        self.name = name

jeffrey = Person("Jeffrey")
print(f"{Person.name} name is {jeffrey.name}")

nico = Person()
nico.name = "Nico"
print(f"{Person.name} name is {nico.name}")
```

See the interview guide's [Q63 on class vs. instance variables](python-interview-questions-answers.md#63-what-is-the-difference-between-class-variables-and-instance-variables) for the full mechanics of why assigning `self.name` never mutates the class-level `name`.

---

## Functions: Arithmetic, Strings & Conditionals

### Question 26. Sum of two numbers

```python
def SumFunction(number1, number2):
    return number1 + number2

print(SumFunction(1, 2))
```

### Question 27. Convert an integer to a string and print it

```python
def printValue(n):
    print(str(n))

printValue(3)
```

### Question 28. Convert an integer to a string and print it (again)

The source repeats Question 27 verbatim as Question 28 — an apparent duplication in the original exercise set. The same solution applies:

```python
def printValue(n):
    print(str(n))

printValue(3)
```

### Question 29. Sum two numbers given as strings

```python
def printValue(s1, s2):
    print(int(s1) + int(s2))

printValue("3", "4")   # 7
```

### Question 30. Concatenate two strings

```python
def printValue(s1, s2):
    print(s1 + s2)

printValue("3", "4")   # 34
```

### Question 31. Print the longer of two strings

**Problem:** Print whichever string is longer; if they're equal length, print both.

```python
def printValue(s1, s2):
    len1 = len(s1)
    len2 = len(s2)
    if len1 > len2:
        print(s1)
    elif len2 > len1:
        print(s2)
    else:
        print(s1)
        print(s2)

printValue("one", "three")
```

### Question 32. Even or odd

**Bug in the source:** the code block in the original is missing its closing ` ``` ` fence, which (in a Markdown renderer) makes the next several questions render as if they were part of this code block. The actual solution logic itself is fine:

```python
def checkValue(n):
    if n % 2 == 0:
        print("It is an even number")
    else:
        print("It is an odd number")

checkValue(7)
```

---

## Dictionaries, Lists & Tuples via Comprehension

### Question 33. Dictionary of squares for keys 1-3

```python
def printDict():
    d = dict()
    d[1] = 1
    d[2] = 2 ** 2
    d[3] = 3 ** 2
    print(d)

printDict()
```

### Question 34. Dictionary of squares for keys 1-20

```python
def printDict():
    d = dict()
    for i in range(1, 21):
        d[i] = i ** 2
    print(d)

printDict()
```

### Question 35. Print only the values of that dictionary

```python
def printDict():
    d = dict()
    for i in range(1, 21):
        d[i] = i ** 2
    for (k, v) in d.items():
        print(v)

printDict()
```

### Question 36. Print only the keys of that dictionary

```python
def printDict():
    d = dict()
    for i in range(1, 21):
        d[i] = i ** 2
    for k in d.keys():
        print(k)

printDict()
```

### Question 37. A list of squares, 1-20

```python
def printList():
    li = list()
    for i in range(1, 21):
        li.append(i ** 2)
    print(li)

printList()
```

### Question 38. First 5 elements of that list

```python
def printList():
    li = list()
    for i in range(1, 21):
        li.append(i ** 2)
    print(li[:5])

printList()
```

### Question 39. Last 5 elements of that list

```python
def printList():
    li = list()
    for i in range(1, 21):
        li.append(i ** 2)
    print(li[-5:])

printList()
```

### Question 40. All elements except the first 5

**Bug in the source:** `print li[5:]` is Python 2 print-statement syntax — it's a `SyntaxError` in Python 3.

```python
def printList():
    li = list()
    for i in range(1, 21):
        li.append(i ** 2)
    print(li[5:])

printList()
```

### Question 41. Same list of squares, as a tuple

```python
def printTuple():
    li = list()
    for i in range(1, 21):
        li.append(i ** 2)
    print(tuple(li))

printTuple()
```

### Question 42. Split a tuple into two halves

**Problem:** Given `(1,2,3,4,5,6,7,8,9,10)`, print the first half and the second half on separate lines.

```python
tp = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
tp1 = tp[:5]
tp2 = tp[5:]
print(tp1)
print(tp2)
```

### Question 43. Even numbers from a tuple, as a new tuple

**Problem:** From `(1,2,3,4,5,6,7,8,9,10)`, build a new tuple of just the even values.

**Bug in the source:** the original does `for i in tp: if tp[i]%2==0:` — this iterates `i` over the tuple's **values** (1 through 10), then re-indexes the tuple *with those values*. Since the tuple only has 10 elements (valid indices 0-9), `tp[10]` raises `IndexError` as soon as `i` reaches `10`. The fix is to test `i` itself, not `tp[i]`.

```python
tp = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
li = list()
for i in tp:
    if i % 2 == 0:      # test the value directly, not tp[i]
        li.append(i)

tp2 = tuple(li)
print(tp2)
```

A one-line comprehension version is even cleaner and sidesteps this entire class of index-vs-value confusion: `tp2 = tuple(x for x in tp if x % 2 == 0)`.

### Question 44. Case-insensitive "yes" check

**Bug in the source:** `raw_input()` and bare `print "Yes"` are both Python 2 syntax.

```python
s = input()
if s == "yes" or s == "YES" or s == "Yes":
    print("Yes")
else:
    print("No")
```

A more robust, less enumeration-heavy version: `if s.lower() == "yes": print("Yes")` — it also happens to accept `"yEs"` and other mixed-case variants the original's exact-match list would miss.

---

## Conditionals, map(), filter() & Lambda

### Question 45. Filter even numbers with filter()

**Bug in the source:** in Python 3, `filter()` returns a lazy **filter object**, not a list — `print(evenNumbers)` would print something like `<filter object at 0x...>` instead of the actual values. Wrap it in `list()` to materialize and display it.

```python
li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
evenNumbers = list(filter(lambda x: x % 2 == 0, li))
print(evenNumbers)
```

### Question 46. Square every element with map()

**Bug in the source:** same issue as Question 45 — `map()` is lazy in Python 3 and needs `list()` to print its actual contents.

```python
li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
squaredNumbers = list(map(lambda x: x ** 2, li))
print(squaredNumbers)
```

### Question 47. Square only the even numbers, using map() + filter()

```python
li = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
evenNumbers = list(map(lambda x: x ** 2, filter(lambda x: x % 2 == 0, li)))
print(evenNumbers)
```

`filter()` runs first (innermost), narrowing the list down to evens; `map()` then squares whatever survives — a small pipeline of two lazy iterators, both list-wrapped at the very end.

### Question 48. Even numbers 1-20 with filter()

```python
evenNumbers = list(filter(lambda x: x % 2 == 0, range(1, 21)))
print(evenNumbers)
```

### Question 49. Squares 1-20 with map()

```python
squaredNumbers = list(map(lambda x: x ** 2, range(1, 21)))
print(squaredNumbers)
```

For all five of Questions 45-49, a list comprehension is the more idiomatic modern Python (see the interview guide's [Q45 on comprehensions vs. map/filter](python-interview-questions-answers.md#144-how-do-comprehensions-compare-to-mapfilter-in-performance-and-readability)) — e.g. Question 49 as `[x ** 2 for x in range(1, 21)]` needs no `lambda` and no `list()` wrapper. They're kept here in `map`/`filter`/`lambda` form since that's specifically what each exercise is testing.

---

## Classes, Inheritance & Static Methods

### Question 50. A static method

```python
class American(object):
    @staticmethod
    def printNationality():
        print("America")

anAmerican = American()
anAmerican.printNationality()
American.printNationality()
```

A `@staticmethod` can be called either on an instance or directly on the class itself, since — unlike a regular method — it never receives `self` or `cls` (see the interview guide's [Q74 on static/class/instance methods](python-interview-questions-answers.md#74-what-is-the-difference-between-a-static-method-a-class-method-and-an-instance-method)).

### Question 51. A class and a subclass

```python
class American(object):
    pass

class NewYorker(American):
    pass

anAmerican = American()
aNewYorker = NewYorker()
print(anAmerican)
print(aNewYorker)
```

### Question 52. A Circle class with an area method

**Bug in the source:** `print aCircle.area()` is Python 2 syntax.

```python
class Circle(object):
    def __init__(self, r):
        self.radius = r

    def area(self):
        return self.radius ** 2 * 3.14

aCircle = Circle(2)
print(aCircle.area())
```

### Question 53. A Rectangle class with an area method

```python
class Rectangle(object):
    def __init__(self, l, w):
        self.length = l
        self.width = w

    def area(self):
        return self.length * self.width

aRectangle = Rectangle(2, 10)
print(aRectangle.area())
```

### Question 54. Shape and its subclass Square, overriding area()

```python
class Shape(object):
    def __init__(self):
        pass

    def area(self):
        return 0

class Square(Shape):
    def __init__(self, l):
        Shape.__init__(self)
        self.length = l

    def area(self):
        return self.length * self.length

aSquare = Square(3)
print(aSquare.area())
```

`Square.area()` **overrides** `Shape.area()` — calling `.area()` on a `Square` instance runs `Square`'s version, not the inherited default that returns `0` (see the interview guide's [Q66 on method overriding](python-interview-questions-answers.md#66-what-is-method-overriding)).

---

## Exceptions

### Question 55. Raise a RuntimeError

```python
raise RuntimeError("something wrong")
```

### Question 56. Catch a division-by-zero exception

**Bug in the source:** `except Exception, err:` is Python 2 syntax — Python 3 requires `except Exception as err:`.

```python
def throws():
    return 5 / 0

try:
    throws()
except ZeroDivisionError:
    print("division by zero!")
except Exception as err:
    print("Caught an exception")
finally:
    print("In finally block for cleanup")
```

Note `ZeroDivisionError` is checked **first** — it's more specific than the general `Exception`, and `except` clauses are matched top to bottom, so the specific case must come before the catch-all (see the interview guide's [Q124 on handling multiple exception types](python-interview-questions-answers.md#124-how-do-you-handle-multiple-exception-types-in-one-block)).

### Question 57. A custom exception class

```python
class MyError(Exception):
    """My own exception class.

    Attributes:
        msg -- explanation of the error
    """

    def __init__(self, msg):
        self.msg = msg

error = MyError("something wrong")
```

---

## Regular Expressions & Unicode

### Question 58. Extract the username from an email address

**Bug in the source:** `raw_input()` is Python 2 syntax.

```python
import re

emailAddress = input()
pat2 = r"(\w+)@((\w+\.)+(com))"
r2 = re.match(pat2, emailAddress)
print(r2.group(1))
```

### Question 59. Extract the company name from an email address

```python
import re

emailAddress = input()
pat2 = r"(\w+)@(\w+)\.(com)"
r2 = re.match(pat2, emailAddress)
print(r2.group(2))
```

### Question 60. Extract all-digit words from a sentence

```python
import re

s = input()
print(re.findall(r"\d+", s))
```

### Question 61. Print a Unicode string

**Bug in the source:** the `u"..."` prefix is a harmless no-op in Python 3 (every `str` is already Unicode by default), but it still parses fine, so this one technically "worked" even in the unconverted original.

```python
unicodeString = "hello world!"
print(unicodeString)
```

### Question 62. Decode an ASCII string as UTF-8

**Bug in the source:** `unicode()` was a Python 2 built-in that no longer exists in Python 3 — every `str` is already Unicode, so no conversion function is needed at all. If you're converting `bytes` to `str`, use `.decode()` instead.

```python
s = input()
print(s)   # already a Unicode str in Python 3 — nothing further needed

# If you specifically have raw bytes to decode:
b = s.encode("ascii")
u = b.decode("utf-8")
print(u)
```

### Question 63. The Unicode source-encoding comment

```python
# -*- coding: utf-8 -*-
```

This comment (traditionally the first or second line of a `.py` file) tells older Python 2 interpreters what encoding the source file itself is written in. It's a historical relic — Python 3 source files are UTF-8 by default, so this line is no longer required, but it's still recognized and harmless to include for clarity or backward-compatibility with tooling.

---

## Recursion & Generators

### Question 64. Sum of 1/2 + 2/3 + ... + n/(n+1)

```python
n = int(input())
total = 0.0
for i in range(1, n + 1):
    total += float(i) / (i + 1)
print(total)
```

*(Renamed the accumulator from `sum` to `total` — `sum` is a built-in function, and shadowing it with a variable name is a common, easy-to-avoid gotcha.)*

### Question 65. f(n) = f(n-1) + 100, f(0) = 1

**Note:** the stated formula says `f(0)=1`, but the sample (`f(5) = 500`) is only consistent with a base case of `f(0)=0` (`0 + 100*5 = 500`) — the original solution (kept below) matches the *sample output*, not the *written formula*, another small inconsistency in the source material.

```python
def f(n):
    if n == 0:
        return 0
    return f(n - 1) + 100

n = int(input())
print(f(n))
```

### Question 66. Fibonacci via recursion

```python
def f(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return f(n - 1) + f(n - 2)

n = int(input())
print(f(n))
```

This naive recursive Fibonacci recomputes the same sub-values exponentially many times — for real use, wrap it in `@functools.lru_cache` (see the interview guide's [Q150 on memoization](python-interview-questions-answers.md#150-what-is-functoolslru_cache-and-how-does-memoization-work)) to make it fast.

### Question 67. Fibonacci sequence via list comprehension

```python
def f(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return f(n - 1) + f(n - 2)

n = int(input())
values = [str(f(x)) for x in range(0, n + 1)]
print(",".join(values))
```

### Question 68. Even numbers 0..n via a generator

```python
def EvenGenerator(n):
    i = 0
    while i <= n:
        if i % 2 == 0:
            yield i
        i += 1

n = int(input())
values = [str(i) for i in EvenGenerator(n)]
print(",".join(values))
```

### Question 69. Numbers divisible by both 5 and 7, via a generator

```python
def NumGenerator(n):
    for i in range(n + 1):
        if i % 5 == 0 and i % 7 == 0:
            yield i

n = int(input())
values = [str(i) for i in NumGenerator(n)]
print(",".join(values))
```

---

## Assertions, eval() & Binary Search

### Question 70. Assert every element of a list is even

```python
li = [2, 4, 6, 8]
for i in li:
    assert i % 2 == 0
```

Remember `assert` is stripped out entirely when Python runs with `-O` — it's meant for catching programmer errors during development, not for validating untrusted input (see the interview guide's [Q198 on assert](python-interview-questions-answers.md#198-what-is-an-assert-statement-and-when-is-it-disabled)).

### Question 71. Evaluate a math expression from input

**Bug in the source:** `raw_input()` is Python 2 syntax.

```python
expression = input()
print(eval(expression))
```

**A word of caution:** `eval()` executes arbitrary Python code — fine for a throwaway exercise with trusted, console-typed input, but never call `eval()` on input from an untrusted source (a web form, an API request) in real code, since it's a direct route to arbitrary code execution.

### Question 72 & 73. Binary search

**Problem:** Both Question 72 and Question 73 are identical in the source — a binary search function that returns the index of a target element in a sorted list, or `-1` if not found.

```python
import math

def bin_search(li, element):
    bottom = 0
    top = len(li) - 1
    index = -1
    while top >= bottom and index == -1:
        mid = int(math.floor((top + bottom) / 2.0))
        if li[mid] == element:
            index = mid
        elif li[mid] > element:
            top = mid - 1
        else:
            bottom = mid + 1
    return index

li = [2, 5, 7, 9, 11, 17, 222]
print(bin_search(li, 11))   # 4
print(bin_search(li, 12))   # -1
```

Each iteration halves the remaining search window by comparing against the midpoint, which is exactly why binary search runs in **O(log n)** instead of the O(n) a linear scan would need — but it only works on an **already-sorted** list.

---

## The random Module

### Question 74. A random float between 10 and 100

```python
import random
print(random.random() * 100)
```

**Note:** `random.random()` returns a float in `[0, 1)`, so `random.random() * 100` actually ranges over `[0, 100)`, not tightly bounded to `[10, 100]` as the question title implies — this mirrors the original's own solution, which has the same looseness. A version that actually honors a `[10, 100]` bound: `random.uniform(10, 100)`.

### Question 75. A random float between 5 and 95

```python
import random
print(random.random() * 100 - 5)
```

Same caveat as Question 74 — `random.uniform(5, 95)` is the precise, idiomatic way to generate a float within an exact bound.

### Question 76. A random even number, 0-10

```python
import random
print(random.choice([i for i in range(11) if i % 2 == 0]))
```

### Question 77. A random number divisible by 5 and 7

**Note:** the question text says "between 0 and 10 inclusive," but no number in that tiny range is divisible by both 5 and 7 (the smallest is 35) — the original solution's range of `range(201)` (0-200) is what actually makes the exercise solvable, so it's kept as-is here.

```python
import random
print(random.choice([i for i in range(201) if i % 5 == 0 and i % 7 == 0]))
```

### Question 78. A list of 5 random numbers, 100-200

**Bug in the source:** the original samples from `range(100)` (i.e., 0-99), not the stated 100-200 range.

```python
import random
print(random.sample(range(100, 201), 5))
```

`random.sample()` picks **distinct** elements (no repeats), unlike calling `random.choice()` in a loop, which could pick the same value twice.

### Question 79. A list of 5 random even numbers, 100-200

```python
import random
print(random.sample([i for i in range(100, 201) if i % 2 == 0], 5))
```

### Question 80. A list of 5 random numbers divisible by 5 and 7, 1-1000

```python
import random
print(random.sample([i for i in range(1, 1001) if i % 5 == 0 and i % 7 == 0], 5))
```

### Question 81. A random integer, 7-15

```python
import random
print(random.randrange(7, 16))
```

`random.randrange(7, 16)` is exclusive of the upper bound, so `16` (not `15`) is passed to include 15 in the possible results.

---

## zlib, timeit & shuffle

### Question 82. Compress and decompress a string

```python
import zlib

s = b"hello world!hello world!hello world!hello world!"
t = zlib.compress(s)
print(t)
print(zlib.decompress(t))
```

`zlib` works on `bytes`, not `str` — hence the `b"..."` byte-string literal (see the interview guide's [Q31 on str vs. bytes](python-interview-questions-answers.md#31-what-is-the-difference-between-a-str-object-and-a-bytes-object)).

### Question 83. Time 100 executions of "1+1"

```python
from timeit import Timer

t = Timer("for i in range(100): 1 + 1")
print(t.timeit())
```

### Question 84 & 85. Shuffle a list

**Problem:** Both Question 84 and Question 85 are identical in the source.

```python
from random import shuffle

li = [3, 6, 7, 8]
shuffle(li)
print(li)
```

`shuffle()` mutates the list **in place** and returns `None` — a classic gotcha is writing `li = shuffle(li)`, which would overwrite `li` with `None`.

---

## Nested Loops & List Comprehension Filtering

### Question 86. Generate all subject/verb/object sentences

```python
subjects = ["I", "You"]
verbs = ["Play", "Love"]
objects = ["Hockey", "Football"]
for i in range(len(subjects)):
    for j in range(len(verbs)):
        for k in range(len(objects)):
            sentence = f"{subjects[i]} {verbs[j]} {objects[k]}."
            print(sentence)
```

Iterating directly over the lists themselves (rather than their indices) is more idiomatic: `for s in subjects: for v in verbs: for o in objects: print(f"{s} {v} {o}.")` — same output, no index bookkeeping needed at all.

### Question 87. Remove even numbers via list comprehension

```python
li = [5, 6, 77, 45, 22, 12, 24]
li = [x for x in li if x % 2 != 0]
print(li)
```

### Question 88. Remove numbers divisible by 5 and 7

```python
li = [12, 24, 35, 70, 88, 120, 155]
li = [x for x in li if x % 5 != 0 and x % 7 != 0]
print(li)
```

### Question 89. Remove elements at even indexes

```python
li = [12, 24, 35, 70, 88, 120, 155]
li = [x for (i, x) in enumerate(li) if i % 2 != 0]
print(li)
```

### Question 90. A 3×5×8 3D array of zeros

```python
array = [[[0 for col in range(8)] for col in range(5)] for row in range(3)]
print(array)
```

Three nested comprehensions, one per dimension — the outermost builds 3 "layers," each of which builds 5 "rows," each of which builds 8 zero-filled "columns."

### Question 91. Remove elements at indexes 0, 4, 5

```python
li = [12, 24, 35, 70, 88, 120, 155]
li = [x for (i, x) in enumerate(li) if i not in (0, 4, 5)]
print(li)
```

### Question 92. Remove all occurrences of the value 24

```python
li = [12, 24, 35, 24, 88, 120, 155]
li = [x for x in li if x != 24]
print(li)
```

---

## Sets: Intersection & Deduplication

### Question 93. Intersection of two lists

```python
set1 = set([1, 3, 6, 78, 35, 55])
set2 = set([12, 24, 35, 24, 88, 120, 155])
set1 &= set2
li = list(set1)
print(li)
```

`&=` is the in-place set-intersection operator — equivalent to `set1 = set1 & set2` (or `set1 = set1.intersection(set2)`), keeping only elements present in **both** sets.

### Question 94. Deduplicate a list, preserving order

```python
def removeDuplicate(li):
    newli = []
    seen = set()
    for item in li:
        if item not in seen:
            seen.add(item)
            newli.append(item)
    return newli

li = [12, 24, 35, 24, 88, 120, 155, 88, 120, 155]
print(removeDuplicate(li))
```

This is the manual, explicit version of the technique covered in the interview guide's [Q47 on order-preserving deduplication](python-interview-questions-answers.md#47-how-do-you-remove-duplicates-from-a-list-while-preserving-order) — `list(dict.fromkeys(li))` achieves the same result in one line, using dict insertion-order preservation instead of a manually tracked `seen` set.

---

## More OOP: A Person Hierarchy

### Question 95. Person, Male and Female subclasses

```python
class Person(object):
    def getGender(self):
        return "Unknown"

class Male(Person):
    def getGender(self):
        return "Male"

class Female(Person):
    def getGender(self):
        return "Female"

aMale = Male()
aFemale = Female()
print(aMale.getGender())
print(aFemale.getGender())
```

`Person.getGender()` acts as a sensible default ("Unknown") for any future subclass that forgets to override it — each subclass here provides its own, more specific answer, a textbook example of polymorphism (see the interview guide's [Q71 on polymorphism](python-interview-questions-answers.md#71-what-is-polymorphism-in-python)).

---

## String Manipulation

### Question 96. Count occurrences of each character

**Bug in the source:** `raw_input()` is Python 2 syntax; also, the original reuses the loop variable name `s` for both the input string and the loop variable (`for s in s:`), which is confusing (though not technically broken, since `s` is fully consumed into the dict before being needed again) — renamed here for clarity.

```python
dic = {}
text = input()
for ch in text:
    dic[ch] = dic.get(ch, 0) + 1
print("\n".join(f"{k},{v}" for k, v in dic.items()))
```

`dict.get(ch, 0)` returns `0` for a character not seen yet, letting `+1` work uniformly whether or not the key already exists — avoiding an explicit `if ch not in dic: dic[ch] = 0` check.

### Question 97. Reverse a string

**Bug in the source:** `raw_input()` is Python 2 syntax.

```python
s = input()
s = s[::-1]
print(s)
```

The `[::-1]` slice — start and stop both omitted, step `-1` — is the idiomatic Python way to reverse any sequence (see the interview guide's [Q37 on reversing a string](python-interview-questions-answers.md#37-how-do-you-reverse-a-string-in-python)).

### Question 98. Print characters at even indexes

**Bug in the source:** `raw_input()` is Python 2 syntax.

```python
s = input()
s = s[::2]
print(s)
```

`[::2]` starts at index 0 and steps by 2, so it picks up indexes `0, 2, 4, ...` — exactly the even-indexed characters.

---

## Permutations & a Classic Puzzle

### Question 99. All permutations of [1, 2, 3]

**Bug in the source:** `print list(...)` is Python 2 print-statement syntax.

```python
import itertools
print(list(itertools.permutations([1, 2, 3])))
```

`itertools.permutations()` is lazy, like `map`/`filter` — wrapping it in `list()` is what actually forces all the permutations to be generated and displayed (see the interview guide's [Q184 on itertools](python-interview-questions-answers.md#184-what-is-the-itertools-module-and-what-are-some-commonly-used-functions-in-it)).

### Question 100. The chickens-and-rabbits puzzle

**Problem:** With 35 heads and 94 legs total among chickens (2 legs) and rabbits (4 legs), how many of each are there?

**Approach:** Brute-force every possible number of chickens `i` from `0` to `35`; the rabbit count `j` is then forced (`j = 35 - i`, since every animal has exactly one head), and we just check whether that split's total leg count matches 94.

```python
def solve(numheads, numlegs):
    ns = "No solutions!"
    for i in range(numheads + 1):
        j = numheads - i
        if 2 * i + 4 * j == numlegs:
            return i, j
    return ns, ns

numheads = 35
numlegs = 94
solutions = solve(numheads, numlegs)
print(solutions)   # (23, 12) -> 23 chickens, 12 rabbits
```

This could also be solved directly with a little algebra (`i + j = 35`, `2i + 4j = 94` → `j = (94 - 70)/2 = 12`, `i = 23`) in O(1) instead of the O(n) brute-force loop — but the brute-force version generalizes trivially to puzzles with more than two animal types, where a closed-form solution isn't as easy to write down.

---

*This concludes the answers guide, covering all 100 exercises from `100+ Python challenging programming exercises.txt`. For a deeper reference on the underlying Python concepts used throughout (comprehensions, generators, decorators, the GIL, and more), see the companion guide `python-interview-questions-answers.md`.*