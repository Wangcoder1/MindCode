/*[2019]（13分）设线性表L=(a?,a?,a?,?,a???,a???,a?)采用带头节点的单链表保存，
请设计一个空间复杂度为O(1)且时间上尽可能高效的算法，重新排列L中的各节点，
得到线性表L’=(a?,a?,a?,a???,a?,a???,?)。
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
}Node;

//尾插法创建单链表
void CreateList(Node** H, int arr[], int n) {
	*H = (Node*)malloc(sizeof(Node));
	(*H)->next = NULL;
	Node* tail = *H;
	for (int i = 0; i < n; i++) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = arr[i];
		p->next = NULL;
		tail->next = p;
		tail = p;
	}
}

//遍历打印链表
void PrintList(Node* H) {
	Node* p = H->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//反转链表
Node* Reverse(Node* head) {
	Node* pre = NULL;
	Node* cur = head;
	Node* nxt;                      //临时存cur原来的下一个节点,防止改完找不到下一个节点
	while (cur != NULL) {
		nxt = cur->next;            
		cur->next = pre;           //把pre里面保存的地址，赋值给当前节点的next （让当前节点反过来指向前方）
		pre = cur;
		cur = nxt;
	}
	return pre;
}

//重排 O(1)空间
void Reorder(Node* H) {
	if (H->next == NULL || H->next->next == NULL) {
		return;
	}

	//快慢指针找到中间节点
	Node* slow = H;
	Node* fast = H;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}

	//断开前后两端，反转后半段
	Node* back = slow->next;
	slow->next = NULL;
	Node* Rback = Reverse(back);

	//交替合并
	Node* p = H->next;
	Node* q = Rback;
	Node* pNxt, * qNxt;
	while (q != NULL) {
		pNxt = p->next;
		qNxt = q->next;

		p->next = q;
		q->next = pNxt;

		p = pNxt;
		q = qNxt;
	}
}

//释放内存
void FreeList(Node* H) {
	Node* q, * p = H;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}
}

int main() {
	int arr[] = {1, 2, 3, 4, 5, 6};
	int n = sizeof(arr) / sizeof(arr[0]);
	Node* H;

	CreateList(&H, arr, n);
	printf("原链表：\n");
	PrintList(H);

	Reorder(H);
	printf("重排后：\n");
	PrintList(H);

	FreeList(H);

	return 0;
}














































