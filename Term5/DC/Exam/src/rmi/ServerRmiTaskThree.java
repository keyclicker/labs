
package rmi;

import model.Patient;

import java.rmi.Remote;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Server {
  public static void main(String[] args) throws Exception {
    Registry registry = LocateRegistry.createRegistry(5000);
    RMI service = new Service();
    registry.rebind("hospital", service);
    System.out.println("server started");
  }

  static class Service extends UnicastRemoteObject implements RMI {
    List<Patient> patients;

    Service() throws Exception {
      super();
      patients = Patient.getList();
    }

    @Override
    public List<Patient> displayInterval(Integer a, Integer b) {
      List<Patient> results = new ArrayList<>();
      for(Patient patient: patients) {
        if(patient.getMedId() > a && patient.getMedId() < b) {
          results.add(patient);
        }
      }
      return results;
    }

    @Override
    public List<Patient> displayAlphabetic() {
      List<Patient> results = patients;
      Collections.sort(results);
      return results;
    }
  }
}

interface RMI extends Remote {
  List<Patient> displayInterval(Integer a, Integer b) throws Exception;
  List<Patient> displayAlphabetic() throws Exception;
}
