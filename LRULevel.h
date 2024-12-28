#ifndef LRU_LEVEL_H
#define LRU_LEVEL_H

#include <unordered_map>
#include "Node.h"

template <typename K, typename V>
class LRULevel {
    private:
        std::unordered_map<K, Node<K, V>*> cache;
        int capacity;
        Node<K, V>* left;
        Node<K, V>* right;

        void remove(Node<K, V>* node);
        void insert(Node<K, V>* node);
    public:
        LRULevel(int capacity);
        //~LRULevel();

        V get(K key);
        Node<K, V>* put(K key, V value);
};

template <typename K, typename V>
LRULevel<K, V>::LRULevel(int capacity): capacity(capacity) {
    left = new Node<K, V>(K(), V());
    right = new Node<K, V>(K(), V());

    left->next = right;
    right->prev = left;
}

/** 
Need to figure out why the deconstructor breaks the program

template <typename K, typename V>
LRULevel<K, V>::~LRULevel() {
    for (auto& pair : cache) {
        delete pair.second;
    }
    delete left;
    delete right;
}
*/

template <typename K, typename V>
void LRULevel<K, V>::remove(Node<K, V>* node) {
    Node<K, V>* next = node->next;
    Node<K, V>* prev = node->prev;

    prev->next = next;
    next->prev = prev;
}

template <typename K, typename V>
void LRULevel<K, V>::insert(Node<K, V>* node) {
    Node<K, V>* next = right;
    Node<K, V>* prev = right->prev;

    node->prev = prev;
    prev->next = node;

    next->prev = node;
    node->next = next;
}

template <typename K, typename V>
V LRULevel<K, V>::get(K key) {
    if (cache.find(key) != cache.end()) {
        Node<K, V>* node = cache[key];
        remove(node);
        insert(node);

        return node->value;
    }

    return V();
}

template <typename K, typename V>
Node<K, V>* LRULevel<K, V>::put(K key, V value) {
    if (cache.find(key) != cache.end()) {
        remove(cache[key]);
        delete cache[key];
    }

    Node<K, V>* node = new Node<K, V>(key, value);
    cache[key] = node;
    insert(node);

    if (cache.size() > capacity) {
        Node<K, V>* nodeToRemove = left->next;
        remove(nodeToRemove);
        cache.erase(nodeToRemove->key);

        return nodeToRemove;
    }

    return nullptr;
}
#endif // LRU_LEVEL_H
