#include <stdio.h>
#include <conio.h>

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return 1;
    }
    return 0;
}

int checkWinner() {
    for (int i = 0; i < 3; i++) {
        // Rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return current_player;

        // Columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return current_player;
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return current_player;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return current_player;

    return 0;
}

void swapPlayerAndMarker() {
    if (current_marker == 'X')
        current_marker = 'O';
    else
        current_marker = 'X';

    if (current_player == 1)
        current_player = 2;
    else
        current_player = 1;
}

void game() {
    printf("Player 1, choose your marker (X or O): ");
    scanf(" %c", &current_marker);
    current_player = 1;

    int player_won = 0;

    for (int i = 0; i < 9; i++) {
        drawBoard();

        int slot;
        printf("Player %d, enter your slot (1-9): ", current_player);
        scanf("%d", &slot);

        if (slot < 1 || slot > 9) {
            printf("Invalid slot! Try again.\n");
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            printf("Slot already taken! Try again.\n");
            i--;
            continue;
        }

        player_won = checkWinner();

        if (player_won == 1 || player_won == 2) {
            drawBoard();
            printf("🎉 Player %d wins! 🎉\n", player_won);
            return;
        }

        swapPlayerAndMarker();
    }

    drawBoard();
    printf("It's a draw! 🤝\n");
}

int main() {
    printf("===== TIC TAC TOE GAME =====\n");
    game();
    getch();
    return 0;
}