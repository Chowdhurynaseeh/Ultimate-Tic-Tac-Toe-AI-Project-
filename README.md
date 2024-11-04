# Tic Tac Toe Game

This is a Tic Tac Toe game implementation in C++. The game allows for a player versus AI mode where the AI utilizes the minimax algorithm to determine its moves.

## Features

- Player vs AI gameplay.
- AI uses a minimax algorithm with alpha-beta pruning for optimal move selection.
- A visual representation of the game board.
- Keeps track of the main board and local boards.

## Getting Started

### Prerequisites

Make sure you have a C++ compiler installed on your machine. You can use g++ or any other modern C++ compiler.

### Installation

1. Clone the repository: `git clone <repository-url>`
2. Navigate to the directory: `cd <repository-directory>`
3. Compile the code: `g++ -o tictactoe tictactoe.cpp`
4. Run the game: `./tictactoe`

## How to Play

The game consists of 9 small Tic Tac Toe boards arranged in a 3x3 grid. Players take turns to make a move on one of the small boards. The current player can only play on a board that is determined by the last move made in the previous round. The first player to win on any of the small boards will win that board. Winning three small boards in a row on the main board will declare them as the overall winner. The game will continue until all boards are filled or one player wins.

## Game Mechanics

### Board Representation

Each small board is represented by a 3x3 grid, while the main board keeps track of the results of the small boards. Players are represented as follows: Player: X and AI: O. The AI employs a minimax algorithm with alpha-beta pruning to determine the best possible move, evaluating potential moves based on immediate win conditions, blocking the player from winning, and strategic advantages based on the position of moves.

### Functions

- `convert(int a)`: Converts player values to characters for display.
- `print_board()`: Prints the current state of the game board.
- `checkWinCondition(int SG[9])`: Checks if a player has won on a given board.
- `realEvaluateSquare(int pos[10])`: Evaluates the score of a small board.
- `evaluatePos(int pos[10], int square)`: Evaluates a move based on its potential.
- `evaluateGame(int position[10][10], int currentBoard)`: Evaluates the overall game state.
- `miniMax(int position[10][10], int boardToPlayOn, int depth, int alpha, int beta, bool maximizingPlayer)`: Implements the minimax algorithm for decision making.

## Contributing

Feel free to submit pull requests or open issues to contribute to this project. Any suggestions for improvement or additional features are welcome!

## License

This project is licensed under the [MIT License](LICENSE). See the [LICENSE](LICENSE) file for details.

### Summary of the MIT License
- You are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of this software.
- The software is provided "as is," without warranty of any kind.
- You must include the original license notice in all copies or substantial portions of the software.

### Other Licensing Options
If you wish to use a different license, please consult the [ChooseALicense.com](https://choosealicense.com/) website for more options.

