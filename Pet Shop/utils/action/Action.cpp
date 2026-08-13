#include "Action.h"

Action::Action(BaseRepository& repo) : repository(repo){ }

ActionAdd::ActionAdd(BaseRepository& repository, Dog dog) : Action(repository), dog(dog) { }

void ActionAdd::undo()
{
	repository.removeDog(dog);
}

void ActionAdd::redo()
{
	repository.addDog(dog);
}

ActionRemove::ActionRemove(BaseRepository& repository, Dog dog): Action(repository), dog(dog) { }

void ActionRemove::undo()
{
	repository.addDog(dog);
}

void ActionRemove::redo()
{
	repository.removeDog(dog);
}

ActionUpdate::ActionUpdate(BaseRepository& repository, Dog oldDog, Dog newDog): Action(repository), oldDog(oldDog), newDog(newDog) {}

void ActionUpdate::undo()
{
	repository.removeDog(newDog);
	repository.addDog(oldDog);
}

void ActionUpdate::redo()
{
	repository.removeDog(oldDog);
	repository.addDog(newDog);
}
