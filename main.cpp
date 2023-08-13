#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TicTacToe {
public:
	TicTacToe(int size) : board(size, vector<char>(size, ' ')), boardSize(size) {}

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

private:
	vector<vector<char>> board;
	int boardSize;

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

int main() {
	int boardSize;
	cout << "Enter the board size (e.g., 3 for 3x3): ";
	cin >> boardSize;

	TicTacToe game(boardSize);
	char currentPlayer = 'X';

	while (!game.isGameOver()) {
		game.printBoard();
		int row;
		char colChar;
		cout << "'" << currentPlayer << "', what's your choice? ";
		cin.clear();
		cin.ignore();
		cin >> colChar >> row;

		int col = colChar - 'A' + 1;
		if (game.makeMove(currentPlayer, row, col)) {
			currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
		}
		else {
			cout << "Invalid move. Try again." << endl;
		}
	}

	game.printBoard();
	char winner = (game.checkWin('X')) ? 'X' : (game.checkWin('O')) ? 'O' : ' ';
	if (winner != ' ') {
		cout << "Congratulations! Player '" << winner << "' wins!" << endl;
	}
	else {
		cout << "It's a draw!" << endl;
	}

	return 0;
}