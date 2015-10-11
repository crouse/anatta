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
    mod->setHeaderData(10, Qt::Horizontal, "现居市");
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
    mod->setHeaderData(38, Qt::Horizontal, "家庭三宝弟子");
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
    int rowNum = ui->tableViewFemale->verticalHeader()->logicalIndexAt(pos);
    int colNum = ui->tableViewFemale->horizontalHeader()->logicalIndexAt(pos);

    int db_id = modelFemale->index(rowNum, 0).data().toInt();
    QString receipt = modelFemale->index(rowNum, 1).data().toString();
    QString sth = modelFemale->index(rowNum, colNum).data().toString();
    qDebug() << db_id << receipt;
    qDebug() << sth;

    QMenu *popMenu = new QMenu(this);
    popMenu->addAction(ui->actionExportPersonalInfo);
    popMenu->addAction(ui->actionPrintPersonnelCredentials);
    popMenu->exec(QCursor::pos());

    delete popMenu;
}

void MainWindow::on_actionExportPersonalInfo_triggered()
{
    // export excel format personnel info
}

void MainWindow::on_actionPrintPersonnelCredentials_triggered()
{
    // export pdf format personnel info
}

void MainWindow::savePdfs(QString fileName, QSqlTableModel *mod, QString filter, QString pixmapPath)
{
#ifndef ONE_PAGE_NUM
#define ONE_PAGE_NUM 8
#endif
    if (!mod) {
        QMessageBox::information(this, "warn", "数据库未连接或者没有导出的数据");
        return;
    }

    int pageNum = 0;
    int leftMargin;
    int leftWordMargin;
    int pixMapMagin;
    int topMargin = 400;
    int blockHeight = 1600;

    int headerPos = 0;
    int footer = 0;

    QString dt = QDate::currentDate().toString(Qt::ISODate);

    QFile pdf_file(fileName);
    pdf_file.open(QIODevice::WriteOnly);
    QPdfWriter *pdf_writer = new QPdfWriter(&pdf_file);
    QPainter *pdf_painter = new QPainter(pdf_writer);
    QFont font;
    font.setFamily("微软雅黑");
    //font.setPixelSize(150);
    font.setPointSize(8);

    QFont mfont;
    //mfont.setPixelSize(120);
    mfont.setPointSize(6);
    mfont.setFamily("苹果方");
    QPen vpen;
    vpen.setStyle(Qt::DashLine);
    pdf_painter->setPen(vpen);
    pdf_painter->setFont(mfont);
    pdf_painter->setRenderHint(QPainter::NonCosmeticDefaultPen, true);
    pdf_writer->setPageSize(QPagedPaintDevice::A4);

    qDebug() << filter;
    //mod->setFilter(filter);
    mod->select();

    for (int i = 0; i < mod->rowCount(); i += 8) {
        /* handle page margin */
        if (pageNum % 2 == 0) {
            pixMapMagin = 800;
            leftMargin = 1800;
            leftWordMargin = leftMargin + 1100;
            footer = 8500;
        } else {
            pixMapMagin = 400;
            leftMargin = 1400;
            leftWordMargin = leftMargin + 1100;
            footer = 1500;
        }

        headerPos = 7500;

        QSqlRecord record[ONE_PAGE_NUM];

        pdf_painter->drawText(QRect(footer, 13400, 600, 300), QString("%2").arg(pageNum + 1));
        pdf_painter->drawLine(QPoint(pixMapMagin, 300), QPoint(9000, 300));
        for(int m = 0; m < 8; ++m) {
            record[m] = mod->record(i + m);
            /* make one page pdf */
            /* set image */

            /* If receipt is empty which means there is no page any more, so end this func */
            QString receipt = record[m].value("receipt").toString();
            if (receipt.isEmpty()) {
                qDebug() << "Receipt is empty" << "Page Num is " << pageNum;
                pdf_painter->end();
                delete pdf_painter;
                delete pdf_writer;
                pdf_file.close();
                return;
            }

            QString pixmapAbsPath = QString("%1/%2.jpg").arg(pixmapPath).arg(receipt);
            qDebug() << pixmapAbsPath;
            //QPixmap pixmap(pixmapAbsPath);
            QPixmap pixmap("/Users/quqinglei/Desktop/myself.jpg"); // [tbd just test]

            int height = m * blockHeight;

            pdf_painter->drawPixmap(pixMapMagin, topMargin + height, 885, 1239, pixmap);

            pdf_painter->setFont(font);
            QString name = QString("姓名：%1").arg(record[m].value("name").toString());
            QString gender = QString("性别：%1").arg(record[m].value("gender").toString());
            QString fname = QString("法名：%1").arg(record[m].value("fname").toString());
            QString race = QString("民族：%1").arg(record[m].value("race").toString());
            QString birthday = QString("生日：%1").arg(record[m].value("birthday").toString());
            QString degree = QString("学历：%1").arg(record[m].value("degree").toString());
            QString addr = QString("住址：%1 %2 %3")
                    .arg(record[m].value("province").toString())
                    .arg(record[m].value("city").toString())
                    .arg(record[m].value("district").toString());
            QString job = QString("工作：%1").arg(record[m].value("job").toString());
            QString level_time = QString("学佛时间/程度：%1/%2")
                    .arg(record[m].value("year2start_learning_buddhism").toString())
                    .arg(record[m].value("deep_understanding_of_dharma").toString());

            QString code = QString("编号：%1").arg(record[m].value("code").toString());
            QString phone = QString("手机：%1").arg(record[m].value("phone_num").toString());
            QString pid = QString("身份证：%1").arg(record[m].value("personnel_id").toString());

            pdf_painter->drawText(QRect(leftMargin, topMargin + height, 10000, 300), name);
            pdf_painter->drawText(QRect(leftMargin + 2500, topMargin + height, 20000, 300), fname);
            pdf_painter->drawText(QRect(leftMargin + 5000, topMargin + height, 20000, 300), gender);

            pdf_painter->drawText(QRect(leftMargin, topMargin + height + 300, 20000, 300), race);
            pdf_painter->drawText(QRect(leftMargin + 2500, topMargin + height + 300, 20000, 300), birthday);
            pdf_painter->drawText(QRect(leftMargin + 5000, topMargin + height + 300, 20000, 300), degree);

            pdf_painter->drawText(QRect(leftMargin, topMargin + height + 600, 20000, 300), addr);
            pdf_painter->drawText(QRect(leftMargin + 2500, topMargin + height + 600, 20000, 300), job);
            pdf_painter->drawText(QRect(leftMargin + 5000, topMargin + height + 600, 20000, 300), level_time);

            pdf_painter->drawText(QRect(leftMargin, topMargin + height + 900, 20000, 300), code);
            pdf_painter->drawText(QRect(leftMargin + 2500, topMargin + height + 900, 20000, 300), phone);
            pdf_painter->drawText(QRect(leftMargin + 5000, topMargin + height + 900, 20000, 300), pid);

            pdf_painter->drawLine(QPoint(pixMapMagin, 1900 + height), QPoint(9000, 1900 + height));


        }

        pdf_writer->newPage();
        ++pageNum;
        qDebug() << "Page num: " << pageNum;
    }

    pdf_painter->end();
    delete pdf_writer;
    delete pdf_painter;
    pdf_file.close();
}

void MainWindow::savePdfFilesAll(QString fileName)
{
    qDebug() << fileName;
    savePdfs(fileName, model, "", "/Users/quqinglei/Destkop/");
    savePdfs(fileName, modelFemale, "", "/Users/quqinglei/Destkop/");
}

void MainWindow::on_actionExportPdf_triggered()
{
    // export all pdf
    // [tbd] test if database is connected, if not QmessageBox info, return
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, "打开保存文件路径", "", "pdf (*.pdf)");
    if (fileName.isNull()) return;
    savePdfFilesAll(fileName);
}
