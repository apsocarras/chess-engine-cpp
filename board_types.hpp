#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <iostream>
// using BitBoard = std::bitset<sizeof(unsigned long long)>; // think this uses size of a pointer to unsigned long long


enum class Color {
    white, black
};

constexpr auto N_Ranks { 8ULL };
constexpr auto N_Files { 8ULL };
constexpr auto N_Squares { N_Ranks * N_Files};

constexpr bool EmptySquare { 0 };
constexpr bool OccupiedSquare { 1 };

constexpr std::array<char, N_Ranks> rank_chars {
    '1', '2', '3', '4', '5', '6', '7', '8' 
};
constexpr std::array<char, static_cast<size_t>(N_Files)> file_chars {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};
constexpr std::array<std::string_view, N_Files> underlined_files {
    "a\u0332",
    "b\u0332",
    "c\u0332",
    "d\u0332",
    "e\u0332",
    "f\u0332",
    "g\u0332",
    "h\u0332"
};


enum class Square : std::size_t {
    a1, a2, a3, a4, a5, a6, a7, a8,
    b1, b2, b3, b4, b5, b6, b7, b8,
    c1, c2, c3, c4, c5, c6, c7, c8,
    d1, d2, d3, d4, d5, d6, d7, d8,
    e1, e2, e3, e4, e5, e6, e7, e8,
    f1, f2, f3, f4, f5, f6, f7, f8,
    g1, g2, g3, g4, g5, g6, g7, g8,
    h1, h2, h3, h4, h5, h6, h7, h8,
};


constexpr Square make_square(int rank, int file) {
    return static_cast<Square>(rank * 8 + file);
}

void print_squares(Color perspective) {
    // Prints the squares based on the files and then numbers 1 through 8. 
    // Used to generate the square array 
    auto print_ranks {
        [](auto begin, auto end){
            std::ranges::for_each(begin, end, [](const char rc) constexpr {
                for (const auto& fc : file_chars) {
                    std::cout << fc << rc;
                    if (fc != 'h') std::cout <<',' << ' ';
                }
                std::cout << '\n';
            });
        }
    };
    
    if (perspective == Color::white) {
        print_ranks(rank_chars.rbegin(), rank_chars.rend());
    } else {
        print_ranks(rank_chars.begin(), rank_chars.end());
    }
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
constexpr std::array<Square,static_cast<std::size_t>(N_Squares)> squares_enum {
    Square::a1, Square::a2, Square::a3, Square::a4, Square::a5, Square::a6, Square::a7, Square::a8,
    Square::b1, Square::b2, Square::b3, Square::b4, Square::b5, Square::b6, Square::b7, Square::b8,
    Square::c1, Square::c2, Square::c3, Square::c4, Square::c5, Square::c6, Square::c7, Square::c8,
    Square::d1, Square::d2, Square::d3, Square::d4, Square::d5, Square::d6, Square::d7, Square::d8,
    Square::e1, Square::e2, Square::e3, Square::e4, Square::e5, Square::e6, Square::e7, Square::e8,
    Square::f1, Square::f2, Square::f3, Square::f4, Square::f5, Square::f6, Square::f7, Square::f8,
    Square::g1, Square::g2, Square::g3, Square::g4, Square::g5, Square::g6, Square::g7, Square::g8,
    Square::h1, Square::h2, Square::h3, Square::h4, Square::h5, Square::h6, Square::h7, Square::h8
};


constexpr std::string_view to_string(Square square) {
    return squares[static_cast<std::size_t>(square)];
}
constexpr char char_rank(int rank) {
    return rank_chars[static_cast<std::size_t>(rank)];
}
constexpr char char_file(int file) {
    return file_chars[static_cast<std::size_t>(file)];
}
