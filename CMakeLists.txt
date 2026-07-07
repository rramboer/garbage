cmake_minimum_required(VERSION 3.28)

project(garbage
    DESCRIPTION "A modern C++ engine for the card game Garbage (Trash)"
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings are applied per target so that fetched third-party code is not built with -Werror.
set(GARBAGE_WARNINGS -Wall -Wextra -Werror -pedantic)

add_library(garbage_lib STATIC
    src/Card.cpp
    src/Deck.cpp
    src/Game.cpp
    src/Hand.cpp
    src/Player.cpp)
target_include_directories(garbage_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(garbage_lib PUBLIC cxx_std_23)
target_compile_options(garbage_lib PRIVATE ${GARBAGE_WARNINGS})

add_executable(garbage src/main.cpp)
target_link_libraries(garbage PRIVATE garbage_lib)
target_compile_options(garbage PRIVATE ${GARBAGE_WARNINGS})

install(TARGETS garbage RUNTIME DESTINATION bin)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 56809e5282f104c5c8b570e7c2996cdc352d94f1 # v3.8.1
        SYSTEM)
    FetchContent_MakeAvailable(Catch2)

    add_executable(garbage_tests
        tests/test_card.cpp
        tests/test_deck.cpp
        tests/test_hand.cpp
        tests/test_player.cpp)
    target_link_libraries(garbage_tests PRIVATE garbage_lib Catch2::Catch2WithMain)
    target_compile_options(garbage_tests PRIVATE ${GARBAGE_WARNINGS})

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(garbage_tests)

    # End-to-end smoke tests of the CLI binary.
    add_test(NAME smoke.full_game COMMAND garbage 2 3 true)
    add_test(NAME smoke.full_game_no_shuffle COMMAND garbage 2 3 false)
    add_test(NAME smoke.rejects_non_numeric_args COMMAND garbage abc 3 true)
    add_test(NAME smoke.rejects_out_of_range_args COMMAND garbage 9 3 true)
    add_test(NAME smoke.rejects_missing_args COMMAND garbage)
    set_tests_properties(
        smoke.rejects_non_numeric_args
        smoke.rejects_out_of_range_args
        smoke.rejects_missing_args
        PROPERTIES WILL_FAIL TRUE)
endif()
