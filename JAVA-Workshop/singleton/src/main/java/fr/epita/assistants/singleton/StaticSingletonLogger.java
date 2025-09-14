package fr.epita.assistants.singleton;

import fr.epita.assistants.logger.Logger;

public class StaticSingletonLogger implements Logger {
    int warnCounter;
    int errorCounter;
    int infoCounter;

    private StaticSingletonLogger() {
        this.warnCounter = 0;
        this.errorCounter = 0;
        this.infoCounter = 0;
    }

    @Override
    public void log(Level level, String message) {
        System.err.println(Logger.getFormattedLog(level, message));
        if (level == Level.ERROR)
            this.errorCounter++;
        else if (level == Level.INFO)
            this.infoCounter++;
        else if (level == Level.WARN)
            this.warnCounter++;
    }

    @Override
    public int getInfoCounter() {
        return this.infoCounter;
    }

    @Override
    public int getWarnCounter() {
        return this.warnCounter;
    }

    @Override
    public int getErrorCounter() {
        return this.errorCounter;
    }

    @Override
    public void reset() {
        this.warnCounter = 0;
        this.infoCounter = 0;
        this.errorCounter = 0;
    }

    private static class InstanceHolder {
        private static final StaticSingletonLogger _INSTANCE = new StaticSingletonLogger();
    }

    public static StaticSingletonLogger getInstance() {
        return InstanceHolder._INSTANCE;
    }
}
