#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

// 큐 구조체 정의
typedef struct {
    QueueNode* Top;
    int size;
} Queue;

// 큐 초기화 함수
void init_queue(Queue* list) {
    list->Top = NULL;
    list->size = 0;
}

// 노드 구조체 정의
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// 스택 구조체 정의
typedef struct {
    StackNode* Top;
    int size;
} Stack;

// 스택 초기화 함수
void init_stack(Stack* list) {
    list->Top = NULL;
    list->size = 0;
}

// 큐 Enqueue 함수
void Enqueue(Queue* list, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = list->Top;
    list->Top = newNode;
    list->size++;
}

// 스택 push 함수
void push(Stack* list, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = list->Top;
    list->Top = newNode;
    list->size++;
}

// 문자열 길이 직접 구하기 (string.h 대체)
int get_length(char *s) {
    int len = 0;
    while (s[len] != '\0' && s[len] != '\n') {
        len++;
    }
    return len;
}

// 스택과 큐를 이용한 팰린드롬 체크 함수
int str_check(char *s1, int n) {
    Stack s;
    Queue q;
    init_stack(&s);
    init_queue(&q);

    // 문자들을 스택과 큐에 삽입
    for (int i = 0; i < n; i++) {
        push(&s, s1[i]);
        Enqueue(&q, s1[i]);
    }

    // 스택과 큐에서 데이터를 꺼내며 비교
    StackNode *s_ptr = s.Top;
    QueueNode *q_ptr = q.Top;
    
    int left = 0;
    int right = n - 1;
    while (left < right) {
        if (s1[left] != s1[right]) {
            return -1;
        }
        left++;
        right--;
    }
    return 1;
}

int main() {
    char str[105];
    int num, i = 0;

    // 문자열 입력 받기
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 0;
    }

    i = get_length(str);

    if (i >= 100 || i < 0) {
        printf("ERROR\n");
    } else {
        num = str_check(str, i);
        if (num == 1) {
            printf("Palindrome\n");
        } else {
            printf("not a palindrome\n");
        }
    }

    return 0;
}