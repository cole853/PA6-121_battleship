/*
		Programmer: Cole Clark
		Date: 11/12/2020

		Description: Battleship game for PA6
*/

#include "battleship.h"


/*************************************************************
* Function:	welcome_screen()				                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: Displays the welcome screen					*
*															*
* Input parameters: void				                    *
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void welcome_screen(void)
{
	printf("\n\t\t\t\t\tWELCOME TO BATTLESHIP!\n");
	printf("\nThe rules of battleship: \n\n");
	printf("1. This is a two player game. You are player one and will be playing against the computer (player 2)\n");
	printf("2. You will have the option to manually place your ships or have them randomly placed.\n");
	printf("3. Each player starts with 5 ships a Carrier (5 spaces), a Battleship (4 spaces), a Cruiser (3 spaces),\n\t a Submarine (3 spaces), and a Destroyer (2 spaces).\n");
	printf("4. Each player will take turns firing at a coordinate on the other player's board until all of one player's ships\n\t are sunk. When a ship is hit it will be marked by a '*' if the shot was a miss it will be marked by a 'm'.\n");
	printf("5. Once all ships on a players board have been sunk the game will end and the player with ships still on their board\n\t is the winner.\n\n");

}


/*************************************************************
* Function:	initialize_game_board()				            *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: sets all spaces in the game board to '~'		*
*															*
* Input parameters: game board, rows, columns				*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void initialize_game_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols)
{
	
	
	for (int row_index = 0; row_index < rows; ++row_index)
	{
		for (int col_index = 0; col_index < cols; ++col_index)
		{
			board[row_index][col_index] = '~';
		}
	}

}


/*************************************************************
* Function:	select_who_starts_first()				        *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: chooses a random number either 1 or 2		*
*															*
* Input parameters: void				                    *
* Returns: int (either 1 or 2)			                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int select_who_starts_first(void)
{
	int start = rand() % 2 + 1;

	printf("\n\nPlayer %d will go first.\n\n", start);

	return start;

}


/*************************************************************
* Function:	Manually_place_ships_on_board()				    *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: allows the player to manually place one ship *
*															*
* Input parameters: game board, ship, direction, row, column*
* Returns: int 1 if good placement 0 if bad			        *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int manually_place_ships_on_board(char board[MAX_ROWS][MAX_COLS], int ship, char direction, int row_num, int col_num)
{

	int length = 0;
	char ship_type = '\0';

	if (ship == 0)
	{
		length = 5;
		ship_type = 'C';
	}
	else if (ship == 1)
	{
		length = 4;
		ship_type = 'B';
	}
	else if (ship == 2)
	{
		length = 3;
		ship_type = 'R';
	}
	else if (ship == 3)
	{
		length = 3;
		ship_type = 'S';
	}
	else if (ship == 4)
	{
		length = 2;
		ship_type = 'D';
	}

	if (direction == 'H' || direction == 'h')
	{
		if (col_num > 10 - length || col_num < 0 || row_num < 0)
		{
			return 1;
		}

		for (int i = 0; i != length; ++i)
		{
			if (board[row_num][col_num + i] != '~')
			{
				return 1;
			}
		}

		for (int j = 0; j != length; ++j)
		{
			board[row_num][col_num + j] = ship_type;
		}

		return 0;
	}
	else if (direction == 'V' || direction == 'v')
	{
		if (row_num > 10 - length || col_num < 0 || row_num < 0)
		{
			return 1;
		}

		for (int i = 0; i != length; ++i)
		{
			if (board[row_num + i][col_num] != '~')
			{
				return 1;
			}
		}

		for (int j = 0; j != length; ++j)
		{
			board[row_num + j][col_num] = ship_type;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}


/*************************************************************
* Function:	randomly_place_ships_on_board()				    *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: places one ship on the board randomly		*
*															*
* Input parameters: game board, length, ship type			*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void randomly_place_ships_on_board(char board[MAX_ROWS][MAX_COLS], int length, char ship_type)
{
	int direction = rand() % 2; //0 is horizontal, 1 is vertical
	int stop = 0;
	int row_num = 0;
	int col_num = 0;

	if (direction == 0) //horizontal
	{
		while (stop == 0)
		{
			row_num = rand() % 10;
			col_num = rand() % (10 - length + 1);
			stop = 1;

			for (int i = 0; i != length; ++i) // checks all spots the ship will be in 
			{
				if (board[row_num][col_num + i] != '~') // if there is not another ship in that spot
				{
					stop = 0;
				}

			}


		}
		for (int j = 0; j != length; ++j)
		{
			board[row_num][col_num + j] = ship_type;
		}

	}
	else if (direction == 1) // vertical
	{
		while (stop == 0)
		{
			col_num = rand() % 10;
			row_num = rand() % (10 - length + 1);
			stop = 1;

			for (int i = 0; i != length; ++i) // checks all spots the ship will be in 
			{
				if (board[row_num + i][col_num] != '~') // if there is not another ship in that spot
				{
					stop = 0;
				}

			}

		}

		for (int j = 0; j != length; ++j)
		{
			board[row_num + j][col_num] = ship_type;
		}
	}
}


/*************************************************************
* Function:	check_shot()     				                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: checks to see if the shot hit or missed		*
*															*
* Input parameters: game board, x, y, check_shot[]			*
* Returns: int 0 if miss 1 if hit			                *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int check_shot(char board[MAX_ROWS][MAX_COLS], int x, int y, int* check_shot)
{
	if (board[y][x] != 'C' && board[y][x] != 'B' && board[y][x] != 'R' && board[y][x] != 'S' && board[y][x] != 'D')
	{
		++check_shot[0];
		return 0;
	}
	else if (board[y][x] == 'C')
	{
		++check_shot[1];
		return 1;
	}
	else if (board[y][x] == 'B')
	{
		++check_shot[2];
		return 1;
	}
	else if (board[y][x] == 'R')
	{
		++check_shot[3];
		return 1;
	}
	else if (board[y][x] == 'S')
	{
		++check_shot[4];
		return 1;
	}
	else if (board[y][x] == 'D')
	{
		++check_shot[5];
		return 1;
	}
}


/*************************************************************
* Function:	is_winner()						                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: checks to see if a player won				*
*															*
* Input parameters: check_shot[]				            *
* Returns: int 1 if won 0 if not won			            *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int is_winner(int* check_shot)
{
	if (check_shot[1] == 5 && check_shot[2] == 4 && check_shot[3] == 3 && check_shot[4] == 3 && check_shot[5] == 2)
	{
		return 1;
	}
	return 0;
}


/*************************************************************
* Function:	update_board()					                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: updates the board depending on the shot		*
*															*
* Input parameters: game board, x, y, is_hit_or_miss		*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void update_board(char board[MAX_ROWS][MAX_COLS], int x, int y, int is_hit_or_miss)
{
	if (is_hit_or_miss == 1)
	{
		board[y][x] = '*';
	}
	else if (is_hit_or_miss == 0)
	{
		board[y][x] = 'm';
	}
	else
	{
		board[y][x] == 'E'; // trying to see if there is any value for is_hit_or_miss that isnt 1 or 0
	}
}


/*************************************************************
* Function:	display_board()					                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints the game board						*
*															*
* Input parameters: game board, rows, cols				    *
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void display_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols)
{
	
	
	printf("      0   1   2   3   4   5   6   7   8   9\n");
	for (int row_index = 0; row_index < rows; ++row_index)
	{
		printf("  %d  ", row_index);

		for (int col_index = 0; col_index < cols; ++col_index)
		{
			printf(" %c  ", board[row_index][col_index]);
		}

		printf("\n");
	}

}


/*************************************************************
* Function:	output_current_move()				            *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: gives a computer generated shot				*
*															*
* Input parameters: game board,	col, row, last_hit_row,		*
*					last_hit_col, check_shot[],				*
*					which_ships_sunk[]			            *
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void output_current_move(char board[MAX_ROWS][MAX_COLS], int *col_ptr, int *row_ptr, int last_hit_row, int last_hit_col, int *check_shot, int *which_ships_sunk)
{
	int is_incomplete_ship = 0; // if there is a ship that has been hit but not sunk this will change to 1
	int intel_shot = 0; 
	int stop = 0; // stops the loop when it's equal to 4
	int already_tried[4] = { 0 , 0 , 0 , 0 };
	int i = 0;
	int j = 0;

	for (int i = 1; i != 6; ++i) // checks to see if a ship has been hit but not sunk
	{
		if (check_shot[i] != 0 && which_ships_sunk[i] != 1)
		{
			is_incomplete_ship = 1;
		}
	}



	if (is_incomplete_ship == 1) // if a ship is hit but not sunk
	{
		do
		{
			*col_ptr = last_hit_col;
			*row_ptr = last_hit_row;

			if (*col_ptr == 0)
			{
				already_tried[0] = 1;
				i = 1;
			}
			if (*col_ptr == 9)
			{
				already_tried[1] = 1;
				i = 2;
			}
			if (*row_ptr == 0)
			{
				already_tried[2] = 1;
				j = 3;
			}
			if (*row_ptr == 9)
			{
				already_tried[3] = 1;
				j = 4;
			}
			
			do
			{
				intel_shot = rand() % 4 + 1;
			} while (intel_shot == i || intel_shot == j);

			if (intel_shot == 1 && already_tried[0] == 0)
			{
				--*col_ptr;
				++already_tried[0];
			}
			else if (intel_shot == 2 && already_tried[1] == 0)
			{
				++*col_ptr;
				++already_tried[1];
			}
			else if (intel_shot == 3 && already_tried[2] == 0)
			{
				--*row_ptr;
				++already_tried[2];
			}
			else if (intel_shot == 4 && already_tried[3] == 0)
			{
				++*row_ptr;
				++already_tried[3];
			}
			
			stop = already_tried[0] + already_tried[1] + already_tried[2] + already_tried[3];

			//intel_shot++;

		} while ((board[*row_ptr][*col_ptr] == 'm' || board[*row_ptr][*col_ptr] == '*') && stop != 4);
	}
	if (stop == 4 || is_incomplete_ship != 1) // if there are no ships that have been hit but are not complete or the previous loop has checked all points around the last hit
	{
		do
		{
			*col_ptr = rand() % 10;
			*row_ptr = rand() % 10;
		} while (board[*row_ptr][*col_ptr] == 'm' || board[*row_ptr][*col_ptr] == '*');
	}
}


/*************************************************************
* Function:	check_if_sunk_ship()				            *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: checks to see if a ship was sunk	and prints	*
*				out which one was sunk						*
*															*
* Input parameters: check_shot[], which_ships_sunk[],		*
*					player_number				            *
* Returns: int number of ship or 0 if none sunk			    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int check_if_sunk_ship(int* check_shot, int* which_ships_sunk, int player_number)
{
	if (player_number == 1)
	{
		if (check_shot[1] == 5 && which_ships_sunk[1] == 0)
		{
			printf("\n\nThe enemy Carrier has been sunk!\n\n");
			which_ships_sunk[1] = 1;
			return 1;
		}
		else if (check_shot[2] == 4 && which_ships_sunk[2] == 0)
		{
			printf("\n\nThe enemy Battleship has been sunk!\n\n");
			which_ships_sunk[2] = 1;
			return 2;
		}
		else if (check_shot[3] == 3 && which_ships_sunk[3] == 0)
		{
			printf("\n\nThe enemy Cruiser has been sunk!\n\n");
			which_ships_sunk[3] = 1;
			return 3;
		}
		else if (check_shot[4] == 3 && which_ships_sunk[4] == 0)
		{
			printf("\n\nThe enemy Submarine has been sunk!\n\n");
			which_ships_sunk[4] = 1;
			return 4;
		}
		else if (check_shot[5] == 2 && which_ships_sunk[5] == 0)
		{
			printf("\n\nThe enemy Destroyer has been sunk!\n\n");
			which_ships_sunk[5] = 1;
			return 5;
		}
	}
	if (player_number == 2)
	{
		if (check_shot[1] == 5 && which_ships_sunk[1] == 0)
		{
			printf("\n\nCaptain, our Carrier has been sunk!\n\n");
			which_ships_sunk[1] = 1;
			return 1;
		}
		else if (check_shot[2] == 4 && which_ships_sunk[2] == 0)
		{
			printf("\n\nCaptain, our Battleship has been sunk!\n\n");
			which_ships_sunk[2] = 1;
			return 2;
		}
		else if (check_shot[3] == 3 && which_ships_sunk[3] == 0)
		{
			printf("\n\nCaptain, our Cruiser has been sunk!\n\n");
			which_ships_sunk[3] = 1;
			return 3;
		}
		else if (check_shot[4] == 3 && which_ships_sunk[4] == 0)
		{
			printf("\n\nCaptain, our Submarine has been sunk!\n\n");
			which_ships_sunk[4] = 1;
			return 4;
		}
		else if (check_shot[5] == 2 && which_ships_sunk[5] == 0)
		{
			printf("\n\nCaptain, our Destroyer has been sunk!\n\n");
			which_ships_sunk[5] = 1;
			return 5;
		}
	}
	return 0;
}


/*************************************************************
* Function:	output_stats()					                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints the stats to the battleship.log file	*
*															*
* Input parameters: outfile, stats p1, stats p2				*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void output_stats(FILE* outfile, Stats p1, Stats p2)
{
	fprintf(outfile, "*** Player 1 Stats ***\n");
	fprintf(outfile, "Number of Hits: %d\n", p1.hits);
	fprintf(outfile, "Number of Misses: %d\n", p1.misses);
	fprintf(outfile, "Total Shots: %d\n", p1.total_shots);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf\n", p1.ratio);
	fprintf(outfile, "\n");

	fprintf(outfile, "*** Player 2 Stats ***\n");
	fprintf(outfile, "Number of Hits: %d\n", p2.hits);
	fprintf(outfile, "Number of Misses: %d\n", p2.misses);
	fprintf(outfile, "Total Shots: %d\n", p2.total_shots);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf\n", p2.ratio);

}


/*************************************************************
* Function:	give_ship_info()				                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints the ship name and number of spaces	*
*															*
* Input parameters: ship				                    *
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void give_ship_info(int ship)
{
	if (ship == 0)
	{
		printf("Place the Carrier. This ship takes 5 spaces\n\n");
	}
	else if (ship == 1)
	{
		printf("Place the Battleship. This ship takes 4 spaces\n\n");
	}
	else if (ship == 2)
	{
		printf("Place the Cruiser. This ship takes 3 spaces\n\n");
	}
	else if (ship == 3)
	{
		printf("Place the Submarine. This ship takes 3 spaces\n\n");
	}
	else if (ship == 4)
	{
		printf("Place the Destroyer. This ship takes 2 spaces\n\n");
	}
}


/*************************************************************
* Function:	get_current_move()				                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: gets a target from the user					*
*															*
* Input parameters: game_board, column, row				    *
* Returns: int 0 if good 1 if bad			                *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int get_current_move(char board[MAX_ROWS][MAX_COLS], int *col_ptr, int *row_ptr)
{
	int col = 0;
	int row = 0;

	printf("\n\nEnter the coordinate you would like to target: \n");
	scanf("%d%d", &col, &row);

	if (board[row][col] == 'm' || board[row][col] == '*' || col > 9 || col < 0 || row > 9 || row < 0)
	{
		return 1;
	}
	else
	{
		*col_ptr = col;
		*row_ptr = row;

		return 0;
	}

}


/*************************************************************
* Function:	delcare_winner()				                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints the winner to the screen and outfile	*
*															*
* Input parameters: outfile, who_won				        *
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void declare_winner(FILE* outfile, int who_won)
{
	if (who_won == 1)
	{
		fprintf(outfile, "\nYou won, player 2 lost\n\n\n");
		printf("YOU WON!!!\n\n");
		printf("Go to battleship.log to see your stats.\n\n");
	}
	else if (who_won == 2)
	{
		fprintf(outfile, "\nYou lost, player 2 won\n\n\n");
		printf("you lost :(\n\n");
		printf("Go to battleship.log to see your stats.");
	}
}


/*************************************************************
* Function:	show_sunk()						                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints a list of sunk ships					*
*															*
* Input parameters: which_ships_sunk[], player_num			*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void show_sunk(int* which_ships_sunk, int player_num)
{
	if (player_num == 1)
	{
		printf("\nEnemy ships sunk without a trace:\n\n");
	}
	else if (player_num == 2)
	{
		printf("\nYour sunken ships:\n\n");
	}

	if (which_ships_sunk[1] != 0)
	{
		printf("Carrier\n");
	}
	if (which_ships_sunk[2] != 0)
	{
		printf("Battleship\n");
	}
	if (which_ships_sunk[3] != 0)
	{
		printf("Cruiser\n");
	}
	if (which_ships_sunk[4] != 0)
	{
		printf("Submarine\n");
	}
	if (which_ships_sunk[5] != 0)
	{
		printf("Destroyer\n");
	}
	
	printf("\n");
}


/*************************************************************
* Function:	play_again()					                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: asks the player whether they want to play	*
*			again and returns the result					*
*															*
* Input parameters: void				                    *
* Returns: char 			                                *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
char play_again(void)
{
	char result = '\0';

	do
	{
		printf("Would you like to play again? Enter Y for yes or N for no.");
		scanf(" %c", &result);

		system("cls");
	} while (result != 'Y' && result != 'y' && result != 'N' && result != 'n');

	return result;
}


/*************************************************************
* Function:	log_shot()						                *
* Date Created: 11/16/2020                                  *
* Date Last Modified: 11/16/2020							*
*															*
* Description: prints a shot to the battleship.log file		*
*															*
* Input parameters: outfile, row, col, is_hit_or_miss,		*
*					which_ship_sunk[], player_number		*
* Returns: void			                                    *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void log_shot(FILE* outfile, int row, int col, int is_hit_or_miss, int which_ship_sunk, int player_number)
{
	if (which_ship_sunk == 0 && is_hit_or_miss == 0)
	{
		fprintf(outfile, "Player %d: %d,%d Miss\n", player_number, row, col);
	}
	else if (which_ship_sunk == 0 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit\n", player_number, row, col);
	}
	else if (which_ship_sunk == 1 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit Sunk Carrier\n", player_number, row, col);
	}
	else if (which_ship_sunk == 2 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit Sunk Battleship\n", player_number, row, col);
	}
	else if (which_ship_sunk == 3 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit Sunk Cruiser\n", player_number, row, col);
	}
	else if (which_ship_sunk == 4 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit Sunk Submarine\n", player_number, row, col);
	}
	else if (which_ship_sunk == 5 && is_hit_or_miss == 1)
	{
		fprintf(outfile, "Player %d: %d,%d Hit Sunk Destroyer\n", player_number, row, col);
	}
}