# CCP6214 Assignment — Group Instructions

## 📁 Project Structure

```
project/
├── README.md                    ← You are here
├── Makefile                     ← Compiles all programs
├── common.h                     ← Shared header (don't edit unless agreed)
├── dataset_generator.cpp        ← Member A
├── radix_sort.cpp               ← Member B
├── radix_sort_step.cpp          ← Member B
├── heap_sort.cpp                ← Member C
├── heap_sort_step.cpp           ← Member C
├── hash_table_search.cpp        ← Member D
└── hash_table_search_step.cpp   ← Member D
```

---

## 👥 Who Does What

| Member | Code Files | Report Section | Demo |
|--------|-----------|----------------|------|
| **Member A (Leader)** | `dataset_generator.cpp` | Q1: Dataset Generation, Q6: Document completeness, Cover page, TOC, References | Dataset Generator |
| **Member B** | `radix_sort.cpp`, `radix_sort_step.cpp` | Q2: Radix Sort | Radix Sort |
| **Member C** | `heap_sort.cpp`, `heap_sort_step.cpp` | Q3: Heap Sort | Heap Sort |
| **Member D** | `hash_table_search.cpp`, `hash_table_search_step.cpp` | Q4: Hash Table Search | Hash Table Search |

> **Everyone** must: run all algorithms on their own PC (10+ input sizes), take screenshots, write Q7 (experiments), and be ready to explain ALL code at the interview.

---

## 🔧 Setup (Everyone Must Do This First)

### Step 1: Install a C++ Compiler

