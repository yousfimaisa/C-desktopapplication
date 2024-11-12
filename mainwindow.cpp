#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prestation.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPainter>
#include <QPrinter>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a QStandardItemModel to hold the data
    model = new QStandardItemModel(0, 6, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("NOM"));
    model->setHorizontalHeaderItem(2, new QStandardItem("CATEGORIE"));
    model->setHorizontalHeaderItem(3, new QStandardItem("DESCRIPTION"));
    model->setHorizontalHeaderItem(4, new QStandardItem("DUREE"));
    model->setHorizontalHeaderItem(5, new QStandardItem("PRIX"));

    // Set the model to the table view
    ui->tableView->setModel(model);
    connect(ui->deconnexion, &QPushButton::clicked, this, &MainWindow::on_deconnexion_clicked);
    //connect(ui->CALENDRIER, &QPushButton::clicked, this, &MainWindow::on_CALENDRIER_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    // Récupérer les données depuis l'interface utilisateur
    QString text = ui->ID->toPlainText();  // Utilisez text() pour QLineEdit
    int ID = text.toInt();  // Convertir en entier

    QString NOM = ui->NOM->toPlainText();  // Récupérer NOM depuis QLineEdit
    QString DESCRIPTION = ui->DESCRIPTION->toPlainText();  // DESCRIPTION est un QTextEdit

    // Récupérer la catégorie sélectionnée
    QString CATEGORIE;
    if (ui->SOIN->isChecked()) {
        CATEGORIE = "SOIN";  // Catégorie 1
    } else if (ui->VACCIN->isChecked()) {
        CATEGORIE = "VACCIN";  // Catégorie 2
    } else if (ui->CONSULTATION->isChecked()) {
        CATEGORIE = "CONSULTATION";  // Catégorie 3
    } else {
        CATEGORIE = "Aucune catégorie sélectionnée";
    }

    // Récupérer le prix depuis le QComboBox
    float PRIX = ui->PRIX->currentText().toFloat();

    QString DUREE = ui->DUREE->toPlainText();  // Récupérer DUREE depuis QLineEdit

    // Ajouter une nouvelle Prestation dans le modèle
    int row = model->rowCount();  // Obtenir la prochaine ligne disponible dans le modèle
    model->insertRow(row);  // Ajouter une nouvelle ligne

    // Créer des QStandardItem avec couleur de texte spécifique
    QStandardItem *idItem = new QStandardItem(QString::number(ID));
    QStandardItem *nomItem = new QStandardItem(NOM);
    QStandardItem *categorieItem = new QStandardItem(CATEGORIE);
    QStandardItem *descriptionItem = new QStandardItem(DESCRIPTION);
    QStandardItem *dureeItem = new QStandardItem(DUREE);
    QStandardItem *prixItem = new QStandardItem(QString::number(PRIX));

    // Changer la couleur du texte (par exemple, rouge)
    QColor textColor = QColor(255, 0, 0);  // Rouge

    idItem->setForeground(QBrush(textColor));
    nomItem->setForeground(QBrush(textColor));
    categorieItem->setForeground(QBrush(textColor));
    descriptionItem->setForeground(QBrush(textColor));
    dureeItem->setForeground(QBrush(textColor));
    prixItem->setForeground(QBrush(textColor));

    // Insérer les données dans les cellules du modèle
    model->setItem(row, 0, idItem);          // Colonne ID
    model->setItem(row, 1, nomItem);         // Colonne NOM
    model->setItem(row, 2, categorieItem);   // Colonne CATEGORIE
    model->setItem(row, 3, descriptionItem); // Colonne DESCRIPTION
    model->setItem(row, 4, dureeItem);       // Colonne DUREE
    model->setItem(row, 5, prixItem);        // Colonne PRIX

    // Rafraîchir la vue
    ui->tableView->resizeColumnsToContents();  // Ajuster la largeur des colonnes pour s'adapter aux données
    ui->tableView->scrollToBottom();  // Faire défiler la table jusqu'en bas pour voir la nouvelle ligne

    // Optionnel : Afficher un message de confirmation
    QMessageBox::information(this, "Ajout réussi", "La prestation a été ajoutée à la table.");
}


/*                                exportation pdf                          */



