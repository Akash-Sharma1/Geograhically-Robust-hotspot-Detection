#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{

    freopen("outputgen.txt","r",stdin);
    freopen("plotcircles.txt","w",stdout);
    cout<<"[\n";
    string s;cin>>s;
    int n=stoi(s);
   for(int i=0;i<n;i++){
    string x,y;
    cin>>x>>y;
    cout<<"\t{\n\t\t\"center\": { \"lat\": "<<x<<" , \"lng\" : "<<y<<"},\n";
    cin>>x;
    cout<<"\t\t\"population\" : "<<x<<"\n\t}";
    if(i<n-1)cout<<",\n";
    }

    cout<<"\n]\n";
    return 0;
}

