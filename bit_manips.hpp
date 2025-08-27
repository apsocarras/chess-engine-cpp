#pragma once

#include "bbc_types.hpp"
#include <iostream>
#include <type_traits>

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
        auto& board()  {
            return m_bitboard.get();
        }
        // pop_bit() method - use .board().flip()
            // video: get_bit(bitboard, square) ? bitboard ^= (1ULL << e4) : ;
};

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
        std::cout << ranks[static_cast<std::size_t>(rank)] << '|';
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