#ifndef bullshit.hpp
#define bullshit.hpp
#define X 48
#define Y 32
void map(int pole[48][32]);
void moving(float tank_position[2],int move_status_X,int move_status_Y,float tank_speed,float *timer_speed_X,float *timer_speed_Y,int *direction);
void obstacles(float tank_position[2],int direction,int pole[48][32]);
void shell_moving(float shell_position[2],int shell_direction,float shell_speed);
void shell_walls(int pole[48][32],float shell_position[2],int *shell_status);
void Shot_in_the_tank(float shell_position[2],int *shell_status,int *XP,float tank_position[2]);

void menu_display(unsigned int brick,unsigned int PVP,unsigned int CRE,unsigned int PVE);
void PVP_display(int pole[X][Y],unsigned int textur[]);
void tank(unsigned int textur,float x,float y,int direction);

void heart(unsigned int textures[],int XP,float Xposition,float Yposition,float Size);
void Win (unsigned int texture);

void ram(float active[2],int direction,float passive[2]);
void grid();
#endif // bullshit
