#include "game.h"

/* INRTODUCTORY PARAGRAPH
 * ----------------------
 * This code provides an implementation of the 2048 game through a combination of functions. The 'make' function creates a new board with a set number of rows and columns defined by the user, by 
 * initialising the members of a pre-defined structure. The score is set to zero and all of the cells have an initial value of -1 to indicate null. The 'remake' function is very similar and 
 * involves reinitialising members of the old structure. Additionally, there are four functions to slide the cells in a given direction, which corresponds to either 'w', 'a', 's', or 'd' on the
 * keyboard. These functions also combine adjacent cells with the same value in the specified direction and subsequently update the score. Finally, the 'legal move check' function checks if any
 * remaining moves are available by checking for empty cells and/or adjacent cells with the same values.
*/  

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
	//Dynamically allocate memory for game and cells (DO NOT modify this)
	game * mygame = malloc(sizeof(game));
	mygame->cells = malloc(rows*cols*sizeof(cell));
	
	mygame->rows = rows;
	mygame->cols = cols;
	mygame->score = 0;
	
	for(int x = 0; x < rows*cols; x++)
	{
		mygame->cells[x] = -1;
	} 

	return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	(*_cur_game_ptr)->rows = new_rows;
	(*_cur_game_ptr)->cols = new_cols;
	(*_cur_game_ptr)-> score = 0;

	for(int x = 0; x < new_rows*new_cols; x++)
	{
		(*_cur_game_ptr)->cells[x] = -1;
	} 

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
	int rows, cols;

	rows = cur_game -> rows;
	cols = cur_game -> cols;
		
	cell *ptr;
	
	if(row < 0 || col < 0 || row*cols + col < 0 || row*cols + col >= rows*cols)
	{
		return NULL;
	}
	else
	{
		ptr = &(cur_game->cells[row*cols + col]);
		return ptr;
	}
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{	
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < cols; i++)
	{

		int l = -1; //initialises last combined row

		for(j = 1; j < rows; j++) //first spot doesn't need to be moved as it's already at the top
		{
			if(cur_game->cells[j*cols + i] != -1) 
			{
				int k = 0;
				
				while(k < j)
				{
					if(cur_game->cells[k*cols + i] == -1)
					{
						break;
					}
					k++;
				}

				if(k < j) //move stuff
				{
					cur_game->cells[k*cols + i] = cur_game->cells[j*cols + i];
					cur_game->cells[j*cols + i] = -1; //clear it
					flag = 1;
				}

				if(k-1 != l)
				{
					if(cur_game->cells[(k-1)*cols + i] == cur_game->cells[k*cols + i])
					{
						cur_game->cells[(k-1)*cols + i] += cur_game->cells[k*cols + i];
						cur_game->cells[k*cols + i] = -1;
						cur_game->score += cur_game->cells[(k-1)*cols + i];
						l = k-1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int move_s(game * cur_game) //slide down
{
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < cols; i++)
	{

		int l = -1; //initialises last combined row

		for(j = rows-1; j >= 0; j--) 
		{
			if(cur_game->cells[j*cols + i] != -1)
			{
				int k = rows-1;
				
				while(k > j)
				{
					if(cur_game->cells[k*cols + i] == -1)
					{
						break;
					}
					k--;
				}

				if(k > j) //move stuff
				{
					cur_game->cells[k*cols + i] = cur_game->cells[j*cols + i];
					cur_game->cells[j*cols + i] = -1; //clear it
					flag = 1;
				}

				if(k+1 != l)
				{
					if(cur_game->cells[(k+1)*cols + i] == cur_game->cells[k*cols + i])
					{
						cur_game->cells[(k+1)*cols + i] += cur_game->cells[k*cols + i];
						cur_game->cells[k*cols + i] = -1;
						cur_game->score += cur_game->cells[(k+1)*cols + i];
						l = k+1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int move_a(game * cur_game) //slide left
{
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < rows; i++)
	{

		int l = -1; //initialises last combined column

		for(j = 1; j < cols; j++) //first spot doesn't need to be moved as it's already in the left-most position
		{
			if(cur_game->cells[i*cols + j] != -1)
			{
				int k = 0;
				
				while(k < j)
				{
					if(cur_game->cells[i*cols + k] == -1)
					{
						break;
					}
					k++;
				}

				if(k < j) //move stuff
				{
					cur_game->cells[i*cols + k] = cur_game->cells[i*cols + j]; 
					cur_game->cells[i*cols + j] = -1; //clear it
					flag = 1;
				}

				if(k-1 != l) 
				{
					if(cur_game->cells[i*cols + (k-1)] == cur_game->cells[i*cols + k]) 
					{
						cur_game->cells[i*cols + (k-1)] += cur_game->cells[i*cols + k];
						cur_game->cells[i*cols + k] = -1;
						cur_game->score += cur_game->cells[i*cols + (k-1)];
						l = k-1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int move_d(game * cur_game) //slide to the right
{
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < rows; i++)
	{

		int l = -1; //initialises last combined column

		for(j = cols-1; j >= 0; j--) 
		{
			if(cur_game->cells[i*cols + j] != -1)
			{
				int k = cols-1;
				
				while(k > j)
				{
					if(cur_game->cells[i*cols + k] == -1)
					{
						break;
					}
					k--;
				}

				if(k > j) //move stuff
				{
					cur_game->cells[i*cols + k] = cur_game->cells[i*cols + j];
					cur_game->cells[i*cols + j] = -1; //clear it
					flag = 1;
				}

				if(k+1 != l)
				{
					if(cur_game->cells[i*cols + (k+1)] == cur_game->cells[i*cols + k])
					{
						cur_game->cells[i*cols + (k+1)] += cur_game->cells[i*cols + k];
						cur_game->cells[i*cols + k] = -1;
						cur_game->score += cur_game->cells[i*cols + (k+1)];
						l = k+1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
	int i, j, rows, cols;

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			int a, b, c, d, x;
			
			a = i + 1;
			b = i - 1;
			c = j + 1;
			d = j - 1;				

			if(cur_game->cells[i*cols + j] == -1)
			{
				return 1;
			}

			if(a > rows*cols) //checks for out of bounds exception
			{
				x = 0; //do nothing
			}
			else
			{
				if(cur_game->cells[a*cols + j] == cur_game->cells[i*cols + j]) //check if cell below is identical
				{
					return 1;
				}
			}
			
			if(b < 0)
			{
				x = 0;
			}
			else
			{
				if(cur_game->cells[b*cols + j] == cur_game->cells[i*cols + j]) //checks cell above
				{
					return 1;
				}
			}	
			if(c > rows*cols)
			{
				x = 0;
			}
			else
			{
				if(cur_game->cells[i*cols + c] == cur_game->cells[i*cols + j]) //checks cell to the right
				{
					return 1;
				}
			}

			if(d < 0)
			{
				x = 0;
			}
			else
			{
				if(cur_game->cells[i*cols + d] == cur_game->cells[i*cols + j]) //checks cell to the left
				{
					return 1;
				}
			}
		}
	}
	return 0; //no empty or matching adjacent cells found
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
