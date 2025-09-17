/**
 * @file Player.cpp
 * @brief Implementation of the Player class and related functions.
 */

#include "Player.h"

#include <algorithm>

Player* Player_factory(std::string const name, short const round) {
    return new ComputerPlayer(name, round);
}
