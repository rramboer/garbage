/**
 * @file Player.cpp
 * @brief Implementation of the Player class and related functions.
 */

#include "Player.h"

#include <memory>
#include <string>
#include <utility>

std::unique_ptr<Player> Player_factory(std::string name, int round) {
    return std::make_unique<ComputerPlayer>(std::move(name), round);
}
