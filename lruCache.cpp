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

        int capacity;
        unordered_map<int, Node*> mp;

        Node* head;
        Node* tail;

        void remove(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } 


};

int main () {}