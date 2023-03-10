#pragma once

#include <string>
#include <vector>

void init_board(std::vector<std::vector<char>> &board, std::string fen_notation);
void print_board(std::vector<std::vector<char>> board);

// bool check_legal(std::vector<std::vector<char>> board, char piece, std::vector<int> from, std::vector<int> to, std::string side);
int make_move(std::vector<std::vector<char>> &board, std::string move, std::string turn);
bool check_checkmate(std::vector<std::vector<char>> board, bool kingIsLowercase);
bool check_stalemate(std::vector<std::vector<char>> board, bool kingIsLowercase);
bool check_check(std::vector<std::vector<char>> board, char piece, int move1_row, int move1_column, int move2_row, int move2_column, std::string turn);
