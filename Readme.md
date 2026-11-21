# Head First Design Patterns: Java, Python and C++

Every chapter of *Head First Design Patterns* implemented in three languages. The Java code is the original; the Python and C++ ports follow the same class names and program flow so the three can be compared side by side.

## Website

`index.html` is the whole repo as a browsable site: rendered notes, the three language versions of every example, the interview Q&A, search, and a file browser. `protocol-explorer/` is linked as a separate sub page.

- **Open it:** serve the folder (`python3 -m http.server`) and visit `http://localhost:8000/`, or deploy the repo root with GitHub Pages (`.nojekyll` is included).
- **Regenerate after editing any note or code:** `python3 site-src/build_site.py`. The page embeds the content, so it must be rebuilt for changes to show.
- The site needs internet only for three CDN libraries (marked, highlight.js, mermaid); the text still shows without them.

## Layout

```
chapN-<pattern>/
├── README.md                   pattern notes + Java vs Python vs C++ differences
├── chapN-<pattern>-notes.md    one-page revision notes (Obsidian-ready, Mermaid diagrams)
├── java/                       original code (sub-folders kept)
├── python/                     Python 3, stdlib only      -> python3 <entry>.py
└── cpp/                        C++17, stdlib only         -> make run   (Makefile per folder)
notes/                          interview Q&A, exercises, PDF
site-src/                       generator for index.html
```

Java: `javac -d out *.java && java -cp out <EntryPoint>` (some files declare a `package`, so use `package.Entry`).
Python: run from inside the chapter's `python/` folder.
C++: `make run`, `make clean`. Builds are warning-free with `-Wall -Wextra -pedantic`.

## Index

| Chapter | Pattern | Revision notes | Sub-folders |
|---|---|---|---|
| [1](chap1-strategy/README.md) | Strategy | [notes](chap1-strategy/chap1-strategy-notes.md) | |
| [2](chap2-observer/README.md) | Observer | [notes](chap2-observer/chap2-observer-notes.md) | `pull` |
| [3](chap3-decorator/README.md) | Decorator | [notes](chap3-decorator/chap3-decorator-notes.md) | |
| [4](chap4-factory/README.md) | Factory Method, Abstract Factory | [notes](chap4-factory/chap4-factory-notes.md) | |
| [5](chap5-singleton/README.md) | Singleton | [notes](chap5-singleton/chap5-singleton-notes.md) | |
| [6](chap6-command/README.md) | Command | [notes](chap6-command/chap6-command-notes.md) | |
| [7](chap7-adaptive/README.md) | Adapter, Facade, Least Knowledge | [notes](chap7-adaptive/chap7-adaptive-notes.md) | `facade`, `leastknowledge` |
| [8](chap8-template-method/README.md) | Template Method | [notes](chap8-template-method/chap8-template-method-notes.md) | |
| [9](chap9-iterator-composite/README.md) | Iterator, Composite | [notes](chap9-iterator-composite/chap9-iterator-composite-notes.md) | |
| [10](chap10-state-pattern/README.md) | State | [notes](chap10-state-pattern/chap10-state-pattern-notes.md) | |
| [11](chap11-proxy/README.md) | Proxy | [notes](chap11-proxy/chap11-proxy-notes.md) | `protection-proxy`, `virtual-proxy` |
| [12](chap12-compound/README.md) | Compound (MVC) | [notes](chap12-compound/chap12-compound-notes.md) | `mvc` |
| [13](chap13-patterns-in-the-real-world/chap13-patterns-in-the-real-world-notes.md) | Patterns in the Real World | [notes](chap13-patterns-in-the-real-world/chap13-patterns-in-the-real-world-notes.md) | no code |
| [14](chap14-leftover-patterns/chap14-leftover-patterns-notes.md) | Appendix: Leftover Patterns (Bridge, Builder, Chain of Responsibility, Flyweight, Interpreter, Mediator, Memento, Prototype, Visitor) | [notes](chap14-leftover-patterns/chap14-leftover-patterns-notes.md) | no code |

## Verification status

Java, Python and C++ stdout were diffed for every entry point that can run headless: they match exactly, apart from the cases below. Each chapter README explains its deviations.

- **Simulated, so not comparable with Java:** Swing and display code (ch2 `SwingObserverExample`, ch8 `MyFrame`, ch11 `ImageProxyTestDrive`, ch12 `DJTestDrive`/`HeartTestDrive`), RMI (ch11 `GumballMonitorTestDrive`), and MIDI timing (ch12 BeatModel uses a simulated clock). Python and C++ agree with each other.
- **Random winner (ch10, ch11):** deterministic by default or with a fixed seed. C++ and Python use different generators, so the same seed gives different sequences.
- **Extras with no Java counterpart:** ch5 thread demo, ch9 native-iteration demos.
- ch10 `GumballMachineTestDrive2` matches Java once the per-run `@hash` in the state's default `toString` is normalized.

## Reference material

### Java

- https://www.geeksforgeeks.org/java/java-interview-questions/
- https://www.interviewbit.com/java-interview-questions/
- https://github.com/in28minutes/JavaInterviewQuestionsAndAnswers
- https://www.javacodegeeks.com/java-interview-questions.html

### Python

- https://www.geeksforgeeks.org/python/python-interview-questions/
- https://www.interviewbit.com/python-interview-questions/
- https://www.sanfoundry.com/1000-python-questions-answers/

### C++

- https://www.geeksforgeeks.org/cpp/cpp-interview-questions/
- https://www.interviewbit.com/cpp-interview-questions/
- https://www.geeksforgeeks.org/cpp/cpp-dynamic-memory-and-oops-practice-problems/
- https://gist.github.com/ayan-b/8802f7ba2e1d95df19cf90e2a98214bc

### Design Patterns book

- https://books.google.co.in/books/about/Head_First_Design_Patterns.html?id=GGpXN9SMELMC&redir_esc=y

### Low-level design

- https://github.com/ashishps1/awesome-low-level-design
- https://github.com/prasadgujar/low-level-design-primer
