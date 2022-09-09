
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
