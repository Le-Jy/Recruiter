package fr.epita.assistants.observer;

public class Person implements Observable.Observer<Swimmer> {
    String name;

    public Person(String name) {
        this.name = name;
    }

    @Override
    public void onEvent(Swimmer event) {
        if (event.status == SwimmerStatus.WAVING) {
            System.out.println(this.name + ": Waves at " + event.name + ".");
        }
    }
}
