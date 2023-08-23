#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#pragma warning(disable:4996)

//colors
#define RED 12
#define BLUE 3
#define GREEN 10
#define YELLOW 14
#define GRAY 8
#define PINK 13
#define WHITE 15
#define WAIT_TIME_MILI_SEC 100
//directions
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
// general
#define BOARD_SIZE 40
#define INITIAL_SNAKE_LENGTH 3
#define MINIMUM_SNAKE_LENGTH 2
#define MAX_LEN_SNAKES 30
#define NUMBER_OF_MOUSES 20
//board_characters
#define EMPTY '0'
#define MOUSE 'm'
#define PLAYER1_SNAKE_HEAD '1'
#define PLAYER2_SNAKE_HEAD '2'
#define PLAYER1_SNAKE_BODY 'a'
#define PLAYER2_SNAKE_BODY 'b'
//Bernard, Poison and golden star
#define BERNARD_CLOCK 'c' //on the board character
#define GOLDEN_STAR '*' //on the board character
#define POISON 'x' //on the board character
#define NUMBER_OF_POISONS 5
#define NUMBER_OF_GOLDEN_STARS 3
#define BERNARD_CLOCK_APPEARANCE_CHANCE_PERCENT 20
#define BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC 2000
#define BERNARD_CLOCK_FROZEN_TIME_MILI_SEC 4000

/*define constant to define who wins*/
#define NOT_SET 0
#define PLAYER1_WINS 1
#define PLAYER2_WINS 2
#define EQUAL 3


CONSOLE_FONT_INFOEX former_cfi;
CONSOLE_CURSOR_INFO former_info;
COORD former_screen_size;

void reset_console() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(consoleHandle, CONSOLE_WINDOWED_MODE, &former_screen_size);
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
	SetConsoleCursorInfo(consoleHandle, &former_info);
}

void hidecursor(HANDLE consoleHandle)
{
	GetConsoleCursorInfo(consoleHandle, &former_info);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void set_console_font_and_font_size(HANDLE consoleHandle) {
	former_cfi.cbSize = sizeof(former_cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 20;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Courier");
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
}

void set_full_screen_mode(HANDLE consoleHandle) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	former_screen_size.X = csbi.dwSize.X; former_screen_size.Y = csbi.dwSize.Y;
	COORD coord;
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, &coord);
}

void init_screen()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_full_screen_mode(consoleHandle);
	hidecursor(consoleHandle);
	set_console_font_and_font_size(consoleHandle);

}

void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction) {
	DWORD64 start_time, check_time;
	start_time = GetTickCount64();
	check_time = start_time + WAIT_TIME_MILI_SEC; //GetTickCount returns time in miliseconds
	char key = 0;
	char player1_key_hit = 0;
	char player2_key_hit = 0;

	while (check_time > GetTickCount64()) {
		if (_kbhit()) {
			key = _getch();
			if (key == 0)
				key = _getch();
			if (key == 'w' || key == 'a' || key == 's' || key == 'd')
				player1_key_hit = key;
			if (key == 'i' || key == 'j' || key == 'k' || key == 'l')
				player2_key_hit = key;
		}
	}

	switch (player1_key_hit) {
	case 'w': if (*player1_snake_direction != DOWN) *player1_snake_direction = UP; break;
	case 'a': if (*player1_snake_direction != RIGHT) *player1_snake_direction = LEFT; break;
	case 's': if (*player1_snake_direction != UP) *player1_snake_direction = DOWN; break;
	case 'd': if (*player1_snake_direction != LEFT) *player1_snake_direction = RIGHT; break;
	default: break;
	}

	switch (player2_key_hit) {
	case 'i': if (*player2_snake_direction != DOWN) *player2_snake_direction = UP; break;
	case 'j': if (*player2_snake_direction != RIGHT) *player2_snake_direction = LEFT; break;
	case 'k': if (*player2_snake_direction != UP) *player2_snake_direction = DOWN; break;
	case 'l': if (*player2_snake_direction != LEFT) *player2_snake_direction = RIGHT; break;
	default: break;
	}
}

void draw_point(char point_content) {
	switch (point_content) {
	case PLAYER1_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED); printf("@"); break;
	case PLAYER2_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("@"); break;
	case PLAYER1_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);  printf("o"); break;
	case PLAYER2_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("o"); break;
	case MOUSE: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY); printf("m"); break;
	case GOLDEN_STAR: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW); printf("*"); break;
	case POISON: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN); printf("x"); break;
	case BERNARD_CLOCK: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PINK); printf("c"); break;
	default: printf(" ");
	}
}

