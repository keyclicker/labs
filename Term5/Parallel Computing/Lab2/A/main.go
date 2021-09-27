package main

import (
	"A/forest"
	"fmt"
	"github.com/inancgumus/screen"
)

func main() {
	screen.Clear()

	var fs, bc uint
	fmt.Print("Choose forest size: ")
	fmt.Scan(&fs)
	fmt.Print("Choose bee count: ")
	fmt.Scan(&bc)

	f := forest.Forest{Size: fs}
	f.CreateBees(bc)

	f.Start()
	f.DisplayForest()
	fmt.Scan(&fs)
}
