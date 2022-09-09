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
    int *arr = new int[n + 1]();
    vector<ll> vect;
    for (int i = 2; i <= n; i++)
        if (arr[i] == 0)
        {
            vect.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
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
struct unionfind
{
    int n;
    vector<int> rank;
    vector<int> parent;
    unionfind(int n)
    {
        rank.resize(n);
        fill(rank.begin(), rank.end(), 0);
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int node)
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
    bool Union(int u, int v)
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
struct seg
{
    vector<vector<int>> tree;
    vector<vector<int>> v;
    seg(vector<vector<int>> arr)
    {
        v = arr;
        vector<vector<int>> t(4 * arr.size(), vector<int>(4 * arr[0].size() - 1, 0));
        tree = t;
    }
    void buildy(int nodex, int startx, int endx, int nodey, int starty, int endy)
    {
        if (starty == endy)
        {
            if (startx == endx)
            {
                tree[nodex][nodey] = v[startx][starty];
            }
            else
            {
                tree[nodex][nodey] = tree[nodex * 2][nodey] + tree[nodex * 2 + 1][nodey];
            }
        }
        else
        {
            int mid = (starty + endy) / 2;
            buildy(nodex, startx, endx, nodey * 2, starty, mid);
            buildy(nodex, startx, endx, nodey * 2 + 1, mid + 1, endy);
            tree[nodex][nodey] = tree[nodex][nodey * 2] + tree[nodex][nodey * 2 + 1];
        }
    }
    void buildx(int nodex, int startx, int endx)
    {
        if (startx == endx)
        {
            buildy(nodex, startx, endx, 1, 1, v[0].size() - 1);
        }
        else
        {
            int mid = (startx + endx) / 2;
            buildx(nodex * 2, startx, mid);
            buildx(nodex * 2 + 1, mid + 1, endx);
            buildy(nodex, startx, endx, 1, 1, v[0].size() - 1);
        }
    }
    void updatey(int nodex, int startx, int endx, int nodey, int starty, int endy, int x, int y, int val)
    {
        if (starty == endy)
        { 
            if(startx==endx){
            tree[nodex][nodey]+=val;
            }
            else{
                tree[nodex][nodey] = tree[nodex * 2][nodey] + tree[nodex * 2 + 1][nodey];
                // tree[nodex][nodey] = 
            }
        }
        else
        {
            int mid = (starty + endy) / 2;
            if (mid >= y)
            {
                updatey(nodex, startx, endx, nodey * 2, starty, mid, x, y, val);
            }
            else
            {
                updatey(nodex, startx, endx, nodey * 2+1,mid+1,endy, x, y, val);
            }
            tree[nodex][nodey] = tree[nodex][nodey * 2] + tree[nodex][nodey * 2 + 1];
        }
    }
    void updatex(int nodex, int startx, int endx, int x, int y, int val)
    {
        if (startx == endx)
        {
            updatey(nodex,startx,endx,1,1,v[0].size()-1,x,y,val);
        }
        else
        {
            int mid = (startx + endx) / 2;
            // int mid = (starty + endy) / 2;
            if (mid >= x)
            updatex(nodex * 2, startx, mid, x, y, val);
            else
            updatex(nodex * 2 + 1, mid + 1, endx, x, y, val);
            updatey(nodex,startx,endx,1,1,v[0].size()-1,x,y,val);
        }
    }
    int query(int nodex,int nodey,int starty,int endy,int c1,int c2){
        if(starty>c2 ||  endy<c1){
            return 0;
        }
        if(starty==endy){
            return tree[nodex][nodey];
        }
        else if(starty>=c1 && endy<=c2){
            return tree[nodex][nodey];
        }
        else{
            int mid = (starty+endy)/2;
            int one = query(nodex,nodey*2,starty,mid,c1,c2);
            int two = query(nodex,nodey*2+1,mid+1,endy,c1,c2);
            return one+two;
        }
    }
    int queryx(int nodex,int startx,int endx,int r1,int r2,int c1,int c2){
        if(startx>r2 || endx< r1){
            return 0;
        }
        if(startx==endx){
            return query(nodex,1,1,v[0].size()-1,c1,c2);
        }
        else if(startx>=r1 && endx<=r2){
            return query(nodex,1,1,v[0].size()-1,c1,c2);
        }
        else{
            int mid = (startx+endx)/2;
            int one = queryx(nodex*2,startx,mid,r1,r2,c1,c2);
            int two = queryx(nodex*2+1,mid+1,endx,r1,r2,c1,c2);
            return one + two;
        }
    }
};
int main()
{

    int m, n;  
    cin >> m >> n;
    vector<vector<int>> v(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> v[i][j];
        }
        // printv(v[i]);
    }
    for (auto i : v)
    {
        // printv(i);
    }
    seg se = seg(v);
    se.buildx(1, 1, m);
    int q;
    cin>>q;
    while(q--){
        char c;
        cin>>c;
        if(c=='q'){
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            cout<<se.queryx(1,1,m,a,c,b,d)<<endl;
        }
        else{
            int x,y,val;
            cin>>x>>y>>val;
            se.updatex(1,1,m,x,y,val);
        }
    }
    
    return 0;
}