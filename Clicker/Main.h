#ifndef MAIN_H
#define MAIN_H


#include<ctime>
#include<cmath>
#include<Windows.h>
#include<cstring>
#include<fstream>
#include<iostream>
#include<mmsystem.h>
#include<glut.h>
#include<GLAux.h>

using namespace std;

GLuint texture[9];

GLint	
	point_menu,														//������������� ����												
	width = 500,				height = 500,
	score = 0,					Time,
	speed = 100,				loop = 0,
	choice = 0,														//����� �����
	random,
	deleteEllipse = 0,			counterName = 0;

GLfloat	
	R, G, B,
	angle, dx, dy;

char	
	Score_Str[] = "Score:",		Score_Buff[4]{},
	Time_Str[] = "Time:",		Time_Buff[3]{},
	NamePlayer[10]{},			BufferName[8]{};

GLboolean	
	coincide = false,			statusLoadFile = true,
	coincide_ = false,			statusName = false;

struct GameEllipse
{
	GLint k = 2, tmp = k;
	GLint x = rand() % (width - 50) + 30, y = rand() % (height - 90) + 30;
};

struct Records
{
	char name[8]{};
	char score_buff[4]{};
	GLint score;
	GLfloat y;
	GLboolean status = true;
};

struct Color
{
	GLfloat R, G, B;
	GLboolean rand = false;
	GLfloat	
		ChoiceColor_x1, ChoiceColor_y1,
		ChoiceColor_x2, ChoiceColor_y2;
};

GameEllipse ellipse[3];
Records records[10];
Records buffer[10];
Color *color = (Color*)malloc(sizeof(Color));

enum Point_Menu
{
	funcMenu,
	funcDrawGameObject,
	funcGameOver,
	funcOptions,
	funcRecords
};

enum Textures
{
	FrameMenu,
	FrameRecords,
	FrameOptions,
	FrameGame,
	FrameGameOver,
	BTN_Menu,
	BTN_NewGame,
	BTN_Options,
	BTN_Records
};

GLvoid LoadTextures();				//�������� �������
GLvoid TimerScaleUp(GLint);			//�������� ������
GLvoid CreateEllipse();				//�������� ������
GLvoid ResizeEllipse(GLint);		//��������� �������
GLvoid DeleteEllipse(GLint n);		//�������� �����
GLvoid ChoiceEllipse();				//����� �����

GLvoid RealiseBarUp();				//������ ��� �������� ��������
GLvoid GameOver();
GLvoid PlayerName();

GLvoid TableRecords();
GLvoid Options();

GLvoid MainMenu();
GLvoid TimerTime(GLint v);			//�������� �������
GLvoid DrawGameObject();			//��������� ������
GLvoid Keyboard(unsigned char, int, int);
GLvoid MouseClck(GLint button, GLint state, GLint x, GLint y);
GLvoid Initialize(int, int);


#endif
