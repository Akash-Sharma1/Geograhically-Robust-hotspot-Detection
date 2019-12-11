#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{

    freopen("randompoints.txt","r",stdin);
    freopen("inpoints.txt","w",stdout);
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

//  AIzaSyBUuOtNyFrqUt5QwgwIhJPMtcaW8Hps6Tk --map api
