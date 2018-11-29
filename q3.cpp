#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include<cstdio>
#include<cstdlib>
#include <iostream>
 
class GUI        //used to implement lines in the GUI
{
public:
    GUI(){}
    void drawLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2 ){  //! draws a single line 
        GLfloat lineVertices[] =
        {x1,y1,z1,
        x2,y2,z2
        };
 
        glEnable(GL_LINE_SMOOTH);
        glPushAttrib(GL_LINE_BIT);
        glLineWidth(1);
        glLineStipple(1, 0x00FF);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, lineVertices);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPopAttrib();
        glDisable(GL_LINE_SMOOTH);
        }
 
        void drawFractalLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2)   //! draws lines recursively(bucket format)
        {
            GLfloat len=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
            drawLine(x1,y1,z1,x2,y2,z2);
            //cout << x1 << "," << y1 << "\n";
            drawLine(x2,y2,z2,x2+len,y2,z2);
            //cout << x2 << "," << y2 << "\n"
            //cout << x2+len << "," << y2 << "\n"
            //cout << x2+len << "," << y2-len << "\n"
            drawLine(x2+len,y2,z2,x2+len,y2+len,z2);
 
        }
        void drawFractalLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat len )             //!draws lines recursively(wave format)
        {
            if(len>=1.0){
            drawLine(x1,y1,z1,x1+len,y1,z1);
            y1+=20;
           
            drawFractalLine(x1,y1,z1,len/2);
            drawFractalLine(x1+(len*(1/2)),y1,z1,len/2);
        }
        }
       
       
};
 
