// Author: Kaylea Box;  Course: COSC 1337 Spring 2016 TT13;  Instructor: Thayer
// Lab: 8 Purpose: this program will use a class and arrays to create a 
// tic-tac-toe board and will allow the user to play the game.

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;
 
 class Board //class definition
 {
 	private:
	char board[3][3]{{'7','8','9'},{'4','5','6'},{'1','2','3'}};
	
	public: 
	void set_board();
	void show_board();
	void make_move(char player);
	bool check_move(int move);
	char check_status();
	void won (char winner);
 };
 
WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}

void place_cursor(HANDLE, int, int);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);
int get_int(string prompt,string badch_errmsg,string range_errmsg, int lo, int hi);
 
int main()
{
	Board game;
//	place_cursor(hConsole, 2, 10);cout<<"let's play toc_tac_toe!\n"; 
	game.show_board();
	char player = 'x';
  	bool playing=true;
  	float x_wins = 0; float o_wins = 0; float cats_wins = 0; int num_games = 1;
  	while(playing) 
	{
		game.make_move(player);	
		game.show_board();
		char winner = game.check_status();
		
		if (winner == 'x')
		{	x_wins += 1;}
		else if (winner == 'o')
		{	o_wins += 1;}
		else if (winner == 'n')
		{	cats_wins +=1;}
		
		if (winner == 'o' or winner == 'x' or winner == 'n')
			{	SetConsoleTextAttribute(hConsole, saved_colors); 
				playing = get_int("would you like to play again? 0 to quit 1 to continue. ",
				"invalid input. ", "input out of range ", 0, 1);
				Sleep(1000);system("CLS");
				if (playing)
				{	num_games += 1; game.set_board(); game.show_board();}
				if (!playing)
				{	
					cout<<"you played "<<num_games<<" games.\n"; 
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); cout<< "x won "<<x_wins/num_games*100<<" %.\n"; 
				 	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); cout<<"o won "<<o_wins/num_games*100<<" %.\n";
					SetConsoleTextAttribute(hConsole, saved_colors); cout<<cats_wins/num_games*100<<" % were cat's games.\n";
				}
			}
			
		player=(player=='x'?'o':'x');
	}
}
//print the board on the screen
void Board::show_board()
{
	place_cursor(hConsole, 2, 10);cout<<"let's play toc_tac_toe!\n";
	int pos_x = 3;
	for (int row=0; row<3; row++)
	{
		place_cursor(hConsole, pos_x, 16);
		for(int col=0; col<3; col++)
		{
			if (board[row][col]== 'x')
			{ SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);}
			else if (board[row][col]== 'o')
			{SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);}
			else 
			{SetConsoleTextAttribute(hConsole, saved_colors);}
			cout<<" "<<board [row][col]<<" ";
			if (col>=0 and col<2)
			{	SetConsoleTextAttribute(hConsole, saved_colors); cout<<"|";}
		}
		if(row >=0 and row<2)
		{	SetConsoleTextAttribute(hConsole, saved_colors); place_cursor(hConsole, pos_x+=1, 16); cout<<"___________";}
		
		cout<<endl;
		pos_x += 1;	
	}
}
//make a move on the board
void Board::make_move(char player)
{
	SetConsoleTextAttribute(hConsole, saved_colors);
	int move = get_int("\nwhere would you like to play on the board?", // get the move and check input
	"invalid input. ","input out of range. ", 1, 9);
	bool bool_move = check_move(move);
	while (!bool_move) //check to see if the move is valid
	{	
		cout<<"enter an open space. "; cin>>move; bool_move = check_move(move);
		place_cursor(hConsole, 11, 0); cout<<"\t\t\t\t\t\t\t";
	}
	//record the move if it is valid
	switch (move)
	{
		case 1: {	board[2][0] = player; break;}
		case 2: {	board[2][1] = player; break;}  
		case 3: {	board[2][2] = player; break;} 
		case 4: {	board[1][0] = player; break;} 
		case 5: {	board[1][1] = player; break;} 
		case 6: {	board[1][2] = player; break;} 
		case 7: {	board[0][0] = player; break;} 
		case 8: {	board[0][1] = player; break;} 
		case 9: {	board[0][2] = player; break;}
		default: {	cout<<"invalid input. "; break;} 
	}
}
//check the game status, has someone won, are there open spaces
char Board:: check_status()
{
	char winner; 
	//check all the winning combinations
	if (board[0][0]== 'x' and board[0][1]== 'x' and board[0][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[0][0]== 'x' and board[1][0]== 'x' and board[2][0]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[1][0]== 'x' and board[1][1]== 'x' and board[1][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[0][1]== 'x' and board[1][1]== 'x' and board[2][1]=='x')
	{	 winner = 'x'; won (winner);}
	else if (board[0][2]== 'x' and board[1][2]== 'x' and board[2][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[2][0]== 'x' and board[2][1]== 'x' and board[2][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[0][0]== 'x' and board[1][1]== 'x' and board[2][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[2][0]== 'x' and board[1][1]== 'x' and board[0][2]=='x')
	{	winner = 'x'; won (winner);}
	else if (board[0][0]== 'o' and board[0][1]== 'o' and board[0][2]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[0][0]== 'o' and board[1][0]== 'o' and board[2][0]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[1][0]== 'o' and board[1][1]== 'o' and board[1][2]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[0][1]== 'o' and board[1][1]== 'o' and board[2][1]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[0][2]== 'o' and board[1][2]== 'o' and board[2][2]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[2][0]== 'o' and board[2][1]== 'o' and board[2][2]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[0][0]== 'o' and board[1][1]== 'o' and board[2][2]=='o')
	{	winner = 'o'; won (winner);}
	else if (board[2][0]== 'o' and board[1][1]== 'o' and board[0][2]=='o')
	{	winner = 'o'; won (winner);}
	//find out if it is a cat's games by checking for open spots on the board
	bool bool_spot;
	int spot =1; 
	switch(spot)
	{
		case 1: {bool_spot=(board[2][0] == '1'? true : false); if (bool_spot) break;}
		case 2: {bool_spot=(board[2][1] == '2'? true : false); if (bool_spot) break;}  
		case 3: {bool_spot=(board[2][2] == '3'? true : false); if (bool_spot) break;} 
		case 4: {bool_spot=(board[1][0] == '4'? true : false); if (bool_spot) break;} 
		case 5: {bool_spot=(board[1][1] == '5'? true : false); if (bool_spot) break;} 
		case 6: {bool_spot=(board[1][2] == '6'? true : false); if (bool_spot) break;} 
		case 7: {bool_spot=(board[0][0] == '7'? true : false); if (bool_spot) break;}
		case 8: {bool_spot=(board[0][1] == '8'? true : false); if (bool_spot) break;} 
		case 9: {bool_spot=(board[0][2] == '9'? true : false); if (bool_spot) break;}
		default: {	break;} 
	}
	if (!bool_spot and winner!='x' and winner!='o')
	{	
		place_cursor(hConsole, 5, 40); SetConsoleTextAttribute(hConsole, saved_colors);
		cout<<"it's a cat's game!\n"; winner = 'n';
	}
	
	return winner;
}
//print out winner information if the game is over
void Board::won(char winner)
{
	place_cursor(hConsole, 5, 40);cout<<winner<< " won! "<<winner<<" won! "<<winner<<" won! \n";
}
//check to see if the move is taken
bool Board::check_move(int move)
{
	bool bool_move;
	switch(move)
	{
		case 1: {bool_move=(board[2][0] == '1'? true : false); break;}
		case 2: {bool_move=(board[2][1] == '2'? true : false); break;}  
		case 3: {bool_move=(board[2][2] == '3'? true : false); break;} 
		case 4: {bool_move=(board[1][0] == '4'? true : false); break;} 
		case 5: {bool_move=(board[1][1] == '5'? true : false); break;} 
		case 6: {bool_move=(board[1][2] == '6'? true : false); break;} 
		case 7: {bool_move=(board[0][0] == '7'? true : false); break;}
		case 8: {bool_move=(board[0][1] == '8'? true : false); break;} 
		case 9: {bool_move=(board[0][2] == '9'? true : false); break;}
		default: {	cout<<"invalid input. "; break;} 
	}
		return bool_move;
}
//set the board array to the original numbers
void Board::set_board()
{
	char brd[3][3] = {{'7','8','9'},{'4','5','6'},{'1','2','3'}};
	for (int row=0; row<3; row++)
	{
		for(int col=0; col<3; col++)
		{board[row][col] = brd[row][col];}
	}
}
//place the cursor for screen output
void place_cursor(HANDLE, int row, int col)
{
	COORD position; //holds the coordinates
	position.Y = row; position.X = col;
	SetConsoleCursorPosition(hConsole, position);
}
//get an integer and handle bad input
int get_int(string prompt,string badch_errmsg,string range_errmsg, int lo, int hi) 
{
	while (true) 
	{
		int user_int_input=0;
	    place_cursor(hConsole, 9, 0); cout<<prompt<<"("<<lo<<"-"<<hi<<"): ";
	    if (cin>>user_int_input) 
		{
	    	if (user_int_input>=lo and user_int_input<=hi)
	        	return user_int_input;
	      else
	        {	
				place_cursor(hConsole, 11, 0);cout<<range_errmsg; //move to the  line below string prompt
				Sleep(1000); place_cursor(hConsole, 11, 0); cout<<"\t\t\t\t\t\t\t"; //clear out error message
			}
	    } 
		else 
		{
	    	place_cursor(hConsole, 11, 0);cout<<badch_errmsg; // move to the line below string prompt
			Sleep(1000); place_cursor(hConsole, 11, 0); cout<<"\t\t\t\t\t\t\t"; //clear out error message
	    	cin.clear(); cin.ignore(1024, '\n');
	    }
	}
}

/*


          let's play toc_tac_toe!
                 7 | 8 | 9
                ___________
                 4 | 5 | 6
                ___________
                 1 | 2 | 3


where would you like to play on the board?(1-9):



          let's play toc_tac_toe!
                 x | 8 | 9
                ___________
                 o | x | o              x won! x won! x won!
                ___________
                 x | o | x

would you like to play again? 0 to quit 1 to continue. (0-1):1

//clears screen



          let's play toc_tac_toe!
                 7 | 8 | o
                ___________
                 x | x | o              o won! o won! o won!
                ___________
                 o | x | o

would you like to play again? 0 to quit 1 to continue. (0-1):

//clears screen


          let's play toc_tac_toe!
                 x | x | o
                ___________
                 o | o | x              it's a cat's game!
                ___________
                 x | o | x

would you like to play again? 0 to quit 1 to continue. (0-1):

you played 3 games.
x won 33.3333 %.
o won 33.3333 %.
33.3333 % were cat's games.

--------------------------------
Process exited after 163.7 seconds with return value 0
Press any key to continue . . .
*/
