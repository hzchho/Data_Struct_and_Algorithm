#include<iostream>
#include<fstream>
#include<string>
#include<vector> 
using namespace std;
bool analysefile(ifstream &file,string str,vector<int> &a,int &count){
	int len1=str.length();
	string line;
	int row=1;
	while(getline(file,line)){
		bool isok=0;
		int len2=line.length();
		for(int i=0;i<len2;i++){
			int k=i;
			for(int j=0;j<len1;j++){
				if(str[j]==line[k]){
					k++;
				}else{
					break;
				}
				if(j==len1-1){
					isok=1;
					count++;
				}
			}
		}
		if(isok==1){
			a.push_back(row);
		}
		row++;
	}
	if(count==0){
		return false;
	}else{
		return true;
	}
}
int countfile(ifstream &file){
	int sum=0;
	string line;
	while(getline(file,line)){
		int len=line.length();
		for(int i=0;i<len;i++){
			if(line[i]==' '){
				continue;
			}else{
				sum++;
			}
		}
	}
	return sum;
}
void frequency(ifstream &file){
	char al[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int num[26];
	for(int i=0;i<26;i++){
		num[i]=0;
	}
	string line;
	while(getline(file,line)){
		int len=line.length();
		for(int i=0;i<len;i++){
			if(line[i]>='a' || line[i]<='z'){
				num[line[i]-'a']++;
			}else if(line[i]>='A' || line[i]<='Z'){
				num[line[i]-'A']++;
			}
		}
	}
	for(int i=0;i<26;i++){
		cout << al[i] << " : " << num[i] << endl; 
	}
}
int main(){
	ifstream ifs;
	ifs.open("file.txt");
	if(!ifs.is_open()){
		cout << "�ļ���ʧ�ܣ�" << endl;
		return 0;
	}
	cout << "�ļ��򿪳ɹ���" << endl; 
	cout << "����������ļ�����ʲô������" << endl;
	cout << "����1����ʾ���ʳ��ֵ�Ƶ��" << endl;
	cout << "����2��������µ�������ʡ�����ţ�" << endl;
	cout << "����3��������г��ֵ���ĸ��Ƶ��" << endl;
	cout << "����0���˳�" << endl;
	int op;
	cin >> op;
	while(op!=0){
		if(op==1){
			if(ifs.eof()){
				cout << "���������ݣ�" << endl;
			}else{
				cout << "������Ҫ���ҵ��ַ�����" << endl;
				string word;
				cin >> word;
				vector<int> index;
				int count=0;
				if(analysefile(ifs,word,index,count)){
					cout << word << "������һ�������ˣ�" << count << "��" << endl; 
					cout << word << "�����г��ֵ�λ����:" << endl; 
					for(int i=0;i<index.size();i++){
						cout << "��" << index[i] << "��" << endl;
					}
				}else{
					cout << word << "�������г��֣�" << endl; 
				}
				ifs.close();
			}
		}else if(op==2){
			if(ifs.eof()){
				cout << "���������ݣ�" << endl; 
			}else{
				cout << "��ƪ���¹��У�" << countfile(ifs) << "���֣�" << endl;
				ifs.close();
			} 
		}else if(op==3){
			if(ifs.eof()){
				cout << "���������ݣ�" << endl; 
			}else{
				cout << "����ÿ����ĸ���ֵ�Ƶ��Ϊ��"  << endl;
				frequency(ifs);
				ifs.close();
			}
		}
		ifs.open("file.txt");
		if(!ifs.is_open()){
			cout << "�ļ���ʧ�ܣ�" << endl;
			return 0;
		}
		cout << "����������ļ�����ʲô������" << endl;
		cout << "����1����ʾ���ʳ��ֵ�Ƶ��" << endl;
		cout << "����2��������µ�������ʡ�����ţ�" << endl;
		cout << "����3��������г��ֵ���ĸ��Ƶ��" << endl;
		cout << "����0���˳�" << endl;
		cin >> op;
	}
	cout << "��ӭ�ٴ�ʹ�ã�" << endl; 
	return 0;
} 
