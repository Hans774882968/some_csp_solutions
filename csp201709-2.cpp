#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
const int SZ = 1000 + 5;

int n,k;
int ans[SZ];
struct Node{
    int typ,id,t;
    bool operator < (const Node &rh) const {
        if(t ^ rh.t) return t > rh.t;
        if(typ ^ rh.typ) return typ < rh.typ;
        return id > rh.id;
    }
};
priority_queue<Node> q;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int main(int argc, char** argv) {
    read(n);read(k);
    rep(i,1,n) ans[i] = i;
    rep(_,1,k){
        int w,s,c;read(w);read(s);read(c);
        q.push({1,w,s});
        q.push({2,w,s + c});
    }
    while(!q.empty()){
        Node u = q.top();q.pop();
        if(u.typ == 1){
            int pos = 1;
            for(;pos <= n;++pos){
                if(ans[pos] == u.id) break;
            }
            ans[pos] = -1;
        }
        else{
            int pos = 1;
            for(;pos <= n;++pos){
                if(ans[pos] == -1) break;
            }
            ans[pos] = u.id;
        }
    }
    rep(i,1,n) printf("%d%c",ans[i]," \n"[i == n]);
    getchar();getchar();
    return 0;
}