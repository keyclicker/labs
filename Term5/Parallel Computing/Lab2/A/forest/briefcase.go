package forest

import "sync"

type Briefcase struct {
	Forest *Forest
	index uint
	m sync.Mutex
}

func (b *Briefcase) GetTask() (r uint, f bool) {
	b.m.Lock()
	defer b.m.Unlock()
	if b.index >= b.Forest.Size {
		return 0, true
	}
	b.index++
	return b.index - 1, false
}
