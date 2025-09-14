package fr.epita.assistants.exceptions;

public class InvalidAgeException extends Exception {
    public InvalidAgeException(int age) {
        super("InvalidAgeException: " + age);
    }
}
