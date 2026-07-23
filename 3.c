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
}Queue;

// 리스트 초기화 함수
void init_list(Queue* list) {
    list->Top = NULL;
    list->size = 0;
}

// 리스트 길이 반환
int size(Queue* list) {
    return list->size;
}

//Queue 출력
void printQueue(Queue* list) {
    Node* curr = list->Top;
    printf("List: ");
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL (length: %d)\n", list->size);
}

//추가
void Enqueue(Queue* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->Top;
    list->Top = newNode;
    list->size++;
}

void isEmpty(Queue* list){
    if (list->Top == NULL) {
        printf("false\n");
        return;
    }
    printf("true\n");

}
//마지막 값 확인
void rear(Queue* list) {
    if (list->Top == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("rear : %d\n",list->Top->next->data);
}
//맨 앞 값 확인
void front(Queue* list){
    if (list->Top == NULL) {
        printf("Queue is empty\n");
        return ;
    }
     printf("front : %d\n",list->Top->data);
}


//맨앞 삭제
void Dequeue(Queue* list) {
    if (list->Top == NULL) {
        printf("Error: List is empty\n");
        return;
    }
    printf("Dequeue : %d",list->Top->data);
    Node* temp = list->Top;
    list->Top = temp->next;
    free(temp);
    list->size--;
}




// 명령어 문자열 비교 함수
int cmd_check(char *s1) {
    char* cmd[] = {
        "exit",      //  0
        "Enqueue",   //  1
        "Dequeue",   //  2
        "size",      //  3
        "front",     //  4
        "rear",      //  5
        "isEmpty",   //  6
        "printQueue" //  7
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
    Queue list;
    init_list(&list);
    int val;
    char str[50];

    while (1) {
        printf("\n========================================\n");
        printf(" Available Commands:\n");
        printf("-exit\n-Enqueue\n-Dequeue\n-size\n-front\n-top\n-rear\n-isEmpty\n-printQueue\n");
        printf("========================================\n");
        printf("Enter command: ");
        scanf("%s", str); 
        
        int result = cmd_check(str);
        
        switch (result) {
            case 0: 
                printf("Ending the program\n");
                return 0;
            case 1:
            printf("Enter integer data to Queue: ");
                scanf("%d", &val);
                Enqueue(&list, val);
                break;
            case 2:
                Dequeue(&list);
                break;
            case 3:
                printf("Current total Queue length: %d\n", size(&list));
                break;  
            case 4:
                front(&list);
                break;
            case 5:
                rear(&list);
                break;
            case 6:
                isEmpty(&list);
                break;
            case 7:
                printQueue(&list);
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    }

    return 0;
}