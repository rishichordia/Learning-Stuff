#include <iostream>
#include <bits/stdc++.h>
#include <string>
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
 
const ll mod = 1e9+7;
const ll nmax = 2e5 + 5;
const ll cnmax = 1e5+1;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};
const char mov[4]={'R','U','L','D'};
using namespace std;
 
void solve()
{
  ll n,x;
  cin>>n>>x;
  vll price(n,0);
  vll pages(n,0);
  fo(i,n)
    cin>>price[i];
  fo(i,n)
    cin>>pages[i];

  vector<vll> dp(n,vector<ll>(n,0));
  fo(i,n)
  {
    char c;
    fo(j,n)
    {
      cin>>c;
      board[i][j]=c;
    }
  }

  dp[0][0] = 1;

  fo(i,n)
  {
    fo(j,n)
    {
      if(board[i][j]=='*')
        dp[i][j] = 0;
      else if(i>0 && j>0)
        dp[i][j] = (dp[i-1][j] + dp[i][j-1])%mod;
      else if(i>0)
        dp[i][j] = dp[i-1][j];
      else if(j>0)
        dp[i][j] = dp[i][j-1];
    }
  }
  cout<<dp[n-1][n-1]<<endl;
}
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL)  ;
    ll t = 1;
    //cin>>t;
    while(t--)
    {
      solve();
    }
  return 0;
}