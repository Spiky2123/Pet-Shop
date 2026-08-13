#pragma once
#include <qwidget.h>
#include <qmessagebox.h>
#include "ui_UiAdmin.h"
#include "../service/AdminService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AdminUi; }
QT_END_NAMESPACE

class AdminUiHandler : public QWidget
{
    Q_OBJECT
private:
    Ui::AdminUi* ui;
    AdminService& service;

public:
    AdminUiHandler(AdminService& s, QWidget* parent = nullptr);
    ~AdminUiHandler();
private:
    void connectSignals();
    void addButtonHandler();
    void updateButtonHandler();
    void removeButtonHandler();
    void populateList();
    void undoHandler();
    void redoHandler();
    void listItemChanged();
    void handleException(const std::exception& e) const;
    void handleErrorMessage() const;
    int getSelectedItem();
};
