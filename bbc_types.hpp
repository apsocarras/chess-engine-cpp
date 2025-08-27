#pragma once
#include <array>
#include <bitset>
#include <cstddef>
#include <string_view>
#include <iostream>
// using BitBoard = std::bitset<sizeof(unsigned long long)>; // think this uses size of a pointer to unsigned long long

constexpr auto N_Ranks { 8 };
constexpr auto N_Files { 8 };
constexpr auto N_Squares { N_Ranks * N_Files};

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

enum class Square {
    a1, a2, a3, a4, a5, a6, a7, a8,
    b1, b2, b3, b4, b5, b6, b7, b8,
    c1, c2, c3, c4, c5, c6, c7, c8,
    d1, d2, d3, d4, d5, d6, d7, d8,
    e1, e2, e3, e4, e5, e6, e7, e8,
    f1, f2, f3, f4, f5, f6, f7, f8,
    g1, g2, g3, g4, g5, g6, g7, g8,
    h1, h2, h3, h4, h5, h6, h7, h8,
};
constexpr std::array<std::string_view,static_cast<std::size_t>(N_Squares)> squares {
    "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
    "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
    "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
    "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
    "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
    "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
    "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
    "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8"
};

template<bool reversed>
constexpr void print_squares() {
    auto print_rows {
        [](auto begin, auto end){
            std::for_each(begin, end, [](const char& c){
                for (int i{1}; i <= 8; ++i) {
                    std::cout << c << i;
                    if (i != 8) std::cout <<',' << ' ';
                }
                std::cout << '\n';
            });
        }
    };
    if constexpr (reversed) {
        print_rows(file_chars.rbegin(), file_chars.rend());
    } else {
        print_rows(file_chars.begin(), file_chars.end());
    }
};


const std::string_view to_string(Square square) {
    return squares[static_cast<std::size_t>(square)];
}
char to_char(Rank rank) {
    return rank_chars[static_cast<std::size_t>(rank)];
}
char to_char(File file) {
    return file_chars[static_cast<std::size_t>(file)];
}


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




constexpr bool EmptySquare { 0 };
constexpr bool OccupiedSquare { 1 };


using BitBoard = std::bitset<64>;
using Rank_t = std::size_t;
using File_t = std::size_t;

