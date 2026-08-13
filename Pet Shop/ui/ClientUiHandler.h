#pragma once
#include <qwidget.h>
#include <qmessagebox.h>
#include "ui_UiClient.h"
#include "../service/UserService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientUi; }
QT_END_NAMESPACE

class ClientUiHandler : public QWidget {
    Q_OBJECT
private:
    Ui::ClientUi* ui;
    UserService& service;
    int index = 0;
    std::vector<Dog> filteredDogs;

public:
    ClientUiHandler(UserService& s, QWidget* parent = nullptr);
    ~ClientUiHandler();
private:
    void connectSignals();
    void adoptButtonHandler();
    void nextButtonHandler();
    void previousButtonHandler();
    void exportButtonHandler();
    void populateList();
    void filterButtonHandler();
    void updateDogData();
    void handleException(const std::exception& e) const;
    void handleErrorMessage() const;
};