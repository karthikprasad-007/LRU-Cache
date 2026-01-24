#include <iostream>
#include <unordered_map>

//Class -> Contains constructor, functions for LRUCache
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

        //Remove LRU from DLL
        void remove(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } 

        //Insert in DLL
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

        //put and get uses map
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
    int capacity;
    std::cout << "=== LRU Cache Manager ===" << std::endl;
    std::cout << "Enter cache capacity: ";
    std::cin >> capacity;
    
    LRUCache cache(capacity);
    int choice;
    
    while(true) {
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. PUT (Insert/Update)" << std::endl;
        std::cout << "2. GET (Retrieve)" << std::endl;
        std::cout << "3. DISPLAY Cache" << std::endl;
        std::cout << "4. EXIT" << std::endl;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                int key, value;
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cout << "Enter value: ";
                std::cin >> value;
                cache.put(key, value);
                std::cout << "✓ Added/Updated key " << key << " with value " << value << std::endl;
                break;
            }
            case 2: {
                int key;
                std::cout << "Enter key to retrieve: ";
                std::cin >> key;
                int result = cache.get(key);
                if(result == -1) {
                    std::cout << "✗ Key " << key << " not found in cache!" << std::endl;
                } else {
                    std::cout << "✓ Value for key " << key << ": " << result << std::endl;
                }
                break;
            }
            case 3: {
                cache.display();
                break;
            }
            case 4: {
                std::cout << "Exiting... Thank you!" << std::endl;
                return 0;
            }
            default:
                std::cout << "✗ Invalid choice! Please enter 1-4." << std::endl;
        }
    }

    return 0;
}