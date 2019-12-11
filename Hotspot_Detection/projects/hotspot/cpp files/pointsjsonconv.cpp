#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{

    freopen("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\myapp\\static\\myapp\\inputgen.txt","r",stdin);
    freopen("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\myapp\\static\\myapp\\testin.txt","w",stdout);
    cout<<"[\n";
    string s;cin>>s;
    int n=min(500,stoi(s));
   for(int i=0;i<n;i++){
    string x;
    cin>>x;
    cout<<"\t{\n\t\t\"lat\" : "<<x<<",\n";
    cin>>x;
    cout<<"\t\t\"lng\" : "<<x<<"\n\t}";
    if(i<n-1)cout<<",\n";
    }

    cout<<"]\n";
    return 0;
}


