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
const int SZ = 50 + 5;

int n,m,lims[SZ];
struct Commo{
    int typ,id,score;
    bool operator < (const Commo &rh) const {
        if(score ^ rh.score) return score > rh.score;
        else if(typ ^ rh.typ) return typ < rh.typ;
        return id < rh.id;
    }
};
set<Commo> commo;
map<int,int> id2score[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int main(int argc, char** argv) {
    read(m);read(n);
    rep(_,1,n){
        int id,score;read(id);read(score);
        rep(i,0,m - 1) commo.insert({i,id,score});
        rep(i,0,m - 1) id2score[i][id] = score;
    }
    int q;read(q);
    while(q--){
        int op;read(op);
        if(op == 1){
            int typ,id,score;read(typ);read(id);read(score);
            commo.insert({typ,id,score});
            id2score[typ][id] = score;
        }
        if(op == 2){
            int typ,id;read(typ);read(id);
            commo.erase({typ,id,id2score[typ][id]});
        }
        if(op == 3){
            int k;read(k);
            rep(i,0,m - 1) read(lims[i]);
            vector<int> ans[SZ];
            for(auto x: commo){
                if(k <= 0) break;
                if(lims[x.typ] <= 0) continue;
                lims[x.typ]--;k--;
                ans[x.typ].push_back(x.id);
            }
            rep(i,0,m - 1){
                if(!ans[i].size()) puts("-1");
                else{
                    rep(j,0,ans[i].size() - 1)
                        printf("%d%c",ans[i][j]," \n"[j == ans[i].size() - 1]);
                }
            }
        }
    }
    getchar();getchar();
    return 0;
}