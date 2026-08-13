#include "ui/AdminUiHandler.h"
#include "repository/SqlRepository.h"
#include "repository/TextFileRepository.h"
#include "repository/FileRepo.h"
#include "service/UserService.h"
#include "ui/ClientUiHandler.h"
#include <QtWidgets/QApplication>
#include <iostream>

std::string selectRunMode() {
    std::string mode;
    while (true) {
        std::cout << "Enter app mode (user / admin): ";
        std::cin >> mode;
        if (mode == "user" || mode == "admin")
            return mode;
        std::cout << "Invalid mode.\n";
    }
}
std::string getRepoFormat() {
    std::string format;
    while (true) {
        std::cout << "Select adoption file format (CSV / HTML): ";
        std::cin >> format;
        for (char& i : format) i = toupper(i);
        if (format == "CSV" || format == "HTML")
            return format;
        std::cout << "Invalid format.\n";
    }
}
std::string getDatabaseType() {
    std::string databaseType;
    while (true) {
        std::cout << "Select database type (text / sqlite): ";
        std::cin >> databaseType;
        for (char& i : databaseType) i = toupper((i));
        if (databaseType == "TEXT" || databaseType == "SQLITE")
            return databaseType;
        std::cout << "Invalid type.\n";
    }
}

FileRepository* createClientRepo(std::string mode) {
    FileRepository* repo = nullptr;
    if (mode == "user") {
        const std::string format = getRepoFormat();
        if (format == "CSV") {
            repo = new CSVRepository("adoptions.csv");
        }
        else
            repo = new HTMLRepository("adoptions.html");
    }
    return repo;
}
BaseRepository* createRepository() {
    const std::string databaseType = getDatabaseType();
    const std::string basePath = "dogs";
    BaseRepository* repository = nullptr;
    if (databaseType == "TEXT")
        repository = new TextFileRepository(basePath + ".txt");
    else
        repository = new SqlRepository(basePath + ".db");
    return repository;
}

int main(int argc, char *argv[])
{
    std::cout << "A";
    const std::string mode = selectRunMode();

    BaseRepository* repository = createRepository();
    FileRepository* adoptionRepo = createClientRepo(mode);

    AdminService adminService = AdminService(*repository);
    UserService userService = UserService(*repository, *adoptionRepo);


    QApplication app(argc, argv);
    if (mode == "admin") {
        AdminUiHandler window(adminService);
        window.show();
        return app.exec();
    }
    else if (mode == "user") {
        ClientUiHandler window(userService);
        window.show();
        return app.exec();
    }
    delete repository;
    delete adoptionRepo;
}
