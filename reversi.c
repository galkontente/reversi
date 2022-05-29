//Name: Gal Kontente
//ID: 207002015
//Description: Reversi game

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#define MAX_SIZE 20
#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY '.'

int boardSize();
void clearBoard(char board[][MAX_SIZE], int size);
void printBoard(char board[][MAX_SIZE], int size);
void turn(char player, char board[][MAX_SIZE], int size);
int leagalMove(int row, int col, char board[][MAX_SIZE], int size, char player);
void change(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej, int count);
int checkThisDirection(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej);
int ableToPlay(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej);
int isItPossible(int row, int col, char board[][MAX_SIZE], int size, char player);
void whoWon(int size, char board[][MAX_SIZE]);

void main()
{
	int size, count = 1;
	char move;
	char board[MAX_SIZE][MAX_SIZE];
	printf("Welcome to Reversi!\n");
	size = boardSize();
	clearBoard(board, size);
	printBoard(board, size);

	while (count < size * size)
	{
		if (ableToPlay(0, 0, board, PLAYER1, size, 0, 0) == 1)
		{
			turn(PLAYER1, board, size);
			printBoard(board, size);
			count = count + 1;
		}
		else if ((ableToPlay(0, 0, board, PLAYER2, size, 0, 0)) == 1 && ableToPlay(0, 0, board, PLAYER1, size, 0, 0) != 1)
			printf("You don't have any moves. Your turn goes to your rival.\n");

		if (ableToPlay(0, 0, board, PLAYER2, size, 0, 0) == 1)
		{
			turn(PLAYER2, board, size);
			printBoard(board, size);
			count = count + 1;
		}
		else if ((ableToPlay(0, 0, board, PLAYER2, size, 0, 0)) != 1 && ableToPlay(0, 0, board, PLAYER1, size, 0, 0) == 1)
			printf("You don't have any moves. Your turn goes to your rival.\n");
		else
		{
			printf("**************\n");
			printf("* Game Over! *\n");
			printf("**************\n");
			whoWon(size, board);
			count = count + 100000;
		}
	}
}

int boardSize()// asks the user to choose the board size
{
	int size;

	while (1)
	{
		printf("Please choose the size of the board:\n 0. Exit.\n 1. 10X10\n 2. 15X15\n 3. 20x20\n");
		scanf("%d", &size);

		if (size == 1)
			return 10;

		else if (size == 2)
			return 15;

		else if (size == 3)
			return 20;

		else if (size < 0 || size > 3)
		{
			printf("Invalid choice, please choose again.\n");
			continue;
		}

		else
		{
			printf("Exit.\n");
			return 0;
		}
	}
}

void clearBoard(char board[][MAX_SIZE], int size)// prints the initial board
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			board[i][j] = '.';
	}
	board[size / 2][size / 2] = 'O';
	board[(size / 2) - 1][(size / 2)] = 'X';
	board[(size / 2) - 1][(size / 2) - 1] = 'O';
	board[size / 2][(size / 2) - 1] = 'X';
}

void printBoard(char board[][MAX_SIZE], int size)// prints the current board
{
	int i, j;
	printf("  ");
	for (i = 1; i <= size; i++)
		printf("%3d", i);

	printf("\n");

	for (i = 0; i < size; i++)
	{
		printf("%2d ", i + 1);
		for (j = 0; j < size; j++)
			printf("%2C ", board[i][j]);
		printf("\n");
	}
}

void turn(char player, char board[][MAX_SIZE], int size)// says who's turn it is and checks if its a leagal move 
{
	int row, col, leagal;
	while (1)
	{
		printf("It's %c's turn.\n", player);
		printf("Please enter the row and the column you want to put your tool in:");
		scanf("%d %d", &row, &col);
		row = row - 1;
		col = col - 1;
		leagal = leagalMove(row, col, board, size, player);

		if (leagal != 0)
		{
			board[row][col] = player;
			return;
		}
		else
		{
			printf("Invalid move, please try again.\n");
			continue;
		}
	}
}

