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
const int SZ = 1e5 + 5,M = 25;
const LL mod = 998244353;
const int dm[7] = {-1,0,1,-1,2,-1,3};

int n;
char s0[SZ];string s;

struct Mat{
    LL m[M][M];
    Mat(){memset(m,0,sizeof m);}
};
Mat mul(Mat a,Mat b){
    Mat ret;
    rep(i,0,M - 6){
        rep(j,0,M - 6){
            LL s = 0;
            rep(k,0,M - 6) s = (s + a.m[i][k] * b.m[k][j] % mod) % mod;
            ret.m[i][j] = s;
        }
    }
    return ret;
}
Mat q_pow(Mat a,int b){
    Mat ret;rep(i,0,M - 6) ret.m[i][i] = 1;
    for(;b;b >>= 1){
        if(b & 1) ret = mul(ret,a);
        a = mul(a,a);
    }
    return ret;
}

int ID(int x,int y = -1){
    if(~y)return (dm[x] + 1) * 4 + dm[y];
    return dm[x];
}

void bf(){
    string s = "1";
    rep(_,1,n){
        string s1 = "";
        rep(i,0,s.length() - 1){
            if(s[i] == '1') s1 += "2";
            if(s[i] == '2') s1 += "4";
            if(s[i] == '4') s1 += "16";
            if(s[i] == '6') s1 += "64";
        }
        s = s1;
    }
    int res[M];memset(res,0,sizeof res);
    rep(i,0,s.length() - 1) res[ID(s[i] - '0')]++;
    rep(i,0,s.length() - 2) res[ID(s[i] - '0',s[i + 1] - '0')]++;
    rep(i,0,M - 6){cout << res[i] << " ";}
    puts("");
}

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int main(int argc, char** argv) {
    read(n);scanf("%s",s0);s = s0;
    //bf();
    if(s.size() > 2){
        puts("todo");
    }
    else{
        Mat m,bas;
        m.m[ID(1)][ID(4)] = m.m[ID(2)][ID(1)] = m.m[ID(4)][ID(2)] = m.m[ID(4)][ID(6)] = m.m[ID(6)][ID(4)] = m.m[ID(6)][ID(6)] = 1;
        m.m[ID(1,6)][ID(4)] = m.m[ID(2,1)][ID(1,4)] = m.m[ID(2,2)][ID(1,1)] = m.m[ID(2,4)][ID(1,2)] = m.m[ID(2,6)][ID(1,6)] = \
        m.m[ID(4,1)][ID(2,4)] = m.m[ID(4,1)][ID(6,4)] = \
        m.m[ID(4,2)][ID(2,1)] = m.m[ID(4,2)][ID(6,1)] = \
        m.m[ID(4,4)][ID(2,2)] = m.m[ID(4,4)][ID(6,2)] = \
        m.m[ID(4,6)][ID(2,6)] = m.m[ID(4,6)][ID(6,6)] = \
        m.m[ID(6,1)][ID(4,4)] = \
        m.m[ID(6,2)][ID(4,1)] = m.m[ID(6,4)][ID(6)] = m.m[ID(6,4)][ID(4,2)] = \
        m.m[ID(6,6)][ID(4,6)] = 1;
        bas.m[ID(1)][0] = 1;
        Mat res = mul(q_pow(m,n),bas);
        if(s.size() == 1) printf("%lld\n",res.m[ID(s[0] - '0')][0]);
        else printf("%lld\n",res.m[ID(s[0] - '0',s[1] - '0')][0]);
        //rep(i,0,M - 6){cout<<res.m[i][0]<<" ";}puts("");//
    }
    getchar();getchar();
    return 0;
}