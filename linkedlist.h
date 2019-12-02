// Sebastian Jach
#pragma once

extern const int seed;

struct SLLNode
{
	int number, position;					// each SLLNode holds a number and position,
	SLLNode *next;							// as well as a pointer to the next node in the list

	SLLNode(int, int, SLLNode*);			
};

// if nextPointer is not specified, nullptr is assigned 
SLLNode::SLLNode(int num, int pos, SLLNode *nextPointer = nullptr)
{
	number = num;
	position = pos;
	next = nextPointer;
}

struct LinkedList
{
	private:
		int size;						
		SLLNode *head, *tail;				

	public:
		LinkedList();
		int getSize();
		void empty();
		void addToHead(int);
		void addToTail(int);
		void addToPosition(int, int);
		void deleteFromHead();
		void deleteFromTail();
		void deleteFromPosition(int);
		void search(std::ofstream&, int);
		void printSize(std::ofstream&);
		void printList(std::ofstream&);
		void lowHigh(int);
		void highLow(int);
		friend LinkedList operator + (const LinkedList& passed, const LinkedList& passed2);
		LinkedList operator ++ (int);
		LinkedList operator -- (int);
};

LinkedList::LinkedList()
{
	size = 0;
	head = tail = nullptr;
}

int LinkedList::getSize()
{
	return size;
}

void LinkedList::empty()
{
	// exception handeling 
	try
	{
		if (size < 1)
			throw;
	}
	catch (...)
	{
		std::cout << "List is already empty...";
	}

	if (size == 1)
	{
		delete head, tail;
		size--;
	}
	else
	{
		SLLNode *tmp = head;					// used to iterate through list

		// tmp iterates through list from head node
		while (tmp->next != nullptr)
		{
			head = head->next;					// head is set to next node
			delete tmp;							// tmp pointing to old head node is deleted
			tmp = head;							// tmp is set to new head node
			size--;
		}

		size--;
		delete tmp, head, tail;					// since tmp points to last node
	}
}

void LinkedList::search(std::ofstream& output, int num)
{
	int number, count = 0;						// counter starts at 0
	SLLNode *tmp = head;						// used to iterate through list
	LinkedList instances;						// used for storing positions 

	if (size == 0)
		std::cout << "Empty list..." << std::endl;
	else
	{
		number = num;
		tmp = head;

		// iterates through list and if match is found, the position is added to a new linked list 
		for (int i = 1; i <= size; i++)
		{
			if (tmp->number == num)
			{
				instances.addToTail(tmp->position);
				count++; 
			}

			tmp = tmp->next;
		}

		delete tmp;
	}

	if (count == 0)
		output << "Number of instances: " << count << std::endl;
	else
	{ 
		output << "Instances: " << count << " /" << " Locations: ";
		instances.printList(output);
	}
}


void LinkedList::printSize(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty..." << std::endl << std::endl;
	else
		output << "Size: " << size << std::endl << std::endl;
}

void LinkedList::printList(std::ofstream& output)
{
	// exception handeling if size is 0 
	try
	{
		if (size == 0)
			throw size;
	}
	catch (...)
	{
		printSize(output);
	}

	SLLNode *tmp = head;

	for (int i = 1; i <= size; i++)
	{
		output << tmp->number << " ";

		// used for formatting
		if (i % 20 == 0)
			output << std::endl;

		tmp = tmp->next;
	}

	output << std::endl;

	tmp = nullptr;
	delete tmp;
}

void LinkedList::addToHead(int num)
{
	if (size == 0)
		head = tail = new SLLNode(num, ++size); 
	else
	{
		SLLNode *tmp = head;

		head = new SLLNode(num, 1, head);			// head points to previous head
		tmp->position++;							// old head node position is updated 

		// updates positions 
		while (tmp->next != nullptr)	
		{
			tmp = tmp->next;
			tmp->position++;
		}

		size++;

		tmp = nullptr;
		delete tmp;		
	}
}

void LinkedList::addToTail(int num)
{
	if (size == 0)
		head = tail = new SLLNode(num, ++size);
	else
	{
		tail->next = new SLLNode(num, ++size);
		tail = tail->next;
	}
}

