#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")
#define IO_SZ (180 << 20)
char IO[IO_SZ], streamWriter[12];
int outIdx, idx;
void putChar(char x) {IO[outIdx++] = x;}
void print(int x) {
    do streamWriter[idx++] = x % 10; while (x /= 10);
    do IO[outIdx++] = streamWriter[--idx]+'0'; while (idx);
}

const int max_weight = 10000;
const int max_initial = 10000;

std::mt19937 gen(998244353);
template<class T>
T randint(T L, T R) {
    return L+(unsigned long long)(R-L+1)*gen()/(std::numeric_limits<unsigned int>::max()+1ULL);
}

std::pair<int, int> randpair(int l, int r) {
    int a = randint(l, r-1);
    int b = randint(l, r-1);
    if (b < a) std::swap(a, b);
    return {a, b+1};
}

// argv
// 1 -> N (cities)
// 2 -> T (trade routes)
// 3 -> K (pencil cities)
// 4 -> D (starting city)
// 5 -> killSPFA (bool determining if that case should kill SPFA)
// 6 -> killBF (bool determining if the case should kill BF with less iterations)
// 7 -> slowDijkstra (case that gets dijkstra's close to worst case)
// 8 -> complete (Case that generates a complete graph)
// 9 -> maxCase (Case that maximizes the shortest path)

std::vector<std::pair<short, short>> adj[5001], P;
int dist[5001];
bool u[5001];

