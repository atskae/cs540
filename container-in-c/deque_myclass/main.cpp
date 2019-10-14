#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>

#include "Deque_MyClass.hpp"

bool compare(const MyClass& x, const MyClass& y) {
	return x.id > y.id;
}

int main() {

	{
		Deque_MyClass deq;
		Deque_MyClass_ctor(&deq, MyClass_less_by_id);

		deq.push_front(&deq, MyClass{30, "Lilycove"});
		deq.push_front(&deq, MyClass{0, "Rustburo"});
		deq.push_front(&deq, MyClass{5, "Sootopolis"});
		deq.push_front(&deq, MyClass{1, "Littleroot"});
		//deq.push_front(&deq, MyClass{25, "Oldale"});

		printf("Before sort\n");
		deq.print(&deq);

		deq.sort(&deq, deq.begin(&deq), deq.end(&deq));

		printf("After sort\n");
		deq.print(&deq);

		Deque_MyClass_dtor(&deq);
	}

	{
		Deque_MyClass deq;
		Deque_MyClass_ctor(&deq, MyClass_less_by_name);

		deq.push_back(&deq, MyClass{30, "Lilycove"});
		deq.push_back(&deq, MyClass{0, "Rustburo"});
		deq.push_front(&deq, MyClass{7, "Dewford"});
		deq.push_back(&deq, MyClass{5, "Sootopolis"});
		deq.push_back(&deq, MyClass{1, "Littleroot"});
		deq.push_back(&deq, MyClass{25, "Oldale"});


		printf("Before sort\n");
		deq.print(&deq);

		//deq.sort(&deq, deq.begin(&deq), deq.end(&deq));
		//printf("After sort\n");
		//deq.print(&deq);

		MyClass_print(&deq.at(&deq, 0));
		Deque_MyClass_Iterator it = deq.begin(&deq);
		it.inc(&it);
		it.inc(&it);
		it.dec(&it);
		it.dec(&it);
		//it.dec(&it);
		it.inc(&it);
		it.inc(&it);
		it.inc(&it);
		it.inc(&it);
		it.inc(&it);
		it.inc(&it);
		it.inc(&it);
		it.dec(&it);

		//it.dec(&it);
		//it.dec(&it);
	//	it.dec(&it);


		MyClass_print(&it.deref(&it));
		printf("it->index=%i, it->num_to_end=%i\n", it.index, it.num_to_end);

		Deque_MyClass_dtor(&deq);
	}

	printf("A Deque (non-macro version)\n");	
    Deque_MyClass deq;
    Deque_MyClass_ctor(&deq, MyClass_less_by_id);

    assert(deq.size(&deq) == 0);
    // size() should return a size_t.
    assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
    assert(deq.empty(&deq));

    // Should print "---- Deque_MyClass, 14".
    printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
    // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
    assert(sizeof deq.type_name == 14);

    deq.push_back(&deq, MyClass{1, "Joe"});
    deq.push_back(&deq, MyClass{2, "Mary"});
    deq.push_back(&deq, MyClass{3, "Tom"});
    deq.push_front(&deq, MyClass{0, "Mike"});
    deq.push_front(&deq, MyClass{-1, "Mary"});

    MyClass_print(&deq.front(&deq));
    MyClass_print(&deq.back(&deq));
    assert(deq.front(&deq).id == -1);
    assert(deq.back(&deq).id == 3);

    deq.pop_front(&deq);
    deq.pop_back(&deq);
    assert(deq.front(&deq).id == 0);
    assert(deq.back(&deq).id == 2);

    assert(deq.size(&deq) == 3);

    for (Deque_MyClass_Iterator it = deq.begin(&deq);
     !Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
        MyClass_print(&it.deref(&it));
    }

//	printf("==Multiple Iterators==\n");

    // Multiple iterators?
    for (Deque_MyClass_Iterator it1 = deq.begin(&deq);
     !Deque_MyClass_Iterator_equal(it1, deq.end(&deq)); it1.inc(&it1)) {
        MyClass_print(&it1.deref(&it1));
        for (Deque_MyClass_Iterator it2 = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it2, deq.end(&deq)); it2.inc(&it2)) {
            MyClass_print(&it2.deref(&it2));
            for (Deque_MyClass_Iterator it3 = deq.begin(&deq);
             !Deque_MyClass_Iterator_equal(it3, deq.end(&deq)); it3.inc(&it3)) {
                MyClass_print(&it3.deref(&it3));
            }
        }
    }

	// Test decrement of end.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
        }

        // printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            MyClass_print(&deq.at(&deq, i));
        }

	assert(deq.at(&deq, 0).id == 0);
        deq.at(&deq, 0).id = 100;
        assert(deq.at(&deq, 0).id == 100);
        // Change via front().
        assert(deq.front(&deq).id == 100);
        deq.front(&deq).id = 0;
        assert(deq.front(&deq).id == 0);
        assert(deq.at(&deq, 0).id == 0); // Verify with at() also.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
            it.deref(&it).id = 200;
            assert(it.deref(&it).id == 200);
            // Change using back().
            assert(deq.back(&deq).id == 200);
            deq.back(&deq).id = 2;
            assert(deq.back(&deq).id == 2);
            assert(it.deref(&it).id == 2); // Verify with iterator also.
        }
	deq.clear(&deq);
	Deque_MyClass_dtor(&deq);

	    {
            Deque_MyClass deq1, deq2;
            Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
            Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

            deq1.push_back(&deq1, MyClass{1, "Joe"});
            deq1.push_back(&deq1, MyClass{2, "Jane"});
            deq1.push_back(&deq1, MyClass{3, "Mary"});
            deq2.push_back(&deq2, MyClass{1, "Joe"});
            deq2.push_back(&deq2, MyClass{2, "Jane"});
            deq2.push_back(&deq2, MyClass{3, "Mary"});

            assert(Deque_MyClass_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_MyClass_equal(deq1, deq2));
            deq1.push_back(&deq1, MyClass{4, "Mary"});
            assert(!Deque_MyClass_equal(deq1, deq2));

            deq1.dtor(&deq1);
            deq2.dtor(&deq2);
        }


    // Test sort with different comparators.
    {
        Deque_MyClass sort_by_id, sorted_by_id;
        Deque_MyClass sort_by_name, sorted_by_name;

        Deque_MyClass_ctor(&sort_by_id, MyClass_less_by_id);
        Deque_MyClass_ctor(&sorted_by_id, MyClass_less_by_id);
        Deque_MyClass_ctor(&sort_by_name, MyClass_less_by_name);
        Deque_MyClass_ctor(&sorted_by_name, MyClass_less_by_name);

        sort_by_id.push_back(&sort_by_id, MyClass{1, "Bob"});
        sort_by_id.push_back(&sort_by_id, MyClass{3, "Sheldon"});
        sort_by_id.push_back(&sort_by_id, MyClass{2, "Alex"});

        sorted_by_id.push_back(&sorted_by_id, MyClass{1, "Bob"});
        sorted_by_id.push_back(&sorted_by_id, MyClass{2, "Alex"});
        sorted_by_id.push_back(&sorted_by_id, MyClass{3, "Sheldon"});

		sort_by_name.push_back(&sort_by_name, MyClass{5, "Pikachu"});
        sort_by_name.push_back(&sort_by_name, MyClass{1, "Bob"});
        sort_by_name.push_back(&sort_by_name, MyClass{4, "Xerxes"});
		sort_by_name.push_back(&sort_by_name, MyClass{3, "Sheldon"});
        sort_by_name.push_back(&sort_by_name, MyClass{2, "Alex"});

        sorted_by_name.push_back(&sorted_by_name, MyClass{2, "Alex"});
        sorted_by_name.push_back(&sorted_by_name, MyClass{1, "Bob"});
		sorted_by_name.push_back(&sorted_by_name, MyClass{5, "Pikachu"});
		sorted_by_name.push_back(&sorted_by_name, MyClass{3, "Sheldon"});
		sorted_by_name.push_back(&sorted_by_name, MyClass{4, "Xerxes"});

	
		assert(!Deque_MyClass_equal(sort_by_id, sorted_by_id));
        sort_by_id.sort(&sort_by_id, sort_by_id.begin(&sort_by_id), sort_by_id.end(&sort_by_id));
		sort_by_id.print(&sort_by_id);
		assert(Deque_MyClass_equal(sort_by_id, sorted_by_id));

		printf("Testing name\n");
		sort_by_name.print(&sort_by_name);
        sorted_by_name.print(&sorted_by_name);
       
	 	assert(!Deque_MyClass_equal(sort_by_name, sorted_by_name));
        sort_by_name.sort(&sort_by_name, sort_by_name.begin(&sort_by_name), sort_by_name.end(&sort_by_name));
        
		printf("AFter sorting by name\n");	
		sort_by_name.print(&sort_by_name);
        sorted_by_name.print(&sorted_by_name);

		assert(Deque_MyClass_equal(sort_by_name, sorted_by_name));
	
		
        sort_by_id.dtor(&sort_by_id);
        sorted_by_id.dtor(&sorted_by_id);
        sort_by_name.dtor(&sort_by_name);
        sorted_by_name.dtor(&sorted_by_name);
    }

	printf("======TESTING push_back===========\n");

	{
		Deque_MyClass sort_by_id, sorted_by_id;
        Deque_MyClass sort_by_name, sorted_by_name;

        Deque_MyClass_ctor(&sort_by_id, MyClass_less_by_id);
        Deque_MyClass_ctor(&sorted_by_id, MyClass_less_by_id);
        Deque_MyClass_ctor(&sort_by_name, MyClass_less_by_name);
        Deque_MyClass_ctor(&sorted_by_name, MyClass_less_by_name);

		sort_by_name.push_back(&sort_by_name, MyClass{5, "Pikachu"});
        sort_by_name.push_back(&sort_by_name, MyClass{1, "Bob"});
        sort_by_name.push_back(&sort_by_name, MyClass{4, "Xerxes"});
		sort_by_name.push_back(&sort_by_name, MyClass{3, "Sheldon"});
        sort_by_name.push_back(&sort_by_name, MyClass{2, "Alex"});
		sort_by_name.push_back(&sort_by_name, MyClass{2, "Emerald"});
		sort_by_name.push_back(&sort_by_name, MyClass{3, "Sapphire"});
        sort_by_name.push_back(&sort_by_name, MyClass{2, "Alex"});
		sort_by_name.push_front(&sort_by_name, MyClass{2, "Elizabeth"});

		sort_by_name.print(&sort_by_name);

		//sort
		sort_by_name.sort(&sort_by_name, sort_by_name.begin(&sort_by_name), sort_by_name.end(&sort_by_name));
		sort_by_name.print(&sort_by_name);


		sort_by_id.dtor(&sort_by_id);
        sorted_by_id.dtor(&sorted_by_id);
        sort_by_name.dtor(&sort_by_name);
        sorted_by_name.dtor(&sorted_by_name);

	}

    //// Sorting Test 2
    {
       Deque_MyClass deq1;
       Deque_MyClass_ctor(&deq1, MyClass_less_by_id);

       for (int i=0;i<10000;i++) {
           deq1.push_back(&deq1, MyClass{i, "Dummy"});
       }

       for (int i=20000;i>=10000;i--) {
           deq1.push_back(&deq1, MyClass{i, "Dummy"});
       }

       deq1.push_back(&deq1, MyClass{20001, "Dummy"});

       auto iter1 =  deq1.end(&deq1);
       iter1.dec(&iter1);	
       
       auto iter2 = deq1.begin(&deq1);
       
       for (int i=0;i<10000;i++) {
           iter2.inc(&iter2);
       }

		
		//printf("deq1 before sorting\n");
		//deq1.print(&deq1);
		
				
		deq1.sort(&deq1, iter2,iter1);

       Deque_MyClass deq2;
       Deque_MyClass_ctor(&deq2 , MyClass_less_by_id);

       for(int i=0;i<=20001;i++) {
           deq2.push_back(&deq2, MyClass{i, "Dummy"});
       }
		
        //printf("deq1 after sorting\n");
		//deq1.print(&deq1);
		//fflush(stdout);
		//
		//printf("deq2\n");
		//deq2.print(&deq2);

      assert(Deque_MyClass_equal(deq1, deq2)); 

      deq1.dtor(&deq1);
      deq2.dtor(&deq2);
    }

	return 0;
}
