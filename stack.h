// Sebastian Jach
#pragma once

struct Card
{
	int suit, rank, color, position;
	Card *next;
	
	Card(int, int, int, int, Card*);
};

Card::Card(int s, int r, int c, int p, Card* nextCard = nullptr)
{
	suit = s;
	rank = r;
	color = c;
	position = p;
	next = nextCard;
}

struct Stack
{
	private:
		int size;
		Card *top;

	public:
		Stack();
		int getSize();
		void empty();
		void printSize(std::ofstream&);
		void push(int, int, int, int);
		void pop();
		void printHand(std::ofstream&);
		void search(std::ofstream&, int, int, int);
		void printStack(std::ofstream&);
		void shuffleDeck(int, std::mt19937&);
		void lowHigh(int);
		void highLow();
		Stack operator + (const Stack&);
		Stack operator ++ (int);
		Stack operator -- (int);
};

int Stack::getSize()
{
	return size;
}

void Stack::empty()
{
	if (size == 1)
	{
		delete top;
		size = 0;
	}
	else
	{
		Card *tmp;

		tmp = top;
		while (tmp->next != nullptr)
		{
			top = top->next;
			delete tmp;
			tmp = top;
			size--;
		}

		size--;
		delete tmp, top;
	}
}

void Stack::printSize(std::ofstream& output)
{
	if (size == 0)
		output << "List is empty...";
	else
		output << "Size: " << size;
}

void Stack::search(std::ofstream& output, int s, int r, int c)
{
	 int suit, rank, color, count = 0;
	Card *tmp;
	LinkedList instances;
	
	if (size == 0)
		output << "Empty list." << std::endl;
	else
	{
		tmp = top;
		suit = s;
		rank = r;
		color = c;
	
		// iterates through stack while checking for matches
		for (int i = 1; i <= size; i++)
		{
			if (tmp->suit == suit && tmp->rank == rank && tmp->color == color)
			{
				instances.addToTail(tmp->position);					// position of instances are added to linked list 
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

// bubble sort 4 times for each cat. 
void Stack::lowHigh(int size)
{
	int num;
	int tmpSize = size;
	Card *tmp = top;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->suit > tmp->next->suit)
		{
			num = tmp->suit;
			tmp->suit = tmp->next->suit;
			tmp->next->suit = num;
			lowHigh(tmpSize - 1);
		}

		tmp = tmp->next;
	}

	tmp = top;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->rank > tmp->next->rank)
		{
			num = tmp->rank;
			tmp->rank = tmp->next->rank;
			tmp->next->rank = num;
			lowHigh(tmpSize - 1);
		}

		tmp = tmp->next;
	}

	tmp = top;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->color > tmp->next->color)
		{
			num = tmp->color;
			tmp->color = tmp->next->color;
			tmp->next->rank = num;
			lowHigh(tmpSize - 1);
		}

		tmp = tmp->next;
	}

	tmp = top;

	for (int i = 1; i < tmpSize; i++)
	{
		if (tmp->position > tmp->next->position)
		{
			num = tmp->position;
			tmp->position = tmp->next->position;
			tmp->next->rank = num;
			lowHigh(tmpSize - 1);
		}

		tmp = tmp->next;
	}


	tmp = nullptr;
	delete tmp;
}

// same as lowHigh()
void Stack::highLow()
{
	int num;
	Card *tmp;
	
	for (int j = 1; j <= size; j++)
	{
		tmp = top;

		for (int i = 1; i < size; i++)
		{
			if (tmp->suit < tmp->next->suit)
			{
				num = tmp->suit;
				tmp->suit = tmp->next->suit;
				tmp->next->suit = num;
			}

			if (tmp->rank < tmp->next->rank)
			{
				num = tmp->rank;
				tmp->rank = tmp->next->rank;
				tmp->next->rank = num;
			}

			if (tmp->color < tmp->next->color)
			{
				num = tmp->color;
				tmp->color = tmp->next->color;
				tmp->next->color = num;
			}

			if (tmp->position < tmp->next->position)
			{
				num = tmp->position;
				tmp->position = tmp->next->position;
				tmp->next->suit = num;
			}

			tmp = tmp->next;
		}
	}

	tmp = nullptr;
	delete tmp;
}

