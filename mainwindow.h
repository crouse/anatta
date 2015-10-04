#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>
#include <QtXlsx>
#include <QtSql>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#define DB_NAME "citta"
#define DB_PASS "123456"
#define DB_USER "citta"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool databaseTest();
    bool connectDatabase();
    void setModel(QSqlTableModel *mod, QString tableName, QTableView *view);
    QLineEdit *lineEditSearch;
    QLineEdit *lineEditConfig;
    QLineEdit *lineEditEditor;


private slots:
    void on_actionSetting_triggered();

    void on_actionDb_triggered();
    void on_actionRefresh_triggered();

private:
    Ui::MainWindow *ui;
    QString serverIp;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *modelFemale;

};

#endif // MAINWINDOW_H
