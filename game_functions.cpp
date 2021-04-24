#include <string>
#include <vector>
#include <iostream>


char to_lowercase(char input) {
    if (input >= 65 && input <= 90) {
        return char(input + 32);
    }
    return input;
}

bool is_lowercase(char input) {
    return input >= 97 && input <= 122;
}

int letter_to_column(char letter) {
    letter = to_lowercase(letter);
    if (letter == 'a') {return 0;}
    if (letter == 'b') {return 1;}
    if (letter == 'c') {return 2;}
    if (letter == 'd') {return 3;}
    if (letter == 'e') {return 4;}
    if (letter == 'f') {return 5;}
    if (letter == 'g') {return 6;}
    if (letter == 'h') {return 7;}
    return -1;
}

int char_to_int(char input);

bool check_legal(std::vector<std::vector<char>> board, char piece, std::vector<int> from, std::vector<int> to, std::string side) {
    piece = to_lowercase(piece);

    bool isLegal = false;
    bool capturing = false;

    bool lowercase_side;

    if (side == "white") {
        lowercase_side = false;
    }
    else {
        lowercase_side = true;
    }

    char attacking = board[to[0]][to[1]];

    if (attacking != '0') {
        if (is_lowercase(attacking) == false && side == "white") {
            return isLegal;
        }
        if (is_lowercase(attacking) == true && side == "black") {
            return isLegal;
        }
        capturing = true;
    }


    // check pawn moves:
    if (piece == 'p') {
        if (side == "white") {
            if (capturing == false) {
                if (from[1] == to[1] && (from[0] - to[0]) == 1) {
                    isLegal = true;
                }
                // check for moving pawn up two spaces:
                else if (from[0] == 6 && from[1] == to[1] && (from[0] - to[0]) == 2) {
                    isLegal = true;
                }
            }
            // check for diagnol capturing:
            else if (capturing == true) {
                if ((from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 1) {
                    isLegal = true;
                }
            }
        }

        else {
            if (capturing == false) {
                if (from[1] == to[1] && (from[0] - to[0]) == -1) {
                    isLegal = true;
                }
                // check for moving pawn up two spaces:
                else if (from[0] == 1 && from[1] == to[1] && (from[0] - to[0]) == -2) {
                    isLegal = true;
                }
            }
            else if (capturing == true) {
                if ((from[0] - to[0]) == -1 && abs(from[1] - to[1]) == 1) {
                    isLegal = true;
                }
            }
        }

    }

    // check bishop (and queen diagnol) moves:
    else if (piece == 'b' || piece == 'q') {
        if (abs(to[0] - from[0]) == abs(to[1] - from[1])) {

            // int row = std::min(from[0], to[0]);
            // int column = std::min(from[1], to[1]);
            int row = from[0];
            int column = from[1];

            int row_factor, column_factor;

            if (row < to[0]) {row_factor = 1;}
            else {row_factor = -1;}
            if (column < to[1]) {column_factor = 1;}
            else {column_factor = -1;}

            bool passing = false;

            for (int i = 0; i < std::abs(from[0] - to[0]) - 1; i++) {
                row += row_factor;
                column += column_factor;
                
                if (board[row][column] != '0') {
                    passing = true;
                }
            }

            if (passing == false) {
                isLegal = true;
            }

            // for (int row = std::min(from[0], to[0]); row < std::max(from[0], to[0]); row++) {

            // }
        } else {
            isLegal = false;
        }
    }

    // check rook (and queen horizontal) moves:
    if (piece == 'r' || (isLegal == false && piece == 'q')) {
        if (from[0] == to[0]) {
            isLegal = true;
            int start = std::min(from[1], to[1]);
            for (int i = 0; i < std::max(from[1], to[1]) - std::min(from[1], to[1]) - 1; i++) {
                start++;
                if (board[from[0]][start] != '0') {
                    isLegal = false;
                }
            }
        } else if (from[1] == to[1]) {
            isLegal = true;
            int start = std::min(from[0], to[0]);
            for (int i = 0; i < std::max(from[0], to[0]) - std::min(from[0], to[0]) - 1; i++) {
                start++;
                if (board[start][from[1]] != '0') {
                    isLegal = false;
                }
            }

        } else {
            isLegal = false;
        }
    }

    // check knight moves:
    else if (piece == 'n') {
        if (abs(to[0] - from[0]) == 2 && abs(to[1] - from[1]) == 1) {
            isLegal = true;
        }
        else if (abs(to[0] - from[0]) == 1 && abs(to[1] - from[1]) == 2) {
            isLegal = true;
        }
        else {
            isLegal = false;
        }
    }

    else if (piece == 'k') {
        if (abs(from[0] - to[0]) == 1 && from[1] == to[1]) {
            isLegal = true;
        }
        else if (abs(from[1] - to[1]) == 1 && from[0] == to[0]) {
            isLegal = true;
        }
        else if (abs(from[1] - to[1]) == 1 && abs(from[1] - to[1]) == abs(from[0] - to[0])) {
            isLegal = true;
        }
        else {
            isLegal = false;
        }
    }

    // check for king in check if move is legal:
    // if (isLegal == false) {return isLegal;}

    // board[to[0]][to[1]] = '0';
    // board[from[0]][from[1]] = piece;

    return isLegal;
    // std::cout << from[0] << from[1];

}


std::vector<int> king_location(std::vector<std::vector<char>> board, bool isLowerCase) {
    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board.size(); column++) {
            char current = board[row][column];
            if (to_lowercase(current) == 'k') {
                if (is_lowercase(current) == isLowerCase) {
                   return {row, column};
                }
            }
        }
    }
    return {0, 0};
}


