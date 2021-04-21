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
        
        if (result == true) {
            if (turn == white) {
                turn = black;
                message = "black to move\n     white moved " + move;
            } else {
                turn = white;
                message = "white to move\n     black moved " + move;
            }
        } else {
            message = turn + " to move\n     INVALID MOVE: " + move;
        }

        system("cls");
        std::cout << "\n     " << message;
        std::cout << "\n\n";
        print_board(board);
    }
}

int main() {
    std::cout << "Welcome to Console Chess!\n";

    // std::cout << (char)0xDB;
    // std::cout << (char)0xFF;

    init_board(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/");
    // init_board(board, "4k3/pppppppp/8/8/8/8/8/8/");
    print_board(board);

    mainloop();
}