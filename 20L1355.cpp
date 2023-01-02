#include<iostream>
#include<fstream>
#include<windows.h>//to access window library
#include<stdio.h>
#include<stdlib.h>
using namespace std;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
class Date;
class Post;
class User;
class Page;
class comment;
class Activity;
class Memory;

class helper
{
public:
	static bool Isequal(char*& arr1,char*& arr2)
	{
		//return true if index of arr1 started from 0 to '\0' equal with arr2 started from 0 to '\0'
		//else return false
		int i;
		int j=0;
		for(i=0;arr1[i]!='\0';i++,j++)
		{
			if(arr1[i]!=arr2[j])
				return false;
		}
		return true;
	}
	static int len(char*& arr)
	{
		//returns stringlen
		if(arr!=0)
		{
			int length=0;
			for(int i=0;arr[i]!='\0';i++)
			{
				if(arr[i]>=0&&arr[i]<=127)
					length++;
			}
				
			return length;
		}
		else
			return 0;
	}
	static char* getstringfrombuffer(char* arr)
	{
		if(arr!=0)
		{
			int l=len(arr)+1;
			char* newarr=new char[l];
			for(int i=0;i<l;i++)
			{
				if(i!=l-1)
				{
					if(arr[i]>=0&&arr[i]<=127)
						newarr[i]=arr[i];
				}				
				else
					newarr[i]='\0';
			}
			return newarr;
		}
		else
			return 0;
		
	}
	static void copystring(char*& arr1,char*& arr2)
	{
		//deep copies arr2 in str1 
		int l=len(arr2);
		int i;
		for(i=0;i<l;i++)
			arr1[i]=arr2[i];
		arr1[i]='\0';
	}
	static char* StringConcatenate(char* cstring1,char*& cstring2)
	{
		//a function that takes two strings inputs and appends str2 at end of str1.
		//return cstring1  
		int size1;
		if(cstring1!=0&&cstring2!=0)//if cstring1 and cstring2 both not null 
		{
			size1=len(cstring1);//size of cstring1
			int size2=size1+len(cstring2)+1;//size for new main string
			char* newstring=new char[size2];
			for(int i=0;i<size1;i++)
				newstring[i]=cstring1[i];
			int indexofcstring_2=0;
			for(int i=size1;i<size2;i++,indexofcstring_2++)
			{
				if(i==size2-1)
					newstring[i]='\0';
				else
					newstring[i]=cstring2[indexofcstring_2];
			}
			cstring1=newstring;
		}
		if(cstring1==0&&cstring2!=0)
		{
			size1=len(cstring2);
			cstring1=new char[size1+1];
			for(int x=0;x<size1+1;x++)
			{
				cstring1[x]=cstring2[x];
				if(x==size1)
					cstring1[x]='\0';
			}
		}
		return cstring1;
		//if cstring2 is 0 and cstring 1 is not null then cstring 1 will remain same
		//if both are null then also cstring1 will be returned null 
	}
};
class object
{
	char* ID;
public:
	object(object& rhs)
	{
		ID=helper::getstringfrombuffer(rhs.ID);
	}
	object()
	{
		ID=0;
	}
	bool IsPage()
	{
		if(ID[0]=='p')
			return true;
		else
			return false;
	}
	virtual void printlistview()=0;//pure virtual
	virtual void ViewTimeline()=0;//pure virtual
	virtual void SeeMemories()=0;//pure virtual
	virtual void Addpostintimeline(Post* newpost)=0;//pure virtual
	object(char*& id)
	{
		ID=helper::getstringfrombuffer(id);
	}
	virtual ~object()
	{
		if(ID!=0)
			delete[] ID;
	}
	virtual void print()//not pure virtual
	{
		cout<<ID;
	}
	bool Ismatched(object*& user)
	{
		if(helper::Isequal(ID,user->ID)==true)
			return true;
		else
			return false;
	}
	char* getid()
	{
		return ID;
	}
	void Loaddatafromfile(ifstream& fin)
	{
		char buffer[30];
		fin>>buffer;
		ID=helper::getstringfrombuffer(buffer);
	}
};
class Date
{
	int day;
	int month;
	int year;
	static Date currentdate;
public:
	static void setcurrentdate(int d,int m,int y)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"------------------------------------------------------------------------"<<endl;
		cout<<"Command: Set current System Date "<<d<<" "<<m<<" "<<y<<endl;
		cout<<"------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		cout<<endl;
		currentdate.day=d;
		currentdate.month=m;
		currentdate.year=y;
	}
	static void printcurrentdate()
	{
		cout<<currentdate.day<<"/"<<currentdate.month<<"/"<<currentdate.year;
	}
	void printdate()
	{
		cout<<"("<<day<<"/"<<month<<"/"<<year<<")";
	}
	bool IsSameExceptYear()
	{
		if(day==currentdate.day&&month==currentdate.month)
			return true;
		else
			return false;
	}
	int getyear()
	{
		return year;
	}
	bool islatestdate()
	{
		if(year==currentdate.year)
		{
			if(month==currentdate.month)
			{
				if(day==currentdate.day||day+1==currentdate.day)
					return true;
			}	
		}
		return false;
	}
	Date()
	{
		day=currentdate.day;
		month=currentdate.month;
		year=currentdate.year;
	}
	void loadDate(ifstream& fin)
	{
		fin>>day;
		fin>>month;
		fin>>year;
	}
	int yearsubtraction()
	{
		return currentdate.year-year;
	}
	~Date()
	{

	}
};
Date Date::currentdate;
class comment
{
	char* ID;
	object* commentby;
	char* text;
	static int commentidnumber;
public:
	void Loadcommentfromfile(ifstream& fin,char*& tempcommenton,char*& tempcommentby)
	{
		char buffer[100];
		fin>>buffer;
		ID=helper::getstringfrombuffer(buffer);
		fin>>buffer;
		tempcommenton=helper::getstringfrombuffer(buffer);
		fin>>buffer;
		tempcommentby=helper::getstringfrombuffer(buffer);
		fin.ignore();
		fin.getline(buffer,100);
		text=helper::getstringfrombuffer(buffer);
	}
	void setcommentby(object*& commenter)
	{
		commentby=commenter;
	}
	bool matchingcommentid(char*& arr)
	{
		//match id of this with arr and if matched then returns true else false
		if(helper::Isequal(arr,ID)==true)//calling helper func
			return true;
		else
			return false;
	}
	comment()
	{
		commentidnumber++;
		ID=0;
		commentby=0;
		text=0;
	}
	comment(object*& comment_by,char*& commenttext)
	{
		char commentidbuffer[20];
		_itoa(commentidnumber,commentidbuffer,10);
		char* id=helper::getstringfrombuffer(commentidbuffer);
		commentidnumber++;
		char* propercommentid=helper::StringConcatenate("c",id);
		ID=helper::getstringfrombuffer(propercommentid);
		delete[] id;
		delete[] propercommentid;
		commentby=comment_by;
		text=helper::getstringfrombuffer(commenttext);
	}
	~comment()
	{
		commentidnumber--;
		if(ID!=0)
			delete[] ID;
		if(text!=0)
			delete[] text;
	}
	void printcomment()
	{
		cout<<"\t\t";
		commentby->print();
		cout<<" wrote: '"<<text<<"'";
	}
};
int comment::commentidnumber=1;
class Activity
{
int type;
char* value;
public:
	Activity()
	{
		value=0;
	}
	void loadactivity(ifstream& fin)
	{
		fin>>type;
		char buffer[80];
		fin.ignore();
		fin.getline(buffer,80);
		value=helper::getstringfrombuffer(buffer);
	}
	~Activity()
	{
		if(value!=0)
			delete[] value;
	}
	void printactivity()
	{
		if(type==1)
			cout<<"feeling";
		if(type==2)
			cout<<"thinking about";
		if(type==3)
			cout<<"Making";
		if(type==4)
			cout<<"Celebrating";	
		cout<<" "<<value;
	}
};
class Post
{
protected:
	Date shareddate;
	char* id;
	char* text; 
	object* sharedby;
private:
	Activity* activityused;
	object** likedby;
	int totallikes;
	comment** comments;
	int totalcomments;
	static int Postidnumber;
public:
	bool IsDateandsharedbyCorrect(object*& user)//check whether the post's sharedby is the user which is passed by parameter
	{
		if(sharedby->Ismatched(user)==true)
		{
			if(shareddate.IsSameExceptYear()==true)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	
	void printlikedlist()
	{
		cout<<"\nPost Liked By:\n";
		if(likedby!=0)
		{
			for(int i=0;likedby[i]!=0;i++)
				likedby[i]->printlistview();		
		}
		else
			cout<<"No likes!"<<endl;
	}
	virtual void Displaypostoftimeline()
	{
		cout<<"---";
		sharedby->print();
		if(activityused!=0)
		{
			cout<<" is ";
			activityused->printactivity();
	
			if(sharedby->IsPage()==true)
			{
				cout<<". ...";
				shareddate.printdate();	
			}
			cout<<endl;
		}
		else
			cout<<" shared ";
		cout<<"'"<<text<<"'";
		if(sharedby->IsPage()==false)
		{
			cout<<"...";
			shareddate.printdate();
		}
		cout<<endl;
		if(comments!=0)
		{
			for(int i=0;comments[i]!=0;i++)
			{
				comments[i]->printcomment();
				cout<<endl;
			}
		}
	}
	bool matchingpostid(char*& arr)
	{
		//match id of this with arr and if matched then returns true else false
		if(helper::Isequal(arr,id)==true)//calling helper func
			return true;
		else
			return false;
	}
	bool islatestpost()
	{
		if(shareddate.islatestdate()==true)
			return true;
		else
			return false;
	}
	bool IsMemory()//checks whether date and month is same
	{
		if(shareddate.IsSameExceptYear()==true)
			return true;
		else
			return false;
	}
	Post(char* posttext=0,object* shared_by=0)
	{
		char* properpostid=0;
		if(posttext!=0)
		{
			char postidbuffer[20];
			_itoa(Postidnumber,postidbuffer,10);
			char* id=helper::getstringfrombuffer(postidbuffer);
			properpostid=helper::StringConcatenate("post",id);
			delete[] id;
		}
		Postidnumber++;
		if(posttext!=0)
			text=helper::getstringfrombuffer(posttext);
		else
			text=posttext;
		sharedby=shared_by;		
		id=properpostid;
		activityused=0;
		likedby=0;
		comments=0;
		totalcomments=0;
		totallikes=0;
	}
	void Loadpostfromfile(ifstream& fin)
	{
		int isactivity;
		fin>>isactivity;
		char buffer[100];
		fin>>buffer;
		id=helper::getstringfrombuffer(buffer);
		shareddate.loadDate(fin);
		fin.ignore();
		fin.getline(buffer,100);
		text=helper::getstringfrombuffer(buffer);
		if(isactivity!=1)
		{
			activityused=new Activity;
			activityused->loadactivity(fin);
		}
	}
	void printpost()
	{
		//print date text shared by activity comments in proper format
		sharedby->print();
		cout<<" ";
		if(activityused==0)
			cout<<"shared '"<<text<<"'"<<endl;
		else
		{
			cout<<"is ";
			activityused->printactivity();
			cout<<endl<<" '"<<text<<"' ...";
			shareddate.printdate();
			cout<<endl;
		}
		if(comments!=0)
		{
			for(int i=0;comments[i]!=0;i++)
			{
				comments[i]->printcomment();
				cout<<endl;
			}
		}
	}
	void addlike(object*& liked_by)
	{
		if(totallikes<10)
		{
			if(likedby!=0)
			{
				likedby[totallikes]=liked_by;
				totallikes++;
				}
				else
				{
					likedby=new object*[10];
					likedby[totallikes]=liked_by;
					totallikes++;
					for(int i=1;i<10;i++)
						likedby[i]=0;
				}			
		}
		else
			cout<<"POST CAN'T BE LIKED BY MORE THAN 10 OBJECTS,SORRY!"<<endl;
	}
	void setsharedby(object*& shared_by)
	{
		sharedby=shared_by;
	}
	void settext(char*& _text)
	{
		text=_text;
	}
	void addcomment(comment*& newcomment)
	{
		if(totalcomments<10)
		{
			if(comments==0)
			{
				comments=new comment*[10];
				comments[0]=newcomment;
				totalcomments++;			
				comments[totalcomments]=0;
				
			}
			else
			{
				comments[totalcomments]=newcomment;
				totalcomments++;
				comments[totalcomments]=0;
			}
		}
		else
			cout<<"CAN'T ADD MORE THAN 10 COMMENTS,SORRY!"<<endl;
	}
	int yearinterval()
	{
		return shareddate.yearsubtraction();
	}
	void Printpostwithoutcomments()
	{
		cout<<"---";
		sharedby->print();
		if(activityused!=0)
		{
			cout<<" is ";
			activityused->printactivity();
	
			if(sharedby->IsPage()==true)
			{
				cout<<". ...";
				shareddate.printdate();	
			}
			cout<<endl;
		}
		else
			cout<<" shared ";
		cout<<"'"<<text<<"'";
		if(sharedby->IsPage()==false)
		{
			cout<<"...";
			shareddate.printdate();
		}
		cout<<endl;
	}
	void printpostwithoutdate()
	{
		sharedby->print();
		cout<<" ";
		if(activityused==0)
			cout<<"shared '"<<text<<"'"<<endl;
		else
		{
			cout<<"is ";
			activityused->printactivity();
			cout<<endl<<" '"<<text<<"'"<<endl;
		}
		if(comments!=0)
		{
			for(int i=0;comments[i]!=0;i++)
			{
				comments[i]->printcomment();
				cout<<endl;
			}
		}
	}
	virtual ~Post()
	{
		Postidnumber--;
		if(id!=0)
			delete[] id;
		if(text!=0)
			delete[] text;
		if(likedby!=0)
			delete[] likedby;
		if(comments!=0)
		{
			for(int i=0;i<totalcomments;i++)
				delete comments[i];
			delete[] comments;
		}
		if(activityused!=0)
			delete activityused;
	}
	int Getyear()
	{
		return shareddate.getyear();
	}
};
int Post::Postidnumber=1;
class Page:public object
{
private:
	Post** Timeline;
	char* Title;
	int totalpostsintimeline;
public:
	bool pageidmatching(char*& arr)
	{
		char* id=getid();
		if(helper::Isequal(arr,id)==true)//calling helper func
			return true;
		else
			return false;
	}
	void ViewTimeline()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"------------------------------------------------------------------------"<<endl;
		cout<<"Command:                View Timeline"<<endl;
		cout<<"------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		print();
		cout<<"-  TimeLine"<<endl;
		for(int i=0;Timeline[i]!=0;i++)
		{
			Timeline[i]->Displaypostoftimeline();
			cout<<endl;
		}
	}
	void printlistview()
	{
		SetConsoleTextAttribute(h,10);
		object::print();
		cout<<"-";
		print();
		SetConsoleTextAttribute(h,15);
		cout<<endl;
	}
	void SeeMemories()
	{
		SetConsoleTextAttribute(h,115);
		cout<<"-----------------------------------------------------------------"<<endl;
		cout<<"Command: SeeYourMemories()"<<endl;
		cout<<"-----------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		for(int i=0;Timeline[i]!=0;i++)
		{
			if(Timeline[i]->IsMemory()==true)
			{
				cout<<"We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago."<<endl;
				cout<<endl<<"On this Day"<<endl;
				cout<<Timeline[i]->yearinterval();
				cout<<" Years Ago"<<endl;
				cout<<"---";
				Timeline[i]->Displaypostoftimeline();
				cout<<endl;
			}
		}
	}
	void Addpostintimeline(Post* newpost)
	{
		if(totalpostsintimeline<=19)
		{
			if(Timeline==0)
			{
				Timeline=new Post*[20];
				Timeline[totalpostsintimeline]=newpost;
				totalpostsintimeline++;
				for(int i=totalpostsintimeline;i<20;i++)
					Timeline[i]=0;
			}
			else
			{
				Timeline[totalpostsintimeline]=newpost;
				totalpostsintimeline++;
			}
		}
		else
			cout<<"No more posts can be added as there is no further space for newpost in timeline of Page."<<endl;
	}
	void Displaypage()
	{
		print();
		cout<<endl;
		for(int i=0;Timeline[i]!=0;i++)
		{
			Timeline[i]->Displaypostoftimeline();
			cout<<endl;
		}
	}
	~Page()
	{
		if(Title!=0)
			delete[] Title;
		if(Timeline!=0)
		{
			for(int i=0;i<totalpostsintimeline;i++)
				delete Timeline[i]; 
			delete[] Timeline;
		}
	}
	void showlatestposts()
	{
		if(Timeline!=0)
		{
			for(int i=0;Timeline[i]!=0;i++)
			{	
				if(Timeline[i]->islatestpost()==true)
				{
					cout<<"---";
					Timeline[i]->printpostwithoutdate();
					cout<<endl;
				}
			}
		}
	}
	Page()
	{
		totalpostsintimeline=0;
		Title=0;
		Timeline=0;
	}
	void print()//polymorphism
	{
		SetConsoleTextAttribute(h,10);
		cout<<Title;
		SetConsoleTextAttribute(h,15);
	}
	void Loaddatafromfile(ifstream& fin)
	{
		//reading and setting the pages
		object::Loaddatafromfile(fin);//calling base class function->class:object function
		fin.ignore();
		char buffer[80];	
		fin.getline(buffer,80);
		Title=helper::getstringfrombuffer(buffer);
	}
};
class Memory:public Post
{
	Post* memoryptr;//old post reference
public:
	Memory(char* postid,Post* oldpostptr,object*& shared_by):Post(postid,shared_by)
	{
		memoryptr=oldpostptr;
	}
	void Displaypostoftimeline()
	{
		cout<<"~~~";
		sharedby->print();
		cout<<" shared a memory~~~...";
		shareddate.printdate();
		cout<<endl<<"'"<<text<<"'"<<endl;

		cout<<"\t\t"<<"(";
		cout<<shareddate.getyear()-memoryptr->Getyear();//years interval
		cout<<" Years Ago)"<<endl;

		memoryptr->Printpostwithoutcomments();//call to func of base class(old post prints without comments)
	}
	~Memory()
	{

	}
};
class User:public object
{
	Post** Timeline;
	char* FirstName;
	char* LastName;
	User** FriendList;
	Page** LikedPages;
	int noofpagesliked;
	int noofaddedfriends;
	int totalpostsintimeline;
public:
	void printlistview()
	{
		SetConsoleTextAttribute(h,6);
		object::print();
		cout<<"-";
		print();
		cout<<endl;
		SetConsoleTextAttribute(h,15);
	}
	void SeeMemories()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"-------------------------------------------------------------------"<<endl;
		cout<<"Command: SeeYourMemories()"<<endl;
		cout<<"-------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		for(int i=0;Timeline[i]!=0;i++)
		{
			if(Timeline[i]->IsMemory()==true)
			{
				cout<<"We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago."<<endl;
				cout<<endl<<"On this Day"<<endl;
				cout<<Timeline[i]->yearinterval();
				cout<<" Years Ago"<<endl;
				cout<<"---";
				Timeline[i]->Displaypostoftimeline();
			}
		}
		cout<<endl;
	}
	void ViewTimeline()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"----------------------------------------------------------------"<<endl;
		cout<<"Command:                View Timeline"<<endl;
		cout<<"----------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		print();
		cout<<"-  TimeLine"<<endl;
		for(int i=0;Timeline[i]!=0;i++)
		{

			Timeline[i]->Displaypostoftimeline();				
			cout<<endl;
		}
	}
	void ViewFriendList()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"-------------------------------------------------------------------"<<endl;
		cout<<"Command:		View Friend List"<<endl;
		cout<<"-------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		print();
		cout<<"-   Friend List"<<endl;
		cout<<endl;
		if(FriendList!=0)
		{
			for(int i=0;i<noofaddedfriends;i++)
				FriendList[i]->printlistview();
		}
		else
		{
			SetConsoleTextAttribute(h,10);
			cout<<"NO friends of the user!"<<endl;
			SetConsoleTextAttribute(h,15);
		}
	}
	void ViewLikedPages()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"---------------------------------------------------------------------------"<<endl;
		cout<<"Comand:		View Liked Pages"<<endl;
		cout<<"---------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		//We have to print the title and ID of the liked pages of this
		print();
		cout<<"-   Liked Pages"<<endl;
		cout<<endl;
		if(LikedPages!=0)
		{
			for(int i=0;i<noofpagesliked;i++)
				LikedPages[i]->printlistview();
		}
		else
		{
			SetConsoleTextAttribute(h,10);
			cout<<"NO pages liked by user!"<<endl;
			SetConsoleTextAttribute(h,15);
		}
	}
	void showlatestposts()
	{
		if(Timeline!=0)
		{
			for(int i=0;Timeline[i]!=0;i++)
			{
				if(Timeline[i]->islatestpost()==true)
				{
					cout<<"---";
					Timeline[i]->printpostwithoutdate();
					cout<<endl;
				}
			}
		}
	}
	void Viewhome()
	{
		SetConsoleTextAttribute(h,112);
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"Command:                View Home"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		print();
		cout<<"-  Home Page"<<endl;
		int i;
		for(i=0;FriendList[i]!=0;i++)
			FriendList[i]->showlatestposts();
		for(i=0;LikedPages[i]!=0;i++)
			LikedPages[i]->showlatestposts();
	}
	void print()//polymorphism
	{
		SetConsoleTextAttribute(h,6);
		cout<<FirstName<<" "<<LastName;
		SetConsoleTextAttribute(h,15);
	}
	bool matchinguserid(char*& arr)
	{
		//match id of this with arr and if matched then returns true else false
		char* id=getid();
		if(helper::Isequal(arr,id)==true)//calling helper func
			return true;
		else
			return false;
	}
	//isk copy constructor k bry mai mam sy puchna h k kesy bny ga???base class ka alg or child class ka alg??
	~User()
	{
		if(FirstName!=0)
			delete[] FirstName;
		if(LastName!=0)
			delete[] LastName;
		int i;
		if(FriendList!=0)
			delete[] FriendList;
		if(LikedPages!=0)
			delete[] LikedPages;
		if(Timeline!=0)
		{
			for(i=0;i<totalpostsintimeline;i++)
				delete Timeline[i];
			delete[] Timeline;	
		}
	}
	User()
	{
		FirstName=0;
		LastName=0;
		FriendList=0;
		LikedPages=0;
		noofpagesliked=0;
		totalpostsintimeline=0;
		noofaddedfriends=0;
		Timeline=0;
	}
	void Loaddatafromfile(ifstream& fin,char**& tempfrndlist)
	{
		//reading and setting id,firstname,last name
		//reading friends in tempfrndlist
		char Buffer[80];
		object::Loaddatafromfile(fin);
		fin>>Buffer;
		FirstName=helper::getstringfrombuffer(Buffer);
		fin>>Buffer;
		LastName=helper::getstringfrombuffer(Buffer);
		fin>>Buffer;
		int i;
		if(Buffer[0]=='-')
			tempfrndlist=0;
		else
		{
			tempfrndlist=new char*[10];
			for(i=0;i<10;i++)
			{
				if(i!=0&&Buffer[0]!=45)
					fin>>Buffer;
				if(Buffer[0]!='-')
					tempfrndlist[i]=helper::getstringfrombuffer(Buffer);
				else
					tempfrndlist[i]=0;
			}
		}
	}
	void likethepage(Page*& Newpage)
	{
		if(noofpagesliked<10)
		{
			if(LikedPages==0)
			{
				LikedPages=new Page*[10];
				LikedPages[noofpagesliked]=Newpage;
				noofpagesliked++;
				for(int i=noofpagesliked;i<10;i++)
					LikedPages[i]=0;
			}
			else
			{
				LikedPages[noofpagesliked]=Newpage;
				noofpagesliked++;
			}
		}
		else
			cout<<"CAN'T LIKE another page because limit is reached,YOU HAVE LIKED TEN PAGES!"<<endl;
	}
	void addfriend(User*& Newfrnd)
	{
		if(noofaddedfriends<10)
		{
			if(FriendList==0)
			{
				FriendList=new User*[10];
				FriendList[noofaddedfriends]=Newfrnd;
				noofaddedfriends++;
				for(int i=noofaddedfriends;i<10;i++)
					FriendList[i]=0;
			}
			else
			{
				FriendList[noofaddedfriends]=Newfrnd;
				noofaddedfriends++;
			}
		}
		else
			cout<<"CAN'T add another frnd because limit is reached,YOU ALREADY HAVE TEN FRIENDS!"<<endl;
	}
	void Addpostintimeline(Post* Newpost)
	{
		if(totalpostsintimeline<20)
		{
			if(Timeline==0)
			{
				Timeline=new Post*[20];
				Timeline[totalpostsintimeline]=Newpost;
				totalpostsintimeline++;
				for(int i=totalpostsintimeline;i<20;i++)
					Timeline[i]=0;
			}
			else
			{
				Timeline[totalpostsintimeline]=Newpost;
				totalpostsintimeline++;
			}
		}
		else
			cout<<"No more posts can be added as there is no further space for newpost in timeline of user."<<endl;
	}
};
class Facebook
{
private:
	User** Users;
	Page** Pages;
	comment** comments;
	Post** posts;
	int totalposts;
	int totalcomments;
	int totalusers;
	int totalpages;
	int commentsindex;
public:
	void Sharememory(object* _sharedby,char* postid,char* text)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"Command: ShareMemory("<<postid<<",'"<<text<<"')"<<endl;
		cout<<"------------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		cout<<endl;
		Post* searchedpost=searchpostbyid(postid);
		if(searchedpost->IsDateandsharedbyCorrect(_sharedby)==true)//confirming sharedby and shareddate
		{
			Memory* ptr=new Memory(text,searchedpost,_sharedby);
			_sharedby->Addpostintimeline(ptr);
			posts[totalposts]=ptr;
			totalposts++;
		}
		else
			cout<<postid<<"can't be shared as memory."<<endl;
	}
	Post* searchpostbyid(char*& arr)
	{
		//searching the post by matching id's of posts(listofposts) with arr
		for(int i=0;i<totalposts;i++)
		{
			if(posts[i]->matchingpostid(arr)==true)//calling func of Post class 
				return posts[i];
		}
		cout<<arr<<"   Post not found!"<<endl;
		return 0;
	}
	void deallocate(char***& arr)
	{
		//deleteing the 3d char array
		if(arr!=0)
		{
			for(int i=0;i<totalusers;i++)
			{
				if(arr[i]!=0)
				{
					for(int j=0;arr[i][j]!=0;j++)
					{
						delete[] arr[i][j];
						arr[i][j]=0;
					}
					delete[] arr[i];
					arr[i]=0;
				}
			}
			delete[] arr;
			arr=0;
		}
	}
	Page* SearchPageByID(char*& arr)
	{
		for(int i=0;i<totalpages;i++)
		{
			if(Pages[i]->pageidmatching(arr)==true)//calling func of Page class 
				return Pages[i];
		}
		cout<<arr<<"  Page not found!"<<endl;
		return 0;
	}

	User* SearchUserByID(char*& arr)
	{
		//searching the user by matching id's of userslist with arr
		for(int i=0;i<totalusers;i++)
		{
			if(Users[i]->matchinguserid(arr)==true)//calling func of User class 
				return Users[i];
		}
		cout<<arr<<"  User not found!"<<endl;
		return 0;
	}
	void viewlikedlist(char* postid)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"-------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   ViewLikedList("<<postid<<")"<<endl;
		cout<<"-------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		Post* requiredpost=searchpostbyid(postid);
		requiredpost->printlikedlist();
	}
	void commentonpost(char* postid,char* commenttext,object* commentby)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"----------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   PostComment("<<postid<<","<<commenttext<<")"<<endl;
		cout<<"----------------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		cout<<endl;
		comment* newone=new comment(commentby,commenttext);
		Post* requiredpost=searchpostbyid(postid);
		requiredpost->addcomment(newone);
		commentsindex++;
		if(commentsindex<20&&comments!=0)
		{
			for(int i=commentsindex;i<20;i++)
				comments[commentsindex]=0;
		}
	}
	void likeonpost(char* postid,object* liked_by)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   LikePost("<<postid<<")"<<endl;
		cout<<"------------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		cout<<endl;
		Post* requiredpost=searchpostbyid(postid);
		requiredpost->addlike(liked_by);
	}
	comment* SearchcommentByID(char*& arr)
	{
		//searching the comment by matching id's of comments(listofcomments) with arr
		for(int i=0;i<totalcomments;i++)
		{
			if(comments[i]->matchingcommentid(arr)==true)//calling func of Comment class 
				return comments[i];
		}
		cout<<arr<<"  Comment not found!"<<endl;
		return 0;
	}
	void ViewPage(char* pageid)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"-------------------------------------------------------------------------------"<<endl;
		cout<<"Command: ViewPage("<<pageid<<")"<<endl;
		cout<<"-------------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		Page* searchedpage=SearchPageByID(pageid);
		searchedpage->Displaypage();
	}
	~Facebook()
	{
		int i;
		if(Users!=0)
		{
			for(i=0;i<totalusers;i++)
				delete Users[i];
			delete[] Users;
		}
		if(Pages!=0)
		{
			for(i=0;i<totalpages;i++)
					 delete Pages[i];
			delete[] Pages;				
		}
		if(comments!=0)
			delete[] comments;
		if(posts!=0)
			delete[] posts;
	}
	Facebook()
	{
		cout<<"\t\t\t\t\tWELCOME TO FACE BOOK\n\n";
		Users=0;
		Pages=0;
		comments=0;
		posts=0;
		totalposts=0;
		totalcomments=0;
		totalusers=0;
		totalpages=0;
		commentsindex=0;
	}
	void associatefriend(char***& tempfrndlist)
	{
		//associating the frnds by using the tempfrndlist   
		if(tempfrndlist!=0)
		{
			int j;
			for(int i=0;i<totalusers;i++)
			{
				if(tempfrndlist[i]!=0)
				{
					for(j=0;tempfrndlist[i][j]!=0;j++)			
					{
						User* Friend=SearchUserByID(tempfrndlist[i][j]);//search fun of FACEBOOK class
						Users[i]->addfriend(Friend);//user's function to add the new friend
						Friend=0;
					}
				}
			}
		}
	}
	object* searchobjectbyid(char*& id)
	{
		object* searchedobject=0;
		if(id[0]=='p')
			searchedobject=SearchPageByID(id);
		if(id[0]=='u')
			searchedobject=SearchUserByID(id);
		return searchedobject;
	}
	void LoadAllComments(char*& commentfilename)
	{
		ifstream commentfile(commentfilename);
		commentfile>>totalcomments;
		totalcomments=totalcomments+1;
		comments=new comment*[20];
		char buffer[100];
		char* tempcommentby=0;
		char* tempcommenton=0;
		Post* requiredpost=0;
		object* commentby=0;
		int i;
		for(i=0;i<totalcomments;i++)
		{
			comments[i]=new comment;
			comments[i]->Loadcommentfromfile(commentfile,tempcommenton,tempcommentby);
			commentby=searchobjectbyid(tempcommentby);
			comments[i]->setcommentby(commentby);
			commentsindex++;
			requiredpost=searchpostbyid(tempcommenton);
			requiredpost->addcomment(comments[i]);
			requiredpost=0;
			commentby=0;
		}
		for(i=commentsindex;i<20;i++)
			comments[commentsindex]=0;
		delete[] tempcommentby;
		delete[] tempcommenton;
		commentfile.close();
	}
	void LoadAllPosts(char*& postfilename)
	{
		ifstream postfile(postfilename);
		postfile>>totalposts;
		totalposts++;
		posts=new Post*[50];//50 posts in facebook at maximum
		char buffer[150];
		char* newbuffer=new char[100];
		object* sharedby=0;
		object* likedby=0;
		for(int i=0;i<totalposts;i++)
		{
			posts[i]=new Post;
			if(i==0)
			{
				for(int j=1;j<50;j++)
					posts[j]=0;
			}
			posts[i]->Loadpostfromfile(postfile);
			postfile>>buffer;
			newbuffer=helper::getstringfrombuffer(buffer);
			sharedby=searchobjectbyid(newbuffer);
			posts[i]->setsharedby(sharedby);
			sharedby->Addpostintimeline(posts[i]);
			for(int j=0;j<10;j++)
			{
				postfile>>buffer;
				if(buffer[0]==45)
					break;
				else
				{
					newbuffer=helper::getstringfrombuffer(buffer);
					likedby=searchobjectbyid(newbuffer);
					posts[i]->addlike(likedby);
					likedby=0;
				}
			}
		}
		delete[] newbuffer;
		postfile.close();
	}
	void LoadAllPages(char*& Pagefilename)
	{
		//loading all pagefile data
		ifstream Pagefile(Pagefilename);
		Pagefile>>totalpages;
		Pages=new Page*[totalpages];
		for(int i=0;i<totalpages;i++)
		{
			Pages[i]=new Page;
			Pages[i]->Loaddatafromfile(Pagefile);
		}
		Pagefile.close();
	}
	void LoadAllUsers(char*& userfilename)
	{
		//loading all user file data
		ifstream userfile(userfilename);
		char*** tempfriendlist=0;
		userfile>>totalusers;
		Users=new User*[totalusers];
		tempfriendlist=new char**[totalusers];
		char buffer[80];
		char* newbuffer=new char[80];
		for(int i=0;i<totalusers;i++)
		{
			Users[i]=new User;
			Users[i]->Loaddatafromfile(userfile,tempfriendlist[i]);
			//load liked pages of the ith user starts here 
			userfile>>buffer;
			if(buffer[0]!=45)
			{
				for(int j=0;j<10;j++)
				{				
					if(j!=0&&buffer[0]!=45)
						userfile>>buffer;
					if(buffer[0]!=45)
					{
						newbuffer=helper::getstringfrombuffer(buffer);
						Page* ptr =SearchPageByID(newbuffer);//page searching fun of FACEBOOK class
						Users[i]->likethepage(ptr);//user's function to like the new page
						delete[] newbuffer;
					}
				}
			}
			//load liked pages of the ith user ends here
		}
		associatefriend(tempfriendlist);
		deallocate(tempfriendlist);
		userfile.close();
	}
	User* SetCurrentUser(char* Arr)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                Set current user ";
		cout<<"'"<<Arr<<"'"<<endl;
		cout<<"------------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		User* Currentuser=SearchUserByID(Arr);
		if(Currentuser!=0)
		{
			cout<<endl;
			cout<<"'";
			Currentuser->print();
			cout<<"'"<<"successfully set as current user"<<endl;
			cout<<endl;
			return Currentuser;
		}
		else
		{
			SetConsoleTextAttribute(h,23);
			cout<<endl;
			cout<<"'"<<Arr<<"'"<<"not set as current user"<<endl;
			SetConsoleTextAttribute(h,15);
			cout<<endl;
			return Currentuser;
		}	
	}
	void LoadAllData(char* Pagefilename,char* Userfilename,char* Commentfilename,char* Postfilename)
	{
		LoadAllPages(Pagefilename);
		LoadAllUsers(Userfilename);
		LoadAllPosts(Postfilename);	
		LoadAllComments(Commentfilename);
	}
	void Viewpost(char* Postid)
	{
		SetConsoleTextAttribute(h,112);
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   ViewPost("<<Postid<<")"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		SetConsoleTextAttribute(h,15);
		Post* requiredpost=searchpostbyid(Postid);
		requiredpost->printpost();
	}
};
void main()
{
	{
		Facebook fb;
		Date::setcurrentdate(15,11,2017);
		cout<<"System Date:\t";
		Date::printcurrentdate();
		cout<<endl;
		cout<<endl;
		fb.LoadAllData("Project-SocialNetworkPages.txt","Project-SocialNetworkUsers.txt","Project-SocialNetworkComments.txt","Project-SocialNetworkPosts.txt");	
		User* CurrentUser= fb.SetCurrentUser("u7");
		CurrentUser->ViewFriendList();
		CurrentUser->ViewLikedPages();
		CurrentUser->Viewhome();
		CurrentUser->ViewTimeline();
		fb.viewlikedlist("post5");
		fb.likeonpost("post5",CurrentUser);
		fb.viewlikedlist("post5");
		fb.commentonpost("post4","Good Luck for your Result",CurrentUser);
		fb.Viewpost("post4");
		fb.commentonpost("post8","Thanks for the wishes",CurrentUser);
		fb.Viewpost("post8");
		CurrentUser->SeeMemories();
		fb.Sharememory(CurrentUser,"post10","Never thought I will be specialist in this field...");
		CurrentUser->ViewTimeline();
		fb.ViewPage("p1");
		system("pause");
	}
}