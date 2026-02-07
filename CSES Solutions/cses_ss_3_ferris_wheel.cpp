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
    ll n,t,x;
    string s;
    t = 1;
    //cin>>t;
    while(t--)
    {
      cin>>n>>x;
      vll p(n,0);
      fo(i,n)
      {
        cin>>p[i];
      }
     sort(p.begin(),p.end());
     int i =0,j=p.size()-1;int ans =0;
     while(i<n&&i<j)
     {
        if(p[i]+p[j]<=x)
        {
          ans++;
          i++;
          j--;
        }
        else
        {
          j--;ans++;
        }
     }
     if(i==j)
        ans++;
     cout<<ans<<endl;
    }
  return 0;
}