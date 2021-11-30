package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

func (g *Garden) Gardener() {
	x, y := len(g.p)/2, len(g.p)/2 // pos
	for {
		g.water(x, y, rand.Float32()*15.0)

		x += rand.Intn(2)*2 - 1
		y += rand.Intn(2)*2 - 1

		if x < 0 {
			x = 0
		}
		if y < 0 {
			y = 0
		}
		if x >= len(g.p) {
			x = len(g.p) - 1
		}
		if y >= len(g.p) {
			y = len(g.p) - 1
		}

		time.Sleep(time.Millisecond * 10)
	}
}

func (g *Garden) Nature() {
	for {
		a := rand.Intn(500) // 0 - rain, !0 - draining
		if a == 0 {
			for i := range g.p {
				for j := range g.p[i] {
					g.water(i, j, rand.Float32()*15.0)
				}
			}
		} else {
			for i := range g.p {
				for j := range g.p[i] {
					g.water(i, j, -rand.Float32()*0.05)
				}
			}
		}
		time.Sleep(time.Millisecond * 10)
	}
}

func (g *Garden) FileMonitor() {
	f, _ := os.Create("output.txt")
	defer f.Close()
	for {
		f.WriteString(g.String() + "\n")
		time.Sleep(time.Millisecond * 1000)
	}
}

func (g *Garden) TerminalMonitor() {
	for {
		fmt.Println(g)
		time.Sleep(time.Millisecond * 100)
	}
}

func main() {
	g := NewGarden(10)
	go g.Nature()
	go g.Gardener()
	go g.FileMonitor()
	g.TerminalMonitor()
}
