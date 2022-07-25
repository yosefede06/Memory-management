#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Magic numbers
#define AGE_ERROR "ERROR: Age should be an integer between 18 and 120 (includes)\n"
#define STUDENT_ERROR "ERROR: The student's number should be a number\n"
#define GRADE_ERROR "ERROR: Grade should be an integer between 0 and 100 (includes)\n"
#define ARGUMENTS_ERROR "USAGE: Please chose:\n1. 'bubble'\n2. 'quick'\n3. 'best' \n"
#define USER_MESSAGE_STUDENT "Enter student info. Then enter\n"
#define USER_MESSAGE_STUDENT_NUMBER "Enter number of students. Then enter\n"
#define MESSAGE_ID_DIGIT_ERROR "ERROR: Id should includes only digits\n"
#define MESSAGE_ID_ERROR "ERROR: Id must have 10 digits and can not start with 0\n"
#define BEST_STUD_INFO "best student info is: %ld,%d,%d\n"
#define LEN_ID 10
#define TOP_GRADE 100
#define MAX_ROW 60
#define LOWER_GRADE 0
#define LEN_MAX 21
#define LOWER_AGE 18
#define PI 10
#define TOP_AGE 120

typedef struct Student
{
    long int id;
    int grade;
    int age;
}Student;

void best_student(Student *start, Student *end)
{
    Student* max_student = NULL; float maximum = 0;
    for(Student* cur = start; cur != end; cur++)
    {
        float temp = (((float)(cur->grade))/(cur->age));
        if(temp > maximum)
        {
            maximum = temp;
            max_student = cur;
        }
    }
    printf(BEST_STUD_INFO, max_student->id,max_student->grade,max_student->age);
}
void swap(Student *xp, Student *yp)
{
    Student temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubble_sort(Student *start, Student *end)
{
    int k = 0; Student* curr;
    for(curr = start; curr != end; curr++)
    {
        k++;
    }
    int i;
    for (i = 0; i < k-1; i++)
    {

        for (Student* l = start; l < end - i - 1; l++ )
        {
            if ((l+1)->grade < l->grade )
            {
                swap(l, l+1);

            }
        }
    }
    for(Student* curr = start; curr != end; curr++)
    {
        printf("%ld,%d,%d\n", curr->id, curr->grade,curr->age);
    }
}

Student* partition(Student* start, Student* end){
    Student* pivot = end;
    int index_of_smaller = -1;

    for (Student* tmp = start; tmp < end; tmp++){
        if (tmp->grade < pivot->grade){
            index_of_smaller++;
            swap(tmp,start+index_of_smaller);
        }
    }
    swap(pivot,start+index_of_smaller+1);
    return start+index_of_smaller+1;
}
void quick_sort_aux(Student* start, Student* end){
    if (start >= end) return;
    Student* pivot = partition(start, end);
    quick_sort_aux(start, pivot-1);
    quick_sort_aux(pivot+1, end);
}
void quick_sort(Student* start,Student *end){
    quick_sort_aux(start,end-1);
    while(start != end){
        printf("%ld,%d,%d\n", start->id, start->grade,start->age);
        start++;
    }
}
int check_number(char str[])
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int check_id(char id[])
{
    if(!check_number(id))
    {
        printf(MESSAGE_ID_DIGIT_ERROR);
        return 0;
    }
    if(strlen(id) != LEN_ID || id[0] == '0')
    {
        printf(MESSAGE_ID_ERROR);
        return 0;
    }
    return 1;
}
int check_age(char age[])
{
    if(!check_number(age))
    {
        fprintf(stdout, AGE_ERROR);
        return 0;
    }
    else{
        long int value = strtol(age, NULL, PI);
        if(value > TOP_AGE || value < LOWER_AGE)
        {
            fprintf(stdout, AGE_ERROR);
            return 0;
        }
        return 1;
    }
}
int check_grade(char grade[])
{
    if(!check_number(grade))
    {
        printf(GRADE_ERROR);
        return 0;
    }
    else{
        long int val = strtol(grade, NULL, PI);
        if(val < LOWER_GRADE ||
        val > TOP_GRADE)
        {
            fprintf(stdout, GRADE_ERROR);
            return 0;
        }
        return 1;
    }
}
int check_student(char* id, char* grade, char* age){
    if(check_id(id) == 0){
        return 0;}
    if(check_grade(grade) == 0){
        return 0;}
    if(check_age(age) == 0){
        return 0;}
    return 1;
}
Student* student_data(long int* num_of_stud)
{
    int bol = 0; char number_input[MAX_ROW];
    while (bol == 0)
    {
        fprintf(stdout, USER_MESSAGE_STUDENT_NUMBER);
        if(fgets(number_input, MAX_ROW, stdin) != NULL)
        {
            if(number_input[0] == '-' || number_input[0] == '0')
            {
                fprintf(stdout, STUDENT_ERROR);
                continue;
            }
            size_t length_size = strlen(number_input);
            if (length_size > 0){
                if(number_input[length_size-1] == '\n'){
                    number_input[--length_size] = '\0';
                }
            }
            bol = check_number(number_input);
            if (bol == 0)
            {
                fprintf(stdout, STUDENT_ERROR);
            }
        }
        else
        {
            return NULL;
        }
    }
    *num_of_stud = strtol(number_input, NULL, PI);
    Student *student_list =
            (Student *) malloc(*num_of_stud
            * sizeof(Student));
    if (student_list == NULL)
    {
        return NULL;
    }
    int i = 0;
    while (i < *num_of_stud)
    {
        fprintf(stdout, USER_MESSAGE_STUDENT);
        if (fgets(number_input, MAX_ROW, stdin)==NULL)
        {
            free(student_list);
            student_list = NULL;
            return NULL;
        }
        char id[LEN_MAX];
        char grade[LEN_MAX];
        char age[LEN_MAX];
        if (sscanf(number_input, "%20[^,],%20[^,],%20[^,]",
                   id, grade, age) == EOF)
        {
            free(student_list);
            student_list = NULL;
            return NULL;
        }
        size_t length_size = strlen(age);
        if (length_size > 0){
            if(age[length_size-1] == '\n'){
                age[--length_size] = '\0';
            }
        }
        if(check_student(id, grade, age) == 0)
        {
            continue;
        }
        student_list[i].age = strtol(age, NULL, PI);
        student_list[i].grade = strtol(grade, NULL, PI);
        student_list[i].id = strtol(id, NULL, PI);
        i++;
    }
    return student_list;
}
int check_valid_argument(char*argv[], int argc){
    if ((argc == 2) &&  ((strcmp(argv[1], "bubble") == 0) ||
    (strcmp(argv[1], "quick") == 0) || (strcmp(argv[1], "best") == 0))){
        return 0;
    }
    else{
        fprintf(stdout, ARGUMENTS_ERROR);
        return EXIT_FAILURE;
    }
}
int main(int argc, char* argv[]){
    if(check_valid_argument(argv, argc) == 1){
        return EXIT_FAILURE;
    }
    long int num_of_stud = 0;
    Student* arr_of_students = student_data(&num_of_stud);
    if(arr_of_students == NULL)
    {
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "best") == 0)
    {
        best_student(arr_of_students, arr_of_students + num_of_stud);
    }
    if (strcmp(argv[1], "quick") == 0)
    {
        quick_sort(arr_of_students, arr_of_students + num_of_stud);
    }
    if (strcmp(argv[1], "bubble") == 0)
    {
        bubble_sort(arr_of_students, arr_of_students + num_of_stud);
    }
    free(arr_of_students);
    return EXIT_SUCCESS;
}