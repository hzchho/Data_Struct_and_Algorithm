#include<iostream>
#include<string>
#include<random>
#include<vector> 
using namespace std;
string name[30]={"ChenYi","WangEr","ZhangSan","LiSi","WangWu","ZhaoLiuLiu",
                 "LuXiaoQi","LiuLaoBa","QinJiu","YangShiSui","XiaShiYi","HuangShiEr",
                 "TaoShiSan","LinShiSi","ChenShiWu","LiShiLu","ZhangShiQi","WangShiBa",
				 "YangDaTou","ChenShuaiShuai","MaoDaYi","MengYiEr","WuZhongYou","GanNinNiang",
				 "LiangShangPo","LuJunYi","SongJiang","GuangYU","ZhangYiDe","LiuXuanDe"};
// 创建一个随机数引擎
random_device rd;
mt19937 gen(rd());
// 创建一个整数分布，范围是 [1, 100]
uniform_int_distribution<int> intDist(1,100);
struct data{
	bool valid;
	string name;
	data():valid(1),name(""){}
};
struct Haxi{
	int size;
	data *peoplename;
	Haxi():size(0),peoplename(NULL){}
};
//获得随机数 
int getrandom(){
	int randomnum=intDist(gen);
	//cout << randomnum << endl;
	return randomnum;
}
//哈希函数：除留余数法
int getHaxi(string str,int N){
	//取姓名中的每个字的首字母在字母表上的位置相加 
	int len=str.length();
	int num=0;
	for(int i=0;i<len;i++){
		if(str[i]>='A'&&str[i]<='Z'){
			num+=str[i]-'0';
		}
	}
	return num%N;
} 
//再散列，第二个哈希函数
int getHaxi2(string str,int N){
	//取每个字母在字母表上的位置相加 
	int num=0;
	int len=str.length();
	for(int i=0;i<len;i++){
		num+=str[i]-'0';
	}
	return num%N;
} 
//方法1：
//建立哈希表	
void setHaxi(Haxi &s,string str,int N){
	if(s.size==N){
		cout << "Store Fail!" << endl;
		return;
	}
    int index=getHaxi(str,N);
    int count=0;
	while(s.peoplename[index].valid==false){
		int d=0;
		count++; 
		if(count==1){
			d=getHaxi2(str,N);
		}else{
			d=1;
		}
		index=(index+d)%N;
	}
	s.peoplename[index].name=str;
	s.peoplename[index].valid=false;
	s.size++;
}
//查找
void findindex(Haxi s,string op,int N){
	int count=0;
	int index=getHaxi(op,N);
	while(s.peoplename[index].valid==false){
		count++;
		if(s.peoplename[index].name==op){
			cout << op << "的位置在：" << index << endl;
			cout << "查找次数为：" << count << endl;
			return; 
		}
		if(count==N){
			cout << "未找到" << endl;
			return;
		}
		if(count==1){
			index=(index+getHaxi2(op,N))%N;
		}else{
			index=(index+1)%N;
		}
	}
	cout << "未找到" << endl;
}	
//计算平均值
void calculate(Haxi s,string op,int N,vector<int> &record){
	int count=0;
	int index=getHaxi(op,N);
	while(s.peoplename[index].valid==false){
		count++;
		if(s.peoplename[index].name==op){
			record.push_back(count);
			return; 
		}
		if(count==30){
			record.push_back(0);
			return;
		}
		if(count==1){
			index=(index+getHaxi2(op,N))%N;
		}else{
			index=(index+1)%N;
		}
	}
	record.push_back(0);
}
//方法2： 
//建立哈希表 
void setHaxi2(Haxi &s,string str,int N){
	if(s.size==N){
		cout << "Store Fail!" << endl;
		return;
	}
    int index=getHaxi(str,N);
	while(s.peoplename[index].valid==false){
		int d=getrandom(); 
		index=(index+d)%N;
	}
	s.peoplename[index].name=str;
	s.peoplename[index].valid=false;
	s.size++;
}
//查找 
void findindex2(Haxi s,string op,int N){
	int count=0;
	int index=getHaxi(op,N);
	while(s.peoplename[index].valid==false){
		count++;
		if(s.peoplename[index].name==op){
			cout << op << "的位置在：" << index << endl;
			cout << "查找次数为：" << count << endl;
			return; 
		}
		if(count==N){
			cout << "未找到" << endl;
			return;
		}
		index=(index+1)%N;
	}
	cout << "未找到" << endl;
}	
//计算平均值
void calculate2(Haxi s,string op,int N,vector<int> &record){
	int count=0;
	int index=getHaxi(op,N);
	while(s.peoplename[index].valid==false){
		count++;
		if(s.peoplename[index].name==op){
			record.push_back(count);
			return; 
		}
		if(count==30){
			record.push_back(30);
			return;
		}
		index=(index+1)%N;
	}
	record.push_back(30);
}
		 
int main(){
	int N=30; 
	Haxi s;
	//建立哈希表 
	cout << "请选择使用的Haxi表处理冲突" << endl;
	cout << "1.双函数" << endl;
	cout << "2.随机数" << endl; //效率有点低，未做优化措施 
	int way;
	cin >> way;
	if(way==1){
		s.peoplename=new data[N+10];
		for(int i=0;i<N;i++){
			string str=name[i];
			setHaxi(s,str,N+10);
		}
		for(int i=0;i<N+10;i++){
			cout << i << ":" << s.peoplename[i].name << endl;
		}
		//查找
		cout << "请输入你要查找的同学的姓名:" << endl; 
		string op;
		cin >> op;
		while(op!="stop"){
			findindex(s,op,N+10);
			cout << "请输入你要查找的同学的姓名:" << endl; 
			cin >> op;
		}
		vector<int> record;
		for(int i=0;i<N;i++){
			calculate(s,name[i],N+10,record);
		}
		double sum=0;
		for(int i=0;i<record.size();i++){
			sum+=record[i];
		}
		cout << "平均查找长度为" << sum/N << endl; 
	}else{
		s.peoplename=new data[N];
		for(int i=0;i<N;i++){
			string str=name[i];
			setHaxi2(s,str,N);
		}
		for(int i=0;i<N;i++){
			cout << i << ":" << s.peoplename[i].name << endl;
		}
		//查找
		cout << "请输入你要查找的同学的姓名:" << endl; 
		string op;
		cin >> op;
		while(op!="stop"){
			findindex2(s,op,N);
			cout << "请输入你要查找的同学的姓名:" << endl; 
			cin >> op;
		}
		vector<int> record;
		for(int i=0;i<N;i++){
			calculate2(s,name[i],N,record);
		}
		double sum=0;
		for(int i=0;i<record.size();i++){
			sum+=record[i];
		}
		cout << "平均查找长度为" << sum/N << endl; 
	}
	delete []s.peoplename;
}
