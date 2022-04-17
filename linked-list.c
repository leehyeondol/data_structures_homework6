/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */
#include<stdio.h>//입출력 헤더
#include<stdlib.h>//라이브러리 헤더

/* 필요한 헤더파일 추가 */

typedef struct Node {//리스트 노드 구조체
	int key;//정수형 변수 key 생성
	struct Node* link;//링크 노드 생성
} listNode;

typedef struct Head {//헤드 노드 구조체
	struct Node* first;//첫번째 노드
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);//초기 내용 설정
int freeList(headNode* h);//리스트 해제

int insertFirst(headNode* h, int key);//첫번째 입력
int insertNode(headNode* h, int key);//노드 입력
int insertLast(headNode* h, int key);//마지막 노드 입력

int deleteFirst(headNode* h);//첫번째값 삭제
int deleteNode(headNode* h, int key);//노드값 삭제 
int deleteLast(headNode* h);//마지막값 삭제
int invertList(headNode* h);//리스트 역순 재배치

void printList(headNode* h);//출력 함수

int main()
{
	printf("[----- [Lee hyeondo] [2019038085] -----] ");
	char command;//커멘드 변수
	int key;//정수형 키변수
	headNode* headnode=NULL;//헤드노드

	do{//whlie의 조건에 따라 반복
		printf("----------------------------------------------------------------\n");//메뉴 출력
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");//커멘드 출력
		scanf(" %c", &command);//커멘드 입ㅈ력

		switch(command) {//반복문
		case 'z': case 'Z'://커멘드가 z라면
			headnode = initialize(headnode);//헤드노드 입력
			break;
		case 'p': case 'P'://커멘드가 p라면
			printList(headnode);//노드 출력
			break;
		case 'i': case 'I'://커멘드가 i라면
			printf("Your Key = ");//"Your Key = "출력
			scanf("%d", &key);//키값 입력
			insertNode(headnode, key);//노드 입력
			break;
		case 'd': case 'D'://커멘드가 d라면
			printf("Your Key = ");//"Your Key = "출력
			scanf("%d", &key);//키값 입력
			deleteNode(headnode, key);//입력한 키 삭제
			break;
		case 'n': case 'N'://커멘드가 n라면
			printf("Your Key = ");//"Your Key = "출력
			scanf("%d", &key);//키값 입력
			insertLast(headnode, key);//마지막 노드 입력
			break;
		case 'e': case 'E'://커멘드가 e라면
			deleteLast(headnode);//노드 삭제
			break;
		case 'f': case 'F'://커멘드가 f라면
			printf("Your Key = ");//"Your Key = "출력
			scanf("%d", &key);//키값 입력
			insertFirst(headnode, key);//첫번째 값 입력
			break;
		case 't': case 'T'://커멘드가 t라면
			deleteFirst(headnode);//첫번째 값 삭제
			break;
		case 'r': case 'R'://커멘드가 r라면
			invertList(headnode);//리스트 반전
			break;
		case 'q': case 'Q'://커멘드가 q라면
			freeList(headnode);//노드 메모리 해제
			break;
		default://모두 아니라면 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");// Concentration!! 출력
			break;
		}

	}while(command != 'q' && command != 'Q');//커멘드가 Q가 아니면 반복

	return 1;//리턴 1 
}

headNode* initialize(headNode* h) {//초기값 설정 함수

	if(h != NULL)//헤드가 NULL이 아니면 
		freeList(h);// freeNode를 호출하여 할당된 메모리 모두 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));//헤드노드의 템프에 동적할당.
	temp->first = NULL;//템프에 첫 노드 연결하고 0으로 초기화
	return temp;//리턴 템프
}

