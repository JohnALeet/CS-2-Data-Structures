#include "gameOfLife.h"

/*
Function to clear terminal depending on OS
*/
void clearScreen()
{
    // use "cls" in windows and "clear" command in Mac and Linux
    #ifdef _WIN32
        system("clS");
    #else
        system("clear");
    #endif
}

/*
Function to initialize all cells in the board.
Takes in 2D array of pointers and size of array
Should create structs and populate the array
*/
void initCells(Cell* board[][10], int boardSize)
{
    for (int row = 0; row < boardSize; row++){

        for (int i = 0; i < boardSize; i++)
        {
            board[row][i] = new Cell;
            board[row][i]->x = i;
            board[row][i]->y = row;

        }
}


}

/*
Function to read the board from a file
Prompt for the file to read inside of the function
Structure of file should consist of 10 lines of 0 or 1 to indicate cell state
*/
void readBoard(Cell* board[][10], int boardSize) 
{
    string myFiles[3] = {"Board0.txt", "Board1.txt", "Board2.txt"};
    int fileNum;
    string inputline;
    cout << "Enter the num of the file you'd like to read: 0) Board0.txt, 1) Board1.txt, 2) Board2.txt " <<endl;
    cin >> fileNum;
    if (fileNum < 0 || fileNum > 2) // 0 =< fileNum =< 2
    {
        cerr << "YOU LOSE! YOU GET NOTHING! GOOD DAY, CERR!" << endl;
        return;
    }

    ifstream fin;
    fin.open(myFiles[fileNum]);

    int row = 0;
    while (getline(fin, inputline)&& row < boardSize) // Open the file, store each line in inputLine.
    {
        for (int i = 0; i < boardSize; i++)//Loop through each character in that row
        {
            char ch = inputline[i];

            if (ch  == '1'|| ch == '0')
            {
                int j;
                    if (ch == '1') j =1;
                else j = 0;

                    board[row][i]->state = j;

            }



        }
        row++;
    }



}

/*
Function to print out all cells to cout
*/
void printCells(Cell* board[][10], int boardSize)
{
    for (int row =0; row < boardSize; row++)
    {
        for( int i = 0; i < boardSize; i++)
        {
            cout << board[row][i]->state;

        }
        cout << endl;

    }
}

/*
Function to count the number of live neighbors for each cell.
Must use the x, y position stored with each cell to determine which neighbors they have
*/
void findNumNeighbors(Cell* board[][10], int boardSize, Cell* curCell)
{
    int x = curCell->x;
    int y = curCell->y;
    int numNeighbors = 0;

    for (int nrow = y - 1; nrow <= y + 1; nrow++)
    {
        for (int ni = x - 1; ni <= x + 1; ni++)
        {
            if (!(ni == x && nrow == y))
            {
                if (ni >= 0 && ni < boardSize && nrow >= 0 && nrow < boardSize)
                {
                    if (board[nrow][ni]->state == 1)
                    {
                        numNeighbors++;
                    }
                }
            }
        }
    }

    curCell->numLiveNeighbors = numNeighbors;
}

/*
Function to update each cell's state based on number of neighbors
Must use following rules:

Any live cell with fewer than two live neighbors dies, as if by underpopulation.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Return if you updated cells or not to break out of while loop from main.
*/
bool updateCellState(Cell* board[][10], int boardSize) 
{
    // for ( int row = 0 ; row < boardSize; row++ ){
    //     for ()

    /*If state >  1, die if state <2 die, return something when true, we  */

    // }
    //Fill with funny logic that does stuff

    return false;
}