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
  ll n;
  cin>>n;
  vector<ll> arr(n,0);
  fo(i,n)
    cin>>arr[i];
  
  vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(n,vector<ll>(2,0)));
  for(ll i=0;i<n;i++)
  {
    dp[i][i][0] = arr[i];
    dp[i][i][1] = 0;
    if(i<n-1)
    {
      dp[i][i+1][0] = max(arr[i],arr[i+1]);
      dp[i][i+1][1] = min(arr[i],arr[i+1]);
    }
  }
  for(int sz = 3;sz<=n;sz++)
  {
    for(int i =0;i+sz-1<n;i++)
    {
      ll j = i+sz-1;
      if(arr[i]+dp[i+1][j][1]>arr[j]+dp[i][j-1][1])
      {
        dp[i][j][0] = arr[i]+dp[i+1][j][1];
        dp[i][j][1] = dp[i+1][j][0];
      }
      else
      {
        dp[i][j][0] = arr[j]+dp[i][j-1][1];
        dp[i][j][1] = dp[i][j-1][0];
      }
    }
  }
  cout<<dp[0][n-1][0];
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