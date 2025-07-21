#include<iostream>
using namespace std;
#include<vector>
#include<stack>
#include<queue>
/*����0�����1��֣��2�����ͺ���3������4������5������6������7��������8���Ϻ�9���人10
�ϲ�11������12������13������14������15������16������17������18����³ľ��19���ɶ�20
����21������22������23������24 
*/
//�ڽӶ��ر� 
struct line{
	int ivex;//�ߵĶ���1 
	int jvex; //�ߵĶ���2 
	line *ilink;//���Ӷ���1����һ����
	line *jlink;//���Ӷ���2����һ����
	int weight; 
}; 
struct graph1{
	int id;
	line* firstedge;
};
struct mymap{
	int begin;
	int end;
	int weight;
	mymap(int a,int b,int c):begin(a),end(b),weight(c){}
};
//�ڽӱ�
struct edge{
	int end;
	int weight;
	edge(int a,int b):end(a),weight(b){}
};
struct graph2{
	int id;
	vector<edge> next;
}; 
//������ȱ���
void DFS(graph1 t[],int visit[],int begin,int n){
	stack<int> store;   //ʹ��ջʵ�ַǵݹ���� 
	vector<mymap> my;    //���ڴ洢�߹�ϵ 
	store.push(begin);
	int i=1;           //������n�Ƚ�ȷ���Ƿ������ 
	cout << begin << " ";
	visit[begin]=1;  //�����һ���ڵ� 
	while(!store.empty()){
		int id=store.top();   //ȡ��ջ��Ԫ�ز�ɾ�� 
		store.pop();              
		line* e=t[id].firstedge;  //����ջ��Ԫ�ض�Ӧ��firstedge 
		int next;
		int nid=id;       //���浱ǰ�ڵ����� 
		while(e!=NULL){
			next=(e->ivex==id)?e->jvex:e->ivex;   //ȷ���뵱ǰ�ڵ���Ե���һ�ڵ����� 
			if(visit[next]==0){   //���û�з��ʹ� 
				cout << next << " ";   //��������� 
				i++;     
				visit[next]=1;
				store.push(next);       //����������Σ��������Ľڵ㲻���ٴα�����Ӱ������ 
				store.push(next);       //���ǿ��Դ���������Ľڵ��޷����˵����� 
				mymap tmpp(id,next,e->weight);
				int k=0;
				for(k=0;k<my.size();k++){
					if(my[k].begin==id&&my[k].end==next){   //���ñ�Ϊ���ʹ������mymap 
						break;
					}
				}
				if(k==my.size()){
					my.push_back(tmpp);
				}
		    	e=(e->ivex==id)?e->jlink:e->ilink;   //ȷ����һ�ڵ�
			   	id=next;
			}else{                           //����ڵ������ɣ�����Ѱ��δ�����Ľڵ� 
				e=(e->ivex==nid)?e->ilink:e->jlink;
			}
		}
		if(store.empty()&&i<n){   //����Ƿ���ͨͼ��Ѱ��Ϊ���ʵĽڵ� 
			for(int j=0;j<n;j++){
				if(visit[j]==0){
					visit[j]=1;
					cout << j << " ";
					store.push(j);
					break;
				}
			}
		}
	} 
	cout << endl << "�߼�Ϊ��" << endl;   //����߼� 
	for(int k=0;k<my.size();k++){
		cout << "(" << my[k].begin << "," << my[k].end << ") ->" << my[k].weight << endl;
	}
} 
//������ȱ���
void BFS(graph1 t[],int visit[],int begin,int n){
	queue<int> store;   //���ö��б��� 
	vector<mymap> my;
	store.push(begin);
	visit[begin]=1;
	int i=0;
	while(!store.empty()){
		int id=store.front();   //ȡ������ͷԪ�ز�ɾ�� 
		store.pop();            
		i++;                    //���� 
		cout << id << " ";
		line* e=t[id].firstedge;  //����˼·��������ȱ������� 
		while(e!=NULL){
			int next=((e->ivex==id)?e->jvex:e->ivex);   
			if(visit[next]==0){
				visit[next]=1;
				store.push(next);
				mymap tmpp(id,next,e->weight);
				int k=0;
				for(k=0;k<my.size();k++){
					if(my[k].begin==id&&my[k].end==next){
						break;
					}
				}
				if(k==my.size()){
					my.push_back(tmpp);
				}
			}
			e=((e->ivex==id)?e->ilink:e->jlink);  //�����Ƚ��к������ 
		}
		if(store.empty()&&i<n){
			for(int j=0;j<n;j++){
				if(visit[j]==0){
					visit[j]=1;
					store.push(j);
					break;
				}
			}
		}
	}
	cout << endl << "�߼�Ϊ��" << endl;
	for(int k=0;k<my.size();k++){
		cout << "(" << my[k].begin << "," << my[k].end << ") ->" << my[k].weight << endl;
	}
}
//�ǵݹ���ȱ��� 
vector<int> dfscount;  //�洢ÿ���ڵ�ĳ��ȣ�������潨��������������� 
void DFS_u(graph2 s[],int visit[],int n){
	stack<int> store;
	int id=0;
	int i=1;
	cout << id << " ";    //�����һ���ڵ� 
	dfscount.push_back(s[0].next.size());   
	visit[0]=1;
	for(id;i<n;){        //���� 
		if(s[id].next.size()){
			int j=s[id].next.size()-1;
			int count=0;
			for(j;j>=0;j--){     //�Ȱ�ͬһ��Ľڵ����ջ�� 
				if(visit[s[id].next[j].end]==0){   //���뵱ǰ�ڵ����ӵĽڵ���δ�����ĳ�Ϊ���� 
					store.push(s[id].next[j].end);
					count++;
				}
			}
			dfscount.push_back(count);  //�洢ÿ���ڵ�ĳ��� 
		}
		if(store.size()){   //�洢ͬ��ڵ��ʼ��ȱ��� 
			id=store.top();
			if(visit[id]==0){
				visit[id]=1;
				i++;
				cout << id << " ";
			}
			store.pop();
		}                    
		if(store.size()==0&&i<n){   //�������ͨͼ�ĵ����ڵ� 
			for(int k=0;k<n;k++){
				if(visit[k]==0){
					store.push(k);
					break;
				}
			}
		}
	}
}
//�������������
void DFS_tree(graph2 s[],int visit[],int num,vector<int> &store_num){
	if(visit[num]==1){
		return;
	}
	visit[num]=1;
	store_num.push_back(num);
	for(int i=0;i<s[num].next.size();i++){     //�ݹ��㷨����������ȱ�����������������д洢������������������� 
		if(visit[s[num].next[i].end]==0){
			DFS_tree(s,visit,s[num].next[i].end,store_num);
		}
	}
} 
//�������������
void BFS_tree(graph2 s[],int visit[],int num,int n){
	queue<int> store;   //ʹ�ö��� 
	store.push(num);
	vector<int> count;
	vector<int> store_num;
	visit[num]=1;
	int i=0;
	while(!store.empty()){    //�ǵݹ齨��������������� 
		int top=store.front();
		store_num.push_back(top);
		i++;
		store.pop();
		int countnum=0;
		for(int j=0;j<s[top].next.size();j++){   //��ͬ��Ԫ�ش������ 
			if(visit[s[top].next[j].end]==0){
				visit[s[top].next[j].end]=1;
				store.push(s[top].next[j].end);
				countnum++;    //�洢δ������ͬ��ڵ�ĸ��� 
			}
		}
		count.push_back(countnum);
		if(i<n&&store.empty()){
			for(int k=0;k<n;k++){
				if(visit[k]==0){
					store.push(k);
					visit[k]=1;
					break;
				}
			}
		}
	}
	int index=1;
	int sum=0;
	for(int k=0;k<store_num.size();k++){
		cout << " " <<store_num[k] ;
		for(int j=0;j<count[k];j++){
			cout << "-";      //���ýڵ�Ĵ���һ������������-" 
		}
		index--;
		sum+=count[k];
		if(index==0){        //���ò���ڵ��ӡ����л��в��� 
			cout << endl;
			index=sum;
			sum=0;
		}
	}
} 

