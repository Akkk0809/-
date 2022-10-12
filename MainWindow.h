#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include "QTableWidget"
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SearchBtn_released();

    void on_ExitBtn_released();

    void on_backBtn_released();

    void on_ExitBtn_2_released();

    void on_SearchBtn_2_released();

    void on_delBtn_released();

    void on_addBtn_clicked();

    void time_update(void);

private:
    Ui::MainWindow *ui;
    void setTableWidget(int, int);
};
#endif // MAINWINDOW_H
