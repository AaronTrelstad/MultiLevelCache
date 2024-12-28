#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include "LRULevel.h"

template <typename K, typename V>
class Cache {
    private:
        std::vector<LRULevel<K, V> > levels;
        int numLevels;
        int capacity;
    public:
        Cache(int numLevels, int capacity);
        V get(K key);
        void put(K key, V value);
};

template <typename K, typename V>
Cache<K, V>::Cache(int numLevels, int capacity) : numLevels(numLevels) {
    for (int i = 0; i < numLevels; ++i) {
        levels.push_back(LRULevel<K, V>(capacity));
    }
}

template <typename K, typename V>
V Cache<K, V>::get(K key) {
    for (auto& level : levels) {
        V value = level.get(key);

        if (value != V()) {
            return value;
        }
    }

    return V();
}

template <typename K, typename V>
void Cache<K, V>::put(K key, V value) {
    Node<K, V>* extraNode;

    for (int i = 0; i < levels.size(); ++i) {
        extraNode = levels[i].put(key, value);

        if (extraNode) {
            key = extraNode->key;
            value = extraNode->value;

            continue;
        }

        break;
    }

    if (extraNode) {
        delete extraNode;
        extraNode = nullptr;
    }  
}

#endif // CACHE_H
