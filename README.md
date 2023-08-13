# Tic-Tac-Toe Game

This is a command-line-based Tic-Tac-Toe game written in C++. The game allows you to play on an expandable game board, which means you can specify the size of the board before starting the game. Players take turns to make their moves, and the first player to complete a row, column, or diagonal with their symbol (X or O) wins the game.

## Features

- Expandable game board: You can choose the size of the board, making the game more challenging and fun.
- Input validation: The program validates user inputs to ensure they are within the bounds of the game board and correspond to valid moves.
- Win detection: The game checks for wins by rows, columns, and diagonals and declares the winner accordingly.
- Draw detection: If the board is filled, and no player has won, the game will end in a draw.

## Getting Started

1. Clone the repository to your local machine.
2. Compile the C++ code using a C++ compiler (e.g., g++).
3. Run the compiled executable.

```
$ g++ tic_tac_toe.cpp -o tic_tac_toe
$ ./tic_tac_toe
```

4. Enter the board size (e.g., 3 for a 3x3 board) to start the game.
5. Players take turns entering their moves by specifying the row (number) and column (alphabet) of their choice. For example, `B2` represents the middle cell of a 3x3 board.

## How to Play

1. The game starts with an empty board of the specified size.
2. Players take turns making moves by entering their preferred cell in the format `<Column><Row>`. For example, to place your symbol in the center of a 3x3 board, enter `B2`.
3. The game continues until one player wins or the board is filled, resulting in a draw.
4. The program will display the board after each move.
5. Once the game is over, the winner will be declared, or a draw will be announced.

## Example Gameplay

```
Enter the board size (e.g., 3 for 3x3): 3
   | A | B | C |
1 |   |   |   |
2 |   |   |   |
3 |   |   |   |
'X', what's your choice? B2
   | A | B | C |
1 |   |   |   |
2 |   | X |   |
3 |   |   |   |
'O', what's your choice? A1
   | A | B | C |
1 | O |   |   |
2 |   | X |   |
3 |   |   |   |
'X', what's your choice? B1
   | A | B | C |
1 | O | X |   |
2 |   | X |   |
3 |   |   |   |
'O', what's your choice? A3
   | A | B | C |
1 | O | X |   |
2 |   | X |   |
3 | O |   |   |
'X', what's your choice? A2
   | A | B | C |
1 | O | X |   |
2 | X | X |   |
3 | O |   |   |
'X' wins!
```

## Contributions

Contributions to this project are welcome. Feel free to open issues or submit pull requests if you find any bugs or have suggestions for improvements.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Enjoy playing the Tic-Tac-Toe game!