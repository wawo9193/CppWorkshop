#include "Maze.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>

std::string SquareTypeStringify(SquareType sq) {
    // { Wall=0, Exit, Empty, Human, Enemy, Treasure };
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
    std::unordered_map<std::string, Position> output_map;
    std::vector<Position> output;

    int i = pos.row, j = pos.col;
    output_map["up"]    = Position{i-1, j};
    output_map["down"]  = Position{i+1, j};
    output_map["left"]  = Position{i, j-1};
    output_map["right"] = Position{i, j+1};

    for (auto it = output_map.begin(); it!=output_map.end();) {
        SquareType st = get_square_value(it->second);

        if (st==SquareType::Wall || st==SquareType::Enemy) {
            output_map.erase(it++);
        } else {
            ++it;
        }
    }
    return output_map;
}

// Move a player to a new position on the board. Return
// true if they moved successfully, false otherwise.
bool Board::MovePlayer(Player *p, std::unordered_map<std::string, Position> pos_map, std::string key) {
    Position player_pos = p->get_position();
    Position next_pos = pos_map[key];

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

// Get the square type of the exit square
SquareType Board::GetExitOccupant() {
    return get_square_value(Position{this->get_rows()-1, this->get_cols()-1});
}

std::ostream& operator<<(std::ostream& os, const Board &b) {
    for (int i=0, m=b.get_rows(); i<m; ++i) {
        for (int j=0, n=b.get_cols(); j<n; ++j) {
            os << SquareTypeStringify(b.get_square_value(Position{i,j})) << "\t";
        }
        os << "\n\n";
    }
    return os;
}

Maze::Maze(Player *human) {
    human->SetPosition(Position{0,0});

    while (!ValidBoard()) {}

    std::vector<Player *> enemies_v = this->board_->get_enemies();

    this->players_.push_back(human);
    this->players_.insert(this->players_.end(), enemies_v.begin(), enemies_v.end());
}

// initialize a new game, given one human player and 
// a number of enemies to generate
void Maze::NewGame() {
    std::cout << *this->board_ << std::endl;
    while(!IsGameOver()) {
        for (Player *p : this->players_) {
            TakeTurn(p);

            if (IsGameOver()) break;
        }
    }
    GenerateReport();
}

bool IsValid(Board *b, std::vector<std::vector<bool> > v, Position p) {
    // get all possible moves
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
    // init enemy count on board, board, visited array, and return if valid
    int enemy_count = (rand() % 3) + 2; // 2-4 enemies
    this->board_ = new Board(enemy_count, 4, 4);
    std::vector<std::vector<bool> > visited(4, std::vector<bool>(4, false));
    return IsValid(this->board_, visited, Position{0,0});
}

// have the given Player take their turn
void Maze::TakeTurn(Player *p) {
    std::unordered_map<std::string, Position> pos_map = this->board_->GetMoves(p->get_position());
    std::string input;
    bool has_moved = false;

    std::cout << p->get_name() << " can go: ";
    for (auto it : pos_map) {
        std::cout << it.first << " ";
    }
    std::cout << std::endl << "Please enter your choice: ";
    std::cin >> input;
    for (char c : input) c = tolower(c);

    if (pos_map.find(input)!=pos_map.end()) {
        has_moved = this->board_->MovePlayer(p, pos_map, input);
    } else {
        std::cout << "Player stayed" << std::endl;
    }

    std::cout << *this->board_ << std::endl;
}

// return true if the human made it to the exit 
// or the enemies ate all the humans
bool Maze::IsGameOver() {
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

// string info about the game's conditions after it is over
std::string Maze::GenerateReport() {
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