void draw_horizonatal_walls() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < BOARD_SIZE + 2; ++i)
		printf("-");
	printf("\n");
}

void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
	system("cls");
	draw_horizonatal_walls();
	for (int i = 0; i < BOARD_SIZE; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("|"); // vertical wall 
		for (int j = 0; j < BOARD_SIZE; j++)
			draw_point(board_content[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("|\n"); // vertical wall
	}
	draw_horizonatal_walls();
}

// prototypes
void init_screen();
void reset_console();
void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction);
void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]);


/*define function to draw mouse in the board*/
void draw_mouse(char board_content[BOARD_SIZE][BOARD_SIZE], int mouse_x[NUMBER_OF_MOUSES], int mouse_y[NUMBER_OF_MOUSES]) {
	int i;
	for (i = 0; i < NUMBER_OF_MOUSES; i++) {
		board_content[mouse_x[i]][mouse_y[i]] = MOUSE;
	}
}

/*define function to clear snake from the board*/
void clear_snake(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_x[MAX_LEN_SNAKES], int snake_y[MAX_LEN_SNAKES], int length_snake) {
	int i;
	for (i = 0; i < length_snake; i++) {
			board_content[snake_x[i]][snake_y[i]] = EMPTY;
	}
}

/*define function to define winner*/
int define_winner(int length_snake1, int length_snake2, int snake1_x[MAX_LEN_SNAKES], int snake1_y[MAX_LEN_SNAKES], int snake2_x[MAX_LEN_SNAKES], int snake2_y[MAX_LEN_SNAKES]) {
	int result = NOT_SET;
	int i;
	/*check if snake1 or snake2 head location is on the snake2 body location*/
	for (i = 1; i < length_snake2; i++) {
		if (snake1_x[0] == snake2_x[i] && snake1_y[0] == snake2_y[i]) {
			result = PLAYER2_WINS;
			break;
		}

		if (snake2_x[0] == snake2_x[i] && snake2_y[0] == snake2_y[i]) {
			result = PLAYER1_WINS;
			break;
		}
	}
	/*check if snake2 or snake1 head location is on the snake1 body location*/
	for (i = 1; i < length_snake1; i++) {
		if (snake2_x[0] == snake1_x[i] && snake2_y[0] == snake1_y[i]) {
			result = PLAYER1_WINS;
			break;
		}

		if (snake1_x[0] == snake1_x[i] && snake1_y[0] == snake1_y[i]) {
			result = PLAYER2_WINS;
			break;
		}
	}

	/*check if snake1 head location is on the snake2 head location*/
	if (snake1_x[0] == snake2_x[0] && snake1_y[0] == snake2_y[0]) {
		if (length_snake1 > length_snake2) {
			result = PLAYER1_WINS;
		}
		else if (length_snake1 < length_snake2) {
			result = PLAYER2_WINS;
		}
		else {
			result = EQUAL;
		}
	}

	/*check if length of snakes is less than 2*/
	if (length_snake1 < 2) {
		result = PLAYER2_WINS;
	}
	if (length_snake2 < 2) {
		result = PLAYER1_WINS;
	}
	return result;
}

/*define function to define diraction*/
void define_diraction(int snake_direction, int snake_x[MAX_LEN_SNAKES], int snake_y[MAX_LEN_SNAKES]) {
	if (snake_direction == UP) {
		snake_x[0] = snake_x[0] - 1;
	}
	else if (snake_direction == RIGHT) {
		snake_y[0] = snake_y[0] + 1;
	}
	else if (snake_direction == DOWN) {
		snake_x[0] = snake_x[0] + 1;
	}
	else if (snake_direction == LEFT) {
		snake_y[0] = snake_y[0] - 1;
	}
}

/*define function to keep snake in board*/
void check_snake_location(int snake_x[MAX_LEN_SNAKES], int snake_y[MAX_LEN_SNAKES]) {
	if (snake_x[0] < 0) {
		snake_x[0] = BOARD_SIZE - 1;
	}
	else if (snake_x[0] > BOARD_SIZE - 1) {
		snake_x[0] = 0;
	}
	else if (snake_y[0] < 0) {
		snake_y[0] = BOARD_SIZE - 1;
	}
	else if (snake_y[0] > BOARD_SIZE - 1) {
		snake_y[0] = 0;
	}
}

