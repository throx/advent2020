#include <iostream>
#include <list>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    while (!cin.eof()) {
        int l;
        cin >> l;
        
        char dash;
        cin >> dash;
        
        int h;
        cin >> h;
        
        char space;
        cin >> space;
        
        char c;
        cin >> c;
        
        char colon;
        cin >> colon;
        
        string password;
        cin >> password;
        
        cout << password << endl;
        cin.ignore();
    }
}
