#ifndef QT_TASK_4_APP_H
#define QT_TASK_4_APP_H

#include <QWidget>
#include <QListWidget>
#include "Dictionary.h"


QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QWidget {
Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

    ~App() override;

private slots:
    void openFromFile();
    void saveToFile();
    void sortByFrequency();
    void fillTextField(QListWidget *qListWidget);

private:
    Ui::App *ui;
    Dictionary* dictionary;
    QListWidget* listWidget;
};


#endif //QT_TASK_4_APP_H
