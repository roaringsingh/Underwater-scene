//#include "./freeglut-3.2.1/include/GL/freeglut.h" //Use for replit
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int flag = 0, ch = 0, ch1 = 0, win;
float speed[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float angle = 0, pi = 3.142, move = 1, x = 0, y = 0;

void plant(float x, float y, float s = 500) {
	x *= s;
	y *= s;
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	for (int noleaf = 0; noleaf < 5; noleaf++) {
		glVertex2f(x + 0.025 * s * noleaf, y + 0.1 * s);
		glVertex2f(x, y);
		glVertex2f(x - 0.025 * s * noleaf, y + 0.1 * s);
		glVertex2f(x, y);
	}
	glEnd();
}

void fish(
	float sp,
	const GLfloat* bodyc,
	const GLfloat* finc,
	const GLfloat* tailc,
	float x,
	float y,
	int f_s = 1,
	float s = 500) {
	glColor3fv(bodyc);
	glBegin(GL_POLYGON);
	glVertex2f(x * s + sp, y * s);
	glVertex2f((x + 0.05 * f_s) * s + sp, (y + 0.05 * f_s) * s);
	glVertex2f((x + 0.15 * f_s) * s + sp, y * s);
	glVertex2f((x + 0.05 * f_s) * s + sp, (y - 0.05 * f_s) * s);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); // eye
	glPointSize(3.0 + abs(f_s));
	glBegin(GL_POINTS);
	glVertex2f((x + 0.03 * f_s) * s + sp, (y + 0.015 * abs(f_s)) * s);
	glEnd();

	glColor3fv(tailc); // tail
	glBegin(GL_TRIANGLES);
	glVertex2f((x + 0.14 * f_s) * s + sp, y * s);
	glVertex2f((x + 0.2 * f_s) * s + sp, (y + 0.03 * f_s) * s);
	glVertex2f((x + 0.2 * f_s) * s + sp, (y - 0.03 * f_s) * s);
	glEnd();

	glColor3fv(finc);
	glBegin(GL_TRIANGLES);
	glVertex2f((x + 0.05 * f_s) * s + sp, (y + 0.045 * f_s) * s);
	glVertex2f((x + 0.09 * f_s) * s + sp, (y + 0.075 * f_s) * s);
	glVertex2f((x + 0.07 * f_s) * s + sp, (y + 0.02 * f_s) * s);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f((x + 0.05 * f_s) * s + sp, (y - 0.045 * f_s) * s);
	glVertex2f((x + 0.09 * f_s) * s + sp, (y - 0.075 * f_s) * s);
	glVertex2f((x + 0.07 * f_s) * s + sp, (y - 0.02 * f_s) * s);
	glEnd();
}

void draw_pixel(GLint cx, GLint cy) {
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}

void plotpixels(GLint h, GLint k, GLint x, GLint y) {
	draw_pixel(x + h, y + k);
	draw_pixel(-x + h, y + k);
	draw_pixel(x + h, -y + k);
	draw_pixel(-x + h, -y + k);
	draw_pixel(y + h, x + k);
	draw_pixel(-y + h, x + k);
	draw_pixel(y + h, -x + k);
	draw_pixel(-y + h, -x + k);
}

void circle_draw(GLint h, GLint k, GLint r) {
	GLint d = 1 - r, x = 0, y = r;
	while (y > x) {
		plotpixels(h, k, x, y);
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	plotpixels(h, k, x, y);
}

void bubbles(int sp) {
	int y = -15;
	for (int no_b = 0; no_b < 20; no_b++) {
		y *= -1;
		circle_draw(-500 + no_b * 50, -490 + sp + y, 20);
	}
}

void drawLeafLeft(float x, float y) {
	glLineWidth(5);
	glColor3f(0.235, 0.471, 0.59);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x - 10, y);
	glEnd();

	glColor3ub(60, 170, 15);
	glBegin(GL_POLYGON);
	glVertex2f(x - 10, y);
	glVertex2f(x - 17, y + 18);
	glVertex2f(x - 50, y + 13);
	glColor3f(0.1, 0.5, 0.0);
	glVertex2f(x - 70, y);
	glVertex2f(x - 50, y - 13);
	glVertex2f(x - 17, y - 18);
	glEnd();
}

