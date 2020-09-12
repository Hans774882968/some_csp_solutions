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

int n,m;bool vis[2][SZ];
vector<int> G[2][SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void dfs(int u,int pos){
    vis[pos][u] = true;
    for(int v: G[pos][u]){
        if(vis[pos][v]) continue;
        dfs(v,pos);
    }
}

int main(int argc, char** argv) {
    read(n);read(m);
    rep(_,1,m){
        int p1,p2;read(p1);read(p2);
        G[0][p1].push_back(p2);
        G[1][p2].push_back(p1);
    }
    int ans = 0;
    rep(i,1,n){
        rep(pos,0,1){
            rep(j,1,n) vis[pos][j] = false;
            dfs(i,pos);
        }
        int reach = 0;
        rep(j,1,n) reach += (vis[0][j] || vis[1][j]);
        ans += (reach == n);
    }
    printf("%d\n",ans);
    getchar();getchar();
    return 0;
}