
#include <array>
#include "stdint.h"
#include "stdio.h"

// Data type to use. (This is arbitrary.)
typedef uint8_t d_type;


// Note: constexpr is used here to make the logic more clear. At compile time constexpr is removed
// by the compiler and replaced with the literal values that were determined at compile time. I
// used c++ 14 when writing/testing this program.


// Length of the states and permuations
constexpr std::size_t len = 5;

constexpr std::array<std::size_t, len> A = {1, 4, 3, 0, 2};
constexpr std::array<std::size_t, len> A_inv = {3, 0, 4, 2, 1};
constexpr std::array<std::size_t, len> B = {2, 4, 1, 0, 3};
constexpr std::array<std::size_t, len> B_inv = {3, 2, 0, 4, 1};
constexpr std::array<std::size_t, len> C = {4, 3, 0, 2, 1};
constexpr std::array<std::size_t, len> C_inv = {2, 4, 3, 1, 0};
constexpr std::array<std::size_t, len> D = {2, 0, 4, 1, 3};
constexpr std::array<std::size_t, len> D_inv = {1, 3, 0, 4, 2};
constexpr std::array<std::size_t, len> E = {4, 3, 1, 0, 2};
constexpr std::array<std::size_t, len> E_inv = {3, 2, 4, 1, 0};

constexpr std::array<std::size_t, len> I = {0, 1, 2, 3, 4};

// Function to compute the resulting permutation given an input state and variables.
std::array<d_type, len> func(const std::array<d_type, len> s, const bool _x, const bool _y) {

    // true and false values where all bits are true or false
    constexpr d_type TRUE = 0xFF;
    constexpr d_type FALSE = 0x00;

    const d_type x = _x ? TRUE : FALSE;
    const d_type y = _y ? TRUE : FALSE;

    
    const std::array<d_type, len> s1 = {
        (s[C[0]] & x) | (s[I[0]] & ~x),
        (s[C[1]] & x) | (s[I[1]] & ~x),
        (s[C[2]] & x) | (s[I[2]] & ~x),
        (s[C[3]] & x) | (s[I[3]] & ~x),
        (s[C[4]] & x) | (s[I[4]] & ~x)
    };

    const std::array<d_type, len> s2 = {
        (s1[B[0]] & y) | (s1[I[0]] & ~y),
        (s1[B[1]] & y) | (s1[I[1]] & ~y),
        (s1[B[2]] & y) | (s1[I[2]] & ~y),
        (s1[B[3]] & y) | (s1[I[3]] & ~y),
        (s1[B[4]] & y) | (s1[I[4]] & ~y)
    };

    const std::array<d_type, len> s3 = {
        (s2[C_inv[0]] & x) | (s2[I[0]] & ~x),
        (s2[C_inv[1]] & x) | (s2[I[1]] & ~x),
        (s2[C_inv[2]] & x) | (s2[I[2]] & ~x),
        (s2[C_inv[3]] & x) | (s2[I[3]] & ~x),
        (s2[C_inv[4]] & x) | (s2[I[4]] & ~x)
    };

    const std::array<d_type, len> s4 = {
        (s3[B_inv[0]] & y) | (s3[I[0]] & ~y),
        (s3[B_inv[1]] & y) | (s3[I[1]] & ~y),
        (s3[B_inv[2]] & y) | (s3[I[2]] & ~y),
        (s3[B_inv[3]] & y) | (s3[I[3]] & ~y),
        (s3[B_inv[4]] & y) | (s3[I[4]] & ~y)
    };


    // return the last state we calculated
    return s4;
}

int main() {
    std::array<d_type, len> state = {1, 2, 3, 4, 5}; // starting state
    for (int i = 0; i < 4; i++) {
        std::array<d_type, len> result = func(state, i&2, i&1);
        printf("%d %d %d %d %d\n", result[0], result[1], result[2], result[3], result[4]);
    }
}
