
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 1. 尾插法创建链表
void CreateList(Node** head, int* arr, int len) {
    *head = (Node*)malloc(sizeof(Node));
    if (*head == NULL) return;

    (*head)->next = NULL;
    Node* p = *head;

    for (int i = 0; i < len; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) return;

        newNode->data = arr[i];
        newNode->next = NULL;

        p->next = newNode;
        p = newNode;
    }
}

// 2. 打印链表
void Print(Node* head) {
    Node* p = head->next;

    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// 3. 寻找中间节点
Node* FindMiddle(Node* head) {
    Node* slow =head->next;
    Node* fast = head->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;    
    }
    return slow;
}

// 4. 判断链表是否有环
int HasCycle(Node* head) {
    Node* slow =head->next;
    Node* fast = head->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        
        if(fast == slow){
            return 1;           //有环
        }
    }
    return 0;                   //无环

}

// 5. 制造一个环：让尾节点指向指定位置
void CreateCycle(Node* head, int target) {
    //找到值为target的节点
    Node* p = head->next;
    while(p != NULL && p->data != target){
        p = p->next;
    }
    if(p == NULL) return;
    //找到尾节点
    Node* tail = head->next;
    while(tail->next != NULL){
        tail = tail->next;
    }
    // 让尾节点的 next 指向目标节点
    tail->next = p;
}

// 6. 解除环
void RemoveCycle(Node* head) {
    // 使用快慢指针找到相遇点
    Node* slow = head->next;
    Node* fast = head->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        
        if(fast == slow) break;
    }
    // 找到环的入口
    slow = head->next;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    // 找到环中最后一个节点
    Node* tail = slow;
    while(tail->next != slow){
        tail = tail->next;
    }
    // 将最后一个节点的 next 设置为 NULL
    tail->next = NULL;
}

// 7. 释放链表
void FreeList(Node* head) {
    // 注意：释放前必须保证链表没有环

    Node* cur = head;

    while (cur != NULL) {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* head = NULL;

    printf("========== 链表管理程序 ==========\n\n");

    CreateList(&head, arr, n);

    printf("原始链表：\n");
    Print(head);

    Node* mid = FindMiddle(head);
    printf("中间数为：%d\n", mid->data);

    printf("\n第一次检测：\n");

    int Cycle = HasCycle(head);
    if(Cycle){
        printf("有环\n");
    }else{
        printf("无环\n");
    }

    printf("制造一个环...\n");
    CreateCycle(head, 20);

    printf("\n第二次检测：\n");

    Cycle = HasCycle(head);
    if(Cycle){
        printf("有环\n");
    }else{
        printf("无环\n");
    }

    printf("解除环...\n");
    RemoveCycle(head);

    printf("\n解除环后的链表：\n");
    Print(head);

    FreeList(head);

    printf("\n程序结束，内存已释放。\n");

    return 0;
}
