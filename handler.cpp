#include "header.h"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")
#define IO_SZ (180 << 20)
char IO[IO_SZ];
int inIdx;
void scanint(int &x) { for (x=IO[inIdx++]-'0'; IO[inIdx++]>='0'; x=x*10+IO[inIdx-1]-'0'); }
void scanshort(short &x) { for (x=IO[inIdx++]-'0'; IO[inIdx++]>='0'; x=x*10+IO[inIdx-1]-'0'); }

int T;
short N, K, D;
std::vector<edge> E;
std::vector<std::pair<short, short>> P;
int main() {
    // generator data already in stdin, no need to freopen
    fread(IO, 1, IO_SZ, stdin);
    scanshort(N); scanint(T);
    for (int i=0; i<T; i++) {
        edge e;
        scanshort(e.x); scanshort(e.y); scanshort(e.Cxy);
        E.push_back(e);
    }
    scanshort(K);
    for (int i=0; i<K; i++) {
        short z, Pz;
        scanshort(z); scanshort(Pz);
        P.emplace_back(z, Pz);
    }
    scanshort(D);
    fclose(stdin);

    printf("%d\n", cheapest_route(N, T, move(E), K, move(P), D));
    return 0;
}
