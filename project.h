#pragma once 
#include<iostream>
#include<cstring>
#include<fstream>
#include<time.h>
#include <limits>

using namespace std;
const string ANSI_RESET = "\033[0m"; // colored notifications
const string ANSI_RED = "\033[31m";

class noti{                          //Class For Notifications
    string cname,announcement;
public:
    
    noti(){  //default constructor
        cname="";
        announcement="";

    }
    noti(string a,string b){ // parametrized constructor
        cname=a;
        announcement=b;
    }
    string getcname()const{ //getter for cname
        return cname;
    }
    string getannouncement()const{ // getter for announcement
        return announcement;
    }

 void annouce(const noti& person, const string& filename) { // File handling
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();

}
void display(string i)  { // Display Func
        if(cname==i)
        cout <<ANSI_RED<<announcement <<ANSI_RESET<< endl;

        cout << endl;
    }      
};
noti* seenoti(const string& filename, int& numUsers) { // Func to See Notifications
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    noti* users = nullptr;
    numUsers = 0;

    while (true) {
        noti person("","");
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; 
        }

        numUsers++;

        noti* temp = new noti[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}

class classjoin{ // Class for joing Class on Gcr
    string name;
    int id;
public:
    
    classjoin(){ // default constructor
        name="";
        id=0;
    }
    classjoin(string a,int b){ // parametrize constructor
        name=a;
        id=b;
    }
    string getname()const{ //getter for name
        return name;
    }

    int getid()const // getter for id
{
    return id;
}  
  void joinclass(const classjoin& person, const string& filename) { // func to join class
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();

}

 void display()  { // Display Func
        cout << "Student Name: " << name << endl;
        cout << "Id " <<id<< endl;

        cout << endl;
    }        
     
};
void removeDataById(const string& filename, int idToRemove) { //Func To remove Class
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        return;
    }

    string tempFilename = "temp.bin";
    ofstream tempFile(tempFilename, ios::binary | ios::out);
    if (!tempFile) {
        cerr << "Error: Unable to open the file " << tempFilename << " for writing." << endl;
        inFile.close();
        return;
    }

    classjoin obj;
    while (inFile.read(reinterpret_cast<char*>(&obj), sizeof(classjoin))) {
        if (obj.getid() != idToRemove) {
            tempFile.write(reinterpret_cast<const char*>(&obj), sizeof(classjoin));
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());         // Delete the original file
    rename(tempFilename.c_str(), filename.c_str()); // Rename the temporary file to the original filename
}
classjoin* seestu(const string& filename, int& numUsers) { // Func to see no. of Enrolled Students in the class
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    classjoin* users = nullptr;
    numUsers = 0;

    while (true) {
        classjoin person("",0);
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; // Reached end of file
        }

        numUsers++;

        classjoin* temp = new classjoin[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}


class grade{ // Class for Grading
    int id,marks,a_n;
public:
    
    grade(){ // Default constructor
        id=0;
        marks=0;
        a_n=0;
    }
    grade(int a,int b,int c){ // PArametrize constructor
        id=a;
        marks=b;
        a_n=c;
    }
    int getid()const{ // GEtter for id
        return id;
    }
    int getmarks()const{ // Getter for marks
        return marks;
    }
    int geta_n()const{// Getter for Get Assignment no
        return a_n;
    }
    double Average(int a){//class avg

        static double avg;
        static int count;
        double temp;
         if(a==1){    
        avg+=marks;
        count++;
    }
    else
         temp=avg/count;
    return temp;

    }
    void addgrade(const grade& person, const string& filename) { // FUnc to add Grade
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();
}

void display(int i)  { // Display func
        if(id==i){
        cout << "Assignment number ->:  " << id << endl;
        cout << "Student id ->: " <<a_n<< endl;
        cout << "marks ->:  " <<marks<< endl;

        cout << endl;}
    }        

};
grade* seegrade(const string& filename, int& numUsers) { // Func to See grades
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file "<< filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    grade* users = nullptr;
    numUsers = 0;

    while (true) {
        grade person(0, 0, 0);
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; // Reached end of file
        }

        numUsers++;

        grade* temp = new grade[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}

class answer{ // Class to Record Answer
    int stu_id,ass_no;
    string answerr;
public:
    
    answer(){ // Defualt Constructor
        stu_id=0;
        ass_no=0;
        answerr=" ";
    }
    answer(int a,int b,string c){ // parametrized Constructor
        stu_id=a;
        ass_no=b;
        answerr=c;
    }
    int getstu_id()const{ // getter for stu id
        return stu_id;
    }
    int getass_no()const{// Getter for Assignment n0
        return ass_no;
    }

    void addanswer(const answer& person, const string& filename) {
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();
}
    void displayT()  {// Display Func
        cout << "Assignment number ->:  " << stu_id << endl;
        cout << "Student id ->: " <<ass_no<< endl;
        cout << "answer ->:  " <<answerr<< endl;

        cout << endl;
    }        
};
answer* seeanswer(const string& filename, int& numUsers) {// FUnc to See anser
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    answer* users = nullptr;
    numUsers = 0;

    while (true) {
        answer person(0, 0, "");
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; 
        }

        numUsers++;

        answer* temp = new answer[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}

class Assignments{ // Class for assignments
    int A_no;
    string Topic;
    int marks;
    int due_date;
public:
    
    Assignments(){ // Default constructor
        A_no=0;
        Topic=" ";
        marks=0;
        due_date=0;

    }
    Assignments(int a,string b,int c,int d){// parametrized constructor
        A_no=a;
        Topic=b;
        marks=c;
        due_date=d;
       
    }

    int getA_no()const{ //Getter for A_no;
        return A_no;
    }
    string getTopic()const{//Getter for TOpic
        return Topic;
    }
    int getMarks()const{//Getter for Markss
        return marks;
    }
    int getDuedate()const{// getter for due date
        return due_date;
    }
     bool valid_date(int d){
        if(d<=due_date)
            return true;
        else
            return false;
    }
   void addassign(const Assignments& person, const string& filename) {
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();
}
    void display()  {//Display func
        cout << "Assignment number: " << A_no << endl;
        cout << "Topic : " <<Topic<< endl;
        cout << "Total marks: " <<marks<< endl;
        cout<<"Due Date : "<<due_date<<endl;
        cout << endl;
    }        
     
    
   
};
Assignments* seeAssign(const string& filename, int& numUsers) { // FUnc to see Assignment
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    Assignments* users = nullptr;
    numUsers = 0;

    while (true) {
        Assignments person(0, "", 0,0);
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; // Reached end of file
        }

        numUsers++;

        Assignments* temp = new Assignments[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}

class UserManagement{ // class user management
    int id;
string name;
string sec;
string role;
string password;
string contact;
public:

	UserManagement(){ // default constructor
		id=0;
		name="";
		sec="";
		role="";
		password="";
		contact="";

	}
	UserManagement(int a,string b,string c,string d,string e,string f){ // PArametrized constructor
		id=a;
		name=b;
		sec=c;
		role=d;
		password=e;
		contact=f;

	} 
    //Getters for Attributes
    int getId()const{
        return id;
    }
    string getname()const{
        return name;
    }
    string getSec()const{
        return sec;
    }
    string getRole()const{
        return role;
    }
    string getpassword()const{
        return password;
    }
    string getContact()const{
        return contact;
    }

	void adduser(const UserManagement& person, const string& filename) {// Func to Add A user
    ofstream outFile(filename, ios::binary | ios::out | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
    outFile.close();
}
 bool match(int a,string b,string c){ //Func to match strings
        if(password==b && role==c && id==a)
            return true;
        else
            return false;
    }
	

void display()  { //Display Func
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << "section: " << sec << endl;
        cout << "Role: " << role << endl;
        cout << "Password: " << password << endl;
        cout << "contact: " << contact << endl;
        cout << endl;
    }



};
UserManagement* seeuser(const string& filename, int& numUsers) { // Func to see User
    ifstream inFile(filename, ios::binary | ios::in);
    if (!inFile) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        numUsers = 0;
        return nullptr;
    }

    UserManagement* users = nullptr;
    numUsers = 0;

    while (true) {
        UserManagement person(0, "", "", "", "", "");
        inFile.read(reinterpret_cast<char*>(&person), sizeof(person));
        
        if (inFile.eof()) {
            break; // Reached end of file
        }

        numUsers++;

        UserManagement* temp = new UserManagement[numUsers];
        for (int i = 0; i < numUsers - 1; i++) {
            temp[i] = users[i];
        }
        temp[numUsers - 1] = person;

        delete[] users;
        users = temp;
    }

    inFile.close();

    return users;
}

class classmanagment { // class For Class management
    string classname, teacher, subject, description;
public:
    
    classmanagment(){ // Default constructor
        classname = " ";
        teacher = " ";
        subject = " ";
        description = " ";
    }

    classmanagment(string a, string b, string c, string d) {//Parametrize constructor
        classname = a;
        teacher = b;
        subject = c;
        description = d;
        
    }
//Getters for attributes
    string getclassname()const{
        return classname;
    }

    string getteacher()const{
        return teacher;
    }
    string getsubject()const{
        return subject;
    }
    string getdescription()const{
        return description;
    }
    //Func to ADD User
    void adduser(const classmanagment& person, const string& filename) {
        ofstream outFile(filename, ios::binary | ios::app);

        if (!outFile) {
            cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
            return;
        }

        outFile.write(reinterpret_cast<const char*>(&person), sizeof(person));
        outFile.close();
    }
//Func to Read Data
    static void readAllData(const string& filename) {
        ifstream inFile(filename, ios::binary);

        if (!inFile) {
            cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
            return;
        }

        classmanagment cls;
        while (inFile.read(reinterpret_cast<char*>(&cls), sizeof(cls))) {
            displayClassData(cls);
        }

        inFile.close();
    }
//Func TO display call data
    static void displayClassData(const classmanagment& cls) {
        cout << "Class Name: " << cls.classname << endl;
        cout << "Teacher: " << cls.teacher << endl;
        cout << "Subject: " << cls.subject << endl;
        cout << "Description: " << cls.description << endl;
        cout << "Students: ";
        
        cout << endl;
    }
};

class LS : public UserManagement, public classmanagment,public Assignments{ // Class for Login/Signup (Inherited)
     string password;
    int id;
    string role;
    bool chack = false;
public:

    LS() { // Default Constructor
        password = " ";
        id = 0;
        role = " ";
    }

    LS(string a, int b, string c) { // PArametrize Constructor
        role = a;
        id = b;
        password = c;
    }
    //Getters for Attriubutes
    string getpass()const{
        return password;
    }
    int getid()const{
        return id;
    }
    string getrole()const{
        return role;
    }
    bool getcheck()const{
        return chack;
    }
//Function To lOgin
    void login(const string& filename, int& numUsers) {
        UserManagement* users = seeuser(filename, numUsers);
        for (int i = 0; i < numUsers; i++) {
            chack = users[i].match(id, password, role);
            if(chack==true)
                break;
        }
            if (chack) {
                delete[] users;
                 static int no_user=0;

                cout << "Welcome to you !\n";
                if(role=="student"){
                    int choice;
                    G1:
                    cout<<"Enter (1) for assignments\nEnter (2) for Grades\nEnter (3) for join new class\nEnter (4) for leave class\nEnter (5) for announcements\nEnter (6) for exit\n";
                    cout<<"Enter your Choice : ";
                    cin>>choice;
                    if(choice==1){
                        Assignments* users = seeAssign("assignments.bin", no_user);
    
                            // Displaying user information
                            for (int i = 0; i < no_user; i++) {
                                users[i].display();
                            }
                        int a,d;
                        cout<<"Enter assignment number to add answer: ";
                        cin>>a;
                        string input;
                        cout<<"Enter answer(use underscore for space): ";
                        cin>>input;
                        cout<<"Enter the Date: ";
                        cin>>d;
                        bool check=false;
                        Assignments* user = seeAssign("assignments.bin", no_user);
    
                           
                            for (int i = 0; i < no_user; i++) {
                                check=user[i].valid_date(d);
                                if(check==true){
                                    answer A(a,id,input);
                                    A.addanswer(A,"answer.bin");
                                    cout<<"***Assignment Submitted Successfully!***\n";
                                    goto G1;

                            }
                                }
                        if(check==false)
                            cout<<"***Failed To Submit Assignment! Due Date is Expired.***\n";
                    }
                    else if(choice==2){
                         grade* users = seegrade("grade.bin", no_user);
    
                           
                            for (int i = 0; i < no_user; i++) {
                                users[i].display(id);
                            }
                           
                            for (int i = 0; i < no_user; i++) {
                                users[i].Average(1);

                            }
                            cout<<"Class Average : "<<users[0].Average(2)<<endl;
                            goto G1;
                    }

                    else if(choice==3){
                        classmanagment::readAllData("class_data.bin");
                        string cname,n;
                        cout<<"Enter class name: ";
                        cin>>cname;
                        cout<<"Enter your name : ";
                        cin>>n;
                        classjoin C(n,id);
                        C.joinclass(C,cname + ".bin");
                        goto G1;
                    }
                    else if(choice==4){
                        string cn;
                        cout<<"Enter class you want to leave: ";
                        cin>>cn;
                        removeDataById(cn +".bin", id);
                        goto G1;
                    }
                    else if(choice==5){
                        string c3;
                        cout<<"Enter class name: ";
                        cin>>c3;
                        noti* users = seenoti("announcement.bin", no_user);
    
                            // Displaying user information
                            for (int i = 0; i < no_user; i++) {
                                users[i].display(c3);
                            }

                            goto G1;
                    }
                    else if(choice==6){
                        return ;
                    }
                        
                    else{
                        cout<<"Wrong input!";
                        goto G1;
                    }
                }
                 else if(role=="teacher"){
                    int choice;
                    G2:
                    cout<<"Enter (1) for add assignments\nEnter (2) for add Grades\nEnter (3) for join new announcement\nEnter (4) for see class student\nEnter (5) to create class\nEnter (6) for exit\n";
                    cout<<"Enter your Choice : ";
                    cin>>choice;
                    if(choice==1){
                        int a_n,mar,date;
                        string topic;
                        cout<<"Enter assignment number: ";
                        cin>>a_n;
                        cout<<"Enter assignment topic: ";
                        cin>>topic;
                        cout<<"Enter totel marks: ";
                        cin>>mar;
                        cout<<"Enter Due Date for Assignment: ";
                        cin>>date;
                        Assignments P(a_n,topic,mar,date);
                        P.addassign(P,"assignments.bin");
                        no_user++;
                        cout<<"***Assignment Assigned Successfully!***\n";
                        goto G2;


                                        }
                    else if(choice==2){
                         answer* users = seeanswer("answer.bin", no_user);
    
                            // Displaying user information
                            for (int i = 0; i < no_user; i++) {
                                users[i].displayT();
                            }
                        int a_nn,idd,mark;

                        cout<<"Enter student id whose marks want to upload: ";
                        cin>>idd;
                        cout<<"Enter assignment number: ";
                        cin>>a_nn;
                        cout<<"Enter marks: ";
                        cin>>mark;
                        grade g(idd,mark,a_nn);
                        g.addgrade(g,"grade.bin");
                                                goto G2;


                    }
                    else if(choice==3){
                        string c1,c2;

                        cout<<" Enter class name: ";
                        cin>>c1;
                        cout<<"Enter announcement (use underscore for space): ";
                        cin>>c2;
                        noti N(c1,c2);
                        N.annouce(N,"announcement.bin");
                                                goto G2;

                    }
                    else if(choice==4){
                        string cnn;
                        cout<<"Enter class name: ";
                        cin>>cnn;
                        classjoin* users = seestu(cnn +".bin", no_user);
    
                            // Displaying user information
                            for (int i = 0; i < no_user; i++) {
                                users[i].display();
                            }
                                                    goto G2;

                    }
                    else if(choice==5){
                        string cnnn,sub;
                        cout<<"Enter class name: ";
                        cin>>cnnn;
                        cout<<"Enter course name: ";
                        cin>>sub;
                        classmanagment C1(cnnn, "Umair", sub, "Study_is_Fun");

                        C1.adduser(C1, "class_data.bin");

                        classmanagment::readAllData("class_data.bin");
                        goto G2;
                    }
                    else if(choice==6){
                        return ;
                    }
                    else{
                        cout<<"wrong input!";
                        goto G2;
                    }
                    }

                }
                else{
                    cout<<"User Not found!\n";
                    return ;
                }

                
            
        
    }
};





