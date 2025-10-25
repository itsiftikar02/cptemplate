class Segtree{
    public:
    struct Node{
        int sum;
        Node(){
            sum=0;
        }
    };
    Node merge(Node a,Node b){
        Node ans;
        ans.sum=a.sum+b.sum;
        return ans;
    }
    vector<Node>tree;
    int len;
    Segtree(){}
    Segtree(int l){
        len=l;
        tree.resize(4*l);
    }
    void build(const vector<int>&vec,int l,int r,int node){
        if(l==r){
            tree[node].sum=vec[l];
            return;
        }
        int mid=(l+r)>>1;
        build(vec,l,mid,2*node);
        build(vec,mid+1,r,2*node+1);
        tree[node]=merge(tree[2*node],tree[2*node+1]);
    }
    void point_update(int l,int r,int node,int idx,int val){
        if(idx>r||idx<l)    return;
        if(idx==l&&idx==r){
            tree[node].sum+=val;
            return;
        }
        int mid=(l+r)>>1;
        point_update(l,mid,2*node,idx,val);
        point_update(mid+1,r,2*node+1,idx,val);
        tree[node]=merge(tree[2*node],tree[2*node+1]);
    }
    Node query(int l,int r,int node,int ql,int qr){
        if(l>=ql&&r<=qr)    return tree[node];
        if(l>qr||r<ql)  return Node();
        int mid=(l+r)>>1;
        return merge(query(l,mid,2*node,ql,qr),query(mid+1,r,2*node+1,ql,qr));
    }
    void build(const vector<int>&vec){
        build(vec,0,len-1,1);
    }
    void point_update(int idx,int val){
        point_update(0,len-1,1,idx,val);
    }
    Node query(int l,int r){
        return query(0,len-1,1,l,r);
    }
};