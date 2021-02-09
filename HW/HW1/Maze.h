#ifndef MAZE_H
#define MAZE_H

#include "Player.h"
#include <vector>
#include <iostream>
#include <unordered_map>

// types of square values that populate the board
enum class SquareType { Wall=0, Exit, Empty, Human, Enemy, Treasure };

// returns an emoji representing the square type
std::string SquareTypeStringify(SquareType sq);

class Board {
public:
	Board() {};
	Board(int enemy_count, const int m, const int n);
	~Board() = default;

	// getters, setters
	int get_rows() const {return rows_; }
	int get_cols() const {return cols_; }
	void set_rows(const int r) { this->rows_=r; }
	void set_cols(const int c) { this->cols_=c; }

	// get square type value for designated position
	SquareType get_square_value(Position pos) const;

	// get enemies on the board 
	std::vector<Player *> get_enemies() const;

	// set the position to a certain square type
	void SetSquareValue(Position pos, SquareType value);

	// checkout 
	std::string ToRelativePosition(Position pos);

	// retrieve valid moves from stated position
	std::unordered_map<std::string, Position> GetMoves(Position pos);

	// move player to next position if valid
	bool MovePlayer(Player *p, std::unordered_map<std::string, Position> pos_map, std::string next_pos);

	// retrieve squaretype of exit
	SquareType GetExitOccupant();

	// overload stream operator to print board
	friend std::ostream& operator<<(std::ostream& os, const Board &b);

private:
	std::vector<std::vector<SquareType> >vec_;
	
	int rows_;
	int cols_;
	
	std::vector<Player *> enemies_v_;
};

class Maze {
public:
	Maze() {}
	Maze(Player *human);
	~Maze(); // del board

	// initialize a new game
	void NewGame();

	// return if current board is valid or not
	bool ValidBoard();

	// have the given Player take their turn
	void TakeTurn(Player *p);

	// Get the next player in turn order
	Player * GetNextPlayer();

	// return true if the human made it to the exit 
	// or the enemies ate human
	bool IsGameOver();

	// string info about the game's conditions after it is over
	std::string GenerateReport();
	friend std::ostream& operator<<(std::ostream& os, const Maze &m);
private:
	Board *board_;
	std::vector<Player *> players_;
	int turn_count_;
};  // class Maze

#endif  // MAZE_H
