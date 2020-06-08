#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>


const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

time_t t;
#define RAINSIZE 50

//Game Speed
int speed = 50;

int start = 0;
int show = 0;

//move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//For the car to move left or right
int lrIndex = 0;

//Car Coming initialization
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;



char s[30];
void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

struct drop {
	float x = 1000;
	float y = 1000;
	float inc = 0.000001;
	float radius = 5;
	float scale = 2;
	float rotationAngle = 0;
	float rotationInc = 0.7;
};

drop rain[RAINSIZE];


void tree(int x, int y)
{
	float x1 = x;
	float y1 = y;

	//Bark
	glColor3f(0.36, 0.25, 0.20);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1 + 11, y1 + 55);
	glVertex2f(x1 + 12, y1 + 45);
	glVertex2f(x1 + 10, y1 + 45);
	glEnd();

	//tree upper
	glColor3f(0.1, 1.46, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1 + 11, y1 + 58);
	glVertex2f(x1 + 15, y1 + 52);
	glVertex2f(x1 + 7, y1 + 52);
	glEnd();
}



void initRain() {
	srand((unsigned)time(&t));
	for (int i = 0; i < RAINSIZE; i++) {
		rain[i].x = rand() % 1200;
		rain[i].y = rand() % 800;
		rain[i].inc = 1.5 + (float)(rand() % 100) / 1000.0;
		rain[i].radius = (float)(rand() % 8);
		rain[i].scale = (float)(rand() % 20000) / 1000.0;

	}
}

void drawParticleShape(int i)
{
	glBegin(GL_POINTS);
	glVertex2d(rain[i].x, rain[i].y);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(rain[i].x, rain[i].y);
	glVertex2d(rain[i].x, rain[i].y + rain[i].radius * 2);
	glEnd();
}

void drawDrop(int i) {
	glColor3f(1, 1, 1);
	glLineWidth(3);
	drawParticleShape(i);
	rain[i].y -= rain[i].inc;
	if (rain[i].y < 0) {
		rain[i].y = 900;
	}
}

void drawRain() {
	for (int i = 0; i < RAINSIZE; i++) {
		drawDrop(i);
	}
}
void idle() {
	drawRain();
}

void startGame()
{

	tree(85, 30);
	tree(2, 15);
	tree(665, 5);

	//Road
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	// Left Border
	glColor3f(0.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(23, 100);
	glVertex2f(23, 0);
	glEnd();

	// Right Border
	glColor3f(0.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(77, 0);
	glVertex2f(77, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Road Middel Border
	//TOP
	glColor3f(0.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivTop + 80);
	glVertex2f(48, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 80);
	glEnd();
	roadDivTop--;

	//Middle
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMdl + 40);
	glVertex2f(48, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 40);
	glEnd();



	roadDivMdl--;

	//Bottom
	glColor3f(1.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivBtm + 0);
	glVertex2f(48, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 0);
	glEnd();
	roadDivBtm--;



	//USER car
	//Front Tire
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 5);
	glVertex2f(lrIndex + 26 - 2, 7);
	glVertex2f(lrIndex + 30 + 2, 7);
	glVertex2f(lrIndex + 30 + 2, 5);
	glEnd();
	//Back Tire
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 1);
	glVertex2f(lrIndex + 26 - 2, 3);
	glVertex2f(lrIndex + 30 + 2, 3);
	glVertex2f(lrIndex + 30 + 2, 1);
	glEnd();
	//Car Body
	glColor3f(0.9, 0.1, 0.3);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 1);
	glVertex2f(lrIndex + 26, 8);
	glColor3f(0.000, 0.545, 0.545);

	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 8);
	glVertex2f(lrIndex + 30, 1);
	glEnd();


	//COmputer operated car 1
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
	glEnd();
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
	glEnd();
	glColor3f(1.000, 0.000, 0.350);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26, car1 + 100);
	glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 30, car1 + 100);
	glEnd();
	car1--;
	if (car1 < -100) {
		car1 = 0;
		lrIndex1 = lrIndex;
	}
	// check car1 for collision
	if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10)) {
		start = 0;
		show = 1;

	}

	//Computer operated car 2
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
	glEnd();
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
	glEnd();
	glColor3f(1.294, 0.000, 1.510);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26, car2 + 100);
	glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 30, car2 + 100);
	glEnd();
	car2--;
	if (car2 < -100) {
		car2 = 0;
		lrIndex2 = lrIndex;
	}
	//check car2 for collision
	if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10)) {
		start = 0;
		show = 1;
	}


	//Computer operated car 3
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
	glEnd();
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
	glEnd();
	glColor3f(1.000, 1.271, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26, car3 + 100);
	glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
	glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
	glVertex2f(lrIndex3 + 30, car3 + 100);
	glEnd();
	car3--;
	if (car3 < -100) {
		car3 = 0;
		lrIndex3 = lrIndex;
	}
	// check car3 for collision
	if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10)) {
		start = 0;
		show = 1;
	}
}

