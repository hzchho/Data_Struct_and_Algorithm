#include<iostream>
using namespace std;
#include<string>
#include<cmath>
#include<stack>
#include<queue>
struct tree{
	char data;
	tree *lchild;
	tree *rchild;
	tree(char x):data(x),lchild(NULL),rchild(NULL){}
};
//����ǰ׺���ʽ������������������������� 
tree *buildtree(string s,int &pos){
	if(pos>=s.length()){
		return NULL;
	}
	char ch=s[pos];
	pos++;
	if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^'){
		tree *p=new tree(ch);
		p->lchild=buildtree(s,pos);
		p->rchild=buildtree(s,pos);
		return p;
	}else if(ch>='a' && ch<='z'){
		tree *p=new tree(ch);
		return p;
	}else{
		tree *p=new tree(ch);
		return p;
	}
}
//�����������������׺���ʽ 
void printin(tree *root,bool isneed){
	if(root==NULL){
		return;
	}
	if(root->data=='+' ||root->data=='-' ){
		if(isneed==1){
			cout << "(" ;
		}
		printin(root->lchild,1);
		cout << root->data;
		printin(root->rchild,1);
		if(isneed==1){
			cout << ")" ;
		}
	}else if(root->data=='*' ||root->data=='/' ||root->data=='^'){
		printin(root->lchild,1);
		cout << root->data;
		printin(root->rchild,1);
	}else{
		cout << root->data ;
	}
}
//��������ֵ��������ڶ����ͬ������ֻ��Ҫ��ֵһ�� 
void giveval(tree* root,char pa,int val){
	if(root==NULL){
		return;
	}
	if(root->data==pa){
		root->data=val+'0';
	}
	giveval(root->lchild,pa,val);
	giveval(root->rchild,pa,val);
}
//������ʽ��ֵ��������δ��ֵ�ı�������0���� 
//1.�Ȱ���׺���ʽ��������ջ 
void putvector(tree *root,queue<char> &store,bool isneed){
	if(root==NULL){
		return;
	}
	if(root->data=='+' ||root->data=='-' ||root->data=='*' ||root->data=='/' ||root->data=='^'){
		store.push('(');
		putvector(root->lchild,store,1);
		store.push(root->data);
		putvector(root->rchild,store,1);
		store.push(')');
	}else{
		store.push(root->data);
	}
}
//2.�������ּ�ļ���
double calculate(double num1,char ope, double num2){ 
	switch (ope){
		case '+':
			return num1+num2;
		case '-':
			return num1-num2;
        case '*':
        	return num1*num2;
        case '/':
        	if(num2==0){
        		return 0;
			}else{
				return num1*1.0/num2;
			}
		case '^':
			return pow(num1,num2);
        default:
        	return 0;
	}
}
//3.�жϷ��ŵ����ȼ� 
int get_pri(char op){
	switch(op){
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '^':
			return 3;
		case '#':
			return 0;
	}
}
//4.���� 
double printval(queue<char> &store){
	if(store.empty()){//����洢��׺���ʽ�Ķ���Ϊ���򷵻�0 
		return 0;
	}
	store.push('#');//�ڶ��������롰#����Ϊ������־ 
	stack<double> int_sta;//����ջ 
	stack<char> op_sta;//�����ջ 
	op_sta.push('#');//�������ջջ�ײ��롰#������ƥ������ 
	for(1;!store.empty();){
		if(store.front()>='0' && store.front()<='9'){//����ж϶�����Ϊ���֣���������ջ 
			double num=store.front()-'0';
			store.pop();
			int_sta.push(num);
		}else if(store.front()>='a' && store.front()<='z'){//�����������δ��ֵ����ĸ��������ֵΪ0��������ջ 
			store.pop();
			int_sta.push(0);
		}else{//������̰����ŷ��Ų������ 
			if(store.front()=='('){//��������������� 
				op_sta.push('(');
				store.pop();
			}else if(store.front()=='+' || store.front()=='-' || store.front()=='*' || store.front()=='/' || store.front()=='^'){
				if(op_sta.top()=='(' || op_sta.top()=='#'){//����������������ۼ��㣬���ջ��Ϊ���Ż�#��ֱ�Ӵ��� 
					op_sta.push(store.front());
					store.pop();
				}else{//�����жϵ�ǰ�������ջ����������ȼ� 
					int pri1=get_pri(store.front());
					int pri2=get_pri(op_sta.top());
					if(pri1<=pri2){//���м������� ��ȡ���������֣�����������뺯�����м��� 
						char top_op=op_sta.top();
						op_sta.pop();
						double num2=int_sta.top();
						int_sta.pop();
						double num1=int_sta.top();
						int_sta.pop();
						double res1=calculate(num1,top_op,num2);
						int_sta.push(res1);
					}else{
						op_sta.push(store.front());
						store.pop();
					}
				}
			}else if(store.front()==')'){//���������ţ���Ѱ�������� �����ǣ�������ȥ������ 
				if(op_sta.top()=='('){
					op_sta.pop();
					store.pop();
				}else{//�����ǣ��������������� 
					char top_op=op_sta.top();
					op_sta.pop();
					double num2=int_sta.top();
					int_sta.pop();
					double num1=int_sta.top();
					int_sta.pop();
					double res1=calculate(num1,top_op,num2);
					int_sta.push(res1);
				}
			}else if(store.front()=='#'){//�������һ���ַ����ж��Ƿ���� 
				if(op_sta.top()=='#'){
					return int_sta.top();
				}else{
					while(op_sta.top()!='#'){
						char top_op=op_sta.top();
						op_sta.pop();
						double num2=int_sta.top();
						int_sta.pop();
						double num1=int_sta.top();
						int_sta.pop();
						double res1=calculate(num1,top_op,num2);
						int_sta.push(res1);
				    }
				    return int_sta.top(); 
				}
			}
		}
	}
} 
//���������ʽ�ϲ� 
tree* combination(tree* root, char opee, tree* root2){
	tree *p=new tree(opee);
	p->lchild=root;
	p->rchild=root2;
	return p;
}
//�������������� 
int judgedepth(tree *root,int &depth){
	if(root==NULL){
		return 0;
	}
	depth++;
	int ldep=judgedepth(root->lchild,depth);
	int rdep=judgedepth(root->rchild,depth);
	return ((ldep>rdep)?ldep:rdep)+1;
}
//����������Ŀ��ӻ����� 
void printtree(tree *root,int depth){
	if(root==NULL){
		return;
	}
	printtree(root->lchild,depth-1);
	for(int i=0;i<depth;i++){
		cout << "   " ;
	}
	cout << root->data << endl;
	printtree(root->rchild,depth-1);
}
int main(){
	cout << "������ǰ׺���ʽ������ȷ�����ʽ������Ч,�����ո�" << endl; 
	string str;
	cin >> str;
	tree * root;
	int pos=0;
	root=buildtree(str,pos);
	int ope;
	do{
		cout << endl;
		cout << "��ѡ����Ҫ���еĲ�����" << endl;
		cout << "1.�����׺���ʽ" << endl;
		cout << "2.�Ա�����ֵ" << endl;
		cout << "3.����������ʽ��ֵ������δ��ֵ�ı�����һ�ɵ���0��" << endl;
		cout << "4.����һ���µķ��ű��ʽ" << endl;
		cout << "5.��ʾ���Ľṹ��ǰ�������Ѵ��ڣ�" << endl;
		cout << "0.�˳�" << endl << endl; 
		cin >> ope;
		if(ope==1){
			printin(root,0);
		}else if(ope==2){
			cout << "��������Ҫ��ֵ�ı�����" << endl;
			char pa;
			cin >> pa;
			cout <<  pa << "=";
			int val;
			cin >> val; 
			giveval(root,pa,val);
		}else if(ope==3){
			queue<char> store;
			putvector(root,store,0);
			double sum=printval(store);
			cout << "���ʽ��ֵΪ��"; 
			cout << sum << endl;
		}else if(ope==4){
			cout << "������Ҫ��ӵı��ʽ��" << endl;
			string str2;
			cin >> str2;
			int pos2=0;
			tree* root2;
			root2=buildtree(str2,pos2);
			cout << "Ҫ���еĲ�����" << endl;
			char opee;
			cin >> opee;
			root=combination(root,opee,root2); 
		}else if(ope==5){
			int depth=0;
			depth=judgedepth(root,depth);
			cout << "Ŀǰ�Ķ���������Ϊ��" << depth << endl;
			cout << "������Ϊ��" << endl;
			printtree(root,depth-1);
		}
	}while(ope);
	cout << "��ӭ�ٴ�ʹ�ã�" << endl; 
	return 0;
}
