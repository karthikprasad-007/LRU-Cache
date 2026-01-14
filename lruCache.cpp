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

        int get(int key) {
           if(mp.find(key)==mp.end()) return -1;
           Node* node = mp[key]; 
           remove(node);
           insertFront(node);
           return node->value;
        }

        void put(int key, int value) {
            if(mp.find(key)!=mp.end()) {
                Node* node = mp[key];
                node->value = value;
                remove(node);
                insertFront(node);
            } else {
                if(mp.size()==capacity) {
                    Node* lru = tail->prev;
                    remove(lru);
                    mp.erase(key);
                    delete lru;
                }
                Node* node = new Node(key, value);
                mp[key] = node;
                insertFront(node);
            }
        }

        void display() {
            Node* curr = head->next;
            std::cout << "Cache (MRU - LRU)\n";
            while(curr!=tail) {
                std::cout << "[" << curr->key << ":" << curr->value << "] ";
                curr = curr->next;
            }
            std::cout << std::endl;
        }
};

int main () {

    LRUCache cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.display();

    cache.get(1);
    cache.display();

    cache.put(3, 30);
    cache.get(2);
    cache.display();

    cache.put(4, 40);
    cache.display();

    return 0;
}