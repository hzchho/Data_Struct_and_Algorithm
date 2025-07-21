#include<iostream>
using namespace std;
#include<stack>
#include<cmath>
#include<cstring>
bool isnum(char a){//�ж��Ƿ�Ϊ���� 
	if(a>='0' && a<='9'){
		return true;
	}else{
		return false;
	}
}
double calculate(double num1,char ope, double num2){//�������ּ�ļ��� 
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
				return num1/num2;
			}
		case '^':
			return pow(num1,num2);
        default:
        	return 0;
	}
}
int get_pri(char op){//�жϷ��ŵ����ȼ� 
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
double operation(const string &a){
	stack<char> op_sta;//�����ջ 
	stack<double> num_sta;//����ջ
	char c='#';
	op_sta.push(c); 
	int len=a.length();
	for(int i=0;i<len;){
		if(a[i]==' '){//����ǿո���������һλ 
			i++;
			continue;
		}
		if(isnum(a[i])==1){//��������֣��ж��Ǽ�λ���������뵽����ջ�� 
			double num=0; 
			while(i<len && isnum(a[i])==1){//��������� 
				num=num*10+(a[i]-'0');
				i++;
			}
			if(a[i]=='.'){//����С������� 
				i++;
				int con=0;
				while(i<len && isnum(a[i])==1){
					num=num*10+(a[i]-'0');
					i++;
					con++;
				}
				while(con){
					con--;
					num=num/10;
				}
			} 
			num_sta.push(num);
		}else{//�������ֵ���� 
			if(a[i]=='('){//���Ϊ�� �����Ժ��� 
				op_sta.push(a[i]);
				i++;
				while(a[i]==' '){
					i++;
				} 
				if(a[i]=='-'){//��������� 
					num_sta.push(0);
				}
			}else if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='^'){//���Ϊ+��-��*��/��^������ж� 
				if(op_sta.top()=='('){
					op_sta.push(a[i]);
					i++;
				}else if(op_sta.top()=='#'){//�����һ�����ŵ���� 
					op_sta.push(a[i]);
					i++;
				}else{
					int pri1=get_pri(a[i]);
					int pri2=get_pri(op_sta.top());
					if(pri1<=pri2){//���м������� 
						char top_op=op_sta.top();
						op_sta.pop();
						double num2=num_sta.top();
						num_sta.pop();
						double num1;
						if(num_sta.empty()){//������ָ������ 
							num1=0;
						}else{
							num1=num_sta.top();
						    num_sta.pop();
						}
						double res1=calculate(num1,top_op,num2);
						num_sta.push(res1);
					}else{
						op_sta.push(a[i]);
						i++;
					}
				}
			}else if(a[i]==')'){//����������������� 
				if(op_sta.top()=='('){//�����������������ɣ���ֱ���������� 
					op_sta.pop();
					i++;
				}else if(op_sta.top()=='#'){//��������1
				    cout << "error!" << endl; 
					return -1;
				}else{
					char top_op=op_sta.top();
					op_sta.pop();
					double num2=num_sta.top();
					num_sta.pop();
					double num1;
					if(num_sta.empty()){
						num1=0;
					}else{
						num1=num_sta.top();
						num_sta.pop();
					}
					double res1=calculate(num1,top_op,num2);
					num_sta.push(res1);
				}
			}else if(a[i]=='#'){//�������#�������������� 
				if(op_sta.top()=='#'){//�������#֮������������� 
					if(num_sta.empty()){
						cout << "error!" << endl;
						return -1;
					}else{
						return num_sta.top();
					}
				}else if(op_sta.top()=='('){//�������#��������� 
					cout << "error!" << endl;
					return -1;
				}else{//������������µ����һ�� 
					while(op_sta.top()!='#'){
						char top_op=op_sta.top();
						op_sta.pop();
						double num2=num_sta.top();
						num_sta.pop();
						double num1;
						if(num_sta.empty()){
							num1=0;
						}else{
							num1=num_sta.top();
						    num_sta.pop();
						}
						double res1=calculate(num1,top_op,num2);
						num_sta.push(res1);
					} 
					return num_sta.top(); 
				}
			}
		}
	}
}
int main(){
	cout << "��ӭʹ�ñ��ʽ��ֵ������" << endl; 
	cout << "��������ʽ��" << endl; 
	cout << "[�밴����ȷ�ĸ�ʽ��'(' ��Ҫ��')'��ԣ���β���һ��'#'��ʾ�������]" << endl; 
	string op;
	getline(cin ,op);
	double result=operation(op);
	cout << "���ʽ���Ϊ��" << result << endl;
	return 0;
} 
