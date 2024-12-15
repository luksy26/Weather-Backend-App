#ifndef NOTIFICATION_FACTORIES_H
#define NOTIFICATION_FACTORIES_H

#include "NotificationTypes.h"
#include <memory>

// Abstract Factory
class NotificationFactory {
  public:
	virtual std::shared_ptr<Notification> createDailyUpdateNotification() = 0;
	virtual std::shared_ptr<Notification> createSevereWeatherNotification() = 0;
	virtual ~NotificationFactory() {}
};

// Concrete Factories
class AndroidNotificationFactory : public NotificationFactory {
  public:
	std::shared_ptr<Notification> createDailyUpdateNotification() override {
		return std::make_shared<AndroidDailyUpdateNotification>();
	}

	std::shared_ptr<Notification> createSevereWeatherNotification() override {
		return std::make_shared<AndroidSevereWeatherNotification>();
	}
};

class AppleNotificationFactory : public NotificationFactory {
  public:
	std::shared_ptr<Notification> createDailyUpdateNotification() override {
		return std::make_shared<AppleDailyUpdateNotification>();
	}

	std::shared_ptr<Notification> createSevereWeatherNotification() override {
		return std::make_shared<AppleSevereWeatherNotification>();
	}
};

#endif // NOTIFICATION_FACTORIES_H
