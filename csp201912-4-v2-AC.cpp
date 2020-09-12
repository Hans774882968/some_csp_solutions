#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
const int SZ = 500 + 5;

int n,m,T,k;
vector<int> G[SZ];
vector<vector<int> > h;int hptr[SZ];
struct Event{int t,to,hidx;};
queue<Event> q;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

bool modify(int v,int hidx){
    if(h[hptr[v]].size() < h[hidx].size() || (h[hptr[v]].size() == h[hidx].size() && h[hptr[v]].back() > h[hidx].back())){
        hptr[v] = hidx;
        return true;
    }
    return false;
}

void show_blk(int u){
    printf("%d",h[hptr[u]].size());
    for(int v: h[hptr[u]]) printf(" %d",v);
    puts("");
}

void event_update(int tim){
    while(!q.empty() && q.front().t <= tim){
        Event ev = q.front();q.pop();int u = ev.to;
        bool fl = modify(u,ev.hidx);
        if(fl){
            for(int v: G[u]) q.push({ev.t + T,v,hptr[u]});//更新后必须创建事件
        }
    }
}

int main(int argc, char** argv) {
    read(n);read(m);
    rep(i,1,m){
        int p1,p2;read(p1);read(p2);
        G[p1].push_back(p2);
        G[p2].push_back(p1);
    }
    read(T);read(k);
    h.push_back(vector<int>(1,0));
    rep(i,1,n) hptr[i] = 0;
    while(k--){
        int x[4];x[0] = 0;
        char s[50];fgets(s,50,stdin);s[strlen(s) - 1] = '\0';
        stringstream ss(s);
        while(ss >> x[++x[0]]);
        int u = x[1],tim = x[2],c = x[3];
        if((--x[0]) == 3){
            event_update(tim);
            vector<int> blk = h[hptr[u]];
            blk.push_back(c);
            h.push_back(blk);
            hptr[u] = h.size() - 1;
            for(int v: G[u]) q.push({tim + T,v,hptr[u]});
        }
        else{
            event_update(tim);
            show_blk(u);
        }
    }
    getchar();getchar();
    return 0;
}