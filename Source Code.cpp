#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<algorithm>
#include<windows.h>
#include<bits/stdc++.h>
#include<string>
#define letter 26
using namespace std;

class Node {
	public:
		Node *next[letter];
		bool isWord;

		Node() {
			for(int i=0; i<letter; i++) {
				next[i] = 0;
			}
			isWord = false;
		}
};
class Trie {
		Node *root;
		unsigned long long size;
		int ind;
		int S_no;
	public:
		Trie() : root(0), size(0) {}

		Trie(string str) : size(0) {
			size++;
			root = new Node();
			Node *temp = root;

			for(int i=0; i<str.length(); i++) {
				int index = str[i]-'a';
				if(temp->next[index] == 0) {
					temp->next[index] = new Node();
				}
				temp = temp->next[index];
			}
			temp->isWord = true;
		}
		void Insert_In_Trie(string str) {
			size++;
			if(root == 0) {
				root = new Node();
			}
			Node *temp = root;
			for(int i=0; i<str.length(); i++) {
				int index=0;
				if(str[i]>='a' && str[i]<='z') {
					index = str[i]-'a';
				} else if(str[i]>='A' && str[i]<='Z') {
					index = str[i]-'A';
				}
				if(temp->next[index] == 0) {
					temp->next[index] = new Node();
				}
				temp = temp->next[index];
			}
			temp->isWord = true;
		}

		unsigned long long getSize() const {
			return size;
		}

		bool case5(string str) {
			int j=0;
			int count=0;
			for(j=0; j<str.length()-1; j++) {
				if(str[j] == '*') {
					++count;
				}
				if(count==1 && str[j]=='*') {
					ind = j;
				}
			}
			if(count == 2) {
				return true;
			}
			return false;
		}
		void Search(string str, int cases) {
			int selection;
			if(root != 0) {
				int index, i=0, level=0;
				char arr[50] = {0};
				bool exist = true;
				Node *temp;
				temp = root;
				S_no = 0;

				while(1) {
					if(str[i] == '*') {
						if(case5(str)) {
							Display_Words(temp, arr, str, level, 5);
							if(S_no == 0) {
								cout<<"\nWord Not Found!\n";
							}
							return;
						}
						break;
					} else if(str[i] == '.') {
						Display_Words(temp, arr, str, level, 4);
						if(S_no == 0) {
							cout<<"\nWord Not Found!\n";
						}
						return;
					} else if(str[i] == '\0') {
						system("cls");
						cout<<"\nInvalid Format!\n";
						return;
					}
					if(str[i]>='a' && str[i]<='z') {
						arr[i] = str[i];

						if(str[i]>='a' && str[i]<='z') {
							index = str[i]-'a';
						}
						if(!temp->next[index]) {
							exist = false;
							break;
						}
						temp = temp->next[index];
						level++;
						i++;
					} else {
						system("cls");
						cout<<"\nInvalid Format\n";
						return;
					}
				}
				if(exist) {
					i++;
					if(str[i] == '\0') {
						Display_Words(temp,arr,str,level, cases);
					} else if(str[i]>='a' && str[i]<='z') {
						Display_Words(temp,arr,str,level, 3);
					}
				} else {
					cout<<"\nWord Not Found!\n";
				}
			}
		}
		void Display_Words(Node *temp, char arr[], string str, int level, int cases) {
			if(temp->isWord != false) {
				arr[level] = '\0';
				++S_no;
				if(cases == 1) {
					cout<<S_no<<".  "<<arr;
					cout<<"\t--> Level of this Word in Trie: "<<level<<endl;
				} else if(cases == 2) {
					Reverse_Display(arr, level);
				} else if(cases == 3) {
					if(cmpCase3(arr, str)) {
						cout<<S_no<<".  "<<arr;
						cout<<"\t--> Level of this Word in Trie: "<<level<<endl;
					} else {
						--S_no;
					}
				} else if(cases == 4) {
					if(cmpCase4(arr, str)) {
						cout<<S_no<<".  "<<arr;
						cout<<"\t--> Level of this Word in Trie: "<<level<<endl;
					} else {
						--S_no;
					}
				} else if(cases == 5) {
					if(cmpCase5(arr, str)) {
						cout<<S_no<<".  "<<arr;
						cout<<"\t--> Level of this Word in Trie: "<<level<<endl;
					} else {
						--S_no;
					}
				}
			}
			for(int i=0; i<letter; i++) {
				if(temp->next[i]) {
					arr[level] = i+'a';
					Display_Words(temp->next[i], arr, str, level+1, cases);
				}
			}
		}
		bool cmpCase5(string arr, string str) {
			int i,j;
			for(i = str.length()-1, j = arr.length()-1; str[i] != '*'; i--, j--) {
				if(str[i] != arr[j]) {
					return false;
				}
			}
			i--;
			for(; j>=ind; j--) {
				if(str[i] == arr[j]) {
					int k, l;
					for(k=i, l=j; str[k]!='*' && l>=ind; k--, l--) {
						if(str[k] != arr[l]) {
							break;
						}
					}
					if(str[k] == '*') {
						return true;
					}
				}
			}
			return false;
		}
		bool cmpCase4(string arr, string str) {
			if(str.length() != arr.length()) {
				return false;
			} else {
				for(int i=str.length()-1, j=arr.length()-1; str[i]!='.'; i--, j--) {
					if(str[i] != arr[j]) {
						return false;
					}
				}
				return true;
			}
		}
		bool cmpCase3(string arr, string str) {
			if(arr.length() < str.length()) {
				return false;
			}
			for(int i=str.length()-1, j=arr.length()-1; str[i]!='*'; i--, j--) {
				if(str[i] != arr[j]) {
					return false;
				}
			}
			return true;
		}
		void Reverse_Display(char arr[], int size) {
			cout<<S_no<<".  ";
			for(int i=size-1; i>=0; i--) {
				cout<<arr[i];
			}
			cout<<"\t--> Level of this Word in Trie: "<<size<<endl;
		}
//		void print()
//		{
//			char str[50] = { 0 };
//			Node *temp = root;
//			Display_Words(temp, str, "", 0, 1);
//		}
};

