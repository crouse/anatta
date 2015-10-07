#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serverIp = "127.0.0.1";

    {
        lineEditSearch = new QLineEdit;
        lineEditSearch->setFixedSize(200, 20);
        lineEditSearch->setStyleSheet("border-radius: 5px;");
        lineEditSearch->setPlaceholderText(" 查询 <ENTER>");
        //connect(lineEditSearch, SIGNAL(returnPressed()), this, SLOT(searchInfo()));
        ui->mainToolBar->addWidget(lineEditSearch);
    }


    /* config lineEdit */
    {
        lineEditConfig = new QLineEdit;
        lineEditConfig->setFixedSize(100, 20);
        lineEditConfig->setStyleSheet("border-radius: 5px;");
        lineEditConfig->setPlaceholderText("服务器地址");
        lineEditConfig->setText(serverIp);
        lineEditConfig->setReadOnly(true);
        //connect(lineEditConfig, SIGNAL(returnPressed()), this, SLOT(setServerAddr()));
        ui->mainToolBar->addWidget(lineEditConfig);
    }


    /* editor lineEdit */
    {
        lineEditEditor = new QLineEdit;
        lineEditEditor->setFixedSize(100, 20);
        lineEditEditor->setStyleSheet("border-radius: 5px; background: yellow");
        lineEditEditor->setPlaceholderText(" 编辑人必填");
        //connect(lineEditEditor, SIGNAL(returnPressed()), this, SLOT(afterLineEditorEditorPressed()));
        ui->mainToolBar->addWidget(lineEditEditor);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSetting_triggered()
{
}

bool MainWindow::databaseTest()
{
    bool ret;
    QTcpSocket tsock;
    tsock.connectToHost(serverIp, 3306);
    ret = tsock.waitForConnected(1000);
    if (ret) tsock.close();
    return ret;
}

bool MainWindow::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(serverIp);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASS);

    if(!db.open()) {
        QMessageBox::critical(this, "数据库错误", db.lastError().text());
        return false;
    }

    return true;
}

