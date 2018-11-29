// NOTE: Please perform the clicks slowly. 
// The process is highly ineffecient and 
// may cause the system to crash by even moderate click speed

#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
using namespace std;
#define tDiff 0.01					//Difference for parametric equation of line segment
#define maxSquareDistance 49		//Checking the point nearby where the mouse was clicked

bool isDragging = false;			//Drag enabler/disabler
int nearestPoint = -1;				//Stores nearest point to mouse click

//Global Points for x and y coordinates 
vector<int> pointX, pointY;			//Stores all the points in sequence for BSpline creation

//Display Function
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);	
	glFlush();
}

//Initiate values for display
void init(void) {
	glClearColor(1, 1, 0, 0.0f);
	glColor3f(0.545098, 0.270588, 0.0745098);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set up orthographics matrix
	gluOrtho2D(0,1280,0,720);
}

//Draw line between passed set of 2 points
void drawLine(float x1,float y1, float x2, float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1,720 - y1);
	glVertex2f(x2,720 - y2);
	glEnd();
	glFlush();
}

//Drawing a point
void drawDot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x,720 - y);
	glEnd();
	glFlush();
}

//Find the point on the BSpline for a given t
//vector[0] has x, vector[1] has y
vector<int> findPoint(vector<int> X, vector<int> Y, double t) {
	if (X.size() == 1) {
		vector<int> position;
		position.push_back(X.at(0));
		position.push_back(Y.at(0));
		return position;
	} else {
		vector<int> newX, newY;
		int i, size;
		size = X.size();
		for (i = 0; i < size - 1; i++) {
			int x = (1-t)*X.at(i) + t*X.at(i+1);
			newX.push_back(x);
			int y = (1-t)*Y.at(i) + t*Y.at(i+1);
			newY.push_back(y);
		}
		return findPoint(newX, newY, t);
	}
}

//De Casteljau's algorithm
//Draw a line between points received by changed t from 0 to 1 (which becomes the BSpline)
void deCas() {
	if(pointX.size() == 0) return;
	double t;
	vector<int> oldPosition;
	for (t = 0; t <= 1.0; t=t+tDiff) {
		vector<int> position = findPoint(pointX, pointY, t);
		if (oldPosition.size() != 0) {
			drawLine(oldPosition.at(0), oldPosition.at(1), position.at(0), position.at(1));
		}
		oldPosition = position;
	}
}

//Handle dragging of a point
void mouseDragHandler(int x, int y) {
	isDragging = true;
	pointX[nearestPoint] = x;		//Change value of the nearest point to where the mouse was when dragged
	pointY[nearestPoint] = y;
	glClear(GL_COLOR_BUFFER_BIT);	//Draw the entire thing again
	glFlush();
	int i, size = pointX.size();
	for (i = 0; i < size; i++) {
		drawDot(pointX.at(i), pointY.at(i));
	}
	deCas();
}

//Get squared difference (for distance calculation)
int getSquareDiff(int x1, int y1, int x2, int y2) {
	return pow((x1 - x2), 2) + pow((y1 - y1), 2);
}

//Handle mouse clicks
void mouseClickHandler(int button, int state, int x, int y) {
	if(state == GLUT_UP && isDragging == false) {
		if(button == GLUT_LEFT_BUTTON) {				//Set a point and add it to the set, then draw the new spline
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			pointX.push_back(x);
			pointY.push_back(y);
			int i, size = pointX.size();
			for (i = 0; i < size; i++) {
				drawDot(pointX.at(i), pointY.at(i));
			}
			deCas();
		} else if (button == GLUT_RIGHT_BUTTON) {		//Remove the nearest point (if below threshHold)

			int i, size = pointX.size();
			int min = 99999999;
			int pos = -1;
			for (i = 0; i < size; i++) {
				int distance = getSquareDiff(x, y, pointX.at(i), pointY.at(i));
				if (distance < min) {
					min = distance;
					pos = i;
				}
			}
			if (min < maxSquareDistance && pos != -1) {
				pointX.erase(pointX.begin() + pos);
				pointY.erase(pointY.begin() + pos);
			}
			size = pointX.size();
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			for (i = 0; i < size; i++) {
				drawDot(pointX.at(i), pointY.at(i));
			}
			deCas();
		}
	} else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {					//Set nearestPoint
		int i, size = pointX.size();
		int min = 99999999;
		for (i = 0; i < size; i++) {
			int distance = getSquareDiff(x, y, pointX.at(i), pointY.at(i));
			if (distance < min && distance < maxSquareDistance) {
				min = distance;
				nearestPoint = i;
			}
		}
	} else if (state == GLUT_UP) {
		isDragging = false;
		nearestPoint = -1;
	}
}

//Main
int main(int argc,char **argv) {
	//Clear the arrays
	pointX.clear();
	pointY.clear();
	//Initialize
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("De Casteljau's Algorithm");
	//Setup Handlers
	glutMouseFunc(mouseClickHandler);
	glutMotionFunc(mouseDragHandler);
	glutDisplayFunc(display);
	//Initialize and run
	init();
	glutMainLoop();
	return 0;
}