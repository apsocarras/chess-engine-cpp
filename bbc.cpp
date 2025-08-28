// https://www.youtube.com/watch?v=o-ySJ2EBarY&list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&index=2
// lightly modifying to C++

#include "bitboard.hpp"
#include <atomic>
#include <cstdlib>
#include <random>
#include <iostream>

int main() {
    BitBoard bitboard { };
    std::default_random_engine generator(std::random_device{}()); 
    std::uniform_int_distribution<int> distribution(0,7);
    const std::pair<int, int> rank_file {distribution(generator),distribution(generator)};
    // std::cout << "Randomly selected rank, file: " << rank_file.first << ", " << rank_file.second << '\n';
    const auto square { rank_file.first * N_Ranks + rank_file.second };
    // std::cout << "Square index: " << square << '\n';
    bitboard.set(square);
    print_bitboard(bitboard);
    constexpr bool reversed { false };
    print_squares<reversed>();
    
    std::cout << '\n' << "Not in A File: " << "\n\n";
    print_bitboard(masks::not_A_file);
    std::cout << '\n' << "Not in H File: " << "\n\n"; 
    print_bitboard(masks::not_H_file);
    std::cout << '\n' << "Not in HG File: " << "\n\n"; 
    print_bitboard(masks::not_HG_file);
    std::cout << '\n' << "Not in AB File: " << "\n\n"; 
    print_bitboard(masks::not_AB_file);


}