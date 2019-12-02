// Sebastian Jach
#pragma once

struct Node
{
	char letter;
	Node *prev;

	Node(char, Node*);
};

Node::Node(char let, Node *prevPointer = nullptr)
{
	letter = let;
	prev = prevPointer;
}

struct Queue
{
	private:
		int size;
		Node *first;
		Node *last;

	public:
		Queue();
		int getSize();
		void empty();
		void printSize(std::ofstream&);
		void print(std::ofstream&);
		void search(std::ofstream&, char);
		void alphabetize();
		void enqueue(char);
		char dequeue();
		Queue operator + (const Queue&);
		Queue operator ++ (int);
		Queue operator -- (int);
};

Queue::Queue()
{
	size = 0;
	first = last = nullptr;
}

int Queue::getSize()
{
	return size;
}

void Queue::empty()
{
	Node *tmp = first;

	while (tmp->prev != nullptr)
	{
		first = first->prev;
		delete tmp;
		tmp = first;
		size--;
	}

	size--;
	delete tmp, first;
}

void Queue::printSize(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty...";
	else
		output << "Size: " << size; 
}

void Queue::print(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty...";
	else
	{
		Node *tmp = first;

		for (int i = 1; i <= size; i++)
		{
			output << tmp->letter;

			if (i % 60 == 0)
				output << std::endl;

			tmp = tmp->prev;
		}

		output << std::endl << std::endl;

		tmp = nullptr;
		delete tmp;
	}
}

void Queue::alphabetize()
{
	bool sorted = true;
	char tmpLetter;
	int s = size;
	Node *tmp = first;

	for (int i = 1; i < size; i++)
	{
		if ((int)tmp->letter > (int)tmp->prev->letter)
		{
			sorted = false;
		}
		tmp = tmp->prev;
	}

	while (sorted == false)
	{
		tmp = first;

		for (int i = 1; i < s; i++)
		{
			if ((int)tmp->letter > (int)tmp->prev->letter)
			{
				tmpLetter = tmp->letter;
				tmp->letter = tmp->prev->letter;
				tmp->prev->letter = tmpLetter;
			}
			tmp = tmp->prev;
		}

		tmp = first;
		sorted = true;

		for (int i = 1; i < size; i++)
		{
			if ((int)tmp->letter > (int)tmp->prev->letter)
			{
				sorted = false;
			}
			tmp = tmp->prev;
		}
		s--;
	}

	tmp = nullptr;
	delete tmp;
}

void Queue::enqueue(char let)
{
	if (size == 0)
		first = last = new Node(let);
	else
	{
		last->prev = new Node(let);
		last = last->prev;
	}

	size++;
}

char Queue::dequeue()
{
	char letter = first->letter;
	if (size == 1)
	{
		Node *tmp = first;
		first = last = nullptr;
		delete tmp;
	}
	else
	{
		Node *tmp = first;
		first = first->prev;
		delete tmp;
	}

	size--;
	return letter;
}

void Queue::search(std::ofstream& output, char letter)
{
	int tmpSize = getSize(), count = 0;			// count starts at 1
	Node *tmp = first;
	LinkedList instances;

	// iterates through queue and checks for matches
	while (tmp->prev != nullptr)
	{
		if (tmp->letter == letter)
			count++;

		instances.addToHead(tmpSize);

		tmp = tmp->prev;
		tmpSize--;
	}

	if (count == 0)
		output << "Instances: " << count << std::endl;
	else
		output << "Instances: " << count << " Locations: ";

	instances.printList(output);

}

Queue Queue::operator+ (const Queue& passed)
{
	Queue tmpQueue;
	Node *tmp, *tmp2;

	tmpQueue.size = size + passed.size;
	tmp = first;
	tmp2 = passed.last;
	tmpQueue.first = passed.first;
	tmpQueue.last = last;
	tmp2->prev = tmp;

	tmp = tmp2 = nullptr;
	delete tmp;

	return tmpQueue;
}

Queue Queue::operator++ (int)
{
	Queue tmpQueue;

	if (size == 0)
		first = last = new Node('x');
	else
	{
		last->prev = new Node('x');
		last = last->prev;
	}

	size++;

	return tmpQueue;
}

Queue Queue::operator-- (int)
{
	Queue tmpQueue;

	if (size == 0)
	{ 
		getSize();
	}
	else
	{
		char letter = first->letter;
		if (size == 1)
		{
			Node *tmp = first;
			first = last = nullptr;
			delete tmp;
		}
		else
		{
			Node *tmp = first;
			first = first->prev;
			delete tmp;
		}

		size--;
	}

	return tmpQueue;
}


