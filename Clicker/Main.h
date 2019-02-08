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
	point_menu,														//Идентификатор меню												
	width = 500,				height = 500,
	score = 0,					Time,
	speed = 100,				loop = 0,
	choice = 0,														//Выбор круга
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

GLvoid LoadTextures();				//Загрузка текстур
GLvoid TimerScaleUp(GLint);			//Анимация кругов
GLvoid CreateEllipse();				//Создание кругов
GLvoid ResizeEllipse(GLint);		//Изменение размера
GLvoid DeleteEllipse(GLint n);		//Удаление круга
GLvoid ChoiceEllipse();				//Выбор круга

GLvoid RealiseBarUp();				//Статус бар игрового процесса
GLvoid GameOver();
GLvoid PlayerName();

GLvoid TableRecords();
GLvoid Options();

GLvoid MainMenu();
GLvoid TimerTime(GLint v);			//Анимация времени
GLvoid DrawGameObject();			//Отрисовка кругов
GLvoid Keyboard(unsigned char, int, int);
GLvoid MouseClck(GLint button, GLint state, GLint x, GLint y);
GLvoid Initialize(int, int);


#endif
