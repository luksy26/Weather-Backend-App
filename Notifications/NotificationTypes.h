#ifndef NOTIFICATION_TYPES_H
#define NOTIFICATION_TYPES_H

#include <iostream>
#include <string>

// Abstract Product for Notifications
class Notification {
  public:
	virtual void notify(const std::string &user,
						const std::string &location) = 0;
	virtual ~Notification() {}
};

// Concrete Products: Daily Update Notifications
class AndroidDailyUpdateNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location) override {
		std::cout << "[Android] Daily Update for " << user << " at " << location
				  << std::endl;
	}
};

class AppleDailyUpdateNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location) override {
		std::cout << "[Apple] Daily Update for " << user << " at " << location
				  << std::endl;
	}
};

// Concrete Products: Severe Weather Notifications
class AndroidSevereWeatherNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location) override {
		std::cout << "[Android] Severe Weather Alert for " << user << " at "
				  << location << std::endl;
	}
};

class AppleSevereWeatherNotification : public Notification {
  public:
	void notify(const std::string &user, const std::string &location) override {
		std::cout << "[Apple] Severe Weather Alert for " << user << " at "
				  << location << std::endl;
	}
};

#endif // NOTIFICATION_TYPES_H