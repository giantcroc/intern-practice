#include<bits/stdc++.h>
using namespace std;
class mystring{
    public:
        mystring(const char* str=nullptr);
        mystring(const mystring& str);
        ~mystring();

        mystring& operator=(const mystring& str);
        mystring operator+(const mystring& str);
        mystring& operator+=(const mystring& str);
        char& operator [](int index);
        bool operator ==(const mystring& str);
        int size() const;
        const char* c_str() const;
    private:
        char* data;
        int length;
};
mystring::mystring(const char* str)
{
    if(str==nullptr)
    {
        length=0;
        data=new char[1];
        *data='\0';
    }
    else{
        length=strlen(str);
        data=new char[length+1];
        strcpy(data,str);
    }
}
mystring::mystring(const mystring& str)
{
    length=str.size();
    data=new char[length+1];
    strcpy(data,str.c_str());
}
int mystring::size() const
{
    return length;
}
mystring::~mystring()
{
    delete [] data;
}
mystring& mystring::operator=(const mystring &str)//赋值操作符4步
{
    if (this == &str) return *this;//1 自我赋值，返回自身引用

    delete[] data;//2 删除原有数据
    
    length = str.size();//3 深拷贝
    data = new char[length + 1];
    strcpy(data, str.c_str());

    return *this;//4 返回自身引用
}
mystring mystring::operator+(const mystring &str)//+操作符3步
{//新建对象包括新空间，拷贝两个数据，返回新空间
    mystring newString;
    newString.length = length + str.size();
    newString.data = new char[newString.length + 1];
    strcpy(newString.data, data);
    strcat(newString.data, str.data);
    return newString;
}

mystring& mystring::operator+=(const mystring &str)//+=操作符5步
{//重分配新空间，拷贝两个数据，删除自己原空间，赋值为新空间，返回引用
    length += str.size();//成员length是实际长度
    char *newdata = new char[length + 1];
    strcpy(newdata, data);
    strcat(newdata, str.c_str());
    delete[] data;
    data = newdata;
    return *this;
}

char& mystring::operator[](int n)
{//下标操作符，返回引用
    if (n >= length) return data[length - 1];//如果越界，返回最后一个字符
    else return data[n];
}

bool mystring::operator==(const mystring &str)
{
    if (length != str.size()) return false;
    return strcmp(data, str.c_str()) ? false : true;
}
const char *mystring::c_str() const
{
    return data;
}
int main()
{
    char a[] = "Hello", b[] = "World!";
    mystring s1(a), s2(b);
    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;
    s1 += s2;
    cout << s1.c_str() << endl;
    s1 = s2;
    cout << s1.c_str() << endl;
    cout << (s1 + s2).c_str() << endl;
    cout << s1.size() << endl;
    cout << s1[1] << endl;
    s1[1]='H';
    cout << s1[1] << endl;
    if (s1 == s2)
        cout << "相等" << endl;
    return 0;
}