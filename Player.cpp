/**
 * @file Player.cpp
 * @brief Implementation of the Player class and related functions.
 */

#include "Player.h"

#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @class HumanPlayer
 * @brief Implements the Player interface.
 */
class HumanPlayer : public Player {
private:
    string name;
    vector<Card> hand;

public:
    HumanPlayer(string const& name_in)
        : name(name_in) {}

    string const& get_name() const override { return name; }

    vector<Card> const& get_hand() const override { return hand; }

    void add_card(Card const& c) override { hand.push_back(c); }

    Card play_card() override {
        if (hand.empty()) {
            throw out_of_range("No cards to play.");
        }
        Card played = hand.back();
        hand.pop_back();
        return played;
    }
};


/**
 * @class ComputerPlayer
 * @brief Implements a Computer strategy for the Player.
 */
class ComputerPlayer : public Player {
private:
    string name;
    vector<Card> hand;

public:
    ComputerPlayer(string const& name_in)
        : name(name_in) {}

    string const& get_name() const override { return name; }

    vector<Card> const& get_hand() const override { return hand; }

    void add_card(Card const& c) override { hand.push_back(c); }

    Card play_card() override {
        if (hand.empty()) {
            throw out_of_range("No cards to play.");
        }
        Card played = hand.back();
        hand.pop_back();
        return played;
    }
};


Player* Player_factory(string const& name, string const& strategy) {
    if (strategy == "Computer") {
        return new ComputerPlayer(name);
    } else if (strategy == "Human") {
        return new HumanPlayer(name);
    } else {
        return nullptr;
    }
}

ostream& operator<<(ostream& os, Player const& p) {
    os << p.get_name();
    os << "'s hand: " << endl;
    for (auto const& card : p.get_hand()) {
        os << card << endl;
    }
    os << endl;
    return os;
}