class FractalCircles{                                                                //! class to implement circles in GUI
public:
    void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint no_of_sides){   //! draws a single circle
        GLint no_of_vertices=no_of_sides + 1;
        GLfloat vertices_x_value[no_of_vertices];
        GLfloat vertices_y_value[no_of_vertices];
        GLfloat vertices_z_value[no_of_vertices];
        for (int i=0; i<no_of_vertices;i++){
            vertices_x_value[i]=x+(radius*cos(i*2.0f*M_PI/no_of_sides));
            vertices_y_value[i]=y+(radius*sin(i*2.0f*M_PI/no_of_sides));
            vertices_z_value[i]=z;
        }
       
        GLfloat points_in_circle[no_of_vertices*3];
       
        for (int i=0;i< no_of_vertices;i++){
            points_in_circle[i*3]=vertices_x_value[i];
            points_in_circle[(i*3)+1]=vertices_y_value[i];
            points_in_circle[(i*3)+2]=vertices_z_value[i];
        }
       
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points_in_circle);
        glDrawArrays(GL_LINE_STRIP, 0, no_of_vertices);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    void drawFractalCircle1(GLfloat x, GLfloat y, GLfloat z,  GLfloat radius, GLint no_of_sides, float aspect_ratio){  //!draws circles recursively(wrt previous coordinates)
        drawCircle(x,y,z,radius,36);
        if (radius >10){
            drawFractalCircle1(x+(x*aspect_ratio), y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle1(x-(x*aspect_ratio), y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle1(x , y+ (y*aspect_ratio), z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle1(x , y- (y*aspect_ratio), z, radius*aspect_ratio,no_of_sides,aspect_ratio);
        }
    }
    void drawFractalCircle2(GLfloat x, GLfloat y, GLfloat z,  GLfloat radius, GLint no_of_sides, float aspect_ratio){  //!draws circles recursively(wrt radius)
        drawCircle(x,y,z,radius,36);
        if (radius >10){
            drawFractalCircle2(x+(radius*aspect_ratio), y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle2(x-(radius*aspect_ratio), y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle2(x , y+ (radius*aspect_ratio), z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle2(x , y- (radius*aspect_ratio), z, radius*aspect_ratio,no_of_sides,aspect_ratio);
        }
 
    }
    void drawFractalCircle(GLfloat x, GLfloat y, GLfloat z,  GLfloat radius, GLint no_of_sides,float aspect_ratio){    //!overloaded function to draw circles recursively wrt aspect_ratio
        drawCircle(x,y,z,radius,36);
        if (radius >8.0){
            drawFractalCircle(x + radius, y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            //printf("%f, %f, %f\n",(float)x, (float)y, (float)radius);
            drawFractalCircle(x - radius, y, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle(x , y+ radius, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
            drawFractalCircle(x , y- radius, z, radius*aspect_ratio,no_of_sides,aspect_ratio);
        }
    }
    void drawFractalCircle(GLfloat x, GLfloat y, GLfloat z,  GLfloat radius, GLint no_of_sides,
        float difference_x, float difference_y, float aspect_ratio){                                                 //!overloaded function to draw circles recursively wrt difference
        drawCircle(x,y,z,radius,36);
        if (radius >10.0){
            drawFractalCircle(x + difference_x, y, z, radius*aspect_ratio,no_of_sides,difference_x,difference_y,aspect_ratio);
            //printf("%f, %f, %f\n",(float)x, (float)y, (float)radius);
            drawFractalCircle(x - difference_x, y, z, radius*aspect_ratio,no_of_sides,difference_x,difference_y,aspect_ratio);
            drawFractalCircle(x , y+ difference_y, z, radius*aspect_ratio,no_of_sides,difference_x,difference_y,aspect_ratio);
            drawFractalCircle(x , y- difference_y, z, radius*aspect_ratio,no_of_sides,difference_x,difference_y,aspect_ratio);
        }
    }
    void drawFractalCircle(GLfloat x, GLfloat y, GLfloat z,  GLfloat radius, GLint no_of_sides, float aspect_ratio, int option){  //!sorts functions accordingly
        if(option==1){
            drawFractalCircle1(x,y,z,no_of_sides, radius,aspect_ratio);
        }
        else if (option==2){
            drawFractalCircle2(x,y,z,radius,no_of_sides, aspect_ratio);
        }
 
 
    }
   
};
class Graphic{                  //!class to implement GUI
public:
    GLFWwindow *window;
    int start(int width, int height){           //! initializes glfw and creates window
       
        if ( !glfwInit( ) )//Initialize
        {
            return -1;
        }
        window = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL);//!Create window
        if (!window) //if we are unable to initialize, terminate
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glViewport(0.0f, 0.0f, width, height); 
        glMatrixMode(GL_PROJECTION);//!Projection view
        glLoadIdentity(); // !replace the current matrix with projection matrix
        glOrtho(0, width, 0, height, 0, 1); //! essentially set coordinate system
        glMatrixMode(GL_MODELVIEW); // !Default matrix mode
        glLoadIdentity();
        return 0;
    }
    int go(int width, int height,GLfloat line_x1,GLfloat line_y1,GLfloat line_z1, GLfloat line_x2,GLfloat line_y2,
     GLfloat line_z2, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint no_of_sides,
    float difference_x, float difference_y, float aspect_ratio){
        int check= start(width, height);
        if (check==-1) return -1;
        while (!glfwWindowShouldClose(window)) //!Loop until the user closes the window
        {
            glClear(GL_COLOR_BUFFER_BIT);
            GUI gui;
            gui.drawFractalLine(line_x1, line_y1, line_z1, line_x2, line_y2, line_z2);
            FractalCircles fg;
            fg.drawFractalCircle(x, y, z, radius, no_of_sides, difference_x, difference_y, aspect_ratio);
           
            glfwSwapBuffers(window);//! Swap front and back buffers
           
         
            glfwPollEvents( );
        }
       
        glfwTerminate( );
        return 0;
    }
    int go(int width, int height,GLfloat line_x1,GLfloat line_y1,GLfloat line_z1, GLfloat length, GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint no_of_sides,
            float aspect_ratio, int option){
        int check= start(width, height);
        if (check==-1) return -1;
        while (!glfwWindowShouldClose(window)) //!Loop until the user closes the window
        {
            glClear(GL_COLOR_BUFFER_BIT);
            GUI gui;
            gui.drawFractalLine(line_x1, line_y1, line_z1, length);
            FractalCircles fg;
            fg.drawFractalCircle(x, y, z, radius, no_of_sides, aspect_ratio, option);
            //! Swap front and back buffers
            glfwSwapBuffers( window );
           
            glfwPollEvents( );
        }
       
        glfwTerminate( );
        return 0;
       
    }
 
};
 
int main(int argc, char *argv[] )
{
    /*Example 1:
    Graphic g;
    int check=g.start(300,300);
    if(check==-1) return -1;
    while (!glfwWindowShouldClose(g.window)) //Loop until the user closes the window
        {
            glClear(GL_COLOR_BUFFER_BIT);
            GUI gui;
            gui.drawFractalLine(20,200,0,20,20,0);
            FractalCircles fg;
            fg.drawFractalCircle(110,110, 0, 90, 36,0.5,2);
            // Swap front and back buffers
            glfwSwapBuffers( g.window );
           
            // Poll for and process events
            glfwPollEvents( );
        }
       
        glfwTerminate( );
        return 0; */
    /*Example 2:
    Graphic g;
    int check=g.start(300,300);
    if(check==-1) return -1;
    while (!glfwWindowShouldClose(g.window)) //Loop until the user closes the window
        {
            glClear(GL_COLOR_BUFFER_BIT);
            GUI gui;
            gui.drawFractalLine(20,20,0,250);
            glfwSwapBuffers( g.window );
           
            // Poll for and process events
            glfwPollEvents( );
        }
       
        glfwTerminate( );
        return 0;
    */
    //Example 3:
    Graphic g;
    int check=g.start(300,300);
    if(check==-1) return -1;
    while (!glfwWindowShouldClose(g.window)) //Loop until the user closes the window
        {
            glClear(GL_COLOR_BUFFER_BIT);
            FractalCircles fg;
            fg.drawFractalCircle(150,150,0,100,36,0.5);
            // Swap front and back buffers
            glfwSwapBuffers( g.window );
           
            // Poll for and process events
            glfwPollEvents( );
        }
       
        glfwTerminate( );
        return 0;
   
   
}