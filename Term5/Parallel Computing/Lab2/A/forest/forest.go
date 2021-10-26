package forest

import (
	"fmt"
	"github.com/inancgumus/screen"
	"math/rand"
	"time"
)

type Position struct {
	X, Y uint
}

type Forest struct {
	Bear Position
	Bees []Position
	Size uint
	briefcase chan uint
}

// NewForest
// Forest constructor
func NewForest(fs uint, bc uint) Forest {
	f := Forest{Size: fs}
	f.Bees = make([]Position, bc)

	// Creating briefcase chan
	f.briefcase = make(chan uint)

	// Positioning bear at random point
	rand.Seed(time.Now().UnixNano())
	f.Bear.X = uint(rand.Intn(int(f.Size)))
	f.Bear.Y = uint(rand.Intn(int(f.Size)))

	return f
}

// StartBee
// Bee Coroutine that scans one line of forest
func (f *Forest) StartBee(bee *Position) {
	for task := range f.briefcase {
		bee.X = task
		for i := uint(0); i < f.Size; i++ {
			bee.Y = i
			time.Sleep(750 * time.Millisecond)

			if bee.X  == f.Bear.X && bee.Y == f.Bear.Y {
				close(f.briefcase)
			}
		}
	}
}

// Start
// Starts bees and filling the briefcaes with tasks
func (f *Forest) Start() {
	go func () {
		// Sarting bee worders
		for i := range f.Bees {
			go f.StartBee(&f.Bees[i])
		}

		// Creating tasks; Task - row to scan
		for i := uint(0); i < f.Size; i++ {
			f.briefcase <- i
		}
	} ()
}

// DisplayForest 
// Displays forest state
func (f *Forest) DisplayForest() {
	const (
		EmptyArea = 0
		BearArea = 1
		BeeArea = 2
		FoundArea = 3
	)

	screen.Clear()

	for {
		screen.MoveTopLeft()

		forest := make([][]uint8, f.Size)
		for i := range forest {
			forest[i] = make([]uint8, f.Size)
		}

		forest[f.Bear.X][f.Bear.Y] = BearArea

		for _, b := range f.Bees {
			forest[b.X][b.Y] = BeeArea
			if  b.X  == f.Bear.X && b.Y == f.Bear.Y {
				forest[b.X][b.Y] = FoundArea
			}
		}

		for _, i := range forest {
			for _, j := range i {
				if j == EmptyArea {
					fmt.Print("[ ]")
				} else if j == BearArea {
					fmt.Print("[#]")
				} else if j == BeeArea {
					fmt.Print("[%]")
				} else if j == FoundArea {
					fmt.Print("[X]")
				}
			}
			fmt.Print("\n")
		}
		time.Sleep(250 * time.Millisecond)
	}
}
