#include <stdio.h>
#include <stdlib.h>

typedef struct Address
{
    char Co[20];
    char Do[20];
    char Si[20];
    char Gu[20];
} Address;

typedef struct
{
    int number;
    char name[20];
    Address *cdsg;
    int grade;
} Student;

// 문자열 비교 함수
int my_strcmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(char *)s1 - *(char *)s2;
}

// 하위명령어 체크 함수
int cmd_check(char *s1) {
    char* cmd[] = {
        "number",       // 0
        "name",         // 1
        "score",        // 2
        "Address",      // 3
        "Country",      // 4
        "Province",     // 5
        "City",         // 6
        "gu District"   // 7
    };
    
    for (int i = 0; i < 8; i++) {
        if (my_strcmp(s1, cmd[i]) == 0) {
            return i; 
        }
    }
    return -1; 
}

// 검색 함수 
int find_matching_indices(Student *list, int count, int type, int *match_indices) {
    int match_count = 0;

    if (type == 0 || type == 2) {
        int target_num;
        printf("Enter target number: ");
        scanf("%d", &target_num);
        
        for (int i = 0; i < count; i++) {
            if ((type == 0 && list[i].number == target_num) || 
                (type == 2 && list[i].grade == target_num)) {
                match_indices[match_count++] = i;
            }
        }
    } else {
        char target_str[50];
        printf("Enter target string: ");
        scanf("%s", target_str);
        
        for (int i = 0; i < count; i++) {
            int match = 0;
            if (type == 1 && my_strcmp(list[i].name, target_str) == 0) match = 1;
            else if (type == 3 && my_strcmp(list[i].cdsg->Co, target_str) == 0) match = 1;
            else if (type == 4 && my_strcmp(list[i].cdsg->Do, target_str) == 0) match = 1;
            else if (type == 5 && my_strcmp(list[i].cdsg->Si, target_str) == 0) match = 1;
            else if (type == 6 && my_strcmp(list[i].cdsg->Gu, target_str) == 0) match = 1;
            
            if (match) {
                match_indices[match_count++] = i;
            }
        }
    }
    return match_count;
}

// 학생 추가
void Add_students(Student *list, int *count, int max) {
    if (*count >= max) {
        printf("List is full!\n");
        return;
    }
    
    list[*count].cdsg = (Address *)malloc(sizeof(Address));
    if (list[*count].cdsg == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Enter number, name, Country, Province, City, gu District, score: ");
    scanf("%d %s %s %s %s %s %d", 
          &(list[*count].number), 
          list[*count].name, 
          list[*count].cdsg->Co, 
          list[*count].cdsg->Do, 
          list[*count].cdsg->Si, 
          list[*count].cdsg->Gu, 
          &(list[*count].grade));
    
    (*count)++;
    printf("Student added successfully.\n");
}

// 특정 인덱스의 학생 삭제 처리 내부 함수
void remove_student_at(Student *list, int *count, int index) {
    free(list[index].cdsg);
    for (int i = index; i < *count - 1; i++) {
        list[i] = list[i + 1];
    }
    (*count)--;
    printf("Student deleted successfully.\n");
}

int sev_cmd(int i);

// 학생 삭제 
void Delete_students(Student *list, int *count) {
    if (*count == 0) {
        printf("No students to delete.\n");
        return;
    }
    
    int delete_type = sev_cmd(0);
    if (delete_type < 0) return;

    int match_indices[100];
    int match_count = find_matching_indices(list, *count, delete_type, match_indices);
    
    // 결과 처리 및 삭제
    if (match_count == 0) {
        printf("Student not found.\n");
    } else if (match_count == 1) {
        remove_student_at(list, count, match_indices[0]);
    } else {
        printf("\nMultiple students found (%d items):\n", match_count);
        for (int i = 0; i < match_count; i++) {
            int idx = match_indices[i];
            printf("[%d] Number: %d, Name: %s, Score: %d, Address: %s %s %s %s\n", 
                   i, list[idx].number, list[idx].name, list[idx].grade,
                   list[idx].cdsg->Co, list[idx].cdsg->Do, 
                   list[idx].cdsg->Si, list[idx].cdsg->Gu);
        }
        
        int choice;
        printf("Enter the index [0-%d] of the student to delete: ", match_count - 1);
        scanf("%d", &choice);
        
        if (choice >= 0 && choice < match_count) {
            remove_student_at(list, count, match_indices[choice]);
        } else {
            printf("Invalid selection.\n");
        }
    }
}

//조건에 맞는 순서대로 정렬
void Sorting_students(Student *list, int count, int sort_type) {
    if (count < 2) return;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int condition = 0;
            switch (sort_type) {
                case 0: condition = (list[j].number > list[j + 1].number); break;
                case 1: condition = (my_strcmp(list[j].name, list[j + 1].name) > 0); break;
                case 2: condition = (list[j].grade > list[j + 1].grade); break;
                case 3: condition = (my_strcmp(list[j].cdsg->Co, list[j + 1].cdsg->Co) > 0); break;
                case 4: condition = (my_strcmp(list[j].cdsg->Do, list[j + 1].cdsg->Do) > 0); break;
                case 5: condition = (my_strcmp(list[j].cdsg->Si, list[j + 1].cdsg->Si) > 0); break;
                case 6: condition = (my_strcmp(list[j].cdsg->Gu, list[j + 1].cdsg->Gu) > 0); break;
            }
            if (condition) {
                Student temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    printf("Students sorted successfully.\n");
}

//찾는 학생을 찾고 출력하는 함수
void Finding_students(Student *list, int count, int find_type) {
    if (find_type < 0) return;

    int match_indices[100];
    int match_count = find_matching_indices(list, count, find_type, match_indices);

    if (match_count == 0) {
        printf("Student not found.\n");
    } else {
        for (int i = 0; i < match_count; i++) {
            int idx = match_indices[i];
            printf("Found - Number: %d, Name: %s, Score: %d, Address: %s %s %s %s\n", 
                   list[idx].number, list[idx].name, list[idx].grade,
                   list[idx].cdsg->Co, list[idx].cdsg->Do, 
                   list[idx].cdsg->Si, list[idx].cdsg->Gu);
        }
    }
}
//파일 저장
void Save_file(Student *list, int count) {
    FILE *file = fopen("attendance.txt", "w");
    if (!file) return;
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %s %s %s %d\n", 
                list[i].number, list[i].name, 
                list[i].cdsg->Co, list[i].cdsg->Do, 
                list[i].cdsg->Si, list[i].cdsg->Gu, 
                list[i].grade);
    }
    fclose(file);
    printf("Data saved to file.\n");
}
//파일 불려오기
void Importing_file(Student *list, int *count) {
    FILE *file = fopen("attendance.txt", "r");
    if (!file) {
        printf("No saved file found.\n");
        return;
    }
    for (int i = 0; i < *count; i++) {
        free(list[i].cdsg);
    }
    fscanf(file, "%d", count);
    for (int i = 0; i < *count; i++) {
        list[i].cdsg = (Address *)malloc(sizeof(Address));
        fscanf(file, "%d %s %s %s %s %s %d", 
                &(list[i].number), list[i].name, 
                list[i].cdsg->Co, list[i].cdsg->Do, 
                list[i].cdsg->Si, list[i].cdsg->Gu, 
                &(list[i].grade));
    }
    fclose(file);
    printf("Data imported from file.\n");
}

