package fr.epita.assistants.myebook;

public interface IUpdatable {
    // Return the current firmware version of the device.
    double getVersion();
    // Update the device to a newer firmware. If called with

    // an older firmware, should do nothing.
    void update(double version);
}
