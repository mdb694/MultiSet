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

void test_multiset_1() {
	std::cout<<"..............PRIMO TEST MULTISET................."<<std::endl;
	multiset<int, compare_int> ms;

	ms.add(1);
	ms.add(6);
	ms.add(9,3);
	ms.add(8, 4);

	std::cout<<ms<<std::endl;
	std::cout<<"Numero elementi: "<<ms.get_numbelement()<<std::endl;
	std::cout<<"Elemento 1 contenuto? "<<ms.contains(1)<<std::endl;
	std::cout<<"Elemento 2 contenuto? "<<ms.contains(2)<<std::endl;
	std::cout<<"Occorrenze elemento 1: "<<ms.get_occourrence(1)<<std::endl;
	std::cout<<"Occorrenze elemento 2: "<<ms.get_occourrence(2)<<std::endl;

	ms.add(1, 3);
	ms.add(6);
	ms.add(9);
	ms.add(8, 3);

	std::cout<<ms<<std::endl;
	std::cout<<"Numero elementi: "<<ms.get_numbelement()<<std::endl;
	std::cout<<"Occorrenze elemento 1: "<<ms.get_occourrence(1)<<std::endl;
	std::cout<<"Occorrenze elemento 2: "<<ms.get_occourrence(2)<<std::endl;

	multiset<int, compare_int> scms;

	
	scms.add(6,2);
	scms.add(1,4);
	scms.add(8,7);
	scms.add(9,4);

	std::cout<<scms<<std::endl;
	std::cout<<(scms==ms)<<std::endl;

	multiset<int, compare_int> thms;

	
	thms.add(4,2);
	thms.add(3,4);
	thms.add(2,2);
	thms.add(1,4);
	
	std::cout<<thms<<std::endl;
	std::cout<<(thms==ms)<<std::endl;
	
	thms.remove(1);
	std::cout<<thms<<std::endl;
	thms.remove(2);
	thms.remove(2);
	std::cout<<thms<<std::endl;

	thms.remove(3,4);
	std::cout<<thms<<std::endl;
	
	std::cout<<ms<<std::endl;
	typename multiset<int,compare_int>::const_element_iterator i,ie;
	for(i=ms.elem_begin(), ie=ms.elem_end();i!=ie;++i)
		std::cout<<*i<<", ";
	std::cout<<std::endl;

	std::cout<<ms<<std::endl<<std::endl<<std::endl;
}

void test_multiset_2() {
	std::cout<<"..............SECONDO TEST MULTISET................."<<std::endl;

	multiset<std::string, compare_string> msstring;

	msstring.add("pippo",6);
	msstring.add("pluto",2);
	msstring.add("paperino",3);
	msstring.add("minni",9);

	std::cout<<msstring<<std::endl;
	typename multiset<std::string,compare_string>::const_element_iterator i,ie;
	for(i=msstring.elem_begin(), ie=msstring.elem_end();i!=ie;++i)
		std::cout<<*i<<", ";
	std::cout<<std::endl;
}



int main() {
	test_multiset_1();
	test_multiset_2();

	return 0;
}
