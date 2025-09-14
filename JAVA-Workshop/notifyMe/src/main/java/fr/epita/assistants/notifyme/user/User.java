package fr.epita.assistants.notifyme.user;

import fr.epita.assistants.notifyme.notify.INotificationSender;

import java.util.ArrayList;
import java.util.List;

public class User implements IMultiNotificationSender{
    String username;
    List<INotificationSender> parNotificationList;
    public User(final String username, final List<INotificationSender> parNotificationList) {
        this.username = username;
        this.parNotificationList = new ArrayList<>();
        this.parNotificationList.addAll(parNotificationList);
    }
    public User(final String username) {
        this.username = username;
        this.parNotificationList = new ArrayList<>();
    }
    public String getUsername() {
        return this.username;
    }
    public void sendNotifications(String parRecipient, String parMessage) {
        for (INotificationSender notifier : this.parNotificationList){
            notifier.notify(this.username, parRecipient, parMessage);
        }
    }

    public void addNotifier(INotificationSender parNotifier) {
        if (parNotifier == null)
            return;
        this.parNotificationList.add(parNotifier);
    }

    public List<INotificationSender> getNotifiers() {
        return this.parNotificationList;
    }
}
