package fr.epita.assistants;

import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import fr.epita.assistants.loggingThreads.*;
import org.slf4j.LoggerFactory;

public class Main {

    static private final Logger LOGGER = (Logger) LoggerFactory.getLogger(Main.class);

    public static void main(String[] args) throws InterruptedException {
        // FIXME: Add startup logging here
        LOGGER.setLevel(Level.INFO);
        LOGGER.info("Entering application");

        TimeWaster waster = new TimeWaster();

        Thread sum = new Thread(() -> waster.sumUpTo(123456789));
        Thread importantThing = new Thread(() -> {
                waster.doImportantThing();
        });

        sum.start();
        importantThing.start();

        // FIXME: Manually interrupt importantThing to test your output
        importantThing.interrupt();

        sum.join();
        importantThing.join();

        LOGGER.info("Clean application exit");
    }
}