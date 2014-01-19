#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* next;
};

void alternate(Node *head){
    // count the number of items in list
    int count = 0;
    Node *p = head;
    while(p){
        count++;
        p=p->next;
    }
    cout <<"No of items "<<count<<endl;

    // move to the middle of the list and reverse second half
    p = head;
    int m = count/2;
    for(int i = 0; i < m - 1; ++i){
        p = p->next;
    }
    cout <<"Middle is "<<m<<", val "<<p->info<<endl;

    Node *middle = p;
    // reverse the second half
    Node *prev = NULL;
    Node *current = middle->next;
    while(current){
        // save next
        Node *next = current->next;
        // reverse
        current->next = prev;
        // advance;
        prev = current;
        current = next;
    }
    
    // connect head of last half to list
    middle->next = prev; 
    
    // display last prev
    cout << "last el "<<prev->info<<endl;
    // display current list status
    cout <<"current list ";
  
    p = head;
    while(p){
        cout<<p->info<<" ";
        p = p->next;
    }
    cout<<endl;
    
    // display list alternating from both halfs
    p = head;
    Node *q = middle->next;   
    while(p != middle->next && q){
        cout<< q->info<<" "<<p->info<<" ";
        p = p->next;
        q = q->next;
    }
    while(q){
        cout<< q->info<<" ";
        q=q->next;
    }
    while(p!=middle->next){
        cout<<p->info<<" ";
        p=p->next;
    }

}


int main() {
    // Start typing your code here...
    int n = 10;
    Node *head = NULL;
    for(int i = 0; i < n; ++i){
        Node *p = new Node;
        p->info = n-i;
        p->next = head;
        head = p;
    }

    Node *p = head;
    while(p){
        cout << p->info<<" ";
        p = p->next;
    }
    cout<<endl;

    alternate(head);

    return 0;
}
