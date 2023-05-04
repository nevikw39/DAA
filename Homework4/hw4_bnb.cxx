/**                  _ _              _____ ___
 *  _ __   _____   _(_) | ____      _|___ // _ \
 * | '_ \ / _ \ \ / / | |/ /\ \ /\ / / |_ \ (_) |
 * | | | |  __/\ V /| |   <  \ V  V / ___) \__, |
 * |_| |_|\___| \_/ |_|_|\_\  \_/\_/ |____/  /_/
 **/
#include <bits/extc++.h>
#ifndef nevikw39
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("abm,bmi,bmi2,mmx,sse,sse2,sse3,ssse3,sse4,popcnt,avx,avx2,fma,tune=native")
#pragma comment(linker, "/stack:200000000")
struct
{
    template <typename T>
    auto &operator<<(const T &x) { return *this; }
} __cerr;
#define cerr __cerr
#else
#pragma message("hello, nevikw39")
#endif
#pragma message("GL; HF!")
#define ALL(X) begin(X), end(X)
#define ST first
#define ND second
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T, typename Cmp = greater<T>, typename Tag = pairing_heap_tag>
using _heap = __gnu_pbds::priority_queue<T, Cmp, Tag>;
template <typename K, typename M = null_type>
using _hash = gp_hash_table<K, M>;
template <typename K, typename M = null_type, typename Cmp = less<K>, typename T = rb_tree_tag>
using _tree = tree<K, M, Cmp, T, tree_order_statistics_node_update>;

struct TSP_brute_force
{
    vector<int> p;
    int cost = numeric_limits<int>::max();

    TSP_brute_force(const vector<vector<int>> &d)
    {
        int n = d.size();
        vector<int> p(n);
        iota(ALL(p), 0);
        do
        {
            int cost = d[p.back()][p.front()];
            for (int i = 1; i < n; i++)
                cost += d[p[i - 1]][p[i]];
            // cerr << '\t' << cost << '\n';
            if (this->cost > cost)
            {
                this->cost = cost;
                this->p = p;
            }
        } while (next_permutation(ALL(p)));
    }
};

struct TSP_branch_bound
{
    vector<int> p;
    int cost = numeric_limits<int>::max();

    struct node
    {
        vector<int> p;
        int cost, n, cur = 0, lv = 1;
        vector<vector<int>> matrix;

        node(const vector<vector<int>> &d) : p{0}, n(d.size()), matrix(d)
        {
            matrix[0][0] = numeric_limits<int>::max();
            cost = reduce_row() + reduce_col();
        }

        node(const node &nd, int x) : p(nd.p), n(nd.n), cur(x), lv(nd.lv + 1), matrix(nd.matrix)
        {
            p.push_back(x);
            for (int i = 0; i < n; i++)
                matrix[nd.cur][i] = matrix[i][cur] = numeric_limits<int>::max();
            matrix[cur][0] = numeric_limits<int>::max();
            cost = nd.cost + nd.matrix[nd.cur][cur] + reduce_row() + reduce_col();
        }

        int reduce_row()
        {
            vector<int> row(n, numeric_limits<int>::max());
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    row[i] = min(row[i], matrix[i][j]);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (matrix[i][j] < numeric_limits<int>::max())
                        matrix[i][j] -= row[i];
            int cost = 0;
            for (int i : row)
                if (i < numeric_limits<int>::max())
                    cost += i;
            return cost;
        }

        int reduce_col()
        {
            vector<int> col(n, numeric_limits<int>::max());
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    col[j] = min(col[j], matrix[i][j]);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (matrix[i][j] < numeric_limits<int>::max())
                        matrix[i][j] -= col[j];
            int cost = 0;
            for (int i : col)
                if (i < numeric_limits<int>::max())
                    cost += i;
            return cost;
        }

        bool operator>(const node &n) const { return cost > n.cost; }
    };

    TSP_branch_bound(const vector<vector<int>> &d)
    {
        int n = d.size();
        _heap<node> pq;
        pq.push(node(d));
        while (pq.size())
        {
            node t = pq.top();
            pq.pop();
            if (t.lv == n)
            {
                p = t.p;
                cost = t.cost;
                break;
            }
            for (int i = 0; i < n; i++)
                if (t.matrix[t.cur][i] < numeric_limits<int>::max())
                    pq.push(node(t, i));
        }
    }
};

int main()
{
#ifndef nevikw39
    cin.tie(nullptr)->sync_with_stdio(false);
#endif // nevikw39

    int n;
    cin >> n;
    vector d(n, vector<int>(n));
    for (auto &i : d)
        for (int &j : i)
            cin >> j;

    auto tik = chrono::high_resolution_clock::now();
    TSP_branch_bound tsp_branch_bound(d);
    auto tok = chrono::high_resolution_clock::now();
    auto wall_time_bb = chrono::duration_cast<chrono::microseconds>(tok - tik).count();

#ifdef nevikw39
    tik = chrono::high_resolution_clock::now();
    TSP_brute_force tsp_brute_force(d);
    tok = chrono::high_resolution_clock::now();
    auto wall_time_bf = chrono::duration_cast<chrono::microseconds>(tok - tik).count();
#endif // nevikw39

    cout << "The shortest Hamiltonian cycle:\n";
    copy(ALL(tsp_branch_bound.p), ostream_iterator<int>(cout, " "));
    cout << tsp_branch_bound.p.front() << '\n'
         << "Total cost: " << tsp_branch_bound.cost << '\n'
         << "Time: " << wall_time_bb << " μs\n";

#ifdef nevikw39
    assert(tsp_brute_force.cost == tsp_branch_bound.cost);
    clog << n << ',' << wall_time_bf << ',' << wall_time_bb << endl;
#endif // nevikw39

    return 0;
}
