#pragma once
#include <iostream>

using namespace std;

template <typename Cell = double>
class Matrix
{
private:
	int n_nRows;
	int n_nCols;

	Cell** m_cells;
	void AllocateCells(int, int);
	void FreeCells();
public:
	Matrix() : n_nRows(0), n_nCols(0), m_cells(nullptr) {}
	Matrix(const Matrix&);
	Matrix(int, int);
	Matrix(int, int, Cell*);
	~Matrix();

	int nRows();
	int nColumns();

	void setVaue(int, int, Cell);

	Cell& operator()(int i, int j) { return m_cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// ���������� ��������� ������������
	Matrix  operator + (const Matrix&);		// �������� ������
	Matrix  operator - (const Matrix&);		// ��������� ������
	Matrix  operator * (const Matrix&);		// ��������� ������
	friend istream& operator >> <> (istream&, Matrix&);			// ���������� ��������� >> ��� ����� �������
	friend ostream& operator << <> (ostream&, const Matrix&);	// ���������� ��������� << ��� ������ �������
};

template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.n_nRows, M.n_nCols);
	for (int i = 0; i < n_nRows; i++)
		for (int j = 0; j < n_nCols; j++)
			m_cells[i][j] = M.m_cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int n_nRows, int n_nCols)
{
	AllocateCells(n_nRows, n_nCols);
	for (int i = 0; i < n_nRows; i++)
		for (int j = 0; j < n_nCols; j++)
			m_cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int n_nRows, int n_nCols, Cell* list)
{
	this->n_nRows = n_nRows;
	this->n_nCols = n_nCols;

	m_cells = new Cell * [n_nRows];

	for (int i = 0; i < n_nRows; i++) {
		m_cells[i] = new Cell[n_nCols];
		for (int j = 0; j < n_nCols; j++) {
			m_cells[i][j] = list[i * n_nCols + j];
		}
	}
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (&M == this)
		return *this;

	if (m_cells != nullptr) {
		FreeCells();
	}

	n_nRows = M.n_nRows;
	n_nCols = M.n_nCols;

	AllocateCells(n_nRows, n_nCols);

	for (int i = 0; i < n_nRows; i++) {
		for (int j = 0; j < n_nCols; j++) {
			m_cells[i][j] = M.m_cells[i][j];
		}
	}

	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (n_nRows == M.n_nRows && n_nCols == M.n_nCols)
	{
		for (int i = 0; i < n_nRows; i++)
			for (int j = 0; j < n_nCols; j++)
				res.m_cells[i][j] += M.m_cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (n_nRows == M.n_nRows && n_nCols == M.n_nCols)
	{
		for (int i = 0; i < n_nRows; i++)
			for (int j = 0; j < n_nCols; j++)
				res.m_cells[i][j] -= M.m_cells[i][j];
	}
	return res;

}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	Matrix<Cell> res(n_nRows, M.n_nCols);

	for (int i = 0; i < n_nRows; i++) {
		for (int j = 0; j < M.n_nCols; j++) {
			{
				res.m_cells[i][j] = 0;
				for (int k = 0; k < n_nCols; k++) {
					res.m_cells[i][j] += m_cells[i][k] * M.m_cells[k][j];
				}
			}
		}
	}
	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int nRows, int nCols)
{
	n_nRows = nRows;
	n_nCols = nCols;

	if (n_nRows < 0) {
		throw std::invalid_argument("Rows size must be greater than 0.");
	}

	if (n_nCols < 0) {
		throw std::invalid_argument("Rows size must be greater than 0.");
	}

	m_cells = new Cell * [n_nRows];
	for (int i = 0; i < n_nRows; i++)
		m_cells[i] = new Cell[n_nCols];
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < n_nRows; i++) {
		delete[] m_cells[i];
	}
	delete[] m_cells;
	n_nRows = 0;
	n_nCols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.n_nRows; i++)
		for (int j = 0; j < M.n_nCols; j++)
			fi >> M.m_cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.n_nRows; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.n_nCols; j++)
			fo << M.m_cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

template <typename Cell>
int Matrix<Cell>::nRows()
{
	return n_nRows;
}

template <typename Cell>
int Matrix<Cell>::nColumns()
{
	return n_nCols;
}

template <typename Cell>
void Matrix<Cell>::setVaue(int i, int j, Cell value)
{
	m_cells[i][j] = value;
}
