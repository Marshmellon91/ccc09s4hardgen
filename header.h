#ifndef _GRADER_HEADER_INCLUDED
#define _GRADER_HEADER_INCLUDED
#include <bits/stdc++.h>
struct edge {
    short x, y, Cxy;
};

int cheapest_route(short, int, std::vector<edge>, short, std::vector<std::pair<short, short>>, short);
#endif

