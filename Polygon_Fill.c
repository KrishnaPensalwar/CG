#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

int v,xa,ya,xb,yb;
int q;
int xin=0,yin=0;

float bc[3],boundary[3],fill[3];

int Round(float a)
{
	return a+0.5;
}

void ddaline(int xa,int ya,int xb,int yb){
	int dx=xb-xa;
	int dy=yb-ya;
	int steps;
	if(abs(dx)>abs(dy)){
		steps=abs(dx);
	}
	else{
		steps=abs(dy);
	}
	float xin=dx/(float)(steps);
	float yin=dy/(float)(steps);
	float x=xa;
	float y=ya;
	glBegin(GL_POINTS);
	glVertex2d(Round(x),Round(y));
	for(int i=0;i<steps;i++){
		x=x+xin;
		y=y+yin;
		glVertex2d(Round(x),Round(y));
	}
	
}


void floodfill(float bc[],float fill[],int x,int y){
	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	glColor3f(fill[0],fill[1],fill[2]);
	if((color[0]==bc[0] && color[1]==bc[1] && color[2]==bc[2]) && (color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2])){
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		floodfill(bc,fill,x+2,y);
		floodfill(bc,fill,x,y+2);
		floodfill(bc,fill,x,y-2);
		floodfill(bc,fill,x-2,y);
	}
}
void boundaryfilling(float boundary[],float fill[],int x,int y){

	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	glColor3f(fill[0],fill[1],fill[2]);
	if((color[0]!=boundary[0] || color[1]!=boundary[1] || color[2]!=boundary[2]) && (color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2])){
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		boundaryfilling(boundary,fill,x+2,y);
		boundaryfilling(boundary,fill,x-2,y);
		boundaryfilling(boundary,fill,x,y+2);
		boundaryfilling(boundary,fill,x,y-2);
	}
}

void myMouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
         
         xin = x;
         yin = 540-y;
         if(q==1){
         	boundaryfilling(boundary,fill,xin,yin);
         }
         else if(q==2){
            floodfill(bc,fill,xin,yin);
         }
     }

}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glBegin(GL_POINTS);
	int i;
	glColor3f(boundary[0],boundary[1],boundary[2]);
	for(i=0;i<v-1;i++){
		ddaline(poly[0][i],poly[1][i],poly[0][i+1],poly[1][i+1]);
	}
	ddaline(poly[0][0],poly[1][0],poly[0][i],poly[1][i]);
	glutMouseFunc(myMouse);
	glEnd();
	glFlush();
}

int main(int argc,char **argv){
	printf("enter no.of vertex: ");
	scanf("%d",&v);
	int val;
	for(int i=0; i<v;i++){
		printf("enter x: ");
		scanf("%d",&val);
		poly[0][i]=val;
		printf("enter y: ");
		scanf("%d",&val);
		poly[1][i]=val;
	
	}
	printf("enter the background color: ");
	for(int i=0; i<3;i++){
		scanf("%f",&bc[i]);	
	}
	printf("enter the boundary color: ");
	for(int i=0; i<3;i++){
		scanf("%f",&boundary[i]);	
	}
	printf("enter the fill color: ");
	for(int i=0; i<3;i++){
		scanf("%f",&fill[i]);	
	}printf("enter what to do :: 1=boundaryfill 2=floodfill");
	scanf("%d",&q);
	
	printf("inside x co-ordinate: ");
	scanf("%d",&xin);
	printf("inside y co-ordinate: ");
	scanf("%d",&yin);
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,520);
	glutInitWindowPosition(0,0);
	glutCreateWindow("polygon");
	glClearColor(bc[0],bc[1],bc[2],0.0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0,640,0,520);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
	
}

