#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QTableWidget"
#include <QScrollBar>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setTableWidget(0,4);
    //显示当前日期时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(time_update()));
    timer->start(1000); //1s执行一次,定时器
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_SearchBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->UserPage);    //切换到用户界面
}


void MainWindow::on_ExitBtn_released()
{
    close();                              //退出系统
}


void MainWindow::on_backBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menuPage);    //切换到主页面
}

void MainWindow::on_ExitBtn_2_released()
{
    close();                              //退出系统
}

void MainWindow::setTableWidget(int, int)  //QTableWidget的初始化
{
        ui->tableWidget->resizeRowsToContents();//调整行内容大小
        ui->tableWidget->setColumnCount(4);//设置列数
        //ui->tableWidget->setRowCount(100);//设置行数
        //设置标题头的文字
        QStringList header;
        header<< tr("物品名称") << tr("数目") << tr("位置") << "添加日期";
        ui->tableWidget->setHorizontalHeaderLabels(header);
        //设置标题头的字体样式
        QFont font = ui->tableWidget->horizontalHeader()->font();
        font.setBold(true);
        ui->tableWidget->horizontalHeader()->setFont(font);

        ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
        ui->tableWidget->verticalHeader()->setDefaultSectionSize(10); //设置行距
        ui->tableWidget->setShowGrid(true); //设置显示格子线
        ui->tableWidget->verticalHeader()->setVisible(true); //设置行号列,false为不显示
        ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //可多选（Ctrl、Shift、 Ctrl+A都可以）
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
        ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers); //设置可编辑
        ui->tableWidget->horizontalHeader()->resizeSection(0,100);//设置表头第一列的宽度为100
        ui->tableWidget->horizontalHeader()->setFixedHeight(30); //设置表头的高度
        ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:white;}"); //设置表头背景色

        //设置水平、垂直滚动条样式,添加头文件 #include <QScrollBar>
        ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                                                              "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                              "QScrollBar::handle:hover{background:gray;}"
                                                              "QScrollBar::sub-line{background:transparent;}"
                                                              "QScrollBar::add-line{background:transparent;}");
        ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                                                            "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                            "QScrollBar::handle:hover{background:gray;}"
                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            "QScrollBar::add-line{background:transparent;}");

        ui->tableWidget->clearContents();//清除表格数据区的所有内容，但是不清除表头
}

void MainWindow::on_SearchBtn_2_released()
{
    //搜索物品信息
    QString arg1 = ui->lineEdit->text();
    if(arg1 == "")
    {
        return;
    }

    QList<QTableWidgetItem *>   items;
    QTableWidgetItem            *item;

    items  = ui->tableWidget->findItems(arg1, Qt::MatchExactly);//在表格中查找数据项

    //找到了这个数据项
    if(items.length() > 0)
    {
        item = items[0];//获取到数据项
        int r = item->row();//获取所在行
        ui->tableWidget->verticalScrollBar()->setSliderPosition(r);//滚动条定位到数据所在位置
        ui->tableWidget->setCurrentItem(item);//将这个数据所在行设置为表格的当前行
    }
}

void MainWindow::on_delBtn_released()
{
    int row;
    row = ui->tableWidget->currentRow();
    if(row < 0)
    {
        QMessageBox::warning(this,QStringLiteral("告警"),QStringLiteral("请先选中要删除的项！"));
        return ;
    }
    ui->tableWidget->removeRow(row);
}

void MainWindow::on_addBtn_clicked()
{
    QString Name,Num,Location,Day;
    Name=ui->lineEdit->text().trimmed();
    Num=ui->lineEdit->text().trimmed();
    Location=ui->lineEdit->text().trimmed();
    Day=ui->lineEdit->text().trimmed();
    int RowCont;
    RowCont = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(RowCont);//增加一行

    //插入元素
    ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(Name));
    ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(Num));
    ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(Location));
    ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(Day));
}

void MainWindow::time_update() //显示系统实时时间功能
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->label->setText(str);
}

