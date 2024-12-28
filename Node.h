#ifndef NODE_H
#define NODE_H

template <typename K, typename V>
class Node {
    public:
        K key;
        V value;
        Node* next;
        Node* prev;

        Node(K key, V value) : key(key), value(value), next(nullptr), prev(nullptr) {};
};

#endif // NODE_H
