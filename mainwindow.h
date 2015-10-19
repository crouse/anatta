#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>
#include <QtSql>
#include <QTcpSocket>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QTableView>
#include <QSqlTableModel>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPageLayout>
#include <QMarginsF>
#include <QFile>
#include <QFont>
#include <QPixmap>
#include <QPen>
#include <QDate>
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
    void savePdfs(QString fileName, QSqlTableModel *mod, QString filter, QString pixmapPath);
    void createCard(QString fileName, QSqlTableModel *mod, QString filter, QString pixmapPath);
    void createCert(QString fileName, QSqlTableModel *mod, QString filter, QString pixmapPath);

    QLineEdit *lineEditSearch;
    QLineEdit *lineEditConfig;
    QLineEdit *lineEditEditor;


private slots:
    void on_actionSetting_triggered();

    void on_actionDb_triggered();
    void on_actionRefresh_triggered();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_tableViewFemale_customContextMenuRequested(const QPoint &pos);

    void on_actionExportPersonalInfo_triggered();

    void on_actionPrintPersonnelCredentials_triggered();

    void on_actionExportPdf_triggered();

    void on_toolButtonImagePath_clicked();

    void on_toolButtonBackPath_clicked();

    void on_actionCard_triggered();

private:
    Ui::MainWindow *ui;
    QString serverIp;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *modelFemale;

};

#endif // MAINWINDOW_H
