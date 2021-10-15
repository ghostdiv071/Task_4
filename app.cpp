// You may need to build the project (run Qt uic code generator) to get "ui_App.h" resolved

#include "app.h"
#include "ui_App.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <iostream>

App::App(QWidget *parent) :
        QWidget(parent), ui(new Ui::App) {
    ui->setupUi(this);
    dictionary = new Dictionary();
    Logger::log(DebugLevel::INFO, "Application is running");

    auto *mainAppLayout = new QHBoxLayout(this); // main horizontal layout
    auto *controlBlock = new QVBoxLayout(); //vertical layout with buttons
    auto *textBlock = new QVBoxLayout();  //vert layout with output text block

    listWidget = new QListWidget(this);//output text block
    fillTextField(listWidget, dictionary->sortByAlphabet());
    textBlock->addWidget(listWidget);

    auto *addWords = new QPushButton("Add words from another file", this);
    auto *recoverDict = new QPushButton("Recover dictionary from file", this);
    auto *saveDictToFile = new QPushButton("Save to file", this);
    auto *alphabetSort = new QPushButton("Sort by alphabet", this);
    auto *freqSort = new QPushButton("Sort by frequency", this);
    auto *exit = new QPushButton("Exit", this);
    controlBlock->addWidget(addWords);
    controlBlock->addWidget(recoverDict);
    controlBlock->addWidget(saveDictToFile);
    controlBlock->addWidget(alphabetSort);
    controlBlock->addWidget(freqSort);
    controlBlock->addWidget(exit);

    mainAppLayout->addLayout(textBlock);
    mainAppLayout->addSpacing(15);
    mainAppLayout->addLayout(controlBlock);

    setLayout(mainAppLayout);

    connect(addWords, &QPushButton::clicked, this, &App::addWordsFromFile);
    connect(recoverDict, &QPushButton::clicked, this, &App::recoverFromFile);
    connect(saveDictToFile, &QPushButton::clicked, this, &App::saveToFile);
    connect(alphabetSort, &QPushButton::clicked, this, &App::sortByAlphabet);
    connect(freqSort, &QPushButton::clicked, this, &App::sortByFrequency);
    connect(exit, &QPushButton::clicked, this, &QApplication::exit);
}

App::~App() {
    delete ui;
}

void App::addWordsFromFile() {
    readFile(QFileDialog::getOpenFileName(this, "", R"(C:\Users\1\Downloads\test for task 4)"));
}

void App::recoverFromFile() {
    dictionary->getDictionary().clear();
    readFile(QString::fromStdString(saveFile));
}

void App::saveToFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "", R"(C:\Users\1\Downloads\test for task 4)");
    saveFile = fileName.toStdString();
    Logger::log(DebugLevel::INFO, "User saves dictionary to file " + fileName.toStdString());
    QFile file(fileName);
    QFileInfo fileInfo(fileName);
    if (file.open(QIODevice::WriteOnly) && checkFileExtension(fileInfo)) {
        QTextStream out(&file);
        for (const auto& pair : dictionary->getDictionary()) {
            for (int i = 0; i < pair.second; ++i) {
                out << QString::fromStdString(pair.first + '\n');
            }
        }
    } else {
        Logger::log(DebugLevel::WARN, "Could not open file");
        qWarning("Could not open file");
    }
    file.close();
}


void App::sortByAlphabet() {
    fillTextField(listWidget, dictionary->sortByAlphabet());
    Logger::log(DebugLevel::INFO, "Dictionary sorted by alphabet");
}

void App::sortByFrequency() {
    fillTextField(listWidget, dictionary->sortByFrequency());
    Logger::log(DebugLevel::INFO, "Dictionary sorted by words frequency");
}

void App::readFile(const QString& fileName) {
    Logger::log(DebugLevel::INFO, "User opens file " + fileName.toStdString());
    QFile file(fileName);
    QFileInfo fileInfo(fileName);
    if (file.open(QIODevice::ReadOnly) && checkFileExtension(fileInfo)) {
        dictionary->fillFromFile(fileName.toStdString());
        fillTextField(listWidget, dictionary->sortByAlphabet());
    } else {
        Logger::log(DebugLevel::WARN, "Could not open file");
        qWarning("Could not open file");
    }
    file.close();
}

void App::fillTextField(QListWidget *qListWidget, const std::vector<std::pair<std::string, int>>& pairs) {
    while (qListWidget->count() > 0) {
        listWidget->takeItem(0);
    }
    for (const auto &pair: pairs) {
        std::string item = pair.first + " " + std::to_string(pair.second);
        QString qString = QString::fromStdString(item);
        qListWidget->addItem(qString);
    }
}

bool App::checkFileExtension(const QFileInfo& fileInfo) {
    return fileInfo.suffix() == "txt";
}
