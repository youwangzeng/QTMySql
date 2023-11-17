#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "form_main.h"

#include <QMainWindow>
#include <Qsqldatabase>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <QSqlError>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *);
public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
