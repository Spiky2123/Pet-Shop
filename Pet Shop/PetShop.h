#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PetShop.h"

class PetShop : public QMainWindow
{
    Q_OBJECT

public:
    PetShop(QWidget *parent = nullptr);
    ~PetShop();

private:
    Ui::PetShopClass ui;
};

