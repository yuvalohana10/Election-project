#pragma once
#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	DynamicArray(int size, int num): _logicalSize(size), _physicalSize(size), _arr(new T[size])
	{
		for (int i = 0; i < size; i++)
		{
			_arr[i].reps = 0;
			_arr[i].votes = 0;
		}
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }
	T& returnidx(int i) { return _arr[i]; }
	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	// example iterator implementation:
	// (causes code duplication)
	class iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		// const_iterator should also be constructible from regular iterator
		friend class const_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			++_i;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--() {
			--_i;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--_i;
			return temp;
		}

		const int get_i() const { return this->_i; }
	};

	class const_iterator
	{
	private:
		const DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(const DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

	   // const_iterator should also be constructible from regular iterator
		friend class const_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		const T& operator*() {
			return  _da->_arr[_i];
		}
		const T* operator->() {
			return  &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			++_i;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--() {
			--_i;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--_i;
			return temp;
		}

		const int get_i() const { return this->_i; }
	};

	class reverse_iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		reverse_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		reverse_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		// const_iterator should also be constructible from regular iterator
		friend class const_iterator;

		const reverse_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const reverse_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const reverse_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		reverse_iterator& operator++() {
			--_i;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			--_i;
			return temp;
		}
		reverse_iterator& operator--() {
			++_i;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			++_i;
			return temp;
		}

		const int get_i() const { return this->_i; }
	};

	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	// returns iterator to first element after deleted element/s
	iterator erase(const iterator& iter)
	{

		iterator iterAfter = iter, itr = begin(), endItr = --end(), iterVal = iter;
		T* temp = new T[_logicalSize - 1];

		if (iterAfter != endItr)
			++iterAfter;

		int i = 0;

		for (i = 0; itr != iter; ++itr, ++i)
		{
			temp[i] = *itr;
		}

		for (; iterAfter != endItr; ++iterAfter, ++i)
		{
			temp[i] = *iterAfter;
		}

		delete[] _arr;

		_arr = temp;

		_logicalSize--;

		--iterVal;

		return iterVal;
	}

	iterator erase(const iterator& first, const iterator& last)
	{
		iterator iterAfter = last, itr = begin(), endItr = end(), iterVal = last, fItr = first;
		T* temp = new T[_logicalSize - 1];

		int i = 0;

		iterVal = fItr;

		if (iterAfter != endItr)
		{
			++iterAfter;
		}

		for (i = 0; itr != first; ++itr, ++i)
		{
			temp[i] = *itr;
		}

		for (int j = 0; iterAfter != endItr; ++iterAfter, ++i, ++j)
		{
			temp[i] = *iterAfter;
			if (j == 0)
				*iterVal = *iterAfter;
		}

		delete[] _arr;

		_arr = temp;

		_logicalSize = i;

		if (last == --endItr)
			iterVal = --end();

		return iterVal;

	}

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}

	const_iterator cbegin() {
		return const_iterator(*this, 0);
	}

	const_iterator cend() {
		return const_iterator(*this, _logicalSize);
	}

	iterator rbegin()
	{
		return end();
	}

	iterator rend()
	{
		return begin();
	}

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	T* _arr;
	int _logicalSize;
	int _physicalSize;
};

