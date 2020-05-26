#include <iostream>
#include"chessengine.h"

int turn; // 0 white 1 black
char m[9][9] = { ' ' };

MATRIX chessBoard;

using namespace std;

void update_m()
{
    char hashedPieces[] = {'k','q','b','h','r','p','K','Q','B','H','R','P',' '};
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            m[i][j] = hashedPieces[chessBoard.m[i][j]];
}

void printBoard()
{
    update_m();
    system("CLS");
    printf("Capital case for WHITE and small case for BLACK\n   ");
    for (int i = 1; i <= 8; i++)
        printf("___%d__", i);
    printf("\n   ");
    for (int i = 1; i <= 8; i++)
        printf("______");
    for (int j = 1; j <= 8; j++)
    {
        printf("\n   ");
        for (int i = 1; i <= 8; i++)
            printf("|     ");

        printf("|\n");
        printf("%d--", j);

        for (int i = 1; i <= 8; i++)
            printf("|  %c  ", m[i][j]);

        printf("|\n   ");

        for (int i = 1; i <= 8; i++)
            printf("|_____");
        printf("|");
    }
}

COORD input(int sourceInput)
{
    if (sourceInput)
        cout << "\nEnter source coordinates:";
    else
        cout << "\nEnter destination coordinates:";

    COORD coord;
    cin >> coord.x >> coord.y;

    return coord;
}

bool notif(int status)
{
    bool maketurn = true;
    switch (status)
    {
    case NO_PIECE:
        cout << "No piece at the source\n";
        maketurn = false;
        break;
    case ME_DESTOUTOFBOARD:
        cout << "Destination coords out of board\n";
        maketurn = false;
        break;
    case ME_SAMECOORDS:
        cout << "Source and dest coords same\n";
        maketurn = false;
        break;
    case ME_INVALIDMOVE:
        cout << "Invalid Move\n";
        maketurn = false;
        break;
    case ME_BLOCKEDMOVE:
        cout << "Blocked move";
        maketurn = false;
        break;
    case ME_SELFCHECK:
        cout << "Selfcheck";
        maketurn = false;
        break;
    case ME_SELFCHECKMATE:
        cout << "Self checkmate";
        maketurn = false;
        break;
    case ME_SELFSTALEMATE:
        cout << "Self stalemate";
        maketurn = false;
        break;
    case CK_CHECK:
        cout << "King under check";
        break;
    case CK_CHECKMATE:
        cout << "King under checkmate you have one move to save";
        break;
    case CK_STALEMATE:
        cout << "King under stalemate you have one move to save";
        break;
    case MISC_INPUTPROMOTETO:
        cout << "Pawn to be promoted to:";
        break;
    case NOT_TURN:
        cout << "Not your turn";
        break;

    default:
        break;
    }

    if(turn)
        cout << "\nTurn: Black\n";
    else
        cout << "\nTurn: White\n";

    return maketurn;
}

int main()
{
    chessEngine ce;
    GAME game;
    
    int init = ce.gameSetup(1, game, &chessBoard);
    printBoard();
    int status = 0;
    bool maketurn = false;
    turn = ce.getTurn();
    while (1)
    {
        if (maketurn)
        {
            if (turn)
                turn = 0;
            else
                turn = 1;
        }

        COORD source = input(1);
        COORD dest = input(0);
        status = ce.makeMove(source, dest, &chessBoard, NULL);
        
        printBoard();     
        maketurn = notif(status);
    }
}

