#include<iostream>
using namespace std;
#include<vector>
#include<stack>
#include<queue>
/*北京0，天津1，郑州2，呼和浩特3，徐州4，沈阳5，大连6，长春7，哈尔滨8，上海9，武汉10
南昌11，福州12，株洲13，广州14，深圳15，西安16，兰州17，西宁18，乌鲁木齐19，成都20
昆明21，贵阳22，柳州23，南宁24 
*/
//邻接多重表 
struct line{
	int ivex;//边的顶点1 
	int jvex; //边的顶点2 
	line *ilink;//连接顶点1的下一条边
	line *jlink;//连接顶点2的下一条边
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
//邻接表
struct edge{
	int end;
	int weight;
	edge(int a,int b):end(a),weight(b){}
};
struct graph2{
	int id;
	vector<edge> next;
}; 
//深度优先遍历
void DFS(graph1 t[],int visit[],int begin,int n){
	stack<int> store;   //使用栈实现非递归遍历 
	vector<mymap> my;    //用于存储边关系 
	store.push(begin);
	int i=1;           //用来与n比较确定是否遍历完 
	cout << begin << " ";
	visit[begin]=1;  //输出第一个节点 
	while(!store.empty()){
		int id=store.top();   //取出栈顶元素并删除 
		store.pop();              
		line* e=t[id].firstedge;  //定义栈顶元素对应的firstedge 
		int next;
		int nid=id;       //保存当前节点数据 
		while(e!=NULL){
			next=(e->ivex==id)?e->jvex:e->ivex;   //确定与当前节点相对的下一节点数据 
			if(visit[next]==0){   //如果没有访问过 
				cout << next << " ";   //输出，访问 
				i++;     
				visit[next]=1;
				store.push(next);       //这里插入两次，遍历过的节点不会再次遍历不影响结果， 
				store.push(next);       //但是可以处理遍历过的节点无法回退的问题 
				mymap tmpp(id,next,e->weight);
				int k=0;
				for(k=0;k<my.size();k++){
					if(my[k].begin==id&&my[k].end==next){   //当该边为访问过则加入mymap 
						break;
					}
				}
				if(k==my.size()){
					my.push_back(tmpp);
				}
		    	e=(e->ivex==id)?e->jlink:e->ilink;   //确定下一节点
			   	id=next;
			}else{                           //后面节点遍历完成，横向寻找未遍历的节点 
				e=(e->ivex==nid)?e->ilink:e->jlink;
			}
		}
		if(store.empty()&&i<n){   //如果是非连通图，寻找为访问的节点 
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
	cout << endl << "边集为：" << endl;   //输出边集 
	for(int k=0;k<my.size();k++){
		cout << "(" << my[k].begin << "," << my[k].end << ") ->" << my[k].weight << endl;
	}
} 
//广度优先遍历
void BFS(graph1 t[],int visit[],int begin,int n){
	queue<int> store;   //采用队列遍历 
	vector<mymap> my;
	store.push(begin);
	visit[begin]=1;
	int i=0;
	while(!store.empty()){
		int id=store.front();   //取出队列头元素并删除 
		store.pop();            
		i++;                    //遍历 
		cout << id << " ";
		line* e=t[id].firstedge;  //以下思路与深度优先遍历类似 
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
			e=((e->ivex==id)?e->ilink:e->jlink);  //区别：先进行横向遍历 
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
	cout << endl << "边集为：" << endl;
	for(int k=0;k<my.size();k++){
		cout << "(" << my[k].begin << "," << my[k].end << ") ->" << my[k].weight << endl;
	}
}
//非递归深度遍历 
vector<int> dfscount;  //存储每个节点的出度，方便后面建立深度优先生成树 
void DFS_u(graph2 s[],int visit[],int n){
	stack<int> store;
	int id=0;
	int i=1;
	cout << id << " ";    //输出第一个节点 
	dfscount.push_back(s[0].next.size());   
	visit[0]=1;
	for(id;i<n;){        //遍历 
		if(s[id].next.size()){
			int j=s[id].next.size()-1;
			int count=0;
			for(j;j>=0;j--){     //先把同一层的节点存入栈中 
				if(visit[s[id].next[j].end]==0){   //在与当前节点连接的节点中未遍历的成为出度 
					store.push(s[id].next[j].end);
					count++;
				}
			}
			dfscount.push_back(count);  //存储每个节点的出度 
		}
		if(store.size()){   //存储同层节点后开始深度遍历 
			id=store.top();
			if(visit[id]==0){
				visit[id]=1;
				i++;
				cout << id << " ";
			}
			store.pop();
		}                    
		if(store.size()==0&&i<n){   //处理非连通图的单独节点 
			for(int k=0;k<n;k++){
				if(visit[k]==0){
					store.push(k);
					break;
				}
			}
		}
	}
}
//深度优先生成树
void DFS_tree(graph2 s[],int visit[],int num,vector<int> &store_num){
	if(visit[num]==1){
		return;
	}
	visit[num]=1;
	store_num.push_back(num);
	for(int i=0;i<s[num].next.size();i++){     //递归算法进行深度优先遍历，将遍历完的序列存储，建立深度优先生成树 
		if(visit[s[num].next[i].end]==0){
			DFS_tree(s,visit,s[num].next[i].end,store_num);
		}
	}
} 
//广度优先生成树
void BFS_tree(graph2 s[],int visit[],int num,int n){
	queue<int> store;   //使用队列 
	store.push(num);
	vector<int> count;
	vector<int> store_num;
	visit[num]=1;
	int i=0;
	while(!store.empty()){    //非递归建立广度优先生成树 
		int top=store.front();
		store_num.push_back(top);
		i++;
		store.pop();
		int countnum=0;
		for(int j=0;j<s[top].next.size();j++){   //将同层元素存入队列 
			if(visit[s[top].next[j].end]==0){
				visit[s[top].next[j].end]=1;
				store.push(s[top].next[j].end);
				countnum++;    //存储未遍历的同层节点的个数 
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
			cout << "-";      //当该节点的存在一个后继则输出“-" 
		}
		index--;
		sum+=count[k];
		if(index==0){        //当该层根节点打印完进行换行操作 
			cout << endl;
			index=sum;
			sum=0;
		}
	}
} 

int main(){
	int n,m;
	cout << "请输入图的顶点数和边数：" << endl;
	cin >> n >> m; //n为节点数，m为边数
	graph2 s[n]; 
	graph1 t[n];
	int visit[n]={0};
	for(int i=0;i<n;i++){
		s[i].id=i;
		t[i].id=i;
		t[i].firstedge=NULL;
	}
	cout << "请输入边之间的连接关系:（顶点1,顶点2,权重）" << endl;
	for(int i=0;i<m;i++){
		int in,out,length;
		cin >> in >> out >> length;
		//多重连接表的建立
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
		//连接表的建立 
		edge tmp1(out,length);
		edge tmp2(in,length);
		s[in].next.push_back(tmp1);
		s[out].next.push_back(tmp2);
	}
	cout << "请选择你要进行的操作：" << endl;
	cout << "1.深度优先遍历（邻接多重表）" << endl;
	cout << "2.广度优先遍历（邻接多重表）" << endl;
	cout << "3.深度优先遍历（非递归）" << endl;
	cout << "4.深度优先生成树" << endl;
	cout << "5.广度优先生成树" << endl; 
	cout << "0.退出" << endl;
	int op;
	cin >> op;
	while(op){
		if(op==1){
			cout << "请输入开始节点：" << endl;
			int begin;
			cin >> begin; 
			DFS(t,visit,begin,n);
			for(int i=0;i<n;i++){
				visit[i]=0;
			}
		}else if(op==2){
			cout << "请输入开始节点：" << endl;
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
		cout << "请选择你要进行的操作：" << endl;
		cout << "1.深度优先遍历（邻接多重表）" << endl;
		cout << "2.广度优先遍历（邻接多重表）" << endl;
		cout << "3.深度优先遍历（非递归）" << endl;
		cout << "4.深度优先生成树" << endl;
		cout << "5.广度优先生成树" << endl; 
		cout << "0.退出" << endl;
		cin >> op;
	} 
}
