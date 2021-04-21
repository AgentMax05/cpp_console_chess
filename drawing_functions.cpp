#include <string>
#include <vector>
#include <iostream>
#include <cmath>

const char white_square = (char)0xDB;
const char black_square = (char)0xFF;
const char upper_dash = (char)196;
const char vertical_dash = (char)179;

std::string full_square_w = std::to_string(white_square) + std::to_string(white_square) + std::to_string(white_square) + std::to_string(white_square) + std::to_string(white_square) + std::to_string(white_square);
std::string full_square_b = std::to_string(black_square) + std::to_string(black_square) + std::to_string(black_square) + std::to_string(black_square) + std::to_string(black_square) + std::to_string(black_square);

void print_line(std::string side) {
    std::cout << "     " << vertical_dash;
    if (side == "white") {
        for (int i = 0; i < 48; i++) {
            if (int(std::trunc(i / 6)) % 2 == 0) {
                std::cout << white_square;
            } else {
                std::cout << black_square;
            }
        }
    }

    else {
        for (int i = 0; i < 48; i++) {
            if (int(std::trunc(i / 6)) % 2 == 0) {
                std::cout << black_square;
            } else {
                std::cout << white_square;
            }
        }
    }

    std::cout << "\n";

}

void draw_text_line(int row, std::vector<std::vector<char>> board) {
    std::cout << "  " << 8 - row << "  " << vertical_dash;
    for (int i = 0; i < board[row].size(); i++) {
        if (board[row][i] == '0') {
            if ((row + i) % 2 == 0) {
                std::cout << white_square << white_square << white_square << white_square << white_square << white_square;
            } else {
                std::cout << black_square << black_square << black_square << black_square << black_square << black_square;
            }
            continue;
        }

        if ((row + i) % 2 == 0) {
            std::cout << white_square << white_square << white_square << board[row][i] << white_square << white_square;
        } else {
            std::cout << black_square << black_square << black_square << board[row][i] << black_square << black_square;
        }
    }

}

int char_to_int(char input) {
    int result = input - 48;
    return result;
}

void init_board(std::vector<std::vector<char>> &board, std::string fen_notation) {
    std::cout << "Setting up board for: " << fen_notation << " position.\n";

    board = {
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    };

    std::vector<std::string> fen = {};

    std::string current_string = "";

    for (int i = 0; i < fen_notation.size(); i++) {
        if (fen_notation[i] == '/') {
            fen.push_back(current_string);
            current_string = "";
            continue;
        }
        current_string += fen_notation[i];
    }


    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < fen[row].size(); column++) {

            int result = char_to_int(fen[row][column]);


            if (0 <= result && result <= 8) {
                for (int i = 0; i < result; i++) {
                    board[row].push_back('0');
                }
                continue;
            }
    
            board[row].push_back(fen[row][column]);

        }
    }

}


void print_board(std::vector<std::vector<char>> board) {
    for (int row = 0; row < board.size(); row++) {
        if ((row) % 2 == 0) {
            print_line("white");

            draw_text_line(row, board);

            std::cout << "\n";
            print_line("white");
        }

        else {
            print_line("black");

            draw_text_line(row, board);

            std::cout << "\n";
            print_line("black");
        }

    }
    std::cout << "     " << (char)192;
    for (int i = 0; i < 48; i++) {
        std::cout << upper_dash;
    }

    std::cout << "\n     " << "   A      B     C     D     E     F     G     H\n";

}

