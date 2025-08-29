#include "bitboard.hpp"
#include "board_types.hpp"
#include <cstdlib>
#include <random>
#include <iostream>


const Square get_random_square() {
    std::default_random_engine generator(std::random_device{}()); 
    std::uniform_int_distribution<int> distribution(0,7);
    const std::pair<int, int> rank_file {distribution(generator),distribution(generator)};
    // std::cout << "Randomly selected rank, file: " << rank_file.first << ", " << rank_file.second << '\n';
    const auto square { make_square(rank_file.first, rank_file.second) };
    return square;
}

constexpr auto reversed { false }; 

void print_mask_constants() {
    std::cout << '\n' << "Not in A File: " << "\n\n";
    print_bitboard(masks::files::not_A_file);
    std::cout << '\n' << "Not in H File: " << "\n\n"; 
    print_bitboard(masks::files::not_H_file);
    std::cout << '\n' << "Not in HG File: " << "\n\n"; 
    print_bitboard(masks::files::not_HG_file);
    std::cout << '\n' << "Not in AB File: " << "\n\n"; 
    print_bitboard(masks::files::not_AB_file);

}

int main() {
    print_squares(Color::white);
    // BitBoard bitboard { };
    // auto view {BitBoardView<BitBoard>(bitboard)};
    // // auto randSquare = get_random_square();
    // auto square { Square::c3 };
    // view.set(square);
    
    // std::cout << "Reference Bitboard: " << '\n';
    // print_bitboard(view);
    // std::cout << '\n';
    // std::cout << '\n';

    // // print_mask_constants();

    
    // // BitBoard seven{((bitboard << 7))};
    // // BitBoard nine{((bitboard << 9))};
    // // BitBoard mask { seven | nine | bitboard };
    // // print_bitboard(mask);

    // // BitBoard attacks {};
    // // print_bitboard(bitboard_constants::masks::not_A_file);
    // // attacks |= ((bitboard << 7));
    // // print_bitboard(attacks);

    
    
    // auto white_attacks { masks::attacks::get_pawn_attacks(square, Color::white)};
    // auto black_attacks { masks::attacks::get_pawn_attacks(square, Color::black)};
    // print_bitboard(white_attacks);
    // print_bitboard(black_attacks);

}