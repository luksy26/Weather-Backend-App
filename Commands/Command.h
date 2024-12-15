// File: Command.h
#ifndef COMMAND_H
#define COMMAND_H

#include "../Proxy/WeatherService.h"
#include "../WeatherClient.h"

class Command {
  public:
	virtual void execute() = 0; // Executes the command
	virtual ~Command() {}
};

#endif // COMMAND_H
