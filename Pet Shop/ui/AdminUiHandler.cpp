#include "AdminUiHandler.h"

AdminUiHandler::AdminUiHandler(AdminService& s, QWidget* parent): service(s), ui(new Ui::AdminUi)
{
	this->ui->setupUi(this);
	this->connectSignals();
	populateList();
}

AdminUiHandler::~AdminUiHandler()
{
	delete this->ui;
}

void AdminUiHandler::connectSignals()
{
	connect(ui->DogList, &QListWidget::currentItemChanged, this, &AdminUiHandler::listItemChanged);
	connect(ui->ViewModeComboBox, &QComboBox::currentIndexChanged, this, &AdminUiHandler::populateList);
	connect(ui->AddPushButton, &QPushButton::clicked, this, &AdminUiHandler::addButtonHandler);
	connect(ui->RemovePushButton, &QPushButton::clicked, this, &AdminUiHandler::removeButtonHandler);
	connect(ui->UpdatePushButton, &QPushButton::clicked, this, &AdminUiHandler::updateButtonHandler);
	connect(ui->UndoPushButton, &QPushButton::clicked, this, &AdminUiHandler::undoHandler);
	connect(ui->RedoPushButton, &QPushButton::clicked, this, &AdminUiHandler::redoHandler);
}

void AdminUiHandler::addButtonHandler()
{
	std::string breed, name, link;
	int age;
	breed = ui->BreedLineEdit->text().toStdString();
	name = ui->NameLineEdit->text().toStdString();
	link = ui->PhotoLineEdit->text().toStdString();
	try {
		age = std::stoi(ui->AgeLineEdit->text().toStdString());
	}
	catch (...)
	{
		handleErrorMessage();
	}
	try {
		Dog dog(service.getBiggestId() + 1, breed, name, link, age);
		DogValidator::validateDog(dog);
		this->service.addDog(dog);
	}
	catch (ValidatorException& e) {
		handleException(e);
		return;
	}
	catch(RepositoryException& e){
		handleException(e);
		return;
	}
	catch (ServiceException& e) {
		handleException(e);
		return;
	}
	populateList();
}

void AdminUiHandler::updateButtonHandler()
{
	std::string breed, name, link;
	int age;
	breed = ui->BreedLineEdit->text().toStdString();
	name = ui->NameLineEdit->text().toStdString();
	link = ui->PhotoLineEdit->text().toStdString();
	try {
		age = std::stoi(ui->AgeLineEdit->text().toStdString());
	}
	catch (...)
	{
		handleErrorMessage();
	}
	try {
		Dog dog(service.getDogAt(getSelectedItem()).getId(), breed, name, link, age);
		DogValidator::validateDog(dog);
		this->service.updateDog(dog);
	}
	catch (std::exception& e) {
		handleException(e);
	}
	populateList();
}

void AdminUiHandler::removeButtonHandler()
{
	try {
		Dog dog = service.getDogAt(this->getSelectedItem());
		service.removeDog(dog);
	}
	catch (std::exception& e) {
		handleException(e);
	}
	populateList();
}

void AdminUiHandler::populateList()
{

	if (ui->DogList->count() > 0)
		ui->DogList->clear();

	std::vector<Dog> dogs = this->service.getAllDogs();
	for (auto d : dogs) {
		QString itemInList = QString::fromStdString(d.getBreed() + " - " + d.getName() + " - " + std::to_string(d.getAge()) + " - " + d.getLink());
		if (ui->ViewModeComboBox->currentIndex() == 1) {
			itemInList = QString::fromStdString(d.getBreed() + " - " + d.getName());
		}
		QFont f{ "Verdana", 15 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		ui->DogList->addItem(item);
	}

	if (dogs.size() > 0)
		ui->DogList->setCurrentRow(0);
}

void AdminUiHandler::undoHandler()
{
	try {
		service.undo();
	}
	catch (std::exception& e) {
		handleException(e);
	}
	populateList();
}

void AdminUiHandler::redoHandler()
{
	try {
		service.redo();
	}
	catch (std::exception& e) {
		handleException(e);
	}
	populateList();
}

void AdminUiHandler::listItemChanged()
{
	if (getSelectedItem() < 0)
		return;
	Dog dog = service.getDogAt(getSelectedItem());
	ui->BreedLineEdit->setText(QString::fromStdString(dog.getBreed()));
	ui->NameLineEdit->setText(QString::fromStdString(dog.getName()));
	ui->PhotoLineEdit->setText(QString::fromStdString(dog.getLink()));
	ui->AgeLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
}

void AdminUiHandler::handleException(const std::exception& e) const
{
	QMessageBox::critical(nullptr, "Error", e.what());
}

void AdminUiHandler::handleErrorMessage() const
{
	QMessageBox::critical(nullptr, "Error", "Unkown Error occured.");
}

int AdminUiHandler::getSelectedItem()
{
	return ui->DogList->currentRow();
}
