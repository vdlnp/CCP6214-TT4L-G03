// *********************************************************
// Program: radix_sort.cpp
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
#include <chrono>

using namespace std;

struct Element {
    long long id;
    string name;
};

// Read dataset from CSV file
vector<Element> readDataset(const string& filename) {
    vector<Element> data;
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return data;
    }
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(',');
        if (pos == string::npos) continue;
        Element e;
        e.id = stoll(line.substr(0, pos));
        e.name = line.substr(pos + 1);
        while (!e.name.empty() && (e.name.back() == '\r' || e.name.back() == '\n' || e.name.back() == ' '))
            e.name.pop_back();
        data.push_back(e);
    }
    in.close();
    return data;
}

// Write sorted elements to file (format: integer/string)
void writeSorted(const string& filename, const vector<Element>& data) {
    ofstream out(filename);
    for (const auto& e : data) {
        out << e.id << "/" << e.name << "\n";
    }
    out.close();
}

// LSD Radix Sort using Counting Sort as stable sub-routine
// Processes from the rightmost digit (d=10) to the leftmost (d=1)
// For a 10-digit integer, each digit is in range [0, 9]
//
// Time Complexity:  O(d * (n + k)) where d=10 digits, k=10 possible values
// Space Complexity: O(n + k) for the counting array and output array
void radixSort(vector<Element>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    long long exp = 1; // Start from rightmost digit (ones place)

    // 10 passes for 10 digits (d=10, d=9, ..., d=1)
    for (int d = 10; d >= 1; d--) {
        // Counting sort based on current digit
        int count[10] = {0};

        // Count occurrences of each digit (0-9)
        for (int i = 0; i < n; i++) {
            int digit = (arr[i].id / exp) % 10;
            count[digit]++;
        }

        // Convert to cumulative count (positions)
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build output array (traverse in reverse for stability)
        vector<Element> output(n);
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i].id / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Copy output back to array
        arr = output;

        exp *= 10; // Move to next digit position
    }
}

int main(int argc, char* argv[]) {
    // =====================================================
    // Input configuration (uncomment one, comment rest)
    // =====================================================
    // string inputFile = "dataset_1000.csv";
    // string inputFile = "dataset_10000.csv";
    // string inputFile = "dataset_100000.csv";
    // string inputFile = "dataset_1000000.csv";
    // string inputFile = "dataset_10000000.csv";
    // string inputFile = "dataset_50000000.csv";
    // string inputFile = "dataset_100000000.csv";
    string inputFile = "";

    if (argc > 1) {
        inputFile = argv[1];
    }
    if (inputFile.empty()) {
        cout << "Usage: radix_sort <dataset_file.csv>" << endl;
        return 1;
    }

    // Step 1: Read dataset (I/O time NOT counted)
    cout << "Reading " << inputFile << "..." << endl;
    vector<Element> data = readDataset(inputFile);
    if (data.empty()) {
        cerr << "Error: No data read from file." << endl;
        return 1;
    }
    cout << "Read " << data.size() << " elements." << endl;

    // Step 2: Sort and measure running time (excluding I/O)
    auto startTime = chrono::high_resolution_clock::now();

    radixSort(data);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // Step 3: Write output (I/O time NOT counted)
    // Extract n from filename: dataset_n.csv -> n
    string sizeStr;
    for (size_t i = 0; i < inputFile.size(); i++) {
        if (isdigit(inputFile[i])) {
            sizeStr += inputFile[i];
        }
    }
    string outputFile = "radix_sorted_dataset_" + sizeStr + ".csv";

    writeSorted(outputFile, data);

    // Print running time to console and output file
    cout << "Radix Sort completed." << endl;
    cout << "Running time: " << elapsed.count() << " seconds" << endl;
    cout << "Output: " << outputFile << endl;

    // Write running time to a separate result file
    ofstream timeFile("radix_sort_time_" + sizeStr + ".txt");
    timeFile << "Input: " << inputFile << endl;
    timeFile << "Algorithm: LSD Radix Sort (rightmost digit first)" << endl;
    timeFile << "Dataset size: " << data.size() << endl;
    timeFile << "Running time: " << elapsed.count() << " seconds" << endl;
    timeFile.close();

    return 0;
}
