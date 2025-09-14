package fr.epita.assistants.loggingThreads;

import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import org.slf4j.LoggerFactory;

import java.math.*;

public class TimeWaster {
    private final Logger LOGGER;

    public TimeWaster() {
        LOGGER = (Logger) LoggerFactory.getLogger(TimeWaster.class);
    }

    /**
     * @param n Last natural number to sum
     * @return The sum of integers from 0 to n
     */
    public BigInteger sumUpTo(int n) {
        LOGGER.setLevel(Level.TRACE);
        LOGGER.trace("Calculating");

        BigInteger sum = BigInteger.ZERO;
        for (int i = 1; i <= n; i++) {
            sum = sum.add(BigInteger.valueOf(i));
        }
        LOGGER.setLevel(Level.DEBUG);
        LOGGER.debug("Finished calculating sum up to " +n+": "+sum);

        return sum;
    }

    public void doImportantThing() {
        LOGGER.setLevel(Level.INFO);
        LOGGER.info("Waiting");
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            LOGGER.setLevel(Level.ERROR);
            LOGGER.error("Wait interrupted");
            return;
        }
            LOGGER.info("Successfully waited");
    }
}
