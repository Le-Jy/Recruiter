package fr.epita.assistants.helloworld;

public class HelloWorld {
    public void printHelloWorld() {
       String hello = "Hello World!";
       System.out.print(hello);
    }
    public void printHelloWorldErr() {
        String hello = "Hello World!";
        System.err.println(hello);
    }
}