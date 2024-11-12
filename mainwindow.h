#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "prestation.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_exportation_clicked();
    void on_reinitialiser_clicked();
    void on_helpButton_clicked();
    void on_stat_clicked();
   // void on_trier_clicked();
     void on_deconnexion_clicked();
   // void on_CALENDRIER_clicked();  // Slot pour ouvrir le calendrier



private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
      QSortFilterProxyModel *proxyModel;
};

#endif // MAINWINDOW_H
