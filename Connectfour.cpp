#include <iostream>
using namespace std;

bool hasWin(char board[][7], char c)
{
// diagonals
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((board [i][j] == '-'))
                continue;
            if( ( i+3 < 6) && ( j+3 < 7))
            {
                if ((board [i][j] == board[i+1][j+1]) && (board[i+1][j+1] == board[i+2][j+2])
                        && (board [i+2][j+2] == board[i+3][j+3])&& (board[i+3][j+3] == c))
                    return true;
            }
            if( ( i-3 > -1) && ( j+3 < 7))
            {
                if ((board [i][j] == board[i-1][j+1]) && (board[i-1][j+1] == board[i-2][j+2])
                        && (board [i-2][j+2] == board[i-3][j+3])&& (board[i-3][j+3] == c))
                    return true;
            }
        }
    }

// horizontal
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((board [i][j] == '-'))
                continue;
            if ((board [i][j] == board[i][j+1]) && (board[i][j+1] == board[i][j+2])
                    && (board [i][j+2] == board[i][j+3])&& (board[i][j+3] == c))
                return true;
        }
    }

// vertical
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((board [i][j] == '-'))
                continue;
            if ((board [i][j] == board[i+1][j]) && (board[i+1][j] == board[i+2][j])
                    && (board [i+2][j] == board[i+3][j])&& (board[i][j] == c))
                return true;
        }
    }

    return false;
}

bool availPlaces(char board[][7])
{
    for (int i = 0;  i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
            if (board[i][j] == '-')
                return true;
    }
}

void printBoard(char board[][7])
{
    cout << " 1 2 3 4 5 6 7" << endl;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }
    cout << "---------------" << endl;

}

int getRow(char board[][7], int c)
{
    for(int i = 5; i >=0 ; i--)
        if(board[i][c] == '-')
            return i;
    return -1;
}

int scores(char board[][7],int depth, int a, int b, bool comp )
{
    if (b<=a)
    {
        return (comp?1000:-1000);
    }
    if(hasWin(board, 'O'))
        return 100-depth;
    if(hasWin(board, 'X'))
        return depth-100;
    if(!availPlaces(board))
        return 0;
    if(depth == 8)
        return 0;
    int bestScore, score;
    bestScore = (comp?-1000:1000);
    for(int j = 0; j < 7; j++)
    {
        int i = getRow(board, j);
        if(i != -1)
        {
            if(comp)
            {
                board[i][j] = 'O';
                score = scores(board,depth+1,a,b, false);
                bestScore = max(bestScore,score);
                a = max(score,a);
                board[i][j] = '-';
            }
            else
            {
                board[i][j] = 'X';
                score = scores(board,depth+1,a,b, true);
                bestScore = min(bestScore,score);
                b = min (score,b);
                board[i][j] = '-';
            }
        }
    }
    return bestScore;
}

int checkScore(int places[7])
{
    int bestScore = -10000;
    int j;
    places[0]+=3;
    places[1]+=2;
    places[2]+=1;
    places[3]+=5;
    places[4]+=1;
    places[5]+=2;
    places[6]+=3;
    for(int i = 0; i < 7; i++)
    {
        if(places[i] > bestScore)
        {
            bestScore = places[i];
            j = i;
        }
    }
    return j;
}

bool place(char board[][7], int col, char player)
{
    if(col < 0 || col >6)
        return false;
    int i = getRow(board, col);
    if (i == -1)
        return false;
    else
        board[i][col] = player;
        return true;
}

void compMove(char board[][7])
{
    int score;
    int places[7];
    for(int j = 0; j < 7; j++)
    {
        int i = getRow(board, j);
        if(i != -1)
        {
            board[i][j] = 'O';
            score = scores(board,0,-1000,1000, false);
            board[i][j] = '-';
            places[j] = score;
        }
        else
        {
            places[j] = -1000;
        }
    }
    int k = checkScore(places);
    place(board, k, 'O');
    printBoard(board);
}

void playerMove(char board[][7], char player)
{
    int c;
    bool placed = false;
    cout << player << " turn:\n";
    cout << "Please choose column: ";
    cin >> c;
    c--;
    while(!place(board,c,player))
    {
        cout << "Invalid column! Please choose another column: " << endl;
        cin >> c;
        c--;
    }
    printBoard(board);
}

void play(char board[][7], bool comp)
{
    int depth = 0;
    printBoard(board);
    while (availPlaces(board))
    {
        playerMove(board,'X');
        if(hasWin(board,'X'))
        {
            cout << "X wins!" << endl;
            return;
        }
        if(comp && availPlaces(board))
        {
            compMove(board);
        }
        else if (availPlaces(board))
        {
            playerMove(board,'O');
        }
        if(hasWin(board,'O'))
        {
            cout << "O wins!" << endl;
            return;
        }
        if(!availPlaces(board))
        {
            cout << "Tie!" << endl;
        }
    }
}

void initialize(char board[][7])
{
    for (int i = 0;  i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            board[i][j] = '-';
        }
    }
}

int main(int argc, char *argv[])
{
    char board [6][7];
    int ans;
    bool computer = false;
    cout << "How many players? (1/2) ";
    cin >> ans;
    if (ans == 2)
    {
        computer = false;
    }
    else
    {
        computer = true;
    }
    initialize(board);
    play(board, computer);
    return 0;
}
