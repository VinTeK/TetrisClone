#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > matrix_t;

void printMatrix(const matrix_t& mat) {
    for (size_t i = 0; i < mat.size(); ++i) {
	for (size_t j = 0; j < mat[i].size(); ++j) {
	    cout << mat[i][j] << " ";
	}
	cout << endl;
    }
    cout << endl;
}

/* [M x N] matrices; not in-place */
matrix_t transpose(const matrix_t& mat) {
    if (mat.size() == 0)
	return mat;

    matrix_t ret(mat[0].size());

    for (size_t i = 0; i < mat[0].size(); ++i) {
	vector<int> row(mat.size());
	for (size_t j = 0; j < mat.size(); ++j) {
	    row[j] = mat[j][i];
	}
	ret[i] = row;
    }
    return ret;
}

void reverseRows(matrix_t& mat) {
    int h = mat.size();
    for (int i = 0; i < h; ++i)
	reverse(mat[i].begin(), mat[i].end());
}

void reverseCols(matrix_t& mat) {
    int h = mat.size(), w = mat[0].size();
    /* Column-major algorithm. This kills the locality. */
    for (int i = 0; i < w; ++i) {
	for (int j = 0; j < h/2; ++j)
	    std::swap(mat[j][i], mat[h-1-j][i]);
    }
}

void rotateCW(matrix_t& mat) {
    mat = transpose(mat);
    reverseRows(mat);
}

void rotateCounterCW(matrix_t& mat) {
    reverseRows(mat);
    mat = transpose(mat);
}

int main() {
    /*
    int mat[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int h = sizeof(mat)/sizeof(mat[0]), w = sizeof(mat[0])/sizeof(int);
    matrix_t m(h);
    for (int i = 0; i < h; ++i)
	m[i] = vector<int>(mat[i], mat[i]+w);
    */
    /* Large matrix test. */
    matrix_t m(2000);
    for (size_t i = 0; i < m.size(); ++i)
	m[i] = vector<int>(4000);

    rotateCW(m);

    return 0;
}
