
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
std::array<d_type, len> func(const std::array<d_type, len> s, const bool _x1, const bool _x2, const bool _x3, const bool _x4) {

    // true and false values where all bits are true or false
    constexpr d_type TRUE = 0xFF;
    constexpr d_type FALSE = 0x00;

    const d_type x1 = _x1 ? TRUE : FALSE;
    const d_type x2 = _x2 ? TRUE : FALSE;
    const d_type x3 = _x3 ? TRUE : FALSE;
    const d_type x4 = _x4 ? TRUE : FALSE;

    
    const std::array<d_type, len> s1 = {
        (s[B[0]] & x1) | (s[I[0]] & ~x1),
        (s[B[1]] & x1) | (s[I[1]] & ~x1),
        (s[B[2]] & x1) | (s[I[2]] & ~x1),
        (s[B[3]] & x1) | (s[I[3]] & ~x1),
        (s[B[4]] & x1) | (s[I[4]] & ~x1)
    };

    const std::array<d_type, len> s2 = {
        (s1[I[0]] & x2) | (s1[C[0]] & ~x2),
        (s1[I[1]] & x2) | (s1[C[1]] & ~x2),
        (s1[I[2]] & x2) | (s1[C[2]] & ~x2),
        (s1[I[3]] & x2) | (s1[C[3]] & ~x2),
        (s1[I[4]] & x2) | (s1[C[4]] & ~x2)
    };

    const std::array<d_type, len> s3 = {
        (s2[B_inv[0]] & x1) | (s2[I[0]] & ~x1),
        (s2[B_inv[1]] & x1) | (s2[I[1]] & ~x1),
        (s2[B_inv[2]] & x1) | (s2[I[2]] & ~x1),
        (s2[B_inv[3]] & x1) | (s2[I[3]] & ~x1),
        (s2[B_inv[4]] & x1) | (s2[I[4]] & ~x1)
    };

    const std::array<d_type, len> s4 = {
        (s3[I[0]] & x2) | (s3[C_inv[0]] & ~x2),
        (s3[I[1]] & x2) | (s3[C_inv[1]] & ~x2),
        (s3[I[2]] & x2) | (s3[C_inv[2]] & ~x2),
        (s3[I[3]] & x2) | (s3[C_inv[3]] & ~x2),
        (s3[I[4]] & x2) | (s3[C_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s5 = {
        s4[A[0]],
        s4[A[1]],
        s4[A[2]],
        s4[A[3]],
        s4[A[4]]
    };

    const std::array<d_type, len> s6 = {
        (s5[I[0]] & x1) | (s5[B[0]] & ~x1),
        (s5[I[1]] & x1) | (s5[B[1]] & ~x1),
        (s5[I[2]] & x1) | (s5[B[2]] & ~x1),
        (s5[I[3]] & x1) | (s5[B[3]] & ~x1),
        (s5[I[4]] & x1) | (s5[B[4]] & ~x1)
    };

    const std::array<d_type, len> s7 = {
        (s6[E[0]] & x2) | (s6[I[0]] & ~x2),
        (s6[E[1]] & x2) | (s6[I[1]] & ~x2),
        (s6[E[2]] & x2) | (s6[I[2]] & ~x2),
        (s6[E[3]] & x2) | (s6[I[3]] & ~x2),
        (s6[E[4]] & x2) | (s6[I[4]] & ~x2)
    };

    const std::array<d_type, len> s8 = {
        (s7[I[0]] & x1) | (s7[B_inv[0]] & ~x1),
        (s7[I[1]] & x1) | (s7[B_inv[1]] & ~x1),
        (s7[I[2]] & x1) | (s7[B_inv[2]] & ~x1),
        (s7[I[3]] & x1) | (s7[B_inv[3]] & ~x1),
        (s7[I[4]] & x1) | (s7[B_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s9 = {
        (s8[E_inv[0]] & x2) | (s8[I[0]] & ~x2),
        (s8[E_inv[1]] & x2) | (s8[I[1]] & ~x2),
        (s8[E_inv[2]] & x2) | (s8[I[2]] & ~x2),
        (s8[E_inv[3]] & x2) | (s8[I[3]] & ~x2),
        (s8[E_inv[4]] & x2) | (s8[I[4]] & ~x2)
    };

    const std::array<d_type, len> s10 = {
        s9[D[0]],
        s9[D[1]],
        s9[D[2]],
        s9[D[3]],
        s9[D[4]]
    };

    const std::array<d_type, len> s11 = {
        (s10[C[0]] & x1) | (s10[I[0]] & ~x1),
        (s10[C[1]] & x1) | (s10[I[1]] & ~x1),
        (s10[C[2]] & x1) | (s10[I[2]] & ~x1),
        (s10[C[3]] & x1) | (s10[I[3]] & ~x1),
        (s10[C[4]] & x1) | (s10[I[4]] & ~x1)
    };

    const std::array<d_type, len> s12 = {
        (s11[I[0]] & x2) | (s11[B[0]] & ~x2),
        (s11[I[1]] & x2) | (s11[B[1]] & ~x2),
        (s11[I[2]] & x2) | (s11[B[2]] & ~x2),
        (s11[I[3]] & x2) | (s11[B[3]] & ~x2),
        (s11[I[4]] & x2) | (s11[B[4]] & ~x2)
    };

    const std::array<d_type, len> s13 = {
        (s12[C_inv[0]] & x1) | (s12[I[0]] & ~x1),
        (s12[C_inv[1]] & x1) | (s12[I[1]] & ~x1),
        (s12[C_inv[2]] & x1) | (s12[I[2]] & ~x1),
        (s12[C_inv[3]] & x1) | (s12[I[3]] & ~x1),
        (s12[C_inv[4]] & x1) | (s12[I[4]] & ~x1)
    };

    const std::array<d_type, len> s14 = {
        (s13[I[0]] & x2) | (s13[B_inv[0]] & ~x2),
        (s13[I[1]] & x2) | (s13[B_inv[1]] & ~x2),
        (s13[I[2]] & x2) | (s13[B_inv[2]] & ~x2),
        (s13[I[3]] & x2) | (s13[B_inv[3]] & ~x2),
        (s13[I[4]] & x2) | (s13[B_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s15 = {
        s14[A_inv[0]],
        s14[A_inv[1]],
        s14[A_inv[2]],
        s14[A_inv[3]],
        s14[A_inv[4]]
    };

    const std::array<d_type, len> s16 = {
        (s15[I[0]] & x1) | (s15[E[0]] & ~x1),
        (s15[I[1]] & x1) | (s15[E[1]] & ~x1),
        (s15[I[2]] & x1) | (s15[E[2]] & ~x1),
        (s15[I[3]] & x1) | (s15[E[3]] & ~x1),
        (s15[I[4]] & x1) | (s15[E[4]] & ~x1)
    };

    const std::array<d_type, len> s17 = {
        (s16[B[0]] & x2) | (s16[I[0]] & ~x2),
        (s16[B[1]] & x2) | (s16[I[1]] & ~x2),
        (s16[B[2]] & x2) | (s16[I[2]] & ~x2),
        (s16[B[3]] & x2) | (s16[I[3]] & ~x2),
        (s16[B[4]] & x2) | (s16[I[4]] & ~x2)
    };

    const std::array<d_type, len> s18 = {
        (s17[I[0]] & x1) | (s17[E_inv[0]] & ~x1),
        (s17[I[1]] & x1) | (s17[E_inv[1]] & ~x1),
        (s17[I[2]] & x1) | (s17[E_inv[2]] & ~x1),
        (s17[I[3]] & x1) | (s17[E_inv[3]] & ~x1),
        (s17[I[4]] & x1) | (s17[E_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s19 = {
        (s18[B_inv[0]] & x2) | (s18[I[0]] & ~x2),
        (s18[B_inv[1]] & x2) | (s18[I[1]] & ~x2),
        (s18[B_inv[2]] & x2) | (s18[I[2]] & ~x2),
        (s18[B_inv[3]] & x2) | (s18[I[3]] & ~x2),
        (s18[B_inv[4]] & x2) | (s18[I[4]] & ~x2)
    };

    const std::array<d_type, len> s20 = {
        s19[D_inv[0]],
        s19[D_inv[1]],
        s19[D_inv[2]],
        s19[D_inv[3]],
        s19[D_inv[4]]
    };

    const std::array<d_type, len> s21 = {
        s20[E[0]],
        s20[E[1]],
        s20[E[2]],
        s20[E[3]],
        s20[E[4]]
    };

    const std::array<d_type, len> s22 = {
        (s21[D[0]] & x3) | (s21[I[0]] & ~x3),
        (s21[D[1]] & x3) | (s21[I[1]] & ~x3),
        (s21[D[2]] & x3) | (s21[I[2]] & ~x3),
        (s21[D[3]] & x3) | (s21[I[3]] & ~x3),
        (s21[D[4]] & x3) | (s21[I[4]] & ~x3)
    };

    const std::array<d_type, len> s23 = {
        (s22[C[0]] & x4) | (s22[I[0]] & ~x4),
        (s22[C[1]] & x4) | (s22[I[1]] & ~x4),
        (s22[C[2]] & x4) | (s22[I[2]] & ~x4),
        (s22[C[3]] & x4) | (s22[I[3]] & ~x4),
        (s22[C[4]] & x4) | (s22[I[4]] & ~x4)
    };

    const std::array<d_type, len> s24 = {
        (s23[D_inv[0]] & x3) | (s23[I[0]] & ~x3),
        (s23[D_inv[1]] & x3) | (s23[I[1]] & ~x3),
        (s23[D_inv[2]] & x3) | (s23[I[2]] & ~x3),
        (s23[D_inv[3]] & x3) | (s23[I[3]] & ~x3),
        (s23[D_inv[4]] & x3) | (s23[I[4]] & ~x3)
    };

    const std::array<d_type, len> s25 = {
        (s24[C_inv[0]] & x4) | (s24[I[0]] & ~x4),
        (s24[C_inv[1]] & x4) | (s24[I[1]] & ~x4),
        (s24[C_inv[2]] & x4) | (s24[I[2]] & ~x4),
        (s24[C_inv[3]] & x4) | (s24[I[3]] & ~x4),
        (s24[C_inv[4]] & x4) | (s24[I[4]] & ~x4)
    };

    const std::array<d_type, len> s26 = {
        s25[B[0]],
        s25[B[1]],
        s25[B[2]],
        s25[B[3]],
        s25[B[4]]
    };

    const std::array<d_type, len> s27 = {
        (s26[I[0]] & x3) | (s26[A[0]] & ~x3),
        (s26[I[1]] & x3) | (s26[A[1]] & ~x3),
        (s26[I[2]] & x3) | (s26[A[2]] & ~x3),
        (s26[I[3]] & x3) | (s26[A[3]] & ~x3),
        (s26[I[4]] & x3) | (s26[A[4]] & ~x3)
    };

    const std::array<d_type, len> s28 = {
        (s27[I[0]] & x4) | (s27[D[0]] & ~x4),
        (s27[I[1]] & x4) | (s27[D[1]] & ~x4),
        (s27[I[2]] & x4) | (s27[D[2]] & ~x4),
        (s27[I[3]] & x4) | (s27[D[3]] & ~x4),
        (s27[I[4]] & x4) | (s27[D[4]] & ~x4)
    };

    const std::array<d_type, len> s29 = {
        (s28[I[0]] & x3) | (s28[A_inv[0]] & ~x3),
        (s28[I[1]] & x3) | (s28[A_inv[1]] & ~x3),
        (s28[I[2]] & x3) | (s28[A_inv[2]] & ~x3),
        (s28[I[3]] & x3) | (s28[A_inv[3]] & ~x3),
        (s28[I[4]] & x3) | (s28[A_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s30 = {
        (s29[I[0]] & x4) | (s29[D_inv[0]] & ~x4),
        (s29[I[1]] & x4) | (s29[D_inv[1]] & ~x4),
        (s29[I[2]] & x4) | (s29[D_inv[2]] & ~x4),
        (s29[I[3]] & x4) | (s29[D_inv[3]] & ~x4),
        (s29[I[4]] & x4) | (s29[D_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s31 = {
        s30[E[0]],
        s30[E[1]],
        s30[E[2]],
        s30[E[3]],
        s30[E[4]]
    };

    const std::array<d_type, len> s32 = {
        (s31[C[0]] & x3) | (s31[I[0]] & ~x3),
        (s31[C[1]] & x3) | (s31[I[1]] & ~x3),
        (s31[C[2]] & x3) | (s31[I[2]] & ~x3),
        (s31[C[3]] & x3) | (s31[I[3]] & ~x3),
        (s31[C[4]] & x3) | (s31[I[4]] & ~x3)
    };

    const std::array<d_type, len> s33 = {
        (s32[D[0]] & x4) | (s32[I[0]] & ~x4),
        (s32[D[1]] & x4) | (s32[I[1]] & ~x4),
        (s32[D[2]] & x4) | (s32[I[2]] & ~x4),
        (s32[D[3]] & x4) | (s32[I[3]] & ~x4),
        (s32[D[4]] & x4) | (s32[I[4]] & ~x4)
    };

    const std::array<d_type, len> s34 = {
        (s33[C_inv[0]] & x3) | (s33[I[0]] & ~x3),
        (s33[C_inv[1]] & x3) | (s33[I[1]] & ~x3),
        (s33[C_inv[2]] & x3) | (s33[I[2]] & ~x3),
        (s33[C_inv[3]] & x3) | (s33[I[3]] & ~x3),
        (s33[C_inv[4]] & x3) | (s33[I[4]] & ~x3)
    };

    const std::array<d_type, len> s35 = {
        (s34[D_inv[0]] & x4) | (s34[I[0]] & ~x4),
        (s34[D_inv[1]] & x4) | (s34[I[1]] & ~x4),
        (s34[D_inv[2]] & x4) | (s34[I[2]] & ~x4),
        (s34[D_inv[3]] & x4) | (s34[I[3]] & ~x4),
        (s34[D_inv[4]] & x4) | (s34[I[4]] & ~x4)
    };

    const std::array<d_type, len> s36 = {
        s35[B_inv[0]],
        s35[B_inv[1]],
        s35[B_inv[2]],
        s35[B_inv[3]],
        s35[B_inv[4]]
    };

    const std::array<d_type, len> s37 = {
        (s36[I[0]] & x3) | (s36[D[0]] & ~x3),
        (s36[I[1]] & x3) | (s36[D[1]] & ~x3),
        (s36[I[2]] & x3) | (s36[D[2]] & ~x3),
        (s36[I[3]] & x3) | (s36[D[3]] & ~x3),
        (s36[I[4]] & x3) | (s36[D[4]] & ~x3)
    };

    const std::array<d_type, len> s38 = {
        (s37[I[0]] & x4) | (s37[A[0]] & ~x4),
        (s37[I[1]] & x4) | (s37[A[1]] & ~x4),
        (s37[I[2]] & x4) | (s37[A[2]] & ~x4),
        (s37[I[3]] & x4) | (s37[A[3]] & ~x4),
        (s37[I[4]] & x4) | (s37[A[4]] & ~x4)
    };

    const std::array<d_type, len> s39 = {
        (s38[I[0]] & x3) | (s38[D_inv[0]] & ~x3),
        (s38[I[1]] & x3) | (s38[D_inv[1]] & ~x3),
        (s38[I[2]] & x3) | (s38[D_inv[2]] & ~x3),
        (s38[I[3]] & x3) | (s38[D_inv[3]] & ~x3),
        (s38[I[4]] & x3) | (s38[D_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s40 = {
        (s39[I[0]] & x4) | (s39[A_inv[0]] & ~x4),
        (s39[I[1]] & x4) | (s39[A_inv[1]] & ~x4),
        (s39[I[2]] & x4) | (s39[A_inv[2]] & ~x4),
        (s39[I[3]] & x4) | (s39[A_inv[3]] & ~x4),
        (s39[I[4]] & x4) | (s39[A_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s41 = {
        s40[E_inv[0]],
        s40[E_inv[1]],
        s40[E_inv[2]],
        s40[E_inv[3]],
        s40[E_inv[4]]
    };

    const std::array<d_type, len> s42 = {
        s41[D[0]],
        s41[D[1]],
        s41[D[2]],
        s41[D[3]],
        s41[D[4]]
    };

    const std::array<d_type, len> s43 = {
        (s42[B[0]] & x1) | (s42[I[0]] & ~x1),
        (s42[B[1]] & x1) | (s42[I[1]] & ~x1),
        (s42[B[2]] & x1) | (s42[I[2]] & ~x1),
        (s42[B[3]] & x1) | (s42[I[3]] & ~x1),
        (s42[B[4]] & x1) | (s42[I[4]] & ~x1)
    };

    const std::array<d_type, len> s44 = {
        (s43[I[0]] & x2) | (s43[E[0]] & ~x2),
        (s43[I[1]] & x2) | (s43[E[1]] & ~x2),
        (s43[I[2]] & x2) | (s43[E[2]] & ~x2),
        (s43[I[3]] & x2) | (s43[E[3]] & ~x2),
        (s43[I[4]] & x2) | (s43[E[4]] & ~x2)
    };

    const std::array<d_type, len> s45 = {
        (s44[B_inv[0]] & x1) | (s44[I[0]] & ~x1),
        (s44[B_inv[1]] & x1) | (s44[I[1]] & ~x1),
        (s44[B_inv[2]] & x1) | (s44[I[2]] & ~x1),
        (s44[B_inv[3]] & x1) | (s44[I[3]] & ~x1),
        (s44[B_inv[4]] & x1) | (s44[I[4]] & ~x1)
    };

    const std::array<d_type, len> s46 = {
        (s45[I[0]] & x2) | (s45[E_inv[0]] & ~x2),
        (s45[I[1]] & x2) | (s45[E_inv[1]] & ~x2),
        (s45[I[2]] & x2) | (s45[E_inv[2]] & ~x2),
        (s45[I[3]] & x2) | (s45[E_inv[3]] & ~x2),
        (s45[I[4]] & x2) | (s45[E_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s47 = {
        s46[D[0]],
        s46[D[1]],
        s46[D[2]],
        s46[D[3]],
        s46[D[4]]
    };

    const std::array<d_type, len> s48 = {
        (s47[I[0]] & x1) | (s47[B[0]] & ~x1),
        (s47[I[1]] & x1) | (s47[B[1]] & ~x1),
        (s47[I[2]] & x1) | (s47[B[2]] & ~x1),
        (s47[I[3]] & x1) | (s47[B[3]] & ~x1),
        (s47[I[4]] & x1) | (s47[B[4]] & ~x1)
    };

    const std::array<d_type, len> s49 = {
        (s48[C[0]] & x2) | (s48[I[0]] & ~x2),
        (s48[C[1]] & x2) | (s48[I[1]] & ~x2),
        (s48[C[2]] & x2) | (s48[I[2]] & ~x2),
        (s48[C[3]] & x2) | (s48[I[3]] & ~x2),
        (s48[C[4]] & x2) | (s48[I[4]] & ~x2)
    };

    const std::array<d_type, len> s50 = {
        (s49[I[0]] & x1) | (s49[B_inv[0]] & ~x1),
        (s49[I[1]] & x1) | (s49[B_inv[1]] & ~x1),
        (s49[I[2]] & x1) | (s49[B_inv[2]] & ~x1),
        (s49[I[3]] & x1) | (s49[B_inv[3]] & ~x1),
        (s49[I[4]] & x1) | (s49[B_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s51 = {
        (s50[C_inv[0]] & x2) | (s50[I[0]] & ~x2),
        (s50[C_inv[1]] & x2) | (s50[I[1]] & ~x2),
        (s50[C_inv[2]] & x2) | (s50[I[2]] & ~x2),
        (s50[C_inv[3]] & x2) | (s50[I[3]] & ~x2),
        (s50[C_inv[4]] & x2) | (s50[I[4]] & ~x2)
    };

    const std::array<d_type, len> s52 = {
        s51[A[0]],
        s51[A[1]],
        s51[A[2]],
        s51[A[3]],
        s51[A[4]]
    };

    const std::array<d_type, len> s53 = {
        (s52[E[0]] & x1) | (s52[I[0]] & ~x1),
        (s52[E[1]] & x1) | (s52[I[1]] & ~x1),
        (s52[E[2]] & x1) | (s52[I[2]] & ~x1),
        (s52[E[3]] & x1) | (s52[I[3]] & ~x1),
        (s52[E[4]] & x1) | (s52[I[4]] & ~x1)
    };

    const std::array<d_type, len> s54 = {
        (s53[I[0]] & x2) | (s53[B[0]] & ~x2),
        (s53[I[1]] & x2) | (s53[B[1]] & ~x2),
        (s53[I[2]] & x2) | (s53[B[2]] & ~x2),
        (s53[I[3]] & x2) | (s53[B[3]] & ~x2),
        (s53[I[4]] & x2) | (s53[B[4]] & ~x2)
    };

    const std::array<d_type, len> s55 = {
        (s54[E_inv[0]] & x1) | (s54[I[0]] & ~x1),
        (s54[E_inv[1]] & x1) | (s54[I[1]] & ~x1),
        (s54[E_inv[2]] & x1) | (s54[I[2]] & ~x1),
        (s54[E_inv[3]] & x1) | (s54[I[3]] & ~x1),
        (s54[E_inv[4]] & x1) | (s54[I[4]] & ~x1)
    };

    const std::array<d_type, len> s56 = {
        (s55[I[0]] & x2) | (s55[B_inv[0]] & ~x2),
        (s55[I[1]] & x2) | (s55[B_inv[1]] & ~x2),
        (s55[I[2]] & x2) | (s55[B_inv[2]] & ~x2),
        (s55[I[3]] & x2) | (s55[B_inv[3]] & ~x2),
        (s55[I[4]] & x2) | (s55[B_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s57 = {
        s56[D_inv[0]],
        s56[D_inv[1]],
        s56[D_inv[2]],
        s56[D_inv[3]],
        s56[D_inv[4]]
    };

    const std::array<d_type, len> s58 = {
        (s57[I[0]] & x1) | (s57[C[0]] & ~x1),
        (s57[I[1]] & x1) | (s57[C[1]] & ~x1),
        (s57[I[2]] & x1) | (s57[C[2]] & ~x1),
        (s57[I[3]] & x1) | (s57[C[3]] & ~x1),
        (s57[I[4]] & x1) | (s57[C[4]] & ~x1)
    };

    const std::array<d_type, len> s59 = {
        (s58[B[0]] & x2) | (s58[I[0]] & ~x2),
        (s58[B[1]] & x2) | (s58[I[1]] & ~x2),
        (s58[B[2]] & x2) | (s58[I[2]] & ~x2),
        (s58[B[3]] & x2) | (s58[I[3]] & ~x2),
        (s58[B[4]] & x2) | (s58[I[4]] & ~x2)
    };

    const std::array<d_type, len> s60 = {
        (s59[I[0]] & x1) | (s59[C_inv[0]] & ~x1),
        (s59[I[1]] & x1) | (s59[C_inv[1]] & ~x1),
        (s59[I[2]] & x1) | (s59[C_inv[2]] & ~x1),
        (s59[I[3]] & x1) | (s59[C_inv[3]] & ~x1),
        (s59[I[4]] & x1) | (s59[C_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s61 = {
        (s60[B_inv[0]] & x2) | (s60[I[0]] & ~x2),
        (s60[B_inv[1]] & x2) | (s60[I[1]] & ~x2),
        (s60[B_inv[2]] & x2) | (s60[I[2]] & ~x2),
        (s60[B_inv[3]] & x2) | (s60[I[3]] & ~x2),
        (s60[B_inv[4]] & x2) | (s60[I[4]] & ~x2)
    };

    const std::array<d_type, len> s62 = {
        s61[A_inv[0]],
        s61[A_inv[1]],
        s61[A_inv[2]],
        s61[A_inv[3]],
        s61[A_inv[4]]
    };

    const std::array<d_type, len> s63 = {
        s62[E_inv[0]],
        s62[E_inv[1]],
        s62[E_inv[2]],
        s62[E_inv[3]],
        s62[E_inv[4]]
    };

    const std::array<d_type, len> s64 = {
        (s63[A[0]] & x3) | (s63[I[0]] & ~x3),
        (s63[A[1]] & x3) | (s63[I[1]] & ~x3),
        (s63[A[2]] & x3) | (s63[I[2]] & ~x3),
        (s63[A[3]] & x3) | (s63[I[3]] & ~x3),
        (s63[A[4]] & x3) | (s63[I[4]] & ~x3)
    };

    const std::array<d_type, len> s65 = {
        (s64[D[0]] & x4) | (s64[I[0]] & ~x4),
        (s64[D[1]] & x4) | (s64[I[1]] & ~x4),
        (s64[D[2]] & x4) | (s64[I[2]] & ~x4),
        (s64[D[3]] & x4) | (s64[I[3]] & ~x4),
        (s64[D[4]] & x4) | (s64[I[4]] & ~x4)
    };

    const std::array<d_type, len> s66 = {
        (s65[A_inv[0]] & x3) | (s65[I[0]] & ~x3),
        (s65[A_inv[1]] & x3) | (s65[I[1]] & ~x3),
        (s65[A_inv[2]] & x3) | (s65[I[2]] & ~x3),
        (s65[A_inv[3]] & x3) | (s65[I[3]] & ~x3),
        (s65[A_inv[4]] & x3) | (s65[I[4]] & ~x3)
    };

    const std::array<d_type, len> s67 = {
        (s66[D_inv[0]] & x4) | (s66[I[0]] & ~x4),
        (s66[D_inv[1]] & x4) | (s66[I[1]] & ~x4),
        (s66[D_inv[2]] & x4) | (s66[I[2]] & ~x4),
        (s66[D_inv[3]] & x4) | (s66[I[3]] & ~x4),
        (s66[D_inv[4]] & x4) | (s66[I[4]] & ~x4)
    };

    const std::array<d_type, len> s68 = {
        s67[E[0]],
        s67[E[1]],
        s67[E[2]],
        s67[E[3]],
        s67[E[4]]
    };

    const std::array<d_type, len> s69 = {
        (s68[I[0]] & x3) | (s68[D[0]] & ~x3),
        (s68[I[1]] & x3) | (s68[D[1]] & ~x3),
        (s68[I[2]] & x3) | (s68[D[2]] & ~x3),
        (s68[I[3]] & x3) | (s68[D[3]] & ~x3),
        (s68[I[4]] & x3) | (s68[D[4]] & ~x3)
    };

    const std::array<d_type, len> s70 = {
        (s69[I[0]] & x4) | (s69[C[0]] & ~x4),
        (s69[I[1]] & x4) | (s69[C[1]] & ~x4),
        (s69[I[2]] & x4) | (s69[C[2]] & ~x4),
        (s69[I[3]] & x4) | (s69[C[3]] & ~x4),
        (s69[I[4]] & x4) | (s69[C[4]] & ~x4)
    };

    const std::array<d_type, len> s71 = {
        (s70[I[0]] & x3) | (s70[D_inv[0]] & ~x3),
        (s70[I[1]] & x3) | (s70[D_inv[1]] & ~x3),
        (s70[I[2]] & x3) | (s70[D_inv[2]] & ~x3),
        (s70[I[3]] & x3) | (s70[D_inv[3]] & ~x3),
        (s70[I[4]] & x3) | (s70[D_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s72 = {
        (s71[I[0]] & x4) | (s71[C_inv[0]] & ~x4),
        (s71[I[1]] & x4) | (s71[C_inv[1]] & ~x4),
        (s71[I[2]] & x4) | (s71[C_inv[2]] & ~x4),
        (s71[I[3]] & x4) | (s71[C_inv[3]] & ~x4),
        (s71[I[4]] & x4) | (s71[C_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s73 = {
        s72[B[0]],
        s72[B[1]],
        s72[B[2]],
        s72[B[3]],
        s72[B[4]]
    };

    const std::array<d_type, len> s74 = {
        (s73[D[0]] & x3) | (s73[I[0]] & ~x3),
        (s73[D[1]] & x3) | (s73[I[1]] & ~x3),
        (s73[D[2]] & x3) | (s73[I[2]] & ~x3),
        (s73[D[3]] & x3) | (s73[I[3]] & ~x3),
        (s73[D[4]] & x3) | (s73[I[4]] & ~x3)
    };

    const std::array<d_type, len> s75 = {
        (s74[A[0]] & x4) | (s74[I[0]] & ~x4),
        (s74[A[1]] & x4) | (s74[I[1]] & ~x4),
        (s74[A[2]] & x4) | (s74[I[2]] & ~x4),
        (s74[A[3]] & x4) | (s74[I[3]] & ~x4),
        (s74[A[4]] & x4) | (s74[I[4]] & ~x4)
    };

    const std::array<d_type, len> s76 = {
        (s75[D_inv[0]] & x3) | (s75[I[0]] & ~x3),
        (s75[D_inv[1]] & x3) | (s75[I[1]] & ~x3),
        (s75[D_inv[2]] & x3) | (s75[I[2]] & ~x3),
        (s75[D_inv[3]] & x3) | (s75[I[3]] & ~x3),
        (s75[D_inv[4]] & x3) | (s75[I[4]] & ~x3)
    };

    const std::array<d_type, len> s77 = {
        (s76[A_inv[0]] & x4) | (s76[I[0]] & ~x4),
        (s76[A_inv[1]] & x4) | (s76[I[1]] & ~x4),
        (s76[A_inv[2]] & x4) | (s76[I[2]] & ~x4),
        (s76[A_inv[3]] & x4) | (s76[I[3]] & ~x4),
        (s76[A_inv[4]] & x4) | (s76[I[4]] & ~x4)
    };

    const std::array<d_type, len> s78 = {
        s77[E_inv[0]],
        s77[E_inv[1]],
        s77[E_inv[2]],
        s77[E_inv[3]],
        s77[E_inv[4]]
    };

    const std::array<d_type, len> s79 = {
        (s78[I[0]] & x3) | (s78[C[0]] & ~x3),
        (s78[I[1]] & x3) | (s78[C[1]] & ~x3),
        (s78[I[2]] & x3) | (s78[C[2]] & ~x3),
        (s78[I[3]] & x3) | (s78[C[3]] & ~x3),
        (s78[I[4]] & x3) | (s78[C[4]] & ~x3)
    };

    const std::array<d_type, len> s80 = {
        (s79[I[0]] & x4) | (s79[D[0]] & ~x4),
        (s79[I[1]] & x4) | (s79[D[1]] & ~x4),
        (s79[I[2]] & x4) | (s79[D[2]] & ~x4),
        (s79[I[3]] & x4) | (s79[D[3]] & ~x4),
        (s79[I[4]] & x4) | (s79[D[4]] & ~x4)
    };

    const std::array<d_type, len> s81 = {
        (s80[I[0]] & x3) | (s80[C_inv[0]] & ~x3),
        (s80[I[1]] & x3) | (s80[C_inv[1]] & ~x3),
        (s80[I[2]] & x3) | (s80[C_inv[2]] & ~x3),
        (s80[I[3]] & x3) | (s80[C_inv[3]] & ~x3),
        (s80[I[4]] & x3) | (s80[C_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s82 = {
        (s81[I[0]] & x4) | (s81[D_inv[0]] & ~x4),
        (s81[I[1]] & x4) | (s81[D_inv[1]] & ~x4),
        (s81[I[2]] & x4) | (s81[D_inv[2]] & ~x4),
        (s81[I[3]] & x4) | (s81[D_inv[3]] & ~x4),
        (s81[I[4]] & x4) | (s81[D_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s83 = {
        s82[B_inv[0]],
        s82[B_inv[1]],
        s82[B_inv[2]],
        s82[B_inv[3]],
        s82[B_inv[4]]
    };

    const std::array<d_type, len> s84 = {
        s83[D_inv[0]],
        s83[D_inv[1]],
        s83[D_inv[2]],
        s83[D_inv[3]],
        s83[D_inv[4]]
    };

    const std::array<d_type, len> s85 = {
        s84[C[0]],
        s84[C[1]],
        s84[C[2]],
        s84[C[3]],
        s84[C[4]]
    };

    const std::array<d_type, len> s86 = {
        (s85[A[0]] & x1) | (s85[I[0]] & ~x1),
        (s85[A[1]] & x1) | (s85[I[1]] & ~x1),
        (s85[A[2]] & x1) | (s85[I[2]] & ~x1),
        (s85[A[3]] & x1) | (s85[I[3]] & ~x1),
        (s85[A[4]] & x1) | (s85[I[4]] & ~x1)
    };

    const std::array<d_type, len> s87 = {
        (s86[I[0]] & x2) | (s86[D[0]] & ~x2),
        (s86[I[1]] & x2) | (s86[D[1]] & ~x2),
        (s86[I[2]] & x2) | (s86[D[2]] & ~x2),
        (s86[I[3]] & x2) | (s86[D[3]] & ~x2),
        (s86[I[4]] & x2) | (s86[D[4]] & ~x2)
    };

    const std::array<d_type, len> s88 = {
        (s87[A_inv[0]] & x1) | (s87[I[0]] & ~x1),
        (s87[A_inv[1]] & x1) | (s87[I[1]] & ~x1),
        (s87[A_inv[2]] & x1) | (s87[I[2]] & ~x1),
        (s87[A_inv[3]] & x1) | (s87[I[3]] & ~x1),
        (s87[A_inv[4]] & x1) | (s87[I[4]] & ~x1)
    };

    const std::array<d_type, len> s89 = {
        (s88[I[0]] & x2) | (s88[D_inv[0]] & ~x2),
        (s88[I[1]] & x2) | (s88[D_inv[1]] & ~x2),
        (s88[I[2]] & x2) | (s88[D_inv[2]] & ~x2),
        (s88[I[3]] & x2) | (s88[D_inv[3]] & ~x2),
        (s88[I[4]] & x2) | (s88[D_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s90 = {
        s89[E[0]],
        s89[E[1]],
        s89[E[2]],
        s89[E[3]],
        s89[E[4]]
    };

    const std::array<d_type, len> s91 = {
        (s90[I[0]] & x1) | (s90[D[0]] & ~x1),
        (s90[I[1]] & x1) | (s90[D[1]] & ~x1),
        (s90[I[2]] & x1) | (s90[D[2]] & ~x1),
        (s90[I[3]] & x1) | (s90[D[3]] & ~x1),
        (s90[I[4]] & x1) | (s90[D[4]] & ~x1)
    };

    const std::array<d_type, len> s92 = {
        (s91[C[0]] & x2) | (s91[I[0]] & ~x2),
        (s91[C[1]] & x2) | (s91[I[1]] & ~x2),
        (s91[C[2]] & x2) | (s91[I[2]] & ~x2),
        (s91[C[3]] & x2) | (s91[I[3]] & ~x2),
        (s91[C[4]] & x2) | (s91[I[4]] & ~x2)
    };

    const std::array<d_type, len> s93 = {
        (s92[I[0]] & x1) | (s92[D_inv[0]] & ~x1),
        (s92[I[1]] & x1) | (s92[D_inv[1]] & ~x1),
        (s92[I[2]] & x1) | (s92[D_inv[2]] & ~x1),
        (s92[I[3]] & x1) | (s92[D_inv[3]] & ~x1),
        (s92[I[4]] & x1) | (s92[D_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s94 = {
        (s93[C_inv[0]] & x2) | (s93[I[0]] & ~x2),
        (s93[C_inv[1]] & x2) | (s93[I[1]] & ~x2),
        (s93[C_inv[2]] & x2) | (s93[I[2]] & ~x2),
        (s93[C_inv[3]] & x2) | (s93[I[3]] & ~x2),
        (s93[C_inv[4]] & x2) | (s93[I[4]] & ~x2)
    };

    const std::array<d_type, len> s95 = {
        s94[B[0]],
        s94[B[1]],
        s94[B[2]],
        s94[B[3]],
        s94[B[4]]
    };

    const std::array<d_type, len> s96 = {
        (s95[D[0]] & x1) | (s95[I[0]] & ~x1),
        (s95[D[1]] & x1) | (s95[I[1]] & ~x1),
        (s95[D[2]] & x1) | (s95[I[2]] & ~x1),
        (s95[D[3]] & x1) | (s95[I[3]] & ~x1),
        (s95[D[4]] & x1) | (s95[I[4]] & ~x1)
    };

    const std::array<d_type, len> s97 = {
        (s96[I[0]] & x2) | (s96[A[0]] & ~x2),
        (s96[I[1]] & x2) | (s96[A[1]] & ~x2),
        (s96[I[2]] & x2) | (s96[A[2]] & ~x2),
        (s96[I[3]] & x2) | (s96[A[3]] & ~x2),
        (s96[I[4]] & x2) | (s96[A[4]] & ~x2)
    };

    const std::array<d_type, len> s98 = {
        (s97[D_inv[0]] & x1) | (s97[I[0]] & ~x1),
        (s97[D_inv[1]] & x1) | (s97[I[1]] & ~x1),
        (s97[D_inv[2]] & x1) | (s97[I[2]] & ~x1),
        (s97[D_inv[3]] & x1) | (s97[I[3]] & ~x1),
        (s97[D_inv[4]] & x1) | (s97[I[4]] & ~x1)
    };

    const std::array<d_type, len> s99 = {
        (s98[I[0]] & x2) | (s98[A_inv[0]] & ~x2),
        (s98[I[1]] & x2) | (s98[A_inv[1]] & ~x2),
        (s98[I[2]] & x2) | (s98[A_inv[2]] & ~x2),
        (s98[I[3]] & x2) | (s98[A_inv[3]] & ~x2),
        (s98[I[4]] & x2) | (s98[A_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s100 = {
        s99[E_inv[0]],
        s99[E_inv[1]],
        s99[E_inv[2]],
        s99[E_inv[3]],
        s99[E_inv[4]]
    };

    const std::array<d_type, len> s101 = {
        (s100[I[0]] & x1) | (s100[C[0]] & ~x1),
        (s100[I[1]] & x1) | (s100[C[1]] & ~x1),
        (s100[I[2]] & x1) | (s100[C[2]] & ~x1),
        (s100[I[3]] & x1) | (s100[C[3]] & ~x1),
        (s100[I[4]] & x1) | (s100[C[4]] & ~x1)
    };

    const std::array<d_type, len> s102 = {
        (s101[D[0]] & x2) | (s101[I[0]] & ~x2),
        (s101[D[1]] & x2) | (s101[I[1]] & ~x2),
        (s101[D[2]] & x2) | (s101[I[2]] & ~x2),
        (s101[D[3]] & x2) | (s101[I[3]] & ~x2),
        (s101[D[4]] & x2) | (s101[I[4]] & ~x2)
    };

    const std::array<d_type, len> s103 = {
        (s102[I[0]] & x1) | (s102[C_inv[0]] & ~x1),
        (s102[I[1]] & x1) | (s102[C_inv[1]] & ~x1),
        (s102[I[2]] & x1) | (s102[C_inv[2]] & ~x1),
        (s102[I[3]] & x1) | (s102[C_inv[3]] & ~x1),
        (s102[I[4]] & x1) | (s102[C_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s104 = {
        (s103[D_inv[0]] & x2) | (s103[I[0]] & ~x2),
        (s103[D_inv[1]] & x2) | (s103[I[1]] & ~x2),
        (s103[D_inv[2]] & x2) | (s103[I[2]] & ~x2),
        (s103[D_inv[3]] & x2) | (s103[I[3]] & ~x2),
        (s103[D_inv[4]] & x2) | (s103[I[4]] & ~x2)
    };

    const std::array<d_type, len> s105 = {
        s104[B_inv[0]],
        s104[B_inv[1]],
        s104[B_inv[2]],
        s104[B_inv[3]],
        s104[B_inv[4]]
    };

    const std::array<d_type, len> s106 = {
        (s105[B[0]] & x3) | (s105[I[0]] & ~x3),
        (s105[B[1]] & x3) | (s105[I[1]] & ~x3),
        (s105[B[2]] & x3) | (s105[I[2]] & ~x3),
        (s105[B[3]] & x3) | (s105[I[3]] & ~x3),
        (s105[B[4]] & x3) | (s105[I[4]] & ~x3)
    };

    const std::array<d_type, len> s107 = {
        (s106[E[0]] & x4) | (s106[I[0]] & ~x4),
        (s106[E[1]] & x4) | (s106[I[1]] & ~x4),
        (s106[E[2]] & x4) | (s106[I[2]] & ~x4),
        (s106[E[3]] & x4) | (s106[I[3]] & ~x4),
        (s106[E[4]] & x4) | (s106[I[4]] & ~x4)
    };

    const std::array<d_type, len> s108 = {
        (s107[B_inv[0]] & x3) | (s107[I[0]] & ~x3),
        (s107[B_inv[1]] & x3) | (s107[I[1]] & ~x3),
        (s107[B_inv[2]] & x3) | (s107[I[2]] & ~x3),
        (s107[B_inv[3]] & x3) | (s107[I[3]] & ~x3),
        (s107[B_inv[4]] & x3) | (s107[I[4]] & ~x3)
    };

    const std::array<d_type, len> s109 = {
        (s108[E_inv[0]] & x4) | (s108[I[0]] & ~x4),
        (s108[E_inv[1]] & x4) | (s108[I[1]] & ~x4),
        (s108[E_inv[2]] & x4) | (s108[I[2]] & ~x4),
        (s108[E_inv[3]] & x4) | (s108[I[3]] & ~x4),
        (s108[E_inv[4]] & x4) | (s108[I[4]] & ~x4)
    };

    const std::array<d_type, len> s110 = {
        s109[D[0]],
        s109[D[1]],
        s109[D[2]],
        s109[D[3]],
        s109[D[4]]
    };

    const std::array<d_type, len> s111 = {
        (s110[I[0]] & x3) | (s110[A[0]] & ~x3),
        (s110[I[1]] & x3) | (s110[A[1]] & ~x3),
        (s110[I[2]] & x3) | (s110[A[2]] & ~x3),
        (s110[I[3]] & x3) | (s110[A[3]] & ~x3),
        (s110[I[4]] & x3) | (s110[A[4]] & ~x3)
    };

    const std::array<d_type, len> s112 = {
        (s111[I[0]] & x4) | (s111[D[0]] & ~x4),
        (s111[I[1]] & x4) | (s111[D[1]] & ~x4),
        (s111[I[2]] & x4) | (s111[D[2]] & ~x4),
        (s111[I[3]] & x4) | (s111[D[3]] & ~x4),
        (s111[I[4]] & x4) | (s111[D[4]] & ~x4)
    };

    const std::array<d_type, len> s113 = {
        (s112[I[0]] & x3) | (s112[A_inv[0]] & ~x3),
        (s112[I[1]] & x3) | (s112[A_inv[1]] & ~x3),
        (s112[I[2]] & x3) | (s112[A_inv[2]] & ~x3),
        (s112[I[3]] & x3) | (s112[A_inv[3]] & ~x3),
        (s112[I[4]] & x3) | (s112[A_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s114 = {
        (s113[I[0]] & x4) | (s113[D_inv[0]] & ~x4),
        (s113[I[1]] & x4) | (s113[D_inv[1]] & ~x4),
        (s113[I[2]] & x4) | (s113[D_inv[2]] & ~x4),
        (s113[I[3]] & x4) | (s113[D_inv[3]] & ~x4),
        (s113[I[4]] & x4) | (s113[D_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s115 = {
        s114[E[0]],
        s114[E[1]],
        s114[E[2]],
        s114[E[3]],
        s114[E[4]]
    };

    const std::array<d_type, len> s116 = {
        (s115[E[0]] & x3) | (s115[I[0]] & ~x3),
        (s115[E[1]] & x3) | (s115[I[1]] & ~x3),
        (s115[E[2]] & x3) | (s115[I[2]] & ~x3),
        (s115[E[3]] & x3) | (s115[I[3]] & ~x3),
        (s115[E[4]] & x3) | (s115[I[4]] & ~x3)
    };

    const std::array<d_type, len> s117 = {
        (s116[B[0]] & x4) | (s116[I[0]] & ~x4),
        (s116[B[1]] & x4) | (s116[I[1]] & ~x4),
        (s116[B[2]] & x4) | (s116[I[2]] & ~x4),
        (s116[B[3]] & x4) | (s116[I[3]] & ~x4),
        (s116[B[4]] & x4) | (s116[I[4]] & ~x4)
    };

    const std::array<d_type, len> s118 = {
        (s117[E_inv[0]] & x3) | (s117[I[0]] & ~x3),
        (s117[E_inv[1]] & x3) | (s117[I[1]] & ~x3),
        (s117[E_inv[2]] & x3) | (s117[I[2]] & ~x3),
        (s117[E_inv[3]] & x3) | (s117[I[3]] & ~x3),
        (s117[E_inv[4]] & x3) | (s117[I[4]] & ~x3)
    };

    const std::array<d_type, len> s119 = {
        (s118[B_inv[0]] & x4) | (s118[I[0]] & ~x4),
        (s118[B_inv[1]] & x4) | (s118[I[1]] & ~x4),
        (s118[B_inv[2]] & x4) | (s118[I[2]] & ~x4),
        (s118[B_inv[3]] & x4) | (s118[I[3]] & ~x4),
        (s118[B_inv[4]] & x4) | (s118[I[4]] & ~x4)
    };

    const std::array<d_type, len> s120 = {
        s119[D_inv[0]],
        s119[D_inv[1]],
        s119[D_inv[2]],
        s119[D_inv[3]],
        s119[D_inv[4]]
    };

    const std::array<d_type, len> s121 = {
        (s120[I[0]] & x3) | (s120[D[0]] & ~x3),
        (s120[I[1]] & x3) | (s120[D[1]] & ~x3),
        (s120[I[2]] & x3) | (s120[D[2]] & ~x3),
        (s120[I[3]] & x3) | (s120[D[3]] & ~x3),
        (s120[I[4]] & x3) | (s120[D[4]] & ~x3)
    };

    const std::array<d_type, len> s122 = {
        (s121[I[0]] & x4) | (s121[A[0]] & ~x4),
        (s121[I[1]] & x4) | (s121[A[1]] & ~x4),
        (s121[I[2]] & x4) | (s121[A[2]] & ~x4),
        (s121[I[3]] & x4) | (s121[A[3]] & ~x4),
        (s121[I[4]] & x4) | (s121[A[4]] & ~x4)
    };

    const std::array<d_type, len> s123 = {
        (s122[I[0]] & x3) | (s122[D_inv[0]] & ~x3),
        (s122[I[1]] & x3) | (s122[D_inv[1]] & ~x3),
        (s122[I[2]] & x3) | (s122[D_inv[2]] & ~x3),
        (s122[I[3]] & x3) | (s122[D_inv[3]] & ~x3),
        (s122[I[4]] & x3) | (s122[D_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s124 = {
        (s123[I[0]] & x4) | (s123[A_inv[0]] & ~x4),
        (s123[I[1]] & x4) | (s123[A_inv[1]] & ~x4),
        (s123[I[2]] & x4) | (s123[A_inv[2]] & ~x4),
        (s123[I[3]] & x4) | (s123[A_inv[3]] & ~x4),
        (s123[I[4]] & x4) | (s123[A_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s125 = {
        s124[E_inv[0]],
        s124[E_inv[1]],
        s124[E_inv[2]],
        s124[E_inv[3]],
        s124[E_inv[4]]
    };

    const std::array<d_type, len> s126 = {
        (s125[D[0]] & x1) | (s125[I[0]] & ~x1),
        (s125[D[1]] & x1) | (s125[I[1]] & ~x1),
        (s125[D[2]] & x1) | (s125[I[2]] & ~x1),
        (s125[D[3]] & x1) | (s125[I[3]] & ~x1),
        (s125[D[4]] & x1) | (s125[I[4]] & ~x1)
    };

    const std::array<d_type, len> s127 = {
        (s126[I[0]] & x2) | (s126[C[0]] & ~x2),
        (s126[I[1]] & x2) | (s126[C[1]] & ~x2),
        (s126[I[2]] & x2) | (s126[C[2]] & ~x2),
        (s126[I[3]] & x2) | (s126[C[3]] & ~x2),
        (s126[I[4]] & x2) | (s126[C[4]] & ~x2)
    };

    const std::array<d_type, len> s128 = {
        (s127[D_inv[0]] & x1) | (s127[I[0]] & ~x1),
        (s127[D_inv[1]] & x1) | (s127[I[1]] & ~x1),
        (s127[D_inv[2]] & x1) | (s127[I[2]] & ~x1),
        (s127[D_inv[3]] & x1) | (s127[I[3]] & ~x1),
        (s127[D_inv[4]] & x1) | (s127[I[4]] & ~x1)
    };

    const std::array<d_type, len> s129 = {
        (s128[I[0]] & x2) | (s128[C_inv[0]] & ~x2),
        (s128[I[1]] & x2) | (s128[C_inv[1]] & ~x2),
        (s128[I[2]] & x2) | (s128[C_inv[2]] & ~x2),
        (s128[I[3]] & x2) | (s128[C_inv[3]] & ~x2),
        (s128[I[4]] & x2) | (s128[C_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s130 = {
        s129[B[0]],
        s129[B[1]],
        s129[B[2]],
        s129[B[3]],
        s129[B[4]]
    };

    const std::array<d_type, len> s131 = {
        (s130[I[0]] & x1) | (s130[A[0]] & ~x1),
        (s130[I[1]] & x1) | (s130[A[1]] & ~x1),
        (s130[I[2]] & x1) | (s130[A[2]] & ~x1),
        (s130[I[3]] & x1) | (s130[A[3]] & ~x1),
        (s130[I[4]] & x1) | (s130[A[4]] & ~x1)
    };

    const std::array<d_type, len> s132 = {
        (s131[D[0]] & x2) | (s131[I[0]] & ~x2),
        (s131[D[1]] & x2) | (s131[I[1]] & ~x2),
        (s131[D[2]] & x2) | (s131[I[2]] & ~x2),
        (s131[D[3]] & x2) | (s131[I[3]] & ~x2),
        (s131[D[4]] & x2) | (s131[I[4]] & ~x2)
    };

    const std::array<d_type, len> s133 = {
        (s132[I[0]] & x1) | (s132[A_inv[0]] & ~x1),
        (s132[I[1]] & x1) | (s132[A_inv[1]] & ~x1),
        (s132[I[2]] & x1) | (s132[A_inv[2]] & ~x1),
        (s132[I[3]] & x1) | (s132[A_inv[3]] & ~x1),
        (s132[I[4]] & x1) | (s132[A_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s134 = {
        (s133[D_inv[0]] & x2) | (s133[I[0]] & ~x2),
        (s133[D_inv[1]] & x2) | (s133[I[1]] & ~x2),
        (s133[D_inv[2]] & x2) | (s133[I[2]] & ~x2),
        (s133[D_inv[3]] & x2) | (s133[I[3]] & ~x2),
        (s133[D_inv[4]] & x2) | (s133[I[4]] & ~x2)
    };

    const std::array<d_type, len> s135 = {
        s134[E[0]],
        s134[E[1]],
        s134[E[2]],
        s134[E[3]],
        s134[E[4]]
    };

    const std::array<d_type, len> s136 = {
        (s135[C[0]] & x1) | (s135[I[0]] & ~x1),
        (s135[C[1]] & x1) | (s135[I[1]] & ~x1),
        (s135[C[2]] & x1) | (s135[I[2]] & ~x1),
        (s135[C[3]] & x1) | (s135[I[3]] & ~x1),
        (s135[C[4]] & x1) | (s135[I[4]] & ~x1)
    };

    const std::array<d_type, len> s137 = {
        (s136[I[0]] & x2) | (s136[D[0]] & ~x2),
        (s136[I[1]] & x2) | (s136[D[1]] & ~x2),
        (s136[I[2]] & x2) | (s136[D[2]] & ~x2),
        (s136[I[3]] & x2) | (s136[D[3]] & ~x2),
        (s136[I[4]] & x2) | (s136[D[4]] & ~x2)
    };

    const std::array<d_type, len> s138 = {
        (s137[C_inv[0]] & x1) | (s137[I[0]] & ~x1),
        (s137[C_inv[1]] & x1) | (s137[I[1]] & ~x1),
        (s137[C_inv[2]] & x1) | (s137[I[2]] & ~x1),
        (s137[C_inv[3]] & x1) | (s137[I[3]] & ~x1),
        (s137[C_inv[4]] & x1) | (s137[I[4]] & ~x1)
    };

    const std::array<d_type, len> s139 = {
        (s138[I[0]] & x2) | (s138[D_inv[0]] & ~x2),
        (s138[I[1]] & x2) | (s138[D_inv[1]] & ~x2),
        (s138[I[2]] & x2) | (s138[D_inv[2]] & ~x2),
        (s138[I[3]] & x2) | (s138[D_inv[3]] & ~x2),
        (s138[I[4]] & x2) | (s138[D_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s140 = {
        s139[B_inv[0]],
        s139[B_inv[1]],
        s139[B_inv[2]],
        s139[B_inv[3]],
        s139[B_inv[4]]
    };

    const std::array<d_type, len> s141 = {
        (s140[I[0]] & x1) | (s140[D[0]] & ~x1),
        (s140[I[1]] & x1) | (s140[D[1]] & ~x1),
        (s140[I[2]] & x1) | (s140[D[2]] & ~x1),
        (s140[I[3]] & x1) | (s140[D[3]] & ~x1),
        (s140[I[4]] & x1) | (s140[D[4]] & ~x1)
    };

    const std::array<d_type, len> s142 = {
        (s141[A[0]] & x2) | (s141[I[0]] & ~x2),
        (s141[A[1]] & x2) | (s141[I[1]] & ~x2),
        (s141[A[2]] & x2) | (s141[I[2]] & ~x2),
        (s141[A[3]] & x2) | (s141[I[3]] & ~x2),
        (s141[A[4]] & x2) | (s141[I[4]] & ~x2)
    };

    const std::array<d_type, len> s143 = {
        (s142[I[0]] & x1) | (s142[D_inv[0]] & ~x1),
        (s142[I[1]] & x1) | (s142[D_inv[1]] & ~x1),
        (s142[I[2]] & x1) | (s142[D_inv[2]] & ~x1),
        (s142[I[3]] & x1) | (s142[D_inv[3]] & ~x1),
        (s142[I[4]] & x1) | (s142[D_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s144 = {
        (s143[A_inv[0]] & x2) | (s143[I[0]] & ~x2),
        (s143[A_inv[1]] & x2) | (s143[I[1]] & ~x2),
        (s143[A_inv[2]] & x2) | (s143[I[2]] & ~x2),
        (s143[A_inv[3]] & x2) | (s143[I[3]] & ~x2),
        (s143[A_inv[4]] & x2) | (s143[I[4]] & ~x2)
    };

    const std::array<d_type, len> s145 = {
        s144[E_inv[0]],
        s144[E_inv[1]],
        s144[E_inv[2]],
        s144[E_inv[3]],
        s144[E_inv[4]]
    };

    const std::array<d_type, len> s146 = {
        (s145[A[0]] & x3) | (s145[I[0]] & ~x3),
        (s145[A[1]] & x3) | (s145[I[1]] & ~x3),
        (s145[A[2]] & x3) | (s145[I[2]] & ~x3),
        (s145[A[3]] & x3) | (s145[I[3]] & ~x3),
        (s145[A[4]] & x3) | (s145[I[4]] & ~x3)
    };

    const std::array<d_type, len> s147 = {
        (s146[D[0]] & x4) | (s146[I[0]] & ~x4),
        (s146[D[1]] & x4) | (s146[I[1]] & ~x4),
        (s146[D[2]] & x4) | (s146[I[2]] & ~x4),
        (s146[D[3]] & x4) | (s146[I[3]] & ~x4),
        (s146[D[4]] & x4) | (s146[I[4]] & ~x4)
    };

    const std::array<d_type, len> s148 = {
        (s147[A_inv[0]] & x3) | (s147[I[0]] & ~x3),
        (s147[A_inv[1]] & x3) | (s147[I[1]] & ~x3),
        (s147[A_inv[2]] & x3) | (s147[I[2]] & ~x3),
        (s147[A_inv[3]] & x3) | (s147[I[3]] & ~x3),
        (s147[A_inv[4]] & x3) | (s147[I[4]] & ~x3)
    };

    const std::array<d_type, len> s149 = {
        (s148[D_inv[0]] & x4) | (s148[I[0]] & ~x4),
        (s148[D_inv[1]] & x4) | (s148[I[1]] & ~x4),
        (s148[D_inv[2]] & x4) | (s148[I[2]] & ~x4),
        (s148[D_inv[3]] & x4) | (s148[I[3]] & ~x4),
        (s148[D_inv[4]] & x4) | (s148[I[4]] & ~x4)
    };

    const std::array<d_type, len> s150 = {
        s149[E[0]],
        s149[E[1]],
        s149[E[2]],
        s149[E[3]],
        s149[E[4]]
    };

    const std::array<d_type, len> s151 = {
        (s150[I[0]] & x3) | (s150[B[0]] & ~x3),
        (s150[I[1]] & x3) | (s150[B[1]] & ~x3),
        (s150[I[2]] & x3) | (s150[B[2]] & ~x3),
        (s150[I[3]] & x3) | (s150[B[3]] & ~x3),
        (s150[I[4]] & x3) | (s150[B[4]] & ~x3)
    };

    const std::array<d_type, len> s152 = {
        (s151[I[0]] & x4) | (s151[E[0]] & ~x4),
        (s151[I[1]] & x4) | (s151[E[1]] & ~x4),
        (s151[I[2]] & x4) | (s151[E[2]] & ~x4),
        (s151[I[3]] & x4) | (s151[E[3]] & ~x4),
        (s151[I[4]] & x4) | (s151[E[4]] & ~x4)
    };

    const std::array<d_type, len> s153 = {
        (s152[I[0]] & x3) | (s152[B_inv[0]] & ~x3),
        (s152[I[1]] & x3) | (s152[B_inv[1]] & ~x3),
        (s152[I[2]] & x3) | (s152[B_inv[2]] & ~x3),
        (s152[I[3]] & x3) | (s152[B_inv[3]] & ~x3),
        (s152[I[4]] & x3) | (s152[B_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s154 = {
        (s153[I[0]] & x4) | (s153[E_inv[0]] & ~x4),
        (s153[I[1]] & x4) | (s153[E_inv[1]] & ~x4),
        (s153[I[2]] & x4) | (s153[E_inv[2]] & ~x4),
        (s153[I[3]] & x4) | (s153[E_inv[3]] & ~x4),
        (s153[I[4]] & x4) | (s153[E_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s155 = {
        s154[D[0]],
        s154[D[1]],
        s154[D[2]],
        s154[D[3]],
        s154[D[4]]
    };

    const std::array<d_type, len> s156 = {
        (s155[D[0]] & x3) | (s155[I[0]] & ~x3),
        (s155[D[1]] & x3) | (s155[I[1]] & ~x3),
        (s155[D[2]] & x3) | (s155[I[2]] & ~x3),
        (s155[D[3]] & x3) | (s155[I[3]] & ~x3),
        (s155[D[4]] & x3) | (s155[I[4]] & ~x3)
    };

    const std::array<d_type, len> s157 = {
        (s156[A[0]] & x4) | (s156[I[0]] & ~x4),
        (s156[A[1]] & x4) | (s156[I[1]] & ~x4),
        (s156[A[2]] & x4) | (s156[I[2]] & ~x4),
        (s156[A[3]] & x4) | (s156[I[3]] & ~x4),
        (s156[A[4]] & x4) | (s156[I[4]] & ~x4)
    };

    const std::array<d_type, len> s158 = {
        (s157[D_inv[0]] & x3) | (s157[I[0]] & ~x3),
        (s157[D_inv[1]] & x3) | (s157[I[1]] & ~x3),
        (s157[D_inv[2]] & x3) | (s157[I[2]] & ~x3),
        (s157[D_inv[3]] & x3) | (s157[I[3]] & ~x3),
        (s157[D_inv[4]] & x3) | (s157[I[4]] & ~x3)
    };

    const std::array<d_type, len> s159 = {
        (s158[A_inv[0]] & x4) | (s158[I[0]] & ~x4),
        (s158[A_inv[1]] & x4) | (s158[I[1]] & ~x4),
        (s158[A_inv[2]] & x4) | (s158[I[2]] & ~x4),
        (s158[A_inv[3]] & x4) | (s158[I[3]] & ~x4),
        (s158[A_inv[4]] & x4) | (s158[I[4]] & ~x4)
    };

    const std::array<d_type, len> s160 = {
        s159[E_inv[0]],
        s159[E_inv[1]],
        s159[E_inv[2]],
        s159[E_inv[3]],
        s159[E_inv[4]]
    };

    const std::array<d_type, len> s161 = {
        (s160[I[0]] & x3) | (s160[E[0]] & ~x3),
        (s160[I[1]] & x3) | (s160[E[1]] & ~x3),
        (s160[I[2]] & x3) | (s160[E[2]] & ~x3),
        (s160[I[3]] & x3) | (s160[E[3]] & ~x3),
        (s160[I[4]] & x3) | (s160[E[4]] & ~x3)
    };

    const std::array<d_type, len> s162 = {
        (s161[I[0]] & x4) | (s161[B[0]] & ~x4),
        (s161[I[1]] & x4) | (s161[B[1]] & ~x4),
        (s161[I[2]] & x4) | (s161[B[2]] & ~x4),
        (s161[I[3]] & x4) | (s161[B[3]] & ~x4),
        (s161[I[4]] & x4) | (s161[B[4]] & ~x4)
    };

    const std::array<d_type, len> s163 = {
        (s162[I[0]] & x3) | (s162[E_inv[0]] & ~x3),
        (s162[I[1]] & x3) | (s162[E_inv[1]] & ~x3),
        (s162[I[2]] & x3) | (s162[E_inv[2]] & ~x3),
        (s162[I[3]] & x3) | (s162[E_inv[3]] & ~x3),
        (s162[I[4]] & x3) | (s162[E_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s164 = {
        (s163[I[0]] & x4) | (s163[B_inv[0]] & ~x4),
        (s163[I[1]] & x4) | (s163[B_inv[1]] & ~x4),
        (s163[I[2]] & x4) | (s163[B_inv[2]] & ~x4),
        (s163[I[3]] & x4) | (s163[B_inv[3]] & ~x4),
        (s163[I[4]] & x4) | (s163[B_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s165 = {
        s164[D_inv[0]],
        s164[D_inv[1]],
        s164[D_inv[2]],
        s164[D_inv[3]],
        s164[D_inv[4]]
    };

    const std::array<d_type, len> s166 = {
        s165[B[0]],
        s165[B[1]],
        s165[B[2]],
        s165[B[3]],
        s165[B[4]]
    };

    const std::array<d_type, len> s167 = {
        (s166[D[0]] & x1) | (s166[I[0]] & ~x1),
        (s166[D[1]] & x1) | (s166[I[1]] & ~x1),
        (s166[D[2]] & x1) | (s166[I[2]] & ~x1),
        (s166[D[3]] & x1) | (s166[I[3]] & ~x1),
        (s166[D[4]] & x1) | (s166[I[4]] & ~x1)
    };

    const std::array<d_type, len> s168 = {
        (s167[I[0]] & x2) | (s167[C[0]] & ~x2),
        (s167[I[1]] & x2) | (s167[C[1]] & ~x2),
        (s167[I[2]] & x2) | (s167[C[2]] & ~x2),
        (s167[I[3]] & x2) | (s167[C[3]] & ~x2),
        (s167[I[4]] & x2) | (s167[C[4]] & ~x2)
    };

    const std::array<d_type, len> s169 = {
        (s168[D_inv[0]] & x1) | (s168[I[0]] & ~x1),
        (s168[D_inv[1]] & x1) | (s168[I[1]] & ~x1),
        (s168[D_inv[2]] & x1) | (s168[I[2]] & ~x1),
        (s168[D_inv[3]] & x1) | (s168[I[3]] & ~x1),
        (s168[D_inv[4]] & x1) | (s168[I[4]] & ~x1)
    };

    const std::array<d_type, len> s170 = {
        (s169[I[0]] & x2) | (s169[C_inv[0]] & ~x2),
        (s169[I[1]] & x2) | (s169[C_inv[1]] & ~x2),
        (s169[I[2]] & x2) | (s169[C_inv[2]] & ~x2),
        (s169[I[3]] & x2) | (s169[C_inv[3]] & ~x2),
        (s169[I[4]] & x2) | (s169[C_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s171 = {
        s170[B[0]],
        s170[B[1]],
        s170[B[2]],
        s170[B[3]],
        s170[B[4]]
    };

    const std::array<d_type, len> s172 = {
        (s171[I[0]] & x1) | (s171[A[0]] & ~x1),
        (s171[I[1]] & x1) | (s171[A[1]] & ~x1),
        (s171[I[2]] & x1) | (s171[A[2]] & ~x1),
        (s171[I[3]] & x1) | (s171[A[3]] & ~x1),
        (s171[I[4]] & x1) | (s171[A[4]] & ~x1)
    };

    const std::array<d_type, len> s173 = {
        (s172[D[0]] & x2) | (s172[I[0]] & ~x2),
        (s172[D[1]] & x2) | (s172[I[1]] & ~x2),
        (s172[D[2]] & x2) | (s172[I[2]] & ~x2),
        (s172[D[3]] & x2) | (s172[I[3]] & ~x2),
        (s172[D[4]] & x2) | (s172[I[4]] & ~x2)
    };

    const std::array<d_type, len> s174 = {
        (s173[I[0]] & x1) | (s173[A_inv[0]] & ~x1),
        (s173[I[1]] & x1) | (s173[A_inv[1]] & ~x1),
        (s173[I[2]] & x1) | (s173[A_inv[2]] & ~x1),
        (s173[I[3]] & x1) | (s173[A_inv[3]] & ~x1),
        (s173[I[4]] & x1) | (s173[A_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s175 = {
        (s174[D_inv[0]] & x2) | (s174[I[0]] & ~x2),
        (s174[D_inv[1]] & x2) | (s174[I[1]] & ~x2),
        (s174[D_inv[2]] & x2) | (s174[I[2]] & ~x2),
        (s174[D_inv[3]] & x2) | (s174[I[3]] & ~x2),
        (s174[D_inv[4]] & x2) | (s174[I[4]] & ~x2)
    };

    const std::array<d_type, len> s176 = {
        s175[E[0]],
        s175[E[1]],
        s175[E[2]],
        s175[E[3]],
        s175[E[4]]
    };

    const std::array<d_type, len> s177 = {
        (s176[C[0]] & x1) | (s176[I[0]] & ~x1),
        (s176[C[1]] & x1) | (s176[I[1]] & ~x1),
        (s176[C[2]] & x1) | (s176[I[2]] & ~x1),
        (s176[C[3]] & x1) | (s176[I[3]] & ~x1),
        (s176[C[4]] & x1) | (s176[I[4]] & ~x1)
    };

    const std::array<d_type, len> s178 = {
        (s177[I[0]] & x2) | (s177[D[0]] & ~x2),
        (s177[I[1]] & x2) | (s177[D[1]] & ~x2),
        (s177[I[2]] & x2) | (s177[D[2]] & ~x2),
        (s177[I[3]] & x2) | (s177[D[3]] & ~x2),
        (s177[I[4]] & x2) | (s177[D[4]] & ~x2)
    };

    const std::array<d_type, len> s179 = {
        (s178[C_inv[0]] & x1) | (s178[I[0]] & ~x1),
        (s178[C_inv[1]] & x1) | (s178[I[1]] & ~x1),
        (s178[C_inv[2]] & x1) | (s178[I[2]] & ~x1),
        (s178[C_inv[3]] & x1) | (s178[I[3]] & ~x1),
        (s178[C_inv[4]] & x1) | (s178[I[4]] & ~x1)
    };

    const std::array<d_type, len> s180 = {
        (s179[I[0]] & x2) | (s179[D_inv[0]] & ~x2),
        (s179[I[1]] & x2) | (s179[D_inv[1]] & ~x2),
        (s179[I[2]] & x2) | (s179[D_inv[2]] & ~x2),
        (s179[I[3]] & x2) | (s179[D_inv[3]] & ~x2),
        (s179[I[4]] & x2) | (s179[D_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s181 = {
        s180[B_inv[0]],
        s180[B_inv[1]],
        s180[B_inv[2]],
        s180[B_inv[3]],
        s180[B_inv[4]]
    };

    const std::array<d_type, len> s182 = {
        (s181[I[0]] & x1) | (s181[D[0]] & ~x1),
        (s181[I[1]] & x1) | (s181[D[1]] & ~x1),
        (s181[I[2]] & x1) | (s181[D[2]] & ~x1),
        (s181[I[3]] & x1) | (s181[D[3]] & ~x1),
        (s181[I[4]] & x1) | (s181[D[4]] & ~x1)
    };

    const std::array<d_type, len> s183 = {
        (s182[A[0]] & x2) | (s182[I[0]] & ~x2),
        (s182[A[1]] & x2) | (s182[I[1]] & ~x2),
        (s182[A[2]] & x2) | (s182[I[2]] & ~x2),
        (s182[A[3]] & x2) | (s182[I[3]] & ~x2),
        (s182[A[4]] & x2) | (s182[I[4]] & ~x2)
    };

    const std::array<d_type, len> s184 = {
        (s183[I[0]] & x1) | (s183[D_inv[0]] & ~x1),
        (s183[I[1]] & x1) | (s183[D_inv[1]] & ~x1),
        (s183[I[2]] & x1) | (s183[D_inv[2]] & ~x1),
        (s183[I[3]] & x1) | (s183[D_inv[3]] & ~x1),
        (s183[I[4]] & x1) | (s183[D_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s185 = {
        (s184[A_inv[0]] & x2) | (s184[I[0]] & ~x2),
        (s184[A_inv[1]] & x2) | (s184[I[1]] & ~x2),
        (s184[A_inv[2]] & x2) | (s184[I[2]] & ~x2),
        (s184[A_inv[3]] & x2) | (s184[I[3]] & ~x2),
        (s184[A_inv[4]] & x2) | (s184[I[4]] & ~x2)
    };

    const std::array<d_type, len> s186 = {
        s185[E_inv[0]],
        s185[E_inv[1]],
        s185[E_inv[2]],
        s185[E_inv[3]],
        s185[E_inv[4]]
    };

    const std::array<d_type, len> s187 = {
        s186[D[0]],
        s186[D[1]],
        s186[D[2]],
        s186[D[3]],
        s186[D[4]]
    };

    const std::array<d_type, len> s188 = {
        (s187[B[0]] & x3) | (s187[I[0]] & ~x3),
        (s187[B[1]] & x3) | (s187[I[1]] & ~x3),
        (s187[B[2]] & x3) | (s187[I[2]] & ~x3),
        (s187[B[3]] & x3) | (s187[I[3]] & ~x3),
        (s187[B[4]] & x3) | (s187[I[4]] & ~x3)
    };

    const std::array<d_type, len> s189 = {
        (s188[C[0]] & x4) | (s188[I[0]] & ~x4),
        (s188[C[1]] & x4) | (s188[I[1]] & ~x4),
        (s188[C[2]] & x4) | (s188[I[2]] & ~x4),
        (s188[C[3]] & x4) | (s188[I[3]] & ~x4),
        (s188[C[4]] & x4) | (s188[I[4]] & ~x4)
    };

    const std::array<d_type, len> s190 = {
        (s189[B_inv[0]] & x3) | (s189[I[0]] & ~x3),
        (s189[B_inv[1]] & x3) | (s189[I[1]] & ~x3),
        (s189[B_inv[2]] & x3) | (s189[I[2]] & ~x3),
        (s189[B_inv[3]] & x3) | (s189[I[3]] & ~x3),
        (s189[B_inv[4]] & x3) | (s189[I[4]] & ~x3)
    };

    const std::array<d_type, len> s191 = {
        (s190[C_inv[0]] & x4) | (s190[I[0]] & ~x4),
        (s190[C_inv[1]] & x4) | (s190[I[1]] & ~x4),
        (s190[C_inv[2]] & x4) | (s190[I[2]] & ~x4),
        (s190[C_inv[3]] & x4) | (s190[I[3]] & ~x4),
        (s190[C_inv[4]] & x4) | (s190[I[4]] & ~x4)
    };

    const std::array<d_type, len> s192 = {
        s191[A[0]],
        s191[A[1]],
        s191[A[2]],
        s191[A[3]],
        s191[A[4]]
    };

    const std::array<d_type, len> s193 = {
        (s192[I[0]] & x3) | (s192[B[0]] & ~x3),
        (s192[I[1]] & x3) | (s192[B[1]] & ~x3),
        (s192[I[2]] & x3) | (s192[B[2]] & ~x3),
        (s192[I[3]] & x3) | (s192[B[3]] & ~x3),
        (s192[I[4]] & x3) | (s192[B[4]] & ~x3)
    };

    const std::array<d_type, len> s194 = {
        (s193[I[0]] & x4) | (s193[E[0]] & ~x4),
        (s193[I[1]] & x4) | (s193[E[1]] & ~x4),
        (s193[I[2]] & x4) | (s193[E[2]] & ~x4),
        (s193[I[3]] & x4) | (s193[E[3]] & ~x4),
        (s193[I[4]] & x4) | (s193[E[4]] & ~x4)
    };

    const std::array<d_type, len> s195 = {
        (s194[I[0]] & x3) | (s194[B_inv[0]] & ~x3),
        (s194[I[1]] & x3) | (s194[B_inv[1]] & ~x3),
        (s194[I[2]] & x3) | (s194[B_inv[2]] & ~x3),
        (s194[I[3]] & x3) | (s194[B_inv[3]] & ~x3),
        (s194[I[4]] & x3) | (s194[B_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s196 = {
        (s195[I[0]] & x4) | (s195[E_inv[0]] & ~x4),
        (s195[I[1]] & x4) | (s195[E_inv[1]] & ~x4),
        (s195[I[2]] & x4) | (s195[E_inv[2]] & ~x4),
        (s195[I[3]] & x4) | (s195[E_inv[3]] & ~x4),
        (s195[I[4]] & x4) | (s195[E_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s197 = {
        s196[D[0]],
        s196[D[1]],
        s196[D[2]],
        s196[D[3]],
        s196[D[4]]
    };

    const std::array<d_type, len> s198 = {
        (s197[C[0]] & x3) | (s197[I[0]] & ~x3),
        (s197[C[1]] & x3) | (s197[I[1]] & ~x3),
        (s197[C[2]] & x3) | (s197[I[2]] & ~x3),
        (s197[C[3]] & x3) | (s197[I[3]] & ~x3),
        (s197[C[4]] & x3) | (s197[I[4]] & ~x3)
    };

    const std::array<d_type, len> s199 = {
        (s198[B[0]] & x4) | (s198[I[0]] & ~x4),
        (s198[B[1]] & x4) | (s198[I[1]] & ~x4),
        (s198[B[2]] & x4) | (s198[I[2]] & ~x4),
        (s198[B[3]] & x4) | (s198[I[3]] & ~x4),
        (s198[B[4]] & x4) | (s198[I[4]] & ~x4)
    };

    const std::array<d_type, len> s200 = {
        (s199[C_inv[0]] & x3) | (s199[I[0]] & ~x3),
        (s199[C_inv[1]] & x3) | (s199[I[1]] & ~x3),
        (s199[C_inv[2]] & x3) | (s199[I[2]] & ~x3),
        (s199[C_inv[3]] & x3) | (s199[I[3]] & ~x3),
        (s199[C_inv[4]] & x3) | (s199[I[4]] & ~x3)
    };

    const std::array<d_type, len> s201 = {
        (s200[B_inv[0]] & x4) | (s200[I[0]] & ~x4),
        (s200[B_inv[1]] & x4) | (s200[I[1]] & ~x4),
        (s200[B_inv[2]] & x4) | (s200[I[2]] & ~x4),
        (s200[B_inv[3]] & x4) | (s200[I[3]] & ~x4),
        (s200[B_inv[4]] & x4) | (s200[I[4]] & ~x4)
    };

    const std::array<d_type, len> s202 = {
        s201[A_inv[0]],
        s201[A_inv[1]],
        s201[A_inv[2]],
        s201[A_inv[3]],
        s201[A_inv[4]]
    };

    const std::array<d_type, len> s203 = {
        (s202[I[0]] & x3) | (s202[E[0]] & ~x3),
        (s202[I[1]] & x3) | (s202[E[1]] & ~x3),
        (s202[I[2]] & x3) | (s202[E[2]] & ~x3),
        (s202[I[3]] & x3) | (s202[E[3]] & ~x3),
        (s202[I[4]] & x3) | (s202[E[4]] & ~x3)
    };

    const std::array<d_type, len> s204 = {
        (s203[I[0]] & x4) | (s203[B[0]] & ~x4),
        (s203[I[1]] & x4) | (s203[B[1]] & ~x4),
        (s203[I[2]] & x4) | (s203[B[2]] & ~x4),
        (s203[I[3]] & x4) | (s203[B[3]] & ~x4),
        (s203[I[4]] & x4) | (s203[B[4]] & ~x4)
    };

    const std::array<d_type, len> s205 = {
        (s204[I[0]] & x3) | (s204[E_inv[0]] & ~x3),
        (s204[I[1]] & x3) | (s204[E_inv[1]] & ~x3),
        (s204[I[2]] & x3) | (s204[E_inv[2]] & ~x3),
        (s204[I[3]] & x3) | (s204[E_inv[3]] & ~x3),
        (s204[I[4]] & x3) | (s204[E_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s206 = {
        (s205[I[0]] & x4) | (s205[B_inv[0]] & ~x4),
        (s205[I[1]] & x4) | (s205[B_inv[1]] & ~x4),
        (s205[I[2]] & x4) | (s205[B_inv[2]] & ~x4),
        (s205[I[3]] & x4) | (s205[B_inv[3]] & ~x4),
        (s205[I[4]] & x4) | (s205[B_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s207 = {
        s206[D_inv[0]],
        s206[D_inv[1]],
        s206[D_inv[2]],
        s206[D_inv[3]],
        s206[D_inv[4]]
    };

    const std::array<d_type, len> s208 = {
        s207[E[0]],
        s207[E[1]],
        s207[E[2]],
        s207[E[3]],
        s207[E[4]]
    };

    const std::array<d_type, len> s209 = {
        (s208[A[0]] & x1) | (s208[I[0]] & ~x1),
        (s208[A[1]] & x1) | (s208[I[1]] & ~x1),
        (s208[A[2]] & x1) | (s208[I[2]] & ~x1),
        (s208[A[3]] & x1) | (s208[I[3]] & ~x1),
        (s208[A[4]] & x1) | (s208[I[4]] & ~x1)
    };

    const std::array<d_type, len> s210 = {
        (s209[I[0]] & x2) | (s209[D[0]] & ~x2),
        (s209[I[1]] & x2) | (s209[D[1]] & ~x2),
        (s209[I[2]] & x2) | (s209[D[2]] & ~x2),
        (s209[I[3]] & x2) | (s209[D[3]] & ~x2),
        (s209[I[4]] & x2) | (s209[D[4]] & ~x2)
    };

    const std::array<d_type, len> s211 = {
        (s210[A_inv[0]] & x1) | (s210[I[0]] & ~x1),
        (s210[A_inv[1]] & x1) | (s210[I[1]] & ~x1),
        (s210[A_inv[2]] & x1) | (s210[I[2]] & ~x1),
        (s210[A_inv[3]] & x1) | (s210[I[3]] & ~x1),
        (s210[A_inv[4]] & x1) | (s210[I[4]] & ~x1)
    };

    const std::array<d_type, len> s212 = {
        (s211[I[0]] & x2) | (s211[D_inv[0]] & ~x2),
        (s211[I[1]] & x2) | (s211[D_inv[1]] & ~x2),
        (s211[I[2]] & x2) | (s211[D_inv[2]] & ~x2),
        (s211[I[3]] & x2) | (s211[D_inv[3]] & ~x2),
        (s211[I[4]] & x2) | (s211[D_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s213 = {
        s212[E[0]],
        s212[E[1]],
        s212[E[2]],
        s212[E[3]],
        s212[E[4]]
    };

    const std::array<d_type, len> s214 = {
        (s213[I[0]] & x1) | (s213[D[0]] & ~x1),
        (s213[I[1]] & x1) | (s213[D[1]] & ~x1),
        (s213[I[2]] & x1) | (s213[D[2]] & ~x1),
        (s213[I[3]] & x1) | (s213[D[3]] & ~x1),
        (s213[I[4]] & x1) | (s213[D[4]] & ~x1)
    };

    const std::array<d_type, len> s215 = {
        (s214[C[0]] & x2) | (s214[I[0]] & ~x2),
        (s214[C[1]] & x2) | (s214[I[1]] & ~x2),
        (s214[C[2]] & x2) | (s214[I[2]] & ~x2),
        (s214[C[3]] & x2) | (s214[I[3]] & ~x2),
        (s214[C[4]] & x2) | (s214[I[4]] & ~x2)
    };

    const std::array<d_type, len> s216 = {
        (s215[I[0]] & x1) | (s215[D_inv[0]] & ~x1),
        (s215[I[1]] & x1) | (s215[D_inv[1]] & ~x1),
        (s215[I[2]] & x1) | (s215[D_inv[2]] & ~x1),
        (s215[I[3]] & x1) | (s215[D_inv[3]] & ~x1),
        (s215[I[4]] & x1) | (s215[D_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s217 = {
        (s216[C_inv[0]] & x2) | (s216[I[0]] & ~x2),
        (s216[C_inv[1]] & x2) | (s216[I[1]] & ~x2),
        (s216[C_inv[2]] & x2) | (s216[I[2]] & ~x2),
        (s216[C_inv[3]] & x2) | (s216[I[3]] & ~x2),
        (s216[C_inv[4]] & x2) | (s216[I[4]] & ~x2)
    };

    const std::array<d_type, len> s218 = {
        s217[B[0]],
        s217[B[1]],
        s217[B[2]],
        s217[B[3]],
        s217[B[4]]
    };

    const std::array<d_type, len> s219 = {
        (s218[D[0]] & x1) | (s218[I[0]] & ~x1),
        (s218[D[1]] & x1) | (s218[I[1]] & ~x1),
        (s218[D[2]] & x1) | (s218[I[2]] & ~x1),
        (s218[D[3]] & x1) | (s218[I[3]] & ~x1),
        (s218[D[4]] & x1) | (s218[I[4]] & ~x1)
    };

    const std::array<d_type, len> s220 = {
        (s219[I[0]] & x2) | (s219[A[0]] & ~x2),
        (s219[I[1]] & x2) | (s219[A[1]] & ~x2),
        (s219[I[2]] & x2) | (s219[A[2]] & ~x2),
        (s219[I[3]] & x2) | (s219[A[3]] & ~x2),
        (s219[I[4]] & x2) | (s219[A[4]] & ~x2)
    };

    const std::array<d_type, len> s221 = {
        (s220[D_inv[0]] & x1) | (s220[I[0]] & ~x1),
        (s220[D_inv[1]] & x1) | (s220[I[1]] & ~x1),
        (s220[D_inv[2]] & x1) | (s220[I[2]] & ~x1),
        (s220[D_inv[3]] & x1) | (s220[I[3]] & ~x1),
        (s220[D_inv[4]] & x1) | (s220[I[4]] & ~x1)
    };

    const std::array<d_type, len> s222 = {
        (s221[I[0]] & x2) | (s221[A_inv[0]] & ~x2),
        (s221[I[1]] & x2) | (s221[A_inv[1]] & ~x2),
        (s221[I[2]] & x2) | (s221[A_inv[2]] & ~x2),
        (s221[I[3]] & x2) | (s221[A_inv[3]] & ~x2),
        (s221[I[4]] & x2) | (s221[A_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s223 = {
        s222[E_inv[0]],
        s222[E_inv[1]],
        s222[E_inv[2]],
        s222[E_inv[3]],
        s222[E_inv[4]]
    };

    const std::array<d_type, len> s224 = {
        (s223[I[0]] & x1) | (s223[C[0]] & ~x1),
        (s223[I[1]] & x1) | (s223[C[1]] & ~x1),
        (s223[I[2]] & x1) | (s223[C[2]] & ~x1),
        (s223[I[3]] & x1) | (s223[C[3]] & ~x1),
        (s223[I[4]] & x1) | (s223[C[4]] & ~x1)
    };

    const std::array<d_type, len> s225 = {
        (s224[D[0]] & x2) | (s224[I[0]] & ~x2),
        (s224[D[1]] & x2) | (s224[I[1]] & ~x2),
        (s224[D[2]] & x2) | (s224[I[2]] & ~x2),
        (s224[D[3]] & x2) | (s224[I[3]] & ~x2),
        (s224[D[4]] & x2) | (s224[I[4]] & ~x2)
    };

    const std::array<d_type, len> s226 = {
        (s225[I[0]] & x1) | (s225[C_inv[0]] & ~x1),
        (s225[I[1]] & x1) | (s225[C_inv[1]] & ~x1),
        (s225[I[2]] & x1) | (s225[C_inv[2]] & ~x1),
        (s225[I[3]] & x1) | (s225[C_inv[3]] & ~x1),
        (s225[I[4]] & x1) | (s225[C_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s227 = {
        (s226[D_inv[0]] & x2) | (s226[I[0]] & ~x2),
        (s226[D_inv[1]] & x2) | (s226[I[1]] & ~x2),
        (s226[D_inv[2]] & x2) | (s226[I[2]] & ~x2),
        (s226[D_inv[3]] & x2) | (s226[I[3]] & ~x2),
        (s226[D_inv[4]] & x2) | (s226[I[4]] & ~x2)
    };

    const std::array<d_type, len> s228 = {
        s227[B_inv[0]],
        s227[B_inv[1]],
        s227[B_inv[2]],
        s227[B_inv[3]],
        s227[B_inv[4]]
    };

    const std::array<d_type, len> s229 = {
        s228[D_inv[0]],
        s228[D_inv[1]],
        s228[D_inv[2]],
        s228[D_inv[3]],
        s228[D_inv[4]]
    };

    const std::array<d_type, len> s230 = {
        (s229[B[0]] & x3) | (s229[I[0]] & ~x3),
        (s229[B[1]] & x3) | (s229[I[1]] & ~x3),
        (s229[B[2]] & x3) | (s229[I[2]] & ~x3),
        (s229[B[3]] & x3) | (s229[I[3]] & ~x3),
        (s229[B[4]] & x3) | (s229[I[4]] & ~x3)
    };

    const std::array<d_type, len> s231 = {
        (s230[E[0]] & x4) | (s230[I[0]] & ~x4),
        (s230[E[1]] & x4) | (s230[I[1]] & ~x4),
        (s230[E[2]] & x4) | (s230[I[2]] & ~x4),
        (s230[E[3]] & x4) | (s230[I[3]] & ~x4),
        (s230[E[4]] & x4) | (s230[I[4]] & ~x4)
    };

    const std::array<d_type, len> s232 = {
        (s231[B_inv[0]] & x3) | (s231[I[0]] & ~x3),
        (s231[B_inv[1]] & x3) | (s231[I[1]] & ~x3),
        (s231[B_inv[2]] & x3) | (s231[I[2]] & ~x3),
        (s231[B_inv[3]] & x3) | (s231[I[3]] & ~x3),
        (s231[B_inv[4]] & x3) | (s231[I[4]] & ~x3)
    };

    const std::array<d_type, len> s233 = {
        (s232[E_inv[0]] & x4) | (s232[I[0]] & ~x4),
        (s232[E_inv[1]] & x4) | (s232[I[1]] & ~x4),
        (s232[E_inv[2]] & x4) | (s232[I[2]] & ~x4),
        (s232[E_inv[3]] & x4) | (s232[I[3]] & ~x4),
        (s232[E_inv[4]] & x4) | (s232[I[4]] & ~x4)
    };

    const std::array<d_type, len> s234 = {
        s233[D[0]],
        s233[D[1]],
        s233[D[2]],
        s233[D[3]],
        s233[D[4]]
    };

    const std::array<d_type, len> s235 = {
        (s234[I[0]] & x3) | (s234[B[0]] & ~x3),
        (s234[I[1]] & x3) | (s234[B[1]] & ~x3),
        (s234[I[2]] & x3) | (s234[B[2]] & ~x3),
        (s234[I[3]] & x3) | (s234[B[3]] & ~x3),
        (s234[I[4]] & x3) | (s234[B[4]] & ~x3)
    };

    const std::array<d_type, len> s236 = {
        (s235[I[0]] & x4) | (s235[C[0]] & ~x4),
        (s235[I[1]] & x4) | (s235[C[1]] & ~x4),
        (s235[I[2]] & x4) | (s235[C[2]] & ~x4),
        (s235[I[3]] & x4) | (s235[C[3]] & ~x4),
        (s235[I[4]] & x4) | (s235[C[4]] & ~x4)
    };

    const std::array<d_type, len> s237 = {
        (s236[I[0]] & x3) | (s236[B_inv[0]] & ~x3),
        (s236[I[1]] & x3) | (s236[B_inv[1]] & ~x3),
        (s236[I[2]] & x3) | (s236[B_inv[2]] & ~x3),
        (s236[I[3]] & x3) | (s236[B_inv[3]] & ~x3),
        (s236[I[4]] & x3) | (s236[B_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s238 = {
        (s237[I[0]] & x4) | (s237[C_inv[0]] & ~x4),
        (s237[I[1]] & x4) | (s237[C_inv[1]] & ~x4),
        (s237[I[2]] & x4) | (s237[C_inv[2]] & ~x4),
        (s237[I[3]] & x4) | (s237[C_inv[3]] & ~x4),
        (s237[I[4]] & x4) | (s237[C_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s239 = {
        s238[A[0]],
        s238[A[1]],
        s238[A[2]],
        s238[A[3]],
        s238[A[4]]
    };

    const std::array<d_type, len> s240 = {
        (s239[E[0]] & x3) | (s239[I[0]] & ~x3),
        (s239[E[1]] & x3) | (s239[I[1]] & ~x3),
        (s239[E[2]] & x3) | (s239[I[2]] & ~x3),
        (s239[E[3]] & x3) | (s239[I[3]] & ~x3),
        (s239[E[4]] & x3) | (s239[I[4]] & ~x3)
    };

    const std::array<d_type, len> s241 = {
        (s240[B[0]] & x4) | (s240[I[0]] & ~x4),
        (s240[B[1]] & x4) | (s240[I[1]] & ~x4),
        (s240[B[2]] & x4) | (s240[I[2]] & ~x4),
        (s240[B[3]] & x4) | (s240[I[3]] & ~x4),
        (s240[B[4]] & x4) | (s240[I[4]] & ~x4)
    };

    const std::array<d_type, len> s242 = {
        (s241[E_inv[0]] & x3) | (s241[I[0]] & ~x3),
        (s241[E_inv[1]] & x3) | (s241[I[1]] & ~x3),
        (s241[E_inv[2]] & x3) | (s241[I[2]] & ~x3),
        (s241[E_inv[3]] & x3) | (s241[I[3]] & ~x3),
        (s241[E_inv[4]] & x3) | (s241[I[4]] & ~x3)
    };

    const std::array<d_type, len> s243 = {
        (s242[B_inv[0]] & x4) | (s242[I[0]] & ~x4),
        (s242[B_inv[1]] & x4) | (s242[I[1]] & ~x4),
        (s242[B_inv[2]] & x4) | (s242[I[2]] & ~x4),
        (s242[B_inv[3]] & x4) | (s242[I[3]] & ~x4),
        (s242[B_inv[4]] & x4) | (s242[I[4]] & ~x4)
    };

    const std::array<d_type, len> s244 = {
        s243[D_inv[0]],
        s243[D_inv[1]],
        s243[D_inv[2]],
        s243[D_inv[3]],
        s243[D_inv[4]]
    };

    const std::array<d_type, len> s245 = {
        (s244[I[0]] & x3) | (s244[C[0]] & ~x3),
        (s244[I[1]] & x3) | (s244[C[1]] & ~x3),
        (s244[I[2]] & x3) | (s244[C[2]] & ~x3),
        (s244[I[3]] & x3) | (s244[C[3]] & ~x3),
        (s244[I[4]] & x3) | (s244[C[4]] & ~x3)
    };

    const std::array<d_type, len> s246 = {
        (s245[I[0]] & x4) | (s245[B[0]] & ~x4),
        (s245[I[1]] & x4) | (s245[B[1]] & ~x4),
        (s245[I[2]] & x4) | (s245[B[2]] & ~x4),
        (s245[I[3]] & x4) | (s245[B[3]] & ~x4),
        (s245[I[4]] & x4) | (s245[B[4]] & ~x4)
    };

    const std::array<d_type, len> s247 = {
        (s246[I[0]] & x3) | (s246[C_inv[0]] & ~x3),
        (s246[I[1]] & x3) | (s246[C_inv[1]] & ~x3),
        (s246[I[2]] & x3) | (s246[C_inv[2]] & ~x3),
        (s246[I[3]] & x3) | (s246[C_inv[3]] & ~x3),
        (s246[I[4]] & x3) | (s246[C_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s248 = {
        (s247[I[0]] & x4) | (s247[B_inv[0]] & ~x4),
        (s247[I[1]] & x4) | (s247[B_inv[1]] & ~x4),
        (s247[I[2]] & x4) | (s247[B_inv[2]] & ~x4),
        (s247[I[3]] & x4) | (s247[B_inv[3]] & ~x4),
        (s247[I[4]] & x4) | (s247[B_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s249 = {
        s248[A_inv[0]],
        s248[A_inv[1]],
        s248[A_inv[2]],
        s248[A_inv[3]],
        s248[A_inv[4]]
    };

    const std::array<d_type, len> s250 = {
        s249[E_inv[0]],
        s249[E_inv[1]],
        s249[E_inv[2]],
        s249[E_inv[3]],
        s249[E_inv[4]]
    };

    const std::array<d_type, len> s251 = {
        s250[C_inv[0]],
        s250[C_inv[1]],
        s250[C_inv[2]],
        s250[C_inv[3]],
        s250[C_inv[4]]
    };

    const std::array<d_type, len> s252 = {
        (s251[B[0]] & x1) | (s251[I[0]] & ~x1),
        (s251[B[1]] & x1) | (s251[I[1]] & ~x1),
        (s251[B[2]] & x1) | (s251[I[2]] & ~x1),
        (s251[B[3]] & x1) | (s251[I[3]] & ~x1),
        (s251[B[4]] & x1) | (s251[I[4]] & ~x1)
    };

    const std::array<d_type, len> s253 = {
        (s252[I[0]] & x2) | (s252[E[0]] & ~x2),
        (s252[I[1]] & x2) | (s252[E[1]] & ~x2),
        (s252[I[2]] & x2) | (s252[E[2]] & ~x2),
        (s252[I[3]] & x2) | (s252[E[3]] & ~x2),
        (s252[I[4]] & x2) | (s252[E[4]] & ~x2)
    };

    const std::array<d_type, len> s254 = {
        (s253[B_inv[0]] & x1) | (s253[I[0]] & ~x1),
        (s253[B_inv[1]] & x1) | (s253[I[1]] & ~x1),
        (s253[B_inv[2]] & x1) | (s253[I[2]] & ~x1),
        (s253[B_inv[3]] & x1) | (s253[I[3]] & ~x1),
        (s253[B_inv[4]] & x1) | (s253[I[4]] & ~x1)
    };

    const std::array<d_type, len> s255 = {
        (s254[I[0]] & x2) | (s254[E_inv[0]] & ~x2),
        (s254[I[1]] & x2) | (s254[E_inv[1]] & ~x2),
        (s254[I[2]] & x2) | (s254[E_inv[2]] & ~x2),
        (s254[I[3]] & x2) | (s254[E_inv[3]] & ~x2),
        (s254[I[4]] & x2) | (s254[E_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s256 = {
        s255[D[0]],
        s255[D[1]],
        s255[D[2]],
        s255[D[3]],
        s255[D[4]]
    };

    const std::array<d_type, len> s257 = {
        (s256[I[0]] & x1) | (s256[A[0]] & ~x1),
        (s256[I[1]] & x1) | (s256[A[1]] & ~x1),
        (s256[I[2]] & x1) | (s256[A[2]] & ~x1),
        (s256[I[3]] & x1) | (s256[A[3]] & ~x1),
        (s256[I[4]] & x1) | (s256[A[4]] & ~x1)
    };

    const std::array<d_type, len> s258 = {
        (s257[D[0]] & x2) | (s257[I[0]] & ~x2),
        (s257[D[1]] & x2) | (s257[I[1]] & ~x2),
        (s257[D[2]] & x2) | (s257[I[2]] & ~x2),
        (s257[D[3]] & x2) | (s257[I[3]] & ~x2),
        (s257[D[4]] & x2) | (s257[I[4]] & ~x2)
    };

    const std::array<d_type, len> s259 = {
        (s258[I[0]] & x1) | (s258[A_inv[0]] & ~x1),
        (s258[I[1]] & x1) | (s258[A_inv[1]] & ~x1),
        (s258[I[2]] & x1) | (s258[A_inv[2]] & ~x1),
        (s258[I[3]] & x1) | (s258[A_inv[3]] & ~x1),
        (s258[I[4]] & x1) | (s258[A_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s260 = {
        (s259[D_inv[0]] & x2) | (s259[I[0]] & ~x2),
        (s259[D_inv[1]] & x2) | (s259[I[1]] & ~x2),
        (s259[D_inv[2]] & x2) | (s259[I[2]] & ~x2),
        (s259[D_inv[3]] & x2) | (s259[I[3]] & ~x2),
        (s259[D_inv[4]] & x2) | (s259[I[4]] & ~x2)
    };

    const std::array<d_type, len> s261 = {
        s260[E[0]],
        s260[E[1]],
        s260[E[2]],
        s260[E[3]],
        s260[E[4]]
    };

    const std::array<d_type, len> s262 = {
        (s261[E[0]] & x1) | (s261[I[0]] & ~x1),
        (s261[E[1]] & x1) | (s261[I[1]] & ~x1),
        (s261[E[2]] & x1) | (s261[I[2]] & ~x1),
        (s261[E[3]] & x1) | (s261[I[3]] & ~x1),
        (s261[E[4]] & x1) | (s261[I[4]] & ~x1)
    };

    const std::array<d_type, len> s263 = {
        (s262[I[0]] & x2) | (s262[B[0]] & ~x2),
        (s262[I[1]] & x2) | (s262[B[1]] & ~x2),
        (s262[I[2]] & x2) | (s262[B[2]] & ~x2),
        (s262[I[3]] & x2) | (s262[B[3]] & ~x2),
        (s262[I[4]] & x2) | (s262[B[4]] & ~x2)
    };

    const std::array<d_type, len> s264 = {
        (s263[E_inv[0]] & x1) | (s263[I[0]] & ~x1),
        (s263[E_inv[1]] & x1) | (s263[I[1]] & ~x1),
        (s263[E_inv[2]] & x1) | (s263[I[2]] & ~x1),
        (s263[E_inv[3]] & x1) | (s263[I[3]] & ~x1),
        (s263[E_inv[4]] & x1) | (s263[I[4]] & ~x1)
    };

    const std::array<d_type, len> s265 = {
        (s264[I[0]] & x2) | (s264[B_inv[0]] & ~x2),
        (s264[I[1]] & x2) | (s264[B_inv[1]] & ~x2),
        (s264[I[2]] & x2) | (s264[B_inv[2]] & ~x2),
        (s264[I[3]] & x2) | (s264[B_inv[3]] & ~x2),
        (s264[I[4]] & x2) | (s264[B_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s266 = {
        s265[D_inv[0]],
        s265[D_inv[1]],
        s265[D_inv[2]],
        s265[D_inv[3]],
        s265[D_inv[4]]
    };

    const std::array<d_type, len> s267 = {
        (s266[I[0]] & x1) | (s266[D[0]] & ~x1),
        (s266[I[1]] & x1) | (s266[D[1]] & ~x1),
        (s266[I[2]] & x1) | (s266[D[2]] & ~x1),
        (s266[I[3]] & x1) | (s266[D[3]] & ~x1),
        (s266[I[4]] & x1) | (s266[D[4]] & ~x1)
    };

    const std::array<d_type, len> s268 = {
        (s267[A[0]] & x2) | (s267[I[0]] & ~x2),
        (s267[A[1]] & x2) | (s267[I[1]] & ~x2),
        (s267[A[2]] & x2) | (s267[I[2]] & ~x2),
        (s267[A[3]] & x2) | (s267[I[3]] & ~x2),
        (s267[A[4]] & x2) | (s267[I[4]] & ~x2)
    };

    const std::array<d_type, len> s269 = {
        (s268[I[0]] & x1) | (s268[D_inv[0]] & ~x1),
        (s268[I[1]] & x1) | (s268[D_inv[1]] & ~x1),
        (s268[I[2]] & x1) | (s268[D_inv[2]] & ~x1),
        (s268[I[3]] & x1) | (s268[D_inv[3]] & ~x1),
        (s268[I[4]] & x1) | (s268[D_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s270 = {
        (s269[A_inv[0]] & x2) | (s269[I[0]] & ~x2),
        (s269[A_inv[1]] & x2) | (s269[I[1]] & ~x2),
        (s269[A_inv[2]] & x2) | (s269[I[2]] & ~x2),
        (s269[A_inv[3]] & x2) | (s269[I[3]] & ~x2),
        (s269[A_inv[4]] & x2) | (s269[I[4]] & ~x2)
    };

    const std::array<d_type, len> s271 = {
        s270[E_inv[0]],
        s270[E_inv[1]],
        s270[E_inv[2]],
        s270[E_inv[3]],
        s270[E_inv[4]]
    };

    const std::array<d_type, len> s272 = {
        (s271[A[0]] & x3) | (s271[I[0]] & ~x3),
        (s271[A[1]] & x3) | (s271[I[1]] & ~x3),
        (s271[A[2]] & x3) | (s271[I[2]] & ~x3),
        (s271[A[3]] & x3) | (s271[I[3]] & ~x3),
        (s271[A[4]] & x3) | (s271[I[4]] & ~x3)
    };

    const std::array<d_type, len> s273 = {
        (s272[D[0]] & x4) | (s272[I[0]] & ~x4),
        (s272[D[1]] & x4) | (s272[I[1]] & ~x4),
        (s272[D[2]] & x4) | (s272[I[2]] & ~x4),
        (s272[D[3]] & x4) | (s272[I[3]] & ~x4),
        (s272[D[4]] & x4) | (s272[I[4]] & ~x4)
    };

    const std::array<d_type, len> s274 = {
        (s273[A_inv[0]] & x3) | (s273[I[0]] & ~x3),
        (s273[A_inv[1]] & x3) | (s273[I[1]] & ~x3),
        (s273[A_inv[2]] & x3) | (s273[I[2]] & ~x3),
        (s273[A_inv[3]] & x3) | (s273[I[3]] & ~x3),
        (s273[A_inv[4]] & x3) | (s273[I[4]] & ~x3)
    };

    const std::array<d_type, len> s275 = {
        (s274[D_inv[0]] & x4) | (s274[I[0]] & ~x4),
        (s274[D_inv[1]] & x4) | (s274[I[1]] & ~x4),
        (s274[D_inv[2]] & x4) | (s274[I[2]] & ~x4),
        (s274[D_inv[3]] & x4) | (s274[I[3]] & ~x4),
        (s274[D_inv[4]] & x4) | (s274[I[4]] & ~x4)
    };

    const std::array<d_type, len> s276 = {
        s275[E[0]],
        s275[E[1]],
        s275[E[2]],
        s275[E[3]],
        s275[E[4]]
    };

    const std::array<d_type, len> s277 = {
        (s276[I[0]] & x3) | (s276[D[0]] & ~x3),
        (s276[I[1]] & x3) | (s276[D[1]] & ~x3),
        (s276[I[2]] & x3) | (s276[D[2]] & ~x3),
        (s276[I[3]] & x3) | (s276[D[3]] & ~x3),
        (s276[I[4]] & x3) | (s276[D[4]] & ~x3)
    };

    const std::array<d_type, len> s278 = {
        (s277[I[0]] & x4) | (s277[C[0]] & ~x4),
        (s277[I[1]] & x4) | (s277[C[1]] & ~x4),
        (s277[I[2]] & x4) | (s277[C[2]] & ~x4),
        (s277[I[3]] & x4) | (s277[C[3]] & ~x4),
        (s277[I[4]] & x4) | (s277[C[4]] & ~x4)
    };

    const std::array<d_type, len> s279 = {
        (s278[I[0]] & x3) | (s278[D_inv[0]] & ~x3),
        (s278[I[1]] & x3) | (s278[D_inv[1]] & ~x3),
        (s278[I[2]] & x3) | (s278[D_inv[2]] & ~x3),
        (s278[I[3]] & x3) | (s278[D_inv[3]] & ~x3),
        (s278[I[4]] & x3) | (s278[D_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s280 = {
        (s279[I[0]] & x4) | (s279[C_inv[0]] & ~x4),
        (s279[I[1]] & x4) | (s279[C_inv[1]] & ~x4),
        (s279[I[2]] & x4) | (s279[C_inv[2]] & ~x4),
        (s279[I[3]] & x4) | (s279[C_inv[3]] & ~x4),
        (s279[I[4]] & x4) | (s279[C_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s281 = {
        s280[B[0]],
        s280[B[1]],
        s280[B[2]],
        s280[B[3]],
        s280[B[4]]
    };

    const std::array<d_type, len> s282 = {
        (s281[D[0]] & x3) | (s281[I[0]] & ~x3),
        (s281[D[1]] & x3) | (s281[I[1]] & ~x3),
        (s281[D[2]] & x3) | (s281[I[2]] & ~x3),
        (s281[D[3]] & x3) | (s281[I[3]] & ~x3),
        (s281[D[4]] & x3) | (s281[I[4]] & ~x3)
    };

    const std::array<d_type, len> s283 = {
        (s282[A[0]] & x4) | (s282[I[0]] & ~x4),
        (s282[A[1]] & x4) | (s282[I[1]] & ~x4),
        (s282[A[2]] & x4) | (s282[I[2]] & ~x4),
        (s282[A[3]] & x4) | (s282[I[3]] & ~x4),
        (s282[A[4]] & x4) | (s282[I[4]] & ~x4)
    };

    const std::array<d_type, len> s284 = {
        (s283[D_inv[0]] & x3) | (s283[I[0]] & ~x3),
        (s283[D_inv[1]] & x3) | (s283[I[1]] & ~x3),
        (s283[D_inv[2]] & x3) | (s283[I[2]] & ~x3),
        (s283[D_inv[3]] & x3) | (s283[I[3]] & ~x3),
        (s283[D_inv[4]] & x3) | (s283[I[4]] & ~x3)
    };

    const std::array<d_type, len> s285 = {
        (s284[A_inv[0]] & x4) | (s284[I[0]] & ~x4),
        (s284[A_inv[1]] & x4) | (s284[I[1]] & ~x4),
        (s284[A_inv[2]] & x4) | (s284[I[2]] & ~x4),
        (s284[A_inv[3]] & x4) | (s284[I[3]] & ~x4),
        (s284[A_inv[4]] & x4) | (s284[I[4]] & ~x4)
    };

    const std::array<d_type, len> s286 = {
        s285[E_inv[0]],
        s285[E_inv[1]],
        s285[E_inv[2]],
        s285[E_inv[3]],
        s285[E_inv[4]]
    };

    const std::array<d_type, len> s287 = {
        (s286[I[0]] & x3) | (s286[C[0]] & ~x3),
        (s286[I[1]] & x3) | (s286[C[1]] & ~x3),
        (s286[I[2]] & x3) | (s286[C[2]] & ~x3),
        (s286[I[3]] & x3) | (s286[C[3]] & ~x3),
        (s286[I[4]] & x3) | (s286[C[4]] & ~x3)
    };

    const std::array<d_type, len> s288 = {
        (s287[I[0]] & x4) | (s287[D[0]] & ~x4),
        (s287[I[1]] & x4) | (s287[D[1]] & ~x4),
        (s287[I[2]] & x4) | (s287[D[2]] & ~x4),
        (s287[I[3]] & x4) | (s287[D[3]] & ~x4),
        (s287[I[4]] & x4) | (s287[D[4]] & ~x4)
    };

    const std::array<d_type, len> s289 = {
        (s288[I[0]] & x3) | (s288[C_inv[0]] & ~x3),
        (s288[I[1]] & x3) | (s288[C_inv[1]] & ~x3),
        (s288[I[2]] & x3) | (s288[C_inv[2]] & ~x3),
        (s288[I[3]] & x3) | (s288[C_inv[3]] & ~x3),
        (s288[I[4]] & x3) | (s288[C_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s290 = {
        (s289[I[0]] & x4) | (s289[D_inv[0]] & ~x4),
        (s289[I[1]] & x4) | (s289[D_inv[1]] & ~x4),
        (s289[I[2]] & x4) | (s289[D_inv[2]] & ~x4),
        (s289[I[3]] & x4) | (s289[D_inv[3]] & ~x4),
        (s289[I[4]] & x4) | (s289[D_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s291 = {
        s290[B_inv[0]],
        s290[B_inv[1]],
        s290[B_inv[2]],
        s290[B_inv[3]],
        s290[B_inv[4]]
    };

    const std::array<d_type, len> s292 = {
        (s291[A[0]] & x1) | (s291[I[0]] & ~x1),
        (s291[A[1]] & x1) | (s291[I[1]] & ~x1),
        (s291[A[2]] & x1) | (s291[I[2]] & ~x1),
        (s291[A[3]] & x1) | (s291[I[3]] & ~x1),
        (s291[A[4]] & x1) | (s291[I[4]] & ~x1)
    };

    const std::array<d_type, len> s293 = {
        (s292[I[0]] & x2) | (s292[D[0]] & ~x2),
        (s292[I[1]] & x2) | (s292[D[1]] & ~x2),
        (s292[I[2]] & x2) | (s292[D[2]] & ~x2),
        (s292[I[3]] & x2) | (s292[D[3]] & ~x2),
        (s292[I[4]] & x2) | (s292[D[4]] & ~x2)
    };

    const std::array<d_type, len> s294 = {
        (s293[A_inv[0]] & x1) | (s293[I[0]] & ~x1),
        (s293[A_inv[1]] & x1) | (s293[I[1]] & ~x1),
        (s293[A_inv[2]] & x1) | (s293[I[2]] & ~x1),
        (s293[A_inv[3]] & x1) | (s293[I[3]] & ~x1),
        (s293[A_inv[4]] & x1) | (s293[I[4]] & ~x1)
    };

    const std::array<d_type, len> s295 = {
        (s294[I[0]] & x2) | (s294[D_inv[0]] & ~x2),
        (s294[I[1]] & x2) | (s294[D_inv[1]] & ~x2),
        (s294[I[2]] & x2) | (s294[D_inv[2]] & ~x2),
        (s294[I[3]] & x2) | (s294[D_inv[3]] & ~x2),
        (s294[I[4]] & x2) | (s294[D_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s296 = {
        s295[E[0]],
        s295[E[1]],
        s295[E[2]],
        s295[E[3]],
        s295[E[4]]
    };

    const std::array<d_type, len> s297 = {
        (s296[I[0]] & x1) | (s296[B[0]] & ~x1),
        (s296[I[1]] & x1) | (s296[B[1]] & ~x1),
        (s296[I[2]] & x1) | (s296[B[2]] & ~x1),
        (s296[I[3]] & x1) | (s296[B[3]] & ~x1),
        (s296[I[4]] & x1) | (s296[B[4]] & ~x1)
    };

    const std::array<d_type, len> s298 = {
        (s297[E[0]] & x2) | (s297[I[0]] & ~x2),
        (s297[E[1]] & x2) | (s297[I[1]] & ~x2),
        (s297[E[2]] & x2) | (s297[I[2]] & ~x2),
        (s297[E[3]] & x2) | (s297[I[3]] & ~x2),
        (s297[E[4]] & x2) | (s297[I[4]] & ~x2)
    };

    const std::array<d_type, len> s299 = {
        (s298[I[0]] & x1) | (s298[B_inv[0]] & ~x1),
        (s298[I[1]] & x1) | (s298[B_inv[1]] & ~x1),
        (s298[I[2]] & x1) | (s298[B_inv[2]] & ~x1),
        (s298[I[3]] & x1) | (s298[B_inv[3]] & ~x1),
        (s298[I[4]] & x1) | (s298[B_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s300 = {
        (s299[E_inv[0]] & x2) | (s299[I[0]] & ~x2),
        (s299[E_inv[1]] & x2) | (s299[I[1]] & ~x2),
        (s299[E_inv[2]] & x2) | (s299[I[2]] & ~x2),
        (s299[E_inv[3]] & x2) | (s299[I[3]] & ~x2),
        (s299[E_inv[4]] & x2) | (s299[I[4]] & ~x2)
    };

    const std::array<d_type, len> s301 = {
        s300[D[0]],
        s300[D[1]],
        s300[D[2]],
        s300[D[3]],
        s300[D[4]]
    };

    const std::array<d_type, len> s302 = {
        (s301[D[0]] & x1) | (s301[I[0]] & ~x1),
        (s301[D[1]] & x1) | (s301[I[1]] & ~x1),
        (s301[D[2]] & x1) | (s301[I[2]] & ~x1),
        (s301[D[3]] & x1) | (s301[I[3]] & ~x1),
        (s301[D[4]] & x1) | (s301[I[4]] & ~x1)
    };

    const std::array<d_type, len> s303 = {
        (s302[I[0]] & x2) | (s302[A[0]] & ~x2),
        (s302[I[1]] & x2) | (s302[A[1]] & ~x2),
        (s302[I[2]] & x2) | (s302[A[2]] & ~x2),
        (s302[I[3]] & x2) | (s302[A[3]] & ~x2),
        (s302[I[4]] & x2) | (s302[A[4]] & ~x2)
    };

    const std::array<d_type, len> s304 = {
        (s303[D_inv[0]] & x1) | (s303[I[0]] & ~x1),
        (s303[D_inv[1]] & x1) | (s303[I[1]] & ~x1),
        (s303[D_inv[2]] & x1) | (s303[I[2]] & ~x1),
        (s303[D_inv[3]] & x1) | (s303[I[3]] & ~x1),
        (s303[D_inv[4]] & x1) | (s303[I[4]] & ~x1)
    };

    const std::array<d_type, len> s305 = {
        (s304[I[0]] & x2) | (s304[A_inv[0]] & ~x2),
        (s304[I[1]] & x2) | (s304[A_inv[1]] & ~x2),
        (s304[I[2]] & x2) | (s304[A_inv[2]] & ~x2),
        (s304[I[3]] & x2) | (s304[A_inv[3]] & ~x2),
        (s304[I[4]] & x2) | (s304[A_inv[4]] & ~x2)
    };

    const std::array<d_type, len> s306 = {
        s305[E_inv[0]],
        s305[E_inv[1]],
        s305[E_inv[2]],
        s305[E_inv[3]],
        s305[E_inv[4]]
    };

    const std::array<d_type, len> s307 = {
        (s306[I[0]] & x1) | (s306[E[0]] & ~x1),
        (s306[I[1]] & x1) | (s306[E[1]] & ~x1),
        (s306[I[2]] & x1) | (s306[E[2]] & ~x1),
        (s306[I[3]] & x1) | (s306[E[3]] & ~x1),
        (s306[I[4]] & x1) | (s306[E[4]] & ~x1)
    };

    const std::array<d_type, len> s308 = {
        (s307[B[0]] & x2) | (s307[I[0]] & ~x2),
        (s307[B[1]] & x2) | (s307[I[1]] & ~x2),
        (s307[B[2]] & x2) | (s307[I[2]] & ~x2),
        (s307[B[3]] & x2) | (s307[I[3]] & ~x2),
        (s307[B[4]] & x2) | (s307[I[4]] & ~x2)
    };

    const std::array<d_type, len> s309 = {
        (s308[I[0]] & x1) | (s308[E_inv[0]] & ~x1),
        (s308[I[1]] & x1) | (s308[E_inv[1]] & ~x1),
        (s308[I[2]] & x1) | (s308[E_inv[2]] & ~x1),
        (s308[I[3]] & x1) | (s308[E_inv[3]] & ~x1),
        (s308[I[4]] & x1) | (s308[E_inv[4]] & ~x1)
    };

    const std::array<d_type, len> s310 = {
        (s309[B_inv[0]] & x2) | (s309[I[0]] & ~x2),
        (s309[B_inv[1]] & x2) | (s309[I[1]] & ~x2),
        (s309[B_inv[2]] & x2) | (s309[I[2]] & ~x2),
        (s309[B_inv[3]] & x2) | (s309[I[3]] & ~x2),
        (s309[B_inv[4]] & x2) | (s309[I[4]] & ~x2)
    };

    const std::array<d_type, len> s311 = {
        s310[D_inv[0]],
        s310[D_inv[1]],
        s310[D_inv[2]],
        s310[D_inv[3]],
        s310[D_inv[4]]
    };

    const std::array<d_type, len> s312 = {
        (s311[D[0]] & x3) | (s311[I[0]] & ~x3),
        (s311[D[1]] & x3) | (s311[I[1]] & ~x3),
        (s311[D[2]] & x3) | (s311[I[2]] & ~x3),
        (s311[D[3]] & x3) | (s311[I[3]] & ~x3),
        (s311[D[4]] & x3) | (s311[I[4]] & ~x3)
    };

    const std::array<d_type, len> s313 = {
        (s312[C[0]] & x4) | (s312[I[0]] & ~x4),
        (s312[C[1]] & x4) | (s312[I[1]] & ~x4),
        (s312[C[2]] & x4) | (s312[I[2]] & ~x4),
        (s312[C[3]] & x4) | (s312[I[3]] & ~x4),
        (s312[C[4]] & x4) | (s312[I[4]] & ~x4)
    };

    const std::array<d_type, len> s314 = {
        (s313[D_inv[0]] & x3) | (s313[I[0]] & ~x3),
        (s313[D_inv[1]] & x3) | (s313[I[1]] & ~x3),
        (s313[D_inv[2]] & x3) | (s313[I[2]] & ~x3),
        (s313[D_inv[3]] & x3) | (s313[I[3]] & ~x3),
        (s313[D_inv[4]] & x3) | (s313[I[4]] & ~x3)
    };

    const std::array<d_type, len> s315 = {
        (s314[C_inv[0]] & x4) | (s314[I[0]] & ~x4),
        (s314[C_inv[1]] & x4) | (s314[I[1]] & ~x4),
        (s314[C_inv[2]] & x4) | (s314[I[2]] & ~x4),
        (s314[C_inv[3]] & x4) | (s314[I[3]] & ~x4),
        (s314[C_inv[4]] & x4) | (s314[I[4]] & ~x4)
    };

    const std::array<d_type, len> s316 = {
        s315[B[0]],
        s315[B[1]],
        s315[B[2]],
        s315[B[3]],
        s315[B[4]]
    };

    const std::array<d_type, len> s317 = {
        (s316[I[0]] & x3) | (s316[A[0]] & ~x3),
        (s316[I[1]] & x3) | (s316[A[1]] & ~x3),
        (s316[I[2]] & x3) | (s316[A[2]] & ~x3),
        (s316[I[3]] & x3) | (s316[A[3]] & ~x3),
        (s316[I[4]] & x3) | (s316[A[4]] & ~x3)
    };

    const std::array<d_type, len> s318 = {
        (s317[I[0]] & x4) | (s317[D[0]] & ~x4),
        (s317[I[1]] & x4) | (s317[D[1]] & ~x4),
        (s317[I[2]] & x4) | (s317[D[2]] & ~x4),
        (s317[I[3]] & x4) | (s317[D[3]] & ~x4),
        (s317[I[4]] & x4) | (s317[D[4]] & ~x4)
    };

    const std::array<d_type, len> s319 = {
        (s318[I[0]] & x3) | (s318[A_inv[0]] & ~x3),
        (s318[I[1]] & x3) | (s318[A_inv[1]] & ~x3),
        (s318[I[2]] & x3) | (s318[A_inv[2]] & ~x3),
        (s318[I[3]] & x3) | (s318[A_inv[3]] & ~x3),
        (s318[I[4]] & x3) | (s318[A_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s320 = {
        (s319[I[0]] & x4) | (s319[D_inv[0]] & ~x4),
        (s319[I[1]] & x4) | (s319[D_inv[1]] & ~x4),
        (s319[I[2]] & x4) | (s319[D_inv[2]] & ~x4),
        (s319[I[3]] & x4) | (s319[D_inv[3]] & ~x4),
        (s319[I[4]] & x4) | (s319[D_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s321 = {
        s320[E[0]],
        s320[E[1]],
        s320[E[2]],
        s320[E[3]],
        s320[E[4]]
    };

    const std::array<d_type, len> s322 = {
        (s321[C[0]] & x3) | (s321[I[0]] & ~x3),
        (s321[C[1]] & x3) | (s321[I[1]] & ~x3),
        (s321[C[2]] & x3) | (s321[I[2]] & ~x3),
        (s321[C[3]] & x3) | (s321[I[3]] & ~x3),
        (s321[C[4]] & x3) | (s321[I[4]] & ~x3)
    };

    const std::array<d_type, len> s323 = {
        (s322[D[0]] & x4) | (s322[I[0]] & ~x4),
        (s322[D[1]] & x4) | (s322[I[1]] & ~x4),
        (s322[D[2]] & x4) | (s322[I[2]] & ~x4),
        (s322[D[3]] & x4) | (s322[I[3]] & ~x4),
        (s322[D[4]] & x4) | (s322[I[4]] & ~x4)
    };

    const std::array<d_type, len> s324 = {
        (s323[C_inv[0]] & x3) | (s323[I[0]] & ~x3),
        (s323[C_inv[1]] & x3) | (s323[I[1]] & ~x3),
        (s323[C_inv[2]] & x3) | (s323[I[2]] & ~x3),
        (s323[C_inv[3]] & x3) | (s323[I[3]] & ~x3),
        (s323[C_inv[4]] & x3) | (s323[I[4]] & ~x3)
    };

    const std::array<d_type, len> s325 = {
        (s324[D_inv[0]] & x4) | (s324[I[0]] & ~x4),
        (s324[D_inv[1]] & x4) | (s324[I[1]] & ~x4),
        (s324[D_inv[2]] & x4) | (s324[I[2]] & ~x4),
        (s324[D_inv[3]] & x4) | (s324[I[3]] & ~x4),
        (s324[D_inv[4]] & x4) | (s324[I[4]] & ~x4)
    };

    const std::array<d_type, len> s326 = {
        s325[B_inv[0]],
        s325[B_inv[1]],
        s325[B_inv[2]],
        s325[B_inv[3]],
        s325[B_inv[4]]
    };

    const std::array<d_type, len> s327 = {
        (s326[I[0]] & x3) | (s326[D[0]] & ~x3),
        (s326[I[1]] & x3) | (s326[D[1]] & ~x3),
        (s326[I[2]] & x3) | (s326[D[2]] & ~x3),
        (s326[I[3]] & x3) | (s326[D[3]] & ~x3),
        (s326[I[4]] & x3) | (s326[D[4]] & ~x3)
    };

    const std::array<d_type, len> s328 = {
        (s327[I[0]] & x4) | (s327[A[0]] & ~x4),
        (s327[I[1]] & x4) | (s327[A[1]] & ~x4),
        (s327[I[2]] & x4) | (s327[A[2]] & ~x4),
        (s327[I[3]] & x4) | (s327[A[3]] & ~x4),
        (s327[I[4]] & x4) | (s327[A[4]] & ~x4)
    };

    const std::array<d_type, len> s329 = {
        (s328[I[0]] & x3) | (s328[D_inv[0]] & ~x3),
        (s328[I[1]] & x3) | (s328[D_inv[1]] & ~x3),
        (s328[I[2]] & x3) | (s328[D_inv[2]] & ~x3),
        (s328[I[3]] & x3) | (s328[D_inv[3]] & ~x3),
        (s328[I[4]] & x3) | (s328[D_inv[4]] & ~x3)
    };

    const std::array<d_type, len> s330 = {
        (s329[I[0]] & x4) | (s329[A_inv[0]] & ~x4),
        (s329[I[1]] & x4) | (s329[A_inv[1]] & ~x4),
        (s329[I[2]] & x4) | (s329[A_inv[2]] & ~x4),
        (s329[I[3]] & x4) | (s329[A_inv[3]] & ~x4),
        (s329[I[4]] & x4) | (s329[A_inv[4]] & ~x4)
    };

    const std::array<d_type, len> s331 = {
        s330[E_inv[0]],
        s330[E_inv[1]],
        s330[E_inv[2]],
        s330[E_inv[3]],
        s330[E_inv[4]]
    };

    const std::array<d_type, len> s332 = {
        s331[B_inv[0]],
        s331[B_inv[1]],
        s331[B_inv[2]],
        s331[B_inv[3]],
        s331[B_inv[4]]
    };


    // return the last state we calculated
    return s332;
}

int main() {
    std::array<d_type, len> state = {1, 2, 3, 4, 5}; // starting state
    for (int i = 0; i < 16; i++) {
        std::array<d_type, len> result = func(state, i&8, i&4, i&2, i&1);
        printf("%d %d %d %d %d\n", result[0], result[1], result[2], result[3], result[4]);
    }
}
