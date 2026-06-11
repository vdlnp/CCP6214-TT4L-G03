// *********************************************************
// Program: heap_sort.cpp
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

// Heapify: maintain max-heap property at index i
// n is the heap size
//
// Time Complexity: O(log n)
void heapify(vector<Element>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare with left child
    if (left < n && arr[left].id > arr[largest].id) {
        largest = left;
    }

    // Compare with right child
    if (right < n && arr[right].id > arr[largest].id) {
        largest = right;
    }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Build max heap from unordered array
// Start from last non-leaf node and heapify each
//
// Time Complexity: O(n)
void buildMaxHeap(vector<Element>& arr) {
    int n = arr.size();
    // Last non-leaf node is at index (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Heap Sort using Max Heap
//
// Algorithm:
// 1. Build a max heap from the input array
// 2. Repeatedly extract the maximum element:
//    a. Swap root (max) with last unsorted element
//    b. Reduce heap size by 1
//    c. Heapify the new root
//
// Time Complexity:  O(n log n) - all cases
// Space Complexity: O(1) - in-place sorting (not counting input)
void heapSort(vector<Element>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Step 1: Build max heap
    buildMaxHeap(arr);

    // Step 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to end
        swap(arr[0], arr[i]);

        // Heapify the reduced heap
        heapify(arr, i, 0);
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
        cout << "Usage: heap_sort <dataset_file.csv>" << endl;
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

    heapSort(data);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // Step 3: Write output (I/O time NOT counted)
    // Extract n from filename
    string sizeStr;
    for (size_t i = 0; i < inputFile.size(); i++) {
        if (isdigit(inputFile[i])) sizeStr += inputFile[i];
    }
    string outputFile = "heap_sorted_dataset_" + sizeStr + ".csv";

    writeSorted(outputFile, data);

    // Print running time
    cout << "Heap Sort completed." << endl;
    cout << "Running time: " << elapsed.count() << " seconds" << endl;
    cout << "Output: " << outputFile << endl;

    // Write running time to a separate result file
    ofstream timeFile("heap_sort_time_" + sizeStr + ".txt");
    timeFile << "Input: " << inputFile << endl;
    timeFile << "Algorithm: Heap Sort (Max Heap)" << endl;
    timeFile << "Dataset size: " << data.size() << endl;
    timeFile << "Running time: " << elapsed.count() << " seconds" << endl;
    timeFile.close();

    return 0;
}
