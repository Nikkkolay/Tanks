#include<GL/glut.h>
#include<GL/GLAux.h>
#include<stdio.h>
#include<windows.h>
#include"bullshit.hpp"
#define X 48
#define Y 32
int pole[X][Y];
float gamemode=1.;
unsigned int textures[17];
struct Tank
{
    int team;
    int XP;
    int direction;
    float tank_position[2];
    float tank_speed;
    float timer_speed_X;
    float timer_speed_Y;
    int move_status_X;
    int move_status_Y;
    int shell_status;
    int shell_direction;
    float shell_position[2];
    float shell_speed;
};
Tank green;
void green_start_pozition()
{
    green.team=0;
    green.XP=4;
    green.direction=1;
    green.tank_position[0]=7;
    green.tank_position[1]=7;
    green.tank_speed=0.17;
    green.shell_speed=0.8;
    green.shell_status=0;
}
Tank blue;

void blue_start_pozition()
{
    blue.team=1;
    blue.XP=4;
    blue.direction=3;

    blue.tank_position[0]=41;
    blue.tank_position[1]=24;
    blue.tank_speed=0.17;
    blue.shell_speed=0.8;
    blue.shell_status=0;
}

void LoadTextures();
void timer(int);
void draw();
void PVP();

void mouse(int button,int state,int x,int y);
void keyboard(unsigned char key,int x,int y);
void keyboardUp(unsigned char key,int x,int y);
void Skeyboard(int key, int x, int y);
void SkeyboardUp(int key, int x, int y);

//void Shot_in_the_tank(float shell_position[2],int *shell_status,int *XP,float tank_position[2]);
int main(int argc,char **argv)
{
    SetConsoleOutputCP(1251);
  printf("инструкция\n\nуправление зелёным танком:\nдвижение -w/a/s/d\nстрельба-пробел\n\nуправление красным танком:\nдвижение -стрелки\nстрельба-'/'или '?'(в правой части клавиатуры)\n");

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(400,100);
    glutInitWindowSize(1200,800);
    glutCreateWindow("tanks");

    LoadTextures();
    glClearColor(217./255,177./255,108./255,1.);
    gluOrtho2D(0,X,0,Y);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(Skeyboard);
    glutSpecialUpFunc(SkeyboardUp);

    glutDisplayFunc(draw);
    glutTimerFunc(20,timer,0);

    glutMainLoop();
}

