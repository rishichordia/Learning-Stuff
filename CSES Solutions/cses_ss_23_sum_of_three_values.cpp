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
  ll t1;
  cin>>n>>x;
  vpll a;
  fo(i,n)
  {
    cin>>t1;
    a.pb({t1,i});
  }
  sort(a.begin(),a.end());
  ll sum =0;
  vll ans;
  bool f = 0;
  fo(i,n-2)
  {
    sum=a[i].ff;
    ll find = x-sum;
    ll l=i+1,r=n-1,temp;
    while(l<r)
    {
      temp = a[l].ff+a[r].ff;
      if(temp == find)
      {
        ans.pb(a[i].ss+1);
        ans.pb(a[l].ss+1);
        ans.pb(a[r].ss+1);
        f=1;
        break;
      }
      else if(temp>find)
      {
       r--; 
      }
      else l++;
    }
    if(f)
      break;
  }
  if(!f)
    cout<<"IMPOSSIBLE\n";
  else
  {
    sort(ans.begin(),ans.end());
    cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<endl;
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
    cout.tie(NULL)  ;
    ll t = 1;
    //cin>>t;
    while(t--)
    {
      solve();
    }
  return 0;
}