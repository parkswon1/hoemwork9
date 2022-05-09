#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node 구조체 생성
	int key; //int형 key
	struct node *left; //왼쪽 노드표시할 포인터
	struct node *right; //오른쪽 노드 표시할 포인터
} Node; //Node로 호출 가능

int initializeBST(Node** h); //int형 initializeBST함수 Node형 이중포인터 h를 매개변수로 받아온다.

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //command받아올 char형 변수
	int key; //key값 받아올 int형 변수
	Node* head = NULL; //head노드의 포인터 생성후 NULL로 초기화
	Node* ptr = NULL;	/* temp */ //Node주소 저장해둘 ptr 생성후 NULL로 초기화
	printf("[----- [Seok Won Park] [2017018003] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command입력 받아와 저장

		switch(command) { //command가 어떤 값이냐에 따라서 구분
		case 'z': case 'Z': //z일경우
			initializeBST(&head); //initializeBST함수 호출후 head주소 넣어주기
			break;
		case 'q': case 'Q': //q일경우
			freeBST(head); //freeBST함수 호출후 head 넣어주기
			break;
		case 'n': case 'N': //n일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아오기
			insert(head, key); //insert함수 호출후 head,key 넣어주기
			break;
		case 'd': case 'D': //d일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아오기
			deleteLeafNode(head, key); //deleteLeafNode함수 호출후 head,key 넣어주기
			break;
		case 'f': case 'F': //f일경우
			printf("Your Key = ");
			scanf("%d", &key); //key값 받아오기
			ptr = searchIterative(head, key); //searchIterative함수 호출후 head,key 넣어주기 그반환값을 ptr에 넣어준다.
			if(ptr != NULL)//ptr이 없으면 key값이 노드안에 없다는 오류 출력
				printf("\n node [%d] found at %p\n", ptr->key, ptr); 
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': //s일경우
			printf("Your Key = "); 
			scanf("%d", &key); //key값 받아오기
			ptr = searchRecursive(head->left, key); //searchRecursive함수 호출후 head의 left의 값,key 넣어주기 그반환값을 ptr에 넣어준다.
			if(ptr != NULL)//ptr이 없으면 key값이 노드안에 없다는 오류 출력
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': //i일경우
			inorderTraversal(head->left); //inorderTraversal함수 호출후 head의 left의 값 넣어주기
			break;
		case 'p': case 'P': //p일경우
			preorderTraversal(head->left); //preorderTraversal함수 호출후 head의 left의 값 넣어주기
			break;
		case 't': case 'T': //t일경우
			postorderTraversal(head->left); //postorderTraversal함수 호출후 head의 left의 값 넣어주기
			break;
		default: //위 case의 다른값일경우 잘못 입력했다는 오류 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q일때 종료

	return 1; //실행잘되면 1 return
}

int initializeBST(Node** h) {//노드에 동적할당을 넣어주는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //만약 빈 노드가 아니라면 동적할당들을 해제해줌
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //h에 node형태로 동적할당
	(*h)->left = NULL;	/* root */ //left값을 NULL로 초기화
	(*h)->right = *h; //right값을 h의 주소값 넣어줌
	(*h)->key = -9999; //key값을 -9999넣어줌
	return 1;
}

void inorderTraversal(Node* ptr) //중위탐색 방법
{
	if(ptr) { //ptr이 true면
		inorderTraversal(ptr->left); //inorderTraversal를 호출후 ptr의 left값을 넣어준다.
		printf(" [%d] ", ptr->key); //ptr의 key값을 출력해준다.
		inorderTraversal(ptr->right); //inorderTraversal를 호출후 ptr의 right값을 넣어준다.
	}
}

void preorderTraversal(Node* ptr)//전위탐색방법
{
	if(ptr) { //ptr이 true면
		printf(" [%d] ", ptr->key); //ptr의 key값을 출력해준다.
		preorderTraversal(ptr->left); //preorderTraversal를 호출후 ptr의 left값을 넣어준다.
		preorderTraversal(ptr->right); //preorderTraversal를 호출후 ptr의 right값을 넣어준다.
	}
}

void postorderTraversal(Node* ptr) //후위탐색방법
{
	if(ptr) { //ptr이 true면
		postorderTraversal(ptr->left); //postorderTraversal를 호출후 ptr의 left값을 넣어준다.
		postorderTraversal(ptr->right); //postorderTraversal를 호출후 ptr의 right값을 넣어준다.
		printf(" [%d] ", ptr->key); //ptr의 key값을 출력해준다.
	}
}


int insert(Node* head, int key)//node를 생성하고key값을 넣어주는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //newnode를 동적할당 받아옴
	newNode->key = key; //newNode의 key값을 key로
	newNode->left = NULL; //left를 NULL로 초기화
	newNode->right = NULL; // right를 NULL로 초기화

	if (head->left == NULL) { //만약 head노드의 left가 NULL이라면
		head->left = newNode; //left에 새로운 노드를 넣어준다
		return 1; //return 1로 정상종료
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr노드 포인터 생성하고 head노드의 left값 넣어줌

	Node* parentNode = NULL; //부모노드 생성하고 NULL로 초기화함
	while(ptr != NULL) { //ptr이 NULL이 아니라면

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //이미 key값을 가졌다면 종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //부모노드를 ptr값을 넣어주고

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //만약 ptr의 key값이 key보다 작다면
			ptr = ptr->right; //오른쪽으로 이동
		else 
			ptr = ptr->left; //왼쪽으로 이동
	}//이동하다보면 ptr이 NULL이됨

	/* linking the new node to the parent */
	if(parentNode->key > key) //부모노드의 key가 key값보다 크다면 
		parentNode->left = newNode; //왼쪽에 newNode를 넣어줌
	else
		parentNode->right = newNode; //오른쪽에 newNode를 넣어줌
	return 1;
}

int deleteLeafNode(Node* head, int key) //key값을 가진 node 삭제하기
{
	if (head == NULL) { //head가 NULL이라면 삭제할 노드가 없다는 오류출력
		printf("\n Nothing to delete!!\n"); 
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL이라면 삭제할 노드가 없다는 오류출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr생성해서 head의 left값을 넣어준다


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //부모노드에 head 노드를 넣어준다

	while(ptr != NULL) { //ptr이 NULL이 아니라면 (빈 노드를 찾아주는것)
 
		if(ptr->key == key) { //key값이 ptr의 key값과 같다면
			if(ptr->left == NULL && ptr->right == NULL) { //left혹은 right가 비었는지 검사

				/* root node case */
				if(parentNode == head) //부모노드가 head라면
					head->left = NULL; //head의 left를 NULL로

				/* left node case or right case*/
				if(parentNode->left == ptr) //부모노드의 left가 ptr이라면
					parentNode->left = NULL; //NULL로초기화
				else
					parentNode->right = NULL; //아니면 오른쪽을 NULL로 초기화

				free(ptr); //ptr노드를 초기화함
			}
			else { //key값을 가진 leaf노드가 없다는 오류 출력
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //부모노드를 ptr로 

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key값이 key값보다 작다면
			ptr = ptr->right; //ptr의 오른족으로 이동
		else
			ptr = ptr->left; //왼쪽으로이동


	}
	//key값을 가진 노드를 찾지 못했다는 오류 출력
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //Recursive방식으로 찾기
{
	if(ptr == NULL) //ptr이 NULL이라면 
		return NULL; //NULL리턴

	if(ptr->key < key) //ptr의 key가 key보다 작다면
		ptr = searchRecursive(ptr->right, key); //searchRecursive함수호출후 ptr의 오른쪽과 key값 넣어줌(오른쪽으로 이동)
	else if(ptr->key > key) //ptr의 key가 key보다 크다면
		ptr = searchRecursive(ptr->left, key); //searchRecursive함수호출후 ptr의 왼쪽과 key값 넣어줌(왼쪽으로 이동)

	/* if ptr->key == key */
	return ptr; 

}
Node* searchIterative(Node* head, int key) //Iterative방식으로 찾기
{
	/* root node */
	Node* ptr = head->left; //ptr포인터 생성후 head노드의 left값을 넣어줌

	while(ptr != NULL) //ptr이 NULL일떄까지 반복
	{
		if(ptr->key == key) //ptr의 key값이 key값과 같다면
			return ptr; //ptr반환

		if(ptr->key < key) ptr = ptr->right; //ptr의 key값이 key값보다 작다면 ptr은 ptr의 오른쪽이됨
		else 
			ptr = ptr->left; //아닐경우 ptr은 left가됨 (왼쪽으로이동)
	}

	return NULL; //NULL을 return
}

void freeNode(Node* ptr) //node 동적할당 해제
{
	if(ptr) { //ptr이 true면
		freeNode(ptr->left); //왼쪽노드 전부 동적할당해제
		freeNode(ptr->right); //오른쪽노드 번부 동적할당 해제
		free(ptr); //마지막으로 ptr동적할당 해제
	}
}

int freeBST(Node* head) //head노드 동적할당 해제
{

	if(head->left == head) //노드가 비었을경우
	{
		free(head); //해드 노드만 동적할당 해제
		return 1;
	}

	Node* p = head->left; //포인터 p head노드의 왼쪽으로 지정

	freeNode(p); //p노드동적할당해제

	free(head); //head동적할당 해제
	return 1;
}