void LoadTextures()
{
    AUX_RGBImageRec//C:\\2_1Tank_Alpha_versia
    *texture1=auxDIBImageLoadA("textures\\green_tank.bmp"),
     *texture2=auxDIBImageLoadA("textures\\blue_tank.bmp"),
      *texture3=auxDIBImageLoadA("textures\\sovet.bmp"),
       *texture4=auxDIBImageLoadA("textures\\swast.bmp"),
        *texture5=auxDIBImageLoadA("textures\\brick.bmp"),
         *texture6=auxDIBImageLoadA("textures\\water.bmp"),
          *texture7=auxDIBImageLoadA("textures\\brick02.bmp"),
           *texture8=auxDIBImageLoadA("textures\\PvP.bmp"),
            *texture9=auxDIBImageLoadA("textures\\creation.bmp"),
             *texture10=auxDIBImageLoadA("textures\\bots.bmp"),
              *texture11=auxDIBImageLoadA("textures\\100%.bmp"),
               *texture12=auxDIBImageLoadA("textures\\75%.bmp"),
                *texture13=auxDIBImageLoadA("textures\\50%.bmp"),
                 *texture14=auxDIBImageLoadA("textures\\25%.bmp"),
                  *texture15=auxDIBImageLoadA("textures\\0%.bmp"),
                    *texture16=auxDIBImageLoadA("textures\\greenWin.bmp"),
                     *texture17=auxDIBImageLoadA("textures\\blueWin.bmp");
    glGenTextures(17,&textures[0]);
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture1->sizeX,texture1->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture1->data);

    glBindTexture(GL_TEXTURE_2D,textures[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture2->sizeX,texture2->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture2->data);

    glBindTexture(GL_TEXTURE_2D,textures[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture3->sizeX,texture3->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture3->data);

    glBindTexture(GL_TEXTURE_2D,textures[3]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture4->sizeX,texture4->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture4->data);

    glBindTexture(GL_TEXTURE_2D,textures[4]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture5->sizeX,texture5->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture5->data);

    glBindTexture(GL_TEXTURE_2D,textures[5]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture6->sizeX,texture6->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture6->data);

    glBindTexture(GL_TEXTURE_2D,textures[6]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture7->sizeX,texture7->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture7->data);

    glBindTexture(GL_TEXTURE_2D,textures[7]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture8->sizeX,texture8->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture8->data);

    glBindTexture(GL_TEXTURE_2D,textures[8]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture9->sizeX,texture9->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture9->data);

    glBindTexture(GL_TEXTURE_2D,textures[9]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture10->sizeX,texture10->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture10->data);

    glBindTexture(GL_TEXTURE_2D,textures[10]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture11->sizeX,texture11->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture11->data);

    glBindTexture(GL_TEXTURE_2D,textures[11]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture12->sizeX,texture12->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture12->data);

    glBindTexture(GL_TEXTURE_2D,textures[12]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture13->sizeX,texture13->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture13->data);

    glBindTexture(GL_TEXTURE_2D,textures[13]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture14->sizeX,texture14->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture14->data);

    glBindTexture(GL_TEXTURE_2D,textures[14]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture15->sizeX,texture15->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture15->data);

     glBindTexture(GL_TEXTURE_2D,textures[15]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture16->sizeX,texture16->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture16->data);

     glBindTexture(GL_TEXTURE_2D,textures[16]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,texture17->sizeX,texture17->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture17->data);
}
void timer(int)
{
    draw();
    glutTimerFunc(20,timer,0);
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    if (gamemode==1.)
    {
        menu_display(textures[4],textures[7],textures[8],textures[9]);
    green_start_pozition();
    blue_start_pozition();
    map(pole);
    }
    if (gamemode>=2&&gamemode<3)
        PVP();

    glDisable(GL_TEXTURE_2D);
      glColor3f(0.,0.,0.5);
      //grid();
    glutSwapBuffers();
}




void PVP()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
   if(green.XP>0&&blue.XP>0)
    {
        PVP_display(pole,textures);
        heart(textures,blue.XP,38.,30.,2.);

        moving(blue.tank_position,blue.move_status_X,blue.move_status_Y,blue.tank_speed,&blue.timer_speed_X, &blue.timer_speed_Y,&blue.direction);
        ram(blue.tank_position,blue.direction,green.tank_position);
        obstacles(blue.tank_position,blue.direction,pole);

        tank(textures[1],blue.tank_position[0],blue.tank_position[1],blue.direction);

        heart(textures,green.XP,8.,30.,2.);
        moving(green.tank_position,green.move_status_X,green.move_status_Y,green.tank_speed,&green.timer_speed_X, &green.timer_speed_Y,&green.direction);
         ram(green.tank_position,green.direction,blue.tank_position);
        obstacles(green.tank_position,green.direction,pole);

        tank(textures[0],green.tank_position[0],green.tank_position[1],green.direction);

        if(green.shell_status==1)
        {
            glDisable(GL_TEXTURE_2D);
            shell_moving(green.shell_position,green.shell_direction,green.shell_speed);
            shell_walls(pole,green.shell_position,&green.shell_status);
            Shot_in_the_tank(green.shell_position,&green.shell_status,&blue.XP,blue.tank_position);
            glEnable(GL_TEXTURE_2D);
        }
        if(blue.shell_status==1)
        {
            glDisable(GL_TEXTURE_2D);
            shell_moving(blue.shell_position,blue.shell_direction,blue.shell_speed);
            shell_walls(pole,blue.shell_position,&blue.shell_status);
            Shot_in_the_tank(blue.shell_position,&blue.shell_status,&green.XP,green.tank_position);
            glEnable(GL_TEXTURE_2D);
        }

    }
    else
    {
    gamemode=2.5;
    if(blue.XP>0) Win(textures[16]);else
     Win(textures[15]);
}
}


void mouse(int button,int state,int x,int y)
{
    if(gamemode==1.&&button==GLUT_LEFT_BUTTON&&state==GLUT_UP&&x>525&&x<675&&y>125&&y<275)
    {
     gamemode=2.;

    }
    if(gamemode==1.&&button==GLUT_LEFT_BUTTON&&state==GLUT_UP&&x>350&&x<500&&y>300&&y<450)
        printf("This mode is in development!\n");
    if(gamemode==1.&&button==GLUT_LEFT_BUTTON&&state==GLUT_UP&&x>700&&x<850&&y>300&&y<450)
        printf("This mode is in development!\n");
    if(gamemode==2.5&&button==GLUT_LEFT_BUTTON&&x>904&&x<1185&&y>669&&y<778)
    {
        gamemode=1.;

    }
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {

    case 'a':
    {
        green.direction=4;
        green.move_status_X=-1;
    }
    break;

    case 'w':
    {

        green.direction=1;
        green.move_status_Y=1;
    }
    break;

    case 'd':
    {
        green.direction=2;
        green.move_status_X=1;
    }
    break;

    case 's':
    {
        green.direction=3;
        green.move_status_Y=-1;
    }
    break;
    }
}

