// *********************************************************
// Program: dataset_generator.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1: Dataset generator
// Member_2: Radix sort
// Member_3: Heap sort
// Member_4: Hash table search
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// Convert student ID letters to digits using the mapping:
// A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8 I=9
// J=0 K=1 L=2 M=3 N=4 O=5 P=6 Q=7 R=8 S=9
// T=0 U=1 V=2 W=3 X=4 Y=5 Z=6
unsigned long long studentIdToSeed(const string& id) {
    const int mapping[] = {1,2,3,4,5,6,7,8,9,0,  // A-I
                           1,2,3,4,5,6,7,8,9,0,  // J-S
                           1,2,3,4,5,6};          // T-Z
    string numStr;
    for (char c : id) {
        if (isdigit(c)) {
            numStr += c;
        } else if (isalpha(c)) {
            numStr += to_string(mapping[toupper(c) - 'A']);
        }
    }
    // Use modulo to fit into unsigned int if needed
    return stoull(numStr) % 4294967296ULL;
}

int main(int argc, char* argv[]) {
    // =====================================================
    // Input configuration (uncomment one line, comment rest)
    // =====================================================
    // long long n = 1000;
    // long long n = 10000;
    // long long n = 100000;
    // long long n = 500000;
    // long long n = 1000000;
    // long long n = 5000000;
    // long long n = 10000000;
    // long long n = 50000000;
    // long long n = 100000000;
    long long n = 0; // will be set from command line

    // Use command line argument if provided
    if (argc > 1) {
        n = atoll(argv[1]);
    }
    if (n <= 0) {
        cout << "Usage: dataset_generator <size>" << endl;
        cout << "Example: dataset_generator 1000000" << endl;
        return 1;
    }

    // =====================================================
    // Seed using group leader's student ID
    // Replace "YOUR_STUDENT_ID" with actual student ID
    // Example: "243UC247CT" -> seed 2431324730
    // =====================================================
    string studentId = "YOUR_STUDENT_ID"; // TODO: Replace with group leader's student ID

    // Seed is placed right after main as required
    unsigned long long seedValue = studentIdToSeed(studentId);
    mt19937_64 rng((unsigned int)seedValue);

    cout << "Generating dataset with " << n << " elements..." << endl;
    cout << "Seed: " << seedValue << endl;

    // =====================================================
    // Step 1: Generate unique random 10-digit integers
    // Using Fisher-Yates shuffle on sequential numbers
    // from a random starting point in valid range
    // =====================================================
    long long MIN_VAL = 1000000000LL;  // 1 billion (10 digits)
    long long MAX_VAL = 9999999999LL;  // ~10 billion (10 digits)
    long long RANGE = MAX_VAL - MIN_VAL + 1;

    // Choose a random starting point ensuring we have n numbers
    uniform_int_distribution<long long> startDist(0LL, RANGE - n);
    long long startOffset = startDist(rng);
    long long startVal = MIN_VAL + startOffset;

    // Fill sequential numbers
    vector<long long> numbers(n);
    for (long long i = 0; i < n; i++) {
        numbers[i] = startVal + i;
    }

    // Fisher-Yates shuffle for randomization
    for (long long i = n - 1; i > 0; i--) {
        uniform_int_distribution<long long> swapDist(0LL, i);
        long long j = swapDist(rng);
        swap(numbers[i], numbers[j]);
    }

    // =====================================================
    // Step 2: Generate random 5-letter strings and write CSV
    // Each string is 5 lowercase letters (a-z)
    // =====================================================
    uniform_int_distribution<int> charDist(0, 25);

    string filename = "dataset_" + to_string(n) + ".csv";
    ofstream out(filename);

    if (!out.is_open()) {
        cerr << "Error: Cannot create file " << filename << endl;
        return 1;
    }

    for (long long i = 0; i < n; i++) {
        string s(5, 'a');
        for (int j = 0; j < 5; j++) {
            s[j] = 'a' + charDist(rng);
        }
        out << numbers[i] << "," << s << "\n";
    }
    out.close();

    cout << "Generated " << filename << " with " << n << " unique elements." << endl;
    cout << "Integer range: " << startVal << " to " << (startVal + n - 1) << endl;

    return 0;
}
