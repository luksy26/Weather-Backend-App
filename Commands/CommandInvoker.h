// File: CommandInvoker.h
#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include "Command.h"
#include <memory>
#include <queue>

class CommandInvoker {
  private:
	std::queue<std::shared_ptr<Command>> commandQueue;

  public:
	void addCommand(const std::shared_ptr<Command> &cmd) {
		commandQueue.push(cmd);
	}

	void executeCommands() {
		while (!commandQueue.empty()) {
			auto cmd = commandQueue.front();
			commandQueue.pop();
			cmd->execute();
		}
	}
};

#endif // COMMAND_INVOKER_H
