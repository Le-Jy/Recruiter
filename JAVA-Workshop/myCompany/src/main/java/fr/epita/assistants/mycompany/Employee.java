package fr.epita.assistants.mycompany;

public abstract class Employee {
    String lastName;
    String firstName;

    public Employee(String lastName, String firstName) {
        this.lastName = lastName;
        this.firstName = firstName;
    }
    @Override
    public String toString() {
        return new String(this.firstName +" "+ this.lastName);
    }

    public String getLastName() {
        return this.lastName;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public void sayMyName() {
        System.out.println("My name is "+  toString()+".");
    }

    public abstract void sayMyJob();
}
