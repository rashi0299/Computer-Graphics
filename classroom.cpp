/*
*
* To compile:
*   g++ classroom.cpp -lglut -lGL -lGLU
*
*/
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//Rotation variables
float _angleX = 0.0f;
float _angleY = 0.0f;
float _angleZ = 0.0f;

//Translation variables
float translateX = 0.0f;
float translateY = 0.0f;
float translateZ = -20.0f;


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
        exit(0);

        //Translation with char keys (arrow keys in separate function below)
        case 'i':                   //Scene moves down (Y-axis)
        translateY -= 1.0f;
        break;

        case 'k':                   //Scene moves up (Y-axis)
        translateY += 1.0f;
        break;

        //Rotation (follows right hand thumb rule)
        case 'w':                   //Scene rotates about +ve X-axis
        _angleX += 1.5f;
        break;

        case 's':                   //Scene rotates about -ve X-axis
        _angleX -= 1.5f;
        break;

        case 'a':                   //Scene rotates about +ve Y-axis
        _angleY += 1.5f;
        break;

        case 'd':                   //Scene rotates about -ve Y-axis
        _angleY -= 1.5f;
        break;

        case 'j':                   //Scene rotates about +ve Z-axis 
        _angleZ += 1.5f;
        break;

        case 'l':                   //Scene rotates about -ve Z-axis
        _angleZ -= 1.5f;
        break;

        case 'r':                   //Reset Scene to initial state
        _angleX = 0.0f;
        _angleY = 0.0f;
        _angleZ = 0.0f;

        translateX = 0.0f;
        translateY = 0.0f;
        translateZ = -20.0f;

    }

    glutPostRedisplay();            //redraw scene
}

//Called when special keys are pressed
void specialInput(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_UP:           //Scene zooms in (Z-axis)
        translateZ += 1.0f;
        break;  
        case GLUT_KEY_DOWN:         //Scene zooms out (Z-axis)
        translateZ -= 1.0f;
        break;
        case GLUT_KEY_LEFT:         //Scene goes left (X-Axis)
        translateX -= 1.0f;
        break;
        case GLUT_KEY_RIGHT:        //Scene goes right (X-Axis)
        translateX += 1.0f;
        break;
    }

    glutPostRedisplay();

}

//Initializes 3D rendering
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


void drawCube(float dimensions[], float center[], float colour[]) {

    //Color set here
    glColor3f(colour[0], colour[1], colour[2]);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);

    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);

    //Back
    glNormal3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);

    //Left
    glNormal3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);

    //Top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], (dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);

    //Bottom
    glNormal3f((dimensions[0]/2)+center[0], -1.0f, 0.0f);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], (dimensions[2]/2)+center[2]);
    glVertex3f((dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);
    glVertex3f(-(dimensions[0]/2)+center[0], -(dimensions[1]/2)+center[1], -(dimensions[2]/2)+center[2]);

    glEnd();

}

