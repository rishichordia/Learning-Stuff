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
  ll n,m;
  string f,s;
  cin>>f>>s;
  n = f.size();
  m = s.size();
  vector<vll> dp(n+1, vll(m+1,INT_MAX));
  for(int i = 0;i<=m;i++)
    dp[0][i]=i;
  for(int i=0;i<=n;i++)
    dp[i][0]=i;
  for(ll i=1;i<=n;i++)
  {
    for(ll j = 1;j<=m;j++)
    {
      if(f[i-1]!=s[j-1])
      {
        dp[i][j]=min(dp[i][j],dp[i-1][j-1]+1); //replace
        dp[i][j]=min(dp[i][j],dp[i-1][j]+1);   //remove the upper letter
        dp[i][j]=min(dp[i][j],dp[i][j-1]+1);   //insert
      }
      else
        dp[i][j] = dp[i-1][j-1];
    }
  }
  cout<<dp[n][m];
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