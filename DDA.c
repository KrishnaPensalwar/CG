//DDALine
#include<stdio.h>
#include<GL/glut.h>
int xa,ya,xb,yb,choice;
int Round(float a)
{
	return (int)(a+0.5);
}
void DDA(int xa,int ya,int xb,int yb,int choice)
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
	float x,y;
	x=xa;
	y=ya;
	glVertex2d(Round(x),Round(y));
	xin=dx/(float)(steps);
	yin=dy/(float)(steps);
	glBegin(GL_POINTS);
	for(int i=0;i<steps;i++)
	{
		switch(choice)
		{
			case 1:
			x=x+xin;
			y=y+yin;
			glVertex2d(Round(x),Round(y));
			break;
			
			case 2:
			if(i%2==0)
			{
				glVertex2d(Round(x),Round(y));
			}
			x=x+xin;
			y=y+yin;
			break;
			
			case 3:
			if(i%8!=0)
			{
				glVertex2d(Round(x),Round(y));
			}
			x=x+xin;
			y=y+yin;
			break;
			
			case 4:
			glVertex2d(Round(x),Round(y));
			x=x+xin;
			y=y+yin;
			break;
		}
	}
	glEnd();
	glFlush();
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,0.0);
	DDA(0,240,640,240,1);
	DDA(320,0,320,480,1);
	
	/*glColor3f(1.0,0.0,0.0);
	DDA(xa,ya,xb,yb,choice);*/
	glEnd();
	glFlush();
}
void Draw1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,0.0);
	DDA(0,240,640,240,1);
	DDA(320,0,320,480,1);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,0.0);
	glEnd();
	glFlush();
}
void Mouse(int button,int state,int x,int y)
{
	y=480-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xa=x;
		ya=y;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		xb=x;
		yb=y;
		glColor3f(1.0,0.0,0.0);
		DDA(xa,ya,xb,yb,choice);
	}
}
int main(int argc,char **argv)
{
	/*printf("Enter First Point:\n");
	printf("Enter xa:");
	scanf("%d",&xa);
	printf("Enter ya:");
	scanf("%d",&ya);
	printf("Enter Second Point:\n");
	printf("Enter xb:");
	scanf("%d",&xb);
	printf("Enter yb:");
	scanf("%d",&yb);*/
	printf("Enter Which Line You Want to Draw:\n1)Simple Line\n2)Dotted Line\n3)Dashed Line\n4)Solid Line\n");
	scanf("%d",&choice);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE||GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("DDA LINE");
	gluOrtho2D(0,640,0,480);
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1.0,0.0,0.0);
	if(choice==4)
	{
		glutDisplayFunc(Draw1);
	}
	else
	{
		glutDisplayFunc(Draw);
	}
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}
