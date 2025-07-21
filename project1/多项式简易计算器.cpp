#include<iostream>
using namespace std;
#include<vector>
#include<cmath>
#include<algorithm>
struct Poly{
	double c;
	double e;
};
typedef vector<Poly> poly;
//�������������ʽ���ܣ������ʽ��a*x^(b)����ʾa����x��b�η� 
void printPoly(poly &a){
	if(a.size()==0){
		cout << "0" ;
		return; 
	}
	for(auto i=a.begin();i!=a.end();i++){
		if(i->c < 0){
			cout << i->c ;
		}else{
			if(i==a.begin()){
				cout << i->c ;
			}else{
				cout << "+" << i->c ;
			}
		}
		if(i->e==0){
			continue;
		}else{
			cout << "*x^" << "(" << i->e << ")" ;
		}
	}
}
//ʵ�ּӷ����� 
poly addPoly(poly &a){
	cout << "��������Ҫ�ӵĶ���ʽ��" << endl;
	poly term;
	poly b;
	int n;
	cin >> n;
	for(int i=0;i<n;i++){
		double c2,e2;
		cin >> c2 >> e2;
		Poly tmp;
		tmp.c=c2;
		tmp.e=e2;
		if(c2==0){
			continue;
		}
		int k=0;
		if(b.size()==0){
			b.push_back(tmp);
		}else{
			while(k<b.size()){
				if(tmp.e==b[k].e){
					b[k].c+=tmp.c;
					break;
				}
				k++;
			}
			if(k==b.size()){
				b.push_back(tmp);
			}
		}
	}
	sort(b.begin(),b.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	cout << "( ";
	printPoly(a);
	cout << " )" << " + " << "(" ;
	printPoly(b); 
	cout << ")" << endl;
	int j=0,k=0;
	while(j<a.size() && k<b.size()){
		if(a[j].e==b[k].e){
			Poly tmp1;
			tmp1.e=a[j].e;
			tmp1.c=a[j].c+b[k].c;
			if(tmp1.c!=0){ 
				term.push_back(tmp1);
			}
			j++;
			k++;
		}else if(a[j].e>b[k].e){
			term.push_back(a[j]);
			j++;
		}else{
			term.push_back(b[k]);
			k++;
		}
	}
	while(j<a.size()){
		term.push_back(a[j]);
		j++;
	}
	while(k<b.size()){
		term.push_back(b[k]);
		k++;
	}
	sort(term.begin(),term.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	return term;
}
//ʵ�ּ������� 
poly subPoly(poly &a){
	cout << "��������Ҫ���Ķ���ʽ��" << endl;
	poly term;
	poly b;
	int n;
	cin >> n;
	for(int i=0;i<n;i++){
		double c2,e2;
		cin >> c2 >> e2;
		Poly tmp;
		tmp.c=c2;
		tmp.e=e2;
		if(c2==0){
			continue;
		}
		int k=0;
		if(b.size()==0){
			b.push_back(tmp);
		}else{
			while(k<b.size()){
				if(tmp.e==b[k].e){
					b[k].c+=tmp.c;
					break;
				}
				k++;
			}
			if(k==b.size()){
				b.push_back(tmp);
			}
		}
	}
	sort(b.begin(),b.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	cout << "( ";
	printPoly(a);
	cout << " )" << " - " << "(" ;
	printPoly(b); 
	cout << ")" << endl;
	int j=0,k=0;
	while(j<a.size() && k<b.size()){
		if(a[j].e==b[k].e){
			Poly tmp1;
			tmp1.c=a[j].c-b[k].c;
			tmp1.e=a[j].e;
			if(tmp1.c!=0){
				term.push_back(tmp1);
			}
			j++;
			k++;
		}else if(a[j].e>b[k].e){
			term.push_back(a[j]);
			j++;
		}else{
			b[k].c=-b[k].c;
			term.push_back(b[k]);
			k++;
		}
	}
	while(a.size()<j){
		term.push_back(a[j]);
		j++;
	}
	while(b.size()<k){
		b[k].c=-b[k].c;
		term.push_back(b[k]);
		k++;
	}
	sort(term.begin(),term.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	return term;
}
//ʵ�������ʽ��x����ֵ����ֵ�� 
double sum(poly &a,int x){
	double sum=0;
	for(int i=0;i<a.size();i++){
		sum+=(a[i].c*pow(x,a[i].e));
	}
	return sum;
}//�� 
poly Derive(poly &a){
	poly term;
	for(int i=0;i<a.size();i++){
		Poly tmp;
		tmp.c=a[i].c*a[i].e;
		tmp.e=a[i].e-1;
		if(tmp.c!=0){
			term.push_back(tmp);
		}
	}
	return term;
}
//ʵ�ֶ���ʽ�˷����� 
poly mulPoly(poly &a){
	cout << "��������Ҫ�˵Ķ���ʽ��" << endl;
	poly term;
	poly b;
	int n;
	cin >> n;
	for(int i=0;i<n;i++){
		double c2,e2;
		cin >> c2 >> e2;
		Poly tmp;
		tmp.c=c2;
		tmp.e=e2;
		if(c2==0){
			continue;
		}
		b.push_back(tmp);
	}
	sort(b.begin(),b.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	cout << "( ";
	printPoly(a);
	cout << " )" << " * " << "(" ;
	printPoly(b); 
	cout << ")" << endl;
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b.size();j++){
			Poly tmp;
			tmp.c=a[i].c*b[j].c;
			tmp.e=a[i].e+b[j].e;
			int k=0;
			if(term.size()==0){
				term.push_back(tmp);
			}else{
				while(k<term.size()){
					if(term[k].e==tmp.e){
						term[k].c+=tmp.c;
						break;
					}
					k++;
				}
				if(k==term.size()){
					term.push_back(tmp);
					sort(term.begin(),term.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
				}
			}
			
		}
	}
	for(int i=0;i<term.size();i++){
		if(term[i].c==0){
			term.erase(term.begin()+i);
		}
	}
	sort(term.begin(),term.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	return term;
}
int main(){
	cout << "��ӭʹ��czh�ƶ���ʽ������" << endl;
	cout << "�����룺(��ʽ��������һ��n��ʾ������������c��e��ʾϵ����ָ��)" << endl; 
	vector<Poly> poly1;
	int n;// ����ʽ��λ��
	cin >> n;
	for(int i=0;i<n;i++){
		double c1,e1;
		cin >> c1 >> e1;
		Poly tmp;
		tmp.c=c1;
		tmp.e=e1;
		if(c1==0){
			continue;
		}
		int k=0;
		if(poly1.size()==0){
			poly1.push_back(tmp);
		}else{
			while(k<poly1.size()){
				if(tmp.e==poly1[k].e){
					poly1[k].c+=tmp.c;
					break;
				}
				k++;
			}
			if(k==poly1.size()){
				poly1.push_back(tmp);
			}
		}
	} 
	sort(poly1.begin(),poly1.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
	cout << endl;
	cout << "******************************" << endl; 
	cout << "��ѡ������Ҫ���еĲ���" << endl;
	cout << "����1:�������ʽ" << endl;
	cout << "����2:����ʽ���" << endl;
	cout << "����3:����ʽ���" << endl;
	cout << "����4:��x������ʽ��ֵ" << endl;
	cout << "����5:�Զ���ʽ��" << endl;
	cout << "����6:����ʽ���"<< endl;
	cout << "����7�������������ʽ" << endl;
	cout << "����0:�˳�ʹ�ã�" << endl; 
	int op;
	while((cin >> op) && op!=0){
		if(op==1){
			cout << "��ǰ�Ķ���ʽ�ǣ�" << endl;
			printPoly(poly1);
		}else if(op==2){
			poly1=addPoly(poly1);
			cout << "����ʽ��ӳɹ���" ; 
		}else if(op==3){
			poly1=subPoly(poly1);
			cout << "����ʽ����ɹ���" ; 
		}else if(op==4){
			int x;
			cin >> x;
			double s=sum(poly1,x);
			cout << "����ʽ:" ;
			printPoly(poly1);
			cout << "��" << x << "����ֵ�ǣ�" ; 
			cout << s ;
		}else if(op==5){
			poly der=Derive(poly1);
			cout << "����ɣ�����ʽ" ;
			printPoly(poly1);
			cout << "�ĵ����ǣ�" ; 
			printPoly(der);
		}else if(op==6){ 
			poly1=mulPoly(poly1);
			cout << "����ʽ��˳ɹ���" ;
		}else if(op==7){
			poly1.clear();	
			cout << "�����룺(��ʽ��������һ��n��ʾ������������c��e��ʾϵ����ָ��)" << endl; 		
			cin >> n;
			for(int i=0;i<n;i++){
				double c1,e1;
				cin >> c1 >> e1;
				Poly tmp;
				tmp.c=c1;
				tmp.e=e1;
				if(c1==0){
					continue;
				}
				int k=0;
				if(poly1.size()==0){
					poly1.push_back(tmp);
				}else{
					while(k<poly1.size()){
						if(tmp.e==poly1[k].e){
							poly1[k].c+=tmp.c;
							break;
						}
						k++;
					}
					if(k==poly1.size()){
						poly1.push_back(tmp);
					}
				}
			}
			sort(poly1.begin(),poly1.end(),[](const Poly&a,const Poly&b){return a.e>b.e;});
			cout << "����ʽ���³�ʼ���ɹ���" ;
		}
		cout << endl;
		cout << endl;
		cout << "******************************" << endl; 
		cout << "��ѡ������Ҫ���еĲ���" << endl;
		cout << "����1:�������ʽ" << endl;
		cout << "����2:����ʽ���" << endl;
		cout << "����3:����ʽ���" << endl;
		cout << "����4:��x������ʽ��ֵ" << endl;
		cout << "����5:�Զ���ʽ��" << endl;
		cout << "����6:����ʽ���"<< endl;
		cout << "����7�������������ʽ" << endl;
		cout << "����0:�˳�ʹ�ã�" << endl; 
	} 
	cout << "��ӭ�ٴ�ʹ�ã�" << endl; 
}
