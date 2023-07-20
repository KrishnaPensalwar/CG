#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
int xc,yc,r;

int Round(float m)
{
	return (int)(m+0.5);
}
void Circle(int xc,int yc,int r)
{
	int x=0;
	int y=r;
	int d=3-2*r;
	do
	{
		glVertex2d(x+xc,y+yc); 
		glVertex2d(y+xc,x+yc);
		glVertex2d(-y+xc,x+yc);
		glVertex2d(-x+xc,y+yc);
		glVertex2d(-x+xc,-y+yc);
		glVertex2d(-y+xc,-x+yc);
		glVertex2d(y+xc,-x+yc);
		glVertex2d(x+xc,-y+yc);
		
		if(d<0)
		{
			x=x+1;
			d=d+4*x+6;
		}
		else
		{
			x=x+1;
			y=y-1;
			d=d+4*(x-y)+10;
		}
	}while(y>=x);
}
void DDA(int xa,int ya,int xb,int yb)
{
	int dx,dy,steps;
	dx=xb-xa;
	dy=yb-ya;
	if(abs(dx)>abs(dy))
	{
		steps=abs(dx);
	}
	else
	{
		steps=abs(dy);
	}
	float xin,yin;
	int x,y;
	x=xa;
	y=ya;
	xin=dx/(float)(steps);
	yin=dy/(float)(steps);
	glVertex2d(Round(x),Round(y));
	for(int i=0;i<steps;i++)
	{
		x=x+xin;
		y=y+yin;
		glVertex2d(Round(x),Round(y));
	}
}
void Mouse(int button,int state,int a,int b)
{
	b=480-b;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xc=a;
		yc=b;
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
		Circle(xc,yc,r);
		glutPostRedisplay();
		glEnd();
		glFlush();
	}
}
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,0.0);
	DDA(320,0,320,480);
	DDA(0,240,640,240);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,1.0,0.0);
	Circle(xc,yc,r);
	glEnd();
	glFlush();
}
int main(int argc,char **argv)
{
	/*printf("Enter Center Points:\n");
	printf("Enter X:");
	scanf("%d",&xc);
	printf("Enter Y:");
	scanf("%d",&yc);*/
	printf("Enter Radius:");
	scanf("%d",&r);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE||GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Circle");
	gluOrtho2D(0,640,0,480);
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,1.0,0.0);
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}

