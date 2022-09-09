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
#define hi         \
     ll tests;     \
     cin >> tests; \
     while (tests--)
#define all(x) x.begin(), x.end()
#define readv(vec)       \
     for (auto &x : vec) \
     {                   \
          cin >> x;      \
     }
#define PHI M_PI
#define graph                    \
     int V;                      \
     cin >> V;                   \
     vector<int> adj[V];         \
     int e;                      \
     for (int i = 0; i < e; i++) \
     {                           \
          int u, v;              \
          cin >> u >> v;         \
          adj[u].push_back(v);   \
          adj[v].push_back(u);   \
     }
#define printv(vec)         \
     for (auto x : vec)     \
     {                      \
          cout << x << ' '; \
     }                      \
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
int main()
{
     int n;
     cin>>n;
     int size = ceil(sqrt(n));
     // cout<<size<<" ";
     vector<int>decompose(size,INT_MAX);
     vector<int>v(n);
     for(int i=0;i<n;i++){
          cin>>v[i];
          decompose[i/size] = min(decompose[i/size],v[i]);
     }
     int q;
     cin>>q;
     while(q--){
          int a,b;
          cin>>a>>b;
          int start = a;
          int ans = INT_MAX;
          while((start%size)!=0){
               ans = min(ans,v[start]);
               start++;
          }
          while((start+size)<b){
               ans=min(ans,decompose[start/size]);
               start+=size;
          }
          while(start!=b){
               ans=min(ans,v[start]);
               start++;
          }
          cout<<ans<<endl;
     }

     return 0;
}