// *********************************************************
// Program: hash_table_search.cpp
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

// =====================================================
// Hash Table Implementation using Separate Chaining
// =====================================================
//
// Hash Function: h(key) = key % tableSize
// Collision Resolution: Separate chaining (linked list per bucket)
//
// Time Complexity:
//   Best case:    O(1) - element found at direct hash position
//   Average case: O(1 + alpha) where alpha = n/tableSize (load factor)
//   Worst case:   O(n) - all elements in same chain
//
// Space Complexity: O(n + tableSize)

struct HashNode {
    Element data;
    HashNode* next;
    HashNode(Element e) : data(e), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;      // Array of bucket pointers
    long long tableSize;   // Number of buckets
    long long numElements; // Total elements stored

    // Simple hash function using modulo
    long long hash(long long key) {
        return ((key % tableSize) + tableSize) % tableSize; // ensure positive
    }

public:
    HashTable(long long size) {
        tableSize = size;
        numElements = 0;
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

    // Insert element into hash table
    void insert(const Element& e) {
        long long index = hash(e.id);
        HashNode* newNode = new HashNode(e);
        newNode->next = table[index];
        table[index] = newNode;
        numElements++;
    }

    // Search for element by integer key
    // Returns the element if found, or a sentinel {-1, ""} if not found
    // Also counts the number of comparisons made
    Element search(long long key, int& comparisons) {
        comparisons = 0;
        long long index = hash(key);
        HashNode* current = table[index];
        while (current != nullptr) {
            comparisons++;
            if (current->data.id == key) {
                return current->data;
            }
            current = current->next;
        }
        return {-1, ""};
    }

    // Get the chain length at a specific bucket
    long long getChainLength(long long index) {
        long long count = 0;
        HashNode* current = table[index];
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Find an element in a bucket with minimum chain length (best case)
    // Returns the key of such an element
    long long findBestCaseElement() {
        for (long long i = 0; i < tableSize; i++) {
            if (table[i] != nullptr && table[i]->next == nullptr) {
                return table[i]->data.id; // Chain length 1 = direct hit
            }
        }
        // Fallback: return first element
        return table[0]->data.id;
    }

    // Find an element in the bucket with maximum chain length (worst case)
    // Returns the key of the LAST element in the longest chain
    long long findWorstCaseElement() {
        long long maxLen = 0;
        long long worstIndex = 0;
        for (long long i = 0; i < tableSize; i++) {
            long long len = getChainLength(i);
            if (len > maxLen) {
                maxLen = len;
                worstIndex = i;
            }
        }
        // Traverse to the last element in this chain
        HashNode* current = table[worstIndex];
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data.id;
    }

    long long getTableSize() { return tableSize; }
    long long getNumElements() { return numElements; }
};

// Check if a number is prime
bool isPrime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Find next prime >= n
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
    // string inputFile = "dataset_10000.csv";
    // string inputFile = "dataset_100000.csv";
    // string inputFile = "dataset_1000000.csv";
    // string inputFile = "dataset_10000000.csv";
    string inputFile = "";

    if (argc > 1) {
        inputFile = argv[1];
    }
    if (inputFile.empty()) {
        cout << "Usage: hash_table_search <dataset_file.csv>" << endl;
        return 1;
    }

    // Step 1: Read dataset (I/O time NOT counted)
    cout << "Reading " << inputFile << "..." << endl;
    vector<Element> data = readDataset(inputFile);
    if (data.empty()) {
        cerr << "Error: No data read from file." << endl;
        return 1;
    }
    long long n = data.size();
    cout << "Read " << n << " elements." << endl;

    // Step 2: Build hash table (build time NOT counted as search time)
    // Use a prime number close to n for good distribution
    long long tableSize = nextPrime(n);
    cout << "Building hash table with " << tableSize << " buckets..." << endl;

    HashTable ht(tableSize);
    for (const auto& e : data) {
        ht.insert(e);
    }

    // Step 3: Measure search times (excluding I/O and table building)
    // Perform n searches for each case as the assignment requires

    // --- BEST CASE: Search for an element with direct hit (chain length 1) ---
    long long bestKey = ht.findBestCaseElement();
    auto startTime = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        int cmp;
        ht.search(bestKey, cmp);
    }
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> bestTime = (endTime - startTime) / (double)n;

    // --- AVERAGE CASE: Search for each element once ---
    startTime = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        int cmp;
        ht.search(data[i].id, cmp);
    }
    endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> avgTime = (endTime - startTime) / (double)n;

    // --- WORST CASE: Search for element in longest chain ---
    long long worstKey = ht.findWorstCaseElement();
    startTime = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        int cmp;
        ht.search(worstKey, cmp);
    }
    endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> worstTime = (endTime - startTime) / (double)n;

    // Extract size string from filename
    string sizeStr;
    for (size_t i = 0; i < inputFile.size(); i++) {
        if (isdigit(inputFile[i])) sizeStr += inputFile[i];
    }

    // Step 4: Output results
    string outputFile = "hash_table_search_dataset_" + sizeStr + ".txt";
    ofstream out(outputFile);

    // Print to both console and file
    cout << "\n===== Hash Table Search Results =====" << endl;
    cout << "Dataset size: " << n << endl;
    cout << "Table size (prime): " << tableSize << endl;
    cout << "Load factor: " << fixed << (double)n / tableSize << endl;
    cout << "Best case time:   " << bestTime.count() << " seconds" << endl;
    cout << "Average case time: " << avgTime.count() << " seconds" << endl;
    cout << "Worst case time:  " << worstTime.count() << " seconds" << endl;

    out << "Best case time: " << bestTime.count() << " seconds" << endl;
    out << "Average case time: " << avgTime.count() << " seconds" << endl;
    out << "Worst case time: " << worstTime.count() << " seconds" << endl;
    out.close();

    cout << "Output: " << outputFile << endl;

    return 0;
}
