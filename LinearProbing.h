#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>


using namespace std;

struct _node {
    string key;
    pair<string, string> value; // Min Temp and Max Temp
    bool deleted; 

    _node(string key, string minTemp, string maxTemp) 
        : key(key), value(minTemp, maxTemp), deleted(false) {}
};

class linearHashMap {
private:
    vector<_node*> table; 
    int capacity; 
    int size = 0; 

    int hashFunction(const string& key) {
        hash<string> hashFunc;
        return hashFunc(key) % capacity; 
    }

    void rehash() {
        int newCapacity = capacity * 2;
        vector<_node*> newTable(newCapacity, nullptr); 

        for (_node* entry : table) {
            if (entry != nullptr && !entry -> deleted) {
                int index = hashFunction(entry->key); 
                while (newTable[index] != nullptr) {
                    index = (index + 1) % newCapacity; 
                }
                newTable[index] = new _node(entry->key, entry->value.first, entry->value.second);
            }

            delete entry; 
        }

        table = newTable; 
        capacity = newCapacity; 
    }

public:
    linearHashMap(int capacity) : capacity(capacity), table(capacity, nullptr) {}

    ~linearHashMap() {
        for (_node* entry : table)
            delete entry; 
    }

    void insert(const string& key, string minTemp, string maxTemp) {
        if (size >= 0.75 * capacity) {
            rehash(); 
        }

        int index = hashFunction(key);
        while (table[index] != nullptr && (!table[index]->deleted || table[index]->key != key)) {
            index = (index + 1) % capacity; 
        }

        if (table[index] != nullptr) {
            delete table[index]; 
        }

        table[index] = new _node(key, minTemp, maxTemp); 
        size++;
    }

    pair<string, string> find(const string& key) {
        int index = hashFunction(key);
        for (int i = 0; i < capacity; i++) {
            if (table[index] == nullptr) 
                return {"-1", "-1"}; 
            if (table[index]->key == key && !table[index] -> deleted)
                return table[index]->value; 
            
            index = (index + 1) % capacity; 
        }

        return {"nothing", "nothing"}; 
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        for (int i = 0; i < capacity; i++) {
            if (table[index] == nullptr) 
                return; 
            if (table[index]->key == key && !table[index]->deleted) {
                table[index]->deleted = true; 
                size--; 
                return; 
            }
            index = (index + 1) % capacity; 
        }
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                cout << "Index " << i << ": Key = " << table[i]->key
                    << ", Min Temp = " << table[i]->value.first
                    << ", Max Temp = " << table[i]->value.second
                    << ", Deleted = " << (table[i]->deleted ? "true" : "false")
                    << endl;
            } else {
                cout << "Index " << i << ": nullptr" << endl;
            }
        }
    }
};
