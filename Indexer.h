#pragma once
#include <list>

class Indexer
{
private:
	std::list<unsigned int> unusedIndex;
	unsigned int maxIndex,currentIndex;
public:
	Indexer()
	{
		maxIndex = currentIndex = 0;
	}
	Indexer(unsigned int maxIndex)
	{
		this->maxIndex = maxIndex;
		currentIndex = 0;
	}

	unsigned int getNextIndex()
	{
		if (unusedIndex.size() == 0)
		{
			if (currentIndex < maxIndex)
			{
				unsigned int index = currentIndex;
				if (index == 599)
				{
					currentIndex++;
					return index;
				}
				currentIndex++;
				return index;
			}
			else
			{
				unsigned int index = currentIndex;
			}
			return UINT_MAX;
		}
		else
		{
			unsigned int index = unusedIndex.front();
			unusedIndex.pop_front();
			return index;
		}
	}
	
	void releaseIndex(unsigned int index)
	{
		if (index < maxIndex)
		{
			unusedIndex.push_back(index);
		}
	}
};