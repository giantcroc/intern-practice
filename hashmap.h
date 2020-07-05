#ifndef _HASHMAP_H_
#define _HASHMAP_H_
template<class Key, class Value>
class HashNode
{
public:
    Key    _key;
    Value  _value;
    HashNode *next;

    HashNode(Key key, Value value)
    {
        _key = key;
        _value = value;
        next = nullptr;
    }
};

template <class Key, class Value, class HashFunc, class EqualKey>
class HashMap
{
public:
    HashMap(int size);
    ~HashMap();
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    HashNode<Key,Value>* find(const Key& key);
    Value& operator [](const Key& key);

private:
    HashFunc hash;
    EqualKey equal;
    HashNode<Key, Value> **table;
    unsigned int _size;
};


template <class Key, class Value, class HashFunc, class EqualKey>
HashMap<Key, Value, HashFunc, EqualKey>::HashMap(int size) : _size(size)
{
    table = new HashNode<Key, Value>*[_size];
    for (unsigned i = 0; i < _size; i++)
        table[i] = nullptr;
}



template <class Key, class Value, class HashFunc, class EqualKey>
HashMap<Key, Value, HashFunc, EqualKey>::~HashMap()
{
    for (unsigned i = 0; i < _size; i++)
    {
        HashNode<Key, Value> *currentNode = table[i];
        while (currentNode)
        {
            HashNode<Key, Value> *temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }
    }
    delete [] table;
}


template <class Key, class Value, class HashFunc, class EqualKey>
void HashMap<Key, Value, HashFunc, EqualKey>::insert(const Key& key, const Value& value)
{
    HashNode<Key, Value>* cur=find(key);
    if(cur==nullptr)
    {
        unsigned int index = hash(key) % _size;
        HashNode<Key, Value> * node = new HashNode<Key, Value>(key,value);
        node->next = table[index];
        table[index] = node;
    }
    else cur->_value = value;
}


template <class Key, class Value, class HashFunc, class EqualKey>
void HashMap<Key, Value, HashFunc, EqualKey>::remove(const Key& key)
{
    unsigned int index = hash(key) % _size;
    HashNode<Key, Value> * node = table[index];
    HashNode<Key, Value> * prev = nullptr;
    while (node)
    {
        if (node->_key == key)
        {
            if (prev == nullptr)
            {
                table[index] = node->next;
            }
            else
            {
                prev->next = node->next;
            }
            delete node;
        }
        prev = node;
        node = node->next;
    }
}

template <class Key, class Value, class HashFunc, class EqualKey>
HashNode<Key,Value>* HashMap<Key, Value, HashFunc, EqualKey>::find(const Key& key)
{
    unsigned int index = hash(key) % _size;
    if (table[index])
    {
        HashNode<Key, Value> * node = table[index];
        while (node)
        {
            if (equal(node->_key,key))
                return node;
            node = node->next;
        }
    }
    return nullptr;
}


template <class Key, class Value, class HashFunc, class EqualKey>
Value& HashMap<Key, Value, HashFunc, EqualKey>::operator [](const Key& key)
{
    HashNode<Key,Value> *cur=find(key);
    if(cur==nullptr)
    {    
        Value temp;
        insert(key,temp);
    }
    return find(key)->_value;
}


#endif