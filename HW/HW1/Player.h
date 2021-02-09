#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

// position of player
struct Position {
	int row;
	int col;

	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}
};


class Player {
public:
	Player(const std::string name, const bool is_human);
	
	// getters, setters
	std::string get_name() const {return name_; }
	int get_points() const {return points_; }
	Position get_position() const {return pos_; }
	bool is_human() const {return is_human_; }

	void ChangePoints(const int x);  

	// set a new position for this player
	void SetPosition(Position pos);

private:
	std::string name_;
	int points_;
	Position pos_;
	bool is_human_;

}; // class Player

#endif  // PLAYER_H
