#include <iostream>
#include <vector>
#include <string>

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::vector<std::pair<std::string, int>>> table;

    static int hashFunction(const std::string& key) {
        // Hash function: sum of ASCII values mod table size
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const std::string& key, int value) {
        int index = hashFunction(key);
        // Check if the key already exists, and update if found
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        // Otherwise, add the new key-value pair
        table[index].emplace_back(key, value);
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                std::cout << "Key \"" << key << "\" removed.\n";
                return;
            }
        }
        std::cout << "Key \"" << key << "\" not found.\n";
    }

    void search(const std::string& key) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                std::cout << "Key \"" << key << "\" found with value: " << pair.second << "\n";
                return;
            }
        }
        std::cout << "Key \"" << key << "\" not found.\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Index " << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    HashTable hashTable;

    hashTable.insert("Alice", 1234);
    hashTable.insert("Bob", 5678);
    hashTable.insert("Charlie", 9101);
    hashTable.insert("Alice", 1111); // Updates value for "Alice"

    std::cout << "Hash Table after insertions:\n";
    hashTable.display();

    hashTable.search("Bob");
    hashTable.search("Dan");

    hashTable.remove("Alice");
    hashTable.remove("Eve");

    std::cout << "Hash Table after deletions:\n";
    hashTable.display();

    return 0;
}