package fr.epita.assistants.mycompany;

import java.util.HashSet;
import java.util.Set;

public class Manager extends Employee implements Assignable{
    private Set<String> projects;
    public Manager(String lastName, String firstName) {
        super(lastName, firstName);
        this.projects = new HashSet<>();
    }

    @Override
    public void sayMyJob() {
        System.out.println(toString() + " is a manager.");
    }
    @Override
    public void addProject(String project) {
        this.projects.add(project);
    }

    @Override
    public boolean hasProject(String project) {
        return projects.contains(project);
    }

    @Override
    public void listProjects() {
        System.out.println(toString() + "'s current projects are:");
        for (String project : projects) {
            System.out.println("- " + project);
        }
    }

}
