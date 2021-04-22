#include <iostream>
#include <string>
#include <vector>
#include <map>

bool check_legal(std::vector<std::vector<char>> board, char piece, std::vector<int> from, std::vector<int> to, std::string side);
bool is_lowercase(char input);
char to_lowercase(char input);

std::map<char, int> piece_values = {{'p', 1}, {'b', 3}, {'n', 3}, {'r', 5}, {'q', 5}};

std::vector<std::vector<int>> best_move(std::vector<std::vector<char>> board, std::string side) {
    
    bool isLowercase;
    if (side == "white") {
        isLowercase = false;
    } else {
        isLowercase = true;
    }

    std::vector<std::vector<std::vector<int>>> possible_moves = {};

    for (int piece_row = 0; piece_row < board.size(); piece_row++) {
        for (int piece_column = 0; piece_column < board[piece_column].size(); piece_column++) {
            char current_piece = board[piece_row][piece_column];
            if (current_piece == '0') {continue;}
            if (is_lowercase(current_piece) != isLowercase) {continue;}
            for (int board_row = 0; board_row < board.size(); board_row++) {
                for (int board_column = 0; board_column < board[board_row].size(); board_column++) {
                    if (check_legal(board, current_piece, {piece_row, piece_column}, {board_row, board_column}, side) == true) {
                        possible_moves.push_back({{piece_row, piece_column}, {board_row, board_column}});
                    }
                }
            }

        }
    }

    std::cout << possible_moves.size();

    std::vector<int> move_points(possible_moves.size());

    // possible_moves structure: { { {start_x, start_y}, {end_x, end_y} } }
    for (int i = 0; i < possible_moves.size(); i++) {

        int point_counter = 0;
        std::vector<std::vector<int>> current = possible_moves[i];

        std::cout << current[0][0] << ", " << current[0][1] << "::" << current[1][0] << ", " << current[1][1] << "\n";

        char previous_piece = board[current[1][0]][current[1][1]];
        char current_piece = board[current[1][0]][current[1][1]];
        board[current[0][0]][current[0][1]] = '0';
        board[current[1][0]][current[1][1]] = current_piece;

        // cycle through board:
        for (int row = 0; row < board.size(); row++) {
            for (int column = 0; column < board[row].size(); column++) {
                if (is_lowercase(board[row][column]) == isLowercase) {
                    point_counter += piece_values[to_lowercase(board[row][column])];
                }
            }
        }

        move_points[i] = point_counter;
    }

    for (int i = 0; i < move_points.size(); i++) {
        std::cout << move_points[i] << " ";
    }

    return possible_moves[0];
}