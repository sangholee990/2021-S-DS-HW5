#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10  //스택의최대 크기 지정 
#define MAX_EXPRESSION_SIZE 20 // 연산자 까지 포함한 최대 사이즈  


typedef enum{
	lparen = 0, 
	rparen = 9,  
	times = 7,   
	divide = 6,  
	plus = 5,    
	minus = 4,   
	operand = 1
} precedence; //연산자 우선순위 구조체  

char infixExp[MAX_EXPRESSION_SIZE];  //infix식 저장배열 선언  
char postfixExp[MAX_EXPRESSION_SIZE]; //postfix식 저장배열 선언 
char postfixStack[MAX_STACK_SIZE]; //연산자 스택 배열 선언 
int evalStack[MAX_STACK_SIZE];	// 계산 스택 배열 

int postfixStackTop = -1; //postfix의 top을 -1로 초기화 
int evalStackTop = -1;	//evalStack의 top을 -1로 초기화  

int evalResult = 0;	 //evaluation 계산 결과값 저장 전역 변수 선언 

void postfixpush(char x); //postfix에 문자 push하는 함수 
char postfixPop(); //postfix에 pop을 해서 값을 가져오는 함수 
void evalPush(int x);//evalstack배열에 값 푸쉬하는 함수 
int evalPop();//evalstack에 pop을 하는 함수 
void getInfix(); // infixexp 를 사용자로 부터 받는 함수 
precedence getToken(char symbol); // 문자를 입력받아 precedence enum 리턴 받는 함수 
precedence getPriority(char x); //우선순위 받는 함수 
void charCat(char* c); // 문자를 postfixexp에 넣는 함수 
void toPostfix(); //중위연산식을 후위연산식으로 변경하는 함수 
void debug();// 현재 정보 출력 함수 
void reset(); // 초기화 함수  
void evaluation(); // postfix로 변환된 식을 연산 하는 함수 

int main()
{   

    printf("[----- [이상호] [2018038016] -----]\n");
	char command;
    
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix(); //중위 연산식 입력 받기 
			break;
		case 'p': case 'P':
			toPostfix(); // infix->postfix로 바꾸기 
			break;
		case 'e': case 'E':
			evaluation(); //후위 연산식 계산하기 
			break;
		case 'd': case 'D':
			debug(); //디버깅 
			break;
		case 'r': case 'R':
			reset(); //모두 리셋 
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //stacktop인덱스 1증가후 stacktop에 x값 저장  
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //postfixstack이 비었으면 pop이 불가능 하기때문에 
        return '\0'; // 리턴 널; 
    else { //postfixstack에 값이 있다면 
    	x = postfixStack[postfixStackTop--]; // stacktop값을 x에 저장후 인덱스 1감소 
    }
    return x; //x 리턴 
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //stacktop인덱스 1증가후 stacktop에 x값 저장 
}

int evalPop()
{
    if(evalStackTop == -1) //evalstack이 비어있을 경우 
        return -1; // -1 리턴 
    else
        return evalStack[evalStackTop--]; //stacktop의 인덱스 값 리턴후 1 감소 
}


void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //중위연산식 사용자로 부터 입력 받음  
}

precedence getToken(char symbol)
{
	switch(symbol) { 
	case '(' : return lparen; //여는 괄호 인경우 lparen 리턴 
	case ')' : return rparen;//닫는  괄호 인경우 rparen 리턴
	case '+' : return plus;//더하기 인경우 plus 리턴
	case '-' : return minus;//빼기  인경우 minus 리턴
	case '/' : return divide;//나누기 인경우 divide 리턴
	case '*' : return times;//곱하기 인경우 times 리턴
	default : return operand;// 피연산자 인경우 operand 리턴
	}
}

precedence getPriority(char x) 
{
	return getToken(x); //우선순위 를 리턴받는다. 
}


void charCat(char* c)
{
	if (postfixExp == '\0') //postfixexp가 비어있다면  
		strncpy(postfixExp, c, 1); // c 를 덮어 씌운다 
	else // 비어있지 않다면 
		strncat(postfixExp, c, 1); // c를 이어 붙인다 
}

void toPostfix()
{
	char *exp= infixExp; //infixexp를 가리키는 포인터 변수 exp 선언 
	
	char x; //문자 조각 저장 변수  
	char p; //pop값 담을 변수 
	
	while(*exp != '\0')
	{
		x= *exp;
			
		if(getPriority(x)==1){ //x가 피연산자 일 경우 
		    charCat(&x); // x를 postfixExp에 저장 
	    }
	    
		else //피연산자 아닐경우 
		{
			
			if(getPriority(x)==9) //닫는 괄호를 만날 경우 
			{
				while(postfixStack[postfixStackTop] !='('){ //여는 괄호 만날때까지 
					p=postfixPop(); // pop해주고 p에 저장 
					charCat(&p); //p값 postfixExp 에 push 
				}
				postfixPop(); // '(' pop 
			}
			else if(getPriority(x)==0){ // 여는 괄호를 만났을 경우 
				postfixPush(x++);
			}
			// 연산자를 만났을 경우 
			/*infixexp 연산자가 postfixstacktop보다 작거나 같으면*/
			else if (getPriority(x)<=getPriority(postfixStack[postfixStackTop])) { 
				p=postfixPop(); //pop해주고  
				charCat(&p); //postfixExp 에 push 
				postfixPush(x);
			}
			else
			{
				postfixPush(x); 
			}
			
			 
	    }    
	    exp++; // 다음원소 탐색 
	}
	
	while(postfixStackTop != -1) //stacktop이 [1]이 될때 까지 
	{
		p=postfixPop();  //남은 요소 전부 pop 
		charCat(&p); // postfixExp에 push 
	}
	
}   
void debug()
{
	int i;
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult); //infixexp ,postfixexp,evalresult 현재 상태 출력 
    
	printf("postfixStack : ");
	for(i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);  //postfixstack 출력 

	printf("\n");

}

void reset()
{
	int i;
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;   // 모든 값들을 초기값으로 설정한다 
}

void evaluation()
{
    char *exp = postfixExp; // postfixExp 가리키는 포인터 선언 
    
    int a,b; // 피연산자  변수 선언  
    int x; // switch 구분  변수  선언 
    
    while(*exp != '\0') 
    {
    	  x=getPriority(*exp); // 문자 구분저장 
    	  
    	  if(getPriority(*exp)==1){
    	  	     evalPush(*exp-48); //아스키코드에서 48을 빼면 원하는 숫자를 얻는다  
		  }
		  else{ // *exp가 가리키기는 값이 연산자 일경우 
		  	    
		  	    a=evalPop();
		  	    b=evalPop(); // pop하여 a b 에 넣는다
				  
				switch(x){
					case 7: // 곱하기 연산자 일경우 
						evalPush(b*a);
						break;
					case 6: // 나누기 연산자 일경우 
					    evalPush(b/a);
					    break;
					case 5://더하기 연산자 일경우 
					    evalPush(b+a);
					    break;
					case 4:	//빼기 연산자 일경우 
					    evalPush(b-a);
					    break;
				}  
				x=0;    
		  } 
		  exp++;// 다음원소 계산 
	}
	evalResult = evalStack[evalStackTop]; //evalstack배열의 top에 연산결과가 축적됐다 
}
