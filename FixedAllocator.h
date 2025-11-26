#pragma once
#include <cstddef>

/*
void FixedVectorTestFunc()
{
	FixedVector<int, 10> v;  //Size 10

	v.push_back(123);
	v.push_back(456);

	for (auto& x : v) {
		printf("%d\n", x);
	}

	if (!v.push_back(789)) {
		printf("Vector is full!\n");
	}
}
*/

template<typename T, std::size_t N>
class FixedVector {
public:
	using value_type = T;
	using size_type = std::size_t;
	using iterator = T*;
	using const_iterator = const T*;

	FixedVector() : _size(0) {}

	~FixedVector() {
		clear();
	}

	void clear() {//Do nothing.	
		_size = 0;
	}

	bool push_back(const T& value) {
		if (_size >= N)
			return false;  // Full
		_data[_size++] = value;
		return true;
	}

	bool pop_back() {
		if (_size == 0)
			return false;		
		--_size;
		return true;
	}

	T& operator[](size_type i) {
		return _data[i];
	}

	const T& operator[](size_type i) const {
		return _data[i];
	}

	bool erase(size_type index) {
		if (index >= _size) return false;
		for (size_type i = index; i < _size - 1; ++i)
			_data[i] = _data[i + 1];
		--_size;
		return true;
	}

	bool erase(iterator iter) {
		//if (index >= _data[_size]) return false;
		size_type index = -1;
		for (size_type i = 0; i < _size - 1; ++i)
			if (&_data[i] == iter)
			{//find index
				index = i;
				break;
			}

		if (index == -1) return false;
		return erase(index);
	}

	bool insert(size_type index, const T& value) {
		if (_size >= N || index > _size) return false;

		for (size_type i = _size; i > index; --i)
			_data[i] = _data[i - 1];

		_data[index] = value;
		++_size;
		return true;
	}

	size_type size() const { return _size; }
	constexpr size_type capacity() const { return N; }
	bool empty() const { return _size == 0; }
	bool full() const { return _size == N; }

	T* begin() { return &_data[0]; }
	T* end() { return &_data[_size]; }
	const T* begin() const { return &_data[0]; }
	const T* end() const { return &_data[_size]; }

private:
	T _data[N];      // Fixed buffer, no heap
	size_type _size;
};
