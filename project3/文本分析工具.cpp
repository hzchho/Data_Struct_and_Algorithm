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
		cout << "文件打开失败！" << endl;
		return 0;
	}
	cout << "文件打开成功！" << endl; 
	cout << "请问你想对文件进行什么操作：" << endl;
	cout << "输入1：显示单词出现的频率" << endl;
	cout << "输入2：求出文章的字数（省略括号）" << endl;
	cout << "输入3：求出文中出现的字母的频率" << endl;
	cout << "输入0：退出" << endl;
	int op;
	cin >> op;
	while(op!=0){
		if(op==1){
			if(ifs.eof()){
				cout << "文中无内容！" << endl;
			}else{
				cout << "请输入要查找的字符串：" << endl;
				string word;
				cin >> word;
				vector<int> index;
				int count=0;
				if(analysefile(ifs,word,index,count)){
					cout << word << "在文中一共出现了：" << count << "次" << endl; 
					cout << word << "在文中出现的位置在:" << endl; 
					for(int i=0;i<index.size();i++){
						cout << "第" << index[i] << "行" << endl;
					}
				}else{
					cout << word << "不在文中出现！" << endl; 
				}
				ifs.close();
			}
		}else if(op==2){
			if(ifs.eof()){
				cout << "文中无内容！" << endl; 
			}else{
				cout << "本篇文章共有：" << countfile(ifs) << "个字！" << endl;
				ifs.close();
			} 
		}else if(op==3){
			if(ifs.eof()){
				cout << "文中无内容！" << endl; 
			}else{
				cout << "文中每个字母出现的频率为："  << endl;
				frequency(ifs);
				ifs.close();
			}
		}
		ifs.open("file.txt");
		if(!ifs.is_open()){
			cout << "文件打开失败！" << endl;
			return 0;
		}
		cout << "请问你想对文件进行什么操作：" << endl;
		cout << "输入1：显示单词出现的频率" << endl;
		cout << "输入2：求出文章的字数（省略括号）" << endl;
		cout << "输入3：求出文中出现的字母的频率" << endl;
		cout << "输入0：退出" << endl;
		cin >> op;
	}
	cout << "欢迎再次使用！" << endl; 
	return 0;
} 
