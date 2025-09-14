package fr.epita.assistants.observer;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Swimmer implements Observable<Swimmer>{
    Set<Observer<Swimmer>> observers;

    String name;

    SwimmerStatus status;

    public Swimmer(String name) {
        this.name = name;
        this.status = SwimmerStatus.OK;
        this.observers = new HashSet<>();
        System.out.println(this.name + " goes into the sea.");
    }

    public void setStatus(SwimmerStatus swimmerStatus) {
        this.status = swimmerStatus;
        if (swimmerStatus == SwimmerStatus.DROWNING) {
            System.out.println(this.name + ": I'm drowning, help!!");
        }
        else if (swimmerStatus == SwimmerStatus.WAVING) {
            System.out.println(this.name + ": Waves towards the shore.");
        }
        this.fire(this);

    }

    @Override
    public Set<Observer<Swimmer>> getObservers() {
        return this.observers;
    }

    @Override
    public void register(Observer<Swimmer>... observers) {
        Collections.addAll(this.observers, observers);
    }

    @Override
    public void unregister(Observer<Swimmer> observer) {
        this.observers.remove(observer);
    }

    @Override
    public void fire(Swimmer event) {
        this.observers.forEach( O -> O.onEvent(event));
    }

    public String getName() {
        return name;
    }

    public SwimmerStatus getStatus() {
        return status;
    }
}
