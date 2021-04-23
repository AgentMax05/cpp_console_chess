#include <iostream>
#include <vector>
#include <string>
#include <map>

bool is_lowercase(char input);
char to_lowercase(char input);

double stacked_pawn = -1.2;
double king_check = 10.0;

extern std::map<char, int> piece_values;
// std::map<char, int> piece_values = {{'p', 1}, {'b', 3}, {'n', 3}, {'r', 5}, {'q', 5}};

int material_value(std::vector<std::vector<char>> board, bool isLowercase) {
    int material_value = 0;
    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (is_lowercase(piece) == isLowercase) {
                material_value += piece_values[to_lowercase(piece)];
            }
        }
    }
    return material_value;
}


double stacked_pawns(std::vector<std::vector<char>> board, bool isLowercase) {
    int direction;
    double counter = 0.0;

    if (isLowercase == true) {
        direction = -1;
    } else {
        direction = 1;
    }

    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char current_piece = board[row][column];
            if (is_lowercase(current_piece) == isLowercase && to_lowercase(current_piece) == 'p') {
                if (is_lowercase(board[row + direction][column]) == isLowercase && to_lowercase(board[row + direction][column]) == 'p') {
                    counter += stacked_pawn;
                }
            }
        }
    }

    return counter;

}


std::vector<double> value_moves(std::vector<std::vector<char>> board, std::vector<std::vector<std::vector<int>>> possible_moves, bool isLowercase, int depth) {
    
    std::vector<double> move_values(possible_moves.size());

    for (int x = 0; x < possible_moves.size(); x++) {

        std::vector<int> current_from = possible_moves[x][0];
        std::vector<int> current_to = possible_moves[x][1];

        double move_value = 0.0;

        char current_piece = board[current_from[0]][current_from[1]];
        char previous_piece = board[current_to[0]][current_to[1]];
        board[current_from[0]][current_from[1]] = '0';
        board[current_to[0]][current_to[1]] = current_piece;


        // evaluate material value:
        double material = material_value(board, isLowercase);
        
        // evaluate stacked pawn deduction:
        double stacked_deduction = stacked_pawns(board, isLowercase);

        move_value = material + stacked_deduction;

        move_values[x] = move_value;

        board[current_to[0]][current_to[1]] = previous_piece;
        board[current_from[0]][current_from[1]] = current_piece;
    }

    return move_values;

}