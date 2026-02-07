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

// variables used for the current problem
int n, median;
vector<int> p;
ll ans, cnt;

void solve() {
  cin >> n;
  p.resize(n);
  for (int &x : p) { cin >> x; }
  sort(p.begin(), p.end());
  median = p[n/2];
  for (const int &x : p) {
    ans += abs(median - x);  // Calculate the cost to modify the stick
                             // length
  }
  cout << ans << "\n";
  return;
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
    solve();
  return 0;
}