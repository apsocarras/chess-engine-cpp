#pragma once
#include <array>
#include <bitset>
#include <cstddef>
#include <string_view>

// using BitBoard = std::bitset<sizeof(unsigned long long)>; // think this uses size of a pointer to unsigned long long


enum class Rank {
    first, second, third, fourth, fifth, sixth, seventh, eighth, NUM_RANKS
};
constexpr std::array<char, static_cast<size_t>(Rank::NUM_RANKS)> rank_chars {
    '1', '2', '3', '4', '5', '6', '7', '8' 
};
enum class File {
    A, B, C, D, E, F, G, H, NUM_FILES
};
constexpr std::array<char, static_cast<size_t>(File::NUM_FILES)> file_chars {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};
constexpr std::array<std::string_view, static_cast<size_t>(File::NUM_FILES)> underlined_files {
    "a\u0332",
    "b\u0332",
    "c\u0332",
    "d\u0332",
    "e\u0332",
    "f\u0332",
    "g\u0332",
    "h\u0332"
};


constexpr auto N_Ranks { 8 };
constexpr auto N_Files { 8 };


constexpr bool EmptySquare { 0 };
constexpr bool OccupiedSquare { 1 };


using BitBoard = std::bitset<64>;
using Rank_t = std::size_t;
using File_t = std::size_t;

