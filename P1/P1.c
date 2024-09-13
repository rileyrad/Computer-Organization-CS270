// P1 Assignment
// Author: Riley Radici
// Date:   8/29/2022
// Class:  CS270
// Email:  Riley.Radici@colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double input[5];
double output[4];

void computeSphere(double radius, double *output)
{
    // Compute area
    double result = (4.0 / 3.0) * 3.141593 * radius * radius * radius;

    // Dereference pointer to return result
    *output = result;
}

void computeCube(double side, double *output)
{
    // Compute area
    double result = side * side * side;

    // Dereference pointer to return result
    *output = result;
}

void computeTetrahedron(double side, double *output)
{
    // Compute area
    double result = 0.117851 * side * side * side;

    // Dereference pointer to return result
    *output = result;
}

void computeCylinder(double radius, double height, double *output)
{
    // Compute area
    double result = 3.141593 * radius * radius * height;

    // Dereference pointer to return result
    *output = result;
}


int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 <double> <double> <double> <double> <double>\n");

        return EXIT_FAILURE;
    }

    // Parse arguments
    double radiusSphere = atof(argv[1]);
	double radiusCube = atof(argv[2]);
	double radiusTetra = atof(argv[3]);
	double radiusCyl = atof(argv[4]);
	double heightCyl = atof(argv[5]);
    

    // Local variable
    double areaSphere;
	double areaCube;
	double areaTetra;
	double areaCyl;

    // Call function
    computeSphere(radiusSphere, &areaSphere);
	computeCube(radiusCube, &areaCube);
	computeTetrahedron(radiusTetra, &areaTetra);
	computeCylinder(radiusCyl, heightCyl, &areaCyl);

    // Print area
    printf("SPHERE, radius = %.5f, volume = %.5f.\n", radiusSphere, areaSphere);
	printf("CUBE, side = %.5f, volume = %.5f.\n", radiusCube, areaCube);
	printf("TETRAHEDRON, side = %.5f, volume = %.5f.\n", radiusTetra, areaTetra);
	printf("CYLINDER, radius = %.5f, height = %.5f, volume = %.5f.\n", radiusCyl, heightCyl, areaCyl);
	

    // Return success
    return EXIT_SUCCESS;
}
