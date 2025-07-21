#include<iostream>
using namespace std;
#include<stack>
#include<cmath>
#include<cstring>
bool isnum(char a){//判断是否为数字 
	if(a>='0' && a<='9'){
		return true;
	}else{
		return false;
	}
}
double calculate(double num1,char ope, double num2){//进行数字间的计算 
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
int get_pri(char op){//判断符号的优先级 
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
	stack<char> op_sta;//运算符栈 
	stack<double> num_sta;//数字栈
	char c='#';
	op_sta.push(c); 
	int len=a.length();
	for(int i=0;i<len;){
		if(a[i]==' '){//如果是空格，则跳到下一位 
			i++;
			continue;
		}
		if(isnum(a[i])==1){//如果是数字，判断是几位数，并插入到数字栈中 
			double num=0; 
			while(i<len && isnum(a[i])==1){//整数的情况 
				num=num*10+(a[i]-'0');
				i++;
			}
			if(a[i]=='.'){//出现小数的情况 
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
		}else{//不是数字的情况 
			if(a[i]=='('){//如果为（ ，可以忽略 
				op_sta.push(a[i]);
				i++;
				while(a[i]==' '){
					i++;
				} 
				if(a[i]=='-'){//处理负数情况 
					num_sta.push(0);
				}
			}else if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='^'){//如果为+，-，*，/，^则进行判断 
				if(op_sta.top()=='('){
					op_sta.push(a[i]);
					i++;
				}else if(op_sta.top()=='#'){//插入第一个符号的情况 
					op_sta.push(a[i]);
					i++;
				}else{
					int pri1=get_pri(a[i]);
					int pri2=get_pri(op_sta.top());
					if(pri1<=pri2){//进行计算的情况 
						char top_op=op_sta.top();
						op_sta.pop();
						double num2=num_sta.top();
						num_sta.pop();
						double num1;
						if(num_sta.empty()){//处理出现负数情况 
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
			}else if(a[i]==')'){//碰到），分情况运算 
				if(op_sta.top()=='('){//如果（）内运算已完成，则直接消除括号 
					op_sta.pop();
					i++;
				}else if(op_sta.top()=='#'){//出错的情况1
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
			}else if(a[i]=='#'){//如果碰到#，则结束运算过程 
				if(op_sta.top()=='#'){//如果两个#之间无其他运算符 
					if(num_sta.empty()){
						cout << "error!" << endl;
						return -1;
					}else{
						return num_sta.top();
					}
				}else if(op_sta.top()=='('){//（后出现#的特殊情况 
					cout << "error!" << endl;
					return -1;
				}else{//正常运算情况下的最后一步 
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
	cout << "欢迎使用表达式求值计算器" << endl; 
	cout << "请输入表达式：" << endl; 
	cout << "[请按照正确的格式：'(' 需要有')'配对，结尾请加一个'#'表示完成输入]" << endl; 
	string op;
	getline(cin ,op);
	double result=operation(op);
	cout << "表达式结果为：" << result << endl;
	return 0;
} 
