#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<bitset>
using namespace cv;
using namespace std;
//����������ѹ����
class HuffmanNode {
public:
	char c;
	long long int weight;
	int parent;//ָ�򸸽ڵ��pos��
	int lchild;//ָ�����ӵ�pos��
	int rchild;//ָ���Һ��ӵ�pos��
	string code;//�洢������code��
	HuffmanNode() :c(0), weight(0), parent(0), lchild(0), rchild(0), code("") {//parentΪ0������parent//string ��ʼ��Ϊ�������ƺ����ռ�ÿռ䣬Ҳ���ܳ�����{����}Ҳ���Գ�ʼ����
	}
};
class HuffmanTree :private HuffmanNode {
private:
	//������
	int TreeSize;
	int LeafSize;
	HuffmanNode* Tree;
	map<char, string> CharToCode;
	map<string, char> CodeToChar;

	//������
	void Sort(HuffmanNode* Tree, int n, int& s1, int& s2) {//���� [1,n-1]��Ԫ�أ��ҳ���С��������//ע�����С����û�и��ڵ����С��������
		multimap<long long int, int> tem;//ʵ�����Զ�����//weight������ͬ��Ҫmultimap
		for (int i = 1; i < n; i++) {
			if (Tree[i].parent == 0) {
				tem.insert(make_pair(Tree[i].weight, i));
			}
		}
		auto p = tem.begin();
		s1 = p->second;//Ӧ�ö԰ɡ�
		p++;
		s2 = p->second;
	}
	void Writeinfile(string input, string filename) {
		ofstream output(filename, ifstream::binary);
		if (!output) cout << "wrong" << endl;
		//��input����Ϊ01�ַ�����
		string newstr = "";
		for (int i = 0; i < input.size(); i++) {
			for (auto j = CharToCode.begin(); j != CharToCode.end(); j++) {
				if ((*j).first == input[i]) {
					newstr += (*j).second;
				}
			}
		}
		//��ChartoCodeд���ļ�;Ҫ˳����볤�ȵ���Ϣ��
		//д��input���ȣ�
		int countload = newstr.length() / 8 + 1;
		char lenoffinal = newstr.length() % 8;
		char tem = (int)CodeToChar.size();
		output << countload;
		output << lenoffinal;
		output << tem;
		for (auto it = CodeToChar.begin(); it != CodeToChar.end(); it++) {
			string s = (*it).first;
			char slen = s.size();
			output << slen;
			for (int i = 0; i < slen; i++) {
				output << s[i];
			}
			output << (*it).second;
		}

		//��01�ַ�����ɰ�λ�������룻
		for (int i = 0; i < newstr.size(); i += 8) {
			string byte = newstr.substr(i, 8); // ����λһ��ָ�
			unsigned char x = static_cast<char>(bitset<8>(byte).to_ulong()); // ����λ������ת��Ϊ�ַ�
			output << x;
		}
		//cout << "�ַ�����ɹ�" << endl;
		output.close();
	}
public:
	HuffmanTree() :TreeSize(0), Tree(nullptr) {}
	void Compress(string path, string filename) {
		//��path����path�ļ��е����ݻ�Ϊstring����input���棻
		ifstream infile(path, ifstream::binary);
		if (!infile) {
			cout << "wrong" << endl;
		}
		string input((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
		//ͳ��Ƶ�ʲ�����map��
		map<char, long long int> m;
		for (int i = 0; i < input.size(); i++) {
			if (m.find(input[i]) != m.end()) {
				m[input[i]] += 1;
			}
			else {
				m[input[i]] = 1;
			}
		}
		//��m����Ϣ�洢��Tree�У�ʵ�ֳ�ʼ��LeafSize��Node��
		LeafSize = m.size();
		TreeSize = 2 * m.size() - 1;
		Tree = new HuffmanNode[TreeSize + 1];//0��Node��ʹ�á���������2*LeafSize-1���ڵ�
		int k = 1;//0�Žڵ㲻ʹ�á�
		for (auto it = m.begin(); it != m.end(); it++, k++) {//��ʼ���ڵ㣻
			Tree[k].weight = it->second;
			Tree[k].c = it->first;
		}
		//��ʼ���ڵ�󣬽��н���������Huffman����ǰ��LeafSize��ԭʼ�ڵ��ΪҶ�ӽڵ㣬LeafSize-1���ڲ��ڵ㣨���ڽ�ԭʼLeafSize���ڵ���ϵ��������
		for (int i = LeafSize + 1; i < 2 * LeafSize; i++) {//����n-1���ںϣ��½ڵ����i�����ںϺ�Tree��2*LeafSize-1��Ϊ���ڵ��ˡ�
			int s1, s2;
			Sort(Tree, i, s1, s2);//�˺���ѡ��weight��С������pos��s1Ϊ��С�ģ�s2Ϊ����С�ģ�//ע�����С����û�и��ڵ����С��������weightС�Ľڵ㴦��Խ��ĵط����������Խ��   
			//�������ڵ��Ϊһ���ڵ㣻
			Tree[i].parent = 0;//�½ڵ��޸��׽ڵ㣻
			Tree[i].rchild = s1;//�ҽڵ�Ϊ��С
			Tree[i].lchild = s2;//��ڵ�Ϊ��С��
			Tree[s1].parent = i;
			Tree[s2].parent = i;//���ӽڵ㸸�׽ڵ��޸�Ϊi��
			Tree[i].weight = Tree[s1].weight + Tree[s2].weight;//�½ڵ��weight����Ϊ����֮�ͣ�
		}
		//���������б��룻��huffman���Ľṹ��֪�����������Ϊǰ׺�룻
		//�Ӹ��ڵ�Tree��2*LeafSize-1�������б����������Ϊ1�������ұ�Ϊ0��ʵ����Ϊ��α�����
		queue<int> pos;//��α�����Ҫ�����飻һ��ʼѹ����ڵ㣻
		pos.push(2 * LeafSize - 1);
		while (pos.size() != 0) {
			int tem = pos.front();
			pos.pop();
			if (Tree[tem].lchild == 0 && Tree[tem].rchild == 0) {//��Ҷ�ӽڵ��ˣ���������
				CharToCode.insert(make_pair(Tree[tem].c, Tree[tem].code));//��Ҷ�ӽڵ����Ϣ�洢������map�У��������룻
				CodeToChar.insert(make_pair(Tree[tem].code, Tree[tem].c));
			}
			else {
				Tree[Tree[tem].lchild].code = Tree[tem].code + "1";
				Tree[Tree[tem].rchild].code = Tree[tem].code + "0";
				pos.push(Tree[tem].lchild);
				pos.push(Tree[tem].rchild);
			}
		}
		//���ϲ���Ϊ����������������ϣ�д��filename��
		Writeinfile(input, filename);
	}
	void DeCompress(string path, string filename) {
		ifstream from(path);
		ofstream to(filename);
		if (!from) cout << "wrong" << endl;
		if (!to) cout << "wrong" << endl;
		map<string, char> m;
		int countload;
		char lenoffinal;
		char msize;
		from >> countload;
		from.read(&lenoffinal, sizeof(char));
		from.read(&msize, sizeof(char));
		for (int i = 0; i < msize; i++) {
			string s = "";
			char c;
			char slen;
			from.read(&slen, sizeof(char));
			for (int i = 0; i < slen; i++) {
				char tem;
				from.read(&tem, sizeof(char));
				s += {tem};
			}
			from.read(&c, sizeof(char));
			m.insert(make_pair(s, c));
		}
		string key = "";
		char tem = 0;
		int printlen = 0;
		for (int i = 0; i < countload; i++) {
			from.read((char*)&tem, sizeof(char));
			int j = 0;
			if (i == countload - 1) {
				for (int k = 0; k < 8 - lenoffinal; k++) {
					j++;
					tem = tem * 2;
				}
			}
			for (; j < 8; j++) {
				if (tem >= 0) {
					key += "0";
				}
				else {
					key += "1";
				}
				if (m.find(key) != m.end()) {
					to.write(&m[key], sizeof(char));
					printlen++;
					key = "";
				}
				tem = tem * 2;
			}
		}
	}
};
class TextCompresser {
public:
	string path;
	string filename;
	TextCompresser(string path, string filename) :path(path), filename(filename) {
	}
	void HuffmanCompress() {
		HuffmanTree my;
		my.Compress(path, filename);
	}
	void HuffmanDeCompress() {
		HuffmanTree my;
		my.DeCompress(path, filename);
	}
};
//P3���͵�����
struct ppmdata {
	int r;
	int g;
	int b;
	ppmdata(int x=0,int y=0,int z=0):r(x),g(y),b(z){}
};
//��Ԫ��
struct triple {
	int row;
	int col;
	ppmdata data;
	triple(int r=0,int c=0,ppmdata q=0):row(r),col(c),data(q){}
};
//�洢P3����
struct ppm {
	string type;
	int width;
	int height;
	int maxvalue;
	triple* sm;
};
//����
struct index {
	int x;
	int y;
	index(int a, int b) :x(a), y(b){}
};
//��P3����ת���ɴ�������
struct store {
	int count;
	int r;
	int g;
	int b;
	vector<index> in;
	store() {};
};
//��ȡP3���͵�ppm�ļ�
ppm readppmP3(ifstream& file) {
	ppm tmp;
	file >> tmp.type;
	cout << "��ͼƬ����Ϊ��" << tmp.type << endl;
	file >> tmp.width >> tmp.height;
	cout << "���Ϊ��" << tmp.width << " �߶�Ϊ��" << tmp.height << endl;
	file >> tmp.maxvalue;
	cout << "�������ֵΪ��" << tmp.maxvalue << endl;
	int r, g, b;
	tmp.sm = new triple[tmp.width * tmp.height];
	for (int i = 0; i < tmp.width * tmp.height; i++) {
		int h = i / tmp.width;
		int c = i % tmp.width;
		file >> r >> g >> b;
		ppmdata q(r, g, b);
		triple s(h, c, q);
		tmp.sm[i] = s;
	}
	return tmp;
}
//ѹ��P3���͵��ļ�
void zipP3(ppm& p) {
	ofstream ofs("zipP3.txt");
	if (!ofs.is_open()) {
		cout << "�ļ���ʧ�ܣ�" << endl;
	}
	ofs << p.type << endl;
	ofs << p.width << " " << p.height << endl;
	ofs << p.maxvalue << endl;
	int size = p.width * p.height;
	//int size = 100;
	vector<store> filestore;
	for (int i = 0; i < size; i++) {
		int red = p.sm[i].data.r;
		int green = p.sm[i].data.g;
		int blue = p.sm[i].data.b;
		int x = p.sm[i].row;
		int y = p.sm[i].col;
		if (filestore.size() == 0) {
			store tmp;
			tmp.r = red;
			tmp.g = green;
			tmp.b = blue;
			tmp.count = 1;
			index tmp1(x, y);
			tmp.in.push_back(tmp1);
			filestore.push_back(tmp);
			//cout << "0" << endl;
		}
		else {
			int j;
			for (j = 0; j < filestore.size(); j++) {
				if (filestore[j].r == red && filestore[j].g == green && filestore[j].b == blue) {
					index tmp1(x, y);
					filestore[j].count++;
					filestore[j].in.push_back(tmp1);
					break;
				}
			}
			if (j == filestore.size()) {
				store tmp;
				tmp.r = red;
				tmp.g = green;
				tmp.b = blue;
				tmp.count = 1;
				index tmp1(x, y);
				tmp.in.push_back(tmp1);
				filestore.push_back(tmp);
				//cout << "2" << endl;
			}
		}
	}
	for (int i = 0; i < filestore.size(); i++) {
		ofs << filestore[i].count << " " << filestore[i].r << " " << filestore[i].g << " " << filestore[i].b << endl;
		int j;
		for (j = 0; j < filestore[i].in.size()-1; j++) {
			ofs << filestore[i].in[j].x << " " << filestore[i].in[j].y << " ";
		}
		ofs << filestore[i].in[j].x << " " << filestore[i].in[j].y << endl;
	}
	ofs.close();
	cout << "ͼ���ļ�ѹ���ɹ�" << endl;
}
//ת��ɻҶ�ͼ��
void changegrey(ifstream& file) {
	ppm tmp;
	tmp = readppmP3(file);
	if (tmp.type == "P2") {
		cout << "��򿪵Ĳ��ǲ�ɫ�ļ���" << endl;
		return;
	}
	int size = tmp.width * tmp.height;
	for (int i = 0; i < size; i++) {
		int grey = (tmp.sm[i].data.r + tmp.sm[i].data.g + tmp.sm[i].data.b) / 3;
		tmp.sm[i].data.r = grey;
		tmp.sm[i].data.g = grey;
		tmp.sm[i].data.b = grey;
	}
	ofstream ofs("grey.ppm");
	tmp.type = "P2";
	ofs << tmp.type << endl;
	ofs << tmp.width << " " << tmp.height << endl;
	ofs << tmp.maxvalue << endl;
	for (int i = 0; i < size; i++) {
		ofs << tmp.sm[i].data.r << " ";
	}
	ofs.close();
}
//��ѹP3���͵��ļ�
void unzipP3(ifstream &ifs) {
	ppm p;
	ifs >> p.type;
	ifs >> p.width >> p.height;
	ifs >> p.maxvalue;
	vector<store> fileps;
	store ps;
	while (ifs >> ps.count >> ps.r >> ps.g >> ps.b) {
		for (int i = 0; i < ps.count; i++) {
			int a, b;
			ifs >> a >> b;
			index tmp(a, b);
			ps.in.push_back(tmp);
		}
		fileps.push_back(ps);
		ps.in.clear();
	}
	p.sm = new triple[p.width * p.height];
	int ind = 0;
	//cout << fileps.size() << endl;
	for (int i = 0; i < fileps.size(); i++) {
		int red = fileps[i].r;
		int green = fileps[i].g;
		int blue = fileps[i].b;
		ppmdata tmp2(red, green, blue);
		for (int j = 0; j < fileps[i].in.size(); j++) {
			triple s(fileps[i].in[j].x, fileps[i].in[j].y, tmp2);
			p.sm[ind] = s;
			ind++;
		}
	}
	ofstream ofs("unzipP3.ppm");
	ofs << p.type << endl;
	ofs << p.width << " " << p.height << endl;
	ofs << p.maxvalue << endl;
	int size = p.width * p.height;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((p.sm[j].row * p.width) + p.sm[j].col == i) {
				ofs << p.sm[j].data.r << " " << p.sm[j].data.g << " " << p.sm[j].data.b << " ";
			}
		}
	}
	ofs.close();
}


