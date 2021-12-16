package sockets;

import model.Patient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Callback {
  public boolean shouldEnd = false;
}

class PatientIterator implements Runnable {
  private Socket socket;
  private Callback callback;
  private List<Patient> patients;

  public PatientIterator(Socket socket, Callback callback, List<Patient> patients) {
    this.callback = callback;
    this.socket = socket;
    this.patients = patients;
  }

  @Override
  public void run() {
    try {
      InputStreamReader ois = new InputStreamReader(socket.getInputStream());
      System.out.println("Receiving input");
      BufferedReader reader = new BufferedReader(ois);
      String message = reader.readLine();
      String splitMessage[] = message.split("#");
      String commandIndex = splitMessage[0];
      System.out.println("Command " + splitMessage[0]);

      if (commandIndex.equals("3")) {
        System.out.println("Close command");
        callback.shouldEnd = true;
        return;
      }

      List<Patient> result = new ArrayList<>();
      switch (commandIndex) {
        case "1": {
          result = patients;
          Collections.sort(result);
          break;
        }
        case "2": {
          Integer x = Integer.parseInt(splitMessage[1]);
          Integer y = Integer.parseInt(splitMessage[2]);
          for (Patient patient : patients) {
            if (patient.getMedId() > x && patient.getMedId() < y) {
              result.add(patient);
            }
          }
          break;
        }
      }

      ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
      oos.writeObject(result);
      ois.close();
      oos.close();
      socket.close();
    } catch (IOException e) {
    }
  }
}

class Server {
  private static ServerSocket server;

  private static int port = 5000;

  public static Callback c = new Callback();

  public static void main(String args[]) throws Exception {
    server = new ServerSocket(port);
    var patients = Patient.getList();

    while (!c.shouldEnd) {
      System.out.println("Waiting for the client request");
      Socket socket = server.accept();
      PatientIterator iterator = new PatientIterator(socket, c, patients);
      iterator.run();
    }
    System.out.println("Shutting down Socket server!!");
    server.close();
  }
}