//Draws the 3D scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Translate the entire system to some other place (Used for scene interaction)
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    //Chair sample

    //Back (red color)
    float dimensions[3], center[3], colour[3];
    dimensions[0] = 4.0f; dimensions[1] = 10.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = -8.0f; center[2] = -7.0f;
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Front (green color)
    dimensions[0] = 4.0f; dimensions[1] = 5.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = -10.5f; center[2] = -11.0f;								//-3
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Seat (blue color)
    dimensions[0] = 4.0f; dimensions[1] = 0.3f; dimensions[2] = 4.3f;
    center[0] = 0.0f; center[1] = -8.0f; center[2] = -9.0f;
    colour[2] = 1.0f; colour[0] = colour[1] = 0.0f;
    drawCube(dimensions, center, colour);  

    //Chair sample end

    //Table sample start
    dimensions[0] = 12.0f; dimensions[1] = 0.3f; dimensions[2] = 8.6f;
    center[0] = 0.0f; center[1] = -6.0f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour);  
	
    //Green
    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = 6.0f; center[1] = -9.5f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 

    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = -6.0f; center[1] = -9.5f; center[2] = -14.0f;
   colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 

    //BUG: flicker while rotating chair (probably due to changing views and decision of which surface to show) 
 
 	 //Back (red color)
    //float dimensions[3], center[3], colour[3];
    dimensions[0] = 4.0f; dimensions[1] = 10.0f; dimensions[2] = 0.3f;
    center[0] = 16.0f; center[1] = -8.0f; center[2] = -7.0f;
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Front (green color)
    dimensions[0] = 4.0f; dimensions[1] = 5.0f; dimensions[2] = 0.3f;
    center[0] = 16.0f; center[1] = -10.5f; center[2] = -11.0f;								//-3
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Seat (blue color)
    dimensions[0] = 4.0f; dimensions[1] = 0.3f; dimensions[2] = 4.3f;
    center[0] = 16.0f; center[1] = -8.0f; center[2] = -9.0f;
    colour[2] = 1.0f; colour[0] = colour[1] = 0.0f;
    drawCube(dimensions, center, colour);  

    //Chair sample end

    //Table sample start
    dimensions[0] = 12.0f; dimensions[1] = 0.3f; dimensions[2] = 8.6f;
    center[0] = 16.0f; center[1] = -6.0f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour);  
	
    //Green
    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = 22.0f; center[1] = -9.5f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 

    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = 10.0f; center[1] = -9.5f; center[2] = -14.0f;
   colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 


		 //Back (red color)
    //chair starts
    //float dimensions[3], center[3], colour[3];
    dimensions[0] = 4.0f; dimensions[1] = 10.0f; dimensions[2] = 0.3f;
    center[0] = -16.0f; center[1] = -8.0f; center[2] = -7.0f;
   colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Front (green color)
    dimensions[0] = 4.0f; dimensions[1] = 5.0f; dimensions[2] = 0.3f;
    center[0] = -16.0f; center[1] = -10.5f; center[2] = -11.0f;								//-3
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Seat (blue color)
    dimensions[0] = 4.0f; dimensions[1] = 0.3f; dimensions[2] = 4.3f;
    center[0] = -16.0f; center[1] = -8.0f; center[2] = -9.0f;
    colour[2] = 1.0f; colour[0] = colour[1] = 0.0f;
    drawCube(dimensions, center, colour); 
 

    //Chair sample end

    //Table sample start
    dimensions[0] = 12.0f; dimensions[1] = 0.3f; dimensions[2] = 8.6f;
    center[0] = -16.0f; center[1] = -6.0f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour);  
	
    //Green
    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = -10.0f; center[1] = -9.5f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 

    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = -22.0f; center[1] = -9.5f; center[2] = -14.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 
    //Table end 

    //chair starts
    dimensions[0] = 4.0f; dimensions[1] = 10.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = -8.0f; center[2] = -50.0f;
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Front (green color)
    dimensions[0] = 4.0f; dimensions[1] = 5.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = -10.5f; center[2] = -46.0f;								//-3
    colour[1] = 1.0f; colour[0] = colour[2] = 0.0f;
    drawCube(dimensions, center, colour);

    //Seat (blue color)
    dimensions[0] = 4.0f; dimensions[1] = 0.3f; dimensions[2] = 4.3f;
    center[0] = 0.0f; center[1] = -8.0f; center[2] = -48.0f;
    colour[2] = 1.0f; colour[0] = colour[1] = 0.0f;
    drawCube(dimensions, center, colour); 
 

    //Chair sample end

    //Table sample start
    dimensions[0] = 12.0f; dimensions[1] = 0.3f; dimensions[2] = 8.6f;
    center[0] = 0.0f; center[1] = -6.0f; center[2] = -45.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour);  
	
    //Green
    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = -6.0f; center[1] = -9.5f; center[2] = -45.0f;
    colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 

    dimensions[0] = 0.3f; dimensions[1] = 7.0f; dimensions[2] = 8.6f;
    center[0] = 6.0f; center[1] = -9.5f; center[2] = -45.0f;
   colour[0] = 0.0f; colour[1] = 0.89; colour[2] = 1.0f;
    drawCube(dimensions, center, colour); 
    //Table end 

    //board
    
    //Back (green color)
   
    dimensions[0] = 40.0f; dimensions[1] = 20.0f; dimensions[2] = 0.3f;
    center[0] = 0.0f; center[1] = 5.0f; center[2] = -60.0f;
    colour[0] = 0.2f; colour[1] = 0.41f; colour[2] = 0.2f;
    drawCube(dimensions, center, colour);
	
    //colour[0] = 1.0f; colour[1] = colour[2] = 0.0f;
    //glutSolidSphere(70,20,20)
	//bottomleft
    glColor3f(0.8, 0.2, 0.1); 
    glTranslatef(-20.0,-5.0,-60.0);

    glutSolidTorus(0.5,1,50,50);
    //topleft
    glColor3f(0.8, 0.2, 0.1); 
    glTranslatef(0.0,20.0,0.0);

    glutSolidTorus(0.5,1,50,50);
	//topright
    glColor3f(0.8, 0.2, 0.1); 
    glTranslatef(40.0,0.0,0.0);

    glutSolidTorus(0.5,1,50,50);
    //bottomright

    glColor3f(0.8, 0.2, 0.1); 
    glTranslatef(0.0,-20.0,0.0);

    glutSolidTorus(0.5,1,50,50);

    glutSolidSphere(150,20,20);

        // Flush buffers to screen
	//Floor
	dimensions[0] = 97.0f; dimensions[1] = 0.1f; dimensions[2] = 100.0f;
	center[0] = -16.0f; center[1] = -8.0f; center[2] = 5.0f;
	colour[0] = 0.3f; colour[1] = 0.3f; colour[2] = 0.3f;
	drawCube(dimensions, center, colour);
    

    glutSwapBuffers();


}

int main(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    //Create the window
    glutCreateWindow("Rotating 3D Cuboid");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);
    glutReshapeFunc(handleResize);

    glutMainLoop();
}
