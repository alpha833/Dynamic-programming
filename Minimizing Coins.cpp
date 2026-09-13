#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;

#define F(i, a, b) for (int i = a; i < b; i++)
#define RF(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int INF = 1e9;

/*
    Problem:
    CSES - Minimizing Coins

    Given n coin denominations and a target sum x,
    find the minimum number of coins required to make x.
    Each coin can be used unlimited times.

    Platform: CSES
    Problem: Minimizing Coins
*/

// ------------------------------------------------------------
// 1. Recursive Solution
// Time:  Exponential
// Space: O(x) recursion stack in worst case
// ------------------------------------------------------------

int recursive(int x, vi &coins)
{
    if (x == 0)
        return 0;

    if (x < 0)
        return INF;

    int ans = INF;

    for (int i = 0; i < (int)coins.size(); i++)
    {
        ans = min(ans, 1 + recursive(x - coins[i], coins));
    }

    return ans;
}

// ------------------------------------------------------------
// 2. Top-Down DP (Memoization)
// Time:  O(n * x)
// Space: O(n * x) for DP + recursion stack
//
// State:
// dp[n][x] = minimum coins needed to make x using first n coins
// ------------------------------------------------------------

int topDown(int n, int x, vi &coins, vvi &dp)
{
    if (x == 0)
        return 0;

    if (x < 0 || n == 0)
        return INF;

    if (dp[n][x] != -1)
        return dp[n][x];

    int pick = 1 + topDown(n, x - coins[n - 1], coins, dp);

    int notPick = topDown(n - 1, x, coins, dp);

    return dp[n][x] = min(pick, notPick);
}

// ------------------------------------------------------------
// 3. Bottom-Up DP (Tabulation)
// Time:  O(n * x)
// Space: O(x)
//
// dp[i] = minimum coins required to make sum i
// ------------------------------------------------------------

int bottomUp(int n, int x, vi &coins)
{
    vi dp(x + 1, INF);

    dp[0] = 0;

    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i)
            {
                dp[i] = min(dp[i],
                            dp[i - coins[j]] + 1);
            }
        }
    }

    return dp[x];
}

void solve()
{
    int n, x;
    cin >> n >> x;

    vi coins(n);

    for (int i = 0; i < n; i++)
        cin >> coins[i];

    // --------------------------------------------------------
    // Recursive
    // --------------------------------------------------------
    // int ans = recursive(x, coins);

    // --------------------------------------------------------
    // Top-Down
    // --------------------------------------------------------
    // vvi dp(n + 1, vi(x + 1, -1));
    // int ans = topDown(n, x, coins, dp);

    // --------------------------------------------------------
    // Bottom-Up
    // --------------------------------------------------------
    int ans = bottomUp(n, x, coins);

    if (ans == INF)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
}

int main()
{
    FAST_IO

    solve();

    return 0;
}
