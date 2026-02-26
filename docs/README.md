# Compact Chain List — Data Structures Project

Academic project for the **Data Structures** course. This repository implements a **Compact Chain List (CCL)** in C++: a compact representation of sequences where consecutive equal elements are stored as blocks (value + length).

## Project Structure

```
iridian-object-oriented-programming/
├── README.md
├── .gitignore
├── docs/
│   ├── development-log.txt      (development log; formerly bitacora.txt)
│   ├── preliminary-report.pdf   (preliminary report; add your PDF here)
│   └── final-report.pdf         (final report; add your PDF here)
├── include/
│   ├── ccl.h                    (CompactChainList class declaration)
│   └── node.h                   (Node class and Element type)
└── src/
    ├── ccl.cpp                  (CompactChainList implementation)
    ├── node.cpp                 (Node implementation)
    └── excusebureau.cpp         (Excuse Bureau problem / demo)
```

## Description

- **CompactChainList (CCL)**: Sequence stored as blocks of (value, length), implemented with a **circular doubly-linked list** of nodes.
- **Node**: Represents one block (element value and run length) with `prev`/`next` pointers.
- **excusebureau.cpp**: Standalone program using a character-based CCL for the “Excuse Bureau” (arena) problem.

---

## Techniques & Tools Used

- **Data structure**: Circular doubly-linked list for the CCL (each node = one block).
- **Object-oriented design**: Classes `Node` and `CompactChainList` with encapsulation (private members, public interface).
- **Constructors**: Default, from `vector<Element>`, and copy constructor (`const CompactChainList&`).
- **Operator overloading**: `+` (lexicographic fusion), `[]` (indexing), `<` and `==` (comparison for ordering/equality).
- **Static members**: `appendRemainingBlocks`, `sortVectorCCL` for operations that do not depend on a single instance.
- **Recursion**: Used in `countSubsequencesFrom` for counting (possibly non-consecutive) subsequence occurrences.
- **STL**: `vector`, `list`, `map`, and `std::sort` for algorithms and auxiliary storage.
- **Complexity-aware design**: Block-level traversal where possible (e.g. `getConsecutiveOcurrences`), auxiliary `findNodeAtPosition` for position-based operations without expanding the list.

---

## How to Run

From the project root:

**Option 1 — Build object files and link (CCL library):**

```bash
g++ -std=c++11 -I include -c src/node.cpp -o node.o
g++ -std=c++11 -I include -c src/ccl.cpp -o ccl.o
# Then link node.o and ccl.o into your main program with -I include when compiling the main .cpp
```

**Option 2 — Build the Excuse Bureau executable (standalone, no shared headers):**

```bash
g++ -std=c++11 -o excusebureau src/excusebureau.cpp
./excusebureau
```

Then feed input as required by the problem (e.g. number of keywords and excuses, then the lines of text).

**Option 3 — Build a program that uses the CCL from `include/` and `src/ccl.cpp` + `src/node.cpp`:**

```bash
g++ -std=c++11 -I include -o myprogram src/node.cpp src/ccl.cpp src/my_main.cpp
./myprogram
```

---

## Documentation

- **docs/development-log.txt**: Chronological development log (formerly *bitacora.txt*).
- **docs/preliminary-report.pdf**: Preliminary project report (add your PDF to this path).
- **docs/final-report.pdf**: Final project report (add your PDF to this path).

## Author

Martín Estrada Agudelo — Data Structures course project.

## License

This project is for academic use within the Data Structures course.
