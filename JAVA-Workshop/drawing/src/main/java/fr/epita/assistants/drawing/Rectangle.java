package fr.epita.assistants.drawing;

public class Rectangle extends Sharp {
    int width;

    public Rectangle(int width, int length) {
        super(length);
        this.width = width;
    }

    @Override
    public void draw() {
        for (int i = 1; i <= length; i++) {
            for (int j = 1; j <= width; j++) {
                if (i== 1 || i == length|| j == width || j == 1) {
                    System.out.print("#");
                    System.out.print(" ");
                } else {
                    System.out.print("  ");
                }
            }
            System.out.println();
        }
    }
}
