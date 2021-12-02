package com.company;

import java.util.LinkedList;
import java.util.Queue;

class BQueue<T> {
  private final Queue<T> queue = new LinkedList<>();
  private boolean isClosed = false;

  public synchronized void put(T value) {
    queue.add(value);
    notifyAll();
  }

  public synchronized T take() {
    try {
      while (queue.isEmpty())
        wait();
    } catch (InterruptedException e) { e.printStackTrace(); }
    return queue.remove();
  }

  public int size() {
    return queue.size();
  }

  public boolean isEmpty() {
    return queue.isEmpty();
  }

  public boolean isClosed() {
    return isClosed;
  }

  public void close() {
    isClosed = true;
  }
}