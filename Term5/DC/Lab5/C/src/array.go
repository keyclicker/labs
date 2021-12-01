package main

import (
	"fmt"
	"math/rand"
	"strings"
	"sync"
)

type Array struct {
	arr []int
	sum int
	ind int // index
	m   sync.RWMutex
}

func NewArray(n int, i int) *Array {
	a := new(Array)
	a.arr = make([]int, n)
	for j := range a.arr {
		a.arr[j] = rand.Intn(100)
		a.sum += a.arr[j]
	}
	return a
}

func (a *Array) String() string {
	a.m.RLock()
	defer a.m.RUnlock()

	sb := strings.Builder{}
	sb.WriteString(fmt.Sprintf("Array-%d: [", a.ind))
	for j := 0; j < len(a.arr)-1; j++ {
		sb.WriteString(fmt.Sprintf("%d, ", a.arr[j]))
	}
	sb.WriteString(fmt.Sprintf("%d] sum: %d", a.arr[len(a.arr)-1], a.sum))
	return sb.String()
}

func (a *Array) Modify(goal int) {
	a.m.Lock()
	defer a.m.Unlock()

	i := rand.Intn(len(a.arr))
	switch {
	case a.sum < goal:
		a.arr[i]++
		a.sum++
	case a.sum > goal:
		a.arr[i]--
		a.sum--
	}
}
