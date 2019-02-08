#include"Main.h"

GLvoid LoadTextures()
{
	AUX_RGBImageRec *TextureBmp[9];
	memset(TextureBmp, 0, sizeof(void *) * 9);
	TextureBmp[FrameMenu] = auxDIBImageLoadA("Texture/Frame Menu.bmp");
	TextureBmp[FrameRecords] = auxDIBImageLoadA("Texture/Records.bmp");
	TextureBmp[FrameOptions] = auxDIBImageLoadA("Texture/Options.bmp");
	TextureBmp[FrameGame] = auxDIBImageLoadA("Texture/Frame Game.bmp");
	TextureBmp[FrameGameOver] = auxDIBImageLoadA("Texture/Game Over.bmp");
	TextureBmp[BTN_Menu] = auxDIBImageLoadA("Texture/Buttons/Menu.bmp");
	TextureBmp[BTN_NewGame] = auxDIBImageLoadA("Texture/Buttons/New Game.bmp");
	TextureBmp[BTN_Options] = auxDIBImageLoadA("Texture/Buttons/Options.bmp");
	TextureBmp[BTN_Records] = auxDIBImageLoadA("Texture/Buttons/Records.bmp");
	glGenTextures(10, &texture[0]);
	for (int i = 0; i < 9; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureBmp[i]->sizeX, TextureBmp[i]->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, TextureBmp[i]->data);
	}
	for (int i = 0; i < 9; i++)
	{
		if (TextureBmp[i])
		{
			if (TextureBmp[i]->data)
				free(TextureBmp[i]->data);

			free(TextureBmp[i]);
		}
	}
}

GLvoid TimerScaleUp(GLint v)
{
	glutPostRedisplay();
	glutTimerFunc(speed, TimerScaleUp, v);
}

GLvoid CreateEllipse()
{
	R = rand() % 255 + 0, G = rand() % 255 + 0,
		B = rand() % 255 + 0;

	glBegin(GL_TRIANGLE_FAN);
	color->rand == false ? glColor3d(color->R, color->G, color->B) : glColor3d(R / 255, G / 255, B / 255);

	choice == 0 ? glVertex2d(ellipse[0].x, ellipse[0].y) :
		choice == 1 ? glVertex2d(ellipse[1].x, ellipse[1].y) :
		glVertex2d(ellipse[2].x, ellipse[2].y);

	for (int i = 0; i <= 360; i++)
	{
		angle = 2.0 * 3.1415 * (GLfloat)i / 360.0;
		dx = cosf(angle);
		dy = sinf(angle);

		choice == 0 ? glVertex2d(ellipse[0].x + dx * ellipse[0].k, ellipse[0].y + dy * ellipse[0].k) :
			choice == 1 ? glVertex2d(ellipse[1].x + dx * ellipse[1].k, ellipse[1].y + dy * ellipse[1].k) :
			glVertex2d(ellipse[2].x + dx * ellipse[2].k, ellipse[2].y + dy * ellipse[2].k);
	}
	glEnd();
	glColor3d(1.0, 1.0, 1.0);
}

GLvoid ResizeEllipse(GLint n)
{
	if (ellipse[n].tmp <= 20)
	{
		ellipse[n].tmp++;
		ellipse[n].k = ellipse[n].tmp;
	}
	else if (ellipse[n].tmp > 20 && ellipse[n].k > 2)
		ellipse[n].k--;
	else
	{
		ellipse[n].x = rand() % (width - 50) + 30;
		ellipse[n].y = rand() % (height - 90) + 30;

		ellipse[n].k = 2;
		ellipse[n].tmp = 2;
	}
}

GLvoid DeleteEllipse(GLint n)
{
	ellipse[n].tmp = 2; ellipse[n].k = 2; deleteEllipse = 0;
	ellipse[n].x = rand() % (width - 50) + 30;
	ellipse[n].y = rand() % (height - 90) + 30;
}

