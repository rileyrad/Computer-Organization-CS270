/* CS270 
 *
 * Author: Riley Radici
 * Date:   2/12/2020
 */

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
    Student* newStudent = (Student*) malloc(sizeof(Student));
    scanf("%s", newStudent -> firstName);
    scanf("%f", &(newStudent -> qualityPoints));
    scanf("%d", &(newStudent -> numCredits));
    *slot = newStudent;
}

void displayStudent(Student s)
{
    float GPA = s.qualityPoints / s.numCredits;
    printf("%s, %.2f\n", s.firstName, GPA);
}
