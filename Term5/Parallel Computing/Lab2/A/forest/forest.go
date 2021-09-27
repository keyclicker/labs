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
	isFinished bool
}

func (f *Forest) StartBeeWorker(bee *Position, brc *Briefcase) {
	task, finish := brc.GetTask()
	for !finish {
		for i := uint(0); i < f.Size; i++ {
			bee.X = task
			bee.Y = i

			time.Sleep(750 * time.Millisecond)

			if bee.X  == f.Bear.X && bee.Y == f.Bear.Y {
				f.isFinished = true;
			}
		}
		task, finish = brc.GetTask()
	}
}

func (f *Forest) CreateBees(n uint) {
	f.Bees = make([]Position, n)
}

func (f *Forest) Start() {
	brc := Briefcase{Forest: f}

	rand.Seed(time.Now().UnixNano())
	f.Bear.X = uint(rand.Intn(int(f.Size)))
	f.Bear.Y = uint(rand.Intn(int(f.Size)))

	for i := range f.Bees {
		go f.StartBeeWorker(&f.Bees[i], &brc)
	}
}

func (f *Forest) DisplayForest() {
	const (
		EmptyArea = 0
		BearArea = 1
		BeeArea = 2
		FoundArea = 3
	)

	screen.Clear()

	for !f.isFinished {
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
