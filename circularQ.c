#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // 배열에 들어갈 요소 char 형 변수 선언 
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // 큐 배열과 front , rear 구조체로 묶어서 선언 


QueueType *createQueue(); // 큐에 대한 배열을 동적할당하여 만드는 함수 
int freeQueue(QueueType *cQ); // 동적할당 해제 함수 
int isEmpty(QueueType *cQ); //큐배열이 비었는지 확인 하는 함수 
int isFull(QueueType *cQ); //큐 배열이 꽉찼는지 확인 하는 함수 
void enQueue(QueueType *cQ, element item); // 큐에 요소 추가하는 함수 
void deQueue(QueueType *cQ, element* item); // 큐 요소 제거하는 함수 
void printQ(QueueType *cQ); //큐 요소 전부 출력 
void debugQ(QueueType *cQ); // front, rear ,요소 상태 출력 
element getElement(); // 요소 입력 받는 함수 

int main(void)
{
	QueueType *cQ = createQueue(); // 큐 동적 할당 후 *cQ에 큐 배열 연결 
	element data; // 원소 입력 변수 선언 
	char command; // 명령 변수  
    
    printf("[----- [이상호] [2018038016] -----]");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': //원소를 넣는 명령 
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //원소 제거 명령 
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':// 원소 출력 명령 
			printQ(cQ);
			break; 
		case 'b': case 'B': //큐 의 현재 상태 출력 명령 
			debugQ(cQ);
			break;
		case 'q': case 'Q': // 프로그램 중단 명령 
   	        freeQueue(cQ); //동적 할당 해제 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); // cQ 동적 할당 
	cQ->front = 0; //front 값 0으로 초기화  
	cQ->rear = 0; // rear 값 0으로 초기화 
	return cQ; //cQ 를 리턴한다 
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //cQ가 비었으면 free하지 않고 1을 리턴 
    free(cQ); // cQ 동적할당을 해제 
    return 1; //1리턴 
}

element getElement() 
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;  //요소 입력 받고 리턴 
}


/* complete the function */
int isEmpty(QueueType *cQ)
{   
    if(cQ->rear==cQ->front){  //머리와 꼬리가 같은 곳을 가리키면 큐는 비어있는 상태이다. 
    	return 1; // 원소 비어있을때  1리턴 
    }
	else{
        return 0;
    }
}

/* complete the function */
int isFull(QueueType *cQ)
{
   if(cQ->front==((cQ->rear+1)%MAX_QUEUE_SIZE)){ //꼬리가 돌아서 머리와 같은곳을 가리키면 꽉찬상태이다 
   	  return 1; //큐가 가득찼으면 1을 리턴 
   }
   else{ // 큐가 가득차지 않았으면 
   return 0; //정상 종료 
   }
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)==1){ //큐가 꽉찼으면 
		printf("Q is full"); //큐가 꽉찼음을 알림  
	}
	else{
		cQ->rear=((cQ->rear)+1)% MAX_QUEUE_SIZE; // rear값을 증가 시킨다 
		cQ->queue[cQ->rear]=item; //큐에 빈공간(rear인덱스 자리)에 원소를 집어넣는다 
	}
	
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)==1){ 
		printf("Q is empty"); //비었음을 알림 
    }
    else{
    	cQ->front=((cQ->front)+1)% MAX_QUEUE_SIZE; //front 값을 증가시킨다  
	cQ->queue[cQ->front] = '\0'; ////front 인덱스에 있는 값을 없앤다.    
	}

}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first 값 하나 증가 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // rear값 하나 증가 

	printf("Circular Queue : [");

	i = first; // i에 first 값 대입 
	while(i != last){ //first == last 까지 원소 출력 
		printf("%3c", cQ->queue[i]); 
		i = (i+1)%MAX_QUEUE_SIZE; //i 를 하나 씩 증가 

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
    int i;
	printf("\n---DEBUG\n");
	for(i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { //i == front 일때 front 명시 
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //큐 요소 순서대로 출력 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front rear값 출력 
}
