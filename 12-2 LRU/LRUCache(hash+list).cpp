#include <unordered_map>

// 1. 定义双向链表节点
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    
    Node() : key(0), value(0), prev(nullptr), next(nullptr) {}
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int size;
    
    // 使用哈希表存储 Key -> Node指针 的映射
    std::unordered_map<int, Node*> cache;
    
    // 伪头部和伪尾部，简化边界判断（不用担心 head 是空的情况）
    Node* head;
    Node* tail;

    // --- 核心：手写链表操作 ---

    // 作用：把一个节点从当前位置“抠”出来
    // 相当于 std::list 的 erase 或 remove，但不释放内存
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 作用：把一个孤立节点插到头部（head 之后）
    // 相当于 std::list 的 push_front
    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 作用：组合技，将一个已存在的节点移动到头部
    // 这就是原本 splice 干的事情
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    // 作用：移除并返回尾部节点（用于内存释放和 Map 删除）
    // 相当于 std::list 的 pop_back
    Node* removeTail() {
        Node* node = tail->prev; // 伪尾部的前一个才是真正的尾部
        removeNode(node);
        return node;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        
        // 初始化伪头和伪尾，并连接起来
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    // 析构函数释放内存
    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr->next;
            delete curr;
            curr = temp;
        }
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        // 找到了，通过 Map 直接拿到节点指针
        Node* node = cache[key];
        
        // 【手动操作】把它移到最前面，标记为最近使用
        moveToHead(node);
        
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // --- Key 已存在 ---
            Node* node = cache[key];
            node->value = value; // 更新值
            moveToHead(node);    // 移到头部
        } else {
            // --- Key 不存在 ---
            // 创建新节点
            Node* newNode = new Node(key, value);
            
            // 存入 Map 和 链表
            cache[key] = newNode;
            addToHead(newNode); // 新来的放头部
            size++;
            
            // 检查容量
            if (size > capacity) {
                // 1. 去掉链表尾部最旧的节点
                Node* removed = removeTail();
                // 2. 去掉 Map 里的映射
                cache.erase(removed->key);
                // 3. 释放内存
                delete removed;
                size--;
            }
        }
    }
};