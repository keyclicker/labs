package main

import (
	"github.com/inancgumus/screen"
)

func main() {
	screen.Clear()

	const (
		ForestSize = 10
		BeeCount   = 5
	)

	f := NewForest(ForestSize, BeeCount)

	go f.Start()
	f.DisplayForest()
}
