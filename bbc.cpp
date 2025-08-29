#include "bitboard.hpp"
#include "board_types.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <random>
#include <iostream>
#include <unordered_map>


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
    // print_squares(Color::white);
    BitBoard<uint64_t> bitboard {};
    // auto randSquare = get_random_square();
    auto square { Square::c3 };
    bitboard.set(square);
    
    // std::cout << '\n';
    // std::cout << "Reference Bitboard: " << '\n';
    // print_bitboard(bitboard);
    // std::cout << '\n';
    // std::cout << '\n';

    // print_mask_constants();

    
    // BitBoard seven{((bitboard << 7))};
    // BitBoard nine{((bitboard << 9))};
    // BitBoard mask { seven | nine | bitboard };
    // std::cout << '\n' << "See attacks NW, NE";
    // print_bitboard(mask);

    // BitBoard<uint64_t> attacks {};
    // print_bitboard(masks::files::not_A_file);
    // attacks |= ((bitboard << 7));
    // print_bitboard(attacks);
    using namespace moves;
    using enum Direction;
    using namespace masks;
    print_bitboard(bitboard);
    std::map<std::string_view, BitBoard<std::uint64_t>> moves {
    { "West", move<W, 0xFFFFFFFFFFFFFFFF>(bitboard) },
    {"East", move<E, 0xFFFFFFFFFFFFFFFF>(bitboard)},
    {"NW", move<NW, 0xFFFFFFFFFFFFFFFF>(bitboard)},
    {"NE", move<NE, 0xFFFFFFFFFFFFFFFF>(bitboard)},    
    // {"SW", move<SW, 0xFFFFFFFFFFFFFFFF>(bitboard)},    
    // {"SE", move<SE, 0xFFFFFFFFFFFFFFFF>(bitboard)},  
    // {"S", move<S, 0xFFFFFFFFFFFFFFFF>(bitboard)},    

    };
    for (auto & [dir, bb] : moves) {
        std::cout << dir << '\n'; 
        bb.set(square);
        print_bitboard(bb);
    }
   
    
    // auto white_attacks { masks::attacks::get_pawn_attacks(square, Color::white)};
    // // auto black_attacks { masks::attacks::get_pawn_attacks(square, Color::black)};
    // auto white{BitBoard(white_attacks)};
    // print_bitboard(white);
    // print_bitboard(bitboard << 1);

}