int main(int argc, const char **argv) {
    short N = atoi(argv[1]);
    int T = atoi(argv[2]);
    short K = atoi(argv[3]);
    short D = atoi(argv[4]);
    bool killSPFA = (argv[5][0] == '1');
    bool killBF = (argv[6][0] == '1');
    bool slowDijkstra = (argv[7][0] == '1');
    bool complete = (argv[8][0] == '1');
    bool maxCase = (argv[9][0] == '1');
    gen.seed(998244353 ^ N ^ T ^ K ^ D ^ (int) killSPFA ^ (int) killBF ^ (int) slowDijkstra ^ (int) complete ^ (int) maxCase);

    print(N); putChar('\n');
    print(T); putChar('\n');

    if (killSPFA) { // SPFA kill attempt
        // only for batch 2
        for (int i=1; i<=N; i++) {
            for (int j=i+2; j<=N; j++) {
                print(i); putChar(' '); print(j); putChar(' '); print(2*(N-i)); putChar('\n');
                adj[i].emplace_back(2*(N-i), j);
                adj[j].emplace_back(2*(N-i), i);
            }
        }
        for (int i=1; i<N; i++) {
            print(i); putChar(' '); print(i+1); putChar(' '); print(1); putChar('\n');
            adj[i].emplace_back(1, i+1);
            adj[i+1].emplace_back(1, i);
        }
    }
    else if (killBF) { // kills Bellman Ford with less iterations
        // boolean array to make sure no duplicate edges
        bool used[N+1][N+1];
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) used[i][j] = false;
        }

        std::vector<std::pair<int, int>> path;
        for (int i=1; i<N; i++) path.emplace_back(i, i+1);
        shuffle(path.begin(), path.end(), gen);
        for (auto [i, j]: path) {
            print(i); putChar(' '); print(j); putChar(' '); print(0); putChar('\n');
            adj[i].emplace_back(0, j);
            adj[j].emplace_back(0, i);
            used[i][j] = true;
        }
        T -= (N-1);

        while (T--) {
            auto [x, y] = randpair(1, N);
            while (used[x][y]) {
                std::pair<int, int> edge = randpair(1, N);
                x = edge.first;
                y = edge.second;
            }
            used[x][y] = true;
            int C = randint(1, max_weight);
            print(x); putChar(' '); print(y); putChar(' '); print(C); putChar('\n');
            adj[x].emplace_back(C, y);
            adj[y].emplace_back(C, x);
        }
    }
    else if (slowDijkstra) { // case causing dijkstra to get close to worst case
        // boolean array to make sure no duplicate edges
        bool used[N+1][N+1];
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) used[i][j] = false;
        }

        // first generate a spanning tree
        for (int i=2; i<=N; i++) {
            int aux = i-1;
            int w = 2*(i-aux)-1;
            print(aux); putChar(' '); print(i); putChar(' '); print(w); putChar('\n');
            adj[i].emplace_back(w, aux);
            adj[aux].emplace_back(w, i);
            used[aux][i] = true;
            T--;
        }

        while (T--) {
            auto [x, y] = randpair(1, N);
            while (used[x][y]) {
                std::pair<int, int> edge = randpair(1, N);
                x = edge.first;
                y = edge.second;
            }
            used[x][y] = true;
            int w = 2*(y-x)-1;
            print(x); putChar(' '); print(y); putChar(' '); print(w); putChar('\n');
            adj[x].emplace_back(w, y);
            adj[y].emplace_back(w, x);
        }
    }
    else if (complete) {
        for (int i=1; i<=N; i++) {
            for (int j=i+1; j<=N; j++) {
                int w = 2*(j-i)-1;
                print(i); putChar(' '); print(j); putChar(' '); print(w); putChar('\n');
                adj[i].emplace_back(w, j);
                adj[j].emplace_back(w, i);
            }
        }
    }
    else if (maxCase) {
        // boolean array to make sure no duplicate edges
        bool used[N+1][N+1];
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) used[i][j] = false;
        }

        std::vector<std::pair<int, int>> path;
        for (int i=1; i<N; i++) path.emplace_back(i, i+1);
        shuffle(path.begin(), path.end(), gen);
        for (auto [i, j]: path) {
            print(i); putChar(' '); print(j); putChar(' '); print(max_weight); putChar('\n');
            adj[i].emplace_back(max_weight, j);
            adj[j].emplace_back(max_weight, i);
            used[i][j] = true;
        }
        T -= (N-1);

        while (T--) {
            auto [x, y] = randpair(1, N);
            while (used[x][y]) {
                std::pair<int, int> edge = randpair(1, N);
                x = edge.first;
                y = edge.second;
            }
            used[x][y] = true;
            int C = max_weight;
            print(x); putChar(' '); print(y); putChar(' '); print(C); putChar('\n');
            adj[x].emplace_back(C, y);
            adj[y].emplace_back(C, x);
        }
    }
    else { // uniformly randomly generated graph
        // boolean array to make sure no duplicate edges
        bool used[N+1][N+1];
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) used[i][j] = false;
        }

        // first generate a spanning tree
        for (int i=2; i<=N; i++) {
            int aux = randint(1, i-1);
            int w = randint(0, max_weight);
            print(i); putChar(' '); print(aux); putChar(' '); print(w); putChar('\n');
            adj[i].emplace_back(w, aux);
            adj[aux].emplace_back(w, i);
            used[aux][i] = true;
            T--;
        }

        // generate the rest of the edges
        while (T--) {
            auto [x, y] = randpair(1, N);
            while (used[x][y]) {
                std::pair<int, int> edge = randpair(1, N);
                x = edge.first;
                y = edge.second;
            }
            used[x][y] = true;
            int C = randint(0, max_weight);
            print(x); putChar(' '); print(y); putChar(' '); print(C); putChar('\n');
            adj[x].emplace_back(C, y);
            adj[y].emplace_back(C, x);
        }
    }

    print(K); putChar('\n');

    int z = N;
    while (K--) {
        int Pz = randint(0, max_initial);
        print(z); putChar(' '); print(Pz); putChar('\n');
        P.emplace_back(z, Pz);
        z--;
    }

    print(D); putChar('\n');
    fwrite(IO, 1, outIdx, stdout);

    memset(dist, 0x3f, sizeof(dist));
    dist[D] = 0;
    for (int i=1; i<=N; i++) {
        int v = -1;
        for (int j=1; j<=N; j++) {
            if (!u[j] && (v == -1 || dist[j] < dist[v])) v = j;
        }
        if (dist[v] > INT32_MAX)
            break;
        u[v] = true;
        for (auto [nextW, nextN]: adj[v]) {
            if (dist[v]+nextW < dist[nextN]) dist[nextN] = dist[v]+nextW;
        }
    }

    int minCost = INT32_MAX;
    for (auto p: P) minCost = std::min(minCost, p.second+dist[p.first]);
    std::cerr << minCost << '\n' << std::flush;
    return 0;
}
