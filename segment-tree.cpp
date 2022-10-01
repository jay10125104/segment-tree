struct Segtree
{
    vector<int> v;
    vector<int>tree;
    Segtree(vector<int> arr)
    {
        v = arr;
        int n=v.size();
        vector<int> t(4 * n);
        tree = t;
    }
    void build(int node, int start, int end)
    {
        //start with node 1 ->> call for  start and end.
        // if start and end are equal then we have a single node;
        //therefore tree[node] = v[start];
        //else we call for left->mid; and mid+1 -> right;
        if (start == end)
        {
            tree[node] = v[start];
            return;
        }
        int mid = (start + end) / 2;
        int left = 2 * node;
        int right = 2 * node + 1;
        build(left, start, mid);
        build(right, mid + 1, end);
        tree[node] = max(tree[left],tree[right]);
    }
    int query(int node, int l, int r, int start, int end)
    {
        // if end < startidx of query or start>endidx of query
        //return -1;
        if (end < l || start > r)
        {
            return -1;
        }
        //if start==end
        //retrun tree[node];
        if (start == end)
        {
            return tree[node];
        }
        // if start and end in middle 
        //return tree[node];
        else if (start >= l && end <= r)
        {
            return tree[node];
        }
        else
        {
            //call for start->mid with node->number 2*node;
            // mid+1->end; with node number -> 2*node+1;
            int mid = (start + end) / 2;
            int left = query(node * 2, l, r, start, mid);
            int right = query(node * 2 + 1, l, r, mid + 1, end);
            return max(left,right); // maxof(left,right);
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
    
    Segtree se = Segtree(v);
    se.build(1,0,n-1);
    int k;
    cin >> k;
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << se.query(1, l, r, 0, n - 1) << endl;
    }

    return 0;
}