void home()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Sky
	glColor3f(0.000, 0.8, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.686, 0.933, 0.933);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();


	//Hills
	//back side hills
	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 55 + 10);
	glVertex2f(20 + 7, 55);
	glVertex2f(0, 55);
	glEnd();

	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(87, 55 + 10);
	glVertex2f(100, 55);
	glVertex2f(60, 55);
	glEnd();


	//front side hills
	glColor3f(0.45, 0.30, 0.30);
	glBegin(GL_TRIANGLES);
	glVertex2f(35, 67);
	glVertex2f(51, 55);
	glVertex2f(10, 55);
	glEnd();

	glColor3f(0.45, 0.30, 0.30);
	glBegin(GL_TRIANGLES);
	glVertex2f(70, 70);
	glVertex2f(90, 55);
	glVertex2f(51, 55);
	glEnd();

	//sun
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(43, 61);
	glVertex2f(59, 61);
	glVertex2f(51, 55);
	glEnd();
	// sun rays
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(44, 61);
	glVertex2f(42, 66);
	glVertex2f(46, 61);
	glVertex2f(44, 66);
	glVertex2f(48, 61);
	glVertex2f(46, 66);
	glVertex2f(50, 61);
	glVertex2f(48, 66);


	glVertex2f(50, 61);
	glVertex2f(52, 66);
	glVertex2f(52, 61);
	glVertex2f(54, 66);
	glVertex2f(54, 61);
	glVertex2f(56, 66);
	glVertex2f(56, 61);
	glVertex2f(58, 66);

	glEnd();

	tree(15, -15);
	tree(70, 5);
	//roof
	glColor3f(0.3, 0.5, 0.8);
	glBegin(GL_POLYGON);
	glVertex2i(50, 50);
	glVertex2i(90, 50);
	glVertex2i(100, 35);
	glVertex2i(60, 35);
	glEnd();
	// Top wall

	glColor3f(0.1, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(40, 35);
	glVertex2i(60, 35);
	glEnd();
	// Front Wall
	glColor3f(0.7, 0.2, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(40, 35);
	glVertex2i(60, 35);
	glVertex2i(60, 10);
	glVertex2i(40, 10);
	glEnd();
	//  Door
	glColor3f(0.7, 0.2, 0.9);
	glBegin(GL_POLYGON);
	glVertex2i(45, 25);
	glVertex2i(50, 25);
	glVertex2i(50, 10);
	glVertex2i(45, 10);


	glEnd();

	// Door Lock
	glColor3f(0.3, 0.7, 0.9);
	glPointSize(15);
	glBegin(GL_POINTS);
	glVertex2i(45, 20);
	glEnd();

	//side Wall
	glColor3f(0.1, 0.2, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(60, 35);
	glVertex2i(100, 35);
	glVertex2i(100, 10);
	glVertex2i(60, 10);
	glEnd();
	// window
	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(61, 30);
	glVertex2i(71, 30);
	glVertex2i(71, 25);
	glVertex2i(61, 25);
	glEnd();

	glColor3f(0.1, 0.7, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(68, 30);
	glVertex2i(68, 25);
	glVertex2i(64, 30);
	glVertex2i(64, 25);
	glEnd();
	// window two
	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(81, 30);
	glVertex2i(91, 30);
	glVertex2i(91, 25);
	glVertex2i(81, 25);
	glEnd();
	// lines of window two
	glColor3f(0.1, 0.7, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(84, 30);
	glVertex2i(88, 30);
	glVertex2i(88, 25);
	glVertex2i(84, 25);
	glEnd();

	// Path
	glColor3f(0.3, 0.5, 0.7);
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glVertex2i(45, 10);
	glVertex2i(55, 10);
	glVertex2i(50, 0);
	glVertex2i(35, 0);
	glEnd();

	//car
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(7, 18);
	glVertex2i(7, 20);
	glVertex2i(18, 18);
	glVertex2i(18, 20);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(7, 11);
	glVertex2i(7, 13);
	glVertex2i(18, 13);
	glVertex2i(18, 11);
	glEnd();
	//body
	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(8, 12);
	glVertex2i(17, 12);
	glVertex2i(15, 10);
	glVertex2i(10, 10);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(8, 12);
	glVertex2i(8, 19);
	glVertex2i(17, 19);
	glVertex2i(17, 12);
	glEnd();

	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(8, 19);
	glVertex2i(10, 21);
	glVertex2i(15, 21);
	glVertex2i(17, 19);
	glEnd();

	glColor3f(0, 1, 0);
	renderBitmapString(1, 50, (void*)font2, "We have enabled dark mode with Rainy effect");
	glColor3f(0, 1, 0);
	renderBitmapString(3, 35, (void*)font1, "Enjoy Gaming!!!");
	glColor3f(0, 1, 0);
	renderBitmapString(70, 15, (void*)font1, "PRESS Y TO CONTINUE");


	glutPostRedisplay();
	glutSwapBuffers();

}

void initialDesign()
{
	//Side track
	glColor3f(0, 0.305, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.7, 0.804, 0.3);
	glVertex2f(100, 50 - 50);
	glVertex2f(0, 50 - 50);
	glEnd();


	//Road
	glColor3f(0.658824, 0.658824, 0.658824);
	glBegin(GL_TRIANGLES);
	glVertex2f(51, 55);
	glVertex2f(90, 0);
	glVertex2f(10, 0);
	glEnd();

	//divider
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(50 + 2, 50 - 50);
	glVertex2f(50 - 2, 50 - 50);
	glEnd();

	// Sky
	glColor3f(0.000, 0.8, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.686, 0.933, 0.933);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();
	//sun
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(43, 61);
	glVertex2f(59, 61);
	glVertex2f(51, 55);
	glEnd();
	// sun rays
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(44, 61);
	glVertex2f(42, 66);
	glVertex2f(46, 61);
	glVertex2f(44, 66);
	glVertex2f(48, 61);
	glVertex2f(46, 66);
	glVertex2f(50, 61);
	glVertex2f(48, 66);


	glVertex2f(50, 61);
	glVertex2f(52, 66);
	glVertex2f(52, 61);
	glVertex2f(54, 66);
	glVertex2f(54, 61);
	glVertex2f(56, 66);
	glVertex2f(56, 61);
	glVertex2f(58, 66);

	glEnd();

	//Hills
	//back side hills
	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 55 + 10);
	glVertex2f(20 + 7, 55);
	glVertex2f(0, 55);
	glEnd();

	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(87, 55 + 10);
	glVertex2f(100, 55);
	glVertex2f(60, 55);
	glEnd();


	//front side hills
	glColor3f(0.45, 0.30, 0.30);
	glBegin(GL_TRIANGLES);
	glVertex2f(35, 67);
	glVertex2f(51, 55);
	glVertex2f(10, 55);
	glEnd();

	glColor3f(0.45, 0.30, 0.30);
	glBegin(GL_TRIANGLES);
	glVertex2f(70, 70);
	glVertex2f(90, 55);
	glVertex2f(51, 55);
	glEnd();


	tree(15, -15);
	tree(70, 5);
	tree(75, -15);
	tree(10, -5);
	tree(665, 5);
	tree(65, -15);



	//info to be displayed
	if (show == 1) {
		glColor3f(1.000, 0.000, 0.000);
		renderBitmapString(45, 60 + 10, (void*)font1, "GAME OVER");
	}

	//instructions
	glColor3f(0, 0, 0);
	renderBitmapString(42.5, 41, (void*)font2, "Press SPACE to START");
	renderBitmapString(44, 35, (void*)font2, "Press ESC to EXIT");
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1)
	{
		startGame();
		drawRain();
	}
	else
		initialDesign();

	glFlush();
	glutSwapBuffers();
}
void welcomeDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRasterPos3f(35, 80, 0);
	glColor3f(1, 1, 1);

	char msg1[] = "A 2D racing car game";
	for (int i = 0; i < strlen(msg1); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
	}
	glColor3f(0.2, 0.7, 0.3);
	glRasterPos3f(30, 60, 0);

	char msg2[] = "Submitted By:";
	for (int i = 0; i < strlen(msg2); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg2[i]);
	}
	glColor3f(0.2, 0.5, 0.9);
	glRasterPos3f(20, 50, 0);

	char msg4[] = "Name:";
	for (int i = 0; i < strlen(msg4); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg4[i]);
	}

	glColor3f(0.2, 0.5, 0.9);
	glRasterPos3f(40, 45, 0);

	char msg3[] = "DIVYA CHERYL MORAS";
	for (int i = 0; i < strlen(msg3); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg3[i]);
	}

	glColor3f(0.2, 0.5, 0.9);
	glRasterPos3f(20, 40, 0);

	char msg5[] = "USN:";
	for (int i = 0; i < strlen(msg5); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg5[i]);
	}
	glColor3f(0.2, 0.5, 0.9);
	glRasterPos3f(40, 30, 0);
	char msg6[] = "4SO17CS035";
	for (int i = 0; i < strlen(msg6); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg6[i]);
	}

	glColor3f(0, 1, 0.6);
	glRasterPos3f(60, 10, 0);
	char msg7[] = "Press X to continue";
	for (int i = 0; i < strlen(msg7); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg7[i]);
	}

	glutSwapBuffers();
}