int main(){
	int n,m;
	cout << "������ͼ�Ķ������ͱ�����" << endl;
	cin >> n >> m; //nΪ�ڵ�����mΪ����
	graph2 s[n]; 
	graph1 t[n];
	int visit[n]={0};
	for(int i=0;i<n;i++){
		s[i].id=i;
		t[i].id=i;
		t[i].firstedge=NULL;
	}
	cout << "�������֮������ӹ�ϵ:������1,����2,Ȩ�أ�" << endl;
	for(int i=0;i<m;i++){
		int in,out,length;
		cin >> in >> out >> length;
		//�������ӱ�Ľ���
		line* line1=new line;
		line1->ivex=in;
		line1->jvex=out;
		line1->weight=length;
		line1->ilink=NULL;
		line1->jlink=NULL;
		if(t[in].firstedge==NULL){
			t[in].firstedge=line1;
		}else{
			line1->ilink=t[in].firstedge;
			t[in].firstedge=line1;
		}
		
		if(t[out].firstedge==NULL){
			t[out].firstedge=line1;
		}else{
			line1->jlink=t[out].firstedge;
			t[out].firstedge=line1;
		}
		//���ӱ�Ľ��� 
		edge tmp1(out,length);
		edge tmp2(in,length);
		s[in].next.push_back(tmp1);
		s[out].next.push_back(tmp2);
	}
	cout << "��ѡ����Ҫ���еĲ�����" << endl;
	cout << "1.������ȱ������ڽӶ��ر�" << endl;
	cout << "2.������ȱ������ڽӶ��ر�" << endl;
	cout << "3.������ȱ������ǵݹ飩" << endl;
	cout << "4.�������������" << endl;
	cout << "5.�������������" << endl; 
	cout << "0.�˳�" << endl;
	int op;
	cin >> op;
	while(op){
		if(op==1){
			cout << "�����뿪ʼ�ڵ㣺" << endl;
			int begin;
			cin >> begin; 
			DFS(t,visit,begin,n);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
		}else if(op==2){
			cout << "�����뿪ʼ�ڵ㣺" << endl;
			int begin;
			cin >> begin; 
			BFS(t,visit,begin,n);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
		}else if(op==3){
			DFS_u(s,visit,n);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
			cout << endl;
		}else if(op==4){
			vector<int> store_num;
			DFS_tree(s,visit,0,store_num);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
			int sum=0;
			int index=1;
			//cout << store_num.size() << " " << dfscount.size();
			for(int k=0;k<store_num.size();k++){
				cout << " " << store_num[k];
				for(int j=0;j<dfscount[k];j++){
					cout << "-";
				}
				index--;
				sum+=dfscount[k];
				if(index==0){
					cout << endl;
					index=sum;
					sum=0;
				}
			}
			cout << endl;
		}else if(op==5){
			BFS_tree(s,visit,0,n);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
			cout << endl;
		}
		cout << endl;
		cout << "��ѡ����Ҫ���еĲ�����" << endl;
		cout << "1.������ȱ������ڽӶ��ر�" << endl;
		cout << "2.������ȱ������ڽӶ��ر�" << endl;
		cout << "3.������ȱ������ǵݹ飩" << endl;
		cout << "4.�������������" << endl;
		cout << "5.�������������" << endl; 
		cout << "0.�˳�" << endl;
		cin >> op;
	} 
}
