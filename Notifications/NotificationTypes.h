#ifndef NOTIFICATION_TYPES_H
#define NOTIFICATION_TYPES_H

#include <iostream>
#include <string>

// Abstract Product for Notifications
class Notification {
  public:
	virtual void notify(const std::string &user, const std::string &location,
						const std::string &weatherCondition) = 0;
	virtual ~Notification() {}
};

// Concrete Products: Daily Update Notifications
class AndroidDailyUpdateNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location,
				const std::string &weatherCondition) override {}
};

class AppleDailyUpdateNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location,
				const std::string &weatherCondition) override {}
};

// Concrete Products: Severe Weather Notifications
class AndroidSevereWeatherNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location,
				const std::string &weatherCondition) override {}
};

class AppleSevereWeatherNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location,
				const std::string &weatherCondition) override {}
};

#endif // NOTIFICATION_TYPES_H