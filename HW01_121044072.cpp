//////////////////////////////////////////////////////////////////////
// 						CSE241 Object Oriented Programming 			//
// Autor:İbrahim ÇETİNKAYA  			Date: Due Date>> October 4	//
// Student Number:121044072 								2014    //
//				HW01_121044072                                      //
//                                                                  //
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define SIZE 200
using namespace std;

//This function that print Menu function by the console 
void printMenuFunction();
//This function that return choice of game for run step to step 
int choiceGameSection();

//This function that get the board of game from file.It finds width of board and height of board 
void getCellsFromFile( int gameBoard[SIZE][SIZE],char* filename, int* width, int* height);

//This function that print the board of game by the console
void printGameBoard(int gameBoard[SIZE][SIZE],int *width,int *height);

//This function that create live cells and dead cells.
void createLiveDead(int gameBoard[SIZE][SIZE],int liveDead[SIZE][SIZE],int *width,int *height);

//This function that a live cell find a living cells for overcrowding or loneliness
int findLiveCellNeighbourNumber(int liveDead[SIZE][SIZE],int x,int y,int *width,int *height);

//This function that a dead cell find a living cells for birth cell
int findLiveNeighbourNumOfBirthDeadCells(int liveDead[SIZE][SIZE] ,int x,int y,int* width, int* height);

//This function that check a live cell become a dead cell and a dead cell become a live cell
void checkRules(int gameBoard[SIZE][SIZE],int liveDead[SIZE][SIZE],int *width,int *height );

//This function that save board of game in output file
void saveGameFile(int gameBoard[SIZE][SIZE],int *width,int *height);

//This function that search a live cell or a dead cell ,return True or False 
bool search(int liveDead[SIZE][SIZE] ,int controlXY,int *width,int *height );

