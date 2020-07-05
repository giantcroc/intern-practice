#include<bits/stdc++.h>
using namespace std;
struct node{
    int val;
    node* left,*right;
    node(int v):val(v),left(nullptr),right(nullptr){}
};
bool dele(node* &root,int val)
{
    if(root==nullptr)
        return false;
    if(val<root->val)
        return dele(root->left,val);
    else if(val>root->val)
        return dele(root->right,val);
    else{
        if(root->left==nullptr)
        {
            node* temp=root->right;
            delete root;
            while(temp&&temp->val==val)
                dele(temp,val);
            root=temp;
            return true;
        }
        if(root->right==nullptr)
        {
            node* temp=root->left;
            delete root;
            root=temp;
            return true;
        }
        node* temp=root->left;
        while(temp&&temp->right)
            temp=temp->right;
        root->val=temp->val;
        dele(root->left,temp->val);
        temp=root->right;
        while(temp&&temp->val==val)
            dele(temp,val);
        root->right=temp;
        return true;
    }
    return false;
}
bool dele1(node* &root,int val)
{
    if(root==nullptr)
        return false;
    if(val<root->val)
        return dele(root->left,val);
    else if(val>root->val)
        return dele(root->right,val);
    else{
        if(root->left==nullptr)
        {
            node* temp=root->right;
            delete root;
            root=temp;
            return true;
        }
        if(root->right==nullptr)
        {
            node* temp=root->left;
            delete root;
            root=temp;
            return true;
        }
        node* temp=root->left;
        node* pre=root;
        while(temp&&temp->right)
        { 
            pre=temp;   
            temp=temp->right;
        }
        root->val=temp->val;
        delete temp;
        if(pre==root)
        {
            root->left=nullptr;
        }
        else{
            pre->right=nullptr;
        }
        return true;
    }
    return false;
}
void insert(node*&root,int val)
{
    if(root==nullptr)
    {
        root=new node(val);
        return;
    }
    if(val<root->val)
        insert(root->left,val);
    else insert(root->right,val);
}
void show(node* root)
{
    queue<node*> q;
    q.push(root);
    while(!q.empty())
    {
        int size=q.size();
        for(int i=0;i<size;i++)
        {
            node* temp=q.front();
            q.pop();
            cout<<temp->val<<' ';
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
        cout<<endl;
    }
}
int main()
{
    node* root=nullptr;
    //int ll[]={5,5,3,3,2,3,4,6,7,6,8,8};
    int ll[]={6,4,2,5,8,7,9};
    for(int i=0;i<7;i++)
        insert(root,ll[i]);
    show(root);
    dele1(root,4);
    show(root);
    return 0;
}

