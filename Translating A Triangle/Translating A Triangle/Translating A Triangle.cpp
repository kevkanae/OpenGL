#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

int x, y;
int menuValue = 0;

void Draw(float x1, float y1) {
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();

}

void Triangle()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(250, 400);
	glVertex2f(400, 100);
	glEnd();
}

void myInit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION); //Specifies which matrix is the current matrix
	glLoadIdentity(); // Loads a Indentity Matrix
	glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0); // Sets the drawing Boundary | Left, Right, Bottom, Top, Near, Far 
	glMatrixMode(GL_MODELVIEW);
}

float myX = 0.0, myY = 0.0, myH = 0.0; // h: angle of rotation
void Display() {

	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen for every frame i.e re-draw new triangle for every angle of rotation
	glLoadIdentity(); // Loads a Indentity Matrix

	//Rotate Around Origin
	if (menuValue == 1) {
		myX = 0.0;
		myY = 0.0;
		myH += 0.1;
		glColor3f(255.0, 179.0, 179.0);
		Draw(0.0, 0.0);
	}

	//Rotate Around Fixed Point
	if (menuValue == 2) {
		myX = x;
		myY = y;
		myH += 0.1;
		glColor3f(255.0, 179.0, 179.0);
		Draw(x, y);
	}

	glTranslatef(myX, myY, 0.0); // Takes the object to origin
	glRotatef(myH, 0.0, 0.0, 1.0); // Rotates it
	glTranslatef(-myX, -myY, 0.0); // Takes the object back to origin

	Triangle();

	glutPostRedisplay();
	glutSwapBuffers();
}

void Menu(int option) {

	if (option == 1) menuValue = 1;
	if (option == 2) menuValue = 2;
	if (option == 3) menuValue = 3;

	Display();
}

int main(int argc, char** argv) {

	std::cout << "Enter Fixed Points (x,y) for Rotation:" << std::endl;

	std::cin >> x >> y;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //initialize buffer
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("4CB18CS034_TriangleRotation");
	myInit(); // Specifying the Clipping Boundary
	glutDisplayFunc(Display); // Definition of what Graphics we wanna display
	// Creating a Menu 
	glutCreateMenu(Menu);
	// Menu Option
	glutAddMenuEntry("Rotate around the ORIGIN", 1);
	glutAddMenuEntry("Rotate around the FIXED POINT", 2);
	glutAddMenuEntry("Stop the Rotation", 3);
	// Assign a Button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}