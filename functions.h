// Sebastian Jach
#pragma once

// fills lists with random numbers 
template <typename GeneralList>
void fillList(GeneralList& list, std::mt19937& gen)
{
	std::uniform_int_distribution<int> distribution(1, 100);
	int number;

	for (int i = 1; i <= 100; i++)
	{
		number = distribution(gen);
		list.addToHead(number);
	}
}

// fills stack with unshuffled deck of cards
template <typename GeneralStack>
void fillStack(GeneralStack& stack)
{
	int count = 0;

	// i = suit, j = rank, 1 = red, 2 = black, count = size
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 13; j++)
		{
			if (i == 1 || i == 3)
				stack.push(i, j, 1, ++count);
			else
				stack.push(i, j, 2, ++count);
		}
}

// fills queue with text using getline()
template <typename GeneralQueue>
void fillQueue(GeneralQueue& queue, std::ifstream& input, std::string text)
{
	while (getline(input, text))
	{
		// restricts input to alphabet only
		for (int i = 0; i < (int)text.length(); i++)
			if (text[i] >= 97 && text[i] <= 122)	
				queue.enqueue(text[i]);
			else if (text[i] >= 65 && text[i] <= 90)
				queue.enqueue(text[i] + 32);			// converts all uppercase letters to lowercase
	}
}