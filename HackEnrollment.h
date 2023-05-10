#ifndef PROVIDED_HACKENROLLMENT_H
#define PROVIDED_HACKENROLLMENT_H

#include <stdio.h>

#define FRIENDSHIP_THRESHOLD 20
#define ENEMY_THRESHOLD 0
#define FRIENDS 20
#define ENEMIES -20
#define NEUTRAL 0
#define ID_LENGTH 9

typedef struct EnrollmentSystem_t *EnrollmentSystem;
typedef struct Student_t *Student;
typedef struct Course_t *Course;
typedef struct Hacker_t *Hacker;

/*
Creates EnrollmentSystem that will contain the students and courses.
Incase of an error returns NULL.
*/
EnrollmentSystem createEnrollment(FILE *students, FILE *courses, FILE *hackers);

/*
Reads the file that describes the queues, returns EnrollmentSystem that represents them.
Incase of an error returns NULL. The function may change sys.
*/
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE *queues);

/*
Writes to out new queues (based on the order in courses file) in which the hackers are at place < Size
in both courses that they asked, or the message:
Cannot satisfy constraints for <Student ID>
When the ID number belongs to the first hacker that didn't get both courses he asked for, based on
the hackers order in the hackers file.
A hacker that asked for 1 course and didn't get in it, will fail the process.
*/
void hackEnrollment(EnrollmentSystem sys, FILE *out);

#endif // PROVIDED_HACKENROLLMENT_H