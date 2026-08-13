#pragma once
#include <exception>
#include "../utils/action/Action.h"

class UndoException : public std::exception {
private:
	std::string message;
public:
	explicit UndoException(std::string message = "Undo Exception");
	[[nodiscard]] const char* what() const noexcept override;
};

class UndoService {
private:
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;
public:
	void addAction(std::unique_ptr<Action> action);
	void undo();
	void redo();
};