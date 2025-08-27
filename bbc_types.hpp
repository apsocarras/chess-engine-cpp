#pragma once
#include <array>
#include <bitset>
#include <cstddef>
#include <functional>
#include <string_view>
#include <iostream>
#include <type_traits>
// using BitBoard = std::bitset<sizeof(unsigned long long)>; // think this uses size of a pointer to unsigned long long

constexpr auto N_Ranks { 8 };
constexpr auto N_Files { 8 };
constexpr auto N_Squares { N_Ranks * N_Files};

using BitBoard = std::bitset<N_Squares>;

constexpr bool EmptySquare { 0 };
constexpr bool OccupiedSquare { 1 };

constexpr std::array<char, N_Ranks> ranks {
    '1', '2', '3', '4', '5', '6', '7', '8' 
};
constexpr std::array<char, static_cast<size_t>(N_Files)> files {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
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

constexpr Square make_square(int rank, int file) {
    return static_cast<Square>(rank * 8 + file);
}

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
        print_rows(files.rbegin(), files.rend());
    } else {
        print_rows(files.begin(), files.end());
    }
};


const std::string_view to_string(Square square) {
    return squares[static_cast<std::size_t>(square)];
}
char char_rank(int rank) {
    return ranks[static_cast<std::size_t>(rank)];
}
char char_file(int file) {
    return files[static_cast<std::size_t>(file)];
}


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

template <typename RankFileFilter>
constexpr BitBoard fill_bitboard(RankFileFilter filter_off) {
    BitBoard bitboard {};
    for (std::size_t rank{}; rank < 8; ++rank) {
        for (std::size_t file{}; file < 8; ++file) {
            if (!filter_off(rank, file)) {
                auto index {rank * 8 + file};
                bitboard.set(index);
            }
        }
    }
    return bitboard;    
}



namespace mask_constants {
    auto not_in_A_file { fill_bitboard([](int rank, int file) { return file == 0; }) };
    auto not_in_H_file { fill_bitboard([](int rank, int file) { return file != 7; }) };
    auto not_in_HG_file { fill_bitboard([](int rank, int file) { return file < 6; }) };
    auto not_AB_file { fill_bitboard([](int rank, int file) { return file > 1; }) };
    
    
}