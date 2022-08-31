#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define for0(i, n) for (long long int i = 0; i < n; i++)
#define vi vector<long long int>
#define pb push_back
#define sz(x) sizeof(x)
#define vec(n, x) vector<long long int> v(n, x)
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
    long long int V;                      \
    cin >> V;                   \
    vector<long long int> adj[V];         \
    long long int e;                      \
    for (long long int i = 0; i < e; i++) \
    {                           \
        long long int u, v;               \
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
vector<ll> sieve(long long int n)
{
    long long int *arr = new long long int[n + 1]();
    vector<ll> vect;
    for (long long int i = 2; i <= n; i++)
        if (arr[i] == 0)
        {
            vect.push_back(i);
            for (long long int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
        }
    return vect;
}
bool pal(string s)
{
    long long int i = 0;
    long long int j = s.size() - 1;
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
long long int powerexpo(long long int x, long long int y, long long int p)
{
    long long int res = 1;
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
struct unionfind
{
    long long int n;
    vector<long long int> rank;
    vector<long long int> parent;
    unionfind(long long int n)
    {
        rank.resize(n);
        fill(rank.begin(), rank.end(), 0);
        parent.resize(n);
        for (long long int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    long long int find(long long int node)
    {
        if (node == parent[node])
        {
            return node;
        }
        else
        {
            return parent[node] = find(parent[node]);
        }
    }
    bool Union(long long int u, long long int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
        {
            return false;
        }
        if (rank[u] < rank[v])
        {
            parent[u] = v;
        }
        else if (rank[u] > rank[v])
        {
            parent[v] = u;
        }
        else
        {
            parent[v] = u;
            rank[u]++;
        }
        return true;
    }
};
// code by CasioFx-69
struct segment
{
    vector<long long int> v;
    vector<pair<long long int, long long int>> tree;
    vector<long long int> lazy;
    segment(vector<long long int> &arr)
    {
        v = arr;
        vector<pair<long long int, long long int>> t(4 * arr.size());
        vector<long long int> te(4 * arr.size());
        tree = t;
        lazy = te;
    }
    void build(long long int node, long long int start, long long int end)
    {
        if (start == end)
        {
            tree[node].first = v[start] * v[start];
            tree[node].second = v[start];
        }
        else
        {
            long long int mid = (start + end) / 2;
            build(node * 2, start, mid);
            build(node * 2 + 1, mid + 1, end);
            tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
            tree[node].second = tree[node * 2].second + tree[node * 2 + 1].second;
        }
    }
    void propogate(long long int node,long long int start,long long int end){
        if(lazy[node]==0){
            return;
        }
        if(start==end){
            tree[node].second+=lazy[node];
            tree[node].first=(tree[node].second*tree[node].second);
            lazy[node]=0;
        }
        else{ 
            long long int range = end-start+1;
            tree[node].first+=(range*lazy[node]*lazy[node]);
            tree[node].first+=(2*tree[node].second*lazy[node]);
            tree[node].second+=(range*lazy[node]);
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
            lazy[node]=0;
        }
    }
    void update(long long int node,long long int start,long long int end,long long int l,long long int r,long long int x){
        propogate(node,start,end);
        if(start>r || end<l){
            return ;
        }
        else if(start==end){
            lazy[node]+=x;
            propogate(node,start,end);
        }
        else if(l<=start && r>=end){
            lazy[node]+=x;
            propogate(node,start,end); 
        }
        else{
            long long int mid=(start+end)/2;
            update(node*2,start,mid,l,r,x);
            update(node*2+1,mid+1,end,l,r,x);
            tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
            tree[node].second = tree[node * 2].second + tree[node * 2 + 1].second;
        }
    }
    pair<long long int,long long int> query(long long int node,long long int start,long long int end,long long int l,long long int r){
        if(start>r || end<l){
            return {0,0};
        }
        propogate(node,start,end);
        if (start == end)
        {
            return tree[node];
        }
        if(start>=l && end<=r){
            return tree[node];
        }
        else{
            long long int mid = (start+end)/2;
            auto left = query(node*2,start,mid,l,r);
            auto right = query(node*2+1,mid+1,end,l,r);
            return {left.first+right.first,left.second+right.second};
        }

    }
};
int main()
{
    long long int n;
    cin >> n;
    vector<long long int> v(n);
    readv(v);
    segment se = segment(v);
    se.build(1, 0, n - 1);
    long long int q;
    cin>>q;
    while(q--){
        long long int a;cin>>a;
        if(a==1){
            long long int b,c,d;cin>>b>>c>>d;
            se.update(1,0,n-1,b,c,d);
        }
        else{
            long long int b,c;
            cin>>b>>c;
            cout<<se.query(1,0,n-1,b,c).first<<endl;
        }
    }

    return 0;
}
