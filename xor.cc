
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
        (s[I[0]] & x) | (s[E[0]] & ~x),
        (s[I[1]] & x) | (s[E[1]] & ~x),
        (s[I[2]] & x) | (s[E[2]] & ~x),
        (s[I[3]] & x) | (s[E[3]] & ~x),
        (s[I[4]] & x) | (s[E[4]] & ~x)
    };

    const std::array<d_type, len> s2 = {
        (s1[I[0]] & y) | (s1[D[0]] & ~y),
        (s1[I[1]] & y) | (s1[D[1]] & ~y),
        (s1[I[2]] & y) | (s1[D[2]] & ~y),
        (s1[I[3]] & y) | (s1[D[3]] & ~y),
        (s1[I[4]] & y) | (s1[D[4]] & ~y)
    };

    const std::array<d_type, len> s3 = {
        (s2[I[0]] & x) | (s2[E_inv[0]] & ~x),
        (s2[I[1]] & x) | (s2[E_inv[1]] & ~x),
        (s2[I[2]] & x) | (s2[E_inv[2]] & ~x),
        (s2[I[3]] & x) | (s2[E_inv[3]] & ~x),
        (s2[I[4]] & x) | (s2[E_inv[4]] & ~x)
    };

    const std::array<d_type, len> s4 = {
        (s3[I[0]] & y) | (s3[D_inv[0]] & ~y),
        (s3[I[1]] & y) | (s3[D_inv[1]] & ~y),
        (s3[I[2]] & y) | (s3[D_inv[2]] & ~y),
        (s3[I[3]] & y) | (s3[D_inv[3]] & ~y),
        (s3[I[4]] & y) | (s3[D_inv[4]] & ~y)
    };

    const std::array<d_type, len> s5 = {
        s4[C[0]],
        s4[C[1]],
        s4[C[2]],
        s4[C[3]],
        s4[C[4]]
    };

    const std::array<d_type, len> s6 = {
        (s5[D[0]] & x) | (s5[I[0]] & ~x),
        (s5[D[1]] & x) | (s5[I[1]] & ~x),
        (s5[D[2]] & x) | (s5[I[2]] & ~x),
        (s5[D[3]] & x) | (s5[I[3]] & ~x),
        (s5[D[4]] & x) | (s5[I[4]] & ~x)
    };

    const std::array<d_type, len> s7 = {
        (s6[C[0]] & y) | (s6[I[0]] & ~y),
        (s6[C[1]] & y) | (s6[I[1]] & ~y),
        (s6[C[2]] & y) | (s6[I[2]] & ~y),
        (s6[C[3]] & y) | (s6[I[3]] & ~y),
        (s6[C[4]] & y) | (s6[I[4]] & ~y)
    };

    const std::array<d_type, len> s8 = {
        (s7[D_inv[0]] & x) | (s7[I[0]] & ~x),
        (s7[D_inv[1]] & x) | (s7[I[1]] & ~x),
        (s7[D_inv[2]] & x) | (s7[I[2]] & ~x),
        (s7[D_inv[3]] & x) | (s7[I[3]] & ~x),
        (s7[D_inv[4]] & x) | (s7[I[4]] & ~x)
    };

    const std::array<d_type, len> s9 = {
        (s8[C_inv[0]] & y) | (s8[I[0]] & ~y),
        (s8[C_inv[1]] & y) | (s8[I[1]] & ~y),
        (s8[C_inv[2]] & y) | (s8[I[2]] & ~y),
        (s8[C_inv[3]] & y) | (s8[I[3]] & ~y),
        (s8[C_inv[4]] & y) | (s8[I[4]] & ~y)
    };

    const std::array<d_type, len> s10 = {
        s9[B[0]],
        s9[B[1]],
        s9[B[2]],
        s9[B[3]],
        s9[B[4]]
    };

    const std::array<d_type, len> s11 = {
        (s10[I[0]] & x) | (s10[D[0]] & ~x),
        (s10[I[1]] & x) | (s10[D[1]] & ~x),
        (s10[I[2]] & x) | (s10[D[2]] & ~x),
        (s10[I[3]] & x) | (s10[D[3]] & ~x),
        (s10[I[4]] & x) | (s10[D[4]] & ~x)
    };

    const std::array<d_type, len> s12 = {
        (s11[I[0]] & y) | (s11[E[0]] & ~y),
        (s11[I[1]] & y) | (s11[E[1]] & ~y),
        (s11[I[2]] & y) | (s11[E[2]] & ~y),
        (s11[I[3]] & y) | (s11[E[3]] & ~y),
        (s11[I[4]] & y) | (s11[E[4]] & ~y)
    };

    const std::array<d_type, len> s13 = {
        (s12[I[0]] & x) | (s12[D_inv[0]] & ~x),
        (s12[I[1]] & x) | (s12[D_inv[1]] & ~x),
        (s12[I[2]] & x) | (s12[D_inv[2]] & ~x),
        (s12[I[3]] & x) | (s12[D_inv[3]] & ~x),
        (s12[I[4]] & x) | (s12[D_inv[4]] & ~x)
    };

    const std::array<d_type, len> s14 = {
        (s13[I[0]] & y) | (s13[E_inv[0]] & ~y),
        (s13[I[1]] & y) | (s13[E_inv[1]] & ~y),
        (s13[I[2]] & y) | (s13[E_inv[2]] & ~y),
        (s13[I[3]] & y) | (s13[E_inv[3]] & ~y),
        (s13[I[4]] & y) | (s13[E_inv[4]] & ~y)
    };

    const std::array<d_type, len> s15 = {
        s14[C_inv[0]],
        s14[C_inv[1]],
        s14[C_inv[2]],
        s14[C_inv[3]],
        s14[C_inv[4]]
    };

    const std::array<d_type, len> s16 = {
        (s15[C[0]] & x) | (s15[I[0]] & ~x),
        (s15[C[1]] & x) | (s15[I[1]] & ~x),
        (s15[C[2]] & x) | (s15[I[2]] & ~x),
        (s15[C[3]] & x) | (s15[I[3]] & ~x),
        (s15[C[4]] & x) | (s15[I[4]] & ~x)
    };

    const std::array<d_type, len> s17 = {
        (s16[D[0]] & y) | (s16[I[0]] & ~y),
        (s16[D[1]] & y) | (s16[I[1]] & ~y),
        (s16[D[2]] & y) | (s16[I[2]] & ~y),
        (s16[D[3]] & y) | (s16[I[3]] & ~y),
        (s16[D[4]] & y) | (s16[I[4]] & ~y)
    };

    const std::array<d_type, len> s18 = {
        (s17[C_inv[0]] & x) | (s17[I[0]] & ~x),
        (s17[C_inv[1]] & x) | (s17[I[1]] & ~x),
        (s17[C_inv[2]] & x) | (s17[I[2]] & ~x),
        (s17[C_inv[3]] & x) | (s17[I[3]] & ~x),
        (s17[C_inv[4]] & x) | (s17[I[4]] & ~x)
    };

    const std::array<d_type, len> s19 = {
        (s18[D_inv[0]] & y) | (s18[I[0]] & ~y),
        (s18[D_inv[1]] & y) | (s18[I[1]] & ~y),
        (s18[D_inv[2]] & y) | (s18[I[2]] & ~y),
        (s18[D_inv[3]] & y) | (s18[I[3]] & ~y),
        (s18[D_inv[4]] & y) | (s18[I[4]] & ~y)
    };

    const std::array<d_type, len> s20 = {
        s19[B_inv[0]],
        s19[B_inv[1]],
        s19[B_inv[2]],
        s19[B_inv[3]],
        s19[B_inv[4]]
    };


    // return the last state we calculated
    return s20;
}

int main() {
    std::array<d_type, len> state = {1, 2, 3, 4, 5}; // starting state
    for (int i = 0; i < 4; i++) {
        std::array<d_type, len> result = func(state, i&2, i&1);
        printf("%d %d %d %d %d\n", result[0], result[1], result[2], result[3], result[4]);
    }
}