GLvoid ChoiceEllipse()
{
	if (deleteEllipse != 1)
	{
		choice = 0;
		CreateEllipse();
		ResizeEllipse(0);
	}
	else
		DeleteEllipse(0);

	if (deleteEllipse != 2)
	{
		random = rand() % 20 + 2;
		if (random == ellipse[0].k)coincide = true;

		if (coincide)
		{
			choice = 1;
			CreateEllipse();
			ResizeEllipse(1);
		}
	}
	else
		DeleteEllipse(1);

	if (deleteEllipse != 3)
	{
		random = rand() % 20 + 2;
		if (random == ellipse[0].k)coincide_ = true;

		if (coincide_)
		{
			choice = 2;
			CreateEllipse();
			ResizeEllipse(2);
		}
	}
	else
		DeleteEllipse(2);
}

GLvoid RealiseBarUp()
{
	glColor3f(1.0, 0.0, 1.0);
	glRasterPos2f(0, height - 24);
	for (int i = 0; Score_Str[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Score_Str[i]);

	glRasterPos2f(width - 400, height - 24);
	_itoa(score, Score_Buff, 10);
	for (int i = 0; Score_Buff[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Score_Buff[i]);

	glRasterPos2f(width - 100, height - 24);
	for (int i = 0; Time_Str[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Time_Str[i]);

	glRasterPos2f(width - 30, height - 24);
	_itoa(Time, Time_Buff, 10);
	for (int i = 0; Time_Buff[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Time_Buff[i]);
	glColor3f(1.0, 1.0, 1.0);
}

GLvoid GameOver()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	point_menu = funcGameOver;

	glBindTexture(GL_TEXTURE_2D, texture[FrameGameOver]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0, 1); glVertex2d(0.0, height);
		glTexCoord2d(1, 1); glVertex2d(width, height);
		glTexCoord2d(1, 0); glVertex2d(width, 0.0);
		glEnd();
	}

	glRasterPos2f(width - 320, height - 180);

	for (int i = 0; Score_Str[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Score_Str[i]);

	glRasterPos2f(width - 220, height - 180);
	_itoa(score, Score_Buff, 10);

	for (int i = 0; Score_Buff[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Score_Buff[i]);
	

	glBindTexture(GL_TEXTURE_2D, texture[BTN_Menu]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 370);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 320);
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 320);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 370);
		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid PlayerName()
{
	glBegin(GL_LINES);												//Choice color
	{
		glColor3d(1.0, 1.0, 1.0);
		glVertex2d(color->ChoiceColor_x1, height - 250);
		glVertex2d(color->ChoiceColor_x2, height - 300);
		glEnd();
	}
	glColor3f(1.0, 0.0, 1.0);
	if (records[counterName].status == false)
	{
		char temp[8]{};
		strcpy(buffer[counterName].name, temp);

		glRasterPos2f(width - 300, height - 150);
		for (int i = 0; i < 8; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
		records[counterName].status = true;
	}
	else
	{
		glRasterPos2f(width - 300, height - 150);
		for (int i = 0; i < loop; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[counterName].name[i]);
	}
	glColor3f(1.0, 1.0, 1.0);
}

GLvoid LoadRecords()
{
	ifstream fin("SaveRecords.txt");
	if (fin.peek() != '\n')
	{
		fin >> counterName;
		for (int i = counterName; i >= 0; i--)
		{
			fin >> buffer[i].name;
			fin >> buffer[i].score_buff;
		}
	}
	else
		counterName = 0;
	fin.close();
}

GLvoid SaveRecords(int n)
{
	ofstream fout("SaveRecords.txt");
	if (counterName < 10)
	{
		fout << counterName << endl;
		for (int i = 0; i <= n; i++)
		{
			fout << records[i].name << endl;
			fout << records[i].score_buff << endl;
		}

	}
	else if (counterName >= 10)
	{
		counterName = 9;
	}
	fout.close();
}

GLvoid TableRecords()
{
	int x;
	point_menu = funcRecords;

	records[5].y = records[0].y = height - 142;
	records[6].y = records[1].y = height - 190;
	records[7].y = records[2].y = height - 235;
	records[8].y = records[3].y = height - 280;
	records[9].y = records[4].y = height - 327;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[FrameRecords]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0, 1); glVertex2d(0.0, height);
		glTexCoord2d(1, 1); glVertex2d(width, height);
		glTexCoord2d(1, 0); glVertex2d(width, 0.0);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[BTN_Menu]);
	glBegin(GL_QUADS);												//Button
	{
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 450);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 400);
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 400);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 450);
		glEnd();
	}

	int a = counterName + 1;
	for (int i = 0, j = counterName; i < a, j >= 0; i++, j--)
	{
		strcpy(records[j].name, buffer[i].name);
		strcpy(records[j].score_buff, buffer[i].score_buff);
		records[j].score = buffer[i].score;
	}
	glColor3f(0.0, 0.0, 1.0);
	/*for (int i = 0; i < a; i++)
		for (int j = 1; j < a - i - j; j++)
		{
			char temp[8]{};
			int temp;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}*/
	
	if (records[counterName].score_buff[0] > 0 && records[counterName].name[0] != '\0')
	{
		//glColor3f(1.0, 0.0, 1.0);
		for (int n = 0; n <= counterName; n++)
		{
			n > 4 ? x = width - 210 : x = width - 440;
			glRasterPos2f(x, records[n].y);

			for (int i = 0; records[n].name[i] != '\0'; i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, records[n].name[i]);
		}
		for (int n = 0; n <= counterName; n++)
		{
			n > 4 ? x = width - 90 : x = width - 300;
			glRasterPos2f(x, records[n].y);
			for (int i = 0; records[n].score_buff[i] != '\0'; i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, records[n].score_buff[i]);
		}
		//glColor3f(1.0, 0.0, 1.0);
		//for (int i = 0; i <= counterName; i++)
		SaveRecords(counterName);
		glColor3f(1.0, 1.0, 1.0);
	}
	
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid Options()
{
	point_menu = funcOptions;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	R = rand() % 255 + 0, G = rand() % 255 + 0,
		B = rand() % 255 + 0;
	glBindTexture(GL_TEXTURE_2D, texture[FrameOptions]);
	glBegin(GL_QUADS);												//Frame
	{
		glTexCoord2d(0, 0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0, 1); glVertex2d(0.0, height);
		glTexCoord2d(1, 1); glVertex2d(width, height);
		glTexCoord2d(1, 0); glVertex2d(width, 0.0);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[BTN_Menu]);
	glBegin(GL_QUADS);												//Button
	{
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 450);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 400);
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 400);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 450);
		glEnd();
	}

	glBegin(GL_QUADS);												//Red
	{
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(width - 480, height - 300);
		glVertex2d(width - 480, height - 250);
		glVertex2d(width - 430, height - 250);
		glVertex2d(width - 430, height - 300);
		glEnd();
	}

	glBegin(GL_QUADS);												//Green
	{
		glColor3d(0.0, 1.0, 0.0);
		glVertex2d(width - 400, height - 300);
		glVertex2d(width - 400, height - 250);
		glVertex2d(width - 350, height - 250);
		glVertex2d(width - 350, height - 300);
		glEnd();
	}

	glBegin(GL_QUADS);												//Blue
	{
		glColor3d(0.0, 0.0, 1.0);
		glVertex2d(width - 320, height - 300);
		glVertex2d(width - 320, height - 250);
		glVertex2d(width - 270, height - 250);
		glVertex2d(width - 270, height - 300);
		glEnd();
	}

	glBegin(GL_QUADS);												//Black
	{
		glColor3d(0.0, 0.0, 0.0);
		glVertex2d(width - 240, height - 300);
		glVertex2d(width - 240, height - 250);
		glVertex2d(width - 190, height - 250);
		glVertex2d(width - 190, height - 300);
		glEnd();
	}

	glBegin(GL_QUADS);												//Rand Color
	{
		glColor3d(R / 255, G / 255, B / 255);
		glVertex2d(width - 160, height - 300);
		glVertex2d(width - 160, height - 250);
		glVertex2d(width - 110, height - 250);
		glVertex2d(width - 110, height - 300);
		glEnd();
	}

	PlayerName();
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid MainMenu()
{
	point_menu = funcMenu;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[FrameMenu]);
	glBegin(GL_QUADS);			//Frame menu
	{
		glTexCoord2d(0, 0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0, 1); glVertex2d(0.0, height);
		glTexCoord2d(1, 1); glVertex2d(width, height);
		glTexCoord2d(1, 0); glVertex2d(width, 0.0);
		glEnd();
	}
	//////
	glBindTexture(GL_TEXTURE_2D, texture[BTN_NewGame]);
	glBegin(GL_QUADS);			//Button New Game
	{
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 200);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 200);
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 250);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 250);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[BTN_Records]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 270);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 270);
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 320);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 320);
		glEnd();;
	}

	glBindTexture(GL_TEXTURE_2D, texture[BTN_Options]);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 1); glVertex2d(width - 100, height - 340);
		glTexCoord2d(0, 1); glVertex2d(width - 400, height - 340);
		glTexCoord2d(0, 0); glVertex2d(width - 400, height - 390);
		glTexCoord2d(1, 0); glVertex2d(width - 100, height - 390);
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();
}

