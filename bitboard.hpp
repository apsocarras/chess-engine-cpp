#pragma once

#include "board_types.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <bitset>

using BitBoard = std::bitset<N_Squares>;

template <typename BoardType>
class BitBoardView {
    // Templatized primarily for const/non-const bit boards 
        // decltype(auto) preserves the reference_wrapper
        // depends on BoardType (std::bitset::reference vs std::bitset::const_reference)
    private: 
        std::reference_wrapper<BoardType> m_bitboard;
    public:
        BitBoardView(BoardType& bb) : m_bitboard { bb } {};

        auto operator()(Square square) -> decltype(auto)  {
            return m_bitboard.get()[static_cast<std::size_t>(square)]; // allow assignment
        }
        constexpr bool operator()(Square square) const { 
            return m_bitboard.get().test(square);
        }
        auto operator()(int rank, int file) -> decltype(auto) { 
            // Video implementation w/ shifting: bitboard & (1ULL << (rank * 8 + file))
            return m_bitboard.get()[static_cast<std::size_t>(rank * 8 + file)]; 
        }
        constexpr bool operator()(int rank, int file) const { 
            return m_bitboard.get().test(rank * 8 + file);
        }
        auto operator<<(std::size_t n) const -> auto {
            return m_bitboard.get() << n;
        }
        auto operator>>(std::size_t n) const -> auto {
            return m_bitboard.get() >> n;
        }
        auto operator<<=(std::size_t n) -> decltype(auto) {
            static_assert(!std::is_const_v<BoardType>, "Cannot shift const board in place");
            return m_bitboard.get() <<= n;
        }
        auto operator>>=(std::size_t n) -> decltype(auto) {
            static_assert(!std::is_const_v<BoardType>, "Cannot shift const board in place");
            return m_bitboard.get() >>= n;
        }

        auto const& board() const {
            return m_bitboard.get();
        }
        auto board() -> decltype(auto) {
            return m_bitboard.get();
        }
        // pop_bit() method - use .board().flip()
            // video: get_bit(bitboard, square) ? bitboard ^= (1ULL << e4) : ;

        auto set(Square square)  {
            auto index { static_cast<size_t>(square)};
            m_bitboard.get().set(index);
        }

};

constexpr BitBoard fill_bitboard(bool(*keep_condition)(int rank, int file)) {
    // Using to precreate mask constants. Fine if unnecessarily checking all files in skipped ranks.
    uint64_t mask = 0;
    for (std::size_t rank = 0; rank < 8; ++rank) {
        for (std::size_t file = 0; file < 8; ++file) {
            if (keep_condition(rank, file)) {
                auto index = rank * 8 + file;
                mask |= (1ULL << index);
            }
        }
    }
    return BitBoard{mask};
}

template <typename BoardType>
void print_bitboard(const BitBoardView<BoardType>& bitboard) {

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
    std::cout << '\n' << "  " << "Decimal: " << bitboard.board().to_ullong() << '\n';
}

inline void print_bitboard(const BitBoard& bitboard) {
    BitBoardView<const BitBoard> view { bitboard };
    print_bitboard(view);
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
        ^ 
      <   >
        v
    */

    
}

namespace masks {
    namespace files {
        constexpr auto not_A_file { fill_bitboard([](int rank, int file) constexpr { return file != 0; }) };
        constexpr auto not_H_file { fill_bitboard([](int rank, int file) constexpr { return file != 7; }) };
        constexpr auto not_HG_file { fill_bitboard([](int rank, int file) constexpr { return file < 6; }) };
        constexpr auto not_AB_file { fill_bitboard([](int rank, int file) constexpr { return file > 1; }) };
    }

    namespace ranks {
        constexpr auto not_1st_rank { fill_bitboard([](int rank, int file) constexpr { return rank != 0; }) };
        constexpr auto not_8th_rank { fill_bitboard([](int rank, int file) constexpr { return rank != 7; }) };
        constexpr auto not_1st2ndrank { fill_bitboard([](int rank, int file) constexpr { return rank > 1; }) };
        constexpr auto not_7th8th_rank { fill_bitboard([](int rank, int file) constexpr { return rank < 6; }) };
    }

    namespace attacks { 
        constexpr BitBoard get_pawn_attacks(Square square, Color color) {
            BitBoard bb {1ULL << static_cast<size_t>(square)};
            if (color == Color::white) {
                return (bb << 7 & files::not_A_file) | (bb << 9 & files::not_H_file); 
            } else {
                return (bb >> 7 & files::not_A_file) | (bb >> 9 & files::not_H_file); 
            }
        }
        template <size_t N>
        constexpr std::array<BitBoard, N >get_pawn_attacks(const std::array<Square, N>& squares, Color color) { 
            std::array<BitBoard, N> bitboards {};
            std::transform(squares.begin(), squares.end(), bitboards.begin(),
            [=](Square square) constexpr {
                return get_pawn_attacks(square, color);
            });
            return bitboards;
        }
    }
}
namespace attack_tables {
    constexpr std::array<std::array<BitBoard, N_Squares>, 2> pawn_attacks {
        masks::attacks::get_pawn_attacks<N_Squares>(squares_enum, Color::white), 
        masks::attacks::get_pawn_attacks<N_Squares>(squares_enum, Color::black)
    };
}



            // std::transform(squares.begin(), squares.end(), bitboards.begin(),
            //     [](Square square) constexpr {
            //         return get_pawn_attacks<BitBoardType, color>(square);
            //     });
