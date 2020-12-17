#pragma once
#include <vector>
#include <algorithm>

template<int N> struct Point : std::vector<__int64> {
    Point(std::initializer_list<__int64> il) : std::vector<__int64>(il) { resize(N); }
    Point() { resize(N); }

    bool operator==(const Point& other) const { return (*this == other); }
    void operator+=(const Point& other) { for (int c = 0; c < N; ++c) { at(c) += other.at(c); } }
    void operator-=(const Point& other) { for (int c = 0; c < N; ++c) { at(c) -= other.at(c); } }

    template<class _F>
    void DoNeighbours(_F fn) const {
        Point d;
        for (auto& x : d) x = -1;

        while (true) {
            if (!std::all_of(d.begin(), d.end(), [](__int64 a) {return a == 0; })) {
                fn((*this) + d);
            }
            
            int c = 0;
            while (c < N) {
                ++d[c];
                if (d[c] != 2) break;
                d[c] = -1;
                ++c;
            }
            if (c == N) break;
        }
    }
};

template<int N> Point<N> operator+ (const Point<N>& a, const Point<N>& b) { Point<N> p(a); p += b; return p; }
template<int N> Point<N> operator- (const Point<N>& a, const Point<N>& b) { Point<N> p(a); p -= b; return p; }

typedef Point<2> Point2;
typedef Point<3> Point3;
typedef Point<4> Point4;