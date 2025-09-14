package fr.epita.assistants.exceptions;

public class InvalidNameException extends Exception {
    public InvalidNameException(String name) {
        super("InvalidNameException: " + name);
    }
}
