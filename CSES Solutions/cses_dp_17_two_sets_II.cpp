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
  ll sum = (n*(n+1))/2;
  if(sum&1)
  {
    cout<<0;
    return;
  }
  ll hsum=sum/2;
  vector<vll> dp(n+1,vll(hsum+1,0));
  rep(i,1,n+1)
    dp[i][0]=1;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=hsum;j++)
    {
      if(j>=i)
        dp[i][j] = (dp[i-1][j] + dp[i-1][j-i])%mod;
      else
        dp[i][j] = dp[i-1][j];
    }
  }
  cout<<dp[n][hsum];
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
    ll t = 1;
    //cin>>t;
    while(t--)
    {
      solve();
    }
  return 0;
}