/*define function to check mouse location*/
void check_mouse_location(int length, int *mouse_x, int *mouse_y, int object_x[MAX_LEN_SNAKES], int object_y[MAX_LEN_SNAKES]) {
	int i;
	for (i = 0; i < length; i++) {
		while (*mouse_x == object_x[i] && *mouse_y == object_y[i]) {
			*mouse_x = rand() % BOARD_SIZE;
			*mouse_y = rand() % BOARD_SIZE;
		}
	}
}

/*define function to draw golden star*/
void draw_golden_star(char board_content[BOARD_SIZE][BOARD_SIZE], int golden_star_x[NUMBER_OF_GOLDEN_STARS], int golden_star_y[NUMBER_OF_GOLDEN_STARS]) {
	int i;
	for (i = 0; i < NUMBER_OF_GOLDEN_STARS; i++) {
		board_content[golden_star_x[i]][golden_star_y[i]] = GOLDEN_STAR;
	}
}

/*define function to check golden star location*/
void check_golden_star_location(int length, int *golden_star_x, int *golden_star_y, int object_x[MAX_LEN_SNAKES], int object_y[MAX_LEN_SNAKES]) {
	int i;
	for (i = 0; i < length; i++) {
		while (*golden_star_x == object_x[i] && *golden_star_y == object_y[i]) {
			*golden_star_x = rand() % BOARD_SIZE;
			*golden_star_y = rand() % BOARD_SIZE;
		}
	}
}


