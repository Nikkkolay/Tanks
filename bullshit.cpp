#include"bullshit.hpp"
#include<stdio.h>
#include<GL/glut.h>
#define X 48
#define Y 32
float a=0;
void map(int pole[X][Y])
{
    for(int i=0; i<X; i++)  //barrier
        for(int k=0; k<1; k++)
            pole[i][k]=1;
    for(int i=0; i<X; i++)
        for(int k=Y; k>Y-3; k--)
            pole[i][k]=1;
    for(int i=0; i<1; i++)
        for(int k=0; k<Y; k++)
            pole[i][k]=1;
    for(int i=X-1; i<X; i++)
        for(int k=0; k<Y; k++)
            pole[i][k]=1;
    for(int i=1; i<6; i++)
        pole[i][5]=1;
    for(int i=1; i<5; i++)
        pole[5][i]=1;
    for(int i=42; i<47; i++)
        pole[i][25]=1;
    for(int i=25; i<30; i++)
        pole[42][i]=1;

    for(int i=20; i<28; i++) //water
        for(int k=14; k<18; k++)
            pole[i][k]=2;
    for(int i=21; i<27; i++)
        pole[i][18]=2;
    for(int i=21; i<27; i++)
        pole[i][13]=2;
    pole[23][19]=2;
    pole[24][19]=2;
    pole[23][12]=2;
    pole[24][12]=2;


    for(int i=6; i<15; i++) //red btick
        pole[40][i]=3;
    for(int i=31; i<40; i++)
        for(int k=18; k<20; k++)
            pole[i][k]=3;
    for(int i=20; i<27; i++)
        for(int k=31; k<33; k++)
            pole[k][i]=3;
    for(int k=18; k<27; k++)
        pole[k][24]=3;
    for(int k=11; k<34; k++)
        pole[k][8]=3;
    pole[11][9]=3;
    pole[11][10]=3;
    for(int k=4; k<9; k++)
        pole[13][k]=3;
    for(int k=4; k<9; k++)
        pole[33][k]=3;
    for(int i=13; i<34; i++)
        if(i!=24&&i!=25&&i!=26)
            pole[i][4]=3;
    for(int k=14; k<17; k++)
        pole[11][k]=3;
    for(int k=20; k<23; k++)
        pole[11][k]=3;
    for(int k=26; k<29; k++)
        pole[11][k]=3;
    for(int i=1; i<8; i++)
        for(int k=15; k<17; k++)
            pole[i][k]=3;
}
void moving(float tank_position[2],int move_status_X,int move_status_Y,float tank_speed,float *timer_speed_X,float *timer_speed_Y,int *direction)
{
 if(move_status_Y!=0) *timer_speed_Y+=0.01;                         //movement of the GREEN tank
    if(move_status_X!=0) *timer_speed_X+=0.01;

    if(move_status_Y!=0&&move_status_X!=0)
    {
        if(*timer_speed_Y<*timer_speed_X)
            tank_position[1]+=move_status_Y*tank_speed;
        if(*timer_speed_Y>*timer_speed_X)
            tank_position[0]+=move_status_X*tank_speed;
    }
    else
    {
        tank_position[0]+=move_status_X*tank_speed;
        tank_position[1]+=move_status_Y*tank_speed;
    }
    if(move_status_Y==1&&move_status_X==0) *direction=1;//
    if(move_status_Y==-1&&move_status_X==0) *direction=3;
    if(move_status_Y==0&&move_status_X==1) *direction=2;
    if(move_status_Y==0&&move_status_X==-1) *direction=4;
}
void obstacles(float tank_position[2],int direction,int pole[X][Y])
{
    float x1=tank_position[0];
    float y1=tank_position[1];
    int x=(int)x1;
    int y=(int)y1;
    for(int i=x-2; i<x+2; i++)
        for(int k=y-2; k<y+2; k++)
            if(pole[i][k]!=0)
            {
                if(i+0.5<tank_position[0]-1&&i+1>tank_position[0]-1&&tank_position[1]+1>k*1.&&tank_position[1]-1<k+1.0&&direction==4)
                    tank_position[0]=i+2.;

                if(i+0.5>tank_position[0]+1&&i<tank_position[0]+1&&tank_position[1]+1>k*1.&&tank_position[1]-1<k+1.0&&direction==2)
                    tank_position[0]=i-1;

                if(tank_position[0]+1.0>i*1.&&tank_position[0]-1<i+1.&&tank_position[1]+1>k*1.&&tank_position[1]+1<k+0.5&&direction==1)
                    tank_position[1]=k-1;

                if(tank_position[0]+1.0>i*1.&&tank_position[0]-1<i+1.&&tank_position[1]-1<k+1.&&tank_position[1]+1>k+1.&&direction==3)
                    tank_position[1]=k+2;
            }
}
void shell_moving(float shell_position[2],int shell_direction,float shell_speed)
{

    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
    glVertex2f(0.1+shell_position[0],0.1+shell_position[1]);
    glVertex2f(0.1+shell_position[0],-0.1+shell_position[1]);
    glVertex2f(-0.1+shell_position[0],-0.1+shell_position[1]);
    glVertex2f(-0.1+shell_position[0],0.1+shell_position[1]);
    glEnd();
    glColor3f(1,1,1);
    if(shell_direction==1) shell_position[1]+=shell_speed;
    if(shell_direction==2) shell_position[0]+=shell_speed;
    if(shell_direction==3) shell_position[1]-=shell_speed;
    if(shell_direction==4) shell_position[0]-=shell_speed;
}
void shell_walls(int pole[48][32],float shell_position[2],int *shell_status)
{
    float x1=shell_position[0];
    float y1=shell_position[1];
    int x=(int)x1;
    int y=(int)y1;
    for(int i=x-1; i<x+1; i++)
        for(int k=y-1; k<y+1; k++)
            if(shell_position[0]+0.1>i && shell_position[0]-0.1<i+1 && shell_position[1]+0.1>k && shell_position[1]-0.1<k+1&&pole[i][k]!=0&&pole[i][k]!=2)
            {
                if(pole[i][k]!=1) pole[i][k]=0;
                *shell_status=0;
            }
}