GLvoid TimerTime(GLint v)
{
	GLint temp = Time - 10;
	Time > 0 ? Time-- : Time = 0;
	if (Time == temp)
	{
		speed -= 10;
		temp -= 10;
	}
	glutTimerFunc(1000, TimerTime, v);
}

GLvoid DrawGameObject()
{
	point_menu = funcDrawGameObject;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	RealiseBarUp();

	glBegin(GL_LINES);
	glVertex2d(0, height - 30);
	glVertex2d(width, height - 30);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[FrameGame]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2d(0.0, 0.0);
	glTexCoord2d(0, 1); glVertex2d(0.0, height - 30);
	glTexCoord2d(1, 1); glVertex2d(width, height - 30);
	glTexCoord2d(1, 0); glVertex2d(width, 0.0);
	glEnd();

	ChoiceEllipse();

	if (Time == 0)
		glutDisplayFunc(GameOver);

	glPopMatrix();
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (point_menu == funcOptions)
	{
		if (loop < 8)
		{
			buffer[counterName].name[loop] = key;
			loop++;
		}
		if (key == 8)
		{
			loop -= 2;
			Options();
		}
	}
}

GLvoid MouseClck(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			GLint yy = height - y;

			switch (point_menu)
			{
			case funcDrawGameObject:
			{
				if ((x <= ellipse[0].x + ellipse[0].k && x >= ellipse[0].x - ellipse[0].k) &&
					(yy <= ellipse[0].y + ellipse[0].k && yy >= ellipse[0].y - ellipse[0].k))
				{
					deleteEllipse = 1;
					DrawGameObject();
					score++;
				}
				if ((x <= ellipse[1].x + ellipse[1].k && x >= ellipse[1].x - ellipse[1].k) &&
					(yy <= ellipse[1].y + ellipse[1].k && yy >= ellipse[1].y - ellipse[1].k))
				{
					deleteEllipse = 2;
					DrawGameObject();
					score++;
				}
				if ((x <= ellipse[2].x + ellipse[2].k && x >= ellipse[2].x - ellipse[2].k) &&
					(yy <= ellipse[2].y + ellipse[2].k && yy >= ellipse[2].y - ellipse[2].k))
				{
					deleteEllipse = 3;
					DrawGameObject();
					score++;
				}
				break;
			}
			case funcMenu:
			{
				if ((x <= width - 100 && x >= width - 400) && (yy <= height - 200 && yy >= height - 250))
				{
					PlaySound("2.wav", NULL, SND_ASYNC);
					Time = 5;
					glutDisplayFunc(DrawGameObject);
				}
				else if ((x <= width - 100 && x >= width - 400) && (yy <= height - 270 && yy >= height - 320))
				{
					glutDisplayFunc(TableRecords);
				}
				else if ((x <= width - 100 && x >= width - 400) && (yy <= height - 340 && yy >= height - 390))
				{
					glutDisplayFunc(Options);
				}
				break;
			}
			case funcGameOver:
			{
				if ((x <= width - 100 && x >= width - 400) && (yy <= height - 320 && yy >= height - 370))
				{
					if (score > 0)
					{
						buffer[counterName].score = score;
						strcpy(buffer[counterName].score_buff, Score_Buff);
					}
					speed = 100; score = 0;
					PlaySound("1.wav", NULL, SND_ASYNC);
					glutDisplayFunc(MainMenu);
				}
				break;
			}
			case funcOptions:
			{
				if (statusName)
				{
					counterName++;
					statusName = false;
				}
				if ((x <= width - 430 && x >= width - 480) && (yy <= height - 250 && yy >= height - 300))
				{
					color->R = 1;	color->G = 0;	color->B = 0;
					color->rand = false;
					color->ChoiceColor_x1 = width - 480;	color->ChoiceColor_x2 = width - 430;
				}
				if ((x <= width - 350 && x >= width - 400) && (yy <= height - 250 && yy >= height - 300))
				{
					color->R = 0;	color->G = 1;	color->B = 0;
					color->rand = false;
					color->ChoiceColor_x1 = width - 400;	color->ChoiceColor_x2 = width - 350;
				}
				if ((x <= width - 270 && x >= width - 320) && (yy <= height - 250 && yy >= height - 300))
				{
					color->R = 0;	color->G = 0;	color->B = 1;
					color->rand = false;
					color->ChoiceColor_x1 = width - 320;	color->ChoiceColor_x2 = width - 270;
				}
				if ((x <= width - 190 && x >= width - 240) && (yy <= height - 250 && yy >= height - 300))
				{
					color->R = 0;	color->G = 0;	color->B = 0;
					color->rand = false;
					color->ChoiceColor_x1 = width - 240;	color->ChoiceColor_x2 = width - 190;
				}
				if ((x <= width - 110 && x >= width - 160) && (yy <= height - 250 && yy >= height - 300))
				{
					color->rand = true;
					color->ChoiceColor_x1 = width - 160;	color->ChoiceColor_x2 = width - 110;
				}
				if ((x <= width - 100 && x >= width - 400) && (yy <= height - 400 && yy >= height - 450))
				{
					glutDisplayFunc(MainMenu);
				}
				if ((x <= width - 3 && x >= width - 42) && (yy <= height - 120 && yy >= height - 160))
				{
					loop = 0;
					if (counterName < 10)
						counterName++;

					buffer[counterName].status = false;
				}
				if ((x <= width - 100 && x >= width - 300) && (yy <= height - 80 && yy >= height - 150))
				{
					glutKeyboardFunc(Keyboard);
				}
				break;
			}
			case funcRecords:
			{
				if ((x <= width - 100 && x >= width - 400) && (yy <= height - 400 && yy >= height - 450))
				{
					glutDisplayFunc(MainMenu);
				}
				break;
			}
			}
		}
	}
}

GLvoid Initialize(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	LoadTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -5, 5);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 200);
	glutCreateWindow("Bubble click");
	PlaySound("1.wav", NULL, SND_ASYNC);
	if (statusLoadFile == true)
	{
		LoadRecords();
		statusLoadFile = false;
		if (counterName == 0)
			statusName = false;
		else
			statusName = true;
	}
	glutReshapeFunc(Initialize);
	glutDisplayFunc(MainMenu);
	glutTimerFunc(speed, TimerScaleUp, 0);
	glutTimerFunc(1000, TimerTime, 1);
	glutMouseFunc(MouseClck);

	glutMainLoop();
}