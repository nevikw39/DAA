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

using Itr = vector<int>::iterator;

int kth_qs(int, Itr, Itr);
int kth_pns(int, Itr, Itr);

int median_of_medians(Itr first, Itr last)
{
    vector<int> medians;
    medians.reserve((last - first + 4) / 5);
    for (Itr itr = first, jtr; itr < last; itr = jtr)
    {
        jtr = min(itr + 5, last);
        sort(itr, jtr);
        medians.push_back(*(itr + (jtr - itr >> 1)));
    }
    return kth_pns(medians.size() >> 1, ALL(medians));
}

int kth_pns(int k, Itr first, Itr last)
{
    if (last - first <= 5)
    {
        sort(first, last);
        return *(first + k);
    }
    int pivot = median_of_medians(first, last);
    auto less = partition(first, last, [=](int x)
                          { return x < pivot; }),
         greater = partition(less, last, [=](int x)
                             { return x == pivot; });
    if (k < less - first)
        return kth_pns(k, first, less);
    else if (k < greater - first)
        return pivot;
    return kth_pns(k - (greater - first), greater, last);
}

int main()
{
#ifndef nevikw39
    cin.tie(nullptr)->sync_with_stdio(false);
#endif // nevikw39

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a)
        cin >> i;

    auto tik = chrono::high_resolution_clock::now();
    int pns = kth_pns(k - 1, ALL(a));
    auto tok = chrono::high_resolution_clock::now();
    auto wall_time_pns = chrono::duration_cast<chrono::milliseconds>(tok - tik).count();
    cout << pns << '\n'
         << "Time: " << wall_time_pns << " ms\n";

#ifdef nevikw39
    tik = chrono::high_resolution_clock::now();
    int qs = kth_qs(k - 1, ALL(a));
    tok = chrono::high_resolution_clock::now();
    auto wall_time_qs = chrono::duration_cast<chrono::milliseconds>(tok - tik).count();
    cout << qs << '\n'
         << "Time: " << wall_time_qs << " ms\n";
#endif // nevikw39

#ifdef nevikw39
    assert(pns == qs);
    clog << n << ',' << wall_time_qs << ',' << wall_time_pns << endl;
#endif // nevikw39

    return 0;
}
