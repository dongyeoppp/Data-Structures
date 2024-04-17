//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void RecursiveReverse(ListNode **ptrHead)		// 연결리스트 뒤집기  (재귀 사용 x)
{
	ListNode *node = *ptrHead;		// node에는 head의 주소를 넣음  
	ListNode *pre_node = node;		// 해당노드의 이전 노드를 담자  
	ListNode *last_node = node;		// 마지막 노드를 저장할거임   
	ListNode *first_node = node;	// 처음에 head가 가리키는 주소 저장    
	int count = 0;		// 마지막 노드 저장하기 위한 변수    
	while(1){
		if(node->next==NULL){		// 마지막 노드일 경우(next가 가르키는 주소가 없을경우 = null)
			if(count == 0){			// ll리스트의 마지막 노드를 last_node에 저장  
				last_node = node;
			}
			node->next = pre_node;		// 해당 노드의 next에 이전노드의 주소를 저장  
			pre_node->next = NULL;		// 이전 노드에 next 값에는 NULL저장  
			if (pre_node == first_node){		// 이전 노드가 처음 노드가 되었을 경우 
				break;
			}
			node = *ptrHead;		// 다시 처음 head가가르키는 node로 이동  
			pre_node= node;			// pre_node도 초기화   
			count++;				// 마지막 노드를 저장했다면 count는 필요없다.  
		}
		pre_node = node;		// node->next 값이 null이 아닐경우 pre_node에 해당 노드 저장   
		node = node->next;		// 다음노드를 가르키는 주소를 node에 저장   
	}
	*ptrHead = last_node;		// while문에 나온이후 head가 가르키는 주소를 마지막 노드로 바꿉니다. 그럼 마지막 노드부터 출력이 됩니다.   
}

void RecursiveReverse(ListNode **ptrHead)		// 연결리스트 뒤집기  (재귀로 구현)
{
	ListNode *pre = *ptrHead;		// pre노드에는 prehead의 주소(ll의head주소를 담고있는)가 들어간다.
	ListNode *node = pre->next;		// head의 다음 노드의 주소를 node에 넣음  

	if(node == NULL){		// 재귀 종료 조건 -> node가 null일경우, pre는 그러면 마지막 노드의 주소를 가르키고 있다.
		return;
	}
	RecursiveReverse(&node);	// node의 주소를 매개변수로 하여 재귀 ->node의 주소값을 넘겼기때문에 node의 값이 계속 갱신될 수 있다.  
	pre->next->next = pre;		// 재귀가 끝났을 때 node의 next값을 pre의 주소로 바꾸어준다.
	pre->next = NULL;			// pre의 next값은 node의 주소가 들어있던걸 null로 바꿔준다.   

	*ptrHead = node;		// ll의 head가 가르키는 노드를 원래 ll리스트의 마지막노드로 바꿔주기위함, node값은 마지막 노드의 주소값으로 계속 갱신된다.   
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
