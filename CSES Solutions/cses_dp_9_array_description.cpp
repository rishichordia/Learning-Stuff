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
  cin>>n>>m;
  vll arr(n,0);
  fo(i,n)
    cin>>arr[i];

  vector<vll>dp(n+1,vll(m+2,0));
  for(int i =1;i<=m;i++)
    if(arr[0]==i || arr[0]==0)
      dp[1][i]=1;
  for(int i = 2;i<=n;i++)
  {
    int c = arr[i-1];
    if(c!=0)
    {
      dp[i][c]= (dp[i][c]+(dp[i-1][c]+dp[i-1][c+1]+dp[i-1][c-1])%mod)%mod;
      continue;
    }
    for(int j = 1;j<=m;j++)
    {
      dp[i][j] = (dp[i][j]+(dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1])%mod)%mod;
    }
  }
  
  ll ans=0;
  for(int i = 1;i<=m;i++)
  {
    if(arr[n-1]==i || arr[n-1]==0)
      ans = (ans + dp[n][i])%mod;
  }
  cout<<ans<<endl;
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