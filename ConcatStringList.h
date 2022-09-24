#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class Node
{
public:
    char* c;
    Node *next;
    Node()
    {
        next = nullptr;
    }
    Node(const char* s){
        int i = 0;
        while(s[i] != '\0'){
            c[i] = s[i];
            i++;
        }
        c[i] = '\0';
        next = nullptr;
    }
    int get_size()
    {
        int i = 0;
        while(c[i] != '\0'){
            i++;
        }
        return i;
    }
};

class ConcatStringList
{
public:
    class ReferencesList;   // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes

public:
    int list_length;
    Node *head;
    Node *tail;
    ConcatStringList();
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const{
        if(index < 0 or index > list_length){
            throw out_of_range("Index of string is invalid!");
        }
        Node *curr = head;
        while(index > curr->get_size()){
            index -= curr->get_size();
            curr = curr->next;
        }
        return curr->c[index - 1];
    }
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList &otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList(){
        list_length = 0;
        Node *temp = head;
        while(!temp){
            delete temp;
            temp = temp->next;
        }
        head = nullptr;
        delete tail;
        tail = nullptr;
    }

public:
    class ReferencesList
    {
        // TODO: may provide some attributes
    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList
    {
        // TODO: may provide some attributes

    public:
        int size() const;
        std::string totalRefCountsString() const;
    };
};
ConcatStringList :: ConcatStringList(){
    head = tail = nullptr;
    list_length = 0;
}
ConcatStringList ::ConcatStringList(const char *s)
{
    Node *curr = new Node(s);
    list_length = curr->get_size();
    tail = curr;
    head = curr;
    tail->next = nullptr;
    head->next = nullptr;
}
int ConcatStringList ::length() const
{
    return list_length;
}
int ConcatStringList :: indexOf(char c) const{
    char ans;
    Node *curr = head;
    int cnt = 0;
    for(int i = 0; i<list_length;i++){
        if(i >= curr->get_size()){
            curr = curr->next;
            cnt = i;
        }
        if(c == curr->c[i - cnt])       return i + 1;
    }
    return -1;
}
std :: string ConcatStringList :: toString() const{
    string res = "";
    Node *curr = head;
    while(curr != nullptr){
        int i = 0;
        while(curr->c[i] != '\0'){
            res += curr->c[i];
            i++;
        }
        curr = curr->next;
    }
    return res;
}
ConcatStringList ConcatStringList :: concat(const ConcatStringList &otherS) const{
    ConcatStringList ans;
    if(head == tail){
        if(otherS.head == otherS.tail){
            Node *temp1 = head;
            Node *temp2 = otherS.head;
            temp1->next = temp2;
            ans.head = temp1;
            ans.tail = temp2;
        }
        else{
            Node *temp1 = head;
            Node *temp2 = otherS.head;
            Node *temp3 = otherS.tail;
            temp1->next = temp2;
            ans.head = temp1;
            ans.tail = temp3;
        }
    }
    else{
        if(otherS.head == otherS.tail){
            Node *temp1 = head;
            Node *temp2 = tail;
            Node *temp3 = otherS.head;
            temp2->next = temp3;
            ans.head = temp1;
            ans.tail = temp3;
        }
        else{
            Node *temp1 = head;
            Node *temp2 = tail;
            Node *temp3 = otherS.head;
            Node *temp4 = otherS.tail;
            temp2->next = temp3;
            ans.head = temp1;
            ans.tail = temp4;
        }
    }
    ans.list_length = list_length + otherS.list_length;
    return ans;
}
ConcatStringList ConcatStringList :: subString(int from, int to) const{
    ConcatStringList ans;
    if(from < 0 or to >= list_length)   throw out_of_range("Index of string is invalid");
    if(from >= to)      throw logic_error("Invalid range");
    Node *curr = head;
    Node *trv;
    while(from > curr->get_size()){
        from -= curr->get_size();
        to -= curr->get_size();
        curr = curr->next;
    }
    bool flag = true;
    Node* dau;
    while(to > curr->get_size()){
        if(from > 0){
            Node *temp;
            for(int i = from; i < curr->get_size();i++){
                temp->c[i - from] = curr->c[i];
            }
            trv = temp;
            if(flag){
                dau = trv;
                flag = false;
            }
            trv = trv->next;
            from = 0;
            to -= curr->get_size();
            curr = curr->next;
        }
        else{
            Node *temp;
            for(int i = 0; i < curr->get_size();i++){
                temp->c[i] = curr->c[i];
            }
            trv = temp;
            trv = trv->next;
            from = 0;
            to -= curr->get_size();
            curr = curr->next;
        }
    }
    for(int i = 0;i<to;i++){
        trv->c[i] = curr->c[i];
    }
    trv->next = nullptr;
    ans.head = dau;
    ans.tail = trv;
    return ans;
}
ConcatStringList ConcatStringList :: reverse() const{
    ConcatStringList ans;
    Node *curr = head;
    Node *prev = nullptr;
    Node *tiep = nullptr;
    while(!curr){
        tiep = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tiep;
    }   
    ans.head = prev;
    return ans;
}

// Reference List
#endif // __CONCAT_STRING_LIST_H__