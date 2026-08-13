#pragma once
#include "../../repository/BaseRepository.h"

class Action {
protected:
	BaseRepository& repository;
public:
	Action(BaseRepository& repo);
	virtual ~Action() = default;

	virtual void undo() = 0;
	virtual void redo() = 0;
};

class ActionAdd : public Action {
private:
	Dog dog;
public:
	ActionAdd(BaseRepository& repository, Dog dog);
	void undo() override;
	void redo() override;
};

class ActionRemove : public Action {
private:
	Dog dog;
public:
	ActionRemove(BaseRepository& repository, Dog dog);
	void undo() override;
	void redo() override;
};

class ActionUpdate : public Action {
private:
	Dog oldDog, newDog;
public:
	ActionUpdate(BaseRepository& repository, Dog oldDog, Dog newDog);
	void undo() override;
	void redo() override;
};