bool check_check(std::vector<std::vector<char>> board, char piece, int move1_row, int move1_column, int move2_row, int move2_column, std::string turn) {

    bool legal = true;

    char previous_piece = board[move2_row][move2_column];
    board[move1_row][move1_column] = '0';
    board[move2_row][move2_column] = piece;

    bool isLowercaseSide;
    std::string check_side;

    if (turn == "white") {isLowercaseSide = false; check_side = "black";}
    else if (turn == "black") {isLowercaseSide = true; check_side = "white";}

    std::vector<int> king = king_location(board, isLowercaseSide);

    for (int board_row = 0; board_row < board.size(); board_row++) {
        for (int board_column = 0; board_column < board[board_row].size(); board_column++) {
            char current_piece = board[board_row][board_column];
            if (is_lowercase(current_piece) != isLowercaseSide) {
                if (check_legal(board, current_piece, {board_row, board_column}, king, check_side)) {
                    legal = false;
                    board[move1_row][move1_column] = piece;
                    board[move2_row][move2_column] = previous_piece;
                    return legal;
                }
            }
        }
    }
    return legal;
}

bool make_move(std::vector<std::vector<char>> &board, std::string move, std::string turn) {
    std::string move1,  move2, current;

    for (int i = 0; i < move.size(); i++) {
        if (move[i] == '-') {
            move1 = current;
            current = "";
            continue;
        }
        current += move[i];
    }
    move2 = current;

    int move1_column = letter_to_column(move1[0]);
    int move1_row =  8 - char_to_int(move1[1]);
    int move2_column = letter_to_column(move2[0]);
    int move2_row = 8 - char_to_int(move2[1]);

    if (move1_column == -1 || move2_column == -1 || move1_row == -1 || move2_row == -1) {
        std::cout << "INVALID MOVE: " << move;
        return false;
    }

    char piece = board[move1_row][move1_column];

    bool correct_side = false;
    if (is_lowercase(piece) && turn == "white") {correct_side = false;}
    else if (!is_lowercase(piece) && turn == "black") {correct_side = false;}
    else {correct_side = true;}

    // std::cout << (is_lowercase(piece) == true && turn == "white");
    // std::cout << (is_lowercase(piece) == false && turn == "black");
    // std::cout << correct_side;
    // std::cout << piece;
    if (piece == '0' || correct_side == false) {
        std::cout << "INVALID MOVE: " << move;
        return false;
    }

    bool legal = check_legal(board, to_lowercase(piece), {move1_row, move1_column}, {move2_row, move2_column}, turn);

    if (legal == false) {
        std::cout << "ILLEGAL MOVE: " << move;
        return false;
    }

    // check for illegal move by check:
    bool legal_check = check_check(board, piece, move1_row, move1_column, move2_row, move2_column, turn);

    if (legal_check == false) {
        return false;
    }

    // promote pawn to queen:
    if (to_lowercase(piece) == 'p' && (move2_row == 0 || move2_row == 7)) {
        if (is_lowercase(piece)) {piece = 'q';}
        else {piece = 'Q';}
    }

    board[move1_row][move1_column] = '0';
    board[move2_row][move2_column] = piece;

    return true;

}