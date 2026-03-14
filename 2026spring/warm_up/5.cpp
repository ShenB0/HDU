#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
const ll INF = 1LL << 60;
const double eps = 1e-7;
const int N =  1e5 + 10;
const int MAXK = 25 + 5;
int a[N];
ll pref[N], dp[N][MAXK];
void solve(){
    int n, k, m;
    cin >> n >> k >> m;
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i -1] + a[i];
    }
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {//向未来递推
        for (int j = 0; j <= k; j++) {
            if (dp[i][j] == -INF) continue;//如果是非法状态，跳过
            if (j == 0) {
                dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + a[i + 1]);//普通下一步
                dp[i + 1][k] = max(dp[i + 1][k], dp[i][0] + 2LL * a[i + 1]);//时空跳跃
            } else {
                dp[i + 1][j - 1] = max(dp[i + 1][j - 1], dp[i][j] + a[i + 1] / 2);//被时空跳跃影响
            }
            int ni = min(i + m + 1, n);//时空跳跃
            int nj = max(0, j - (ni - i));
            ll sum = pref[ni] - pref[i];//区间和
            dp[ni][nj] = max(dp[ni][nj], dp[i][j] + sum);
        }
    }
    cout << *max_element(dp[n], dp[n] + k + 1) << "\n";//取最值
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}