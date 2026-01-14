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

        void display(Node* head) {
            Node* temp = head;
            while(temp->next == NULL) temp = temp->next;
        }
        
};

int main () {}