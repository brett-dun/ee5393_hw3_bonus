
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
        (s[B[0]] & x) | (s[I[0]] & ~x),
        (s[B[1]] & x) | (s[I[1]] & ~x),
        (s[B[2]] & x) | (s[I[2]] & ~x),
        (s[B[3]] & x) | (s[I[3]] & ~x),
        (s[B[4]] & x) | (s[I[4]] & ~x)
    };

    const std::array<d_type, len> s2 = {
        (s1[C[0]] & y) | (s1[I[0]] & ~y),
        (s1[C[1]] & y) | (s1[I[1]] & ~y),
        (s1[C[2]] & y) | (s1[I[2]] & ~y),
        (s1[C[3]] & y) | (s1[I[3]] & ~y),
        (s1[C[4]] & y) | (s1[I[4]] & ~y)
    };

    const std::array<d_type, len> s3 = {
        (s2[B_inv[0]] & x) | (s2[I[0]] & ~x),
        (s2[B_inv[1]] & x) | (s2[I[1]] & ~x),
        (s2[B_inv[2]] & x) | (s2[I[2]] & ~x),
        (s2[B_inv[3]] & x) | (s2[I[3]] & ~x),
        (s2[B_inv[4]] & x) | (s2[I[4]] & ~x)
    };

    const std::array<d_type, len> s4 = {
        (s3[C_inv[0]] & y) | (s3[I[0]] & ~y),
        (s3[C_inv[1]] & y) | (s3[I[1]] & ~y),
        (s3[C_inv[2]] & y) | (s3[I[2]] & ~y),
        (s3[C_inv[3]] & y) | (s3[I[3]] & ~y),
        (s3[C_inv[4]] & y) | (s3[I[4]] & ~y)
    };

    const std::array<d_type, len> s5 = {
        s4[A[0]],
        s4[A[1]],
        s4[A[2]],
        s4[A[3]],
        s4[A[4]]
    };


    // return the last state we calculated
    return s5;
}

int main() {
    std::array<d_type, len> state = {1, 2, 3, 4, 5}; // starting state
    for (int i = 0; i < 4; i++) {
        std::array<d_type, len> result = func(state, i&2, i&1);
        printf("%d %d %d %d %d\n", result[0], result[1], result[2], result[3], result[4]);
    }
}