void MainWindow::setModel(QSqlTableModel *mod, QString tableName, QTableView *view)
{
    mod = new QSqlTableModel(this);

    if (tableName == "zen_male") {
        model = mod;
    } else {
        modelFemale = mod;
    }

    mod->setTable(tableName);
    mod->setEditStrategy(QSqlTableModel::OnFieldChange);
    mod->setSort(0, Qt::AscendingOrder);
    mod->setHeaderData(0, Qt::Horizontal, "序号");
    mod->setHeaderData(1, Qt::Horizontal, "收据号");
    mod->setHeaderData(2, Qt::Horizontal, "姓名");
    mod->setHeaderData(3, Qt::Horizontal, "手机号");
    mod->setHeaderData(4, Qt::Horizontal, "性别");
    mod->setHeaderData(5, Qt::Horizontal, "法名");
    mod->setHeaderData(6, Qt::Horizontal, "民族");
    mod->setHeaderData(7, Qt::Horizontal, "生日");
    mod->setHeaderData(8, Qt::Horizontal, "学历");
    mod->setHeaderData(9, Qt::Horizontal, "现居省");
    mod->setHeaderData(10, Qt::Horizontal, "先居市");
    mod->setHeaderData(11, Qt::Horizontal, "现居区县");
    mod->setHeaderData(12, Qt::Horizontal, "详细街道地址");
    mod->setHeaderData(13, Qt::Horizontal, "皈依证号");
    mod->setHeaderData(14, Qt::Horizontal, "工作");
    mod->setHeaderData(15, Qt::Horizontal, "爱好");
    mod->setHeaderData(16, Qt::Horizontal, "身份证号码");
    mod->setHeaderData(17, Qt::Horizontal, "健康状况");
    mod->setHeaderData(18, Qt::Horizontal, "电话号码");
    mod->setHeaderData(19, Qt::Horizontal, "编辑时间");
    mod->setHeaderData(20, Qt::Horizontal, "工作单位");
    mod->setHeaderData(21, Qt::Horizontal, "邮编号码");
    mod->setHeaderData(22, Qt::Horizontal, "毕业时间");
    mod->setHeaderData(23, Qt::Horizontal, "毕业学校");
    mod->setHeaderData(24, Qt::Horizontal, "第一份工作入职时间");
    mod->setHeaderData(25, Qt::Horizontal, "第一份工作入职单位");
    mod->setHeaderData(26, Qt::Horizontal, "第二份工作入职时间");
    mod->setHeaderData(27, Qt::Horizontal, "第二份工作入职单位");
    mod->setHeaderData(28, Qt::Horizontal, "退休时间");
    mod->setHeaderData(29, Qt::Horizontal, "退休工作单位");
    mod->setHeaderData(30, Qt::Horizontal, "学佛起始时间");
    mod->setHeaderData(31, Qt::Horizontal, "学佛时间（年）");
    mod->setHeaderData(32, Qt::Horizontal, "是否深刻理解佛法层次");
    mod->setHeaderData(33, Qt::Horizontal, "学佛因缘");
    mod->setHeaderData(34, Qt::Horizontal, "读经数量");
    mod->setHeaderData(35, Qt::Horizontal, "认为易学的经典");
    mod->setHeaderData(36, Qt::Horizontal, "认为难读懂的经典");
    mod->setHeaderData(37, Qt::Horizontal, "格言");
    mod->setHeaderData(38, Qt::Horizontal, "家庭三宝地址");
    mod->setHeaderData(39, Qt::Horizontal, "编辑人姓名");
    mod->setHeaderData(40, Qt::Horizontal, "修改人姓名");
    mod->setHeaderData(41, Qt::Horizontal, "学佛小组种类");
    mod->setHeaderData(42, Qt::Horizontal, "学佛小组地址");
    mod->setHeaderData(43, Qt::Horizontal, "是否提供学佛场地");
    mod->setHeaderData(44, Qt::Horizontal, "其他信息");
    mod->setHeaderData(45, Qt::Horizontal, "标记");
    mod->setHeaderData(46, Qt::Horizontal, "IP地址");
    mod->setHeaderData(47, Qt::Horizontal, "数据来源");
    mod->setHeaderData(48, Qt::Horizontal, "记录写入时间");
    mod->setHeaderData(49, Qt::Horizontal, "打印状态"); // default 0, success 1
    mod->setHeaderData(50, Qt::Horizontal, "数据准备情况");
    mod->select();

    //ui->tableView->setModel(model);
    view->setModel(mod);
}

void MainWindow::on_actionDb_triggered()
{
    bool conStatus = databaseTest();
    if (conStatus == false) {
        QMessageBox::critical(this, "", "请设置正确的数据库地址以及端口.");
        return;
    }
    bool stat = connectDatabase();
    if (!stat) {
        qDebug() << "Not connected.";
        return;
    }
    qDebug() << "set Model";

    setModel(model, "zen_male", ui->tableView);
    setModel(modelFemale, "zen_female", ui->tableViewFemale);
}

void MainWindow::on_actionRefresh_triggered()
{
    model->select();
    ui->tableView->reset();

    modelFemale->select();
    ui->tableViewFemale->reset();
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos) // male
{
    int rowNum = ui->tableView->verticalHeader()->logicalIndexAt(pos);
    int colNum = ui->tableView->horizontalHeader()->logicalIndexAt(pos);

    int db_id = model->index(rowNum, 0).data().toInt();
    QString receipt = model->index(rowNum, 1).data().toString();
    QString sth = model->index(rowNum, colNum).data().toString();
    qDebug() << db_id << receipt;
    qDebug() << sth;

    QMenu *popMenu = new QMenu(this);
    popMenu->addAction(ui->actionExportPersonalInfo);
    popMenu->addAction(ui->actionPrintPersonnelCredentials);
    popMenu->exec(QCursor::pos());

    delete popMenu;
}

void MainWindow::on_tableViewFemale_customContextMenuRequested(const QPoint &pos) // female
{
    qDebug() << pos;
}

void MainWindow::on_actionExportPersonalInfo_triggered()
{
    // export excel format personnel info
}

void MainWindow::on_actionPrintPersonnelCredentials_triggered()
{
    // export pdf format personnel info
}
