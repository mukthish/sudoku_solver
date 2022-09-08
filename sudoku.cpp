#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

// FUNCTION TO CHECK THE VALIDITY OF THE BOARD
bool isValidSudoku(vector<vector<char>>& board) {
    int row[9][9] = {0}, col[9][9] = {0}, box[9][9] = {0};

    for (int i = 0; i < 9; i++) 
        for (int j = 0; j < 9; j++) 
            if (board[i][j] != '.') 
                if (row[i][board[i][j] - '1']++ or col[j][board[i][j] - '1']++ or box[(i/3) * 3 + j/3][board[i][j] - '1']++)
                    return false;

    return true;
}

// FUNCTION TO CHECK THE VALIDITY OF THE PERFORMED MOVE
bool check(vector<vector<char>> &board, int i, int j, char c) {
    int row = i - i%3, col = j - j%3;
    
    for (int x = 0; x < 9; x++)
        if (board[i][x] == c or board[x][j] == c) return false;
    
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++) 
            if (board[row + x][col + y] == c) return false;
    
    return true;
}

// FUNCTION TO SOLVE THE BOARD
bool solveSudoku(vector<vector<char>> &board, int i, int j) {
    // ROW OUT OF BOUND
    if (i == 9) 
        return true;

    // COLUMN OUT OF BOUND
    if (j == 9) 
        return solveSudoku(board, i + 1, 0);

    // NOT AN EMPTY SPACE
    if (board[i][j] != '.') 
        return solveSudoku(board, i, j + 1);
    
    // CHECK THE VALIDITY OF EACH NUMBER
    for(char c = '1'; c <='9'; c++) {
        if (check(board, i, j, c)) {
            // SELECT THE NUMBER 'c'
            board[i][j] = c;
            // CHECK VALIDITY FOR NEXT SPACE
            if (solveSudoku(board, i, j + 1)) 
                return true;
            // IF NOT VALID BACKTRACK
            board[i][j] = '.';
        }
    }
    
    return false;
}

void displaySudoku (const vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board(9, vector<char>(9, '.'));
    
    ifstream fin;
    fin.open("input.txt");

    // READING INPUT FROM A FILE
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fin >> board[i][j];
        }
    }

    cout << "\nThe Board read from input is:\n\n";
    displaySudoku(board);

    cout << "\nChecking to see if the board is valid:\n";
    if (!isValidSudoku(board)) {
        cout << "The board isn't valid.\n";
    }
    else {
        cout << "\nThe board is valid." << endl << "\nProceeding to solve the board." << endl;
        solveSudoku(board, 0, 0);
        cout << "\nThe board after solving is:\n\n";
        displaySudoku(board);
    }
    return 0;
}