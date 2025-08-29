#pragma once

#include "board_types.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <type_traits>
#include <bitset>


template <typename BoardType>
class BitBoard {
    // Templatized to support const/non-const BoardType and std::bitset vs std::uint_64 underlying implementation (BoardType)
    private: 
        BoardType m_bitboard;
    public:
        constexpr BitBoard() : m_bitboard  { BoardType()} {}; 
        explicit constexpr BitBoard(BoardType bb) : m_bitboard { bb } {};

        constexpr BoardType& get() {
            return m_bitboard;
        }
        constexpr const BoardType& get() const {
            return m_bitboard;
        }

        constexpr bool get(Square square) const {
            // std::bitset::test
            return m_bitboard & (1ULL << static_cast<std::uint64_t>(square));
        }

        constexpr void set(Square square) {
            m_bitboard |= (1ULL << static_cast<std::uint64_t>(square));
        }

        constexpr void flip(Square square) {
            return m_bitboard ? m_bitboard ^= (1ULL << static_cast<std::uint64_t>(square)) : 0; 
        }

        // Operators
        constexpr BitBoard operator<<(std::size_t n) const { return BitBoard{m_bitboard << n}; }
        constexpr BitBoard operator>>(std::size_t n) const { return BitBoard{m_bitboard >> n}; }
        constexpr BitBoard operator|(const BitBoard& other) const { return BitBoard{m_bitboard | other.get()}; }
        constexpr BitBoard operator&(const BitBoard& other) const { return BitBoard{m_bitboard & other.get()}; }
        constexpr BitBoard operator^(const BitBoard& other) const { return BitBoard{m_bitboard ^ other.get()}; }

        constexpr BitBoard& operator|=(const BitBoard& other) { m_bitboard |= other.get(); return *this; }
        constexpr BitBoard& operator&=(const BitBoard& other) { m_bitboard &= other.get(); return *this; }
        constexpr BitBoard& operator^=(const BitBoard& other) { m_bitboard ^= other.get(); return *this; }
        constexpr BitBoard& operator<<=(std::size_t n) { m_bitboard <<= n; return *this; }
        constexpr BitBoard& operator>>=(std::size_t n) { m_bitboard >>= n; return *this; }

        // Call operator
        constexpr bool operator()(Square square) const { 
            return (*this).get(square);
        }
        constexpr bool operator()(int rank, int file) const { 
            Square square {static_cast<Square>(rank * 8 + file) };
            return (*this).get(square);
        }
};


template <typename BoardType>
void print_bitboard(const BitBoard<BoardType>& bitboard) {

    // Print files 
    std::cout << "   ";
    for (int index {0}; index < N_Files; ++index) {
        std::cout << underlined_files[index];
        if (index < 7)
            std::cout << ' ';
    }   
    std::cout << '\n';
    
    for (int rank{7}; rank >= 0; --rank) {
        std::cout << rank_chars[static_cast<std::size_t>(rank)] << '|';
        for (std::size_t file{0}; file < N_Files; ++file) {
            std::cout << ' ' << bitboard(rank, file);
        }   
        std::cout << '\n';         
    }   
    std::cout << '\n' << "  " << "Decimal: " << bitboard.get() << '\n';
}

inline void print_bitboard(uint64_t bitboard) {
    BitBoard<uint64_t> bb {bitboard};
    print_bitboard(bb);
} 


inline void print_bitboard() {
    // Print empty chessboard 
    for (int rank{0}; rank < 8; rank++) {
        for (int file{0}; file < 8; file++) {
            int square { rank * 8 + file };
            std::cout << " " << square << " ";
        }   
        std::cout << '\n';         
    }    
}

