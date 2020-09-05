#pragma once

template <typename T>
class Array
{
public:
	Array();
	Array(int initialSize);
	~Array();

	void Add(T value);
	int Size();

	// T should have <= operator defined
	void Sort();

private:
	const int initialSize = 8;
	int numElements = 0;
	int dataLength = 0;
	T* data = nullptr;

	// Assumes that all of the elements in data will fit in the resized array
	void Resize(int newSize);

	T* MergeSort(T* data, int length);
	T* Merge(T* left, int leftLen, T* right, int rightLen);
};
