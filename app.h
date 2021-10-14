#ifndef QT_TASK_4_APP_H
#define QT_TASK_4_APP_H

#include <QWidget>
#include <QListWidget>
#include <QFileInfo>
#include "Dictionary.h"


QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QWidget {
Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

    ~App() override;

    void readFile(const QString& fileName);

    void fillTextField(QListWidget *qListWidget, const std::vector<std::pair<std::string, int>>& pairs);

    bool checkFileExtension(const QFileInfo& fileInfo);

    bool checkFileName(const QString& fileName);

private slots:
    void addWordsFromFile();
    void recoverFromFile();
    void saveToFile();
    void sortByAlphabet();
    void sortByFrequency();


private:
    Ui::App *ui;
    Dictionary* dictionary;
    std::string saveFile;
    QListWidget* listWidget;
};


#endif //QT_TASK_4_APP_H
