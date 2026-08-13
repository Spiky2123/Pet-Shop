#include "ClientUiHandler.h"

ClientUiHandler::ClientUiHandler(UserService& s, QWidget* parent): service(s), ui(new Ui::ClientUi)
{
	this->ui->setupUi(this);
	filteredDogs = service.getAll();
	populateList();
	connectSignals();
}

ClientUiHandler::~ClientUiHandler()
{
	delete ui;
}

void ClientUiHandler::connectSignals()
{
	connect(ui->AdoptButton, &QPushButton::clicked, this, &ClientUiHandler::adoptButtonHandler);
	connect(ui->BackButton, &QPushButton::clicked, this, &ClientUiHandler::previousButtonHandler);
	connect(ui->NextButton, &QPushButton::clicked, this, &ClientUiHandler::nextButtonHandler);
	connect(ui->FilterPushButton, &QPushButton::clicked, this, &ClientUiHandler::filterButtonHandler);
	connect(ui->ExportButton, &QPushButton::clicked, this, &ClientUiHandler::exportButtonHandler);
}

void ClientUiHandler::adoptButtonHandler()
{
	try {
		service.adoptDog(filteredDogs[index]);
		filteredDogs.erase(filteredDogs.begin() + index);
		updateDogData();
		populateList();
		service.saveAdoptions();
	}
	catch (ServiceException& e)
	{
		handleException(e);
	}
	catch (RepositoryException& e)
	{
		handleException(e);
	}
	catch (...) {
		handleErrorMessage();
	}
}

void ClientUiHandler::nextButtonHandler()
{
	index++;
	if (index >= filteredDogs.size())
		index = 0;
	updateDogData();
}

void ClientUiHandler::previousButtonHandler()
{
	index--;
	if (index < 0)
		index = filteredDogs.size() - 1;
	updateDogData();
}

void ClientUiHandler::exportButtonHandler()
{
	service.displayAdoptions();
}

void ClientUiHandler::populateList()
{
	if (ui->AdoptionList->count() > 0)
		ui->AdoptionList->clear();

	std::vector<Dog> dogs = this->service.getAdoptions();
	for (auto d : dogs) {
		QString itemInList = QString::fromStdString(d.getBreed() + " - " + d.getName() + " - " + std::to_string(d.getAge()) + " - " + d.getLink());
		QFont f{ "Verdana", 15 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		ui->AdoptionList->addItem(item);
	}
	ui->AdoptionList->setCurrentRow(-1);
	updateDogData();
}

void ClientUiHandler::filterButtonHandler()
{
	filteredDogs = service.getDogsByBreed(ui->FilterLineEdit->text().toStdString());
	updateDogData();
}

void ClientUiHandler::updateDogData()
{
	if (filteredDogs.size() == 0)
	{
		ui->NameLabel->setText("-");
		ui->BreedLabel->setText("-");
		ui->AgeLabel->setText("-");
		return;
	}
	if (index >= filteredDogs.size())
		index = 0;
	ui->NameLabel->setText("<a href=\"" + QString::fromStdString(filteredDogs[index].getLink()) + "\">" + QString::fromStdString(filteredDogs[index].getName()) + "</a>");
	ui->BreedLabel->setText(QString::fromStdString(filteredDogs[index].getBreed()));
	ui->AgeLabel->setText(QString::fromStdString(std::to_string(filteredDogs[index].getAge())));
}

void ClientUiHandler::handleException(const std::exception& e) const
{
	QMessageBox::critical(nullptr, "Error", e.what());
}

void ClientUiHandler::handleErrorMessage() const
{
	QMessageBox::critical(nullptr, "Error", "Unkown Error occured.");
}
