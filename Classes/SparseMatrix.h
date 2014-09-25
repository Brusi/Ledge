#ifndef  SPARSE_MATRIX_H_
#define  SPARSE_MATRIX_H_

#include <map>

#include "IJ.h"

/*
 * Sparse matrix with a template type and a default value (for empty cells)
 */
template <class T>
class SparseMatrix {
public:

	SparseMatrix() {}
	SparseMatrix(T defaultValue) : _defaultValue(defaultValue) {}
	// Return true if the matrix has a (non-default) value in this point.
	bool hasAt(const IJ& ij) const;
	bool hasAt(int i, int j) const;

	// Set the matrix value at a point.
	void setAt(const IJ& ij, T value);
	void setAt(int i, int j, T value);

	// Returns the matrix value at a given point. Return the default value if there is no value set.
	T& getAt(const IJ& ij);
	T& getAt(int i, int j);

	// Restore the default value at a given point.
	bool delAt(const IJ& ij);
	bool delAt(int i, int j);

	// Iterator
	typename std::map<IJ, T>::iterator begin() {
		return _matrix.begin();
	}
	typename std::map<IJ, T>::iterator end() {
		return _matrix.end();
	}

	T defVal() const;

	// Delete all entries.
	void clear();
	
private:
	// Matrix map
	std::map <IJ, T>  _matrix;
	T _defaultValue;

};

template <class T>
bool SparseMatrix<T>::hasAt(const IJ& ij) const
{
	return !(_matrix.find(ij) == _matrix.end());
}

template <class T>
bool SparseMatrix<T>::hasAt(int i, int j) const
{
	return this->hasAt(IJ(i, j));
}

template <class T>
void SparseMatrix<T>::setAt(const IJ& ij, T value)
{
	// Delete if setting to default value.
	//if (value == _defaultValue) {
	//	this->delAt(ij);
	//	return;
	//}
	//CCLOG("SUPRISE!!");
	_matrix[ij] = value;
}

template <class T>
void SparseMatrix<T>::setAt(int i, int j, T value)
{
	this->setAt(IJ{ i, j }, value);
}

template <class T>
T& SparseMatrix<T>::getAt(const IJ& ij)
{
	// If not exists in matrix, return default value.
	if (_matrix.find(ij) == _matrix.end()) {
		return _defaultValue;
	}
	return _matrix[ij];
}


template <class T>
T& SparseMatrix<T>::getAt(int i, int j)
{
	return getAt(IJ(i, j));
}

template <class T>
bool SparseMatrix<T>::delAt(const IJ& ij)
{
	auto it = _matrix.find(ij);
	
	// If deleting an empty cell, do nothing and return false.
	if (it == _matrix.end()) {
		return false;
	}
	_matrix.erase(it);
}

template <class T>
bool SparseMatrix<T>::delAt(int i, int j)
{
	return delAt(IJ(i, j));
}

template <class T>
T SparseMatrix<T>::defVal() const
{
	return defaultValue;
}

template <class T>
void SparseMatrix<T>::clear()
{
	// While not empty, delete the first entry.
	while (!_matrix.empty()) {
		auto it = _matrix.begin();
		auto key = it->first;
		this->delAt(key);
	}
}



#endif // SPARSE_MATRIX_H_