int main()
{
	Mat image;
	ifstream ifs;
	string filename;
	cout << "��ѡ����Ҫ�򿪵��ļ���" << endl;
	cout << "1.color-block.ppm" << endl;
	cout << "2.lena-128-gray.ppm" << endl;
	cout << "3.lena-512-gray.ppm" << endl;
	int op;
	cin >> op;
	if (op == 1) {
		filename = "color-block.ppm";
	}
	else if (op == 2) {
		filename = "lena-128-gray.ppm";
	}
	else if (op == 3) {
		filename = "lena-512-gray.ppm";
	}
	//��ʼ�����ļ�
	ifs.open(filename);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
	}
	cout << "������Ҫ����ʲô����" << endl;
	cout << "1.�򿪵�ǰͼ���ļ�" << endl;
	cout << "2.ѹ����ǰͼ���ļ�" << endl;
	cout << "3.ת��Ϊ�Ҷ�ͼ��(��ͼר������)" << endl;
	cout << "4.����ͼ��" << endl;
	cout << "5.��ѹ��ǰͼ���ļ�" << endl;
	cout << "6.�򿪱��ͼ���ļ�" << endl;
	cout << "0.�˳�ʹ��" << endl;
	int op2;
	cin >> op2;
	while(op2!=0){
		if (op2 == 1) {
			image = imread(filename);
			namedWindow("Image");
			imshow("Image", image);
			waitKey(0);
		}
		else if (op2 == 2) {
			string t;
			ifs >> t;
			ifs.close();
			ifs.open(filename);
			if (t == "P3") {
				ppm p;
				p = readppmP3(ifs);
				ifs.close();
				ifs.open(filename);
				zipP3(p);
			}
			else if(t=="P2") {
				HuffmanTree my;
				my.Compress(filename,"zipP2.txt");
				cout << "ͼ���ļ�ѹ���ɹ�" << endl;
			}
		}
		else if (op2 == 3) {
			changegrey(ifs);
			cout << " �Ƿ�򿪻Ҷ�ͼ��" << endl;
			cout << " YES or NO" << endl;
			string op5;
			cin >> op5;
			if (op5 == "YES") {
				image = imread("grey.ppm");
				imshow("Grey", image);
				waitKey(0);
			}
			ifs.close();
			ifs.open(filename);
		}
		else if (op2 == 4) {
			cout << " a.�Ŵ�ͼ��2����" << endl;
			cout << " b.��Сͼ��0.5����" << endl;
			image = imread(filename);
			char op4;
			cin >> op4;
			if (op4 == 'a') {
				Mat largeimage;
				Size largesize(0, 0);
				double scale = 2.0;
				cv::resize(image, largeimage, largesize, scale, scale, cv::INTER_LINEAR);
				cv::imshow("Large Image", largeimage);
				cv::waitKey(0);
			}
			else if (op4 == 'b') {
				Mat smallimage;
				Size smallsize(0, 0);
				double scale = 0.5;
				cv::resize(image, smallimage, smallsize, scale, scale, cv::INTER_LINEAR);
				cv::imshow("Small Image", smallimage);
				cv::waitKey(0);
			}
		}
		else if (op2 == 5) {
			string t;
			ifs >> t;
			if (t == "P3") {
				ifstream ifs2("zipP3.txt");
				unzipP3(ifs2);
				ifs2.close();
				cout << " ��ѹ�ɹ���" << endl;
				cout << " �Ƿ�򿪽�ѹ����ļ�" << endl;
				cout << " YES or NO" << endl;
				string op6;
				cin >> op6;
				if (op6 == "YES") {
					image = imread("unzipP3.ppm");
					imshow("Unzip", image);
					waitKey(0);
				}
			}
			else if (t == "P2") {
				HuffmanTree my;
				my.DeCompress("zipP2.txt", "unzipP2.ppm");
				cout << " ��ѹ�ɹ���" << endl;
				cout << " �Ƿ�򿪽�ѹ����ļ�" << endl;
				cout << " YES or NO" << endl;
				string op6;
				cin >> op6;
				if (op6 == "YES") {
					image = imread("unzipP2.ppm");
					imshow("Unzip", image);
					waitKey(0);
				}
			}
			ifs.close();
			ifs.open(filename);
		}
		else if (op2 == 6) {
			cout << "��ѡ����Ҫ�򿪵��ļ���" << endl;
			cout << "1.color-block.ppm" << endl;
			cout << "2.lena-128-gray.ppm" << endl;
			cout << "3.lena-512-gray.ppm" << endl;
			int op3;
			cin >> op3;
			if (op3 == 1) {
				filename = "color-block.ppm";
			}
			else if (op3 == 2) {
				filename = "lena-128-gray.ppm";
			}
			else if (op3 == 3) {
				filename = "lena-512-gray.ppm";
			}
		}
		cout << "������Ҫ����ʲô����" << endl;
		cout << "1.�򿪵�ǰͼ���ļ�" << endl;
		cout << "2.ѹ����ǰͼ���ļ�" << endl;
		cout << "3.ת��Ϊ�Ҷ�ͼ��(��ͼר������)" << endl;
		cout << "4.����ͼ��" << endl;
		cout << "5.��ѹ��ǰͼ���ļ�" << endl;
		cout << "6.�򿪱��ͼ���ļ�" << endl;
		cout << "0.�˳�ʹ��" << endl;
		cin >> op2;
	}
	cout << "��ӭ�ٴ�ʹ��" << endl;
}
