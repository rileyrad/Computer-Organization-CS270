 /** @mainpage 
   *  \htmlinclude "STRUCTS.html"
   */
/* CS270 
 *
 * Author: Riley Radici
 * Date:   2/12/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
    int tempNumStudents = 0;
    scanf("%d", &tempNumStudents);
    ClassRoster roster;
    roster.numStudents = tempNumStudents;
    roster.students = (Student**)calloc(tempNumStudents, sizeof(Student*));
    for (int i = 0; i < tempNumStudents; i++){
        readStudentAndEnroll(&roster.students[i]);
    }
    for (int i = 0; i < tempNumStudents; i++){
        displayStudent(*roster.students[i]);
        free(roster.students[i]);
    }
    free(roster.students);
    return 0;
}
