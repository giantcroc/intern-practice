#include<bits/stdc++.h>
using namespace std;
struct listnode{
    int key;
    int value;
    listnode* prev,*next;
    listnode(int key,int value):key(key),value(value),prev(nullptr),next(nullptr){}
};
class LRUCache {
public:
    LRUCache(int cap) {
        capacity=cap;
        head=new listnode(0,0);
        tail=new listnode(0,0);
        head->next=tail;
        tail->prev=head;
        used=0;
    }
    int get(int key) {
        if(maps.find(key)==maps.end())
            return -1;
        listnode*cur=maps[key];
        remove(cur);
        add_tail(cur);
        return cur->value;
    }
    
    void put(int key, int value) {
        if(maps.find(key)!=maps.end())
        {
            listnode*cur=maps[key];
            remove(cur);
            add_tail(cur);
            cur->value=value;
        }
        else{
            if(used==capacity)
            {
                listnode* temp=head->next;
                remove(temp);
                maps.erase(temp->key);
                delete temp;
            }
            else used++;
            listnode* cur=new listnode(key,value);
            add_tail(cur);
            maps[key]=cur;
        }
    }
    void add_tail(listnode* cur)
    {
        cur->next=tail;
        cur->prev=tail->prev;
        tail->prev->next=cur;
        tail->prev=cur;
    }
    void remove(listnode* cur)
    {
        cur->next->prev=cur->prev;
        cur->prev->next=cur->next;
    }
    unordered_map<int,listnode*> maps;
    int capacity;
    int used;
    listnode* head,*tail;
};
int main()
{
    LRUCache* obj = new LRUCache(1);
    obj->put(2,1);
    //obj->show(obj->head);
    cout<<obj->get(2)<<endl;
    obj->put(3,2);
    //obj->show(obj->head);
    cout<<obj->get(2)<<endl;
    return 0;
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */