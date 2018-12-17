#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
int main(){

//ifstream constructor opens the fiel

ifstream inClientFile("account_ledger.txt", ios::in);

//exit program if ifstream could not open file
if (!inClientFile)
{
    cerr <<"File could not be opened" <<endl;
    exit (EXIT_FAILURE);
} //end if
string name,line,action;
string account;
string balance;
 

while(getline(inClientFile,line)){
	
	cout <<line <<endl;
	stringstream iss(line);
	getline(iss,action, ' ');
	getline(iss,name, ' ');
	getline(iss,account, ' ');
	getline(iss,balance, ' ' );

	
//	cout << action  <<endl;
//	cout << name    << endl;
//	cout << account << endl;
//	cout << balance << endl;

}

return 0;
}
                                                  
