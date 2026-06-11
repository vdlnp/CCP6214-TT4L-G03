// *********************************************************
// Program: radix_sort_step.cpp
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

// Print array in step format: [int/str, int/str, ...] label
void printStep(ofstream& out, const vector<Element>& arr, const string& label) {
    out << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i > 0) out << ", ";
        out << arr[i].id << "/" << arr[i].name;
    }
    out << "] " << label << "\n";
}

// LSD Radix Sort with step-by-step output
// Shows the array after each digit pass
void radixSortWithSteps(vector<Element>& arr, ofstream& out) {
    int n = arr.size();
    if (n <= 0) return;

    // Print original array
    printStep(out, arr, "original");

    long long exp = 1; // Start from rightmost digit (ones place)

    // 10 passes for 10 digits: d=10 (ones) to d=1 (billions)
    for (int d = 10; d >= 1; d--) {
        int count[10] = {0};

        // Count occurrences of each digit
        for (int i = 0; i < n; i++) {
            int digit = (arr[i].id / exp) % 10;
            count[digit]++;
        }

        // Cumulative count
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build output (reverse for stability)
        vector<Element> output(n);
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i].id / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        arr = output;

        // Print array after this digit pass
        printStep(out, arr, "d=" + to_string(d));

        exp *= 10;
    }
}

int main(int argc, char* argv[]) {
    // =====================================================
    // Input configuration (uncomment one, comment rest)
    // =====================================================
    // string inputFile = "dataset_1000.csv";
    // int startRow = 1;
    // int endRow = 7;
    string inputFile = "";
    int startRow = 0;
    int endRow = 0;

    if (argc > 3) {
        inputFile = argv[1];
        startRow = atoi(argv[2]);
        endRow = atoi(argv[3]);
    }
    if (inputFile.empty() || startRow <= 0 || endRow <= 0) {
        cout << "Usage: radix_sort_step <dataset_file.csv> <start_row> <end_row>" << endl;
        cout << "Example: radix_sort_step dataset_1000.csv 1 7" << endl;
        return 1;
    }

    // Read full dataset
    cout << "Reading " << inputFile << "..." << endl;
    vector<Element> data = readDataset(inputFile);
    if (data.empty()) {
        cerr << "Error: No data read." << endl;
        return 1;
    }
    cout << "Read " << data.size() << " elements." << endl;

    // Extract subset from startRow to endRow (1-indexed)
    int start = startRow - 1; // Convert to 0-indexed
    int end = endRow - 1;
    if (start < 0) start = 0;
    if (end >= (int)data.size()) end = (int)data.size() - 1;

    vector<Element> subset(data.begin() + start, data.begin() + end + 1);
    cout << "Sorting rows " << startRow << " to " << endRow << " (" << subset.size() << " elements)." << endl;

    // Extract size string from filename
    string sizeStr;
    for (size_t i = 0; i < inputFile.size(); i++) {
        if (isdigit(inputFile[i])) sizeStr += inputFile[i];
    }

    string outputFile = "dataset_" + sizeStr + "_radix_sorted_step_" +
                        to_string(startRow) + "_" + to_string(endRow) + ".txt";
    ofstream out(outputFile);

    if (!out.is_open()) {
        cerr << "Error: Cannot create output file." << endl;
        return 1;
    }

    // Perform radix sort with steps
    radixSortWithSteps(subset, out);

    out.close();
    cout << "Steps written to " << outputFile << endl;

    return 0;
}