void MainWindow::on_exportation_clicked()
{
    // Créer un objet QPrinter pour générer un fichier PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    // Ouvrir une boîte de dialogue pour sélectionner le fichier de sortie PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter vers PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;  // Si l'utilisateur annule, on ne fait rien
    }

    printer.setOutputFileName(fileName);  // Définir le nom du fichier de sortie

    // Créer un QPainter pour dessiner sur le PDF
    QPainter painter(&printer);
    painter.setFont(QFont("Arial", 12));  // Choisir une police pour le texte

    // Dessiner le titre
    painter.drawText(200, 50, "Exportation des Prestations");

    // Dessiner les entêtes des colonnes
    int yOffset = 100;
    painter.drawText(50, yOffset, "ID");
    painter.drawText(150, yOffset, "NOM");
    painter.drawText(250, yOffset, "CATEGORIE");
    painter.drawText(350, yOffset, "DESCRIPTION");
    painter.drawText(500, yOffset, "DUREE");
    painter.drawText(600, yOffset, "PRIX");

    // Dessiner les données de la table
    yOffset += 30;
    for (int row = 0; row < model->rowCount(); ++row) {
        painter.drawText(50, yOffset, model->data(model->index(row, 0)).toString());
        painter.drawText(150, yOffset, model->data(model->index(row, 1)).toString());
        painter.drawText(250, yOffset, model->data(model->index(row, 2)).toString());
        painter.drawText(350, yOffset, model->data(model->index(row, 3)).toString());
        painter.drawText(500, yOffset, model->data(model->index(row, 4)).toString());
        painter.drawText(600, yOffset, QString::number(model->data(model->index(row, 5)).toFloat()));

        yOffset += 20;
    }

    painter.end();  // Terminer l'écriture dans le fichier PDF

    // Afficher un message de confirmation
    QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées avec succès dans un fichier PDF.");
}

void MainWindow::on_reinitialiser_clicked()
{
    ui->ID->clear();
    ui->NOM->clear();
    ui->DESCRIPTION->clear();
    ui->DUREE->clear();
    ui->PRIX->setCurrentIndex(0);  // Réinitialiser le QComboBox
    ui->SOIN->setChecked(false);
    ui->VACCIN->setChecked(false);
    ui->CONSULTATION->setChecked(false);
}


void MainWindow::on_helpButton_clicked()
{
    // Créer une boîte de message avec le texte d'aide
    QMessageBox helpBox(this);
    helpBox.setWindowTitle("Aide - Gestion des Prestations");
    helpBox.setIcon(QMessageBox::Information);

    // Ajouter le texte explicatif dans le message
    QString helpText = "Bienvenue dans le système de gestion des prestations.\n\n"
                       "Voici quelques fonctionnalités disponibles :\n"
                       "- Ajouter une prestation : Saisissez les détails dans les champs et cliquez sur Ajouter.\n"
                       "- Exporter en PDF : Exporte les données sous forme de fichier PDF.\n"
                       "- Réinitialiser : Réinitialise tous les champs du formulaire.\n"
                       "Utilisez la barre de recherche pour filtrer les prestations par nom.\n";

    helpBox.setText(helpText);

    // Afficher la boîte de message
    helpBox.exec();
}void MainWindow::on_deconnexion_clicked()
{
    // Afficher une boîte de message pour confirmer la déconnexion
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Déconnexion", "Voulez-vous vraiment vous déconnecter ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Réinitialiser les champs de l'interface (si nécessaire)
        ui->ID->clear();
        ui->NOM->clear();
        ui->DESCRIPTION->clear();
        ui->DUREE->clear();
        ui->PRIX->setCurrentIndex(0);  // Réinitialiser le QComboBox
        ui->SOIN->setChecked(false);
        ui->VACCIN->setChecked(false);
        ui->CONSULTATION->setChecked(false);

        // Optionnel : Si vous avez des connexions de base de données ouvertes, fermez-les ici
        // Par exemple :
        // db.close();

        // Fermer la fenêtre principale après déconnexion
        this->close();  // Cette ligne ferme la fenêtre principale de l'application

        // Si vous avez une fenêtre de connexion, vous pouvez la montrer ici
        // loginWindow->show(); // Afficher la fenêtre de connexion si nécessaire
    }
}



void MainWindow::on_stat_clicked()
{
    // Créer une fenêtre de statistiques
    QWidget *statWindow = new QWidget();
    statWindow->setWindowTitle("Statistiques des Prestations");
    QVBoxLayout *layout = new QVBoxLayout();

    // Graphique des prestations par catégorie
    QPieSeries *series = new QPieSeries();
    series->append("Soin", 60);
    series->append("Consultation", 25);
    series->append("Vaccination", 15);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Prestations");

    QChartView *chartView = new QChartView(chart);
    layout->addWidget(chartView);

    // Afficher la fenêtre des statistiques
    statWindow->setLayout(layout);
    statWindow->resize(600, 400);
    statWindow->show();
}
/*void MainWindow::on_trier_clicked()
{
    // Vérifiez si le proxyModel et le modèle source sont correctement définis
    if (proxyModel->sourceModel()) {
        // Trier par la colonne 1 (Nom), tri croissant
        proxyModel->sort(1, Qt::AscendingOrder);  // 1 pour la colonne "NOM" (index 1)
        QMessageBox::information(this, "Tri effectué", "Les données ont été triées par nom de prestation.");
    } else {
        QMessageBox::warning(this, "Erreur", "Le modèle source n'est pas défini.");
    }
}
*/





