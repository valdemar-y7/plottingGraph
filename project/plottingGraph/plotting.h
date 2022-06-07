#pragma once
#include "evaluating.h"
#include <Windows.h>
#include <conio.h>
#include <thread>

static COLORREF redColor = RGB(255, 51, 0);			//
static COLORREF blueColor = RGB(0, 255, 255);		// объявление цвета
static COLORREF greenColor = RGB(51, 255, 51);		//
static COLORREF yellowColor = RGB(255, 255, 0);		//
static COLORREF whiteColor = RGB(255, 255, 255);	//
static COLORREF greyColor = RGB(128, 128, 128);		//
static COLORREF recColor = whiteColor;				//
static COLORREF gridColor = greyColor;				//

static const int recXstart = 50;					//
static const int recYstart = 40;					//Координаты прямоугольной рамки
static const int recXend = 450;						//
static const int recYend = 440;						//
static const int length = recXend - recXstart;		//Длина прямоугольника
static const int width = recYend - recYstart;		//Ширина прямоугольника

static bool stop = false;										
static bool duplicateColor[length + 1][width + 1] = { 0 };		//Массив переменных, используемых для проверки того, был пиксель окрашен до этого или нет
static HWND consoleWindow = GetConsoleWindow();					

void resetColor(bool a[length + 1][width + 1]);	//Сброс и дублирование цвета

void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step);	//Функция рисования горизонтальной линии
void drawVertical(double firstX, double lastX, double firstY, double lastY, double step);	//Функция рисования вертикальной линию

void labelling(string fs[], int n, string type[]);											
void numberline(double firstX, double lastX, double firstY, double lastY, double step);		//число осей

void exitThread(thread* thread);		
void addGraph(string& f1, string& f2, string& type, int& n);	//Функция добавления графика
void deleteGraph(string fs[], string type[], int& n);			//Функция удаления графика
void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor);	//График
void plotGraph(string fs[], string type[], int n);	//Функция обрабатывает проблемы с перемещением и масштабированием графика, вызывает поток для рисования каждого графика

void myGraph(); //запуск