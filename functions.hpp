#include <string>
#include <vector>

void init_board(std::vector<std::vector<char>> &board, std::string fen_notation);
void print_board(std::vector<std::vector<char>> board);

bool make_move(std::vector<std::vector<char>> &board, std::string move, std::string turn);
// char to_lowercase(char input);