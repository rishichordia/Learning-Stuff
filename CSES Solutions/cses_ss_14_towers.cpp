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

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,t;
    t = 1;
    //cin>>t;
    while(t--)
    {
      cin>>n;
      vpll a;
      ll temp;
      fo(i,n)
      {
        cin>>temp;
        a.pb({temp,i});
      }
      sort(a.begin(),a.end());
      set<ll> pos;
      pos.insert(a[n-1].ss);
      ll ans =1,idx=a[n-1].ss;  
      for(ll j=n-2;j>=0;j--)
      {
        auto itr= pos.lower_bound(a[j].ss);
        if(itr==pos.begin())
        {
          ans++;
        }
        else
        {
          itr--;
          pos.erase(itr);
        }
        pos.insert(a[j].ss);
      } 
      cout<<ans<<endl; 
    }
  return 0;
}