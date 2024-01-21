#pragma once
#include <ostream>
#include <vector>


class SparseSet
{
public:
	std::vector<std::size_t> sparse_vec;
	std::vector<std::size_t> dense_vec;
	std::size_t dense_end{ 0 };
	std::size_t capacity{ 0 };

	SparseSet(const std::size_t size)
		: sparse_vec(size, 0), dense_vec(size, 0), capacity(size)
	{}

	void insert(std::size_t index) {
		sparse_vec[index] = dense_end;
		dense_vec[dense_end] = index;
		dense_end++;
		
	}
	void remove(std::size_t index) {
		const std::size_t dense_index = sparse_vec[index];
		const std::size_t last_index = dense_vec[dense_end - 1];
		dense_vec[dense_index] = last_index;
		sparse_vec[last_index] = dense_index;
		sparse_vec[index] = 0;
		dense_vec[dense_end - 1] = 0;
		dense_end--;
		
	}




};

inline std::ostream& operator<<(std::ostream& os, const SparseSet& set) {
	os << "s: [";
	for (auto i : set.sparse_vec) {
		os << i << " ";
	}
	os << "]" << std::endl;

	os << std::endl;
	os << "d: [";
	for (auto i : set.dense_vec) {
		os << i << " ";
	}
	os << "]" << std::endl;

	os << std::endl;
	return os;
}

