// You may need to build the project (run Qt uic code generator) to get "ui_App.h" resolved

#include "app.h"
#include "ui_App.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>

App::App(QWidget *parent) :
        QWidget(parent), ui(new Ui::App) {
    ui->setupUi(this);
    dictionary = new Dictionary();

    auto *mainAppLayout = new QHBoxLayout(this); // main horizontal layout
    auto *controlBlock = new QVBoxLayout(); //vertical layout with buttons
    auto *textBlock = new QVBoxLayout();  //vert layout with output text block

    listWidget = new QListWidget(this);//output text block
    fillTextField(listWidget);
    textBlock->addWidget(listWidget);

    auto *openFile = new QPushButton("Open from file", this);
    auto *saveFile = new QPushButton("Save to file", this);
    auto *alphabetSort = new QPushButton("Sort by alphabet", this);
    auto *freqSort = new QPushButton("Sort by frequency", this);
    auto *exit = new QPushButton("Exit", this);
    controlBlock->addWidget(openFile);
    controlBlock->addWidget(saveFile);
    //controlBlock->addWidget(alphabetSort);
    controlBlock->addWidget(freqSort);
    controlBlock->addWidget(exit);

    mainAppLayout->addLayout(textBlock);
    mainAppLayout->addSpacing(15);
    mainAppLayout->addLayout(controlBlock);

    setLayout(mainAppLayout);

    connect(openFile, &QPushButton::clicked, this, &App::openFromFile);
    connect(saveFile, &QPushButton::clicked, this, &App::saveToFile);
    connect(freqSort, &QPushButton::clicked, this, &App::sortByFrequency);
    connect(exit, &QPushButton::clicked, this, &QApplication::exit);
}

App::~App() {
    delete ui;
}

void App::openFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "", R"(C:\Users\1\Downloads\test for task 4)");
    QFile file(fileName);
    QFileInfo fileInfo(fileName);
    if (file.open(QIODevice::ReadOnly) && fileInfo.suffix() == "txt") {
        //std::cout << fileName.toStdString() << std::endl;
        dictionary->fillFromFile(fileName.toStdString());
        fillTextField(listWidget);
    } else {
        qWarning("Could not open file");
    }
}

void App::saveToFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "", R"(C:\Users\1\Downloads\test for task 4)");
    QFile file(fileName);
    QFileInfo fileInfo(fileName);
    if (file.open(QIODevice::WriteOnly) && fileInfo.suffix() == "txt") {
        QTextStream out(&file);

    } else {
        qWarning("Could not open file");
    }
    file.close();
}

void App::sortByFrequency() {

}

void App::fillTextField(QListWidget *qListWidget) {
    while (qListWidget->count() > 0) {
        listWidget->takeItem(0);
    }
    for (const auto &pair: dictionary->getDictionary()) {
        std::string item = pair.first + " " + std::to_string(pair.second);
        //std::cout << item << std::endl;
        QString qString = QString::fromStdString(item);
        qListWidget->addItem(qString);
    }
}

