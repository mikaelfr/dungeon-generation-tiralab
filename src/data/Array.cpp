#include "Array.h"
#include <string.h>
#include <iostream>

template<typename T>
Array<T>::Array()
{
	data = new[initialSize];
	dataLength = initialSize;
}

template<typename T>
Array<T>::Array(int initialSize)
{
	data = new[initialSize];
	dataLength = initialSize;
}

template<typename T>
Array<T>::~Array()
{
	if (data)
		delete[] data;
}

template<typename T>
void Array<T>::Add(T value)
{
	if (dataLength <= numElements)
	{
		Resize(dataLength * 2);
	}

	data[numElements++] = value;
}

template<typename T>
int Array<T>::Size()
{
	return numElements;
}

template<typename T>
void Array<T>::Sort()
{
	T* sortedArray = MergeSort(data, numElements);

	if (sortedArray != data)
		delete[] data;

	data = sortedArray;
}

template<typename T>
void Array<T>::Resize(int newSize)
{
	if (numElements >= newSize)
	{
		std::cerr << "There are currently more elements than there is room in the new array." << std::endl;
		return;
	}

	T* newArray = new T[newSize];

	if (!memcpy_s(newArray, newSize * sizeof(T), data, numElements * sizeof(T)))
	{
		std::cerr << "Couldn't copy to new array when resizing." << std::endl;
		return;
	}

	delete[] data;
	data = newArray;
}

template<typename T>
T* Array<T>::MergeSort(T* data, int length)
{
	if (length <= 1)
		return data;

	int halfPoint = length / 2;
	T* left = new T[halfPoint];
	T* right = new T[length - halfPoint];

	if (!memcpy_s(left, halfPoint * sizeof(T), data, halfPoint * sizeof(T)))
	{
		std::cerr << "Couldn't copy left array" << std::endl;
		return nullptr;
	}

	if (!memcpy_s(right, (length - halfPoint) * sizeof(T), data + halfPoint, (length - halfPoint) * sizeof(T)))
	{
		std::cerr << "Couldn't copy right array" << std::endl;
		return nullptr;
	}

	// Recursively sort both sides
	T* mergedLeft = MergeSort(left, halfPoint);
	delete[] left;
	T* mergedRight = MergeSort(right, length - halfPoint);
	delete[] right;

	// Merge both sorted sides
	T* merged = Merge(mergedLeft, halfPoint, mergedRight, length - halfPoint);
	delete[] mergedLeft;
	delete[] mergedRight;

	return merged;
}

template<typename T>
T* Array<T>::Merge(T* left, int leftLen, T* right, int rightLen)
{
	int li, ri, resi = 0;
	T* result = new T[leftLen + rightLen];
	
	// Build result array by placing smallest of the two sorted arrays
	while (li < leftLen && ri < rightLen)
	{
		if (left[li] <= right[ri])
		{
			result[resi++] = left[li++];
		}
		else
		{
			result[resi++] = right[ri++];
		}
	}

	// Insert the rest into result array
	if (!memcpy_s(result + resi, (leftLen + rightLen - resi) * sizeof(T), left + li, (leftLen - li) * sizeof(T)))
	{
		std::cerr << "Couldn't copy left array" << std::endl;
		return nullptr;
	}

	if (!memcpy_s(result + resi, (leftLen + rightLen - resi) * sizeof(T), right + ri, (rightLen - ri) * sizeof(T)))
	{
		std::cerr << "Couldn't copy right array" << std::endl;
		return nullptr;
	}

	return result;
}
