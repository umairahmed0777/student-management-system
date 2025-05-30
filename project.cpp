#include<iostream>
#include <string>
#include "project.h"
using namespace std;

int max(UserManagement &M){//  Helping Func to Assign ids
	static int a=0;
	if (M.getId()>a){
		return M.getId()+1;
	}
	else 
	return a;
}
int main(){  // Main Function
	static int a=1;
	static int no_user=0;
	UserManagement* users = seeuser("user_data.bin", no_user);
 	
    // Displaying user information
    for (int i = 0; i < no_user; i++) {
        users[i].display();
    }
    delete[] users;
	int start;
	again:
	cout<<"Press (1) for sign up\nPress(2) for login\nPress (3) for exit";
	cin>>start;

	if(start==1){
	UserManagement* users = seeuser("user_data.bin", no_user);
 	int maxi=0;
    // Displaying user information
    for (int i = 0; i < no_user; i++) {
        maxi=max(users[i]);
    }
    if(maxi>0){
    	a=maxi;
    }
    else
    	a=1;
	string b,c,d,e,f;
	cout<<"Enter you name: ";
	cin>>b;
	cout<<"Enter you section: ";
	cin>>c;
	cout<<"Enter you Role: ";
	cin>>d;
	cout<<"Enter you password: ";
	cin>>e;
	cout<<"Enter you contact: ";
	cin>>f;

	UserManagement P(a,b,c,d,e,f);
	P.adduser(P,"user_data.bin");
	no_user++;
	cout<<"Successfully User Created!\n\nYour id is  "<<a<<endl;
	a++;
	goto again;
	

}	else if(start==2){
	string h,i;
	int g;
	cout<<"Enter you id: ";
	cin>>g;
	cout<<"Enter you Role: ";
	cin>>h;
	cout<<"Enter you password: ";
	cin>>i;
   	LS l1(h,g,i);
    l1.login("user_data.bin", no_user);
    	goto again;


}
else if(start==3)
	return 0;
else {
	cout<<"Wrong input";
	goto again;
	}

	

	return 0;
}

