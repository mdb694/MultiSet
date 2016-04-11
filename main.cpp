#include <iostream>
#include "multiset.h"

struct compare_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

struct compare_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return ucase(a)==ucase(b);
	}
private:
	std::string ucase(const std::string &str) const {
		std::string tmp(str);
		for(int i=0; i< tmp.size(); ++i)
			tmp[i]=std::toupper(tmp[i]);
	
		return tmp;
	}	
};

//................................................//............................//..............

void test_maultiset_1() {
	std::cout<<"..............PRIMO TEST MULTISET................."<<std::endl;
	multiset<int, compare_int> ms;

	ms.add(1);
	ms.add(6);
	ms.add(9,3);
	ms.add(8, 4);

	std::cout<<ms<<std::endl;

	ms.add(1, 3);
	ms.add(6);
	ms.add(9);
	ms.add(8, 3);

	std::cout<<ms<<std::endl;
}



int main() {
	test_maultiset_1();
//	test_maultiset_2();

	return 0;
}
