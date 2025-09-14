package fr.epita.assistants.singleton;

import fr.epita.assistants.logger.Logger;

public enum SingletonEnumLogger implements Logger {
    INSTANCE();
    int warnCounter;
    int errorCounter;
    int infoCounter;

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
}
