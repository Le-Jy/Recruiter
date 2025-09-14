package fr.epita.assistants.mycompany;

import java.util.ArrayList;
import java.util.HashMap;

public class Company {
    String name;
    ArrayList<Employee> employees;
    HashMap<Employee, Manager> employeeManagement;


    public Company(String name) {
        this.name = name;
        employees = new ArrayList<>();
        employeeManagement = new HashMap<>();
    }

    public int size() {
        return employees.size();
    }

    public void hire(Employee p) {
        employees.add(p);
    }

    public void fire(Employee p) {
        employees.remove(p);
    }

    public void printEmployees () {
        System.out.println("The company " + this.name + " employs:");
        for (int i = 0 ; i < size(); i++) {
            System.out.println("- " + employees.get(i).toString());
        }
    }

    public boolean addEmployeeManagement(Employee e, Manager m) {
        boolean interrupt = false;
        if (!employees.contains(e)) {
            System.out.println(e.toString() + " is not employed by " + name + ".");
            interrupt =  true;
        }
        if (!employees.contains(m)) {
            System.out.println(m.toString() + " is not employed by " + name + ".");
            interrupt = true;
        }
        if (interrupt)
            return false;
        if (employeeManagement.get(e) == null) {
                System.out.println(e.toString() + " now has a manager.");
                employeeManagement.put(e, m);
            }
        else {
                System.out.println(e.toString() + " has a new manager.");
                employeeManagement.replace(e, m);
            }
        return true;
    }

    public void printManager(Employee e) {
        if (employeeManagement.containsKey(e)) {
            Manager manager = employeeManagement.get(e);
            if (manager != null) {
                System.out.println(manager + " manages " + e + ".");
            } else {
                System.out.println(e + " is managed by nobody.");
            }
        } else {
            System.out.println(e + " is managed by nobody.");
        }
    }
    public void printEmployeesProject() {
        for (Employee employee : employees) {
            if (employee instanceof Assignable assignableEmployee) {
                assignableEmployee.listProjects();
            }
        }
    }
}
