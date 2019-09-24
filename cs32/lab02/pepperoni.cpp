#include <iostream>
#include <string>
using namespace std;

int main(){
	string pepp = "pepperoni ";
	string justa;
	for(int i = 0; i < 146; i++){
		if(i <= 73){
			justa = justa + pepp[i % 10];
			cout << justa << endl;
		}
		else{
			justa--;
			cout << justa << endl;
		}
	}
	return 0;
}