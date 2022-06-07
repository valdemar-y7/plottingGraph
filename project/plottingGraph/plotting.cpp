#include "plotting.h"
#include <locale>

void resetColor(bool a[length + 1][width + 1]) {
	for (int i = 0; i <= length; i++)
		for (int j = 0; j <= width; j++)
			a[i][j] = 0;
}

void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step) {	//Функция для рисовки горизонтальных линий
	double nX = (lastX - firstX) / step;	//Количество сегментов на оси Ox
	double nY = (lastY - firstY) / step;	//Количество сегментов на оси Oy
	double spacePixelX = length / nX;		//Уровень разделения по оси Ox в пикселях
	double spacePixelY = width / nY;		//Уровень разделения по оси Oy в пикселях
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) 
		for (int i = recXstart; i <= recXend; i++) {		//Петля, идущая по краю прямоугольника
			SetPixel(consoleDC, i, recYstart, recColor);	//верхний край
			SetPixel(consoleDC, i, recYend, recColor);		//нижний край
			if ((i - recXstart) % (int)spacePixelX == 0 && (i != recXstart) && (i != recXend)) 	//Проверка координат, чтобы нарисовать сетку	
				for (int j = recYstart + 1; j < recYend; j++) //Рисование сетки вертикально сверху вниз
					if (duplicateColor[i - recXstart][j - recYstart] == 0) 
						SetPixel(consoleDC, i, j, gridColor);
		}
	ReleaseDC(consoleWindow, consoleDC);
}

void drawVertical(double firstX, double lastX, double firstY, double lastY, double step) {	 //Аналогично рисованию горизонтальной линии
	double nX = (lastX - firstX) / step;	
	double nY = (lastY - firstY) / step;	
	double spacePixelX = length / nX;		
	double spacePixelY = width / nY;
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) {
		for (int i = recYstart; i <= recYend; i++) {
			SetPixel(consoleDC, recXstart, i, recColor);		
			SetPixel(consoleDC, recXend, i, recColor);				
			if ((i - recYstart) % (int)spacePixelY == 0 && (i != recYstart) && (i != recYend)) 			
				for (int j = recXstart + 1; j < recXend; j++) 
					if (duplicateColor[j - recXstart][i - recYstart] == 0)
						SetPixel(consoleDC, j, i, gridColor);
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void labelling(string fs[], int n, string type[]) {
	setlocale(LC_ALL, "rus");
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csInfo); //инфо консоль
	WORD oldColor = csInfo.wAttributes; //сохранить цвет
	int a[4] = { 10, 11, 12, 14};	//маркировка
	destCoord.X = recXend / 8 + 4;	//подходящее место
	destCoord.Y = recYstart / 16;	
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "ГРАФИКИ ФУНКЦИЙ" << endl;
	int i = 0;
	int j = 0;
	while (i < n) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a[j]); 
		destCoord.Y += 2;
		SetConsoleCursorPosition(hStdout, destCoord);
		if (type[i] == "") 
			cout << "y = " << fs[i];
		else 
			cout << type[i];
		i += 2;
		j++;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), oldColor);
	//Меню
	setlocale(LC_ALL, "rus");
	destCoord.Y += 5;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Меню:";
	destCoord.Y += 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "WSAD для перемещения обзора";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "+/- для увеличения и уменьшения обзора";	
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "U для добавления графика функции";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "I для удаления графика функции";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "ESC, чтобы завершить программу";
}

void numberline(double firstX, double lastX, double firstY, double lastY, double step) {	//работа с осями
	double nX = (lastX - firstX) / step;
	double nY = (lastY - firstY) / step;	
	double spacePixelX = length / nX;		
	double spacePixelY = width / nY;
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Нумерация по оси У
	double tempY = lastY;							
	for (int i = recYstart; i <= recYend; i++)			
		if ((i - recYstart) % (int)spacePixelY == 0) {	
			if (tempY >= 0)								
				destCoord.X = recXstart / 8 - 4;
			else
				destCoord.X = recXstart / 8 - 5;
			destCoord.Y = i / 16;							
			SetConsoleCursorPosition(hStdout, destCoord);	//Перемещение курсора в нужное положение
			cout << tempY;									//номер
			tempY -= step;									//Должно быть пронумеровано сверху вниз и сначала tempY = lastY должно быть на каждой итерации, затем уменьшать темп на наибольшее разделение
		}

	//Числа по оси X
	destCoord.Y = recYend / 16 + 1;						
	double tempX = firstX;								
	for (int i = recXstart; i <= recXend; i++)			
		if ((i - recXstart) % (int)spacePixelX == 0) {	
			if (tempX >= 0)								
				destCoord.X = i / 8;					
			else
				destCoord.X = i / 8 - 1;
			SetConsoleCursorPosition(hStdout, destCoord); 
			cout << tempX;
			tempX += step;							
		}
}

