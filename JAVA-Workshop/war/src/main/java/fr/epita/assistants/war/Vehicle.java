package fr.epita.assistants.war;

public class Vehicle extends Combatant {
    String name;
    int defense;

    public Vehicle(String name, int defense) {
        this.name = name;
        this.defense = defense;
    }

    @Override
    public void printState() {
        System.out.println("I have " + this.defense + " defense points.");
    }

    @Override
    void attack(Soldier s) {
        s.kill();
    }

    @Override
    public void attack(Vehicle v) {
        v.defense /= 2;
    }

    @Override
    public void scream() {
        System.out.println("I'm " + this.name + '!');
    }
}