//명령어 함수
int main_cmd_check(char *s1) {
    char* cmd[] = {
        "exit",             // 0
        "Add_students",     // 1
        "Delete_students",  // 2
        "Sorting_students", // 3
        "Finding_students", // 4
        "Save_file",        // 5
        "Importing_file",   // 6
        "Auto_save_mode"    // 7
    };
    
    for (int i = 0; i < 8; i++) {
        if (my_strcmp(s1, cmd[i]) == 0) {
            return i; 
        }
    }
    return -1; 
}

//하위 명령어 함수
int sev_cmd(int i) {
    int sev_result;
    char sev_str[50];
    if (i == 0) {
        printf("\n========================================\n");
        printf(" Available Commands:\n");
        printf("-number\n-name\n-score\n-Address\n");
        printf("========================================\n");
        printf("Enter command: ");
        scanf("%s", sev_str); 
    } else {
        printf("\n========================================\n");
        printf(" Available Commands:\n");
        printf("-Country\n-Province\n-City\n-gu District\n");
        printf("========================================\n");
        printf("Enter command: ");
        while (getchar() != '\n');
        scanf("%[^\n]", sev_str);
    }   
    
    sev_result = cmd_check(sev_str);
    switch (sev_result) {
        case 0: return 0; // number
        case 1: return 1; // name
        case 2: return 2; // score
        case 3: return sev_cmd(1); // Address 
        case 4: return 3; // Country
        case 5: return 4; // Province
        case 6: return 5; // City
        case 7: return 6; // gu District
        default:
            printf("Invalid input. Please try again.\n");
            return -1;
    }
}

int main() { 
    int max_students = 100;
    Student *student_list = (Student *)malloc(sizeof(Student) * max_students);
    int student_count = 0;
    
    char main_str[50];
    int Auto_save_mode = 0;
    int main_result;

    while (1) {
        printf("\n========================================\n");
        printf(" Available Commands:\n");
        printf("-exit\n-Add_students\n-Delete_students\n-Sorting_students\n-Finding_students\n-Save_file\n-Importing_file\n-Auto_save_mode : ");
        if (Auto_save_mode == 1) {
            printf("ON\n");
        } else {
            printf("OFF\n");
        }
        printf("========================================\n");
        printf("Enter command: ");
        scanf("%49s", main_str); 
        
        main_result = main_cmd_check(main_str);
        
        switch (main_result) {
            case 0: 
                printf("Ending the program\n");
                for (int i = 0; i < student_count; i++) free(student_list[i].cdsg);
                free(student_list);
                return 0;
            case 1:
                Add_students(student_list, &student_count, max_students);
                break;
            case 2:
                Delete_students(student_list, &student_count);
                break;  
            case 3: {
                int sort_type = sev_cmd(0);
                if (sort_type >= 0) Sorting_students(student_list, student_count, sort_type);
                break;
            }
            case 4: {
                int find_type = sev_cmd(0);
                if (find_type >= 0) Finding_students(student_list, student_count, find_type);
                break;
            }
            case 5:
                Save_file(student_list, student_count);
                break;
            case 6:
                Importing_file(student_list, &student_count);
                break;
            case 7:
                Auto_save_mode = !Auto_save_mode;
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
        if (Auto_save_mode == 1) {
            Save_file(student_list, student_count);
        }
    }

    return 0;
}