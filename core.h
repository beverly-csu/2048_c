#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#define SIZE 4
#define WIDTH 9
#define HEIGHT 5

void init();
void drawRect(int x, int y, int width, int height, char* title);
void close();
void detectKeys(int* field);
void randomGenerate(int* field);
bool down(int* field);
bool up(int* field);
bool right(int* field);
bool left(int* field);
void initField(int* field);
void start(int* field);
void update(int* field);
int numLen(int number);