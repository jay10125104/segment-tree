struct seg
{
    vector<int> v;
    vector<int> tree;
    vector<int> lazy;
    seg(vector<int>&arr)
    {
        v = arr;
        vector<int> dummy1(4 * v.size());
        vector<int> dummy2(4 * v.size());
        tree = dummy1;
        lazy = dummy2;
    }
    void build(int node,int start,int end){
        if(start==end){
            tree[node]=v[start];
        }
        else{
            int mid = (start+end)/2;
            build(node*2,start,mid);
            build(node*2+1,mid+1,end);
            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }
    void propogate(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] += lazy[node];
            lazy[node] = 0;
        }
        else
        {
            tree[node] += ((end - start + 1) * lazy[node]);
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }
    void update(int node, int start, int end, int l, int r, int x)
    {
        propogate(node, start, end);
        if (start > r || end < l)
        {
            return;
        }
        if (start == end)
        {
            tree[node] += x;
        }
        else if (l <= start && end <= r)
        {
            lazy[node] += x;
            propogate(node, start, end);
        }
        else
        {
            int mid = (start + end) / 2;
            update(node * 2, start, mid, l, r, x);
            update(node * 2 + 1, mid + 1, end, l, r, x);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }
    int query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
        {
            return 0;
        }
        propogate(node,start,end);
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
            int left = query(node * 2, start, mid, l, r);
            int right = query(node * 2 + 1, mid + 1, end, l, r);
            return left + right;
        }
    }
};
// int main()
// {
//     int n;
//     cin>>n;
//     vector<int>v(n);
//     readv(v);
//     int q;
//     cin>>q;
//     // printv(v);
//     seg se = seg(v);
//     se.build(1,0,n-1);
//     while(q--){
//         int a;
//         cin>>a;
//         if(a==0){
//             int b,c;
//             cin>>b>>c;
//             cout<<se.query(1,0,n-1,b,c)<<endl;
//         }
//         else{
//             int b,c,d;
//             cin>>b>>c>>d;
//             se.update(1,0,n-1,b,c,d);
//         }
//     }
//     return 0;
// }