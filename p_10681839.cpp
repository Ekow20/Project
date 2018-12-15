#include<iostream>
#include<fstream>
#include<iomanip>
 
using namespace std;
 
 
 
class student
{
	int IndexNo;
	char name[50];
	int ComSci,Stats,Algebra,VecMec,Physics ;
	double Percentage;
	char grade;
	void calculate();	
public:
	void getdata();		
	void showdata() const;	
	int getIDNum() const;
}; 

class staff
{
	int StaffID;
	char name[50];
	string Address;
	string Department;
	string Subject;	
public:
    void getdata();
	void showdata() const;
	int getStaffID() const;	
};

 
 
void student::calculate()
{
	Percentage=(ComSci+Stats+Algebra+VecMec+Physics)/5.0;
	if(Percentage>=80)
		grade='A';
	else if(Percentage>=70)
		grade='B';
	else if(Percentage>=60)
		grade='C';
	else if(Percentage>=50)
		grade='D';
	else if(Percentage>=40)
		grade='E';
	else 
		grade='F';
	
}
 
void student::getdata()
{
	cout<<"\nEnter The Index number of the student ";
	cin>>IndexNo;
	cout<<"\n\nEnter student's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter the score for Computer Science: ";
	cin>>ComSci;
	cout<<"\nEnter the score for Statistics: ";
	cin>>Stats;
	cout<<"\nEnter the score for Algebra: ";
	cin>>Algebra;
	cout<<"\nEnter the score for Vectors & Mechanics: ";
	cin>>VecMec;
	cout<<"\nEnter the score for Physics: ";
	cin>>Physics;
	calculate();
}

void staff::getdata()
{
	cout<<"\nPlease enter Staff ID: ";
	cin>>StaffID;
	cout<<"\n\nPlease enter Staff's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nPlease enter Staff address: ";
	cin>>Address;
	cout<<"\nPlease enter Departmaent of Staff: ";
	cin>>Department;
	cout<<"\nPlease Enter lecture Subject: ";
	cin>>Subject;
} 
 
void student::showdata() const
{
	cout<<"\nID Number: "<<IndexNo;
	cout<<"\nName: "<<name;
	cout<<"\nComputer Science: "<<ComSci;
	cout<<"\nStatistics: "<<Stats;
	cout<<"\nAlgebra: "<<Algebra;
	cout<<"\nVectors and Mechanics: "<<VecMec;
	cout<<"\nPhysics: "<<Physics;
	cout<<"\nOverall Percentage: "<<Percentage;
	cout<<"\nGrade: "<<grade;
}
 
void staff::showdata() const
{
	cout<<"\nStaff's ID: "<<StaffID;
	cout<<"\nStaff's Name: "<<name;
	cout<<"\nStaff's Address: "<<Address;
	cout<<"\nStaff's Department: "<<Department;
	cout<<"\nStaff's Subject: "<<Subject;
}
 
int  student::getIDNum() const
{
	return IndexNo;
}
 
int staff::getStaffID() const
{
	return StaffID;
 } 
  
 
void Input_student()
{
	student studentObj;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	studentObj.getdata();
	outFile.write(reinterpret_cast<char *> (&studentObj), sizeof(student));
	outFile.close();
   	cout<<"\n\nStudent record has been added ....Press Enter";
	cin.ignore();
	cin.get();
}
 
void Input_staff()
{
	staff staffObj;
	ofstream outputFile;
	outputFile.open("staff.dat",ios::binary|ios::app);
	staffObj.getdata();
	outputFile.write(reinterpret_cast<char *> (&staffObj), sizeof(staff));
	outputFile.close();
   	cout<<"\n\nStaff Information has been added....Press Enter ";
	cin.ignore();
	cin.get(); 
 
}
 
 
 
void Search_student(int id)
{
	student studentObj;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Please the file could not be open ... Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&studentObj), sizeof(student)))
	{
		if(studentObj.getIDNum()==id)
		{
	  		 studentObj.showdata();
	  		 cout<<"\n\tPress Enter to continue";
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
	cout<<"\n\nDoes not exist....Try again";
	cin.ignore();
	cin.get();
}
 
 
void modify_student(int id)
{
	bool found=false;
	student studentObj;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Please the file could not be open ... Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&studentObj), sizeof(student));
		if(studentObj.getIDNum()==id)
		{
			studentObj.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			studentObj.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(studentObj));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&studentObj), sizeof(student));
		    	cout<<"\n\n\t Student Information has bee modified";
		    	cout<<"\n\tPress Enter to continue";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Sorry, such a record does not Exist ";
	cin.ignore();
	cin.get();
}

