package fr.epita.assistants.war;

public class Soldier extends Combatant{
    protected int health;
    protected int damage;
    protected String scream;

    public Soldier() {
        this.health = 15;
        this.damage = 3;
        this.scream = "No pity for losers!";
    }

    public void kill() {
        this.health = 0;
    }

    @Override
    public void printState() {
        System.out.println("I have " + this.health + " health points.");
    }

    @Override
    public void attack(Soldier s) {
       s.health -= this.damage;
    }

    @Override
    void attack(Vehicle v) {
        System.out.println("I can't fight this.");
    }

    @Override
    public void scream() {
        System.out.println(this.scream);
    }
}