void drawLeafRight(float x, float y) {
	glLineWidth(5);
	glColor3ub(60, 120, 15);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x + 10, y);
	glEnd();

	glColor3ub(60, 170, 15);
	glBegin(GL_POLYGON);
	glVertex2f(x + 10, y);
	glVertex2f(x + 17, y + 18);
	glVertex2f(x + 50, y + 13);
	glColor3f(0.1, 0.5, 0.0);
	glVertex2f(x + 70, y);
	glVertex2f(x + 50, y - 13);
	glVertex2f(x + 17, y - 18);
	glEnd();
}

void drawSineWave() {
	glPointSize(8.0);
	glBegin(GL_POINTS);
	for (angle = 0; angle < 500.0; angle = angle + 0.9) {
		glColor3ub(46, 110, 7);
		x = (sin(angle * pi / 90) * 15);
		y = angle;
		glVertex2f(x + 400, y - 500);
	}
	glEnd();
	drawLeafLeft(400, -420);
	drawLeafLeft(409, -290);
	drawLeafLeft(385, -180);
	drawLeafLeft(397, -40);
	drawLeafRight(385, -360);
	drawLeafRight(397, -220);
	drawLeafRight(411, -90);
}

void mov(float scale) {
	if (speed[1] >= -1 * 2.5 * scale)
		speed[1] -= (0.075 + speed[0]);
	else
		speed[1] = 2.5 * scale;

	if (speed[2] >= -1 * 2.5 * scale)
		speed[2] -= (0.1 + speed[0]);
	else
		speed[2] = 2.5 * scale;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat red[3] = { 1.0, 0.0, 0.0 };
	GLfloat yellow[3] = { 1.0, 1.0, 0.0 };
	GLfloat green[3] = { 0.0, 1.0, 0.0 };
	float scale = 500;

	if (move == 1)
		mov(scale);

	if (speed[3] <= 2.5 * scale)
		speed[3] += 0.2;

	plant(0.8, -0.9);
	plant(0.5, -0.95);
	plant(0.175, -0.9);
	plant(-0.175, -0.95);
	plant(-0.5, -0.9);
	plant(-0.8, -0.95);

	fish(-speed[1], red, red, red, 1, 0, -3);
	fish(-speed[2], yellow, green, green, -0.5, 0.560, -1);
	fish(-speed[2], yellow, green, green, -0.5, 0.440, -1);
	fish(-speed[2], yellow, green, green, -0.625, 0.625, -1);
	fish(-speed[2], yellow, green, green, -0.625, 0.5, -1);
	fish(-speed[2], yellow, green, green, -0.625, 0.375, -1);
	fish(-speed[2], yellow, green, green, -0.75, 0.685, -1);
	fish(-speed[2], yellow, green, green, -0.75, 0.562, -1);
	fish(-speed[2], yellow, green, green, -0.75, 0.440, -1);
	fish(-speed[2], yellow, green, green, -0.75, 0.315, -1);
	fish(-speed[2], yellow, green, green, -0.875, 0.625, -1);
	fish(-speed[2], yellow, green, green, -0.875, 0.5, -1);
	fish(-speed[2], yellow, green, green, -0.875, 0.375, -1);

	drawSineWave();
	bubbles(speed[3]);

	glutPostRedisplay();
	glutSwapBuffers();
}

void keys(unsigned char key, int x, int y) {
	if (key == 's')
		move = 1 - move;
	if (key == 'f')
		speed[0] += 0.025;
	if (key == 'j')
		if (speed[0] > 0)
			speed[0] -= 0.025;
	if (key == 'b')
		speed[3] = 0;
	if (key == 27) {
		glutDestroyWindow(win);
		exit(0);
	}
}

void myinit() {
	glClearColor(0, 0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	win = glutCreateWindow("Fish");
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutMainLoop();
}
