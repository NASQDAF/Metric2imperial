#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <Windows.h>
using namespace std;

void mod1();
void mod2();
void	regget(double& d, std::string& s);
template<typename T> T pow_dec(T a, int b);
template <typename _T> void imp2met(_T imp, string s);
template <typename T1, typename T2> std::map<T2, T1> swapMap(std::map<T1, T2> t);
typedef std::map<std::string, int> SImap;
typedef std::map<int, std::string> ISmap;


SImap SIMetricMap = { 
	{"mm", 1}, 
	{"cm", 2}, 
	{"m", 3}, 
	{"km", 4} 
};
SImap SIImpericMap = {
	{"mil", 1}, 
	{"point", 2}, 
	{"line", 3}, 
	{"inch", 4},
	{"hand", 5},
	{"foot", 6},
	{"yard", 7},
	{"rod", 8},
	{"chain", 9},
	{"furlong", 10},
	{"statute mile", 11},
	{"league", 12} 
};
std::map<int, float> IFImperic2MetricMap = { 
	{1, 0.0254f}, 
	{2, 0.353f}, 
	{3, 2.1167f}, 
	{4, 25.4f},
	{5, 101.6f},
	{6, 304.8f},
	{7, 914.4f},
	{8, 5029.2f},
	{9, 20116.8f},
	{10, 201168.0f},
	{11, 1609344.0f},
	{12,  4828032.0f} 
};

ISmap ISImpericMap = swapMap(SIImpericMap);
ISmap ISMetricMap = swapMap(SIMetricMap);

void main() {
	short gorn = 1;
	while (gorn!=0) {
		cout << "\n\tMod 1: Metric to summary Imperic converter\n\n\tMod 2: Imperic to Metric test\nuser: ";
		cin >>gorn;
		if (gorn == 1) mod1();
		else if (gorn == 2) mod2();
		else Sleep(50);
	}
	system("pause");
}

void	regget(double& d, std::string& s) {

	if (s == "0" || s == "exit") exit(0);
	
	std::string dou, str;
	std::regex 	rs("([A-z])+$");
	std::regex 	rd("(\\d)+((\\.(\\d)+)|((?= )|()))");
	smatch md, ms;

	std::regex_search(s, md, rd);
	std::regex_search(s, ms, rs);

	d = atof(string(md[0]).c_str());
	s = ms[0];
}

template<typename T>
T pow_dec(T a, int b) {
	for (size_t i = 1; i < b; i++)
		a *= 10;
	return a;
}

template <typename T1, typename T2>
std::map<T2, T1> swapMap(std::map<T1, T2> templateMap) {
	std::map<T2, T1> T;
	for (std::pair<T1, T2> i : templateMap)
		T[i.second] = (i.second, i.first);
	return T;
}

template <typename _T> void imp2met(_T imp, string s) {
	auto it = SIMetricMap.find(s);
	double d;
	int i;
	if (it != SIMetricMap.end())
		switch (it->second) {
		default:
			cout << "\nInput valid number\n";
			break;

		case 4:
			imp *= 1000;
		case 3:
			imp *= 100;
		case 2:
			imp *= 10;
			cout << endl;

		case 1: {
			i = imp / 4828032.0f;
			if (i)cout << i << " league" << endl;

			i = (imp -= 4828032 * i) / 1609344.0f;
			if (i)cout << i << " statute mile" << endl;

			i = (imp -= 1609344 * i) / 201168.0f;
			if (i)cout << i << " furlong" << endl;

			i = (imp -= 201168 * i) / 20116.8f;
			if (i)cout << i << " chain" << endl;

			i = (imp -= 20116.8 * i) / 5029.2f;
			if (i)cout << i << " rod" << endl;

			i = (imp -= 5029.2f * i) / 914.4f;
			if (i)cout << i << " yard" << endl;

			i = (imp -= 914.4f * i) / 304.8f;
			if (i)cout << i << " foot" << endl;

			i = (imp -= 304.8f * i) / 101.6f;
			if (i)cout << i << " hand" << endl;

			i = (imp -= 101.6f * i) / 25.4f;
			if (i)cout << i << " inch" << endl;

			i = (imp -= 25.4f * i) / 2.1167f;
			if (i)cout << i << " line" << endl;

			i = (imp -= 2.1167f * i) / 0.353;
			if (i)cout << i << " point" << endl;

			d = (imp - 0.353f * i) / 0.0254;
			cout << d << " mil" << endl << endl;
			break;
		}
		}
}

void mod1() {
	string s;
	double d;
	cout << "Insert metric value\t\tenter 0 to exit\n\n(e.g. 12 mm || 55.3km)\n";
	while (1) {
		s.clear();
		d = 0.0f;
		cout << "\n\tMetric: ";
		cin.ignore();
		getline(cin, s);
		regget(d, s);
		imp2met(d, s);
		system("pause");
		system("cls");
	}
}


void mod2() {
	srand(time(NULL));
	double d;
	while (1) {
		system("cls");

		short _rd = rand() % SIImpericMap.size() + 1, _to = rand() % SIMetricMap.size() + 1;
		std::string imp = ISImpericMap.find(_rd)->second;
		float f = rand() % 10 + 1 * (SIImpericMap.size()+1 - _rd);
		
		cout << "\n Convert " << f << " " << imp << " to " << ISMetricMap.find(_to)->second << "\n\nAnswer:";
		cin >> d;		

		double answer = f * IFImperic2MetricMap.find(_rd)->second/ pow_dec(1, _to);
		double k = f*IFImperic2MetricMap.find(_rd)->second / pow_dec(d, _to);
		
		if (k < 1.05&& k > 0.95)
			cout << "\nGreat\n";
		else
			cout << "\nAnswer:     " << answer << "\nDifference: " << abs(answer-d) << ISMetricMap.find(_to)->second << endl;
		system("pause");
	}
}