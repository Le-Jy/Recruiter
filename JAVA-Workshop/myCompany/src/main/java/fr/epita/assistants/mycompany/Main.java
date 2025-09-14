package fr.epita.assistants.mycompany;

public class Main {
    public static void main(String[] args) {
        Secretary s1 = new Secretary("Compiler", "Tigrou");
        Engineer e1 = new Engineer("Ritchie", "Dennis");
        Manager m1 = new Manager("Thompson", "Ken");
        Manager m2 = new Manager("Appel", "Andrew");
        Engineer e2 = new Engineer("Smith", "John");
        Manager m3 = new Manager("Toy", "Spidou");
        s1.sayMyName();
        s1.sayMyJob();
        e1.sayMyName();
        e1.sayMyJob();
        m1.sayMyName();
        m1.sayMyJob();
        System.out.println("---");
        Company labCompiling = new Company("labCompiling");
        labCompiling.hire(s1);
        labCompiling.hire(e1);
        labCompiling.hire(m1);
        labCompiling.hire(m2);
        labCompiling.printEmployees();
        System.out.println("---");
        System.out.println(labCompiling.addEmployeeManagement(e1, m1));
        System.out.println(labCompiling.addEmployeeManagement(s1, m1));
        System.out.println(labCompiling.addEmployeeManagement(s1, m2));
        System.out.println(labCompiling.addEmployeeManagement(e2, m2));
        System.out.println(labCompiling.addEmployeeManagement(e2, m3));
        System.out.println("---");
        labCompiling.printManager(e1);
        labCompiling.printManager(s1);
        labCompiling.printManager(m2);
    }
}
