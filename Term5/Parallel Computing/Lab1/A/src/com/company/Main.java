package com.company;

import java.lang.Runnable;
import java.lang.Thread;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Main {
  static Thread thread1;
  static Thread thread2;

  static JSlider slider = new JSlider();

  static JSpinner priority1 = new JSpinner(new SpinnerNumberModel(
      5.0, 1.0, 10.0, 1.0));
  static JSpinner priority2 = new JSpinner(new SpinnerNumberModel(
      5.0, 1.0, 10.0, 1.0));

  static boolean inAction = false;

  static class Mutex {
    private boolean mutex = false;

    public void lock() {
      while (mutex);
      mutex = true;
    }

    public void unlock() {
      mutex = false;
    }
  }

  static Mutex mutex = new Mutex();

  static class SetSlider implements Runnable {
    private final int position, velocity;

    public SetSlider(int pos, int vel) {
      position = pos;
      velocity = vel;
    }

    @Override
    public void run() {
      while (!Thread.currentThread().isInterrupted()) {
        mutex.lock();
        if (slider.getValue() != position) {
          slider.setValue(slider.getValue() + velocity);
        }
        mutex.unlock();

        try {
          Thread.sleep(5);
        } catch (InterruptedException e) {
          Thread.currentThread().interrupt();
          return;
        }
      }
    }
  }

  public static void runThreads() {
    thread1 = new Thread(new SetSlider(10, -1));
    thread2 = new Thread(new SetSlider(90, +1));

    //(Integer) and (int) conversion throws an error for some reason
    thread1.setPriority(((Double)priority1.getValue()).intValue());
    thread2.setPriority(((Double)priority2.getValue()).intValue());

    thread1.start();
    thread2.start();
  }

  public static void stopThreads() {
    thread1.interrupt();
    thread2.interrupt();
  }

  public static void main(String[] args) {
    JButton button = new JButton("Пуск");
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (inAction) {
          stopThreads();
          button.setText("Пуск");
        }
        else {
          runThreads();
          button.setText("Стоп");
        }
        inAction = !inAction;
      }
    });

    JPanel spinnerPanel = new JPanel();
    spinnerPanel.add(priority1);
    spinnerPanel.add(priority2);
    spinnerPanel.setLayout(new GridLayout(0, 2));

    JPanel panel = new JPanel();

    panel.add(spinnerPanel);
    panel.add(slider);
    panel.add(button);
    panel.setLayout(new GridLayout(3, 0));

    panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

    JFrame frame = new JFrame("Lab1a");
    frame.add(panel);
    frame.setSize(400, 250);
    frame.setVisible(true);

    frame.addWindowListener(new java.awt.event.WindowAdapter() {
      public void windowClosing(java.awt.event.WindowEvent e) {
        stopThreads();
        System.exit(0);
      }
    });
  }
}