void modify_staff(int id)
{
	bool found=false;
	staff staffObj;
	fstream FileIO;
	FileIO.open("staff.dat",ios::binary|ios::in|ios::out);
	if(!FileIO)
	{
		cout<<"Please the file could not be open ... Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!FileIO.eof() && found==false)
	{
 
		FileIO.read(reinterpret_cast<char *> (&staffObj), sizeof(staff));
		if(staffObj.getStaffID()==id)
		{
			staffObj.showdata();
			cout<<"\n\nPlease Enter The New Details of staff"<<endl;
			staffObj.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(staffObj));
		    	FileIO.seekp(pos,ios::cur);
		    	FileIO.write(reinterpret_cast<char *> (&staffObj), sizeof(staff));
		    	cout<<"\n\n\t Staff Information has bee modified";
		    	cout<<"\n\tPress Enter to continue";
		    	found=true;
		}
	}
	FileIO.close();
	if(found==false)
	cout<<"\n\n Sorry, such staff information does not Exist ";
	cin.ignore();
	cin.get();
} 
 
 
void delete_student(int n)
{
	student studentObj;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Please the file could not be open ... Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&studentObj), sizeof(student)))
	{
		if(studentObj.getIDNum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&studentObj), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
 
 
void delete_staff(int x)
{
	staff staffObj;
	ifstream FileIn;
	FileIn.open("staff.dat",ios::binary);
	if(!FileIn)
	{
		cout<<"Please the file could not be open ... Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream FileOut;
	FileOut.open("Temp2.dat",ios::out);
	FileIn.seekg(0,ios::beg);
	while(FileIn.read(reinterpret_cast<char *> (&staffObj), sizeof(staff)))
	{
		if(staffObj.getStaffID()!=x)
		{
			FileOut.write(reinterpret_cast<char *> (&staffObj), sizeof(staff));
		}
	}
	FileOut.close();
	FileIn.close();
	remove("staff.dat");
	rename("Temp2.dat","staff.dat");
	cout<<"\n\n\tStaff Information Deleted ..";
	cin.ignore();
	cin.get();
}
 
    void MainMenu (){
  char Option;
  cout<<"#######################################################################"<<endl;
  cout<<endl;
  cout<<"\t\t COMPSA SCHOOL MANAGEMENT SYSTEM"<<endl;
  cout<<endl;
  cout<<"#######################################################################"<<endl;
  cout<<endl;
  
  cout<<" Please select an Option (eg 1)\n\n";
  cout<<"\t1. STUDENT MANAGEMENT\n";
  cout<<"\t2. STAFF MANAGEMENT\n"; 	
  cout<<"\t3. EXIT PROGRAM\n\n";
  cin>>Option;
  
  switch(Option){
  	
  	case '1':
{		    		
  	char Op;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
	system("cls");
	cout<<"\t\tSTUDENT MANAGEMENT\n\n";
    cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
	cout<<"\n\n\t1. ADD STUDENT RECORD";
	cout<<"\n\t2. SEARCH AND DISPLAY STUDENT RECORD ";
	cout<<"\n\t3. EDIT STUDENT RECORD";
	cout<<"\n\t4. DELETE STUDENT RECORD";
	cout<<"\n\t5. GO BACK\n\n";
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
	cout<<"\n\nPlease Input your Option (eg 2): ";
	cin>>Op;
	system("cls");
	switch(Op)
	{
	case '1':
		Input_student(); 
		break;
	
	case '2':	
	  cout<<"\n\n\tPlease Enter Student's Index number: ";
	   cin>>num;
	   Search_student(num); break;
	case '3':
		cout<<"\n\n\tPlease Enter Student's Index number: "; 
		cin>>num;
		modify_student(num);break;
	case '4':	
	    cout<<"\n\n\tPlease Enter Student's Index number: "; 
		cin>>num;
		delete_student(num);
		break;
	case '5':	
	    MainMenu();
	default:	cout<<"\a"; 
		
    }
	}while(Op!='5');
 
		
}

  	case '2':
{
	char Op;
	int num2;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
	system("cls");
	cout<<"\t\tSTAFF MANAGEMENT\n\n";
    cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
	cout<<"\n\n\t1. ADD STAFF INFORMATION";
	cout<<"\n\t2. EDIT STAFF INFORMATION";
	cout<<"\n\t3. DELETE STAFF INNFORMATION";
	cout<<"\n\t4. GO BACK\n\n";
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
	cout<<"\n\nPlease Input your Option (eg 1): ";
	cin>>Op;
	system("cls");
	switch(Op)
	{
	case '1':
		Input_staff();
		break;
	
	case '2':	
	  cout<<"\n\n\tPlease Enter Staff ID number: ";
	   cin>>num2;
	   modify_staff(num2);
	   break;
	case '3':
		cout<<"\n\n\tPlease Enter Staff's ID number: "; 
		cin>>num2;
		delete_staff(num2);
		break;
	
	case '4':
	    MainMenu();	
	    break;
	default:	cout<<"\a"; 
		
    }
	}while(Op!='4');
 
		
		  }  		
	
      	  
	case '3': 
	  exit(0);
	
	default :
	 cout<<"Sorry, Invalid Option";	
  	 break;
  }
	}
 
 
int main()
{
	
  	MainMenu();
  	return 0;
	
	
	
}
