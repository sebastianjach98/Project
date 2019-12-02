// Sebastian Jach
#pragma once

extern const int seed;

struct CLLNode
{
	int number, position;
	CLLNode *next;

	CLLNode(int, int, CLLNode*);
};

CLLNode::CLLNode(int num, int pos, CLLNode *nextPointer = nullptr) // if nextPointer is not specified, nullptr is assigned 
{
	number = num;
	position = pos;
	next = nextPointer;
}

struct CircularList
{
	private:
		int size;
		CLLNode *tail;

	public:
		CircularList();
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
		CircularList operator + (const CircularList&);
		CircularList operator ++ (int);
		CircularList operator -- (int);
};

CircularList::CircularList()
{
	size = 0;
	tail = nullptr;
}

int CircularList::getSize()
{
	return size;
}

void CircularList::empty()
{
	CLLNode *tmp = tail->next;

	// iterates through list 
	while (tmp->next != tail->next)
	{
		tail->next = tmp->next;		// tail is set to second node from beginning
		delete tmp;					// tmp pointing to old head is deleted
		tmp = tail->next;			// tmp is set to the new head
	}

	size = 0;
	delete tmp;
}

void CircularList::search(std::ofstream& output, int num)
{
	int number, count = 0;			// counter starts at 0
	CLLNode *tmp;					// used to iterate through list
	LinkedList instances;			// used for storing positions 
	
	if (size == 0)
		std::cout << "Empty list..." << std::endl;
	else
	{
		number = num;
		count = 0;

		tmp = tail->next;

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

void CircularList::printSize(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty..." << std::endl;
	else
		output << "Size: " << size << std::endl;
}

void CircularList::printList(std::ofstream& output)
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

	if (size == 1)
		output << tail->number;
	else
	{
		CLLNode *tmp = tail->next;

		for (int i = 1; i <= size; i++)
		{
			output << tmp->number << " ";

			// used for formatting
			if (i % 20 == 0)
				output << std::endl;

			tmp = tmp->next;
		}
	}

	output << std::endl;
}

void CircularList::addToHead(int num)
{
	if (size == 0)
	{
		tail = new CLLNode(num, ++size);
		tail->next = tail;
	}
	else
	{
		CLLNode *tmp = tail->next;							// tmp points to first node
		tail->next = new CLLNode(num, 1, tail->next);		// tail->next points to new node
		tmp->position++;

		// updates positions
		while (tmp->next != tail->next)
		{
			tmp = tmp->next;
			tmp->position++;
		}

		size++;

		tmp = nullptr;
		delete tmp;
	}
}

void CircularList::addToTail(int num)
{
	if (size == 0)
	{
		tail = new CLLNode(num, ++size);
		tail->next = tail;
	}
	else
	{
		tail->next = new CLLNode(num, ++size, tail->next);
		tail = tail->next;
	}
}

void CircularList::addToPosition(int num, int pos)
{
	if (pos < 1 || pos > size)
		std::cout << "size = " << size << ", pos = " << pos << "(error)";
	else if (size == 1 || pos == 1)
		addToHead(num);
	else
	{

		CLLNode *tmp = tail->next;						// tmp is set to first node

		// tmp iterates until it reaches node before insertion point
		while (tmp->position != pos - 1)				
			tmp = tmp->next;

		tmp->next = new CLLNode(num, pos, tmp->next);	// tmp points to a new node 

		tmp = tmp->next->next;
		tmp->position++;

		// positions updated
		while (tmp->next != tail->next)
		{
			tmp = tmp->next;
			tmp->position++;
		}

		size++;

		tmp = nullptr;
		delete tmp;
	}
}

void CircularList::deleteFromHead()
{
	CLLNode *tmp = tail->next;					// tmp is equal to first node
	
	tail->next = tmp->next;						// tail->next is equal to second node 
	delete tmp;									// first node is deleted
	tmp = tail->next;							// tmp points to new first node

	tmp->position--;

	// positions updated
	while (tmp->next != tail->next)
	{
		tmp = tmp->next;
		tmp->position--;
	}
	
	size--;

	tmp = nullptr;
	delete tmp;
}

void CircularList::deleteFromTail()
{
	if (size == 0)
		std::cout << "List is empty." << std::endl;
	else
	{
		CLLNode *tmp = tail;
		CLLNode *tmp2 = tail->next;

		// iterates through list until node before tail is reached
		while (tmp2->next != tail)
			tmp2 = tmp2->next;

		tmp2->next = tail->next;
		tail = tmp2;
		size--;

		tmp2 = nullptr;
		delete tmp, tmp2;
	}
}

void CircularList::deleteFromPosition(int pos)
{
	CLLNode *tmp;					
	CLLNode *tmp2 = tail->next;				// tmp2 = first node

	// iterates until node before deletion point is pointed to 
	while (tmp2->position != pos - 1)		
		tmp2 = tmp2->next;

	tmp = tmp2->next;						// tmp is equal to node to be deleted
	tmp2->next = tmp->next;
	tmp2 = tmp2->next;
	tmp2->position--;

	// updates positions 
	while (tmp2->next != tail->next)
	{
		tmp2 = tmp2->next;
		tmp2->position--;
	}

	size--;

	tmp2 = nullptr;
	delete tmp, tmp2;
}

// same as previous lowHigh()
void CircularList::lowHigh(int size)
{
	int num;
	int tmpSize = size;
	CLLNode *tmp = tail->next;

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

// same as previous highLow()
void CircularList::highLow(int size)
{
	int num;
	int tmpSize = size;
	CLLNode *tmp = tail->next;

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

CircularList CircularList::operator+ (const CircularList& passed)
{
	CircularList tmpList;
	CLLNode *tmpPtr;

	tmpList.size = size + passed.size;

	tmpPtr = passed.tail->next;
	tmpList.tail = passed.tail;
	tmpList.tail->next = tail->next;
	tail->next = tmpPtr;

	tmpPtr = nullptr;
	delete tmpPtr;

	return tmpList;
}

CircularList CircularList::operator++ (int)
{
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> distribution(1, 100);
	CircularList tmpList;
	int num = distribution(gen);

	if (size == 0)
	{
		tail = new CLLNode(num, ++size);
		tail->next = tail;
	}
	else
	{
		CLLNode *tmp = tail->next;
		tail->next = new CLLNode(num, 1, tail->next);

		tmp->position++;

		while (tmp->next != tail->next)
		{
			tmp = tmp->next;
			tmp->position++;
		}

		size++;

		tmp = nullptr;
		delete tmp;
	}

	return tmpList;
}

CircularList CircularList::operator-- (int)
{
	CircularList tmpList;

	if (size == 1)
	{
		delete tail;
		size--;
	}
	else
	{
		CLLNode *tmp = tail->next;
		tail->next = tmp->next;
		delete tmp;
		tmp = tail->next;
		tmp->position--;

		while (tmp->next != tail->next)
		{
			tmp = tmp->next;
			tmp->position--;
		}

		size--;

		tmp = nullptr;
		delete tmp;
	}

	return tmpList;
}