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
                
                // std::vector<std::vector<int>> bot_move = best_move(board, turn);

                // char piece = board[bot_move[0][0]][bot_move[0][1]];
                // board[bot_move[0][0]][bot_move[0][1]] = '0';
                // board[bot_move[1][0]][bot_move[1][1]] = piece;
                
                // std::cout << bot_move[0][0] << ", " << bot_move[0][1] << " :: " << bot_move[1][0] << ", " << bot_move[1][1] << "\n";
                // std::cin;

                turn = white;

                std::vector<std::vector<int>> move = bot_move(board, true, 4);

                std::vector<int> move1 = move[0];
                std::vector<int> move2 = move[1];

                char piece = board[move1[0]][move1[1]];
                board[move1[0]][move1[1]] = '0';
                board[move2[0]][move2[1]] = piece;

                // int a;
                // std::cout << "\nmove done: ";
                // std::cin >> a;
                // message = "white to move\n     black moved " + std::to_string(bot_move[0][0]) + ", " + std::to_string(bot_move[1][1]) + " to " + std::to_string(bot_move[0][0]) + ", " + std::to_string(bot_move[1][1]);
                // message = "black to move\n     white moved " + move;
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
    // init_board(board, "6k1/5p2/6p1/8/7p/8/6PP/6K1/");

    print_board(board);

    mainloop();
}