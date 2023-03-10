#include <iostream>
#include <string>
#include <vector>
#include "functions.hpp"

std::string white = "white";
std::string black = "black";
std::string turn = white;
std::string move;
std::string message;

std::vector<std::vector<char>> board = {
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};

bool running = true;

void mainloop() {
    while (running) {
        std::cout << "Enter move:\n";
        std::cin >> move;
        bool result = make_move(board, move, turn);
        bool isCheckmate = false;

        if (result == true) {
            // check if the other king is in checkmate
            isCheckmate = check_checkmate(board, turn == white);

            if (isCheckmate) {
                message = "checkmate\n     " + turn + " wins";
            } else if (turn == white) {
                message = "black to move\n     white moved " + move;
                turn = black;
            } else {
                turn = white;
                message = "white to move\n     black moved " + move;
            }
        } else if (result == false) {
            message = turn + " to move\n     INVALID MOVE: " + move;
        }

        system("cls");
        std::cout << "\n     " << message;
        std::cout << "\n\n";
        print_board(board);

        if (isCheckmate) {
            running = false;
        }
    }

    system("pause"); // wait for enter before closing
}

int main() {
    std::cout << "Welcome to Console Chess!\n";

    init_board(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/");

    print_board(board);

    mainloop();
}