namespace moves {
    /*
    a8, b8, c8, d8, e8, f8, g8, h8.          
    a7, b7, c7, d7, e7, f7, g7, h7        ^ N
    a6, b6, c6, d6, e6, f6, g6, h6.   W <   > E
    a5, b5, c5, d5, e5, f5, g5, h5        v S 
    a4, b4, c4, d4, e4, f4, g4, h4
    a3, b3, c3, d3, e3, f3, g3, h3
    a2, b2, c2, d2, e2, f2, g2, h2
    a1, b1, c1, d1, e1, f1, g1, h1
    */
    enum class Direction : int {
        // N=8,
        // S=-8,
        // E=1,
        // W=-1,
        // NW=7,
        // SW=-7,
        // NE=9, 
        // SE=-9
        N=0,
        E=1,
        W=-1,
        NW=7,
        NE=9, 
        S=-8,
        SW=-9,
        SE=-7
    };
    template <Direction D, std::uint64_t Mask, typename BoardType>
    constexpr BitBoard<BoardType> move(BitBoard<BoardType>& bb) {
        const auto d{ static_cast<int>(D) };
        if constexpr (d > 0) {
            auto foo { (d & Mask)};
            return bb << (d & Mask);
        } else {
            auto foo { (-d) & Mask };
            return bb >> ((-d) & Mask);
        }
    }
}

namespace masks {
    using Mask = std::uint64_t;
    constexpr Mask gen_mask(bool(*keep_condition)(int rank, int file)) {
        // Using to precreate mask constants at compile time. Fine if unnecessarily checking all files in skipped ranks.
        uint64_t mask = 0;
        for (std::size_t rank = 0; rank < 8; ++rank) {
            for (std::size_t file = 0; file < 8; ++file) {
                if (keep_condition(rank, file)) {
                    auto index = rank * 8 + file;
                    mask |= (1ULL << index);
                }
            }
        }
        return mask;
    }

    namespace files {
        constexpr auto not_A_file { gen_mask([](int rank, int file) constexpr { return file != 0; }) };
        constexpr auto not_H_file { gen_mask([](int rank, int file) constexpr { return file != 7; }) };
        constexpr auto not_HG_file { gen_mask([](int rank, int file) constexpr { return file < 6; }) };
        constexpr auto not_AB_file { gen_mask([](int rank, int file) constexpr { return file > 1; }) };
    }

    namespace ranks {
        constexpr auto not_1st_rank { gen_mask([](int rank, int file) constexpr { return rank != 0; }) };
        constexpr auto not_8th_rank { gen_mask([](int rank, int file) constexpr { return rank != 7; }) };
        constexpr auto not_1st2ndrank { gen_mask([](int rank, int file) constexpr { return rank > 1; }) };
        constexpr auto not_7th8th_rank { gen_mask([](int rank, int file) constexpr { return rank < 6; }) };
    }

    namespace attacks { 
        constexpr uint64_t get_pawn_attacks(Square square, Color color) {
            using namespace moves;
            using enum Direction;
            BitBoard<uint64_t> bb {};
            bb.set(square);
            auto bb_bits {bb.get()};
            if (color == Color::white) {
                // return (bb_bits << (7 & files::not_A_file)) | (bb_bits << (9 & files::not_H_file)); 
                return (move<NW, files::not_A_file>(bb) | move<NE, files::not_H_file>(bb)).get(); 
            } else {
                // return (bb_bits >> (7 & files::not_A_file)) | (bb_bits >> (9 & files::not_H_file)); 
                return (move<SW, files::not_A_file>(bb) | move<SE, files::not_H_file>(bb)).get(); 
            }
        }
        template <size_t Num>
        constexpr std::array<BitBoard<uint64_t>,Num> get_pawn_attacks(const std::array<Square, Num>& squares, Color color) { 
            std::array<BitBoard<uint64_t>, Num> bitboards {};
            for (size_t i {}; i < Num; ++i) {
                bitboards[i] = BitBoard<uint64_t>{get_pawn_attacks(squares[i], color)};
            }
            return bitboards;
        }
    }
}
namespace attack_tables {

    constexpr std::array<std::array<BitBoard<uint64_t>, N_Squares>, 2> pawn_attacks {
        masks::attacks::get_pawn_attacks<N_Squares>(squares_enum, Color::white), 
        masks::attacks::get_pawn_attacks<N_Squares>(squares_enum, Color::black)
    };
}


