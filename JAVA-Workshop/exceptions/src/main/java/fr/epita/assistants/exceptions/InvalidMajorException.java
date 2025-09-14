package fr.epita.assistants.exceptions;

public class InvalidMajorException extends Exception {
    public InvalidMajorException(String major) {
        super("InvalidMajorException: " + major);
    }
}
