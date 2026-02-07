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
    ll n,m,t;
    t =1;
    cin>>t;
    while(t--)
    {
      cin>>n>>m;
      if(n==0&&m==0)
       { cout<<"YES\n";
      continue;}
      else if(n==0||m==0)
      {
        cout<<"NO\n";
        continue;}
      if(m>n)
      {
        swap(n,m);
      }
      if(2*m==n)
        cout<<"YES\n";
      else
      {
        if(2*m>n&&(2*m-n)%3==0)
        {
          if(2*n>m && (2*n-m)%3==0)
            cout<<"YES\n";
          else
            cout<<"NO\n";
        }
        else
        cout<<"NO\n";
      }
    }
    return 0;
}