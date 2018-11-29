#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include<cstdio>
#include<string>
 
using namespace std;
 
class Point{
    /**This class is used to store the points in the line*/
private:
    int x, y;
 
public:
    Point(int X,int Y){
        /**Initializes the point*/
        x= X; //x coordinate
        y=Y; //y coordinate
    }
 
    int getx(){
        /**Get x coordinate*/
        return x;
    }
 
    int gety(){
        /** Get y coordinate*/
        return y;
    }
 
    void printPoint(){
        /** Prints the x and y corrdinate*/
        cout << x << ", " << y << '\n';
    }
};
 
 
class Line{
    /**This class is used to implement lines*/
    private:
        Point start, end;
        int d,x,y,dx,dy;
        vector<Point> points_in_the_line;
 
        void getLineSlopeGreaterThanOrEqualTo1(){
            /**Function to find all the points in the line when the slope is >=1*/
            //!cout << "Slope Greater Than Or Equal To 1\n";
            //!cout << x << ", " << y << '\n';
            Point point(x,y);
            points_in_the_line.push_back(point);
            while (x<end.getx()){
                if (d<=0){
                    d+=2*dy;
                }
                else{
                    d+=(2*(dy-dx));
                    y++;
                }
                x++;
                //cout << x << ", " << y << '\n';
                Point point(x,y);
                points_in_the_line.push_back(point);
            }
        }
 
        void getLineSlopeLessThan1(){
            //!cout << "Slope Less Than 1\n";
            //!cout << x << ", " << y << '\n';
            Point point(x,y);
            points_in_the_line.push_back(point); //!pusing the first point into the vector
            while (y<end.gety()){
                if (d<=0){
                    d+=2*dx;
                }
                else{
                    d+=(2*(dx-dy));
                    x++;
                }
                y++;
                //!cout << x << ", " << y << '\n';
                Point point(x,y);
                points_in_the_line.push_back(point);
            }
        }
 
    public:
        Line(int start_x, int start_y, int end_x, int end_y): start(start_x,start_y), end(end_x, end_y){}
 
        vector<Point> getLine(){
            if (end.getx()<start.getx()){
                swap(end,start);
            }
            dx= end.getx()-start.getx();
            dy= end.gety()- start.gety();
            d= (2*dx)- dy;
            x= start.getx();
            y= start.gety();
            if (dy==0 || dx/dy >=1){
                getLineSlopeGreaterThanOrEqualTo1();
            }
            else{
                getLineSlopeLessThan1();
            }
            return points_in_the_line;
        }  
};
 
 
class Circle{
private:
   
    int x1,y1,r;
    std::vector<Point> points_in_circle;
public:
    Circle(int center_x,int center_y, int radius){
        x1= center_x;
        y1= center_y;
        r= radius;
        //cout << '\n' << x1 << ", " << y1 << ", " << r << '\n';
    }
 
    void plot(int x, int y)
    {
        //cout << x << ", " << y << '\n';
        Point point(x,y);
        points_in_circle.push_back(point);
    }
     
    void drawSymmetry(int x, int y)
    {
     //!Plot the 8-way symmetry  
        plot(x,y);
        plot(x,-y);
        plot(-x,y);
        plot(-x,-y);
        plot(y,x);
        plot(-y,x);
        plot(y,-x);
        plot(-y,-x);
    }
     
    vector<Point> drawCircle()
    {
       
        int x = 0;
        int y = r;
     
       
        int d = 1 - r;
     
        int deltaE = 3;
        int deltaSE = (-2 * y) + 5;
     
        drawSymmetry(x,y);
     
       
        while (y > x)
        {
            if(d < 0)
            {
                //!Select East point
                d += deltaE;
                deltaE += 2;
                deltaSE += 2;
            }
            else
            {
                //!Select South East point
                d += deltaSE;
                deltaE += 2;
                deltaSE += 4;
                y--;
            }
            x++;
     
            drawSymmetry(x,y);
        }
        return points_in_circle;
    }
 
};
 
 
class GUI{
private:
    GLFWwindow *window;
    int width, height;
 
    void plotPixel(Point p){
            GLfloat point_array[2]; //!The array for each point
            point_array[0]= p.getx();
            point_array[1]= p.gety();
            glVertexPointer(2, GL_FLOAT, 0, point_array);
            glDrawArrays(GL_POINTS, 0, 1); //! Draw the vertices
    }
public:
   
    GUI(int w, int h){
        width=w;
        height= h;
    }
 
    int GUIStart(){
        if(!glfwInit()) //!Initializing glfw
            {
                fprintf(stderr, "Failed to initialize GLFW\n");
                return -1;
            }
        window = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL); //!Create window
        if (!window){
            glfwTerminate(); //!Error in creating Window
            return -1;
        }
        glfwMakeContextCurrent(window);
        glViewport(0.0f, 0.0f, width, height); //!Configure the coordinate system
        glMatrixMode(GL_PROJECTION); //!View as projection
        glLoadIdentity();
        glOrtho(-width/2, width/2, -height/2, height/2, 0, 1); //!Set coordinate system as (0, screen width) as x axis range and (0, screen height) as y axis range
        glMatrixMode(GL_MODELVIEW); //! Switch back to default view
        glLoadIdentity();
        return 0;
 
    }
 
    int go(vector<Point> points){
        int check= GUIStart();
        while (!glfwWindowShouldClose(window)){
            glClear(GL_COLOR_BUFFER_BIT);//!Clear window
            glEnableClientState(GL_VERTEX_ARRAY); //!Using a vertex array
            
            for (auto i=points.begin();i!= points.end(); i++){
                Point &p= *i;
                plotPixel(p);
            }
            glDisableClientState(GL_VERTEX_ARRAY);
            glfwSwapBuffers(window);
            glfwPollEvents(); //!Poll events
        }
        glfwTerminate();
        return 0;
    }
};
 
void swap(Point& a, Point& b){
    Point temp = a;
    a = b;
    b = temp;
}
 
int main(int argc, char *argv[])
{
    GUI gui(300, 300);
    /*int x0= atoi(argv[1]);
    int x1= atoi(argv[3]);
    int y0= atoi(argv[2]);
    int y1= atoi(argv[4]);
    Line line(x0,y0,x1,y1);
    vector<Point> points_to_be_drawn= line.getLine();
    int x= gui.go(points_to_be_drawn);
    cout << x;*/
    int x0= atoi(argv[1]);
    int y0= atoi(argv[2]);
    int r= atoi(argv[3]);
    Circle circle(x0,y0,r);
    vector<Point> points_to_be_drawn= circle.drawCircle();
    /*for (auto i=points_to_be_drawn.begin();i!= points_to_be_drawn.end(); i++){
                Point &p= *i;
                p.printPoint();
            }*/
    int x= gui.go(points_to_be_drawn);
    //cout << x;
    return 0;
}