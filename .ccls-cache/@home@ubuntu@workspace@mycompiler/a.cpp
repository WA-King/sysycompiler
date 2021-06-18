const int maxn=50;
int dt[maxn*4];
int L[maxn*4],R[maxn*4];
void pushup(int k) {
    dt[k]=dt[k*2]+dt[k*2+1];
}
void build(int l,int r,int k) {
    L[k]=l;
    R[k]=r;
    if(l==r) {
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,k*2);
    build(mid+1,r,k*2+1);
}
void change(int pos,int k,int x) {
    if(L[k]==R[k]) {
        dt[k]=x;
        return ;
    }
    int mid=(L[k]+R[k])/2;
    if(mid>=pos) change(pos,k*2,x);
    else change(pos,k*2+1,x);
	pushup(k);
}
int query(int l,int r,int k) {
    if(l<=L[k]&&R[k]<=r) {
        return dt[k];
    }
    int ans=0,mid=(L[k]+R[k])/2;
    if(mid>=l) ans=ans+query(l,r,k*2);
    if(mid<r) ans=ans+query(l,r,k*2+1);
    return ans;
}
int main() {
    int l,r;
    getint(l);
    getint(r);
    build(l,r,1);
    printint(L[1]);
    printint(R[1]);
    int q;
    getint(q);
    while(q>0) {
        q=q-1;
        int ty;
        getint(ty);
        if(ty==1) {
            int pos,x;
            getint(pos);
            getint(x);
            change(pos,1,x);
        }
        else {
            int l,r;
            getint(l);
            getint(r);
            int ans=query(l,r,1);
            printint(ans);
        }
    }
}