void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor) {
	double nX = (lastX - firstX) / step;	//Количество сегментов по оси X
	double nY = (lastY - firstY) / step;	//Количество сегментов по оси Y
	double spacePixelX = length / nX;	
	double spacePixelY = width / nY;	

	//Диаграмма
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) {
		//Построение графика функции
		double X0, X1, X2;		
		double Y0, Y1, Y2;	
		double j0, j1, j2;		
		double dx = (lastX - firstX) / length; 

		for (int i = recXstart; i < recXend; i++) {
			X0 = firstX + dx * (i - (double)recXstart - 1);	
			X1 = firstX + dx * (i - (double)recXstart);
			X2 = firstX + dx * (i - (double)recXstart + 1);
			Y0 = eval(f, X0);
			Y1 = eval(f, X1);
			Y2 = eval(f, X2);
			j0 = -Y0 * width / (lastY - firstY);
			j0 = round(j0 + (recYend + firstY * width / (lastY - firstY)));
			j1 = -Y1 * width / (lastY - firstY);
			j1 = round(j1 + (recYend + firstY * width / (lastY - firstY)));
			j2 = -Y2 * width / (lastY - firstY);
			j2 = round(j2 + (recYend + firstY * width / (lastY - firstY)));

			if (j1 < recYend && j1 > recYstart) {	
				SetPixel(consoleDC, i, (int)j1, funcColor);
				duplicateColor[i - recXstart][(int)j1 - recYstart] = 1;
				SetPixel(consoleDC, i, (int)j1+1, funcColor);
				duplicateColor[i - recXstart][(int)j1+1 - recYstart] = 1;
			}
			else
				continue;

			if ((j2 <= recYstart || j2 - j0 >= 1) && Y1 > Y0) {
				for (int t = (int)(j1 + j0) / 2; t > recYstart; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j2 >= recYend || j0 - j2 >= 1) && Y1 < Y0) {
				for (int t = (int)(j1 + j0) / 2; t < recYend; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j0 <= recYstart || j0 - j2 >= 1) && Y1 > Y2) {
				for (int t = (int)(j1 + j2) / 2; t > recYstart; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j0 >= recYend ||j2 - j0 >= 1) && Y1 < Y2) {
				for (int t = (int)(j1 + j2) / 2; t < recYend; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if (j0 > j1 && j0 - j1 <= 100)	//j0 > j1
				for (int t = (int)j1; t <= (j0 + j1) / 2; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}	
				}
			else
				if (j1 > j0 && j1 - j0 <= 100)	//j1 > j0
					for (int t = (int)j1; t >= (j0 + j1) / 2; t--) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
					}
			if (j1 > j2 && j1 - j2 <= 100)	//j1 > j2
				for (int t = (int)j1; t >= (j1 + j2) / 2; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
			else
				if (j2 > j1 && j2 - j1 <= 100)	//j2 > j1
					for (int t = (int)j1; t <= (j1 + j2) / 2; t++) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
					}
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void exitThread(thread* thread) {
	stop = true;
	thread->join();
}

void addGraph(string& f1, string& f2, string& type, int& n) {
	string fs;
	char opt;
graphOrShape:
			rewind(stdin);
			cout << "f(x): ";
			do {
				getline(cin, fs);
			} while (fs == "");
			f1 = fs;
			f2 = "";
			type = "";
			n = n + 2;
			return;
}

void deleteGraph(string fs[], string type[], int& n) {
	setlocale(LC_ALL, "rus");
	if (n <= 0) {
		cout << "Ошибка! Нажмите ESC, чтобы вернуться в меню";
		char t;
		do {
			t = _getch();
		} while (t != 27);
	}
	else {
		cout << "Какой график функции удалить?\n";
		int i = 0;
		int j = 0;
		while (i < n) {
			j++;
			if (type[i] == "")
				cout << j << ". y = " << fs[i] << endl;
			else
				cout << j << ". " << type[i] << endl;
			i += 2;
		}
		char t;
		do {
			t = _getch();
			if (t != 27 && (t < '1' || t > j + 48))
				cout << "";
		} while (t != 27 && (t < '1' || t > j + 48));
		if (t == 27)
			return;
		int k = t - 48;
		for (int i = 2 * k - 2; i < n - 2; i++) {
			fs[i] = fs[i + 2];
			type[i] = type[i + 2];
		}
		n -= 2;
	}
}

void plotGraph(string fs[], string type[], int n) {
	COLORREF colors[4] = { greenColor, blueColor, redColor, yellowColor };
	double range = 4;
	double x1 = -range, x2 = range, y1 = -range, y2 = range, step = 1, moveStep = step;
	thread a[8], t1, t2;
step1:
	system("cls");
	labelling(fs, n, type);
	numberline(x1, x2, y1, y2, step);
	stop = false;
	resetColor(duplicateColor);
	t1 = thread(drawHorizontal, x1, x2, y1, y2, step);
	t2 = thread(drawVertical, x1, x2, y1, y2, step);
	int i = 0;
	int j = 0;
	while (i < n) {
		if (type[i] == "") {
			a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[j]);
		}		
		else {
			a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[j]);
			a[i + 1] = thread(plot, fs[i + 1], x1, x2, y1, y2, step, colors[j]);
		}	
		i += 2;
		j += 1;
	}
	while (true) {
		char c = _getch();
		if (c == 119 || c == 115 || c == 97 || c == 100 || c == 45 || c == 43) {
			switch (c) {
			case 87:
			case 119: { //Move up
				y1 = y1 + moveStep;
				y2 = y2 + moveStep;
				break;
			}
			case 83: 
			case 115: { //Move down
				y1 = y1 - moveStep;
				y2 = y2 - moveStep;
				break;
			}
			case 65:
			case 97: { //Move left
				x1 = x1 - moveStep;
				x2 = x2 - moveStep;
				break;
			}
			case 68:
			case 100: { //Move right
				x1 = x1 + moveStep;
				x2 = x2 + moveStep;
				break;
			}
			case 45: {	//Zoom out
				step = step * 2;
				if ((x1 + x2) / 2 / step != round((x1 + x2) / 2 / step)) {
					x1 = x1 - moveStep;
					x2 = x2 - moveStep;
				}
				if ((y1 + y2) / 2 / step != round((y1 + y2) / 2 / step)) {
					y1 = y1 - moveStep;
					y2 = y2 - moveStep;
				}
				double oldx1 = x1, oldy1 = y1;
				x1 = (x1 + x2) / 2 - range * step;
				x2 = (oldx1 + x2) / 2 + range * step;
				y1 = (y1 + y2) / 2 - range * step;
				y2 = (oldy1 + y2) / 2 + range * step;
				moveStep = step;
				break;
			}
			case 43: {	//Zoom in
				step = step / 2;
				double oldx1 = x1, oldy1 = y1;
				x1 = (x1 + x2) / 2 - range * step;
				x2 = (oldx1 + x2) / 2 + range * step;
				y1 = (y1 + y2) / 2 - range * step;
				y2 = (oldy1 + y2) / 2 + range * step;
				moveStep = step;
				break;
			}
			}
			exitThread(&t1);
			exitThread(&t2);
			for (int i = 0; i < n; i++) 
				if (fs[i] != "")
					exitThread(&a[i]);	
			goto step1;
		}
		if (c == 117 || c == 85 || c == 105 || c == 73 || c == 27) {
			exitThread(&t1);
			exitThread(&t2);
			for (int i = 0; i < n; i++) 
				if (fs[i] != "")
					exitThread(&a[i]);
			system("cls");
			if (c == 85 || c == 117) {
				addGraph(fs[n], fs[n + 1], type[n], n);
				goto step1;
			}
			if (c == 105 || c == 73) {
				deleteGraph(fs, type, n);
				goto step1;
			}
			if (c == 27) 
				return;
		}
	}
}

void myGraph() {
	string fs[8], g[8];
	int n = 0;
	addGraph(fs[0], fs[1], g[0], n);
	if (fs[0] != "")
		plotGraph(fs, g, n);
}