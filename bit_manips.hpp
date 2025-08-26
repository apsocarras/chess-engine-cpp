#pragma once

#include "bbc_types.hpp"
#include <algorithm>
#include <type_traits>

template <typename BoardType>
class BitBoardView {
    private: 
        std::reference_wrapper<BoardType> m_bitboard;
    public:
        BitBoardView(BoardType& bb) : m_bitboard { bb } {};

        auto operator()(int rank, int file) -> decltype(auto) { 
            // Video implementation w/ shifting: bitboard & (1ULL << (rank * 8 + file))
            return m_bitboard.get()[
                static_cast<std::size_t>(rank * N_Ranks + file)
            ];        
        }
        auto operator()(int rank, int file) const -> decltype(auto)  { 
            return m_bitboard.get()[
                static_cast<std::size_t>(rank * N_Ranks + file)
            ];        
        }
        auto operator<<(std::size_t n) const -> decltype(auto) {
            return m_bitboard.get() << n;
        }
        auto operator>>(std::size_t n) const -> decltype(auto) {
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

};

template <typename BoardType>
void print_bitboard(const BitBoardView<BoardType>& bitboard) {

    // Print files 
    std::cout << "   ";
    for (int index {0}; index < N_Files; ++index) {
        std::cout << file_chars[index];
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