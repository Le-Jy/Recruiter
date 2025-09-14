package fr.epita.assistants.observer;

public class Lifeguard implements Observable.Observer<Swimmer> {
    String name;

    public Lifeguard(String name) {
        this.name = name;
        System.out.println(this.name + " begins to keep an eye on the swimmers.");
    }

    @Override
    public void onEvent(Swimmer event) {
        if (event.status == SwimmerStatus.DROWNING) {
            System.out.println(this.name + ": I will save you " + event.name + "!");
        }
        else if (event.status == SwimmerStatus.TOO_FAR) {
            System.out.println(this.name + ": " + event.name + "!" + " You are too far, come back!");
        }

    }
}
