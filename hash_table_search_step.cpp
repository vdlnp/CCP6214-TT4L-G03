// *********************************************************
// Program: hash_table_search_step.cpp
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

// =====================================================
// Hash Table with Separate Chaining for Search Steps
// =====================================================

struct HashNode {
    Element data;
    HashNode* next;
    HashNode(Element e) : data(e), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    long long tableSize;

    long long hash(long long key) {
        return ((key % tableSize) + tableSize) % tableSize;
    }

public:
    HashTable(long long size) {
        tableSize = size;
        table = new HashNode*[tableSize];
        for (long long i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (long long i = 0; i < tableSize; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(const Element& e) {
        long long index = hash(e.id);
        HashNode* newNode = new HashNode(e);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Search with step-by-step output
    // Each comparison in the chain is written to the output file
    // Found format:    element_int = element_int/element_str
    // Not match:       element_int != target_int
    // End of chain:    -1 != target_int
    void searchWithSteps(long long target, ofstream& out) {
        long long index = hash(target);
        HashNode* current = table[index];

        // Print hash index info
        out << "Hash index: " << index << endl;

        if (current == nullptr) {
            // Empty bucket - not found immediately
            out << "-1 != " << target << endl;
            return;
        }

        // Traverse the chain
        while (current != nullptr) {
            if (current->data.id == target) {
                // Found!
                out << current->data.id << " = " << current->data.id << "/" << current->data.name << endl;
                return;
            } else {
                // Not a match - show comparison
                out << current->data.id << " != " << target << endl;
            }
            current = current->next;
        }

        // Reached end of chain without finding
        out << "-1 != " << target << endl;
    }
};

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long long nextPrime(long long n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) n++;
    while (!isPrime(n)) n += 2;
    return n;
}

int main(int argc, char* argv[]) {
    // =====================================================
    // Input configuration (uncomment one, comment rest)
    // =====================================================
    // string inputFile = "dataset_1000.csv";
    // long long foundTarget = 1000000038;    // a key that exists in dataset
    // long long notFoundTarget = 123456789;  // a key that does NOT exist
    string inputFile = "";
    long long foundTarget = 0;
    long long notFoundTarget = 0;

    if (argc > 3) {
        inputFile = argv[1];
        foundTarget = atoll(argv[2]);
        notFoundTarget = atoll(argv[3]);
    }
    if (inputFile.empty() || foundTarget == 0) {
        cout << "Usage: hash_table_search_step <dataset_file.csv> <found_target> <not_found_target>" << endl;
        cout << "Example: hash_table_search_step dataset_1000.csv 1000000038 123456789" << endl;
        return 1;
    }

    // Read dataset
    cout << "Reading " << inputFile << "..." << endl;
    vector<Element> data = readDataset(inputFile);
    if (data.empty()) {
        cerr << "Error: No data read." << endl;
        return 1;
    }
    long long n = data.size();
    cout << "Read " << n << " elements." << endl;

    // Build hash table
    long long tableSize = nextPrime(n);
    cout << "Building hash table with " << tableSize << " buckets..." << endl;
    HashTable ht(tableSize);
    for (const auto& e : data) {
        ht.insert(e);
    }

    // Extract size string from filename
    string sizeStr;
    for (size_t i = 0; i < inputFile.size(); i++) {
        if (isdigit(inputFile[i])) sizeStr += inputFile[i];
    }

    // --- Search for FOUND target ---
    string foundFile = "dataset_" + sizeStr + "_hash_table_search_step_" + to_string(foundTarget) + ".txt";
    ofstream foundOut(foundFile);
    if (foundOut.is_open()) {
        cout << "\n--- Searching for FOUND target: " << foundTarget << " ---" << endl;
        foundOut << "Search for target: " << foundTarget << " (found)" << endl;
        ht.searchWithSteps(foundTarget, foundOut);
        foundOut.close();
        cout << "Output: " << foundFile << endl;
    }

    // --- Search for NOT-FOUND target ---
    string notFoundFile = "dataset_" + sizeStr + "_hash_table_search_step_" + to_string(notFoundTarget) + ".txt";
    ofstream notFoundOut(notFoundFile);
    if (notFoundOut.is_open()) {
        cout << "\n--- Searching for NOT-FOUND target: " << notFoundTarget << " ---" << endl;
        notFoundOut << "Search for target: " << notFoundTarget << " (not found)" << endl;
        ht.searchWithSteps(notFoundTarget, notFoundOut);
        notFoundOut.close();
        cout << "Output: " << notFoundFile << endl;
    }

    return 0;
}