void spe_key(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_DOWN:
		speed = speed - 2;
		break;
	case GLUT_KEY_UP:
		speed = speed + 2;
		break;

	case GLUT_KEY_LEFT:
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (speed / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
		break;


	case GLUT_KEY_RIGHT:
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (speed / 10);
			if (lrIndex > 44) {
				lrIndex = 45;
			}
		}
		break;

	default:
		break;
	}

}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':glutDisplayFunc(home);
		glutPostRedisplay();
		break;

	case 'y':glutDisplayFunc(display);
		break;
	case ' ':
		if (start == 0) {
			start = 1;
			show = 0;
			speed = 50;
			roadDivTopMost = 0;
			roadDivTop = 0;
			roadDivMdl = 0;
			roadDivBtm = 0;
			lrIndex = 0;
			car1 = 0;
			lrIndex1 = 0;
			car2 = +35;
			lrIndex2 = 0;
			car3 = +70;
			lrIndex3 = 0;
		}
		break;
	case 'r':
		drawRain();
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();

}



void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / speed, timer, 0);
}

int main(int argc, char* argv[])
{
	srand(1);
	initRain();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D Car Game");
	glutDisplayFunc(welcomeDisplay);
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(keys);
	glutIdleFunc(idle);

	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(0.184, 0.310, 0.310, 1);
	glutTimerFunc(1000, timer, 0);
	glutMainLoop();

	return 0;

}