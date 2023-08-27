//Badger
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Move {
	int row, col;
};

class TicTacToe {
public:
	TicTacToe() : boardSize(3), board(boardSize, vector<char>(boardSize, ' ')) {}
	TicTacToe(short int size) : boardSize(size), board(boardSize, vector<char>(boardSize, ' ')) {}

	void printBoard() const {
		cout << "   ";
		for (int i = 0; i < boardSize; ++i) {
			cout << " " << static_cast<char>('A' + i) << " ";
		}
		cout << endl;

		for (int row = 0; row < boardSize; ++row) {
			cout << " " << row + 1 << " ";
			for (int col = 0; col < boardSize; ++col) {
				cout << "|" << board[row][col] << "|";
			}
			cout << endl;
		}
	}

	bool makeMove(char player, int row, int col) {
		if (row < 1 || row > boardSize || col < 1 || col > boardSize || board[row - 1][col - 1] != ' ') {
			return false; // Invalid move
		}
		board[row - 1][col - 1] = player;
		return true;
	}

	bool isGameOver() const {
		return checkWin('X') || checkWin('O') || isBoardFull();
	}

	bool checkWin(char player) const {
		for (int i = 0; i < boardSize; ++i) {
			// Check rows and columns
			if (board[i][0] == player && allMatchInRow(board[i], player)) return true;
			if (board[0][i] == player && allMatchInColumn(i, player)) return true;
		}
		// Check diagonals
		return (board[0][0] == player && allMatchInDiagonal(player, 1, 1, 1)) ||
			   (board[0][boardSize - 1] == player && allMatchInDiagonal(player, 1, -1, 1));
	}

	 int evaluate() {
		// Checking for Rows for X or O victory.
		for (int row = 0; row < boardSize; ++row) {
			if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
				if (board[row][0] == 'O')
					return 10; // Bot ('O') wins
				else if (board[row][0] == 'X')
					return -10; // Player ('X') wins
			}
		}

		// Checking for Columns for X or O victory.
		for (int col = 0; col < boardSize; ++col) {
			if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
				if (board[0][col] == 'O')
					return 10;
				else if (board[0][col] == 'X')
					return -10;
			}
		}

		// Checking for Diagonals for X or O victory.
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			if (board[0][0] == 'O')
				return 10;
			else if (board[0][0] == 'X')
				return -10;
		}

		if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			if (board[0][2] == 'O')
				return 10;
			else if (board[0][2] == 'X')
				return -10;
		}

		// If none of the above conditions are met, it's a draw
		return 0;
	}

	bool isMovesLeft() {
		for (int row = 0; row < boardSize; ++row) {
			for (int col = 0; col < boardSize; ++col) {
				if (board[row][col] == ' ') {
					return true;
				}
			}
		}
		return false;
	}


	int minimax(int depth, bool isMax) {
		int score = evaluate();

		if (score == 10)
			return score;

		if (score == -10)
			return score;

		if (!isMovesLeft())
			return 0;

		if (isMax) {
			int best = INT_MIN;

			for (int row = 0; row < boardSize; ++row) {
				for (int col = 0; col < boardSize; ++col) {
					if (board[row][col] == ' ') {
						board[row][col] = 'O';
						int moveScore = minimax(depth + 1, false);
						board[row][col] = ' ';
						best = max(best, moveScore);
					}
				}
			}
			return best;
		} else {
			int best = INT_MAX;

			for (int row = 0; row < boardSize; ++row) {
				for (int col = 0; col < boardSize; ++col) {
					if (board[row][col] == ' ') {
						board[row][col] = 'X';
						int moveScore = minimax(depth + 1, true);
						board[row][col] = ' ';
						best = min(best, moveScore);
					}
				}
			}
			return best;
		}
	}

	Move findBestMove() {
		int bestVal = INT_MIN;
		Move bestMove = { -1, -1 };

		for (int row = 0; row < boardSize; ++row) {
			for (int col = 0; col < boardSize; ++col) {
				if (board[row][col] == ' ') {
					board[row][col] = 'O';
					int moveVal = minimax(0, false);
					board[row][col] = ' ';

					if (moveVal > bestVal) {
						bestMove.row = row;
						bestMove.col = col;
						bestVal = moveVal;
					}
				}
			}
		}
		// Scuffed way of getting choice to actually appear on board since bot was choosing bad moves.
		// Seems to work; hopefully it doesn't choose option too far off of board :)
		bestMove.row+=1;
		bestMove.col+=1;

		return bestMove;
	}

private:
	int boardSize;
	vector<vector<char>> board;

	bool allMatchInRow(const vector<char>& row, char player) const {
		for (char cell : row) {
			if (cell != player) return false;
		}
		return true;
	}

	bool allMatchInColumn(int col, char player) const {
		for (int i = 0; i < boardSize; ++i) {
			if (board[i][col] != player) return false;
		}
		return true;
	}

	bool allMatchInDiagonal(char player, int rowStep, int colStep, int startRow) const {
		int row = startRow;
		int col = (colStep == 1) ? 0 : boardSize - 1;

		for (int i = 0; i < boardSize; ++i) {
			if (board[row][col] != player) return false;
			row += rowStep;
			col += colStep;
		}
		return true;
	}

	bool isBoardFull() const {
		for (int row = 0; row < boardSize; ++row) {
			for (int col = 0; col < boardSize; ++col) {
				if (board[row][col] == ' ') {
					return false; // At least one empty cell exists
				}
			}
		}
		return true; // All cells are filled
	}
};

int main(int argc, char** argv) {
	short int size=3;
	if (argc > 2 || (argc == 2 && argv[1][0]+argv[1][1] == '-'+'h')) {
		std::cerr << "Usage: " << argv[0] << " <board_size(default is 3)>" << std::endl;
		return 1;
	}
	else if(argc == 2){
		// Parse the command line argument for board size
		size = std::atoi(argv[1]);
	}
	TicTacToe game(size);
	char currentPlayer = 'X';

	while (!game.isGameOver()) {
		game.printBoard();

		if (currentPlayer == 'X') {
			// Player's turn
			int row;
		char colChar;
		cout << "'" << currentPlayer << "', what's your choice? ";
		cin >> colChar >> row;

		int col = colChar - 'A' + 1;
		if (game.makeMove(currentPlayer, row, col)) {
			currentPlayer = 'O';
		}
		else {
			cout << "Invalid move. Try again." << endl;
		}
		} else {
			// Bot's turn
			Move bestMove = game.findBestMove();
			game.makeMove('O', bestMove.row, bestMove.col);
			currentPlayer = 'X';
		}
	}

	game.printBoard();
	char winner = (game.checkWin('X')) ? 'X' : (game.checkWin('O')) ? 'O' : ' ';
	if (winner != ' ') {
		cout << "Congratulations! Player '" << winner << "' wins!" << endl;
	} else {
		cout << "It's a draw!" << endl;
	}

	return 0;
}
// FIXME: bot only works for size 3 board :(