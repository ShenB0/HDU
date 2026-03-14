//断链成环+线性筛+特征+前缀和+dp预处理
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
const int INF = 1 << 30;
const double eps = 1e-7;
const int MAXI = 140;
const int N = 2e5 + 10;
const int R = 113;
int a[N], pref[N];//a[]:断链成环记录初始每个点;pref[]:对于环记录前缀和
int to[N][11];
vector<int> prime;//记录质数
vector<int> nxt(MAXI + 1, 0);//对0~MAXI快速取出小于等于i的质数
void init(){
    vector<bool> is_prime(MAXI + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXI; i++) {//线性筛
        if (is_prime[i]) {
            prime.push_back(i);
        }
        for (int p : prime) {
            if (i * p > MAXI) break;
            is_prime[i * p] = false;
            if (i % p == 0) break;
        }
    }
    int ptr = 0;
    int num = prime.size();
    for (int i = 0; i <= MAXI; i++) {//预处理nxt[]
        while (ptr + 1 < num && prime[ptr + 1] <= i) {
            ptr++;
        }
        if (prime[ptr] <= i) {
            nxt[i] = prime[ptr];
        } else {
            nxt[i] = 0;
        }
    }
}
void solve(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {//输入
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++) {//前缀和
        pref[i] = pref[i - 1] + a[i];
    }
    //初始化to数组
    for (int i = 0; i <= a[2 * n]; i++) {
        to[2 * n][i] = 2 * n;
    }
    for (int i = a[2 * n] + 1; i <= 10; i++) {
        to[2 * n][i] = 2 * n + 1;
    }
    for (int i = 2 * n - 1; i >= 1; i--) {
        for (int j = 0; j <= a[i]; j++) {
            to[i][j] = i;
        }
        for (int j = a[i] + 1; j <= 10; j++) {
            to[i][j] = to[i + 1][j];
        }
    }
    // for (int j = 0; j <= 10; j++) {
    //     int last = INF;
    //     for (int i = 2 * n; i >= 1; i--) {
    //         if (a[i] >= j) {
    //             last = i;
    //         }
    //         to[i][j] = last;
    //     }
    // }
    int ans = 0;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        cur = 0;
        int s = i, e = i + n;
        while  (s < e) {
            auto it = upper_bound(prime.begin(), prime.end(), cur);
            if (it == prime.end()) break;
            int delta = *it - cur;
            if (delta > 10) {
                break;
            }
            int next = to[s][delta];
            if (next >= e) {
                break;
            }
            cur = nxt[cur + a[next]];
            ans = max(cur, ans);
            s = next + 1;
            if (ans >= R) {
                cout << ans << "\n";
                return ;
            }
        }
        if (ans >= R) {
            cout << ans << "\n";
            return ;
        }
    }
    reverse(a + 1, a + 1 + 2 * n);
    for (int i = 1; i <= 2 * n; i++) {//前缀和
        pref[i] = pref[i - 1] + a[i];
    }
    //初始化to数组
    for (int i = 0; i <= a[2 * n]; i++) {
        to[2 * n][i] = 2 * n;
    }
    for (int i = a[2 * n] + 1; i <= 10; i++) {
        to[2 * n][i] = 2 * n + 1;
    }
    for (int i = 2 * n - 1; i >= 1; i--) {
        for (int j = 0; j <= a[i]; j++) {
            to[i][j] = i;
        }
        for (int j = a[i] + 1; j <= 10; j++) {
            to[i][j] = to[i + 1][j];
        }
    }
    cur = 0;
    for (int i = 1; i <= n; i++) {
        cur = 0;
        int s = i, e = i + n;
        while  (s < e) {
            auto it = upper_bound(prime.begin(), prime.end(), cur);
            if (it == prime.end()) break;
            int delta = *it - cur;
            if (delta > 10) {
                break;
            }
            int next = to[s][delta];
            if (next >= e) {
                break;
            }
            cur = nxt[cur + a[next]];
            ans = max(cur, ans);
            s = next + 1;
            if (ans >= R) {
                cout << ans << "\n";
                return ;
            }
        }
        if (ans >= R) {
            cout << ans << "\n";
            return ;
        }
    }
    cout << ans << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}