#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// external function declarations:
bool is_lowercase(char input);
char to_lowercase(char input);
bool check_legal(std::vector<std::vector<char>> board, char piece, std::vector<int> from, std::vector<int> to, std::string side);
bool check_check(std::vector<std::vector<char>> board, char piece, int move1_row, int move1_column, int move2_row, int move2_column, std::string turn);
std::vector<int> king_location(std::vector<std::vector<char>> board, bool isLowerCase);

std::map<char, int> piece_values = {{'p', 1}, {'b', 3}, {'n', 3}, {'r', 5}, {'q', 9}};
std::vector<std::vector<int>> center_squares = {{3, 2}, {4, 2}, {3, 3}, {3, 4}, {4, 3}, {4, 4}, {3, 5}, {4, 5}};
std::map<std::string, double> transposition_table;

// setting move scoring for different variables:
double stacked_pawn = -0.5;
double king_check = 3;
double material_factor = 0.65;
double center = 1.0;

// white is a positive value while black is a negative value
// this tries to find an overall value for the board to see if
// black or white is favored

// convert board position to string:
std::string board_to_str(std::vector<std::vector<char>> board, bool lowercaseSide, int depth) {
    std::string board_str = "";
    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            board_str += board[row][column];
        }
    }
    board_str += std::to_string(lowercaseSide);
    board_str += std::to_string(depth);
    return board_str;
}

// find all possible moves for given side
std::vector<std::vector<std::vector<int>>> find_moves(std::vector<std::vector<char>> board, bool isLowercase) {

    std::vector<std::vector<std::vector<int>>> possible_moves = {};
    std::string side;

    if (isLowercase == true) {side = "black";}
    else if (isLowercase == false) {side = "white";}

    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (piece == '0') {continue;}
            if (is_lowercase(piece) != isLowercase) {continue;}

            for (int b_row = 0; b_row < board.size(); b_row++) {
                for (int b_column = 0; b_column < board[b_row].size(); b_column++) {
                    if (check_legal(board, piece, {row, column}, {b_row, b_column}, side) == true) {
                        if (check_check(board, piece, row, column, b_row, b_column, side) == true) {
                            possible_moves.push_back({{row, column}, {b_row, b_column}});
                        }
                    }
                }
            }
        }
    }

    return possible_moves;

}

double material_value(std::vector<std::vector<char>> board) {
    double white_counter = 0;
    double black_counter = 0;
    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (piece != '0') {
                if (is_lowercase(piece) == false) {
                    white_counter += piece_values[to_lowercase(piece)];
                }
                else if (is_lowercase(piece) == true) {
                    black_counter += piece_values[to_lowercase(piece)];
                }
            }
        }
    }
    white_counter = white_counter * material_factor;
    black_counter = black_counter * material_factor * -1;

    return white_counter + black_counter;   
}

double stacked_pawns(std::vector<std::vector<char>> board) {
    double white_counter = 0;
    double black_counter = 0;

    // starting from 1 since 0 will create error since row - 1
    for (int row = 1; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (piece == '0') {continue;}
            if (to_lowercase(piece) != 'p') {continue;}

            bool lowercase = is_lowercase(piece);
            if (to_lowercase(board[row - 1][column]) == 'p') {
                if (is_lowercase(board[row - 1][column]) == lowercase) {
                    if (lowercase == true) {
                        black_counter += stacked_pawn;
                    }
                    else {
                        white_counter += stacked_pawn;
                    }
                }
            }
        }
    }
    black_counter = -1 * black_counter;
    return white_counter + black_counter;
}

double in_check(std::vector<std::vector<char>> board) {
    double white_counter = 0;
    double black_counter = 0;

    std::vector<int> white_king = king_location(board, false);
    std::vector<int> black_king = king_location(board, true);

    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (piece == '0') {continue;}

            if (is_lowercase(piece) == false) {
                bool legal = check_legal(board, piece, {row, column}, black_king, "white");
                if (legal == true) {
                    white_counter += king_check;
                }
            }

            else if (is_lowercase(piece) == true) {
                bool legal = check_legal(board, piece, {row, column}, white_king, "black");
                if (legal == true) {
                    black_counter += king_check;
                }
            }

        }
    }

    black_counter = -1 * black_counter;
    return white_counter + black_counter;
}

