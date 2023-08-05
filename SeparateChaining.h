#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct node {
    string key;
    pair<string, string> value; // Precipitation and Wind Speed
    node* next;

    node(string key, string precipitation, string windSpeed)
        : key(key), value(precipitation, windSpeed), next(nullptr) {}
};


class chainingHashMap {
private:
    vector<node*> buckets;
    int capacity;

    int hashFunction(const string& key) {
        hash<string> hashFunc;
        return hashFunc(key) % capacity;
    }

public:
    chainingHashMap(int capacity) : capacity(capacity), buckets(capacity, nullptr) {}

    ~chainingHashMap() {
        for (node* head : buckets) {
            while (head) {
                node* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }

    void insert(const string& key, string precipitation, string windSpeed) {
        int index = hashFunction(key);
        node* newNode = new node(key, precipitation, windSpeed);

        if (buckets[index] == nullptr) {
            buckets[index] = newNode;
        } else {
            node* current = buckets[index];
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        node* currentNode = buckets[index];
        node* prev = nullptr;

        while (currentNode != nullptr && currentNode->key != key) {
            prev = currentNode;
            currentNode = currentNode->next;
        }

        if (currentNode == nullptr) return; // Key not found

        if (prev != nullptr) {
            prev->next = currentNode->next;
        } else {
            buckets[index] = currentNode->next; // Set the next node as the new head
        }

        delete currentNode;
    }

    pair<string, string> find(const string& key) {
        int index = hashFunction(key);
        node* currentNode = buckets[index];

        while (currentNode != nullptr) {
            if (currentNode->key == key) {
                return currentNode->value;
            }
            currentNode = currentNode->next;
        }

        return {"-1.0", "-1.0"}; // Return error values if not found
    }
};