int main() {
	srand(time(NULL));
	//First define the variables you need during the game

	/*define variables*/
	int snake1_x[MAX_LEN_SNAKES] = { EMPTY };
	int snake2_x[MAX_LEN_SNAKES] = { EMPTY };
	int snake1_y[MAX_LEN_SNAKES] = { EMPTY };
	int snake2_y[MAX_LEN_SNAKES] = { EMPTY };
	int mouse_x[NUMBER_OF_MOUSES];
	int mouse_y[NUMBER_OF_MOUSES];
	int golden_star_x[NUMBER_OF_GOLDEN_STARS];
	int golden_star_y[NUMBER_OF_GOLDEN_STARS];
	int mouse_number = NUMBER_OF_MOUSES;
	int golden_star_number = NUMBER_OF_GOLDEN_STARS;
	int result = NOT_SET;
	int length_snake1 = INITIAL_SNAKE_LENGTH;
	int length_snake2 = INITIAL_SNAKE_LENGTH;
	int i;
	int j;
	int k;
	int swap1_x;
	int swap1_y;
	int swap2_x;
	int swap2_y;
	char board_content[BOARD_SIZE][BOARD_SIZE];
	int player1_snake_direction, player2_snake_direction;

	/*define initial snakes*/
	for (i = 0; i < length_snake1; i++) {
		snake1_x[i] = BOARD_SIZE - (length_snake1 - i);
		snake1_y[i] = 0;
	}

	for (i = 0; i < length_snake2; i++) {
		snake2_x[i] = length_snake2 - (i + 1);
		snake2_y[i] = BOARD_SIZE - 1;
	}

	/*define initial snakes direction*/
	player1_snake_direction = UP;
	player2_snake_direction = DOWN;

	//Do not forget to Initialize your variables, specially board_content
	init_screen(); //call this to make window adjustments

	/*define mouse and check mouse location*/
	for (i = 0; i < NUMBER_OF_MOUSES; i++) {
		mouse_x[i] = rand() % BOARD_SIZE;
		mouse_y[i] = rand() % BOARD_SIZE;
		for (j = 0; j < length_snake1; j++) {
			while (snake1_x[j] == mouse_x[i] && snake1_y[j] == mouse_y[i]) {
				mouse_x[i] = rand() % BOARD_SIZE;
				mouse_y[i] = rand() % BOARD_SIZE;
			}	
		}

		for (j = 0; j < length_snake2; j++) {
			while (snake2_x[j] == mouse_x[i] && snake2_y[j] == mouse_y[i]) {
				mouse_x[i] = rand() % BOARD_SIZE;
				mouse_y[i] = rand() % BOARD_SIZE;
			}	
		}

		for (k = 0; k < i; k++) {
			while (mouse_x[i] == mouse_x[k] && mouse_y[i] == mouse_y[k]) {
				mouse_x[i] = rand() % BOARD_SIZE;
				mouse_y[i] = rand() % BOARD_SIZE;
			}
		}
	}

	/*define golden star and check golden star location*/
	for (i = 0; i < NUMBER_OF_GOLDEN_STARS; i++) {
		golden_star_x[i] = rand() % BOARD_SIZE;
		golden_star_y[i] = rand() % BOARD_SIZE;
		for (j = 0; j < length_snake1; j++) {
			while (snake1_x[j] == golden_star_x[i] && snake1_y[j] == golden_star_y[i]) {
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_y[i] = rand() % BOARD_SIZE;
			}
		}

		for (j = 0; j < length_snake2; j++) {
			while (snake2_x[j] == golden_star_x[i] && snake2_y[j] == golden_star_y[i]) {
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_y[i] = rand() % BOARD_SIZE;
			}
		}

		for (j = 0; j < NUMBER_OF_MOUSES; j++) {
			while (mouse_x[j] == golden_star_x[i] && mouse_y[j] == golden_star_y[i]) {
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_y[i] = rand() % BOARD_SIZE;
			}
		}

		for (k = 0; k < i; k++) {
			while (golden_star_x[k] == golden_star_x[i] && golden_star_y[k] == golden_star_y[i]) {
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_y[i] = rand() % BOARD_SIZE;
			}
		}
	}
	

	/*draw mouse*/
	draw_mouse(board_content, mouse_x, mouse_y);

	/*draw golden star*/
	draw_golden_star(board_content, golden_star_x, golden_star_y);

	/*draw snake1*/
	for (i = 0; i < length_snake1; i++) {
		if (i == 0) {
			board_content[snake1_x[i]][snake1_y[i]] = PLAYER1_SNAKE_HEAD;
		}
		else {
			board_content[snake1_x[i]][snake1_y[i]] = PLAYER1_SNAKE_BODY;
		}
	}

	/*draw snake2*/
	for (i = 0; i < length_snake2; i++) {
		if (i == 0) {
			board_content[snake2_x[i]][snake2_y[i]] = PLAYER2_SNAKE_HEAD;
		}
		else {
			board_content[snake2_x[i]][snake2_y[i]] = PLAYER2_SNAKE_BODY;
		}
	}


	while (TRUE) {
		draw_board(board_content);
		wait_and_get_direction(&player1_snake_direction, &player2_snake_direction);
		//do some check after key press, and let snakes move forward one house

		/*clear snake*/
		clear_snake(board_content, snake1_x, snake1_y, length_snake1);
		clear_snake(board_content, snake2_x, snake2_y, length_snake2);


		/*back up snake1 head location*/
		swap1_x = snake1_x[0];
		swap1_y = snake1_y[0];

		/*define snake1 diraction*/
		define_diraction(player1_snake_direction, snake1_x, snake1_y);
		

		/*keep snake 1 in board*/
		check_snake_location(snake1_x, snake1_y);

		/*check if snake1 eats mouse*/
		for (i = 0; i < NUMBER_OF_MOUSES; i++) {
			if (snake1_x[0] == mouse_x[i] && snake1_y[0] == mouse_y[i]) {
				if (length_snake1 < MAX_LEN_SNAKES) {
					length_snake1 = length_snake1 + 1;
				}
				mouse_x[i] = rand() % BOARD_SIZE;
				mouse_y[i] = rand() % BOARD_SIZE;
				check_mouse_location(length_snake1, &mouse_x[i], &mouse_y[i], snake1_x, snake2_y);
				check_mouse_location(length_snake2, &mouse_x[i], &mouse_y[i], snake2_x, snake2_y);
				check_mouse_location(golden_star_number, &mouse_x[i], &mouse_y[i], golden_star_x, golden_star_y);
				board_content[mouse_x[i]][mouse_y[i]] = MOUSE;
			}
		}

		/*check if snake 1 eats golden star*/
		for (i = 0; i < NUMBER_OF_GOLDEN_STARS; i++) {
			if (snake1_x[0] == golden_star_x[i] && snake1_y[0] == golden_star_y[i]) {
				length_snake2 = length_snake2 - 1;
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_x[i] = rand() % BOARD_SIZE;
				check_golden_star_location(length_snake1, &golden_star_x[i], &golden_star_y[i], snake1_x, snake1_y);
				check_golden_star_location(length_snake2, &golden_star_x[i], &golden_star_y[i], snake2_x, snake2_y);
				check_golden_star_location(mouse_number, &golden_star_x[i], &golden_star_y[i], mouse_x, mouse_y);
				board_content[golden_star_x[i]][golden_star_y[i]] = GOLDEN_STAR;
			}
		}
		

		/*change snake1 location*/
		for (i = 1; i < length_snake1; i++) {
			swap2_x = snake1_x[i];
			swap2_y = snake1_y[i];
			snake1_x[i] = swap1_x;
			snake1_y[i] = swap1_y;
			swap1_x = swap2_x;
			swap1_y = swap2_y;
		}
		
		/*back up snake2 head location*/
		swap1_x = snake2_x[0];
		swap1_y = snake2_y[0];

		/*define snake2 diraction*/
		define_diraction(player2_snake_direction, snake2_x, snake2_y);

		/*keep snake2 in board*/
		check_snake_location(snake2_x, snake2_y);

		/*check if snake2 eats mouse*/
		for (i = 0; i < NUMBER_OF_MOUSES; i++) {
			if (snake2_x[0] == mouse_x[i] && snake2_y[0] == mouse_y[i]) {
				if (length_snake2 < MAX_LEN_SNAKES) {
					length_snake2 = length_snake2 + 1;
				}
				mouse_x[i] = rand() % BOARD_SIZE;
				mouse_y[i] = rand() % BOARD_SIZE;
				check_mouse_location(length_snake1, &mouse_x[i], &mouse_y[i], snake1_x, snake2_y);
				check_mouse_location(length_snake2, &mouse_x[i], &mouse_y[i], snake2_x, snake2_y);
				check_mouse_location(golden_star_number, &mouse_x[i], &mouse_y[i], golden_star_x, golden_star_y);
				board_content[mouse_x[i]][mouse_y[i]] = MOUSE;
			}
		}

		/*check if snake2 eats golden star*/
		for (i = 0; i < NUMBER_OF_GOLDEN_STARS; i++) {
			if (snake2_x[0] == golden_star_x[i] && snake2_y[0] == golden_star_y[i]) {
				length_snake1 = length_snake1 - 1;
				golden_star_x[i] = rand() % BOARD_SIZE;
				golden_star_x[i] = rand() % BOARD_SIZE;
				check_golden_star_location(length_snake1, &golden_star_x[i], &golden_star_y[i], snake1_x, snake1_y);
				check_golden_star_location(length_snake2, &golden_star_x[i], &golden_star_y[i], snake2_x, snake2_y);
				check_golden_star_location(mouse_number, &golden_star_x[i], &golden_star_y[i], mouse_x, mouse_y);
				board_content[golden_star_x[i]][golden_star_y[i]] = GOLDEN_STAR;
			}
		}
		

		/*change snake2 location*/
		for (i = 1; i < length_snake2; i++) {
			swap2_x = snake2_x[i];
			swap2_y = snake2_y[i];
			snake2_x[i] = swap1_x;
			snake2_y[i] = swap1_y;
			swap1_x = swap2_x;
			swap1_y = swap2_y;
		}

		/*define the winner*/
		result = define_winner(length_snake1, length_snake2, snake1_x, snake1_y, snake2_x, snake2_y);

		/*check if game is finished*/
		if (result != 0) {
			break;
		}

		/*draw snake1*/
		for (i = 0; i < length_snake1; i++) {
			if (i == 0) {
				board_content[snake1_x[i]][snake1_y[i]] = PLAYER1_SNAKE_HEAD;
			}
			else {
				board_content[snake1_x[i]][snake1_y[i]] = PLAYER1_SNAKE_BODY;
			}
		}

		/*draw snake2*/
		for (i = 0; i < length_snake2; i++) {
			if (i == 0) {
				board_content[snake2_x[i]][snake2_y[i]] = PLAYER2_SNAKE_HEAD;
			}
			else {
				board_content[snake2_x[i]][snake2_y[i]] = PLAYER2_SNAKE_BODY;
			}
		}

		
	}
	//The Game is Finished, Show the result

	/*define who wins*/
	if (result == PLAYER1_WINS) {
		system("cls");
		reset_console();
		printf("Player 1 wins\n");
	}
	else if (result == PLAYER2_WINS) {
		system("cls");
		reset_console();
		printf("Player 2 wins\n");
	}
	else {
		system("cls");
		reset_console();
		printf("Equal\n");
	}
	return 0;
}