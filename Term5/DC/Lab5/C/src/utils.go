package main

import (
	"strings"
)

func genArrays(size, count int) []*Array {
	arrs := make([]*Array, count)
	for i := range arrs {
		arrs[i] = NewArray(size, i)
	}
	return arrs
}

func arraysToString(arrs []*Array) string {
	sb := strings.Builder{}
	for i := range arrs {
		sb.WriteString(arrs[i].String() + "\n")
	}
	return sb.String()
}

func isSumEqual(arrs []*Array) (bool, int) {
	eq, avg := true, 0
	prevSum := -1
	for _, a := range arrs {
		sum := a.sum
		if sum != prevSum && prevSum != -1 {
			eq = false
		}
		avg += sum
		prevSum = sum
	}
	avg /= len(arrs)
	return eq, avg
}
