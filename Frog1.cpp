#include <bits/stdc++.h>
using namespace std;

/*
    Frog 1 - AtCoder DP

    Problem:
    A frog is initially on stone 0.
    From stone i, it can jump to:
        1. i + 1
        2. i + 2

    Cost of jumping from stone i to stone j:
        |h[i] - h[j]|

    Find the minimum cost to reach the last stone.
*/


// ============================================================
// 1. RECURSION
// ============================================================

int recursion(int i, vector<int>& h) {

    // Base case
    if(i == 0)
        return 0;

    // Only one possible jump: 0 -> 1
    if(i == 1)
        return abs(h[1] - h[0]);

    return min(
        recursion(i - 1, h) + abs(h[i] - h[i - 1]),
        recursion(i - 2, h) + abs(h[i] - h[i - 2])
    );
}


// ============================================================
// 2. MEMOIZATION (Top-Down DP)
// ============================================================

int memoization(int i, vector<int>& h, vector<int>& dp) {

    // Base case
    if(i == 0)
        return 0;

    if(i == 1)
        return abs(h[1] - h[0]);

    // Already calculated
    if(dp[i] != -1)
        return dp[i];

    return dp[i] = min(
        memoization(i - 1, h, dp) + abs(h[i] - h[i - 1]),
        memoization(i - 2, h, dp) + abs(h[i] - h[i - 2])
    );
}


// ============================================================
// 3. TABULATION (Bottom-Up DP)
// ============================================================

int tabulation(vector<int>& h) {

    int n = h.size();

    vector<int> dp(n);

    dp[0] = 0;

    if(n >= 2)
        dp[1] = abs(h[1] - h[0]);

    for(int i = 2; i < n; i++) {

        dp[i] = min(
            dp[i - 1] + abs(h[i] - h[i - 1]),
            dp[i - 2] + abs(h[i] - h[i - 2])
        );
    }

    return dp[n - 1];
}


// ============================================================
// 4. SPACE OPTIMIZATION
// ============================================================

int spaceOptimized(vector<int>& h) {

    int n = h.size();

    if(n == 1)
        return 0;

    // prev2 = dp[i - 2]
    // prev1 = dp[i - 1]

    int prev2 = 0;
    int prev1 = abs(h[1] - h[0]);

    for(int i = 2; i < n; i++) {

        int curr = min(
            prev1 + abs(h[i] - h[i - 1]),
            prev2 + abs(h[i] - h[i - 2])
        );

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}


// ============================================================
// MAIN
// ============================================================

int main() {

    int n;
    cin >> n;

    vector<int> h(n);

    for(int i = 0; i < n; i++)
        cin >> h[i];


    // 1. Recursion
    // Time: O(2^N)
    // Space: O(N) recursion stack
    cout << "Recursion: "
         << recursion(n - 1, h) << '\n';


    // 2. Memoization
    // Time: O(N)
    // Space: O(N) DP + O(N) recursion stack
    vector<int> dp(n, -1);

    cout << "Memoization: "
         << memoization(n - 1, h, dp) << '\n';


    // 3. Tabulation
    // Time: O(N)
    // Space: O(N)
    cout << "Tabulation: "
         << tabulation(h) << '\n';


    // 4. Space Optimized
    // Time: O(N)
    // Space: O(1)
    cout << "Space Optimized: "
         << spaceOptimized(h) << '\n';

    return 0;
}
