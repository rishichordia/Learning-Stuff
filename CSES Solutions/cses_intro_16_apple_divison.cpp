#include <bits/stdc++.h>

typedef long long int ll;
 
#define deb(x) cout << #x << " is " << x << "\n"
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << "\n"
#define fo(i,n) for(ll i=0;i<n;i++)
#define rep(i,j,n) for(ll i=j;i<n;i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector<pll>
using namespace std;
 
void solve(vector<vector<char>>& board, int row,
           vector<bool>& occupiedCol,
           vector<bool>& occupiedPrimary,
           vector<bool>& occupiedSecondary, int& ans)
{
    if (row == 8) {
        ans += 1;
        return;
    }
    for (int col = 0; col < 8; col++) {
        if (board[row][col] == '*' || occupiedCol[col]
            || occupiedPrimary[row - col + 8]
            || occupiedSecondary[row + col]) {
            continue;
        }
        occupiedCol[col] = occupiedPrimary[row - col + 8]
            = occupiedSecondary[row + col] = true;
        solve(board, row + 1, occupiedCol, occupiedPrimary,
              occupiedSecondary, ans);
        occupiedCol[col] = occupiedPrimary[row - col + 8]
            = occupiedSecondary[row + col] = false;
    }
}
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long int n,t;
    vector<vector<char>> mat(8,vector<char>(8,'.'));
    fo(i,8)
      {
        fo(j,8)
        {
          cin>>mat[i][j];
        }
      }
    vector<bool> occupiedCol(10, false),
        occupiedPrimary(20, false),
        occupiedSecondary(20, false);
 
    int ans = 0;
    solve(mat, 0, occupiedCol, occupiedPrimary,
          occupiedSecondary, ans);
    cout << ans << "\n";
}