int leagalMove(int row, int col, char board[][MAX_SIZE], int size, char player)// checks if the move is leagal (one direction available is enough to make it leagal)
{
	int condition = 0, count = 0;
	char notMyPlayer = (player == PLAYER1) ? PLAYER2 : PLAYER1;
	if (row > size || row < 0 || col > size || col < 0) //checks if its inside the board game.
		return 0;
	if (board[row][col] == EMPTY)
	{
		if (board[row][col - 1] == notMyPlayer)// left
		{
			count = checkThisDirection(row, col, board, player, size, 0, -1);
			if (count > 0)
			{
				change(row, col, board, player, size, 0, -1, count);
				condition = 1;
			}
		}

		if (board[row][col + 1] == notMyPlayer)// right
		{
			count = checkThisDirection(row, col, board, player, size, 0, 1);
			if (count > 0)
			{
				change(row, col, board, player, size, 0, 1, count);
				condition = 1;
			}
		}

		if (board[row - 1][col] == notMyPlayer)// up
		{
			count = checkThisDirection(row, col, board, player, size, -1, 0, count);
			if (count > 0)
			{
				change(row, col, board, player, size, -1, 0, count);
				condition = 1;
			}
		}

		if (board[row + 1][col] == notMyPlayer)// down
		{
			count = checkThisDirection(row, col, board, player, size, 1, 0);
			if (count > 0)
			{
				change(row, col, board, player, size, 1, 0, count);
				condition = 1;
			}
		}

		if (board[row - 1][col - 1] == notMyPlayer)	// up and left
		{
			count = checkThisDirection(row, col, board, player, size, -1, -1);
			if (count > 0)
			{
				change(row, col, board, player, size, -1, -1, count);
				condition = 1;
			}
		}

		if (board[row - 1][col + 1] == notMyPlayer)	// up and right
		{
			count = checkThisDirection(row, col, board, player, size, -1, 1);
			if (count > 0)
			{
				change(row, col, board, player, size, -1, 1, count);
				condition = 1;
			}
		}

		if (board[row + 1][col - 1] == notMyPlayer)// down and left
		{
			count = checkThisDirection(row, col, board, player, size, 1, -1);
			if (count > 0)
			{
				change(row, col, board, player, size, 1, -1, count);
				condition = 1;
			}
		}

		if (board[row + 1][col + 1] == notMyPlayer)//down and right 
		{
			count = checkThisDirection(row, col, board, player, size, 1, 1);
			if (count > 0)
			{
				change(row, col, board, player, size, 1, 1, count);
				condition = 1;
			}
		}
	}
	return condition;
}

void change(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej, int count)// changes the rival's tools to the current player's   
{
	int i = row + changei, j = col + changej, t;
	for (t = 0; t < count; t++)
	{
		board[i][j] = player;
		i += changei;
		j += changej;
	}
}

int checkThisDirection(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej)// each time the i and j changes according to the dorection we want to check. We check if there is a move to that direction.
{
	char notMyPlayer = (player == 'X') ? 'O' : 'X';
	int count = 0;
	while ((board[row + changei][col + changej] == notMyPlayer))
	{
		count++;
		row += changei;
		col += changej;
		if (board[row + changei][col + changej] == EMPTY)
		{
			count = 0;
			break;
		}
		if ((row + changei) >= size || (row + changei) < 0 || (col + changej) >= size || (col + changej) < 0)
			return 0;
	}
	return count;
}

int isItPossible(int row, int col, char board[][MAX_SIZE], int size, char player)// to use inside ableToPlay, checks if there are moves before the turn changes.
{
	int condition = 0, count = 0;
	char notMyPlayer = (player == PLAYER1) ? PLAYER2 : PLAYER1;
	if (row > size || row < 0 || col > size || col < 0)
		return 0;
	if (board[row][col] == EMPTY)
	{
		if (board[row][col - 1] == notMyPlayer)// left
		{
			count = checkThisDirection(row, col, board, player, size, 0, -1);
			if (count > 0)
				condition = 1;
		}

		if (board[row][col + 1] == notMyPlayer)// right
		{
			count = checkThisDirection(row, col, board, player, size, 0, 1);
			if (count > 0)
				condition = 1;
		}

		if (board[row - 1][col] == notMyPlayer)// up
		{
			count = checkThisDirection(row, col, board, player, size, -1, 0, count);
			if (count > 0)
				condition = 1;
		}

		if (board[row + 1][col] == notMyPlayer)// down
		{
			count = checkThisDirection(row, col, board, player, size, 1, 0);
			if (count > 0)
				condition = 1;
		}

		if (board[row - 1][col - 1] == notMyPlayer)	// up and left
		{
			count = checkThisDirection(row, col, board, player, size, -1, -1);
			if (count > 0)
				condition = 1;
		}

		if (board[row - 1][col + 1] == notMyPlayer)	// up and right
		{
			count = checkThisDirection(row, col, board, player, size, -1, 1);
			if (count > 0)
				condition = 1;
		}

		if (board[row + 1][col - 1] == notMyPlayer)// down and left
		{
			count = checkThisDirection(row, col, board, player, size, 1, -1);
			if (count > 0)
				condition = 1;
		}

		if (board[row + 1][col + 1] == notMyPlayer)//down and right 
		{
			count = checkThisDirection(row, col, board, player, size, 1, 1);
			if (count > 0)
				condition = 1;
		}
	}
	return condition;
}

int ableToPlay(int row, int col, char board[][MAX_SIZE], char player, int size, int changei, int changej)// before the turn changes to the other player, it checks if the other player has any moves.
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == EMPTY)
			{
				if (isItPossible(i, j, board, size, player) != 0)
					return 1;
			}
		}
	}
	return 0;
}

void whoWon(int size, char board[][MAX_SIZE])// count how many tools each player has at the end of the game and tells us who won and how many points each player has.
{
	int i, j, countX = 0, countO = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == PLAYER1)
				countX++;
			if (board[i][j] == PLAYER2)
				countO++;
		}
	}
	if (countX > countO)
	{
		printf("X Won!\n");
		printf("X has %d points, and O has %d points\n", countX, countO);
	}

	else if (countO > countX)
	{
		printf("O Won!\n");
		printf("O has %d points, and X has %d points\n", countO, countX);
	}

	else
		printf("Its a tie!\nBoth Players have %d points\n", countX);
}
