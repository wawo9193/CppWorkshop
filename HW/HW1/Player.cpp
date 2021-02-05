#include "Player.h"

#include <iostream>

// methods
Player::Player(const std::string name, const bool is_human): name_(name), points_(0), pos_(Position{0,0}), is_human_(is_human) {}

void Player::ChangePoints(const int x) {
    this->points_ += x;
}

void Player::SetPosition(Position pos) {
    this->pos_ = pos;
}

// std::string Player::ToRelativePosition(Position other) {
//     if (other.get_cols()>4 || other.get_rows()>4) return "you shall not pass";
//     if (this->pos_==other) return "stay";

//     std::vector<int> diff = other - this->pos_;
//     if (diff[0]<0) return "down";
//     if (diff[0]>0) return "up";
//     if (diff[1]<0) return "left";
//     if (diff[1]>0) return "right";

//     return "shaddup";
// }

// std::ostream& operator<<(std::ostream& os, Player& p) {
//     os << "Name: " << this->name_ << "\tPoints: " << this->points_ << "\n";
//     return os;
// }
