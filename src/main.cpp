/**
 * @file main.cpp
 * @brief Command-line entry point for the Garbage card game simulation.
 */

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <memory>
#include <optional>
#include <print>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "Game.h"
#include "Player.h"
#include "const.h"

namespace {

/**
 * @brief Parses an entire string as a base-10 integer.
 * @return The parsed value, or std::nullopt if the string is not a valid integer.
 */
std::optional<int> parse_int(std::string_view text) {
    int value = 0;
    // std::from_chars requires a [first, last) char pointer range; this is its canonical usage.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto const* const last = text.data() + text.size();
    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
    auto const [ptr, ec] = std::from_chars(text.data(), last, value);
    if (ec != std::errc {} || ptr != last) {
        return std::nullopt;
    }
    return value;
}

void print_usage(std::string_view program_name) {
    std::println(stderr, "Usage: {} num_players starting_round shuffle_enabled", program_name);
}

}

int main(int argc, char* argv[]) try {
    auto const args = std::span(argv, static_cast<size_t>(argc));

    if (args.size() != 4) {
        print_usage(args.empty() ? "garbage" : args[0]);
        return 1;
    }

    auto const num_players = parse_int(args[1]);
    auto const starting_round = parse_int(args[2]);
    if (!num_players.has_value() || !starting_round.has_value()) {
        std::println(stderr, "num_players and starting_round must be integers");
        print_usage(args[0]);
        return 1;
    }

    if (*num_players < 1 || *num_players > Config::MAX_PLAYER_COUNT) {
        std::println(stderr, "num_players must be between 1 and {}", Config::MAX_PLAYER_COUNT);
        return 1;
    }

    if (*starting_round < 1 || *starting_round > Config::MAX_STARTING_ROUND) {
        std::println(stderr, "starting_round must be between 1 and {}", Config::MAX_STARTING_ROUND);
        return 1;
    }

    std::string shuffle_enabled_in(args[3]);
    std::ranges::transform(shuffle_enabled_in, shuffle_enabled_in.begin(),
                           [](unsigned char c) { return std::tolower(c); });
    bool const shuffle_enabled
        = (shuffle_enabled_in == "true" || shuffle_enabled_in == "1" || shuffle_enabled_in == "t");

    std::vector<std::unique_ptr<Player>> players;
    players.reserve(static_cast<size_t>(*num_players));
    for (int i = 0; i < *num_players; ++i) {
        players.push_back(Player_factory("Player " + std::to_string(i + 1), *starting_round));
    }

    Game game(std::move(players), shuffle_enabled);
    game.run();

    return 0;
} catch (std::exception const& e) {
    // std::fputs cannot throw, so errors cannot escape main.
    std::fputs("Fatal error: ", stderr);
    std::fputs(e.what(), stderr);
    std::fputs("\n", stderr);
    return 1;
}
