#include <iostream>
#include <vector>

using namespace std;

int main() {
	
	cout << "Practicing with lambdas" << endl;

	/*
		lambda format
		[ capture clause ] (parameters) -> return type { function body }
	*/
	
	vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int>::iterator p = find_if(nums.begin(), nums.end(), [](int i) -> bool { return i > 4; }); // lambda here!
	while(p != nums.end()) {
		cout << *p << endl;
		p++;
	}

	// captures allow variables to be grabbed from surrounding scope ; captures the value when the lambda is created
	char c = 0;
	
	// capture by value
	cout << "Capture by value" << endl;
	auto cap = [c]() { cout << "Inside lambda, c=" << c << endl; }; // create time here ; captures 'c'
	for(int i=0; i<10; i++) {
		cout << "---Iteration " << i << "---" << endl;
		c = c + i; // does not change the captured value in lambda
		cout << "Outside lambda, c=" << c << endl;
		cap(); // see for yourself ; always prints the original capture value 'a', even though variable c is changed
	}

	// capture by reference
	cout << "Capture by reference" << endl;
	auto cap_ref = [&c]() { cout << "Inside lambda, c=" << c << endl; };
	for(int i=0; i<10; i++) {
		cout << "---Iteration " << i << "---" << endl;
		c = c + i; 
		cout << "Outside lambda, c=" << c << endl;
		cap_ref(); 
	}

	return 0;
}
