#include "core.h"

int numLen(int number) {
	int count = 0;
	while (number) {
		number /= 10;
		count++;
	}
	return count;
}

void update(int* field) {
	char* string = { 0 };
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int num = field[i * SIZE + j];
			int len = numLen(num);
			string = (char*)malloc(sizeof(char) * (WIDTH - 1));
			if (string) {
				if (len > 0) {
					_itoa_s(num, string, len + 1, 10);
				}
				else {
					string = "";
				}
				drawRect((HEIGHT + 1) * i + 1, (WIDTH + 1) * j + 1, HEIGHT, WIDTH, string);
			}
		}
	}
}
void start(int* field) {
	for (int i = 0; i < 2; i++)
	{
		int pos = rand() % (SIZE * SIZE);
		field[pos] = 2;
	}
}

void initField(int* field) {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (field)
				field[i * SIZE + j] = 0;
}

bool left(int* field) {
	bool space_before = false;
	bool step = false;
	int temp = 0;
	for (int i = 0; i < SIZE; i++)
	{

		for (int count = 0; count < SIZE; count++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (field[i * SIZE + j] == 0) {
					space_before = true;
					continue;
				}
				else {
					if (space_before && j != 0 && field[i * SIZE + j - 1] == 0) {
						int temp = field[i * SIZE + j];
						field[i * SIZE + j] = 0;
						field[i * SIZE + j - 1] = temp;
						space_before = false;
						step = true;
					}
				}
				if (j < SIZE - 1) {
					if (field[i * SIZE + j] == field[i * SIZE + j + 1]) {
						field[i * SIZE + j] *= 2;
						field[i * SIZE + j + 1] = 0;
						step = true;
					}
				}
			}
		}
		space_before = false;
	}
	return step;
}

bool right(int* field) {
	bool space_before = false;
	int temp = 0;
	bool step = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int count = 0; count < SIZE; count++)
		{
			for (int j = SIZE - 1; j >= 0; j--)
			{
				if (field[i * SIZE + j] == 0) {
					space_before = true;
					continue;
				}
				else {
					if (space_before && j < SIZE - 1 && field[i * SIZE + j + 1] == 0) {
						int temp = field[i * SIZE + j];
						field[i * SIZE + j] = 0;
						field[i * SIZE + j + 1] = temp;
						space_before = false;
						step = true;
					}
				}
				if (j > 0) {
					if (field[i * SIZE + j] == field[i * SIZE + j - 1]) {
						field[i * SIZE + j] *= 2;
						field[i * SIZE + j - 1] = 0;
						step = true;
					}
				}
			}
		}
		space_before = false;
	}
	return step;
}

bool up(int* field) {
	int temp = 0;
	bool step = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int count = 0; count < SIZE; count++)
		{
			for (int j = SIZE - 1; j > 0; j--)
			{
				if (field[j * SIZE + i] != 0 && field[(j - 1) * SIZE + i] == 0) {
					int temp = field[j * SIZE + i];
					field[j * SIZE + i] = 0;
					field[(j - 1) * SIZE + i] = temp;
					step = true;
				}
				if (field[j * SIZE + i] == field[(j - 1) * SIZE + i]) {
					field[(j - 1) * SIZE + i] *= 2;
					field[j * SIZE + i] = 0;
					step = true;
				}
			}
		}
	}
	return step;
}

bool down(int* field) {
	int temp = 0;
	bool step = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int count = 0; count < SIZE; count++)
		{
			for (int j = 0; j < SIZE - 1; j++)
			{
				if (field[j * SIZE + i] != 0 && field[(j + 1) * SIZE + i] == 0) {
					int temp = field[j * SIZE + i];
					field[j * SIZE + i] = 0;
					field[(j + 1) * SIZE + i] = temp;
					step = true;
				}
				if (field[j * SIZE + i] == field[(j + 1) * SIZE + i]) {
					field[(j + 1) * SIZE + i] *= 2;
					field[j * SIZE + i] = 0;
					step = true;
				}
			}
		}
	}
	return step;
}

void randomGenerate(int* field) {
	int randPos = rand() % (SIZE * SIZE);
	int value = rand() % 2;
	while (1) {
		if (field[randPos] == 0) {
			if (!value) {
				field[randPos] = 2;
			}
			else {
				field[randPos] = 4;
			}
			break;
		}
		else
			randPos = rand() % (SIZE * SIZE);
	}
}

void detectKeys(int* field) {
	bool step = false;
	int symbol = 0;
	while ((symbol = _getch()) != 27) {
		switch (symbol)
		{
		case 119: // W
			step = up(field);
			break;
		case 97: // A
			step = left(field);
			break;
		case 115: // S
			step = down(field);
			break;
		case 100: // D
			step = right(field);
			break;
		default:
			break;
		}
		update(field);
		if (step) {
			Sleep(300);
			randomGenerate(field);
			update(field);
			step = false;
		}
	}
}

void drawRect(int x, int y, int width, int height, char* title) {
	if (strlen(title) > (size_t)width)
		return;
	int symbol;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 && j == 0)
				symbol = 201;
			else if (i == width - 1 && j == height - 1)
				symbol = 188;
			else if (i == 0 && j != 0 && j != height - 1)
				symbol = 205;
			else if ((j == 0 || j == height - 1) && i != 0 && i != width - 1)
				symbol = 186;
			else if (i == width - 1 && j == 0)
				symbol = 200;
			else if (i == 0 && j == height - 1)
				symbol = 187;
			else if (i == width - 1 && j != 0 && j != height - 1)
				symbol = 205;
			else
				symbol = ' ';
			printf_s("\x1b[%d;%dH%c", x + i, y + j, symbol);
		}
	}
	int offset = 1;
	if (strlen(title) == 1)
		offset++;
	printf_s("\x1b[%d;%dH\x1b[30;1m%s", x + height / 2 - 2, y + offset + (width / 2), title);
}

void init() {
	printf_s("\x1b[?25l");
}

void close() {
	printf_s("\x1b[?25h");
}