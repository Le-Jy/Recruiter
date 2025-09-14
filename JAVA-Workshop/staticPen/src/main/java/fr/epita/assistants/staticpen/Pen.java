package fr.epita.assistants.staticpen;

public class Pen {

    public enum Color {
        RED,
        BLUE
    };
    static int nb_inst = 0;
    static int nb_red = 0;
    static int nb_blue = 0;
    Color color;

    public Pen(final Color color) {
        this.color = color;
        nb_inst++;
        if (color == Color.RED)
            nb_red++;
        else
            nb_blue++;
    }

    public static int getRedPenCounter() {
        return nb_red;
    }

    public static int getPenCounter() {
        return nb_inst;
    }

    public static int getBluePenCounter() {
        return nb_blue;
    }

    public void changeColor(final Color color) {
        this.color = color;
        if (color == Color.RED){
            nb_red++;
            nb_blue--;
        }
        else {
            nb_red--;
            nb_blue++;
        }
    }

    public static void resetCounts() {
        nb_red = 0;
        nb_blue = 0;
        nb_inst = 0;
    }

    public void print() {
        if (this.color == Color.RED)
            System.out.println("I'm a RED pen.");
        else
            System.out.println("I'm a BLUE pen.");
    }
}