int freeList(headNode* h){//메모리 해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//노드 p에 첫번째 노드입력

	listNode* prev = NULL;//노드 prev생성 및 NULL로 초기화
	while(p != NULL) {//연결된 노드들 모두 NULL이 될때까지 반복
		prev = p;//prev에 p 입력
		p = p->link;//p는 다음노드
		free(prev);//prev 해제
	}
	free(h);//헤드 노드 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드 입력 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//구조체 노드의 키값에 인자 키 입력
	node->link = NULL;//노드에 link 는 NULL

	if (h->first == NULL)//첫번째 연결 노드가 NULL이면
	{
		h->first = node;//첫번째 노드는 동적할당한 노드 입력
		return 0;
	}

	listNode* n = h->first;//n에 첫번째 노드 입력
	listNode* trail = h->first;//trail노드 생성 첫 노드 입력

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//n이 NULL이 아닌동안
		if(n->key >= key) {//노드와 연결된 키가 입력한 키보다 크다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {//첫번째가 n과 같다면
				h->first = node;//첫번째 노드에 node를 가리키고
				node->link = n;//노드는 원래 첫 노드를 가리킴
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;//링크에 n 입력
				trail->link = node;//trail의 링크는 노드를 가리킴
			}
			return 0;
		}

		trail = n;//trail = n
		n = n->link;//n은 n의link
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;//trail은 node를 가리킴
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//마지막 노드 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드는 키를 가리킴
	node->link = NULL;//노드의 링크는 NULL

	if (h->first == NULL)//만약 첫번째 노드가 비어있다면
	{
		h->first = node;//첫번째 노드에 노드 입력
		return 0;
	}

	listNode* n = h->first;//첫번째 노드는 n
	while(n->link != NULL) {//n이 가리키는게 NULL이 아닌동안
		n = n->link;//n은 한칸이동
	}
	n->link = node;//마지막 n은 노드를 가리킴
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//첫노드 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드는 키를 가르킴

	node->link = h->first;//첫번째 노드가 노드가 가리키는 노드를 보게됨 
	h->first = node;//헤드가 가리키던 첫번째 노드가 입력받은 노드로 변경

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//노드 삭제 함수

	if (h->first == NULL)//첫번째 노드가 없으면
	{
		printf("nothing to delete.\n");//삭제할 노드 없음 출력
		return 0;
	}

	listNode* n = h->first;//첫번째 노드는 n
	listNode* trail = NULL;//트레일 노드 생성

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//마지막 노드까지
		if(n->key == key) {//첫 노드가 가리티는 노드가 키이면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {//노드가 첫 노드면
				h->first = n->link;//첫 노드는 n의 다음노드를 가리킴
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;//트레일이 n의 다음 노드를 가리킴
			}
			free(n);//n 메모리 해제
			return 0;
		}

		trail = n;//trail은 n
		n = n->link;//n은 다음 노드 
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);//찾지 못한경우 "cannot find the node for key 출력
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//마지막 노드 삭제 함수

	if (h->first == NULL)//첫번째 노드가 0이면
	{
		printf("nothing to delete.\n");//삭제할 노드 없음 출력
		return 0;
	}

	listNode* n = h->first;//n에 첫 노드입력
	listNode* trail = NULL;//트레일 노드 생성

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {//첫 노드가 가리키는 노드가 없으면
		h->first = NULL;//첫 노드는 NULL
		free(n);//n 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {//가리키는 노드가 NULL일때까지
		trail = n;//트레일 노드는 n
		n = n->link;//n은 다음 노드
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;//트레일의 다음 노드는 NULL
	free(n);//n메모리 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//첫 노드 삭제 함수

	if (h->first == NULL)//첫노드가 NULL이면
	{
		printf("nothing to delete.\n");//삭제할게 없음을 출력
		return 0;
	}
	listNode* n = h->first;//n에 첫번째 노드 입력

	h->first = n->link;//첫번째 노드는 다음노드를 가리킴
	free(n);//n 메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//리스트 역순 재배치 함수


	if(h->first == NULL) {//만약 첫번째 노드가 비어있다면
		printf("nothing to invert...\n");//역순할 리스트가 없음을 출력
		return 0;
	}
	listNode *n = h->first;//n에 첫번째 노드 입력
	listNode *trail = NULL;//트레일 노드 생성
	listNode *middle = NULL;//미들 노드 생성

	while(n != NULL){//마지막 노드까지 반복
		trail = middle;//트레일노드에 미들노드 입력
		middle = n;//미들노드는 현재노드 입력
		n = n->link;//현재 노드는 다음 노드 
		middle->link = trail;//미들 노드의 다음노드는 트레일 노드 
	}

	h->first = middle;//첫 노드는 미들 노드 

	return 0;
}


void printList(headNode* h) {//노드 출력
	int i = 0;//정수형 변수 생성
	listNode* p;//노드 p 생성

	printf("\n---PRINT\n");//"\n---PRINT\n" 출력

	if(h == NULL) {//헤드 노드가 0이면
		printf("Nothing to print....\n");//출력할게 없음을
		return;
	}

	p = h->first;//노드 p에 첫 리스트 입력

	while(p != NULL) {//p노드가 0이 아닌동안
		printf("[ [%d]=%d ] ", i, p->key);//i와 p노드의 다음값 출력
		p = p->link;//p노드 한칸 이동
		i++;//i에 1추가
	}

	printf("  items = %d\n", i);//최종 갯수 출력
}

