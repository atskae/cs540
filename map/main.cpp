#include <stdio.h>
#include <string>
#include <map>

#include "Map.hpp"

using namespace std;

struct Person {
    string name;
    int age;
};

int main() {
    cs540::Map<const Person, int> pmap;
    
    cs540::Map<string, int> mymap;

    pair<string, int> p1;
    p1.first = "Atsuko";
    p1.second = 25;

    pair<string, int> p2;
    p2.first = "Tyrone";
    p2.second = 42;

    pair<string, int> p3;
    p3.first=  "Skylake";
    p3.second = 2;

    pair<string, int> p4;
    p4.first=  "May";
    p4.second = 47;

    pair<string, int> p5;
    p5.first = "Poland";
    p5.second = 54;

    pair<string, int> p6;
    p6.first = "Nauru";
    p6.second = 10;

    pair<string, int> p7;
    p7.first = "Pikachu";
    p7.second = 25;

    mymap.insert(p1);
    mymap.insert(p7);
    mymap.insert(p4);
    mymap.insert(p2);
    mymap.insert(p3);
    mymap.insert(p1); // attempt to insert again
    mymap.insert(p5);
    mymap.insert(p6);
    mymap.insert(p4); // attempt to insert again
    mymap.print();

    cs540::Map<string, int>::Iterator it = mymap.find("Poland");
    it->second = 888;

    // Create a const version of this mymap
    const cs540::Map<string, int> const_mymap(mymap);
    cs540::Map<string, int>::ConstIterator const_it = const_mymap.begin();

    // forwards
    printf("Goin` forwards\n");
    while(const_it != const_mymap.end()) {
        std::cout << "key=" << const_it->first << std::endl;
        const_it++;
    }
    // background
    printf("Goin` backwards\n");
    const_it = const_mymap.end();
    const_it--;
    while(const_it != const_mymap.end()) {
        pair<string, int> key_val = *const_it;
        std::cout << "key=" << key_val.first << ", value=" << const_it->second << std::endl;
        const_it--;
    }

    printf("Reverse iterator\n");
    cs540::Map<string, int>::ReverseIterator rit = mymap.rbegin();
    while(rit != mymap.end()) {
        pair<string, int> key_val = *rit;
        std::cout << "key=" << key_val.first << ", value=" << rit->second << std::endl;
        rit--;
    }
    it = mymap.end();
    it--;
    rit++; // point to last element

    printf("comparing it and rit %d\n", it == rit);

    vector<pair<string, int>> vec;
    vec.push_back(p1);
    vec.push_back(p5);
    vec.push_back(p2);
    vec.push_back(p7);
   
    printf("Inserting using a vector iterator\n"); 
    cs540::Map<string, int> vec_mymap;
    vec_mymap.insert(vec.begin(), vec.end());
    //vec_mymap.print();

    printf("compare maps: %d\n", vec_mymap < mymap);
    mymap.print();
    vec_mymap.print();

    //printf("Testing copy assignemnt\n");
    //mymap.print();
    //vec_mymap.print();
    //mymap = vec_mymap;
    //mymap.print();
    
    // copy assignment ; what does a normal mymap do?
    //map<string, int> first;
    //map<string, int> second;
    //first["Bob"] = 2;
    //first["Arthur"] = 7;
    //first["Torres"] = 1;

    //second = first;
    //first["Richard"] = 77;
    //first["William"] = 222;

    //printf("First\n");
    //for(auto pair : first) {
    //    cout << pair.first << "," << pair.second << endl;
    //}

    //printf("Second\n");
    //for(auto pair : second) {
    //    cout << pair.first << "," << pair.second << endl;
    //}

    //printf("Initialize with list\n");
    ////vector<pair<string, int>> init_list;
    ////init_list.push_back(p1);
    ////init_list.push_back(p2);
    //cs540::Map<string, int> mymap_list({ {"djibouti", 11}, {"bulgaria", 13444}, {"lisa", 1}, {"tomato", 222}, {"alfred", 21}, {"eggplant", 1}});
    //mymap_list.print();

    //it = mymap.find("Skylake");
    //it = mymap.find("May");
    //it = mymap.find("Tyrone");
    //it = mymap.find("Misty");   
    //it = mymap.find("Pikachu");   
    //mymap.erase(it);
    //
    //it = mymap.find("Poland");
    //mymap.erase(it);

    //mymap.erase("Nauru");
    //mymap.erase("May");
    ////mymap.erase("Misty"); // fails

    //mymap["Raymondo"] = 12;
    //mymap["Raymondo"] = 17;
    //
    //cs540::Map<string, int>::Iterator it2 = mymap.find("Raymondo");
    //printf("Const Iterator for Raymondo.\n");
    ////cs540::Map<string, int>::ConstIterator itc = mymap.find("Raymondo");
    //
    //mymap.print();

    //printf("Matching iterators? %d\n", it == it2);
 
    //cs540::Map<string, int> mymap2;
    //mymap2.insert(p7);
    //mymap2.insert(p2);
    //mymap2.insert(p3);
    //mymap2.insert(p4);
    //mymap2.insert(p5);
    //mymap2.print();
    //
    //printf("Matching mymaps? %d\n", mymap == mymap2);

    //cs540::Map<string, int> mymap3;
    //cs540::Map<string, int> mymap4;

    //mymap3.insert(p7);
    //mymap4.insert(p7);

    //mymap3["Cat"] = 25;
    //mymap4["Cat"] = 25;

    //printf("Matching mymaps? 3&4 = %d\n", mymap3 == mymap4);
    //mymap3.print();

    //cs540::Map<string, int> mymap5(mymap3);
    //printf("Copied mymap\n");
    //mymap5.print();

    ////int mymapped = mymap.at("Pikachu");
    ////printf("pikachu mymapped=%d\n", mymapped);

    //const cs540::Map<string, int> mymap6(mymap2);
    //const int mymapped2 = mymap6.at("Pikachu");
    //printf("Pikachu const mymapped=%d\n", mymapped2);

    //cs540::Map<string, int>::ConstIterator itc2 = mymap6.find("Pikachu");
    //std::cout << "from const iterator got " << (*itc2).second << std::endl;  
    //std::cout << "from const iterator, with at() got " << mymap6.at("Pikachu") << std::endl;  

    //printf("Clearing mymap\n");
    //mymap.clear();
    //mymap.print();

    //mymapped = mymap.at("Totadile"); // should fail

    return 0;
}