void Shot_in_the_tank(float shell_position[2],int *shell_status,int *XP,float tank_position[2])
{
    if(tank_position[0]-1<=shell_position[0]&&tank_position[0]+1>=shell_position[0]&&tank_position[1]-1<=shell_position[1]&&tank_position[1]+1>=shell_position[1])
    {
         if(*XP!=0) *XP=*XP-1;
        *shell_status=0;
    }
}

void tank(unsigned int textur,float x,float y,int direction)
{
    glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,textur);
    if(direction==1)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(-1+x,-1+y);
        glTexCoord2f(0,1);
        glVertex2f(-1+x,1+y);
        glTexCoord2f(1,1);
        glVertex2f(1+x,1+y);
        glTexCoord2f(1,0);
        glVertex2f(1+x,-1+y);
        glEnd();
    }
    if(direction==2)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(1,0);
        glVertex2f(-1+x,-1+y);
        glTexCoord2f(0,0);
        glVertex2f(-1+x,1+y);
        glTexCoord2f(0,1);
        glVertex2f(1+x,1+y);
        glTexCoord2f(1,1);
        glVertex2f(1+x,-1+y);
        glEnd();
    }
    if(direction==3)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex2f(-1+x,-1+y);
        glTexCoord2f(1,0);
        glVertex2f(-1+x,1+y);
        glTexCoord2f(0,0);
        glVertex2f(1+x,1+y);
        glTexCoord2f(0,1);
        glVertex2f(1+x,-1+y);
        glEnd();
    }
    if(direction==4)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex2f(-1+x,-1+y);
        glTexCoord2f(1,1);
        glVertex2f(-1+x,1+y);
        glTexCoord2f(1,0);
        glVertex2f(1+x,1+y);
        glTexCoord2f(0,0);
        glVertex2f(1+x,-1+y);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void menu_display(unsigned int brick,unsigned int PVP,unsigned int CRE,unsigned int PVE)
{
   glEnable(GL_TEXTURE_2D);
   glColor3f(a,a,a);
    glBindTexture(GL_TEXTURE_2D,brick);
   for(int i=0; i<X; i++)
        for(int k=0; k<Y; k++)
            {
                glBegin(GL_QUADS);//4
                glTexCoord2f(0,0);
                glVertex2f(i,k);
                glTexCoord2f(1,0);
                glVertex2f(i+1,k);
                glTexCoord2f(1,1);
                glVertex2f(i+1,k+1);
                glTexCoord2f(0,1);
                glVertex2f(i,k+1);
                glEnd();
            }
  glBindTexture(GL_TEXTURE_2D,PVP);//7
                glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(21,21);
                glTexCoord2f(1,0);
                glVertex2f(27,21);
                glTexCoord2f(1,1);
                glVertex2f(27,27);
                glTexCoord2f(0,1);
                glVertex2f(21,27);
                glEnd();

glBindTexture(GL_TEXTURE_2D,CRE);//8
                glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(14,14);
                glTexCoord2f(1,0);
                glVertex2f(20,14);
                glTexCoord2f(1,1);
                glVertex2f(20,20);
                glTexCoord2f(0,1);
                glVertex2f(14,20);
                glEnd();

glBindTexture(GL_TEXTURE_2D,PVE);//9
                glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(28,14);
                glTexCoord2f(1,0);
                glVertex2f(34,14);
                glTexCoord2f(1,1);
                glVertex2f(34,20);
                glTexCoord2f(0,1);
                glVertex2f(28,20);
                glEnd();
     glDisable(GL_TEXTURE_2D);

     if(a!=1) a+=0.003;
}
void PVP_display(int pole[X][Y],unsigned int textures[])
{
    glEnable(GL_TEXTURE_2D);
 for(int i=0; i<X; i++)
        for(int k=0; k<Y; k++)
            if(pole[i][k]!=0)
            {

                glBindTexture(GL_TEXTURE_2D,textures[3+pole[i][k]]);
                glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(i,k);
                glTexCoord2f(1,0);
                glVertex2f(i+1,k);
                glTexCoord2f(1,1);
                glVertex2f(i+1,k+1);
                glTexCoord2f(0,1);
                glVertex2f(i,k+1);
                glEnd();

            }
    glBindTexture(GL_TEXTURE_2D,textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(1,1);
    glTexCoord2f(1,0);
    glVertex2f(5,1);
    glTexCoord2f(1,1);
    glVertex2f(5,5);
    glTexCoord2f(0,1);
    glVertex2f(1,5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(43,26);
    glTexCoord2f(0,1);
    glVertex2f(47,26);
    glTexCoord2f(1,1);
    glVertex2f(47,30);
    glTexCoord2f(1,0);
    glVertex2f(43,30);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void heart(unsigned int textures[],int XP,float Xposition,float Yposition,float Size)
{
glEnable(GL_TEXTURE_2D);

if(XP==4) glBindTexture(GL_TEXTURE_2D,textures[10]);
if(XP==3) glBindTexture(GL_TEXTURE_2D,textures[11]);
if(XP==2) glBindTexture(GL_TEXTURE_2D,textures[12]);
if(XP==1) glBindTexture(GL_TEXTURE_2D,textures[13]);
if(XP==0) glBindTexture(GL_TEXTURE_2D,textures[14]);
glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(Xposition,Yposition);
        glTexCoord2f(1,0);
        glVertex2f(Xposition+Size,Yposition);
        glTexCoord2f(1,1);
        glVertex2f(Xposition+Size,Yposition+Size);
        glTexCoord2f(0,1);
        glVertex2f(Xposition,Yposition+Size);
        glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Win (unsigned int texture)
{
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture);
 glBegin(GL_QUADS);
        glTexCoord2f(1-240./256,0);
        glVertex2f(0,0);
        glTexCoord2f(1,0);
        glVertex2f(48,0+0);
        glTexCoord2f(1,160./256);
        glVertex2f(48,32);
        glTexCoord2f(1-240./256,160./256);
        glVertex2f(0,32);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}

void ram(float active[2],int direction,float passive[2])
{
if(direction==1&&active[0]+1>passive[0]-1&&active[0]-1<passive[0]+1&&active[1]+1>passive[1]-1&&active[1]+1<passive[1]) active[1]=passive[1]-2;
if(direction==2&&active[1]+1>passive[1]-1&&active[1]-1<passive[1]+1&&active[0]+1>passive[0]-1&&active[0]+1<passive[0]) active[0]=passive[0]-2;
if(direction==3&&active[0]+1>passive[0]-1&&active[0]-1<passive[0]+1&&active[1]-1<passive[1]+1&&active[1]-1>passive[1]) active[1]=passive[1]+2;
if(direction==4&&active[1]+1>passive[1]-1&&active[1]-1<passive[1]+1&&active[0]-1<passive[0]+1&&active[0]-1>passive[0]) active[0]=passive[0]+2;
}
void grid()
{
 glColor3f(0.,0.,0.5);
 glBegin(GL_LINES);
     for(float i=0;i<=X;i+=1.)
     {
       glVertex2f(i,0);
       glVertex2f(i,Y);
     }
    for(float i=0;i<=Y;i+=1.)
     {
       glVertex2f(0,i);
       glVertex2f(X,i);
     }
     glEnd();
}
