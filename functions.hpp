#include <string>
#include <vector>

void init_board(std::vector<std::vector<char>> &board, std::string fen_notation);
void print_board(std::vector<std::vector<char>> board);

// bool check_legal(std::vector<std::vector<char>> board, char piece, std::vector<int> from, std::vector<int> to, std::string side);
bool make_move(std::vector<std::vector<char>> &board, std::string move, std::string turn);
std::vector<std::vector<int>> best_move(std::vector<std::vector<char>> board, std::string side);
std::vector<std::vector<int>> bot_move(std::vector<std::vector<char>> board, bool lowercaseSide, int depth);