double center_control(std::vector<std::vector<char>> board) {
    double white_counter = 0;
    double black_counter = 0;

    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board[row].size(); column++) {
            char piece = board[row][column];
            if (piece == '0') {continue;}

            bool lowercase = is_lowercase(piece);
            std::string side = "white";
            if (lowercase == true) {side = "black";}

            for (int i = 0; i < center_squares.size(); i++) {
                if (check_legal(board, piece, {row, column}, center_squares[i], side) == true) {
                    if (lowercase == true) {
                        black_counter += center;
                    } else {
                        white_counter += center;
                    }
                }
            }

        }
    }

    black_counter = black_counter * -1;
    return white_counter + black_counter;

}

double value_board(std::vector<std::vector<char>> board) {
    double material = material_value(board);
    double pawns = stacked_pawns(board);
    double check = in_check(board);
    double control_center = center_control(board);

    // std::cout << material << " " << pawns << " " << check << " " << control_center;

    return material + pawns + check + control_center;
}

// alpha is maximum value, beta is minimum value, initialized at -999999, and 999999 (opposite of max and min)
double minimax(std::vector<std::vector<char>> board, bool lowercaseSide, int depth, std::vector<std::vector<int>> move, double alpha, double beta) {
    std::vector<int> move1 = move[0];
    std::vector<int> move2 = move[1];

    char piece = board[move1[0]][move1[1]];
    char previous = board[move2[0]][move2[1]];

    if (to_lowercase(piece) == 'p' && (move2[0] == 0 || move2[0] == 7)) {
        if (is_lowercase(piece)) {piece = 'q';}
        else {piece = 'Q';}
    }
    board[move1[0]][move1[1]] = '0';
    board[move2[0]][move2[1]] = piece;


    if (depth == 0) {
        return value_board(board);
    }

    std::string board_string = board_to_str(board, lowercaseSide, depth);

    if (transposition_table.find(board_string) != transposition_table.end()) {
        return transposition_table[board_string];
    }

    std::vector<std::vector<std::vector<int>>> enemy_moves = find_moves(board, lowercaseSide == false);

    // lowercase side is black meaning minimizing side
    if (lowercaseSide == true) {
        double lowest = 999999;
        for (int i = 0; i < enemy_moves.size(); i++) {
            double score = minimax(board, lowercaseSide == false, depth - 1, enemy_moves[i], alpha, beta);
            if (score < lowest) {
                lowest = score;
                if (lowest < beta) {
                    beta = lowest;
                }
                if (beta <= alpha) {
                    transposition_table[board_string] = lowest;
                    return lowest;
                }
            }
        }
    }

    else {
        double highest = -999999;
        for (int i = 0; i < enemy_moves.size(); i++) {
            double score = minimax(board, lowercaseSide == false, depth - 1, enemy_moves[i], alpha, beta);
            if (score > highest) {
                highest = score;
                if (highest > alpha) {
                    alpha = highest;
                }
                if (beta <= alpha) {
                    transposition_table[board_string] = highest;
                    return highest;
                }
            }
        }
    }

    // std::vector<double> move_scores = {};

    // for (int i = 0; i < enemy_moves.size(); i++) {
    //     double score = minimax(board, lowercaseSide == false, depth - 1, enemy_moves[i]);
    //     move_scores.push_back(score);
    // }

    // if (lowercaseSide == true) {
    //     double lowest = 999999;

    //     for (int i = 0; i < move_scores.size(); i++) {
    //         if (move_scores[i] < lowest) {
    //             lowest = move_scores[i];
    //         }
    //     }
    //     return lowest;
    // }

    // else {
    //     double highest = -999999;

    //     for (int i = 0; i < move_scores.size(); i++) {
    //         if (move_scores[i] > highest) {
    //             highest = move_scores[i];
    //         }
    //     }
    //     return highest;
    // }

}

std::vector<std::vector<int>> bot_move(std::vector<std::vector<char>> board, bool lowercaseSide, int depth) {

    std::vector<std::vector<std::vector<int>>> moves = find_moves(board, lowercaseSide);

    double best_score = 0.0;
    int best_move = 0;

    for (int i = 0; i < moves.size(); i++) {
        double score = minimax(board, lowercaseSide, depth - 1, moves[i], -999999, 999999);

        if (lowercaseSide == false) {
            std::cout << "POOP";
            if (score > best_score) {
                best_score = score;
                best_move = i;
            }
        } else {
            if (score < best_score) {
                best_score = score;
                best_move = i;
            }
        }
    }
    std::cout << "\nmove score was: " << best_score;
    return moves[best_move];
}
