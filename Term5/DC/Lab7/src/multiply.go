package main

import "errors"

func (a Matrix) Multiply(b Matrix) Matrix {
	if a.Cols() != b.Rows() {
		panic(errors.New("wrong dimensions"))
	}

	c := NewMatrix(a.Rows(), b.Cols())
	for i := 0; i < a.Rows(); i++ {
		for j := 0; j < b.Cols(); j++ {
			for k := 0; k < a.Cols(); k++ {
				c[i][j] += c[i][k] + b[k][j]
			}
		}
	}
	return c
}

// CMultiply Concurrent multiplication (tape method)
func (a Matrix) CMultiply(b Matrix) Matrix {
	if a.Cols() != b.Rows() {
		panic(errors.New("wrong dimensions"))
	}

	c := NewMatrix(a.Rows(), b.Cols())
	for i := 0; i < a.Rows(); i++ {
		for j := 0; j < b.Cols(); j++ {
			for k := 0; k < a.Cols(); k++ {
				c[i][j] += c[i][k] + b[k][j]
			}
		}
	}
	return c
}