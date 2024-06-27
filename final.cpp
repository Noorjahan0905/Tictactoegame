#include <iostream>
using namespace std;
class Board {
protected:
    char board[3][3];
    char initial;
public:
    Board() : initial('1') {
        reset();
    }

    void reset() {
        int count = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '0' + count++;
            }}}

    void reset(char initialChar) {
        initial = initialChar;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = initial;
            }}}

    void display() {
        cout << "  Tic Tac Toe\n\n";
        cout << "PLAYER - 1 [X]  PLAYER - 2 [O]\n\n";
        for (int i = 0; i < 3; i++) {
            cout << "     |     |     \n";
            cout << "  " << board[i][0] << "  |  " << board[i][1] << "  |  " << board[i][2] << " \n";
            cout << "__|_|__\n";
        }
        cout << "     |     |     \n";
        cout << endl;
    }

    friend class Game;
};

class Game : public Board {
private:
    int choice;
    int row, column;
    char turn;
    bool draw;

public:
    Game() : turn('X'), draw(false) {}

    void player_turn() {
        if (turn == 'X') {
            cout << "Player - 1 [X] turn : ";
        } else {
            cout << "Player - 2 [O] turn : ";
        }
        cin >> choice;

        row = (choice - 1) / 3;
        column = (choice - 1) % 3;

        if (turn == 'X' && board[row][column] == initial) {
            board[row][column] = 'X';
            turn = 'O';
        } else if (turn == 'O' && board[row][column] == initial) {
            board[row][column] = 'O';
            turn = 'X';
        } else {
            cout << "Box already filled or invalid! Please choose another!\n";
            player_turn();
        }
    }

    bool gameover() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != initial)
                return false;
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != initial)
                return false;
        }
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != initial)
            return false;
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != initial)
            return false;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == initial)
                    return true;
            }
        }
        draw = true;
        return false;
    }

    void announce_result() {
        if (turn == 'X' && draw == false) {
            cout << "Congratulations! Player no. 2 [O] has won the game\n";
        } else if (turn == 'O' && draw == false) {
            cout << "Congratulations! Player no. 1 [X] has won the game\n";
        } else {
            cout << "GAME DRAW!!!\n";
        }
    }

    void reset_game() {
        turn = 'X';
        draw = false;
        reset();
    }

    void reset_game(char initial) {
        turn = 'X';
        draw = false;
        reset(initial);
    }
};

int main() {
    Game ticTacToe;
    char playAgain;
    char customReset;

    cout << "TIC TAC TOE GAME\n";
    cout << "FOR 2 PLAYERS\n\n";

    do {
        cout << "Do you want to reset the board with a custom character? (y/n): ";
        cin >> customReset;

        if (customReset == 'y' || customReset == 'Y') {
            char initialChar;
            cout << "Enter the character to reset the board with: ";
            cin >> initialChar;
            ticTacToe.reset_game(initialChar);
        } else {
            ticTacToe.reset_game();
        }

        while (ticTacToe.gameover()) {
            ticTacToe.display();
            ticTacToe.player_turn();
            ticTacToe.gameover();
        }

        ticTacToe.display();
        ticTacToe.announce_result();

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing Tic Tac Toe!\n";

    return 0;
}
