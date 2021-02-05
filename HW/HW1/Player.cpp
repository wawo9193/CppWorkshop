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
