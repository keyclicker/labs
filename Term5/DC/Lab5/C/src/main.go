package main

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

func changer(arrs []*Array, index int, wg *sync.WaitGroup) {
	for {
		eq, avg := isSumEqual(arrs)
		fmt.Printf("From goroutine-%d\n%sequal: %s\n\n",
			index, arraysToString(arrs), strconv.FormatBool(eq))

		if eq {
			wg.Done()
			return
		}

		arrs[index].Modify(avg)

		time.Sleep(10 * time.Millisecond)
	}
}

func main() {
	arrs := genArrays(5, 3)
	print(arraysToString(arrs))

	wg := sync.WaitGroup{}

	for i := range arrs {
		wg.Add(1)
		go changer(arrs, i, &wg)
	}

	wg.Wait()
}
