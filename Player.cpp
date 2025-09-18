/**
 * @file Player.cpp
 * @brief Implementation of the Player class and related functions.
 */

#include "Player.h"

#include <algorithm>

Player* Player_factory(std::string name, short round) {
    return new ComputerPlayer(std::move(name), std::move(round));
}
