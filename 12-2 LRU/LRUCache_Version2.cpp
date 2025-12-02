#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity; // 缓存容量
    // 双向链表存储 (key, value) 对。
    // 我们需要存储 key，这样当从链表尾部删除节点时，也能通过 key 从哈希表中删除对应的映射。
    std::list<std::pair<int, int>> cacheList;
    // 哈希表存储 key 到 链表迭代器 的映射，实现 O(1) 查找。
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        // 如果 key 不在哈希表中，直接返回 -1
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }
        
        // key 存在。我们需要将这个节点移动到链表头部（标记为最近使用）。
        // std::list::splice 可以将元素从一个位置转移到另一个位置，时间复杂度为 O(1)。
        // 语法: list.splice(目标位置, 源列表, 源元素迭代器)
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        
        // 返回该节点的值
        return cacheMap[key]->second;
    }
    
    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // 情况 1: Key 已经存在
            // 更新 value
            cacheMap[key]->second = value;
            // 将该节点移动到链表头部
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        } else {
            // 情况 2: Key 不存在
            if (cacheList.size() == capacity) {
                // 缓存已满，需要淘汰最久未使用的元素（即链表尾部的元素）
                int keyToRemove = cacheList.back().first;
                cacheList.pop_back();     // 从链表移除
                cacheMap.erase(keyToRemove); // 从哈希表移除
            }
            
            // 将新元素插入到链表头部
            cacheList.push_front({key, value});
            // 在哈希表中保存 key 和对应的迭代器
            cacheMap[key] = cacheList.begin();
        }
    }
};