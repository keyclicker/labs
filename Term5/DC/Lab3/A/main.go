package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const maxCount = 10

type Pot struct {
	honey int
	mutex sync.Mutex
	full  *sync.Cond
}

func NewPot() *Pot {
	pot := new(Pot)
	pot.honey = 0
	pot.full = sync.NewCond(&pot.mutex)
	return pot
}

func (pot *Pot) bee(id int) {
	for {
		time.Sleep(time.Duration(rand.Float32()*5.0) * time.Second)
		pot.mutex.Lock()
		if pot.honey < maxCount {
			pot.honey++
			fmt.Printf("[%v] <- Bee %v\n", pot.honey, id)
			if pot.honey == maxCount {
				pot.full.Signal()
			}
		}
		pot.mutex.Unlock()
	}
}

func (pot *Pot) bear() {
	for {
		pot.mutex.Lock()
		pot.full.Wait()
		time.Sleep(time.Duration(rand.Float32()*2.0) * time.Second)
		pot.honey = 0
		fmt.Printf("[%v] -> Bear ate all honey!\n", pot.honey)
		pot.mutex.Unlock()
	}
}

func main() {
	pot := NewPot()

	go pot.bear()
	for i := 0; i < 10; i++ {
		go pot.bee(i)
	}
	<-make(chan int)
}
