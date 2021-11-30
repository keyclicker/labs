package main

import (
	"fmt"
	"math/rand"
	"sync"
)

type Plant float32
type Garden struct {
	p [][]Plant // plants
	m sync.RWMutex
}

func NewGarden(d int) Garden {
	g := make([][]Plant, d)
	for i := range g {
		g[i] = make([]Plant, d)
		for j := range g[i] {
			g[i][j] = Plant(rand.Float32() * 100.0)
		}
	}
	return Garden{g, sync.RWMutex{}}
}

func (g *Garden) String() string {
	g.m.RLock()
	defer g.m.RUnlock()

	var ret string
	for i := range g.p {
		for j := range g.p[i] {
			ret += fmt.Sprintf("%5.0f ", g.p[i][j])
		}
		ret += "\n"
	}
	return ret
}

func (g *Garden) water(x, y int, d float32) {
	g.m.Lock()
	defer g.m.Unlock()

	g.p[x][y] += Plant(d)
	switch {
	case g.p[x][y] > 100:
		g.p[x][y] = 100
	case g.p[x][y] < 0:
		g.p[x][y] = 0
	}
}
