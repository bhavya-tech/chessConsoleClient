#include <iostream>
#include"chessengine.h"
#include <fstream>
int turn; // 0 white 1 black
char m[9][9] = { ' ' };

MATRIX chessBoard;
static chessEngine ce;

using namespace std;

void update_m()
{
    char hashedPieces[] = {'k','q','b','h','r','p','K','Q','B','H','R','P',' '};
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            m[i][j] = hashedPieces[chessBoard.m[i][j]];
}

void switchbg(char* bg)
{
    if (*bg == ' ')
        *bg = 178;
    else
        *bg = ' ';
}

void printBoard()
{
    char bg = 178;
    update_m();
    system("CLS");
    //printf("Capital case for WHITE and small case for BLACK\n   ");
    printf("                                     ");
    for (int i = 1; i <= 8; i++)
        printf("   %d   ", i);
    printf("\n   ");
    printf("                               ");

    for (int j = 1; j <= 8; j++)
    {
        printf("\n      ");
        printf("                               ");

        for (int i = 1; i <= 8; i++)
        {
            for (int j = 0; j < 7; j++)
                printf("%c", bg);
            switchbg(&bg);
        }
            
        printf("\n   ");
        printf("                               ");

        printf("%d  ", j);

        for (int i = 1; i <= 8; i++)
        {
            char ch = m[i][j];
            if (m[i][j] == ' ')
                ch = bg;

            printf("%c%c%c%c%c%c%c", bg, bg, bg, ch, bg, bg, bg);
            switchbg(&bg);
        }

        printf("\n      ");
        printf("                               ");

        for (int i = 1; i <= 8; i++)
        {
            for (int j = 0; j < 7; j++)
                printf("%c", bg);
            switchbg(&bg);
        }
        switchbg(&bg);
    }
    printf("\n");
}

void saveGame()
{
    ofstream gamedata("chess.txt");
    ce.saveGame(&gamedata);
    cout << "Game successfully saved";
    gamedata.close();
}

COORD input(int sourceInput)
{
    printf("\n\n                               ");

    if (sourceInput)
        cout << "Enter source coordinates:";
    else
        cout << "Enter destination coordinates:";

    printf("\n                               ");

    COORD coord;
    char x, y;
    cin >> x >> y;

    if (x >= '1' && x <= '8')
    {
        coord.x = x - '0';
        coord.y = y - '0';
    }
    else
    {
        switch (x)
        {
        case 's':
            saveGame();

        default:
            cout << "Enter give proper input";
            return input(sourceInput);
        }
        return input(sourceInput);
    }
    return coord;
}

void notif(int status)
{
    printf("\n                               ");

    switch (status)
    {
    case NO_PIECE:
        cout << "No piece at the source\n";
        break;
    case ME_DESTOUTOFBOARD:
        cout << "Destination coords out of board\n";
        break;
    case ME_SAMECOORDS:
        cout << "Source and dest coords same\n";
        break;
    case ME_INVALIDMOVE:
        cout << "Invalid Move\n";
        break;
    case ME_BLOCKEDMOVE:
        cout << "Blocked move";
        break;
    case ME_SELFCHECK:
        cout << "Selfcheck";
        break;
    case ME_SELFCHECKMATE:
        cout << "Self checkmate";
        break;
    case ME_SELFSTALEMATE:
        cout << "Self stalemate";
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

    printf("\n                               ");

    if(ce.getTurn())
        cout << "Turn: Black";
    else
        cout << "Turn: White";
}

int main()
{
    GAME game;
    ifstream gamedata ("chess.txt");
    int init = ce.gameSetup(&gamedata, &chessBoard);
    gamedata.close();
    printBoard();
    notif(0);
    int status = 0;
    turn = ce.getTurn();
    while (1)
    {
        COORD source = input(1);
        COORD dest = input(0);
        status = ce.makeMove(source, dest, &chessBoard, NULL);
        
        printBoard();  
        notif(status);
    }
}

