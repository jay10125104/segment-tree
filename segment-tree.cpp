#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define for0(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>
#define pb push_back
#define sz(x) sizeof(x)
#define vec(n, x) vector<int> v(n, x)
const ll INF = 1e18;
const ll MOD = 1000000007;
#define hi        \
    ll tests;     \
    cin >> tests; \
    while (tests--)
#define all(x) x.begin(), x.end()
#define readv(vec)      \
    for (auto &x : vec) \
    {                   \
        cin >> x;       \
    }
#define PHI M_PI
#define graph                   \
    int V;                      \
    cin >> V;                   \
    vector<int> adj[V];         \
    int e;                      \
    for (int i = 0; i < e; i++) \
    {                           \
        int u, v;               \
        cin >> u >> v;          \
        adj[u].push_back(v);    \
        adj[v].push_back(u);    \
    }
#define printv(vec)       \
    for (auto x : vec)    \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl;
#define sortasc(vec) sort(all(vec));
#define sortdes(vec) sort(vec.rbegin(), vec.rend());
#define setpre(x) cout << fixed << setprecision(10) << x << endl
#define kick cout << 'C' << 'a' << 's' << 'e' << ' ' << '#' << k << ':' << ' '
vector<ll> sieve(int n)
{
    int *tree = new int[n + 1]();
    vector<ll> vect;
    for (int i = 2; i <= n; i++)
        if (tree[i] == 0)
        {
            vect.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                tree[j] = 1;
        }
    return vect;
}
bool pal(string s)
{
    int i = 0;
    int j = s.size() - 1;
    while (i < j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
ll op1(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
ll op2(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll op3(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
int powerexpo(int x, int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
        {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll C(ll a, ll b) { return (a + b - 1) / b; }
// code by CasioFx-69
struct Segtree
{
    vector<int> v;
    Segtree(vector<int> arr)
    {
        v = arr;
    }
    void build(int node, int start, int end, vector<int> &tree)
    {
        if (start == end)
        {
            tree[node] = v[start];
            return;
        }
        int mid = (start + end) / 2;
        int left = 2 * node;
        int right = 2 * node + 1;
        build(left, start, mid, tree);
        build(right, mid + 1, end, tree);
        tree[node] = tree[left] +  tree[right];
    }
    int query(vector<int> &tree, int node, int l, int r, int start, int end)
    {
        if (end < l || start > r)
        {
            return 0;
        }
        if (start == end)
        {
            return tree[node];
        }
        else if (start >= l && end <= r)
        {
            return tree[node];
        }
        else
        {
            int mid = (start + end) / 2;
            int left = query(tree, node * 2, l, r, start, mid);
            int right = query(tree, node * 2 + 1, l, r, mid + 1, end);
            return left+right;
        }
    }
};
// return 0;
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    readv(v); // input;
    vector<int> tree(4 * n);
    Segtree se = Segtree(v);
    se.build(1,0,n-1,tree);
    int k;
    cin >> k;
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << se.query(tree, 1, l, r, 0, n - 1) << endl;
    }

    return 0;
}