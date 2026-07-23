#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 연결 리스트 구조체 정의
typedef struct {
    Node* Top;
    int size;
}Stack;

// 리스트 초기화 함수
void init_list(Stack* list) {
    list->Top = NULL;
    list->size = 0;
}

// 리스트 길이 반환
int size(Stack* list) {
    return list->size;
}

void printStack(Stack* list) {
    Node* curr = list->Top;
    printf("List: ");
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL (length: %d)\n", list->size);
}

//추가
void push(Stack* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->Top;
    list->Top = newNode;
    list->size++;
}
//Stack이 빈 것인지 판단하는 함수
void isEmpty(Stack* list){
    if (list->Top == NULL) {
        printf("false\n");
        return;
    }
    else{
        printf("true\n");
    }
}
//Stack의 top의 값을 출력하는 코드
int top(Stack* list){
    if (list->Top == NULL) {
        printf("Stack is empty\n");
        return 0;
    }
    else{
        printf("top : %d\n",list->Top->data);
        return 0;
    }
}


//맨 아래의 값을 삭제하는 합수
void pop(Stack* list) {
    if (list->Top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    if (list->Top->next == NULL) {
        printf("%d",list->Top->data);
        free(list->Top);
        list->Top = NULL;
    } else {
        Node* prev = NULL;
        Node* curr = list->Top;
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        printf("%d",curr->data);
        prev->next = NULL;
        free(curr);
    }
    list->size--;
}




// 명령어 문자열 비교 함수
int cmd_check(char *s1) {
    char* cmd[] = {
        "exit",         //  0
        "push",         //  1
        "pop",          //  2
        "size",         //  3
        "top",          //  4
        "isEmpty",      //  5
        "printStack"    //  6
    };
    
    for (int i = 0; i < 7; i++) {
        char *p1 = s1;
        char *p2 = cmd[i];
        
        while (*p1 && (*p1 == *p2)) {
            p1++;
            p2++;
        }
        
        if (*p1 == '\0' && *p2 == '\0') {
            return i; 
        }
    }
    
    return -1; 
}

int main() {  
    Stack list;
    init_list(&list);
    int val;
    char str[50];

    while (1) {
        printf("\n========================================\n");
        printf(" Available Commands:\n");
        printf("-exit\n-push\n-pop\n-size\n-top\n-isEmpty\n-printStack\n");
        printf("========================================\n");
        printf("Enter command: ");
        scanf("%s", str); 
        
        int result = cmd_check(str);
        
        switch (result) {
            case 0: 
                printf("Ending the program\n");
                return 0;
            case 1:
            printf("Enter integer data to Stack: ");
                scanf("%d", &val);
                push(&list, val);
                break;
            case 2:
                pop(&list);
                break;
            case 3:
                printf("Current total stack length: %d\n", size(&list));
                break;  
            case 4:
                top(&list);
                break;
            case 5:
                isEmpty(&list);
                break;
            case 6:
                printStack(&list);
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    }

    return 0;
}