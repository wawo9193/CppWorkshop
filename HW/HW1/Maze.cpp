#include "Maze.h"

#include <iostream>
#include <random>
#include <string>
#include <vector>

std::string SquareTypeStringify(SquareType sq) {
    /*
    * All SquareType Enums:
    * { Wall=0, Exit, Empty, Human, Enemy, Treasure };
    */
    std::unordered_map<SquareType, std::string> emo_map = {
        { SquareType::Wall, "🟫 " },
        { SquareType::Exit, "🚪" },
        { SquareType::Empty, " " },
        { SquareType::Human, "🦹‍" },
        { SquareType::Enemy, "👾" },
        { SquareType::Treasure, "💎" }
    };
	return emo_map[sq];
}

Board::Board(int enemy_count, const int m, const int n): 
    vec_(std::vector<std::vector<SquareType> >(m, std::vector<SquareType>(n, SquareType::Empty))), 
    rows_(m), 
    cols_(n) {

    // Goes through the entire board (2d vec) and places their square type
    // based on certain parameters. i.e. human is always (0,0), etc.
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (!i && !j) {
                SetSquareValue(Position{i,j}, SquareType::Human);
            } else if (i==m-1 && j==n-1) {
                SetSquareValue(Position{i,j}, SquareType::Exit);
            } else {
                int r = (rand() % 100) + 1;
                if (r<=20) {
                    SetSquareValue(Position{i,j}, SquareType::Wall);
                } else {
                    r = (rand() % 100) + 1;
                    if (r<=10) {
                        SetSquareValue(Position{i,j}, SquareType::Treasure);
                    } else {
                        SetSquareValue(Position{i,j}, SquareType::Empty);
                    }
                }
            }
        }
    }

    // Places all of the enemies onto the board starting from top right.
    // Also adds them to the players vector that is a part of Board class.
    for (int i=0; i<m; ++i) {
        for (int j=n-1; j>0; --j) {
            
            if (enemy_count && 
                get_square_value(Position{i,j})!=SquareType::Wall &&
                get_square_value(Position{i,j})!=SquareType::Exit) {
                    Player *p = new Player("borg" + std::to_string(enemy_count), false);
                    p->SetPosition(Position{i,j});
                    SetSquareValue(Position{i,j}, SquareType::Enemy);
                    this->enemies_v_.push_back(p);
                    --enemy_count;
                }
        }
    }
}

void Board::SetSquareValue(Position pos, SquareType value) {
    this->vec_[pos.row][pos.col] = value;
}

SquareType Board::get_square_value(Position pos) const {
    if (pos.row<0 || pos.col<0 || pos.row>=this->get_rows() || pos.col>=this->get_cols()) 
        return SquareType::Wall;
    return this->vec_[pos.row][pos.col];
}

std::vector<Player *> Board::get_enemies() const {
    return this->enemies_v_;
}

std::unordered_map<std::string, Position> Board::GetMoves(Position pos) {
    /*
    * Params:
    *   pos - this is the position object relative to the board
    * 
    * Functionality:
    *   Takes in the position on the board and looks at all relative positions
    *   to the passed in position. If there is a Wall (either wall or out of bounds),
    *   or an enemy then erase that possiblity from map of moves.
    */

    std::unordered_map<std::string, Position> moves;

    int i = pos.row, j = pos.col;
    moves["up"]    = Position{i-1, j};
    moves["down"]  = Position{i+1, j};
    moves["left"]  = Position{i, j-1};
    moves["right"] = Position{i, j+1};

    for (auto it = moves.begin(); it!=moves.end();) {
        SquareType st = get_square_value(it->second);

        if (st==SquareType::Wall || st==SquareType::Enemy) {
            moves.erase(it++);
        } else {
            ++it;
        }
    }
    return moves;
}

bool Board::MovePlayer(Player *p, std::unordered_map<std::string, Position> moves, std::string key) {
    /*
    * Params:
    *   p - the player that will be moved, whether enemy or human.
    *   moves - the moves that are allowable for the current player.
    *   key - a certain direction, i.e. "left", "right", etc.
    * 
    * Functionality:
    *   To move the passed in player to a new position on the board, based on a string input `key`
    *   Then handles the move by changing squaretypes as needed.
    */ 

    Position player_pos = p->get_position();
    Position next_pos = moves[key];

    // increment points if treasure
    if (get_square_value(next_pos)==SquareType::Treasure) p->ChangePoints(1);

    // get prev square val
    SquareType player = get_square_value(player_pos);
    
    // if player is at exit don't erase exit square
    if (player_pos.row==get_rows()-1 && player_pos.col==get_cols()-1) {
        SetSquareValue(player_pos, SquareType::Exit);
    } else {
        SetSquareValue(player_pos, SquareType::Empty);
    }

    // move player square val to new pos
    SetSquareValue(next_pos, player);
    p->SetPosition(next_pos);

    return false;
}

