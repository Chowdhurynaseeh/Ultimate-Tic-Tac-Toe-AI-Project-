#include<bits/stdc++.h>
using namespace std;

// Constants and Defaults
int currentTurn = 1; // Current turn indicator (1 for player, -1 for AI)
int player = 1; // Player identifier
int ai = -1; // AI identifier
int currentBoard = -1; // Track which board is currently being played
int gameRunning = true; // Flag to indicate if the game is ongoing
int RUNS = 0; // Count of minimax runs
int MOVES = 0; // Track number of moves made
int switchAroo = 1; // Placeholder for potential game mode switch
int AIACTIVE = true; // Flag to enable/disable AI
char playerNames[3][10] = {"PLAYER", "AI", "X"}; // Player names for display
int Infinity = 1e9; // Representation of infinity for minimax
int bestMove = -1; // Best move found by the AI
int bestScore[10]; // Scores for different positions

// Boards is a 2D array where each of the 9 arrays represents a local Tic Tac Toe board
int boards[10][10] = {0}; // Initialize local boards to 0 (empty)

// This array is edited when a player wins a local board
int mainBoard[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Tracks the main game board

// Convert player values to characters for display
char convert(int a) {
    if (a == -1) {
        return 'O'; // AI is represented by 'O'
    } else if (a == 1) {
        return 'X'; // Player is represented by 'X'
    } else return '*'; // Empty space is represented by '*'
}

// Function to print the current state of the boards
void print_board() {
    // Print the local boards
    for (int j = 0; j < 11; j++) {
        cout << "- "; // Separator line
    }
    cout << endl << endl;

    // Loop through each row of the local boards
    for (int i = 0; i < 3; i++) {
        for (int j = i * 3; j < (i + 1) * 3; j++) {
            cout << convert(boards[j][0]) << " " << convert(boards[j][1]) << " " << convert(boards[j][2]) << " ";
            if (j + 1 < (i + 1) * 3) {
                cout << "| "; // Separator for columns
            }
        }
        cout << endl;

        // Repeat for the second row of each local board
        for (int j = i * 3; j < (i + 1) * 3; j++) {
            cout << convert(boards[j][3]) << " " << convert(boards[j][4]) << " " << convert(boards[j][5]) << " ";
            if (j + 1 < (i + 1) * 3) {
                cout << "| "; // Separator for columns
            }
        }
        cout << endl;

        // Repeat for the third row of each local board
        for (int j = i * 3; j < (i + 1) * 3; j++) {
            cout << convert(boards[j][6]) << " " << convert(boards[j][7]) << " " << convert(boards[j][8]) << " ";
            if (j + 1 < (i + 1) * 3) {
                cout << "| "; // Separator for columns
            }
        }

        cout << endl << endl;

        // Print the separator line
        for (int j = 0; j < 11; j++) {
            cout << "- "; // Separator line
        }
        cout << endl << endl;
    }

    // Print the main board
    cout << convert(mainBoard[0]) << " " << convert(mainBoard[1]) << " " << convert(mainBoard[2]) << endl;
    cout << convert(mainBoard[3]) << " " << convert(mainBoard[4]) << " " << convert(mainBoard[5]) << endl;
    cout << convert(mainBoard[6]) << " " << convert(mainBoard[7]) << " " << convert(mainBoard[8]) << endl;
    cout << endl;

    // Print final separator
    for (int j = 0; j < 11; j++) {
        cout << "- "; // Separator line
    }
    cout << endl;
}

// Check for win conditions in a standard Tic Tac Toe board
int checkWinCondition(int SG[9]) {
    int a = 1; // Check for player win
    // Check rows, columns, and diagonals for a win
    if (SG[0] + SG[1] + SG[2] == a * 3 ||
        SG[3] + SG[4] + SG[5] == a * 3 ||
        SG[6] + SG[7] + SG[8] == a * 3 ||
        SG[0] + SG[3] + SG[6] == a * 3 ||
        SG[1] + SG[4] + SG[7] == a * 3 ||
        SG[2] + SG[5] + SG[8] == a * 3 ||
        SG[0] + SG[4] + SG[8] == a * 3 ||
        SG[2] + SG[4] + SG[6] == a * 3) {
        return a; // Return player win
    }

    a = -1; // Check for AI win
    if (SG[0] + SG[1] + SG[2] == a * 3 ||
        SG[3] + SG[4] + SG[5] == a * 3 ||
        SG[6] + SG[7] + SG[8] == a * 3 ||
        SG[0] + SG[3] + SG[6] == a * 3 ||
        SG[1] + SG[4] + SG[7] == a * 3 ||
        SG[2] + SG[5] + SG[8] == a * 3 ||
        SG[0] + SG[4] + SG[8] == a * 3 ||
        SG[2] + SG[4] + SG[6] == a * 3) {
        return a; // Return AI win
    }
    return 0; // No winner
}

// Evaluates a single Tic Tac Toe board to determine its value
int realEvaluateSquare(int pos[10]) {
    int evaluation = 0; // Initial evaluation score
    int points[10] = {4, 2, 4, 2, 8, 2, 4, 2, 4}; // Point values for squares

    // Calculate evaluation based on current state
    for (int bw = 0; bw < 9; bw++) {
        evaluation -= pos[bw] * points[bw]; // Score negative for occupied squares
    }

    int a = 2; // Check for player pairs and potential wins
    // Checking for possible wins
    if (pos[0] + pos[1] + pos[2] == a ||
        pos[3] + pos[4] + pos[5] == a ||
        pos[6] + pos[7] + pos[8] == a) {
        evaluation -= 6; // Penalty for allowing player to win
    }
    if (pos[0] + pos[3] + pos[6] == a ||
        pos[1] + pos[4] + pos[7] == a ||
        pos[2] + pos[5] + pos[8] == a) {
        evaluation -= 6; // Penalty for allowing player to win
    }
    if (pos[0] + pos[4] + pos[8] == a ||
        pos[2] + pos[4] + pos[6] == a) {
        evaluation -= 7; // Penalty for allowing player to win
    }

    // Check for AI threats and potential wins
    a = -1; // AI checks
    if ((pos[0] + pos[1] == 2 * a && pos[2] == -a) ||
        (pos[1] + pos[2] == 2 * a && pos[0] == -a) ||
        (pos[0] + pos[2] == 2 * a && pos[1] == -a) ||
        (pos[3] + pos[4] == 2 * a && pos[5] == -a) ||
        (pos[3] + pos[5] == 2 * a && pos[4] == -a) ||
        (pos[5] + pos[4] == 2 * a && pos[3] == -a) ||
        (pos[6] + pos[7] == 2 * a && pos[8] == -a) ||
        (pos[6] + pos[8] == 2 * a && pos[7] == -a) ||
        (pos[7] + pos[8] == 2 * a && pos[6] == -a) ||
        (pos[0] + pos[3] == 2 * a && pos[6] == -a) ||
        (pos[0] + pos[6] == 2 * a && pos[3] == -a) ||
        (pos[3] + pos[6] == 2 * a && pos[0] == -a) ||
        (pos[1] + pos[4] == 2 * a && pos[7] == -a) ||
        (pos[1] + pos[7] == 2 * a && pos[4] == -a) ||
        (pos[4] + pos[7] == 2 * a && pos[1] == -a) ||
        (pos[2] + pos[5] == 2 * a && pos[8] == -a) ||
        (pos[2] + pos[8] == 2 * a && pos[5] == -a) ||
        (pos[5] + pos[8] == 2 * a && pos[2] == -a) ||
        (pos[0] + pos[4] == 2 * a && pos[8] == -a) ||
        (pos[2] + pos[4] == 2 * a && pos[6] == -a) ||
        (pos[6] + pos[4] == 2 * a && pos[0] == -a)) {
        evaluation += 6; // AI potential win
    }
    return evaluation; // Return evaluation score
}

// Evaluate a single local board's potential
int evaluatePos(int pos[10], int square) {
    pos[square] = ai; // Temporarily place AI
    int evaluation = realEvaluateSquare(pos); // Evaluate board with AI's perspective
    pos[square] = player; // Temporarily place player
    int evalPlayer = realEvaluateSquare(pos); // Evaluate board with player's perspective
    pos[square] = 0; // Reset square
    return evaluation - evalPlayer; // Difference gives AI advantage
}

// Evaluate the entire game state
int evaluateGame(int position[10][10], int currentBoard) {
    int eval = 0; // Initialize overall evaluation
    for (int eh = 0; eh < 9; eh++) {
        eval += evaluatePos(position[eh], eh); // Evaluate each local board
        int tmpWin = checkWinCondition(position[eh]); // Check for winner
        mainBoard[eh] = tmpWin; // Update main board
    }
    eval -= checkWinCondition(mainBoard) * 5000; // Heavily penalize if main board is won
    return eval; // Return evaluation
}

// Minimax algorithm implementation for AI decision-making
pair<int, int> miniMax(int position[10][10], int boardToPlayOn, int depth, int alpha, int beta, bool maximizingPlayer) {
    RUNS++; // Increment run count
    int calcEval = evaluateGame(position, boardToPlayOn); // Get current evaluation
    if (depth <= 0 || abs(calcEval) > 5000) return {calcEval, -1}; // Base case

    // If there's no valid board to play on, reset
    if (boardToPlayOn != -1 && (checkWinCondition(position[boardToPlayOn]) != 0 || !emptySquare(position[boardToPlayOn]))) {
        boardToPlayOn = -1;
    }

    int maxEval = maximizingPlayer ? -Infinity : Infinity; // Initialize maxEval
    for (int mm = 0; mm < 9; mm++) { // Iterate through local boards
        for (int trr = 0; trr < 9; trr++) { // Iterate through squares in the board
            if (checkWinCondition(position[mm]) == 0 && position[mm][trr] == 0) {
                position[mm][trr] = maximizingPlayer ? ai : player; // Make the move
                int eval = miniMax(position, (boardToPlayOn == -1) ? trr : boardToPlayOn, depth - 1, alpha, beta, !maximizingPlayer).first; // Recursion
                position[mm][trr] = 0; // Undo the move
                // Update maxEval and alpha/beta values
                if (maximizingPlayer) {
                    if (eval > maxEval) maxEval = eval; // Update maxEval if necessary
                    alpha = max(alpha, eval); // Update alpha
                } else {
                    if (eval < maxEval) maxEval = eval; // Update maxEval if necessary
                    beta = min(beta, eval); // Update beta
                }
            }
            if (beta <= alpha) break; // Alpha-beta pruning
        }
    }
    return {maxEval, boardToPlayOn}; // Return the best evaluation and board
}

// Main function and game loop would go here...
int main() {
    // Initialize game settings
    cout << "Welcome to 3D Tic Tac Toe!" << endl;
    cout << "Player is X and AI is O." << endl;

    while (gameRunning) {
        // Print the current game state
        print_board();

        // Check if the main board has a winner
        int mainWin = checkWinCondition(mainBoard);
        if (mainWin != 0) {
            // Announce the winner and exit the game loop
            cout << (mainWin == player ? "PLAYER wins!" : "AI wins!") << endl;
            break;
        }

        // Determine which board the player can play on
        cout << "Select a board to play on (0-8): ";
        cin >> currentBoard;

        // Validate the input
        if (currentBoard < 0 || currentBoard > 8 || checkWinCondition(boards[currentBoard]) != 0 || !emptySquare(boards[currentBoard])) {
            cout << "Invalid board selection. Please try again." << endl;
            continue; // Retry if invalid
        }

        // Player's turn: request their move
        int playerMove;
        cout << "Enter your move (0-8) for board " << currentBoard << ": ";
        cin >> playerMove;

        // Validate the player's move
        if (playerMove < 0 || playerMove > 8 || boards[currentBoard][playerMove] != 0) {
            cout << "Invalid move. Please try again." << endl;
            continue; // Retry if invalid
        }

        // Update the board with the player's move
        boards[currentBoard][playerMove] = player; // Player's move
        MOVES++; // Increment move count

        // Check for win after player's move
        if (checkWinCondition(boards[currentBoard]) == player) {
            mainBoard[currentBoard] = player; // Update main board
        }

        // Check if the game has ended after the player's move
        if (checkWinCondition(mainBoard) != 0) {
            print_board(); // Show final board state
            cout << (mainWin == player ? "PLAYER wins!" : "AI wins!") << endl;
            break; // Exit the game loop
        }

        // AI's turn: if AI is active
        if (AIACTIVE) {
            cout << "AI is making its move..." << endl;

            // Use the minimax algorithm to determine the best move
            pair<int, int> aiMove = miniMax(boards, currentBoard, 5, -Infinity, Infinity, true);
            bestMove = aiMove.second; // Best move determined by AI

            // Place the AI's move
            boards[currentBoard][bestMove] = ai; // AI's move
            MOVES++; // Increment move count

            // Check for win after AI's move
            if (checkWinCondition(boards[currentBoard]) == ai) {
                mainBoard[currentBoard] = ai; // Update main board
            }

            // Check if the game has ended after AI's move
            if (checkWinCondition(mainBoard) != 0) {
                print_board(); // Show final board state
                cout << "AI wins!" << endl;
                break; // Exit the game loop
            }
        }

        // Check if the game is a draw (if all boards are full and no winner)
        if (MOVES >= 81) { // Maximum moves in a 3D Tic Tac Toe game
            print_board(); // Show final board state
            cout << "It's a draw!" << endl;
            break; // Exit the game loop
        }
    }

    return 0; // End of the program
}

