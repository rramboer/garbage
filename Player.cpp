/**
 * @file Player.cpp
 * @brief Implementation of the Player class and related functions.
 */

#include "Player.h"

#include <algorithm>
#include <iostream>

using namespace std;

Player* Player_factory(string const& name, short const& round) {
    return new ComputerPlayer(name, round);
}

ostream& operator<<(ostream& os, Player const& p) {
    os << p.get_name() << endl;
    os << "Round: " << p.get_round() << endl;
    return os;
}
