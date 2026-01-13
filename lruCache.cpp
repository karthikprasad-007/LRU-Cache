#include <iostream>
#include <unordered_map>

class LRUCache {
    private:
        struct Node {
            int key, value;
            Node* prev;
            Node* next;

            Node(int k, int v) {
                key = k;
                v = value;
                prev = NULL;
                next = NULL;
            }
        }
};

int main () {}