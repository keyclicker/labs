package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const maxCount = 10

var (
	pot        int
	pm         sync.Mutex
	full       = make(chan bool)
	beeCounter int
)

func bee() {
	id := beeCounter
	beeCounter++
	for {
		time.Sleep(time.Duration(rand.Float32()*5.0) * time.Second)
		pm.Lock()
		if pot < maxCount {
			pot++
			fmt.Printf("[%v] <- Bee %v\n", pot, id)
			if pot == maxCount {
				full <- true
			}
		}
		pm.Unlock()
	}
}

func bear() {
	for range full {
		time.Sleep(time.Duration(rand.Float32()*2.0) * time.Second)
		pm.Lock()
		pot = 0
		pm.Unlock()
		fmt.Printf("[%v] -> Bear ate all honey!\n", pot)
	}
}

func main() {
	go bear()
	for i := 0; i < 10; i++ {
		go bee()
	}
	<-make(chan int)
}
