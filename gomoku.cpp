#include <bits/stdc++.h>
using namespace std;

const int N = 15;
const int M = 15;
const int a_row = 5;
const int n_players = 2;
char marks[n_players] = {'X', 'O'};
char grid[N][M];
const int win_N = 5;

//This function prints the grid of Gomoku as the game progresses
void print_grid() {
	for (int i = 0; i< n_players; i++) {
        cout << "Player " << i+1 << ": " << marks[i] << "  ";
        if (i < n_players-1)
            cout << "vs  ";
	}
	cout << "\n";
	cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < M; cout << "---", i++);
        cout << "--\n";
    }
}
//This function checks if the game has a win state or not
bool check_win() {
    //rows
    int counter = -2;
    for(int i=0;i<N;i++){
        for(int j=0;j<M-1;j++){
            if(grid[i][j] == grid[i][j+1] && grid[i][j] != '.'){
                counter++;
                if(counter == win_N ){
                    return true;
                }
            }
        }
    }

    //columns
    counter = -2;
    for(int i=0;i<N;i++){
        for(int j=0;j<M-1;j++){
            if(grid[j][i] == grid[j+1][i] && grid[j][i] != '.'){
                counter++;
                if(counter == win_N ){
                    return true;
                }
            }
        }
    }

    // Diagonals

    //----\\\\-----
    counter = 1;
    for(int i=0;i<N;i++){
        for(int j=0;j<M-1;j++){
            if(i==j && grid[i][j] == grid[i+1][j+1] && grid[i][j] != '.'){
                counter++;
                if(counter == win_N ){
                    return true;
                }
            }
        }
    }


    //----////------
    counter = 1;
    for(int i=0;i<N-1;i++){
        if(grid[i][(N-1)-i] == grid[i+1][(N-1)-(i+1)] && grid[i][(N-1)-i] != '.'){
            counter++;
            if(counter == win_N ){
                return true;
            }
        }
    }

    return false;

}
//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {
    //----rows------
    int counter = 0;
    for(int i= 0;i<N;i++){
        for (int j = 0;j<M-4;j++){
            for (int x = 0 ; x < win_N;x++){
              if(grid[i][j] == '.' || grid[i][j] == mark && grid[i][j+x] == mark || grid[i][j+x] == '.'){
                counter ++;
            }

         }
        }
        if (counter >= win_N)
            return false;
    }
    //----columns-------
    counter = 0;
    for(int i= 0;i<N;i++){
        for (int j = 0;j<M-4;j++){
            for(int x = 0;x<win_N;x++){
                if (grid[j][i] == '.' || grid[j][i] == mark && grid[j+x][i] == mark || grid[j+x][i] == '.')
                    counter++;
            }

        }
        if (counter >= win_N)
            return false;
    }
    //---diagonals------
    //----\\\-----
    counter = 0;
    for(int i= 0;i<N;i++){
        for (int j = 0;j<M-4;j++){
            if (i == j){
                for(int x = 0; x<win_N;x++){
                if(grid[i][j] == '.' || grid[i][j] == mark && grid[i+x][j+x] == mark || grid[i+x][j+x] == '.')
                    counter++;

                }
            }
        }
        if (counter >= win_N)
            return false;
    }
    //----///-----
    counter = 0;
    for (int i=0;i<N-1;i++){
        for(int x = 0; x<win_N;x++){
            if (grid[i][(N-1)-i] == mark || grid[i][(N-1)-i] == '.' && grid[i+x][(N-1)-(i+x)] == mark || grid[i+x][(N-1)-(i+x)] == '.')
                counter++;
        }
        if (counter>=win_N)
            return false;
    }

    return true;
}
//This function checks if the game has a tie state or not
bool check_tie() {
    bool all_tie = true;
    for (int i = 0; i < n_players; i++)
        if (!check_tie_player(marks[i]))
            all_tie = false;
    return all_tie;
}
//This function checks if given cell is empty or not
bool check_empty(int i, int j) {

    if(grid[i][j] == '.')
    {
        return true;
    }
    else{
        return false;
    }

}
//This function checks if given position is valid or not
bool check_valid_position(int i, int j) {

    if(-1 < i && i < N && -1 < j && j < M)
    {
        return true;
    }else
    {
        return false;
    }

}
//This function sets the given mark to the given column
void set_cell(int i, int j, char mark) {
    grid[i][j] = mark;
}
//This function clears the game structures
void grid_clear() {
    for(int i = 0; i< N;i++){
        for(int j = 0; j<M;j++){
            grid[i][j] = '.';
        }
    }
}
//This function reads a valid position input
void read_input(int &i, int &j) {
    cout << "Enter the row index and column index: ";
    cin >> i >> j;
    while (!check_valid_position(i, j) || !check_empty(i, j)) {
        cout << "Enter a valid row index and a valid column index: ";
        cin >> i >> j;
    }
}
//MAIN FUNCTION
void play_game() {
    cout << "Gomoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i, j;
		read_input(i, j);
        //Set the input position with the mark
        set_cell(i, j, marks[player]);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
        }
        //Check if the state of the grid has a tie state
        if (check_tie()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = (player + 1) % n_players;
    }
}
int main() {
    while (true) {
    	grid_clear();
    	play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