void Stack::printHand(std::ofstream& output)
{
	Card *tmp = top;

	for (int i = 1; i <= 7; i++)
	{
		if (tmp->suit == 1)
		{
			if (tmp->rank == 1)
				output << "[A of S]";
			else if (tmp->rank == 11)
				output << "[J of S]";
			else if (tmp->rank == 12)
				output << "[Q of S]";
			else if (tmp->rank == 13)
				output << "[K of S]";
			else
				output << "[" << tmp->rank << " of S]";
		}
		else if (tmp->suit == 2)
		{
			if (tmp->rank == 1)
				output << "[A of H]";
			else if (tmp->rank == 11)
				output << "[J of H]";
			else if (tmp->rank == 12)
					output << "[Q of H]";
			else if (tmp->rank == 13)
					output << "[K of H]";
			else
				output << "[" << tmp->rank << " of H]";
		}
		else if (tmp->suit == 3)
		{
			if (tmp->rank == 1)
				output << "[A of C]";
			else if (tmp->rank == 11)
				output << "[J of C]";
			else if (tmp->rank == 12)
				output << "[Q of C]";
			if (tmp->rank == 13)
				output << "[K of C]";
			else
				output << "[" << tmp->rank << " of C]";
		}
		else
		{
			if (tmp->rank == 1)
				output << "[A of D]";
			else if (tmp->rank == 11)
				output << "[J of D]";
			else if (tmp->rank == 12)
				output << "[Q of D]";
			else if (tmp->rank == 13)
				output << "[K of D]";
			else
				output << "[" << tmp->rank << " of D]";
		}

		tmp = tmp->next;
	}

	tmp = nullptr;
	delete tmp;
}

// Sebastian's attempt at the modern version of the Fisher–Yates shuffle (recursively)
void Stack::shuffleDeck(int offset, std::mt19937& gen)
{
	std::uniform_int_distribution<int> distribution(offset, 52);	// offset is increased by 1 each function call so one side,
	int suit, rank, color, random;									// can be the shuffled side and the offset continues growing until the whole
	Card *tmp, *tmp2;												// stack has been shuffled 

	tmp = tmp2 = top;

	if (offset != size)							// base case
	{
		random = distribution(gen);				// random number generated 

		if (offset == random)					// random is used as the location of node *this is why range of distribution is between offset and 52!
			shuffleDeck(++offset, gen);			// in the case that two numbers are the same, the fuction gets called again with no action, nothing to swap!
		else
		{
			for (int i = 1; i < offset; i++)	// this for loop transveres through left side (swapped side)
				tmp = tmp->next;
 
			for (int i = 1; i < random; i++)	// this for loop transverses through the unsorted side (untouched side)
				tmp2 = tmp2->next;

			// this implementation ensures the two transversals will never overlap and one side will gradually over take the other side (hence the increasing offset)

			// suits, ranks and colors are all swapped between the two locations 
			suit = tmp->suit;
			rank = tmp->rank;
			color = tmp->color;
			tmp->suit = tmp2->suit;
			tmp->rank = tmp2->rank;
			tmp->color = tmp2->color;
			tmp2->suit = suit;
			tmp2->rank = rank;
			tmp2->color = color;

			shuffleDeck(++offset, gen);			// function called again with incrimented offset 
		}
	}
}

Stack::Stack()
{
	size = 0;
	top = nullptr;
}

void Stack::push(int suit, int rank, int color, int position)
{
	if (size == 0)
		top = new Card(suit, rank, color, position);
	else
		top = new Card(suit, rank, color, position, top);

	size++;
}

void Stack::pop()
{
	Card *tmp = top;

	if (size == 1)
		top = nullptr;
	else
		top = top->next;

	delete tmp;
	size--;
}

void Stack::printStack(std::ofstream& output)
{
	if (size == 0)
		output << "Empty stack..." << std::endl;
	else
	{
		Card *tmp = top;

		while (tmp->next != nullptr)
		{
			output << "[" << tmp->suit << " " << tmp->rank << " " << tmp->color << " " << tmp->position << "]" << std::endl;
			tmp = tmp->next;
		}
		output << "[" << tmp->suit << " " << tmp->rank << " " << tmp->color << " " << tmp->position << "]" << std::endl;

		tmp = nullptr;
		delete tmp;
	}
}

Stack Stack::operator+ (const Stack& passed)
{
	Stack tmp;
	Card *tmpPointer = top;

	tmp.size = size + passed.size;
	tmp.top = tmpPointer;

	while (tmpPointer->next != nullptr)
		tmpPointer = tmpPointer->next;

	tmpPointer->next = passed.top;

	return tmp;
}

Stack Stack::operator++ (int)
{
	std::mt19937 gen(373);
	std::uniform_int_distribution<int> distribution(1, 9);
	Stack tmp;
	int num1, num2, num3, num4;

	num1 = distribution(gen);
	num2 = distribution(gen);
	num3 = distribution(gen);
	num4 = distribution(gen);

	if (size == 0)
		top = new Card(num1, num2, num3, num4);
	else
		top = new Card(num1, num2, num3, num4, top);

	size++;
	return tmp;
}

Stack Stack::operator-- (int)
{
	Stack tmp;
	Card *pointer = top;

	if (size == 1)
		top = nullptr;
	else
		top = top->next;

	size--;
	delete pointer;
	return tmp;
}