#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

//尾插法创建链表
void CreateList(Node** head, int arr[], int len){
    *head = (Node*)malloc(sizeof(Node));
    (*head)->next = NULL;
    Node* p = *head;
    for(int i = 0; i < len; i++){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        p->next = newNode;
        p = newNode;
    }
}

//打印链表
void Print(Node* head){
    Node* p = head->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
}

//反转链表
void ReverseList(Node* head){
    Node* pre = NULL;
    Node* cur = head->next;
    while(cur != NULL){
        Node* p = cur->next;
        cur->next = pre;
        pre = cur;
        cur = p; 
    }
    head->next = pre;
}

//释放链表
void FreeList(Node* head){
    Node* cur = head;
    while(cur != NULL){
        Node* p = cur;
        cur = cur->next;
        free(p);
    }
}

int main(){
    Node* head;
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    CreateList(&head, arr , n);
    printf("反转链表前：\n");
    Print(head);
    printf("\n");
    
    ReverseList(head);
    printf("反转链表后：\n");
    Print(head);
    
    FreeList(head);
    
    return 0;
}











































