package com.company;

import java.lang.Runnable;
import java.lang.Thread;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Main {
  static JFrame frame = new JFrame("Unlocked");
  static JSlider slider = new JSlider();

  static Thread thread1;
  static Thread thread2;

  static int lockedBy = 0;

  static public void lock(int by) {
    lockedBy = by;
    frame.setTitle("Locked by " + lockedBy);
  }

  static public void unlock() {
    lockedBy = 0;
    frame.setTitle("Unlocked");
  }


  static class SetSlider implements Runnable {
    private final int position;

    public SetSlider(int pos) {
      position = pos;
    }

    @Override
    public void run() {
      slider.setValue(position);

      try {
        Thread.sleep(3000);
      } catch (InterruptedException ex) {
        ex.printStackTrace();
      }

      unlock();
    }
  }

  public static void showError() {
    JOptionPane.showMessageDialog(frame, "Зайнято потоком " + lockedBy);
  }

  public static void main(String[] args) {
    JButton start1 = new JButton("Пуск1");
    JButton start2 = new JButton("Пуск2");
    JButton stop1 = new JButton("Стоп1");
    JButton stop2 = new JButton("Стоп2");

    start1.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (lockedBy == 0) {
          lock(1);
          thread1 =  new Thread(new SetSlider(10));
          thread1.setPriority(1);
          thread1.start();
        }
        else {
          showError();
        }
      }
    });

    start2.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (lockedBy == 0) {
          lock(2);
          thread2 =  new Thread(new SetSlider(90));
          thread2.setPriority(10);
          thread2.start();
        }
        else {
          showError();
        }
      }
    });

    stop1.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (lockedBy != 2) {
          unlock();
          thread1.stop();
        }
        else {
          showError();
        }
      }
    });

    stop2.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (lockedBy != 1) {
          unlock();
          thread1.stop();
        }
        else {
          showError();
        }
      }
    });

    JPanel panel = new JPanel();
    panel.add(slider);
    panel.add(start1);
    panel.add(start2);
    panel.add(stop1);
    panel.add(stop2);
    panel.setLayout(new GridLayout(5, 0));

    panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

    frame.add(panel);
    frame.setSize(400, 400);
    frame.setVisible(true);
  }
}
