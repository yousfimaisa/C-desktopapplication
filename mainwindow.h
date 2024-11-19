/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QMainWindow>
#include <QSqlQueryModel>
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
    //void on_chercher_clicked(const QString &chercherLineEdit);
private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
*/



// zedtha ena









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
  void on_exporter_clicked();
    void on_reinitialiser_clicked();
    void on_helpButton_clicked();
    void on_stat_clicked();
    void on_trier_clicked();
    void on_deconnexion_clicked();
    void on_supprimer_clicked();
    void on_CALENDRIER_clicked();
    void on_option_currentIndexChanged(int index);
    void keyPressEvent(QKeyEvent *event) override;
    void on_facture_2_clicked();
    void rechercher();
    void testInsertionSansTableView();
    void afficherHistorique();
    void onTimerTick();
     void on_PARAMETRE_clicked();
private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTimer *timer;  // Chronomètre pour effectuer une action répétée
    void startChronometer();  // Méthode pour démarrer le chronomètre

};

#endif // MAINWINDOW_H


