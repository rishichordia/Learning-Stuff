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
    ll n,t,m,temp;
    string s;
    t = 1;
    //cin>>t;
    while(t--)
    {
      cin>>n>>m;
      vll cp(m,0);
      multiset<ll> s;
      fo(i,n)
      {
        cin>>temp;
        s.insert(temp);
      }
      fo(i,m)
      {
        cin>>cp[i];
      }
      fo(i,m)
      {
        if(s.empty())
        {
          cout<<-1<<endl;
          continue;
        }
        auto x = s.lower_bound(cp[i]);
        if(x==s.begin()&&*x>cp[i])
        {
          cout<<-1<<endl;
        }
        else if(x!=s.end())
        {
          if(*x>cp[i])
          {
            --x;
          }
          cout<<*x<<endl;
          s.erase(x);
        }
        else
        {
          --x;
          cout<<*x<<endl;
          s.erase(x);
        }
      }
    }
  return 0;
}