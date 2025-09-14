package fr.epita.assistants.notifyme.notify;

public interface INotificationSender {
    /**
     * Entrypoint to send notifications.
     * @param parMessage the message to use for the notification - may be discarded by the implementation
     */
    void notify(final String parSender, final String parReceiver, final String parMessage);
}