int main(int argc, char const *argv[])
{
	int gameBoard[SIZE][SIZE];
	int liveDead[SIZE][SIZE];
	int width = 0;
	int height = 0;
	char filename[SIZE] ;
	int stepCounter;
	int choice;
	int status;
	char temp ;
	char check;
	
	printMenuFunction();
	cout << "Please enter the name of initial file"<<endl;
	cin >> filename;
	getCellsFromFile(gameBoard,filename,&width,&height);

	createLiveDead(gameBoard,liveDead,&width,&height);

	printGameBoard(gameBoard,&width,&height);

	choice = choiceGameSection();
	if (choice == 1){
		
		cout<< "Please enter the number of game step  "<< endl;
		cin>> stepCounter;
		for(int i=0; i< stepCounter;i++){
		checkRules(gameBoard,liveDead,&width,&height );
		createLiveDead(liveDead,gameBoard,&width,&height);
		printGameBoard(gameBoard,&width,&height);
		}
		cout <<" Click  Yes(Y) or No(N) to save Game : ";
		cin >> check;
		printf("check %c\n", check);
		if (check == 'Y')
			saveGameFile(gameBoard,&width,&height);	

	}else if(choice == 2){
		temp =getchar();
		cout << "Please click to enter: ";
		status = getchar();
		if ( 10 == status)
		{
			checkRules(gameBoard,liveDead,&width,&height );
			createLiveDead(liveDead,gameBoard,&width,&height);
			printGameBoard(gameBoard,&width,&height);
			cout <<" Click  Yes(Y) or No(N) to save Game : ";
			cin >> check;
			if (check == 'Y')
				saveGameFile(gameBoard,&width,&height);
		}
		else
			cout<< "Please try again";
	}
	return 0;
}
void getCellsFromFile(int gameBoard[SIZE][SIZE], char* filename, int* width, int* height){
	FILE* inp;
	int c;
	int num1,num2;
	int number;
	int numberoflive = 0;
	inp = fopen(filename, "r");
	
	if(inp == NULL){
		cout << "file not found" << endl;
		exit(1);
	}
	fscanf(inp,"%d%d",&num1,&num2);
	
	for (int i = 0; i < num1 ; ++i)
	{
		for (int j = 0; j < num2 ; ++j)
		{
			fscanf(inp,"%d",&gameBoard[i][j]);
		}
	}
	*width = num1;
	*height = num2;
	fclose(inp);

}
void printGameBoard(int gameBoard[SIZE][SIZE],int *width,int *height){

	for (int i = 0; i < (*height); ++i)
	{
		for (int j = 0; j < (*width); ++j)
		{
			if (gameBoard[i][j] == 1)
				cout<<"X";
			else
				cout<<" ";
		}
		cout<<endl;
	}
}
void createLiveDead(int gameBoard[SIZE][SIZE],int liveDead[SIZE][SIZE],int *width,int *height){
	for (int i = 0; i < (*height); ++i)
	{
		for (int j = 0; j < (*width); ++j)
		{
			liveDead[i][j] = gameBoard[i][j];
		}
	}
}
void checkRules(int gameBoard[SIZE][SIZE],int liveDead[SIZE][SIZE],int *width,int *height ){
	int numLiveNeighbour;
	for (int i = 0; i < (*height); ++i)
	{
		for (int j = 0; j < (*width); ++j)
		{
			if ( liveDead[i][j] == 1){	
				numLiveNeighbour = findLiveCellNeighbourNumber(gameBoard,i,j,width,height);
				if (2 == numLiveNeighbour || 3 == numLiveNeighbour)
				{
					continue;
				}
				else if (2 > numLiveNeighbour || 3 < numLiveNeighbour)
				{
					liveDead[i][j] = 0 ;
				}
			}
			else if (liveDead[i][j] == 0){
				numLiveNeighbour = findLiveNeighbourNumOfBirthDeadCells(gameBoard,i,j,width,height);
				if (3 == numLiveNeighbour)
				{
					liveDead[i][j] = 1;
				}
			}
			
		}
	}
}
bool search(int liveDead[SIZE][SIZE] ,int controlXY,int *width,int *height ){
	 
	for (int i = 0; i < *height ; ++i)
	{
		for (int j = 0; j < *width ; ++j)
		{
			if (controlXY == 1)
				return true;
			else
				return false;
		}
	}
}
int findLiveCellNeighbourNumber(int liveDead[SIZE][SIZE],int x,int y,int *width,int *height){
	bool exist;
	int numCellOfLiveNeigbour = 0;
	 if (x == 0 && y == 0){
	 	//The upper of left corner
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if (x == 0 && y == (*width) -1 )
	{
		//The down of left corner
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x+1][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if (x == (*height)-1 && y ==0)
	{
		//The upper of right corner
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if (x == (*width)-1 && y == (*height) -1 )
	{
		//The down of right corner
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if (x == (*width) -1 && 0< y < (*height) -1 )
	{
		//The upper of right corner Between the down of right corner
		//en sağ üst arası en sağ alt 
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if ( 0 < x < (*width) -1 &&  y == (*height) -1 )
	{
		//en sağ üst arası en sağ alt 
		// The down of the left corner between The down of the right corner 
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numCellOfLiveNeigbour += 1;
	}
	else if (x-1 >= 0 &&  ( y+1 < ( (*height)-1) ) && y-1 >= 0 &&   ( x+1 < (*width)-1 ) )
	{
		//First Neigbour(x-1,y-1)
		exist = search(liveDead,liveDead[x-1][y-1],width,height );

		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Second Neigbour(x,y-1)
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
			
		//Third Neihbour(x+1,y-1)
		exist = search(liveDead,liveDead[x+1][y-1],width,height );		
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Fourth Neighbour(x-1,y)
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Fifth Neighbour(x+1,y)
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Sixth Neighbour(x-1,y+1)
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Seventh Neihbour(x,y+1)
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
		//Eighth Neighbour (x+1,y+1)
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist){
			numCellOfLiveNeigbour += 1;
		}
	}
	
	return numCellOfLiveNeigbour;

}
int findLiveNeighbourNumOfBirthDeadCells(int liveDead[SIZE][SIZE] ,int x,int y,int* width, int* height){
	bool exist;
	int numLiveCellNeighOfDeadCell = 0;
	if ( x == 0 && y == 0 ){//The upper of the left corner
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if (  ( 0 < x < (*width) - 1 ) && y == 0 ){
		//The upper of the left corner  between The upper of the right corner 
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if ( x == 0 && y == ( (*width) -1 ) ){
		//The upper of the right corner 
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if (x == 0 && ( 0 < y < (*height) -1) ){
		//The upper of the right corner between  the down of the right corner
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if (x == 0 && y == (*height) -1 ){
		// the down of the left corner
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if ( 0 < x < (*width) -1  && y == (*height) -1  ){
		//the down of the right corner between the down of the left corner
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if (x == (*width) -1 && y == (*height) -1 )
	{
		//The down of right corner
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else if (x == (*width) -1 && 0 < y < (*height) -1 )
	{
		//The upper of right corner between The down of right corner
		exist = search(liveDead,liveDead[x-1][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist)
			numLiveCellNeighOfDeadCell += 1;
	}
	else{
		//The middle of Game Board
			//First Neighbour (x-1,y-1)
		exist = search(liveDead,liveDead[x-1][y-1],width,height );

		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
		//Second Neigbour(x,y-1)
		exist = search(liveDead,liveDead[x][y-1],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}	
		//Third Neihbour(x+1,y-1)
		exist = search(liveDead,liveDead[x+1][y-1],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
		//Fourth Neighbour(x-1,y)
		exist = search(liveDead,liveDead[x-1][y],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}

		//Fifth Neighbour(x+1,y)
		exist = search(liveDead,liveDead[x+1][y],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
		//Sixth Neighbour(x-1,y+1)
		exist = search(liveDead,liveDead[x-1][y+1],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
		//Seventh Neihbour(x,y+1)
		exist = search(liveDead,liveDead[x][y+1],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
		
		//Eighth Neighbour (x+1,y+1)
		exist = search(liveDead,liveDead[x+1][y+1],width,height );
		if (exist){
			numLiveCellNeighOfDeadCell += 1;
		}
	}	
	return numLiveCellNeighOfDeadCell;
}

void printMenuFunction(){
	cout << "\t\t-----WELCOME THE GAME OF LIFE-----" << endl;
	cout << "\t\t###########################################################" << endl;
	cout << "\t\t#     The Game Rules =>                                   #" << endl;
	cout << "\t\t#---------------------------------------------------------#" << endl;
	cout << "\t\t# 1-> If a dead cell have  three live cell neighbour,a    #" << endl;
	cout << "\t\t#  dead cell become(birth) a live cell                    #" << endl;
	cout << "\t\t# 2-> If a live cell have two or three live cell neighbour#" << endl;
	cout << "\t\t# ,a live cell survival                                   #" << endl;
	cout << "\t\t# 3-> If a live cell has overcrowding or loneliness,a live#" << endl;
	cout << "\t\t#  cell dead                                              #" << endl;
	cout << "\t\t###########################################################" << endl;
}
int choiceGameSection(){
	int choice;
	do{
	cout << "\t\t###########################################################" << endl;
	cout << "\t\t#                  THE GAME CHOICE                        #" << endl;
	cout << "\t\t# ---  If The game run automatically,Please enter the  1  #" << endl;
	cout << "\t\t# ---  If The game run step to step ,Please enter the  2  #" << endl;
	cout << "\t\t###########################################################" << endl;
	cout << "\t\tPlease enter the choice of game  "<< endl;
	cin >> choice ;

	}while(choice  != 1 && choice != 2);
	return choice;
}
void saveGameFile(int gameBoard[SIZE][SIZE],int *width,int *height){
	FILE *outp;
	char saveFileName[SIZE];
	cout << "If The game board save file,Please enter the name of File: "<<endl;
	cin >> saveFileName;
	outp = fopen(saveFileName,"w"); 
	for (int i = 0; i < *height; ++i)
	{
		for (int j = 0; j < *width; ++j)
		{
			if (gameBoard[i][j] == 1)
				fprintf(outp,"X");
			else
				fprintf(outp," ");
		}
		fprintf(outp,"\n");
	}
	fclose(outp);
}
