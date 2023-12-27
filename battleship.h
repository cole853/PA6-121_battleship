/*	
		Programmer: Cole Clark
		Date: 11/12/2020

		Description: Battleship game for PA6
*/
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define _CRT_SECURE_NO_WARNINGS

#define MAX_ROWS 10
#define MAX_COLS 10

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct stats
{
	int hits;
	int misses;
	int total_shots;
	double ratio;

}Stats;


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
void welcome_screen(void);


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
void initialize_game_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols);


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
int select_who_starts_first(void);


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
int manually_place_ships_on_board(char board[MAX_ROWS][MAX_COLS], int ship, char direction, int row_num, int col_num);


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
void randomly_place_ships_on_board(char board[MAX_ROWS][MAX_COLS], int length, char ship_type);


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
int check_shot(char board[MAX_ROWS][MAX_COLS], int x, int y, int* check_shot);


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
int is_winner(int* check_shot);


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
void update_board(char board[MAX_ROWS][MAX_COLS], int x, int y, int is_hit_or_miss);


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
void display_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols);


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
void output_current_move(char board[MAX_ROWS][MAX_COLS], int* col_ptr, int* row_ptr, int last_hit_row, int last_hit_col, int* check_shot, int* which_ships_sunk);


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
int check_if_sunk_ship(int* check_shot, int* which_ships_sunk, int player_number);


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
void output_stats(FILE* outfile, Stats p1, Stats p2);


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
void give_ship_info(int ship);


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
int get_current_move(char board[MAX_ROWS][MAX_COLS], int* col_ptr, int* row_ptr);


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
void declare_winner(FILE* outfile, int who_won);


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
void show_sunk(int* which_ships_sunk, int player_num);


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
char play_again(void);


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
void log_shot(FILE* outfile, int row, int col, int is_hit_or_miss, int which_ship_sunk, int player_number);

#endif