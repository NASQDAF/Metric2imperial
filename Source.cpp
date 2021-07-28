#include <iostream>
#include <string>
#include <regex>
using namespace std;

void	regget(double& d, std::string& s);
template <typename _T> void imp2met(_T imp, string s);


void main() {
	string s;
	double d;
	cout << "Insert metric value\t\tenter 0 to exit\n\n(e.g. 12 mm || 55.3km)\n";
	while (1) {
		s.clear();
		d = 0.0f;
		cout << "\n\tMetric: ";
		getline(cin, s);
		regget(d, s);
		imp2met(d, s);
	}
	system("pause");
}

void	regget(double& d, std::string& s) {

	if (s == "0") exit(0);
	
	std::string dou, str;
	std::regex 	rs("([A-z])+$");
	std::regex 	rd("(\\d)+((\\.(\\d)+)|((?= )|()))");
	smatch md, ms;

	std::regex_search(s, md, rd);
	std::regex_search(s, ms, rs);

	d = atof(string(md[0]).c_str());
	s = ms[0];
}

template <typename _T> void imp2met(_T imp, string s) {
	short sh = 0;
	sh = s == "mm" ? 1 :
		s == "cm" ? 2 :
		s == "m" ? 3 :
		s == "km" ? 4 : 0;
	double d;
	int i;
	switch (sh) {
	default:
		cout << "\nInput valid number\n";
		break;

	case 4:
		imp *= 1000;
		cout << endl;
	case 3:
		imp *= 100;
		cout << endl;
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