void Find_meaning(string word)
{
	fstream file;
    vector<string> sorteddata;
	string meaning;
    file.open("Dict2.txt", ios::in);
    if (file.is_open())
    {
        while(!file.eof())
        {
            string d;
            getline(file, d);
            sorteddata.push_back(d);
        }
        file.close();
    }
    sort(sorteddata.begin(), sorteddata.end());
    for (int i = 0; i < sorteddata.size(); i++)
    {
        if (sorteddata.at(i).find(word) != string::npos)
        {
            meaning = sorteddata.at(i).substr(sorteddata.at(i).find(" ") + 1);
			break;
        }
    }
	int selection;
	cout<<"Do you want to view the meaning of this word ?\n1 : YES\n2 : NO"<<endl;
	cin>>selection;
	if (selection == 1)
	{
		cout<<endl<<endl<<"MEANING OF THIS WORD IS : "<<endl<<endl;
		cout<<meaning<<endl;
	}
	else{
		return;
	}
}

class Words {
		Trie t1, t2;
		string str;
	public:
		void Input() {
			ifstream fin;
			fin.open("Dict.txt");

			if(fin.is_open()) {
				while(!fin.eof()) {
					fin>>str;
					t1.Insert_In_Trie(str);
					reverse(str.begin(),str.end());
					t2.Insert_In_Trie(str);
				}

				fin.close();
			} else {
				cout<<"\nError: File not found!";
			}
		}
		void Search_Word() {
			vector<string> wordlist;
			string meaning;
			while(1) {
				system("cls");
				cout<<"\n\t\t*** DICTIONARY ***";
				cout<<"\n\nTotal Number of Words in the Dictionary are: "<<t1.getSize()<<endl;
				cout<<"\n\n**************\n";
				cout<<"|             INSTRUCTIONS             |\n";
				cout<<"|**************|\n";
				cout<<"| To Exit --> Enter \"-\"                |"<<endl;
				cout<<"| Enter Only lower Case Alphabets      |"<<endl;
				cout<<"|                                      |"<<endl;
				cout<<"| Input Formats:                       |"<<endl;
				cout<<"| 1) abc*                              |"<<endl;
				cout<<"| 2) *def                              |"<<endl;
				cout<<"| 3) abc*def                           |"<<endl;
				cout<<"| 4) abc..def                          |"<<endl;
				cout<<"| 5) abc*def*ghi                       |"<<endl;
				cout<<"**************\n";
				cout<<"\nEnter Word to Search with Desired Format: ";
				cin>>str;
				meaning = str;
				if(str[0] == '-') {
					cout<<"\nThank You!"<<endl;;
					printhistory(&wordlist);
					break;
				} else if(str[0] == '*') {
					system("cls");
					cout<<endl;
					reverse(str.begin(),str.end());
					t2.Search(str, 2);
				} else {
					system("cls");
					cout<<endl;
					t1.Search(str, 1);
				}
				meaning.erase(remove(meaning.begin(), meaning.end(), '*'));
				wordlist.push_back(meaning);
				Find_meaning(meaning);
				cout<<"\n\n\n\nPress any key to continue...\n";
				getch();
			}
		}
		void printhistory(vector<string> *wordlist)
		{
			fstream file;
			file.open("searchhistory.txt", ios::out);
			if (file.is_open())
			{
				file<<"YOU SEARCHED THE WORDS IN THIS ORDER : "<<endl;
				for (int i = 0; i < wordlist->size(); i++)
				{
					file<<wordlist->at(i)<<endl;
				}
				file.close();
			}
		}
		void merge(string arr[], int l, int m, int r) {
			int n1 = m-l+1;
			int n2 = r-m;
			string L[n1], R[n2];
			for (int i = 0; i<n1; i++) {
				L[i] = arr[l+i];
			}

			for(int j=0; j<n2; j++) {
				R[j] = arr[m+1+j];
			}

			int i = 0, j = 0, k = l;

			while(i<n1 && j<n2) {
				if(L[i] <= R[j]) {
					arr[k] = L[i];
					i++;
				} else {
					arr[k] = R[j];
					j++;
				}
				k++;
			}
			while(i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
			while(j < n2) {
				arr[k] = R[j];
				j++;
				k++;
			}
		}
		void Merge_Sort(string arr[], int l, int r) {
			if(l>=r) {
				return;
			}
			int m = (l+r-1)/2;
			Merge_Sort(arr, l, m);
			Merge_Sort(arr, m+1, r);
			merge(arr, l, m, r);
		}
		void Sort() {
			int i=0;
			ifstream fin;
			int x = 0;
			string hold;
			string Input, temp;
			label:
			cout<<"\n\nEnter File Name: ";
			cin>>hold;
			fin.open(hold.c_str());
			if(!fin)
			{
				cout<<"Error ! File does not exist. Please enter a new name"<<endl;
				getch();
				goto label;
			}
			else{
				string Input;
				while(!fin.eof())
				{
					fin>>Input;
					x++;
				}
			}
			int count = x;
			string data[count];
			fin.open(hold.c_str());

			while(!fin.eof()) {
				fin>>Input;
				data[i]=Input;
				i++;
			}

			fin.close();

			Merge_Sort(data,0,count-1);

			ofstream outfile;
			outfile.open("Sorted.txt");

			for(int i=0; i<count; i++) {
				outfile<<data[i]<<endl;
			}

			cout<<"\nSorting File Alphabatically";
			int z=0;

			while(z<5) {
				Sleep(1000);
				cout<<".";
				z++;
			}
			cout<<endl<<"\nFile is now Sorted"<<endl;
			cout<<"\nPress any key to continue...\n";
			getch();
		}
};

int main() {
	system("Color 70");
	Words w;
	cout<<"\n\t\t*** DICTIONARY ***";
	w.Sort();
	w.Input();
	w.Search_Word();

	return 0;
}