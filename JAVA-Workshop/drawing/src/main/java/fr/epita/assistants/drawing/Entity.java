package fr.epita.assistants.drawing;

import lombok.Getter;

public abstract class Entity implements IDrawable {
    @Getter
    private final long id;
    private static long SEQUENCE = 0;

    public Entity() {
        this.id = SEQUENCE;
        SEQUENCE++;
    }

    @Override
    public abstract void draw();
}