**Windows:**
- Install [MinGW-w64](https://www.mingw-w64.org/) or use the g++ that comes with VS Code + C++ extension
- After installing, open Command Prompt and verify:
  ```
  g++ --version
  ```

**Mac:**
```bash
xcode-select --install
g++ --version
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt install g++ make
g++ --version
```

### Step 2: Clone the Repository

```bash
git clone <YOUR_GITHUB_REPO_URL>
cd <project-folder>
```

### Step 3: Compile Everything

```bash
make all
```

This should produce 7 executable files with **zero errors and zero warnings**.

If you see compilation errors in YOUR assigned files, fix them, then:
```bash
git add .
git commit -m "fix: describe what you fixed"
git push
```

---

## 📝 Step-by-Step Tasks for Each Member

---

### 🅰️ Member A — Leader (Dataset Generator)

#### Your Code File
- `dataset_generator.cpp`

#### What You Need To Do

1. **Replace the student ID seed** (line ~56):
   ```cpp
   string studentId = "YOUR_STUDENT_ID"; // ← Put group leader's student ID here
   ```
   For example, if the leader's ID is `243UC247CT`, change it to:
   ```cpp
   string studentId = "243UC247CT";
   ```
   The code will automatically convert letters to digits using the mapping from the assignment.

2. **Test your generator** by running it with different sizes:
   ```bash
   ./dataset_generator 1000
   ./dataset_generator 10000
   ./dataset_generator 100000
   ```
   Check that the output file `dataset_n.csv` looks like:
   ```
   4047986219,hatts
   4047986452,kqclx
   ...
   ```
   Each row should have a **10-digit integer** and a **5-letter lowercase string**.

3. **Verify uniqueness** — open the CSV and confirm no duplicate integers.

4. **Commit and push** so others can use your generator.

5. **Write Q1 in the report** — include:
   - How the generator works (Fisher-Yates shuffle, sequential + randomize)
   - How the seed works (student ID → number mapping)
   - Code snippets showing key parts
   - Screenshot of sample output (first 10 rows)

6. **Also responsible for**:
   - Cover page, Table of Contents, References page
   - Final document formatting and completeness check (Q6)
   - Upload large files to OneDrive
   - Create and submit the final `.zip`

---

### 🅱️ Member B — Radix Sort

#### Your Code Files
- `radix_sort.cpp` — Sorts full dataset and measures running time
- `radix_sort_step.cpp` — Shows step-by-step output for a subset of rows

#### What You Need To Do

1. **Review and understand** both files. Make sure you can explain:
   - How LSD Radix Sort works (processing rightmost digit first)
   - Why counting sort is used as the stable sub-routine
   - Time complexity: **O(d × (n + k))** where d=10, k=10
   - Space complexity: **O(n + k)**

2. **Test with a small dataset**:
   ```bash
   # First generate a dataset (or get one from Member A)
   ./dataset_generator 1000

   # Run radix sort
   ./radix_sort dataset_1000.csv

   # Check output
   head -5 radix_sorted_dataset_1000.csv
   ```

3. **Test the step output**:
   ```bash
   ./radix_sort_step dataset_1000.csv 1 7
   cat dataset_1000_radix_sorted_step_1_7.txt
   ```
   Expected format:
   ```
   [int/name, int/name, ...] original
   [int/name, int/name, ...] d=10
   [int/name, int/name, ...] d=9
   ...
   [int/name, int/name, ...] d=1
   ```

4. **If you find bugs, fix them** and push to GitHub:
   ```bash
   git add .
   git commit -m "fix: radix sort - describe fix"
   git push
   ```

5. **Write Q2 in the report** — include:
   - Theoretical time & space complexity analysis
   - How the algorithm works (diagrams help)
   - Code snippets with explanations of key parts
   - The step-by-step output from `radix_sort_step`
   - Running time table for 10+ input sizes (from Q7)
   - Chart/graph of input size vs running time

---

### 🅲 Member C — Heap Sort

#### Your Code Files
- `heap_sort.cpp` — Sorts full dataset and measures running time
- `heap_sort_step.cpp` — Shows step-by-step output for a subset of rows

#### What You Need To Do

1. **Review and understand** both files. Make sure you can explain:
   - How Max Heap works (parent > children property)
   - `buildMaxHeap` — O(n) to build heap from unsorted array
   - `heapify` — O(log n) to restore heap property
   - Overall time complexity: **O(n log n)** — all cases (best, average, worst)
   - Space complexity: **O(1)** — in-place sorting

2. **Test with a small dataset**:
   ```bash
   # First generate a dataset
   ./dataset_generator 1000

   # Run heap sort
   ./heap_sort dataset_1000.csv

   # Check output
   head -5 heap_sorted_dataset_1000.csv
   ```

3. **Test the step output**:
   ```bash
   ./heap_sort_step dataset_1000.csv 1 7
   cat dataset_1000_heap_sorted_step_1_7.txt
   ```
   Expected format:
   ```
   [int/name, int/name, ...] initial
   [int/name, int/name, ...] i = 6
   [int/name, int/name, ...] i = 5
   ...
   [int/name, int/name, ...] i = 1
   ```

4. **If you find bugs, fix them** and push to GitHub:
   ```bash
   git add .
   git commit -m "fix: heap sort - describe fix"
   git push
   ```

5. **Write Q3 in the report** — include:
   - Theoretical time & space complexity analysis
   - How the algorithm works (max heap diagram, extract-max process)
   - Code snippets with explanations of `heapify` and `buildMaxHeap`
   - The step-by-step output from `heap_sort_step`
   - Running time table for 10+ input sizes (from Q7)
   - Chart/graph of input size vs running time

---

### 🅳 Member D — Hash Table Search

#### Your Code Files
- `hash_table_search.cpp` — Searches hash table and measures best/average/worst times
- `hash_table_search_step.cpp` — Shows search path for a specific target

#### What You Need To Do

1. **Review and understand** both files. Make sure you can explain:
   - Hash function: `h(key) = key % tableSize` (tableSize is a prime number)
   - Collision resolution: **Separate chaining** (linked list per bucket)
   - Best case: **O(1)** — direct hit, chain length 1
   - Average case: **O(1 + α)** where α = n/tableSize (load factor)
   - Worst case: **O(n)** — all elements in same chain
   - Space complexity: **O(n + tableSize)**

2. **Test with a small dataset**:
   ```bash
   # First generate a dataset
   ./dataset_generator 1000

   # Run hash table search
   ./hash_table_search dataset_1000.csv
   ```

3. **Test the step output**:
   ```bash
   # Find a valid target from the first line of the dataset
   head -1 dataset_1000.csv
   # Example output: 4047986219,hatts
   # Use the integer as the found target

   ./hash_table_search_step dataset_1000.csv 4047986219 123456789
   ```
   This produces two files:
   - `dataset_1000_hash_table_search_step_4047986219.txt` (found case)
   - `dataset_1000_hash_table_search_step_123456789.txt` (not found case)

   Expected format for **found**:
   ```
   Search for target: 4047986219 (found)
   Hash index: 308
   4047986219 = 4047986219/hatts
   ```

   Expected format for **not found**:
   ```
   Search for target: 123456789 (not found)
   Hash index: 594
   4047986505 != 123456789
   -1 != 123456789
   ```

4. **If you find bugs, fix them** and push to GitHub:
   ```bash
   git add .
   git commit -m "fix: hash table search - describe fix"
   git push
   ```

5. **Write Q4 in the report** — include:
   - Theoretical time & space complexity analysis (best, average, worst)
   - How the hash table works (hash function, chaining)
   - Code snippets with explanations
   - Search step outputs (found and not-found cases)
   - Running time table for best/average/worst at 10+ input sizes
   - Chart/graph of input size vs running time

---

## 🧪 Experiments — EVERYONE Must Do This Individually

### Step 1: Generate All 10 Datasets

Member A generates all 10 sizes. Share the files via GitHub or OneDrive:

| Size # | Input Size | Filename |
|--------|-----------|----------|
| 1 | 1,000 | `dataset_1000.csv` |
| 2 | 10,000 | `dataset_10000.csv` |
| 3 | 50,000 | `dataset_50000.csv` |
| 4 | 100,000 | `dataset_100000.csv` |
| 5 | 500,000 | `dataset_500000.csv` |
| 6 | 1,000,000 | `dataset_1000000.csv` |
| 7 | 5,000,000 | `dataset_5000000.csv` |
| 8 | 10,000,000 | `dataset_10000000.csv` |
| 9 | 50,000,000 | `dataset_50000000.csv` |
| 10 | 100,000,000 | `dataset_100000000.csv` |

> ⚠️ Adjust size #10 if it takes more than 6 hours. The largest size MUST make Radix Sort and Heap Sort differ by at least 60 seconds.

### Step 2: Run All Algorithms On Your Own Machine

```bash
# Radix Sort — all 10 sizes
./radix_sort dataset_1000.csv
./radix_sort dataset_10000.csv
./radix_sort dataset_50000.csv
./radix_sort dataset_100000.csv
./radix_sort dataset_500000.csv
./radix_sort dataset_1000000.csv
./radix_sort dataset_5000000.csv
./radix_sort dataset_10000000.csv
./radix_sort dataset_50000000.csv
./radix_sort dataset_100000000.csv

# Heap Sort — all 10 sizes
./heap_sort dataset_1000.csv
./heap_sort dataset_10000.csv
./heap_sort dataset_50000.csv
./heap_sort dataset_100000.csv
./heap_sort dataset_500000.csv
./heap_sort dataset_1000000.csv
./heap_sort dataset_5000000.csv
./heap_sort dataset_10000000.csv
./heap_sort dataset_50000000.csv
./heap_sort dataset_100000000.csv

# Hash Table Search — all 10 sizes
./hash_table_search dataset_1000.csv
./hash_table_search dataset_10000.csv
./hash_table_search dataset_50000.csv
./hash_table_search dataset_100000.csv
./hash_table_search dataset_500000.csv
./hash_table_search dataset_1000000.csv
./hash_table_search dataset_5000000.csv
./hash_table_search dataset_10000000.csv
./hash_table_search dataset_50000000.csv
./hash_table_search dataset_100000000.csv
```

### Step 3: Record Results

For each run, **take a screenshot** of the command prompt showing:
- The command you typed
- The running time output

Create a results table like this:

| Input Size | Radix Sort (s) | Heap Sort (s) | Hash Search Best (s) | Hash Search Avg (s) | Hash Search Worst (s) |
|-----------|---------------|--------------|--------------------|--------------------|--------------------|
| 1,000 | ? | ? | ? | ? | ? |
| 10,000 | ? | ? | ? | ? | ? |
| ... | ... | ... | ... | ... | ... |
| 100,000,000 | ? | ? | ? | ? | ? |

### Step 4: Create Charts

Use Excel or Google Sheets to create:
1. **Line chart**: Input size (x-axis) vs Running time in seconds (y-axis) — both sorts on same graph
2. **Bar chart**: Hash table search best/average/worst times

Put these in your Q7 section of the report.

---

## 📸 Screenshots You Need (Everyone)

1. **Hardware specs** of your own PC:
   - Windows: Press `Win + Pause` or search "About your PC"
   - Mac: Apple menu → About This Mac
   - Linux: Run `lscpu` and `free -h`

2. **Running time screenshots** for every input size and every algorithm (30 screenshots total = 10 sizes × 3 algorithms)

---

## 🤝 Q5 Conclusion — All Members Collaborate

This section must cover:

1. **Findings**: Compare Radix Sort vs Heap Sort on the same hardware
   - Which was faster? By how much at each size?
   - Did the time difference grow with input size?

2. **Best sorting algorithm**: Which is better for array-based implementation and why?
   - Consider time complexity, space complexity, and stability

3. **AVL Comparison (theory only — no code needed)**:
   - Compare **Hash Table Search** vs **Array-based AVL BST** vs **Linked-list-based AVL BST**
   - Compare for: Search, Insert, Delete operations
   - Cover: Time complexity (best, average, worst) and Space complexity

---

## ⚠️ Important Rules

1. **No built-in sort/search** — all algorithms are implemented from scratch ✅
2. **Running time excludes I/O** — timer starts after reading, stops before writing ✅
3. **10+ input sizes** per algorithm ✅
4. **Task percentage = 100%** for every member — everyone must understand all code
5. **Zero mark** if absent from interview or caught plagiarizing

---

## 📅 Suggested Timeline

| Date | Milestone |
|------|-----------|
| **Now** | Clone repo, compile, verify your assigned code works |
| **+3 days** | Member A: finalize dataset generator, generate all 10 datasets, share files |
| **+1 week** | Everyone: run all experiments on your own PC, take screenshots |
| **+1.5 weeks** | Everyone: write your assigned report section (Q1–Q4) |
| **+2 weeks** | All: collaborate on Q5 (Conclusion + AVL comparison) |
| **+2.5 weeks** | Member A: compile final report, upload to OneDrive, submit zip |
| **Week 13** | Practice demo, prepare for interview |

---

## 🆘 Troubleshooting

| Problem | Solution |
|---------|----------|
| `g++: command not found` | Install g++ (see Setup section above) |
| `make: command not found` | Install `make` via your package manager |
| Compilation error in my file | Read the error message, fix the code, push to GitHub |
| Program runs out of memory (large datasets) | Normal for 100M elements — use a smaller max size |
| Running times too close (< 60s difference) | Increase the largest dataset size |
| Git push rejected | `git pull` first, resolve conflicts, then `git push` |

---

## 📞 Contact

If you're stuck, message the group chat. If your assigned code has issues you can't fix, push what you have and tag the group leader for help.
