# CCP6214-TT4L-G03

Algorithm Design & Analysis — Assignment (40 marks)

## Group Info
- **Lecture Section:** TC1L
- **Tutorial Section:** TT4L
- **Group Number:** G03
- **Group ID:** TT4L_G03

## Folder Structure
```
CCP6214-TT4L-G03/
├── code/                  ← All source code
│   ├── dataset_generator.cpp
│   ├── radix_sort.cpp
│   ├── radix_sort_step.cpp
│   ├── heap_sort.cpp
│   ├── heap_sort_step.cpp
│   ├── hash_table_search.cpp
│   ├── hash_table_search_step.cpp
│   ├── common.h
│   └── Makefile
├── datasets/              ← Generated dataset CSV files
├── output/                ← Sorted output + step files
├── screenshots/           ← Running time screenshots
│   ├── member_a/
│   ├── member_b/
│   ├── member_c/
│   └── member_d/
└── README.md
```

## Setup
```bash
git clone https://github.com/YOUR_USERNAME/CCP6214-TT4L-G03.git
cd CCP6214-TT4L-G03/code
make all
```

## Members
| # | Name | Student ID | Assigned |
|---|------|-----------|----------|
| 1 | ? | ? | Dataset Generator + Report Assembly |
| 2 | ? | ? | Radix Sort |
| 3 | ? | ? | Heap Sort |
| 4 | ? | ? | Hash Table Search |


## Task Distribution
👤 MEMBER A (Leader) - @tag

Code:
• dataset_generator.cpp

Report:
• Q1 - Dataset Generation
• Cover page, TOC, References
• Final document assembly & submission

To do:
1. Replace "YOUR_STUDENT_ID" in dataset_generator.cpp with your student ID
2. Test it works: ./dataset_generator 1000
3. Generate all 10 dataset sizes (1K to 100M)
4. Share dataset files with everyone
5. Write Q1 in report

Demo: Present dataset generator

━━━━━━━━━━━━━━━━━━━━

👤 MEMBER B - @tag

Code:
• radix_sort.cpp
• radix_sort_step.cpp

Report:
• Q2 - Radix Sort

To do:
1. Review and understand both files
2. Test: ./radix_sort dataset_1000.csv
3. Test steps: ./radix_sort_step dataset_1000.csv 1 7
4. Fix any bugs, push to GitHub
5. Write Q2 in report (complexity analysis + code explanation + charts)

Demo: Present radix sort

━━━━━━━━━━━━━━━━━━━━

👤 MEMBER C - @tag

Code:
• heap_sort.cpp
• heap_sort_step.cpp

Report:
• Q3 - Heap Sort

To do:
1. Review and understand both files
2. Test: ./heap_sort dataset_1000.csv
3. Test steps: ./heap_sort_step dataset_1000.csv 1 7
4. Fix any bugs, push to GitHub
5. Write Q3 in report (complexity analysis + code explanation + charts)

Demo: Present heap sort

━━━━━━━━━━━━━━━━━━━━

👤 MEMBER D - @tag

Code:
• hash_table_search.cpp
• hash_table_search_step.cpp

Report:
• Q4 - Hash Table Search

To do:
1. Review and understand both files
2. Test: ./hash_table_search dataset_1000.csv
3. Test steps: ./hash_table_search_step dataset_1000.csv <found_target> 123456789
4. Fix any bugs, push to GitHub
5. Write Q4 in report (complexity analysis + code explanation + charts)

Demo: Present hash table search

━━━━━━━━━━━━━━━━━━━━

👥 EVERYONE must do:

1. Run ALL 3 algorithms on 10 input sizes on YOUR OWN PC
2. Screenshot every running time
3. Screenshot your PC hardware specs
4. Fill in Q7 (experiments) with your own results + charts
5. Be ready to explain ALL code at interview (not just your part)
6. Help with Q5 (conclusion + AVL comparison) — we do this together

━━━━━━━━━━━━━━━━━━━━
