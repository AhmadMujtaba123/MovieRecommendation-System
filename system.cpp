#include<iostream>
#include<cmath>
#include<windows.h>
#include<iomanip>
using namespace std;

void gotoxy(short x, short y)           //definition of gotoxy function
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void display_Data(int arr[][5], int rn, int cn)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
	cout << "       item1 " << "  item2" << "  item3" << "  item4" << " item5 " << endl;
	for (int index = 0; index < rn; index++)
	{
		SetConsoleTextAttribute(h, 14);
		cout << "User" << index + 1 << "::";
		for (int index1 = 0; index1 < cn; index1++)
		{
			SetConsoleTextAttribute(h, 7);
			cout << "  " << arr[index][index1] << "    ";
		}
		cout << endl;
	}
}

void display_Data1(float arr[][5], int rn, int cn)
{
	int y=2;
	gotoxy(45,0);
	cout<<"\t\t------Similarities by User to User------"<<endl;
	gotoxy(45,1);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
	cout << "         user1  " << "  user2  " << "  user3   " << "  user4  " << " user5" << endl;
	for (int index = 0; index < rn; index++)
	{	gotoxy(45,y);
		SetConsoleTextAttribute(h, 14);
		cout << "User" << index + 1 << "::";
		for (int index1 = 0; index1 < cn; index1++)
		{
			SetConsoleTextAttribute(h, 7);
			cout << "  " <<fixed<<setprecision(2)<< arr[index][index1] << "   ";
		}
		cout << endl;
		y++;
	}
}



void geta_Row(int data[][5], int Arr[], int rn)
{
	for (int index = 0; index < 5; index++)
	{
		Arr[index] = data[rn][index];
	}
}



int Sum(int A[], int size)
{
	int sum = 0;
	for (int index = 0; index < size; index++)
	{
		sum = sum + A[index];
	}
	return sum;
}

void Product(int C[], int A[], int B[], int size)
{
	for (int index = 0; index < size; index++)
	{
		C[index] = A[index] * B[index];
	}
}

float CosineSimilarity(int A[], int B[], int size)
{
	
	int C1[5];
	int C2[5];
	int C3[5];
	Product(C1, A, B, size);
	Product(C2, A, A, size);
	Product(C3, B, B, size);

	int Sum1 = 0;
	int Sum2 = 0;
	int Sum3 = 0;
	Sum1 = Sum(C1, size);
	Sum2 = Sum(C2, size);
	Sum3 = Sum(C3, size);

	float cosine = 0;
	cosine = Sum1 / (sqrt(Sum2) * sqrt(Sum3));
	return cosine;
}

void Ratings(float r_Similarity[][5],int User_No,int &maxindex,int &maxindex1)
{
	int index1;
	float max;

	if(r_Similarity[User_No-1][0]!=1)
	max=r_Similarity[User_No-1][0];
	else
	max=r_Similarity[User_No-1][0]-0.1;
	for(int index=User_No-1;index<User_No;index++)
	{

		for(index1=0;index1<5;index1++)
		{

			if(max<r_Similarity[index][index1]&&r_Similarity[index][index1]!=1)
			{
				max=r_Similarity[index][index1];
				maxindex=index1;
			}

		}
	}
	maxindex=maxindex+1;

	float max1;
	;
	if(r_Similarity[User_No-1][0]!=1)
	max1=r_Similarity[User_No-1][0];
	else
	max1=r_Similarity[User_No-1][0]-0.1;

	for(int index2=User_No-1;index2<User_No;index2++)
	{
		for(int index3=0;index3<5;index3++)
		{

			if(index3!=index1&&max>r_Similarity[index2][index3]&&r_Similarity[index2][index3]!=1)
			{
				max1=r_Similarity[index2][index3];
				maxindex1=index3;
			}
		}
	}
	maxindex1=maxindex1+1;
}

int search_item(int data[5][5],int item,int &maxindex,int &maxindex1)
{
	int s1;
	int s2;
	int sum;
	int avg;

		s1=data[maxindex-1][item-1];

		s2=data[maxindex1-1][item-1];


	sum=s1+s2;
	avg=sum/2;
	return avg;
}
int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int data[5][5] ={{2,3,1,1,2},
					{1,4,2,3,2},
					{5,3,1,4,2},
					{4,2,0,3,1},
					{5,5,3,2,1}};
	int A_r[5];
	int B_r[5];
	int A_c[5];
	int B_c[5];
	int rows = 5;
	int columns = 5;
	float r_Similarity[5][5];
	float c_Similarity[5][5];
	int user_no=4;
	int item_no=3;
	int max;
	int max1;
	int avg;
	
	cout<<"\t------Ratings------"<<endl;
	display_Data(data, 5, 5);

		for(int index=0;index<5;index++)
		{
			geta_Row(data, A_r, index);
			for (int index1 = 0; index1 < 5; index1++)
			{ 
				geta_Row(data, B_r, index1);                             //get a row functon
				r_Similarity[index][index1] = CosineSimilarity(A_r, B_r, 5);    //Making Similarity Array
			}
			cout << endl;
		}

	display_Data1(r_Similarity,5,5);               //Display Data function
	SetConsoleTextAttribute(h, 11);
	cout<<"We are rating user's 4 item no 3."<<endl;
	SetConsoleTextAttribute(h, 14);
	cout<<"User No:";
	SetConsoleTextAttribute(h, 7);
	cout<<user_no<<endl;
	SetConsoleTextAttribute(h, 14);
	cout<<"Item No:";
	SetConsoleTextAttribute(h, 7);
	cout<<item_no<<endl;
	Ratings(r_Similarity,user_no,max,max1);        //Finding most closer 2 similar users to current user.
	cout<<"Nearest User's:"<<max<<" ";
	cout<<max1<<endl;
	avg=search_item(data,item_no,max,max1);      //Searching items already rated by Maximum Similar Users
	SetConsoleTextAttribute(h, 11);
	cout<<"New Rating of User "<<user_no<<" of item "<<item_no<<" is:";
	SetConsoleTextAttribute(h, 7);
	cout<<avg;                                  //Rating of Current User

}
