// Sebastian Jach
#pragma once

extern const int seed;

struct DLLNode
{
	int number, position;
	DLLNode *next, *prev;

	DLLNode(int, int, DLLNode*, DLLNode*);
};

DLLNode::DLLNode(int num, int pos, DLLNode *nextPointer = nullptr, DLLNode *prevPointer = nullptr)
{
	number = num;
	position = pos;
	next = nextPointer;
	prev = prevPointer;
}

struct DoublyList
{
	private:
		int size;
		DLLNode *head, *tail;

	public:
		DoublyList();
		int getSize();
		void empty();
		void search(std::ofstream&, int);
		void printSize(std::ofstream&);
		void printList(std::ofstream&);
		void addToHead(int);
		void addToTail(int);
		void addToPosition(int, int);
		void deleteFromHead();
		void deleteFromTail();
		void deleteFromPosition(int);
		void lowHigh(int);
		void highLow(int);
		DoublyList operator + (const DoublyList&);
		DoublyList operator ++ (int);
		DoublyList operator -- (int);
};


DoublyList::DoublyList()
{
	size = 0;
	head = tail = nullptr;
}

int DoublyList::getSize()
{
	return size;
}

void DoublyList::empty()
{
	if (size == 1)
	{
		delete head, tail;
		size--;
	}
	else
	{
		DLLNode *tmp;

		tmp = head;

		// iterates through list
		while (tmp->next != nullptr)
		{
			head = head->next;				// head is set to next node
			delete tmp;						// tmp pointing to old head is deleted
			tmp = head;						// tmp is set to new head
			size--;
		}

		size--;
		delete tmp, head;
	}
}


void DoublyList::search(std::ofstream& output, int num)
{
	int number, count = 0;					// counter starts at 0
	DLLNode *tmp;							// used to iterate through list
	LinkedList instances;					// used for storing positions 

	if (size == 0)
		output << "Empty list." << std::endl;
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

		tmp = nullptr;
	}

	if (count == 0)
		output << "Number of instances: " << count << std::endl;
	else
	{
		output << "Instances: " << count << " /" << " Locations: ";
		instances.printList(output);
	}
}

void DoublyList::printSize(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty..." << std::endl;
	else
		output << "Size: " << size << std::endl;
}

void DoublyList::printList(std::ofstream& output)
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

	DLLNode *tmp = head;

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

void DoublyList::addToHead(int num)
{
	if (size == 0)
		head = tail = new DLLNode(num, ++size);
	else
	{
		DLLNode *tmp = head;

		head = new DLLNode(num, 1, head);			// head points to previous head
		tmp->prev = head;							// old head points to new head
		tmp->position++;

		// updates positions
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
			tmp->position++;
		}

		tmp = nullptr;
		delete tmp;
		size++;
	}
}

void DoublyList::addToTail(int num)
{
	if (size == 0)
		head = tail = new DLLNode(num, ++size);
	else
	{
		tail->next = new DLLNode(num, ++size);
		tail->next->prev = tail;
		tail = tail->next;
	}
}

void DoublyList::addToPosition(int num, int pos)
{
	DLLNode *tmp = head;

	// iterates until tmp points to position node before insertion 
	while (tmp->position != pos - 1)
		tmp = tmp->next;

	tmp->next = new DLLNode(num, pos, tmp->next, tmp);		// tmp->next points to a new node that uses,
	tmp = tmp->next->next;									// both its default constructors in order,
	tmp->position++;										// to point to it's next and prev node

	// updates remaining list positons 
	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
		tmp->position++;
	}

	tmp = nullptr;
	delete tmp;
	size++;
}

void DoublyList::deleteFromHead()
{
	if (size == 0)
		std::cout << "List is empty." << std::endl;
	else
	{
		DLLNode *tmp = head;

		if (size == 1)
			head = tail = nullptr;
		else
		{
			head = head->next;			// head is set to next node
			head->prev = nullptr;		// head stops pointing to node to be deleted
			head->position = 1;			// makes position of head 1

			delete tmp;
			tmp = head;

			// updates remaining list positions 
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
				tmp->position--;
			}

			tmp = nullptr;
		}

		delete tmp;
		size--;
	}
}

void DoublyList::deleteFromTail()
{
	if (size == 0)
		std::cout << "List is empty." << std::endl;
	else
	{
		DLLNode *tmp = tail;			// tmp is equal to tail
		tail = tail->prev;				// tail is equal to second to last node
		tail->next = nullptr;			// tail stops pointing to node to be deleted

		size--;

		delete tmp;
	}
}

void DoublyList::deleteFromPosition(int pos)
{
	DLLNode *tmp = head;					// tmp = head
	DLLNode *tmp2;

	// iterates until tmp reaches to position before deletion
	while (tmp->position != pos - 1)
		tmp = tmp->next;

	tmp2 = tmp->next;						// tmp2 is equal to node to be deleted
	tmp2->next->prev = tmp;					// node after tmp2 points to node before tmp2
	tmp->next = tmp2->next;					// node before tmp2 points to node after tmp2
	delete tmp2;

	// remaining positions updated
	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
		tmp->position--;
	}

	tmp = nullptr;
	delete tmp;
	size--;
}

// same as linked list lowHigh()
void DoublyList::lowHigh(int size)
{
	int num;
	int tmpSize = size;
	DLLNode *tmp = head;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->number > tmp->next->number)
		{
			num = tmp->number;
			tmp->number = tmp->next->number;
			tmp->next->number = num;
			lowHigh(tmpSize - 1);
		}

		tmp = tmp->next;
	}

	tmp = nullptr;
	delete tmp;
}

// same as linked list highLow()
void DoublyList::highLow(int size)
{
	int num;
	int tmpSize = size;
	DLLNode *tmp = head;

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

DoublyList DoublyList::operator+ (const DoublyList& passed) 
{
	int tmpSize = size;
	DoublyList tmpList;
	DLLNode *tmp;

	tmpList.size = size + passed.size;			// new size
	tmp = tail->next = passed.head;				// tail and tmp point to head of second list
	passed.head->prev = tail;					// head of second list points to tail of first list

	tmp->position = ++tmpSize;					// updates position of second head node

	// updates remaining positions
	while (tmp->next != nullptr)
	{
		tmp = tmp->next;
		tmp->position = ++tmpSize;
	}

	tmpList.head = head;						// new head pointer points to first lists head
	tmpList.tail = passed.tail;					// new tail pointer points to second lists tail  

	return tmpList;
}

// same funtuinality as addToHead()
DoublyList DoublyList::operator++ (int)
{
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> distribution(1, 100);
	DoublyList tmpList;

	int num = distribution(gen);				// node is assigned random value 

	if (size == 0)
		head = tail = new DLLNode(num, ++size);
	else
	{
		DLLNode *tmp = head;

		head = new DLLNode(num, 1, head);
		tmp->prev = head;
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
DoublyList DoublyList::operator-- (int)
{
	DoublyList tmpList;

	if (size == 1)
		head = tail = nullptr;
	else
	{
		DLLNode *tmp = head;

		head = head->next;
		head->prev = nullptr;
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