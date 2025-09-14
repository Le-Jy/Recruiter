package fr.epita.assistants.exceptions;

import java.util.ArrayList;

public class Student {
    String name;
    int age;
    String major;

    public Student(String name, int age, String major) throws InvalidNameException, InvalidAgeException, InvalidMajorException {
        ArrayList<String> majorsList = new ArrayList<>();
        majorsList.add("IMAGE");
        majorsList.add("GISTRE");
        majorsList.add("SRS");
        majorsList.add("SCIA");
        majorsList.add("MTI");
        majorsList.add("TCOM");
        majorsList.add("SIGL");
        majorsList.add("GITM");
        majorsList.add("ICE");
        majorsList.add("SANTE");
        majorsList.add("SSIE");
        majorsList.add("IF");
        majorsList.add("STARTUP");
        majorsList.add("Q");
        if (name.matches("[^0-9]*[0-9]+[^0-9]*"))
            throw new InvalidNameException(name);
        this.name = name;
        if (age <= 0 || age >= 130)
            throw new InvalidAgeException(age);
        this.age = age;
        if (!majorsList.contains(major.toUpperCase()))
            throw new InvalidMajorException(major);
        this.major = major.toUpperCase();
    }

    @Override
    public String toString() {
        return "Name: " + name + ", Age: " + age + ", Major: " + major;
    }
}
