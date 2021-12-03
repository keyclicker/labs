package main

import (
	"fmt"
	"math/rand"
	"strings"
)

type Vector []float32
type Matrix []Vector


func NewMatrix(r, c int) Matrix {
	m := make(Matrix, r)
	for i := range m {
		m[i] = make(Vector, c)
		for j := range m[i] {
			m[i][j] = 0
		}
	}
	return m
}

func RandMatrix(r, c int) Matrix {
	m := NewMatrix(r, c)
	for i := range m {
		for j := range m[i] {
			m[i][j] = rand.Float32() * 100.0
		}
	}
	return m
}

func (m Matrix) Rows() int {
	return len(m)
}

func (m Matrix) Cols() int {
	return len(m[0])
}

func (m Matrix) String() string {
	sb := strings.Builder{}
	for i := range m {
		sb.WriteString("| ")
		for j := range m[i] {
			sb.WriteString(fmt.Sprintf(" %4.1f ", m[i][j]))
		}
		sb.WriteString(" |\n")
	}
	return sb.String()
}

