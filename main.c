/*
		Programmer: Cole Clark
		Date: 11/12/2020

		Description: Battleship game for PA6
*/

#include "battleship.h"

int main(void)
{
	srand((unsigned int)time(NULL));

	char play_again_answer = '\0';

	do
	{

		FILE* outfile = fopen("battleship.log", "w");

		Stats player1;
		Stats player2;

		char* game_board1[MAX_ROWS][MAX_COLS] = { { '\0' } };
		char* game_board2[MAX_ROWS][MAX_COLS] = { { '\0' } };
		char* hit_or_miss[MAX_ROWS][MAX_COLS] = { { '\0' } };

		int check_shot_p1[6] = { 0 };
		int check_shot_p2[6] = { 0 };
		int which_ships_sunk_p1[6] = { 0 };
		int which_ships_sunk_p2[6] = { 0 };
		int is_game_over = 0;
		int is_hit_or_miss = 0;
		int who_starts = 0;
		int p2_col = 0;
		int p2_row = 0;
		int p1_col = 0;
		int p1_row = 0;
		int who_won = 0;
		int good_move = 2;
		int last_hit_row = 0;
		int last_hit_col = 0;
		int which_ship_sunk = 0;

		char carrier = 'C';
		char battleship = 'B';
		char cruiser = 'R';
		char submarine = 'S';
		char destroyer = 'D';

		char rand_or_manual = '\0';
		int x = 0;
		int y = 0;

		char horizontal_or_vertical = '\0';

		initialize_game_board(game_board1, MAX_ROWS, MAX_COLS);
		initialize_game_board(game_board2, MAX_ROWS, MAX_COLS);
		initialize_game_board(hit_or_miss, MAX_ROWS, MAX_COLS);

		randomly_place_ships_on_board(game_board2, 5, carrier);
		randomly_place_ships_on_board(game_board2, 4, battleship);
		randomly_place_ships_on_board(game_board2, 3, cruiser);
		randomly_place_ships_on_board(game_board2, 3, submarine);
		randomly_place_ships_on_board(game_board2, 2, destroyer);

		welcome_screen();
		system("pause");
		system("cls");

		do // asks whether to place randomly or manually repeats if an option isn't selected
		{

			printf("Would you like to choose your Ship locations or have them randomly selected for you?\n Enter R for random or M to manually select.\n");
			scanf(" %c", &rand_or_manual);
			system("cls");
		} while (rand_or_manual != 'R' && rand_or_manual != 'r' && rand_or_manual != 'M' && rand_or_manual != 'm');

		if (rand_or_manual == 'r' || rand_or_manual == 'R') // if the player wants randomly placed ships
		{
			randomly_place_ships_on_board(game_board1, 5, carrier);
			randomly_place_ships_on_board(game_board1, 4, battleship);
			randomly_place_ships_on_board(game_board1, 3, cruiser);
			randomly_place_ships_on_board(game_board1, 3, submarine);
			randomly_place_ships_on_board(game_board1, 2, destroyer);
		}

		else if (rand_or_manual == 'm' || rand_or_manual == 'M') // if the player wants to place their ships manually 
		{
			int ship = 0;
			int placement_good_bad = 0;

			while (ship != 5)
			{
				printf("To place ships enter a 'V' for vertical or 'H' for horizontal.\n Then enter the coordinates of the top or farthest left point where you want to place.\n\n");

				give_ship_info(ship);

				display_board(game_board1, MAX_ROWS, MAX_COLS);

				printf("\n\n");
				scanf(" %c", &horizontal_or_vertical);
				scanf("%d%d", &x, &y);

				placement_good_bad = manually_place_ships_on_board(game_board1, ship, horizontal_or_vertical, y, x);

				if (placement_good_bad != 1)
				{
					++ship;
				}
				system("cls");

			}

		}

		display_board(game_board1, MAX_ROWS, MAX_COLS); // print players game board
		who_starts = select_who_starts_first(); // chooses who will start and prints it out for the player to see
		system("pause"); // pauses so player can see the message
		system("cls"); // clears the screen before starting the game

		if (who_starts == 1)
		{
			do
			{

				do
				{
					printf("\t\tTarget Board\n\n"); //prints target board
					display_board(hit_or_miss, MAX_ROWS, MAX_COLS); // shows the target board for the player
					show_sunk(which_ships_sunk_p2, 1); // shows a list of the enemy ships that have been sunk
					good_move = get_current_move(hit_or_miss, &p1_col, &p1_row); // gets coordinates to hit from the user
					system("cls"); // clears the screen

				} while (good_move != 0); // makes sure the spot hasn't been targeted before and that the target is on the board

				is_hit_or_miss = check_shot(game_board2, p1_col, p1_row, check_shot_p2); // checks to see if the shot hit or missed. returns 1 if hit, 0 if missed and updates and array to determine whether the player won
				update_board(hit_or_miss, p1_col, p1_row, is_hit_or_miss); // changes the target board to see enemy hits and misses

				printf("\t\tTarget Board\n\n");
				display_board(hit_or_miss, MAX_ROWS, MAX_COLS);
				which_ship_sunk = check_if_sunk_ship(check_shot_p2, which_ships_sunk_p2, 1);
				show_sunk(which_ships_sunk_p2, 1);

				log_shot(outfile, p1_row, p1_col, is_hit_or_miss, which_ship_sunk, 1);
				is_game_over = is_winner(check_shot_p2); // returns 1 if the game is over returns 0 if it is not over
				who_won = 1;

				system("pause"); // pauses so player can see the message
				system("cls"); // clears the screen before starting the game

				if (is_game_over != 1)
				{
					output_current_move(game_board1, &p2_col, &p2_row, last_hit_row, last_hit_col, check_shot_p1, which_ships_sunk_p1); // gets coordinates from player 2 and stores them in p2_col and p2_row
					is_hit_or_miss = check_shot(game_board1, p2_col, p2_row, check_shot_p1); // checks to see if the shot hit or missed. returns 1 if hit, 0 if missed and updates and array to determine whether the player won

					if (is_hit_or_miss == 1)
					{
						last_hit_col = p2_col;
						last_hit_row = p2_row;
					}

					update_board(game_board1, p2_col, p2_row, is_hit_or_miss); // changes the players board to see enemy hits and misses
					display_board(game_board1, MAX_ROWS, MAX_COLS); // shows players updated board after player2's turn
					which_ship_sunk = check_if_sunk_ship(check_shot_p1, which_ships_sunk_p1, 2);
					show_sunk(which_ships_sunk_p1, 2);

					log_shot(outfile, p2_row, p2_col, is_hit_or_miss, which_ship_sunk, 2);
					is_game_over = is_winner(check_shot_p1); // returns 1 if the game is over returns 0 if it is not over
					who_won = 2;

					system("pause"); // pauses so player can see the message
					system("cls"); // clears the screen before starting the game

				}

			} while (is_game_over != 1);
		}

		if (who_starts == 2)
		{
			do
			{
				output_current_move(game_board1, &p2_col, &p2_row, last_hit_row, last_hit_col, check_shot_p1, which_ships_sunk_p1); // gets coordinates from player 2 and stores them in p2_col and p2_row
				is_hit_or_miss = check_shot(game_board1, p2_col, p2_row, check_shot_p1); // checks to see if the shot hit or missed. returns 1 if hit, 0 if missed and updates and array to determine whether the player won

				if (is_hit_or_miss == 1)
				{
					last_hit_col = p2_col;
					last_hit_row = p2_row;
				}

				update_board(game_board1, p2_col, p2_row, is_hit_or_miss); // changes the players board to see enemy hits and misses
				display_board(game_board1, MAX_ROWS, MAX_COLS); // shows players updated board after player2's turn
				which_ship_sunk = check_if_sunk_ship(check_shot_p1, which_ships_sunk_p1, 2);
				show_sunk(which_ships_sunk_p1, 2);

				log_shot(outfile, p2_row, p2_col, is_hit_or_miss, which_ship_sunk, 2);
				is_game_over = is_winner(check_shot_p1); // returns 1 if the game is over returns 0 if it is not over
				who_won = 2;

				system("pause"); // pauses so player can see the message
				system("cls"); // clears the screen before starting the game

				if (is_game_over != 1)
				{
					do
					{
						printf("\t\tTarget Board\n\n"); //prints target board
						display_board(hit_or_miss, MAX_ROWS, MAX_COLS); // shows the target board for the player
						show_sunk(which_ships_sunk_p2, 1); // shows a list of the enemy ships that have been sunk
						good_move = get_current_move(hit_or_miss, &p1_col, &p1_row); // gets coordinates to hit from the user
						system("cls"); // clears the screen

					} while (good_move != 0); // makes sure the spot hasn't been targeted before and that the target is on the board

					is_hit_or_miss = check_shot(game_board2, p1_col, p1_row, check_shot_p2); // checks to see if the shot hit or missed. returns 1 if hit, 0 if missed and updates and array to determine whether the player won
					update_board(hit_or_miss, p1_col, p1_row, is_hit_or_miss); // changes the players board to see enemy hits and misses

					printf("\t\tTarget Board\n\n");
					display_board(hit_or_miss, MAX_ROWS, MAX_COLS);
					which_ship_sunk = check_if_sunk_ship(check_shot_p2, which_ships_sunk_p2, 1);
					show_sunk(which_ships_sunk_p2, 1);

					log_shot(outfile, p1_row, p1_col, is_hit_or_miss, which_ship_sunk, 1);
					is_game_over = is_winner(check_shot_p2); // returns 1 if the game is over returns 0 if it is not over
					who_won = 1;

					system("pause"); // pauses so player can see the message
					system("cls"); // clears the screen before starting the game

				}

			} while (is_game_over != 1);
		}

		player1.hits = check_shot_p2[1] + check_shot_p2[2] + check_shot_p2[3] + check_shot_p2[4] + check_shot_p2[5];
		player1.misses = check_shot_p2[0];
		player1.total_shots = player1.hits + player1.misses;
		player1.ratio = ( (double) player1.hits / (double) player1.misses) * 100;

		player2.hits = check_shot_p1[1] + check_shot_p1[2] + check_shot_p1[3] + check_shot_p1[4] + check_shot_p1[5];
		player2.misses = check_shot_p1[0];
		player2.total_shots = player2.hits + player2.misses;
		player2.ratio = ( (double) player2.hits / (double) player2.misses) * 100;

		declare_winner(outfile, who_won);
		output_stats(outfile, player1, player2);

		fclose(outfile);

		play_again_answer = play_again();

	} while (play_again_answer != 'N' && play_again_answer != 'n');


	return 0;
}