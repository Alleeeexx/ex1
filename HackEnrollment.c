#include "HackEnrollment.h"
#include "IsraeliQueue.h"
#include <string.h>

struct Student_t
{
    unsigned int id;
    unsigned int credits;
    unsigned int gpa;
    char *name;
    char *surname;
    char *city;
    char *department;
};

struct Course_t
{
    int number;
    int size;
    IsraeliQueue queue;
};

struct Hacker_t
{
    Student student;
    int *courses;
    int *friends;
    int *enemies;
};

struct EnrollmentSystem_t
{
    Student *students;
    Course *courses;
    Hacker *hackers;
};

/*
create functions for various structs
*/
Student createStudent(unsigned int id, unsigned int credits, unsigned int gpa,
                      char *name, char *surname, char *city, char *deparment);
Course createCourse(int number, int size);
Hacker createHacker(Student student, int *courses, int *friends, int *enemies);

/*
free functions for various structs
*/
void freeStudent(Student student);
void freeCourse(Course course);
void freeHacker(Hacker hacker);
void freeEnrollmentSystem(EnrollmentSystem sys);

/*
read and other functions for various files
*/
Student *readStudents(FILE *students);
Hacker *readHackers(FILE *hackers);
Course *readCourses(FILE *courses);
int findLines(FILE *file);
int findStringLength(FILE *file);
int findArgsInLine(FILE *file);

EnrollmentSystem createEnrollment(FILE *students, FILE *courses, FILE *hackers)
{
    if (students == NULL || courses == NULL || hackers == NULL)
    {
        return NULL;
    }
    EnrollmentSystem sys = (EnrollmentSystem)malloc(sizeof(EnrollmentSystem));
    if (sys == NULL)
    {
        return NULL;
    }
}

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE *queues);

void hackEnrollment(EnrollmentSystem sys, FILE *out);

/*
finds the number of lines in a file, useful for getting number of students, queues, etc...
(seems to work so thats good)
*/
int findLines(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    int lines = 0;
    rewind(file);
    char currentChar = fgetc(file);
    while (currentChar != EOF)
    {
        if (currentChar == '\n')
        {
            lines++;
        }
        currentChar = fgetc(file);
    }
    rewind(file);
    return lines;
}

/*
finds how many charachters until the next space or \n or EOF
and points the pointer to the start of the string it counted
*/
int findStringLength(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    int length = 0;
    char c = fgetc(file);
    if (c == ' ')
    {
        c = fgetc(file);
    }
    while (c != ' ' && c != '\n' && c != EOF)
    {
        length++;
        c = fgetc(file);
    }
    fseek(file, -(length + 1), SEEK_CUR);
    return length;
}

Student createStudent(unsigned int id, unsigned int credits, unsigned int gpa,
                      char *name, char *surname, char *city, char *deparment)
{
    Student student = (Student)malloc(sizeof(Student));
    if (student == NULL)
    {
        return NULL;
    }
    student->id = id;
    student->credits = credits;
    student->gpa = gpa;
    student->name = name;
    student->surname = surname;
    student->city = city;
    student->department = deparment;
    return student;
}

void freeStudent(Student student)
{
    if (student == NULL)
    {
        return;
    }
    free(student->name);
    free(student->surname);
    free(student->city);
    free(student->department);
    free(student);
}

Student *readStudents(FILE *studentsFile)
{
    if (studentsFile == NULL)
    {
        return NULL;
    }
    int studentAmount = findLines(studentsFile);
    Student *students = (Student *)malloc(studentAmount * sizeof(Student));
    if (students == NULL)
        return NULL;
    unsigned int id, credits, gpa, length;
    char *name, *surname, *city, *department;
    for (int i = 0; i < studentAmount; i++)
    {
        fscanf(studentsFile, "%d %d %d", &id, &credits, &gpa);
        length = findStringLength(studentsFile);
        name = malloc((length + 1) * sizeof(char));
        fgets(name, length + 1, studentsFile);
        length = findStringLength(studentsFile);
        surname = malloc((length + 1) * sizeof(char));
        fgets(surname, length + 1, studentsFile);
        length = findStringLength(studentsFile);
        city = malloc((length + 1) * sizeof(char));
        fgets(city, length + 1, studentsFile);
        length = findStringLength(studentsFile);
        department = malloc((length + 1) * sizeof(char));
        fgets(department, length + 1, studentsFile);
        if (name == NULL || surname == NULL || city == NULL || department == NULL)
        {
            free(name);
            free(surname);
            free(city);
            free(department);
            for (int j = 0; j < i; i++)
            {
                freeStudent(students[j]);
            }
            return NULL;
        }
        students[i] = createStudent(id, credits, gpa, name, surname, city, department);
        if (students[i] == NULL)
        {
            for (int j = 0; j < i; i++)
            {
                freeStudent(students[j]);
            }
            return NULL;
        }
    }
    return students;
}

Course createCourse(int number, int size)
{
    Course course = (Course)malloc(sizeof(Course));
    if (course == NULL)
    {
        return NULL;
    }
    course->number = number;
    course->size = size;
    course->queue = NULL;
    return course;
}

void freeCourse(Course course)
{
    if (course == NULL)
    {
        return NULL;
    }
    // freeIsraeliQueue(course->queue) <---------BRUH MOMENTO
    free(course);
}

Course *readCourses(FILE *coursesFile)
{
    if (coursesFile == NULL)
    {
        return NULL;
    }
    int courseAmount = findLines(coursesFile);
    Course *courses = (Course *)malloc(courseAmount * sizeof(Student));
    if (courses == NULL)
        return NULL;
    int number, size;
    for (int i = 0; i < courseAmount; i++)
    {
        fscanf(coursesFile, "%d %d", &number, &size);
        courses[i] = createCourse(number, size);
        if (courses[i] == NULL)
        {
            for (int j = 0; j < i; i++)
            {
                freeCourse(courses[j]);
            }
            return NULL;
        }
    }
    return courses;
}

Hacker createHacker(Student student, int *courses, int *friends, int *enemies)
{
    Hacker hacker = (Hacker)malloc(sizeof(Hacker));
    if (hacker == NULL)
    {
        return NULL;
    }
    hacker->student = student;
    hacker->courses = courses;
    hacker->friends = friends;
    hacker->enemies = enemies;
    return hacker;
}

void freeHacker(Hacker hacker)
{
    if (hacker == NULL)
    {
        return NULL;
    }
    free(hacker->courses);
    free(hacker->friends);
    free(hacker->enemies);
    free(hacker);
}

Hacker *readHackers(FILE *hackersFile)
{
    if (hackersFile == NULL)
    {
        return NULL;
    }
    int hackerAmount = findLines(hackersFile) / 4;
    Hacker *hackers = (Hacker *)malloc(hackerAmount * sizeof(Hacker));
    if (hackers == NULL)
        return NULL;
    for (int i = 0; i < hackerAmount; i++)
    {
    }
}