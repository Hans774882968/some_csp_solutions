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
#include <cassert>
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

struct Node{
    string s;int dep;
};
queue<Node> q;

struct Mat;
Mat getM();

struct Mat{
    LL m[M][M];
    Mat(){memset(m,0,sizeof m);}
};
Mat m = getM();
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

int ID(string x){
    if(x.size() > 1) return (dm[x[0] - '0'] + 1) * 4 + dm[x[1] - '0'];
    return dm[x[0] - '0'];
}

string getson(string s){
    string s1;
    rep(i,0,s.length() - 1){
        if(s[i] == '1') s1 += "2";
        if(s[i] == '2') s1 += "4";
        if(s[i] == '4') s1 += "16";
        if(s[i] == '6') s1 += "64";
    }
    return s1;
}
//暴力对拍
void bf(){
    string s1 = "1";
    rep(_,1,n) s1 = getson(s1);
    LL ans = 0;
    rep(i,0,s1.size() - s.size()) if(s1.substr(i,s.size()) == s) ans = (ans + 1) % mod;
    cout << ans << endl;
}
//生成转移矩阵
Mat getM(){
    Mat m;
    string nums = "1246";
    map<string,string> trans_map;
    rep(i,0,3){
        rep(j,-1,3){
            string tmp;
            if(~j) tmp = to_string(nums[i] - '0') + to_string(nums[j] - '0');
            else tmp = to_string(nums[i] - '0');
            trans_map[tmp] = getson(tmp);
        }
    }
    for(auto x: trans_map){
        if(x.first.size() == 1){
            rep(i,0,x.second.size() - 1)
                m.m[ID(x.second[i] - '0')][ID(x.first)] = 1;
        }
        rep(i,0,(int)(x.second.size()) - 2){
            string sub = x.second.substr(i,2);
            int idx = trans_map[to_string(x.first[0] - '0')].size();
            if(x.first.size() > 1 && i != idx - 1) continue;//x.first.size() > 1时，只有跨区间的才可行
            m.m[ID(sub)][ID(x.first)] = 1;
        }
    }
    return m;
}

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

LL calc(string s,int b){
    Mat bas;
    bas.m[ID(1)][0] = 1;
    Mat res = mul(q_pow(m,b),bas);
    if(s.size() == 1) return res.m[ID(s[0] - '0')][0];
    return res.m[ID(s[0] - '0',s[1] - '0')][0];
}

string getfa(string s){
    string fa = "";
    rep(i,0,s.size() - 1){
        if(s[i] == '2') fa += "1";
        else if(s[i] == '4') fa += "2";
        else if(s[i] == '1' && (i == s.size() - 1 || s[i + 1] == '6')) fa += "4",++i;
        else if(s[i] == '6' && (i == s.size() - 1 || s[i + 1] == '4')) fa += "6",++i;
        else return "";
    }
    return fa;
}

LL bfs(){
    LL ans = 0;
    q.push({s,n});
    while(!q.empty()){
        Node u = q.front();q.pop();
        string s0 = u.s;int dep = u.dep;
        if(s0 == "" || dep < 0) continue;
        if(s0.size() <= 2) ans = (ans + calc(s0,dep)) % mod;
        else{
            q.push({getfa(s0),dep - 1});
            if(s0[0] == '4') q.push({getfa("6" + s0),dep - 1});
            if(s0[0] == '6') q.push({getfa("1" + s0),dep - 1});
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    read(n);scanf("%s",s0);s = s0;
    printf("%lld\n",bfs());
    getchar();getchar();
    return 0;
}