void LinkedList::addToPosition(int num, int pos)
{
	SLLNode *tmp = head;		
	SLLNode *tmp2 = head->next; 

	// iterates until tmp2 points to position of insertion 
	while (tmp2->position != pos) 
	{
		tmp = tmp2;									// tmp trails behind tmp2 
		tmp2 = tmp2->next;
	}

	tmp->next = new SLLNode(num, pos, tmp2);		// tmp points to a new node which points to tmp2 
	tmp2->position++;								// tmp2 position is updated 

	// updates remaining list positons 
	while (tmp2->next != nullptr)			 
	{
		tmp2 = tmp2->next;
		tmp2->position++;
	}

	size++;

	tmp = tmp2 = nullptr;
	delete tmp, tmp2;			
}

void LinkedList::deleteFromHead()
{
	if (size == 0)
		std::cout << "List is empty." << std::endl;
	else
	{
		if (size == 1)
			head = tail = nullptr;
		else
		{
			SLLNode *tmp = head;

			head = head->next;					// head is set to next node
			head->position = 1;					// makes position of head 1 

			delete tmp;
			tmp = head;

			// updates remaining list positions 
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
				tmp->position--;
			}

			tmp = nullptr;
			delete tmp;
		}

		size--;
	}
}

void LinkedList::deleteFromTail()
{
	if (size == 0)
		std::cout << "List is empty." << std::endl;
	else
	{
		SLLNode *tmp = head;
		SLLNode *tmp2 = tail;

		// iterates through list until node before tail is reached
		while (tmp->next != tail)
			tmp = tmp->next;

		size--;

		tail = tmp;							// tail is set to node before tail
		tail->next = nullptr;				// tail points to nullptr
		tmp = nullptr;				
		delete tmp, tmp2;
	}
}

void LinkedList::deleteFromPosition(int pos)
{
	SLLNode *tmp = head;					// tmp = head
	SLLNode *tmp2 = head->next;				// tmp2 = node after head

	// iterates until tmp2 reaches to position of deletion
	while (tmp2->position != pos)
	{
		tmp = tmp2;							// tmp trails behind tmp2
		tmp2 = tmp2->next;
	}

	tmp->next = tmp2->next;					// tmp no longer points to node to be deleted 
	tmp = tmp->next;
	tmp->position--;						// position is reflected 

	// remaining positions updated
	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
		tmp->position--;
	}

	size--;

	tmp = nullptr;
	delete tmp, tmp2;
}

void LinkedList::lowHigh(int size)
{
	int num;
	int tmpSize = size;
	SLLNode *tmp = head;

	for (int i = 1; i < tmpSize; i++)
	{
		// bubble sort with recursion 
		if (tmp->number > tmp->next->number)
		{
			num = tmp->number;
			tmp->number = tmp->next->number;
			tmp->next->number = num;
			lowHigh(tmpSize - 1);				// function is called recursively while size is deincrimented each time, 
		}										// this is to avoid stack overflow 

		tmp = tmp->next;
	}

	tmp = nullptr;
	delete tmp;
}

// identical to lowHigh() 
void LinkedList::highLow(int size)
{
	int num;
	int tmpSize = size;
	SLLNode *tmp = head;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->number < tmp->next->number)
		{
			num = tmp->number;
			tmp->number = tmp->next->number;
			tmp->next->number = num;
			highLow(tmpSize - 1); 
		}

		tmp = tmp->next;
	}

	tmp = nullptr;
	delete tmp;
}

LinkedList operator + (const LinkedList& passed, const LinkedList& passed2)
{
	int tmpSize = passed.size;
	LinkedList tmpList;
	SLLNode *tmp;

	tmpList.size = passed.size + passed2.size;
	tmp = passed.tail->next = passed2.head;
	tmp->position = ++tmpSize;

	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
		tmp->position = ++tmpSize;
	}

	tmpList.head = passed.head;
	tmpList.tail = passed2.tail;

	return tmpList;
}


// same functionality as addToHead()
LinkedList LinkedList::operator++ (int)
{
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> distribution(1, 100);
	LinkedList tmpList;

	int num = distribution(gen);			// node is assigned random value 

	if (size == 0)
		head = tail = new SLLNode(num, ++size);
	else
	{
		SLLNode *tmp = head;

		head = new SLLNode(num, 1, head);
		tmp->position++;

		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
			tmp->position++;
		}

		tmp = nullptr;
		delete tmp;
		size++;
	}

	return tmpList;
}

// same functionality as deleteFromHead()
LinkedList LinkedList::operator-- (int)
{
	LinkedList tmpList;

	if (size == 1)
		head = tail = nullptr;
	else
	{
		SLLNode *tmp = head;

		head = head->next;
		head->position = 1;
		delete tmp;
		tmp = head;

		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
			tmp->position--;
		}

		tmp = nullptr;
		delete tmp;
	}

	size--;
	return tmpList;
}