//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int maxHeight(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c;
    char e;
	c = 1;

    BTNode *root;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the maximum height of the binary tree.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("\nPlease input your choice(1/2/0): ");
        if(scanf("%d", &c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                c = maxHeight(root);
                printf("The maximum height of the binary tree is: %d\n",c);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int maxHeight(BTNode *node)     // 이진트리 깊이 구하기

{ 
    int count = 0;      // 이진트리의 depth 값을 담음   
    int max = 0;        // depth값 저장   
    BTNode *removed;        // stack에서 pop을 한 값을 저장  
    BTNode *node1 = node;       // 루트 노드를 저장   
    Stack ss = { NULL };        // 비어있는 스택 생성 
    push(&ss,node);             // 루트 노드 먼저 스택에 넣어주기  
    while(1){
        if (ss.top==NULL){       // 스택이 비어있을 경우 break
            break;
        }
        removed = pop(&ss);        
        if (removed == node1->left || removed == node1->right){     // 스택에서 루트노드와 연결된 노드가 나왔을 경우 원래 count값 max에 저장 이후 , count 값 1로 재설정 (오른쪽 노드들 다 돌고 왼쪽노드로 간다.)
            max =count;
            count = 1;
        }
        if (removed->left != NULL){     // 왼쪽 노드가 null이 아닐 경우 push
            push(&ss,removed->left);        
        }
        if(removed ->right != NULL){        // 오른쪽 노드가 null이 아닐 경우 push
            push(&ss,removed->right);
        }
        if (removed->right == NULL &&  removed->left == NULL)       // leaf node 일 경우 push 하지 않기 (count도 하지 않아야 함)
        {
            continue;
        }   
        count++;        // count +1 
    }
    if(max>=count){     // 오른쪽 노드, 왼쪽 노드의 depth를 비교하여 큰 값을 return    
        return max;
        }
    else{
        return count;
    }   


    //  /////////////////////// (재귀로 구현)
   
    // if (node == NULL){      // node가 존재하지 않을 경우 -1 return 
    //     return -1;
    // }
    // if (node->left == NULL && node->right == NULL){     // 자녀 노드가 없는 노드일 경우 return 0
    //     return 0;
    // }
    // int a = maxHeight(node->left);      // 왼쪽 재귀 -> 왼쪽 자식노드를 루트로 하여 깊이 계산 
    // int b = maxHeight(node->right);     // 오른쪽 재귀  -> 오른쪽 자식 노드를 루트로 하여 깊이 계산  
    // if (a>b){
    //     return a+1;     // 왼쪽 트리가 더 높은 경우 높이에 +1을 더해 return 
    // }
    // else{
    //     return b+1;     // 오른쪽 트리가 더 높은 경우 높이에 +1을 더해 return
    // }
}

///////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