void keyboardUp(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'a':
    {
        green.move_status_X=0;
        green.timer_speed_X=0.;
    }
    break;
    case 'w':
    {

        green.move_status_Y=0;
        green.timer_speed_Y=0.;
    }
    break;
    case 'd':
    {
        green.move_status_X=0;
        green.timer_speed_X=0.;
    }
    break;
    case 's':
    {
        green.move_status_Y=0;
        green.timer_speed_Y=0.;
    }
    break;

    case ' ':
    {
        if(green.shell_status==0)
        {
            green.shell_status=1;
            if(green.direction==1)
            {
                green.shell_position[0]=green.tank_position[0]-0.17;
                green.shell_position[1]=green.tank_position[1]+1;
            }
            if(green.direction==2)
            {
                green.shell_position[0]=green.tank_position[0]+1;
                green.shell_position[1]=green.tank_position[1]+0.17;
            }
            if(green.direction==3)
            {
                green.shell_position[0]=green.tank_position[0]+0.17;
                green.shell_position[1]=green.tank_position[1]-1;
            }
            if(green.direction==4)
            {
                green.shell_position[0]=green.tank_position[0]-1;
                green.shell_position[1]=green.tank_position[1]-0.17;
            }
            green.shell_direction=green.direction;
        }


    } break;
    case '/':
    {
        if(blue.shell_status==0)
        {
            blue.shell_status=1;
            if(blue.direction==1)
            {
                blue.shell_position[0]=blue.tank_position[0];
                blue.shell_position[1]=blue.tank_position[1]+0.5;
            }
            if(blue.direction==2)
            {
                blue.shell_position[0]=blue.tank_position[0]+0.5;
                blue.shell_position[1]=blue.tank_position[1];
            }
            if(blue.direction==3)
            {
                blue.shell_position[0]=blue.tank_position[0];
                blue.shell_position[1]=blue.tank_position[1]-0.5;
            }
            if(blue.direction==4)
            {
                blue.shell_position[0]=blue.tank_position[0]-0.5;
                blue.shell_position[1]=blue.tank_position[1];
            }
            blue.shell_direction=blue.direction;
        }


    }break;

     case 'y':blue.XP=0;break;
    }
}

void Skeyboard(int key, int x, int y)
{


    switch(key)
    {
    case GLUT_KEY_UP:
    {
        blue.direction=1;
        blue.move_status_Y=1;
    }
    break;
    case GLUT_KEY_DOWN:
    {
        blue.direction=3;
        blue.move_status_Y=-1;
    }
    break;
    case GLUT_KEY_LEFT:
    {
        blue.direction=4;
        blue.move_status_X=-1;
    }
    break;
    case GLUT_KEY_RIGHT:
    {
        blue.direction=2;
        blue.move_status_X=1;
    }
    break;
    }
    if(glutGetModifiers()==GLUT_ACTIVE_CTRL)
        if(blue.shell_status==0)
        {
            blue.shell_status=1;
            if(blue.direction==1)
            {
                blue.shell_position[0]=blue.tank_position[0]-0.17;
                blue.shell_position[1]=blue.tank_position[1]+1;
            }
            if(blue.direction==2)
            {
                blue.shell_position[0]=blue.tank_position[0]+1;
                blue.shell_position[1]=blue.tank_position[1]+0.17;
            }
            if(blue.direction==3)
            {
                blue.shell_position[0]=blue.tank_position[0]+0.17;
                blue.shell_position[1]=blue.tank_position[1]-1;
            }
            if(blue.direction==4)
            {
                blue.shell_position[0]=blue.tank_position[0]-1;
                blue.shell_position[1]=blue.tank_position[1]-0.17;
            }
            blue.shell_direction=blue.direction;
        }
}

void SkeyboardUp(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
    {
        blue.move_status_X=0;
        blue.timer_speed_X=0.;
    }
    break;
    case GLUT_KEY_UP:
    {

        blue.move_status_Y=0;
        blue.timer_speed_Y=0.;
    }
    break;
    case GLUT_KEY_RIGHT:
    {
        blue.move_status_X=0;
        blue.timer_speed_X=0.;
    }
    break;
    case GLUT_KEY_DOWN:
    {
        blue.move_status_Y=0;
        blue.timer_speed_Y=0.;
    }
    break;
    }
}
