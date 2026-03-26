#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
/*
Why not use just a map?
A map can tell you whether a key exists, but it does not maintain LRU order.
mp[key]

Why not use just a linked list?
A linked list can store order, but searching for a key would be slow.
Node *next, *prev;

map for fast lookup
linked list for fast reordering

key structures:
map: key → node
doubly linked list: usage order
head: most recently used
tail: least recently used

Operations:
get → if found, move to head
set existing → update + move to head
set new → if full, remove tail; then insert at head
*/


struct Node {
    int key, value;
    Node *next, *prev;
    Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
};

class Cache {
    //abstract base class
protected:
    map<int, Node*> mp;
    int cp;
    Node *head, *tail;
public:
    Cache(int capacity) : cp(capacity), head(nullptr), tail(nullptr) {}
    virtual void set(int key, int value) = 0;
    virtual int get(int key) = 0;
    // = 0 means these are pure virtual. So you cannot do Cache c(5);   // not allowed
    virtual ~Cache() {}
};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) : Cache(capacity) {}

    void moveToHead(Node* node) {
        if (node == head) return; // If node is already the most recently used, do nothing

        // Unlink node from current pos
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == tail) tail = node->prev;

        // Move to front
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = head;
    }

    void set(int key, int value) override { // This is the insertion/update logic, override means this function is implementing the virtual function from the base class.
        // if key already exists, update val and move it to head
        if (mp.find(key) != mp.end()) {
            Node *node = mp[key];
            node->value = value;
            moveToHead(node);
        } else { // key is new, create a new node
            Node *node = new Node(key, value);

            if ((int)mp.size() == cp) { // If the cache already has cp items, we must evict one: The least recently used = tail
                mp.erase(tail->key); 
                if (tail->prev) { // If tail->prev exists:move tail backward, delete the old tail
                    tail = tail->prev;
                    delete tail->next;
                    tail->next = nullptr;
                } else { // if only one node in list, then removing it leaves an empty cache:
                    delete tail;
                    head = tail = nullptr;
                }
            }

            node->next = head;
            if (head) head->prev = node;
            head = node;
            if (!tail) tail = node;

            mp[key] = node;
        }
    }

    int get(int key) override {
        if (mp.find(key) == mp.end()) return -1;
        Node *node = mp[key];
        moveToHead(node);
        return node->value;
    }
};

int main() {
    int n, capacity;
    cin >> n >> capacity;

    LRUCache cache(capacity);

    for (int i = 0; i < n; i++) {
        // Each line is either: get key, set key value
        string command;
        cin >> command;

        if (command == "get") {
            int key;
            cin >> key;
            cout << cache.get(key) << "\n";
        } else if (command == "set") {
            int key, value;
            cin >> key >> value;
            cache.set(key, value);
        }
    }
    return 0;
}
