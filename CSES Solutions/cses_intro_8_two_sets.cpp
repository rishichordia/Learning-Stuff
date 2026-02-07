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
    //cin>>t;
    while(t--)
    {
      cin>>n;
      ll sum=n*(n+1)/2;
      if(sum&1)
        {
            cout<<"NO\n";continue;
        }
      unordered_set<ll> ans;
      ll cur = 0;
      sum=sum/2;
      for(int i=n;i>0;i--)
      {
        if(cur+i<sum)
        {
            ans.insert(i);
            cur+=i;
        }
        else if(cur+i==sum)
        {
            ans.insert(i);
            break;
        }

      }
      cout<<"YES\n";
      cout<<ans.size()<<endl;
      for(auto x:ans)
        cout<<x<<" ";
      cout<<endl;
      cout<<n-ans.size()<<endl;
      for(ll i=1;i<n+1;i++)
        {
            if(ans.find(i)==ans.end())
                cout<<i<<" ";
        }
    }
    return 0;
}