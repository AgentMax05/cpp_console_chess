# cpp_console_chess
A CLI chess game you can play in the console, coded in C++.

This is a small project I started when I was in 9th grade, and never really finished.
Currently it should work for 2 players, however the program doesn't allow en passant moves nor castling.

P.S. keep in mind this isn't the cleanest code as most of it was written when I was first learning C++!

## UI
Here's what the game looks like:
<!-- <image src="https://user-images.githubusercontent.com/64991518/224203536-b17b5fb7-14af-4de9-a5ff-4e81ff70635d.png" width=600> -->
<image src="https://user-images.githubusercontent.com/64991518/224524711-db98387d-6070-4c11-b9a2-a1d8c5cb6f24.png" width=600>

Each piece is represented by a letter: p for pawn, r for rook, n for knight, b for bishop, q for queen, and k for king.
Uppercase letters represent white pieces, while lowercase letters represent black pieces.
  
## Entering Moves
Moves must be entered in the following format: [file-from][rank-from]-[file-to][rank-to]. 
In other words, the position of the piece with the letter first and then number, followed by a dash, and then the destination for the piece to be moved to.
