package com.company;

import java.lang.Runnable;
import java.lang.Thread;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Main {
  static JSlider slider = new JSlider();

  static class SetSlider implements Runnable {
    private final int position;

    public SetSlider(int pos) {
      position = pos;
    }

    @Override
    public void run() {
      slider.setValue(position);
    }
  }

  public static void runThreads() {
    Thread thread1 = new Thread(new SetSlider(10));
    Thread thread2 = new Thread(new SetSlider(90));

    thread1.setPriority(2);
    thread2.setPriority(1);

    thread1.start();
    thread2.start();
  }

  public static void main(String[] args) {
    JButton button = new JButton("Пуск");
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        runThreads();
      }
    });

    JPanel panel = new JPanel();
    panel.add(slider);
    panel.add(button);
    panel.setLayout(new GridLayout(2, 0));

    panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));


    JFrame frame = new JFrame("Lab1a");
    frame.add(panel);
    frame.setSize(400, 400);
    frame.setVisible(true);
  }
}
