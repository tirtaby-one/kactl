/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  array<int, 3> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N>
using Mat = array<array<T, N>, N>;

template<class T, int N> // V * V
Mat<T, N> mul(Mat<T, N> a, Mat<T, N> b) {
    Mat<T, N> c{};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                c[i][k] += a[i][j] * b[j][k];
    return c;
}

template<class T, int N> // V * ar
array<T, N> mul(Mat<T, N> a, array<T, N> v) {
    array<T, N> res{};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            res[i] += a[i][j] * v[j];
    return res;
}

template<class T, int N> // matrix pow
Mat<T, N> mpow(Mat<T, N> a, ll p) {
    assert(p >= 0);
    Mat<T, N> res{};
    for (int i = 0; i < N; i++)
        res[i][i] = 1;
    while (p) {
        if (p & 1) res = mul<T, N>(res, a);
        a = mul<T, N>(a, a);
        p >>= 1;
    }
    return res;
}