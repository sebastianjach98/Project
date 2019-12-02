// Sebastian Jach
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "structures.h"

const int seed = 373;

int main()
{
	std::mt19937 gen(seed);						// random number generator 
	std::ofstream output("output.txt");			// output to file
	std::ifstream input("text.txt");			// input from file
	std::string text;

	// structure declarations 
	LinkedList sll, sll1, sll2, sll3;
	DoublyList dll, dll1, dll2, dll3;
	CircularList cll, cll1, cll2, cll3;
	Stack stack, stack1, stack2, stack3;
	Queue queue, queue1, queue2, queue3;

	output << "Sebastian Jach" << std::endl;
	output << "Prof. McFarland" << std::endl;
	output << "Assignment 1" << std::endl << std::endl;

	// linked list 
	output << "-----------------------------------------------------------" << std::endl;
	output << "Linked list" << std::endl;
	output << "-----------------------------------------------------------" << std::endl;

	fillList(sll, gen);							// passing by reference, fillList() in functions.h
	sll.printList(output);						// printing list

	sll.printSize(output);						// printing size

	output << "Low to high: " << std::endl;
	sll.lowHigh(sll.getSize());					// sorting low to high, passing int of linked list size
	sll.printList(output);

	output << "High to low: " << std::endl;
	sll.highLow(sll.getSize());					// sorting high to low
	sll.printList(output);

	sll.empty();								// deleting sll
	sll.printSize(output);						// printing size

	// doubly linked list
	output << "------------------------------------------------------------" << std::endl;
	output << "Doubly list" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	fillList(dll, gen);	
	dll.printList(output);

	dll.printSize(output);

	output << "Low to high: " << std::endl;
	dll.lowHigh(dll.getSize());	
	dll.printList(output);

	output << "High to low: " << std::endl;
	dll.highLow(dll.getSize());		
	dll.printList(output);

	dll.empty();					
	dll.printList(output);

	// circular list
	output << "------------------------------------------------------------" << std::endl;
	output << "Circular list" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	fillList(cll, gen);				
	cll.printList(output);

	output << "Low to high: " << std::endl;
	cll.lowHigh(cll.getSize());		
	cll.printList(output);

	output << "High to low: " << std::endl;
	cll.highLow(cll.getSize());		
	cll.printList(output);

	cll.empty();
	cll.printList(output);
	
	// stack
	output << "------------------------------------------------------------" << std::endl;
	output << "Stack" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	fillStack(stack);					// passing by reference 	
	stack.shuffleDeck(1, gen);			// passing 1 to be incremented for recursion 
	stack.printHand(output);

	stack.empty();
	output << std::endl << std::endl;
	stack.printStack(output);

	// queue
	output << std::endl;
	output << "------------------------------------------------------------" << std::endl;
	output << "Queue" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	fillQueue(queue, input, text); 		// passing by reference
	queue.print(output);

	queue.alphabetize();				// sorting
	output << std::endl << "Alphabetized:" << std::endl;
	queue.print(output);

	queue.empty();
	queue.printSize(output);
	output << std::endl << std::endl;
	
	// demo of the remainding functions
	output << "------------------------------------------------------------" << std::endl;
	output << "Demo(all functions)" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	// linked list
	output << std::endl << "Linked list" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	sll1.addToHead(1);
	output << "sll1.addToHead(1):				";
	sll1.printList(output);

	sll1.addToTail(2);
	output << "sll1.addToTail(2):				";
	sll1.printList(output);

	sll1.addToPosition(8, 2);
	output << "sll1.addToPosition(8, 2):		";
	sll1.printList(output);

	sll1--;
	output << "sll1--:							";
	sll1.printList(output);

	sll2++;
	output << "sll2++:							";
	sll2.printList(output);

	sll2.addToTail(2);
	output << "sll2.addToTail(2):				";
	sll2.printList(output);
	
	sll3 = sll1 + sll2;
	output << "sll3 = sll1 + sll2:				";
	sll3.printList(output);

	output << "sll3.search(output, 2):			";
	sll3.search(output, 2);
	
	sll3.deleteFromPosition(2);
	output << "sll3.deleteFromPosition(2):		";
	sll3.printList(output);
	
	sll3.deleteFromTail();
	output << "sll3.deleteFromTail():			";
	sll3.printList(output);

	sll3.deleteFromHead();
	output << "sll3.deleteFromhead():			";
	sll3.printList(output);

	sll3.empty();
	output << "sll3.empty():					";
	sll3.printSize(output);
	
	// doubly linked list
	output << "Doubly list" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	dll1.addToHead(1);
	output << "dll1.addToHead(1):				";
	dll1.printList(output);

	dll1.addToTail(2);
	output << "dll1.addToTail(2):				";
	dll1.printList(output);

	dll1.addToPosition(8, 2);
	output << "dll1.addToPosition(8, 2):		";
	dll1.printList(output);

	dll1--;
	output << "dll1--:							";
	dll1.printList(output);

	dll2++;
	output << "dll2++:							";
	dll2.printList(output);

	dll2.addToTail(2);
	output << "dll2.addToTail(2):				";
	dll2.printList(output);

	dll3 = dll1 + dll2;
	output << "dll3 = dll1 + dll2:				";
	dll3.printList(output);

	output << "dll3.search(8):					";
	dll3.search(output, 8);

	dll3.deleteFromPosition(2);
	output << "dll3.deleteFromPosition(2):		";
	dll3.printList(output);

	dll3.deleteFromTail();
	output << "dll3.deleteFromTail():			";
	dll3.printList(output);

	dll3.deleteFromHead();
	output << "dll3.deleteFromHead():			";
	dll3.printList(output);

	dll3.empty();
	output << "dll3.empty():					";
	dll3.printList(output);

	// circular list
	output << "Circular list" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	cll1.addToHead(1);
	output << "cll1.addToHead(1):				";
	cll1.printList(output);

	cll1.addToTail(2);
	output << "cll1.addToTail(2):				";
	cll1.printList(output);

	cll1.addToPosition(8, 2);
	output << "cll1.addToPosition(8, 2):		";
	cll1.printList(output);

	cll1--;
	output << "cll1--:							";
	cll1.printList(output);

	cll2++;
	output << "cll2++:							";
	cll2.printList(output);

	cll2.addToTail(2);
	output << "cll2.addToTail(2):				";
	cll2.printList(output);

	cll3 = cll1 + cll2;
	output << "cll3 = cll1 + cll2:				";
	cll3.printList(output);

	output << "cll3.search(55):				";
	cll3.search(output, 55);

	cll3.deleteFromPosition(2);
	output << "cll3.deleteFromPosition(2):		";
	cll3.printList(output);

	cll3.deleteFromTail();
	output << "cll3.deleteFromTail():			";
	cll3.printList(output);

	cll3.deleteFromHead();
	output << "cll3.deleteFromHead():			";
	cll3.printList(output);

	cll3.empty();
	output << "cll3.empty():					";
	cll3.printList(output);


	// stack
	output << "Stack" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	stack1.push(1, 1, 1, 1);
	output << "stack1.push(1, 1, 1, 1):" << std::endl;
	stack1.printStack(output);

	stack2.push(2, 2, 2, 2);
	output << std::endl << "stack2.push(2, 2, 2, 2):" << std::endl;
	stack2.printStack(output);

	stack2++;
	output << std::endl << "stack2++:" << std::endl;
	stack2.printStack(output);

	output << std::endl << "stack2.search(output, 2, 2, 2): ";
	stack2.search(output, 2, 2, 2);

	stack3 = stack1 + stack2;
	output << std::endl << "stack3 = stack1 + stack2:" << std::endl;
	stack3.printStack(output);

	stack3.lowHigh(stack3.getSize());
	output << std::endl << "stack3.lowHigh(stack3.getSize()):" << std::endl;
	stack3.printStack(output);

	stack3.highLow();
	output << std::endl << "stack3.highLow(stack3.highLow()): " << std::endl;
	stack3.printStack(output);




	stack3.pop();
	output << std::endl << "stack3.pop():" << std::endl;
	stack3.printStack(output);

	stack3--;
	output << std::endl << "stack3--:" << std::endl;
	stack3.printStack(output);

	stack3.empty();
	output << std::endl << "stack3.empty(): ";
	stack3.printStack(output);
	output << std::endl;

	// Queue
	output << "Queue" << std::endl;
	output << "------------------------------------------------------------" << std::endl;

	queue1.enqueue('a');
	output << "queue1.enqueue(a):				";
	queue1.print(output);
	
	queue1.enqueue('b');
	output << "queue1.enqueue(b):				";
	queue1.print(output);

	queue1.enqueue('b');
	output << "queue1.enqueue(b):				";
	queue1.print(output);

	output << "queue1.search(output, 'b'):		";
	queue1.search(output, 'b');

	queue2.enqueue('e');
	output << "queue2.enqueue('e'):			";
	queue2.print(output);

	queue2++;
	output << "queue2++:						";
	queue2.print(output);

	queue3 = queue1 + queue2;
	output << "queue3 = queue1 + queue2:		";
	queue3.print(output);

	output << std::endl;
	queue3.printSize(output);
	output << std::endl;

	queue3++;
	output << "queue3++:						";
	queue3.print(output);

	output << "queue3.print(output):			";
	queue3.print(output);

	queue3--;
	output << "queue3--:						";
	queue3.print(output);

	queue3.empty();
	queue3.print(output);

	output.close();

	return 0;
}