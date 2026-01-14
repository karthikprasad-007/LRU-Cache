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
                value = v;
                prev = NULL;
                next = NULL;
            }
        };

        int capacity;
        std::unordered_map<int, Node*> mp;

        Node* head;
        Node* tail;

        void remove(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } 

        void insertFront(Node* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
        }
    public:
        LRUCache(int cap) {
            capacity = cap;
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head->next = tail;
            tail->prev = head;
        }



        
};

int main () {}