SquareType Board::GetExitOccupant() {
    /* 
    * Functionality:
    *   Get the squaretype of the exit square, this could signify end of game. 
    */
    return get_square_value(Position{this->get_rows()-1, this->get_cols()-1});
}

std::ostream& operator<<(std::ostream& os, const Board &b) {
    /* 
    * Functionality:
    *   Overloads stream operator to show board state. 
    */

    for (int i=0, m=b.get_rows(); i<m; ++i) {
        for (int j=0, n=b.get_cols(); j<n; ++j) {
            os << SquareTypeStringify(b.vec_[i][j]) << "\t";
        }
        os << "\n\n";
    }
    return os;
}

Maze::Maze(Player *human) {
    human->SetPosition(Position{0,0});

    // find valid board
    while (!ValidBoard()) {}

    std::vector<Player *> enemies_v = this->board_->get_enemies();

    this->players_.push_back(human);
    this->players_.insert(this->players_.end(), enemies_v.begin(), enemies_v.end());
}

bool IsValid(Board *b, std::vector<std::vector<bool> > v, Position p) {
    /*
    * Params:
    *   b - the board which we are checking if is valid.
    *   v - the board laid out in booleans to mark visited.
    *   p - the current position being checked.
    * 
    * Functionality:
    *   This helper function is a DFS implementation where it looks for a valid path
    *   from {0,0} (Human position) to the exit {3,3}.
    */

    // get valid moves
    std::unordered_map<std::string, Position> moves = b->GetMoves(p);
    int i = p.row, j = p.col;

    if (moves.empty() || v[i][j]) return false; // restricted on all sides or visited
    if (i==3 && j==3) return true; // found exit

    v[i][j] = true; // set to visited
    int res = 0;

    for (auto it : moves) {
        // collects any 'true' value when exit is found
        res += IsValid(b, v, it.second);
    }

    // bool return of int defaults to 0 or 1
    return res;
}

bool Maze::ValidBoard() {
    /* 
    * Functionality:
    *   Creates a board and checks for it's validity (possible path to exit) using helper, `IsValid` 
    */

    int enemy_count = (rand() % 3) + 2; // 2-4 enemies
    this->board_ = new Board(enemy_count, 4, 4);
    std::vector<std::vector<bool> > visited(4, std::vector<bool>(4, false));

    return IsValid(this->board_, visited, Position{0,0});
}

void Maze::NewGame() {
    /* init new game and loop until `IsGameOver` returns true */

    std::cout << *this->board_ << std::endl;
    while(!IsGameOver()) {
        // players vec = {human, enemy_1, ..., enemy_n}
        for (Player *p : this->players_) {
            TakeTurn(p);

            if (IsGameOver()) break;
        }
    }
}

void Maze::TakeTurn(Player *p) {
    /*
    * Params:
    *   p - the player whose turn it is.
    * 
    * Functionality:
    *   This function searches for valid moves with `GetMoves` at the current position,
    *   then it outputs what moves are valid. From here it asks and retrieves console input
    *   for the user's move choice. If the move stated by the player isn't in the valid moves
    *   map, then it will default to staying put. An updated board is printed afterwards.
    */ 

    std::unordered_map<std::string, Position> moves = this->board_->GetMoves(p->get_position());
    std::string input;

    std::cout << p->get_name() << " can go: ";
    for (auto it : moves) {
        std::cout << it.first << " ";
    }
    std::cout << std::endl << "Please enter your choice: ";
    std::cin >> input;
    for (char c : input) c = tolower(c);

    if (moves.find(input)!=moves.end()) {
        this->board_->MovePlayer(p, moves, input);
    } else {
        std::cout << "Player stayed" << std::endl;
    }

    std::cout << *this->board_ << std::endl;
}

bool Maze::IsGameOver() {
    /*
    * Functionality:
    *   Checks if:
    *       - Human is at exit
    *       - No valid moves are available for Human
    *       - Checks if any enemies are at Human position  
    *   Returns true if so, else false.
    */

    Player* human = this->players_.front();
    Position human_pos = human->get_position();
    int col_max = this->board_->get_cols();
    int row_max = this->board_->get_rows();

    if (human_pos.col==col_max-1 && human_pos.row==row_max-1) return true;
    if (this->board_->GetMoves(human->get_position()).empty()) return true;

    for (int i=1, n=this->players_.size(); i<n; ++i) {
        Position enemy_pos = this->players_.at(i)->get_position();

        if (human_pos==enemy_pos) return true;
    }

    return false;
}

std::string Maze::GenerateReport() {
    /*
    * Functionality:
    *   Gathers a solid string output of the game's state after game is over,
    *   delimits using '$' char.
    */

    std::string output;

    if (this->board_->GetExitOccupant()==SquareType::Human) {
        output += "$Congratulations, you reached the exit!$";
    } else {
        output += "$Game Over!$";
    }
    
    for (Player *p : this->players_) {
        output += "$" + p->get_name() + " Total Points: " + std::to_string(p->get_points()) + "$";
    }
    return output;
}

Maze::~Maze() {
    delete this->board_;
}
