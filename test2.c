#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Course_t *Course;

struct Course_t
{
    int number;
    int size;
};

int main()
{
    Course *std = (Course *)malloc(2 * sizeof(Course));
    std[0] = (Course)malloc(sizeof(Course));
    std[1] = (Course)malloc(sizeof(Course));
    std[0]->number = 5;
    std[0]->size = 7;
    std[1]->number = 23;
    std[1]->size = 1;
    printf("number is %d, size is %d\n", std[0]->number, std[0]->size);
    printf("number is %d, size is %d\n", std[1]->number, std[1]->size);
    free(NULL);
    int *a;
    // free(a);
    printf("XasdasdD");
}