/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prestation.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPainter>
#include <QPrinter>
#include <QFileDialog>
#include <QSortFilterProxyModel>

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



*/




























// hethi zetha ena  ::





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
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QModelIndexList>
#include <QMessageBox>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include<QTimer>










MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this); // Créer une instance de QTimer
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick); // Connecter le signal timeout à un slot


    // zedtha teb3a clavier ww fazet
    this->setFocus();  // Assurez-vous que la fenêtre principale a le focus


    // Create a QStandardItemModel to hold the data
    model = new QStandardItemModel(0, 6, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("NOM"));
    model->setHorizontalHeaderItem(2, new QStandardItem("CATEGORIE"));
    model->setHorizontalHeaderItem(3, new QStandardItem("DESCRIPTION"));
    model->setHorizontalHeaderItem(4, new QStandardItem("DUREE"));
    model->setHorizontalHeaderItem(5, new QStandardItem("PRIX"));
    //
    model->setHorizontalHeaderItem(6, new QStandardItem("DATES"));
    model->setHorizontalHeaderItem(7, new QStandardItem("ID_EMPLOYE"));



    // Set the model to the table view
    ui->tableView->setModel(model);
    connect(ui->deconnexion, &QPushButton::clicked, this, &MainWindow::on_deconnexion_clicked);
    //connect(ui->CALENDRIER, &QPushButton::clicked, this, &MainWindow::on_CALENDRIER_clicked);
    connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::rechercher);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    connect(ui->facture_2, &QPushButton::clicked, this, &MainWindow::on_facture_2_clicked);
    connect(ui->boutonAfficherHistorique, &QPushButton::clicked, this, &MainWindow::afficherHistorique);
    connect(ui->CALENDRIER, &QPushButton::clicked, this, &MainWindow::on_CALENDRIER_clicked);
    connect(ui->exporter, &QPushButton::clicked, this, &MainWindow::on_exporter_clicked);
      connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);



}

MainWindow::~MainWindow()
{
    delete ui;
}


#include <QRegularExpression>
#include <QMessageBox>
#include <QBrush>
#include <QColor>

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QDebug>


#include <QCryptographicHash>

// Fonction de chiffrement simple
QByteArray crypterTexte(const QByteArray &data, const QString &motDePasse) {
    QByteArray cle = QCryptographicHash::hash(motDePasse.toUtf8(), QCryptographicHash::Sha256);
    QByteArray resultat = data;

    for (int i = 0; i < resultat.size(); ++i) {
        resultat[i] = resultat[i] ^ cle[i % cle.size()]; // XOR entre les données et la clé
    }
    return resultat;
}



void sauvegarderDansFichierCrypte(QTableView *tableView, const QString &cheminFichier, const QString &motDePasse) {
    QFile fichier(cheminFichier);

    // Vérifier et créer le dossier
    QDir dossier = QFileInfo(cheminFichier).absoluteDir();
    if (!dossier.exists()) {
        dossier.mkpath(".");
    }

    if (!fichier.open(QIODevice::WriteOnly)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier pour écrire.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'enregistrer les données dans le fichier.");
        return;
    }

    QTextStream flux;
    QByteArray contenuNonCrypte;

    QAbstractItemModel *model = tableView->model();

    // Construire le contenu non chiffré
    for (int col = 0; col < model->columnCount(); ++col) {
        contenuNonCrypte.append(model->headerData(col, Qt::Horizontal).toString().toUtf8() + ",");
    }
    contenuNonCrypte.append("\n");

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            contenuNonCrypte.append(model->data(model->index(row, col)).toString().toUtf8() + ",");
        }
        contenuNonCrypte.append("\n");
    }

    // Crypter le contenu
    QByteArray contenuCrypte = crypterTexte(contenuNonCrypte, motDePasse);

    // Écrire le contenu chiffré dans le fichier
    fichier.write(contenuCrypte);
    fichier.close();

    qDebug() << "Fichier historique chiffré enregistré dans :" << cheminFichier;
    QMessageBox::information(nullptr, "Succès", "L'historique a été sauvegardé avec chiffrement.");
}




QString lireFichierCrypte(const QString &cheminFichier, const QString &motDePasse) {
    QFile fichier(cheminFichier);

    if (!fichier.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier pour lire.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de lire le fichier.");
        return QString();
    }

    QByteArray contenuCrypte = fichier.readAll();
    fichier.close();

    // Décrypter le contenu
    QByteArray contenuDecrypte = crypterTexte(contenuCrypte, motDePasse);

    return QString(contenuDecrypte);
}

void MainWindow::on_ajouter_clicked()
{
    // Récupérer les données depuis l'interface utilisateur
    QString textID = ui->ID->toPlainText().trimmed();  // Utilisez text() pour QLineEdit et supprimez les espaces
    QString NOM = ui->NOM->toPlainText().trimmed();      // Récupérer NOM depuis QLineEdit et supprimez les espaces
    QString DESCRIPTION = ui->DESCRIPTION->toPlainText().trimmed();  // Récupérer DESCRIPTION depuis QTextEdit
    QString DUREE = ui->DUREE->toPlainText().trimmed();  // Récupérer DUREE depuis QLineEdit
    float PRIX = ui->PRIX->currentText().toFloat();      // Récupérer PRIX depuis le QComboBox
    //
    QString dateStr = ui->DATES->dateTime().toString("yyyy-MM-dd hh:mm:ss"); // Formatage de la date en texte
    QString textID_EMPLOYE = ui->ID_EMPLOYE->toPlainText().trimmed();


    // Récupérer la catégorie sélectionnée
    QString CATEGORIE;
    if (ui->SOIN->isChecked()) {
        CATEGORIE = "SOIN";
    } else if (ui->VACCIN->isChecked()) {
        CATEGORIE = "VACCIN";
    } else if (ui->CONSULTATION->isChecked()) {
        CATEGORIE = "CONSULTATION";
    }

    // Vérifier que toutes les données sont bien renseignées
    if (textID.isEmpty() || NOM.isEmpty() || DESCRIPTION.isEmpty() || CATEGORIE.isEmpty() || DUREE.isEmpty() || PRIX == 0.0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification que l'ID est numérique et de taille 2
    bool isNumeric;
    int ID = textID.toInt(&isNumeric);
    if (!isNumeric || textID.length() != 2) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre de 3 chiffres.");
        return;
    }
    // Vérification que l'ID est numérique et de taille 2
    bool isNumeric1;
    int ID_EMPLOYE = textID_EMPLOYE.toInt(&isNumeric1);
    if (!isNumeric || textID_EMPLOYE.length() != 2) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre de 3 chiffres.");
        return;
    }

    // Vérification que NOM contient uniquement des lettres alphabétiques
    QRegularExpression regex("^[a-zA-Z]+$");
    QRegularExpressionMatch match = regex.match(NOM);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le NOM doit contenir uniquement des lettres.");
        return;
    }

    // Vérification que le prix est un nombre positif
    if (PRIX <= 0) {
        QMessageBox::warning(this, "Erreur", "Le PRIX doit être un nombre positif.");
        return;
    }

    // Vérification que la durée est un nombre valide
    bool dureeOk;
    int duree = DUREE.toInt(&dureeOk);
    if (!dureeOk || duree <= 0) {
        QMessageBox::warning(this, "Erreur", "La DURÉE doit être un nombre positif.");
        return;
    }

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
    //
    // QStandardItem *dateItem = new QStandardItem(DATES.toString("yyyy-MM-dd hh:mm:ss"));
    QStandardItem *dateItem = new QStandardItem(dateStr);
    QStandardItem *id_employeItem = new QStandardItem(QString::number(ID_EMPLOYE));


    // Changer la couleur du texte (par exemple, rouge)
    QColor textColor = QColor(255, 0, 0);  // Rouge
    idItem->setForeground(QBrush(textColor));
    nomItem->setForeground(QBrush(textColor));
    categorieItem->setForeground(QBrush(textColor));
    descriptionItem->setForeground(QBrush(textColor));
    dureeItem->setForeground(QBrush(textColor));
    prixItem->setForeground(QBrush(textColor));
    id_employeItem->setForeground(QBrush(textColor));


    // Insérer les données dans les cellules du modèle
    model->setItem(row, 0, idItem);          // Colonne ID
    model->setItem(row, 1, nomItem);         // Colonne NOM
    model->setItem(row, 2, categorieItem);   // Colonne CATEGORIE
    model->setItem(row, 3, descriptionItem); // Colonne DESCRIPTION
    model->setItem(row, 4, dureeItem);       // Colonne DUREE
    model->setItem(row, 5, prixItem);        // Colonne PRIX
    //
    model->setItem(row, 6, dateItem);
    model->setItem(row, 7, id_employeItem);
    //   teb3a trier   :::::::::::::::::::::::::::::::


    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);  // 'model' est votre modèle source
    ui->tableView->setModel(proxyModel);

    // Rafraîchir la vue
    ui->tableView->resizeColumnsToContents();  // Ajuster la largeur des colonnes pour s'adapter aux données
    ui->tableView->scrollToBottom();  // Faire défiler la table jusqu'en bas pour voir la nouvelle ligne

    // Afficher un message de confirmation
    QMessageBox::information(this, "Ajout réussi", "La prestation a été ajoutée à la table.");
    // Préparer la requête SQL
    // Préparer la requête SQL
    QSqlQuery query;
    query.prepare("INSERT INTO PRESTATION (NOM, ID, DESCRIPTION, DUREE, PRIX, CATEGORIE, DATES) "
                  "VALUES (:NOM, :ID, :DESCRIPTION, :DUREE, :PRIX, :CATEGORIE, :DATES)");

    query.bindValue(":NOM", NOM);
    query.bindValue(":ID", ID);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":DUREE", duree);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":DATES", dateStr);
    query.bindValue(":ID_EMPLOYE", ID_EMPLOYE);
    // Exécuter la requête et vérifier l'exécution
    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête :" << query.lastError().text();
        qDebug() << "Requête exécutée :" << query.executedQuery();
        return;
    }

    // Rafraîchir la table ou afficher un message de confirmation
    QMessageBox::information(this, "Succès", "Les données ont été ajoutées avec succès dans la base de données.");
    // sauvegarderDansFichierTexte(ui->tableView);


/*
    QSqlQuery query;

    // Étape 1 : Vérifier si l'ID existe déjà dans la table
    query.prepare("SELECT COUNT(*) FROM PRESTATION WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'ID :" << query.lastError().text();
        return;
    }

    query.next(); // Accéder au premier résultat
    int count = query.value(0).toInt();

    if (count > 0) {
        // L'ID existe déjà, afficher un message ou générer un nouvel ID
        QMessageBox::warning(nullptr, "Erreur", "Cet ID existe déjà. Veuillez en utiliser un autre.");
        return;
    }

    // Étape 2 : Insérer les données si l'ID est unique
    query.prepare("INSERT INTO PRESTATION (NOM, ID, DESCRIPTION, DUREE, PRIX, CATEGORIE, DATES, ID_EMPLOYE) "
                  "VALUES (:NOM, :ID, :DESCRIPTION, :DUREE, :PRIX, :CATEGORIE, :DATES, :ID_EMPLOYE)");

    query.bindValue(":NOM", NOM);
    query.bindValue(":ID", ID);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":DUREE", duree);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":DATES", dateStr);
    query.bindValue(":ID_EMPLOYE", ID_EMPLOYE);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête :" << query.lastError().text();
        qDebug() << "Requête exécutée :" << query.executedQuery();
        return;
    }

    // Si l'insertion réussit
    qDebug() << "Insertion réussie dans la table PRESTATION.";
    QMessageBox::information(nullptr, "Succès", "Les données ont été ajoutées avec succès.");


*/










    QString cheminFichier = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/hist/historique.txt";
    QString motDePasse = "MSROBOT"; // Vous pouvez demander ce mot de passe à l'utilisateur
    sauvegarderDansFichierCrypte(ui->tableView, cheminFichier, motDePasse);


}

void MainWindow::afficherHistorique() {
    // Chemin du fichier historique
    QString cheminFichier = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/hist/historique.txt";

    // Demander le mot de passe à l'utilisateur
    bool ok;
    QString motDePasse = QInputDialog::getText(this, "Mot de passe", "Entrez le mot de passe :", QLineEdit::Password, "", &ok);

    if (!ok || motDePasse.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Mot de passe requis pour accéder à l'historique.");
        return;
    }

    // Lire le fichier avec le mot de passe
    QString contenu = lireFichierCrypte(cheminFichier, motDePasse);

    if (contenu.isEmpty()) {
        // Si le contenu est vide, cela signifie que le mot de passe est incorrect ou que le fichier est inaccessible
        // Afficher les données décryptées en texte brut
        QString contenuDecrypté = lireFichierCrypte(cheminFichier, "incorrect");
        if (contenuDecrypté.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Le mot de passe est incorrect et le fichier est inaccessible.");
        } else {
            // Affichage du contenu décrypté
            QMessageBox::information(this, "Historique Décrypté", contenuDecrypté);
        }
    } else {
        // Si le mot de passe est correct, afficher le contenu crypté lisiblement
        QMessageBox::information(this, "Historique", contenu);
    }
}


void MainWindow::on_option_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        // Ajouter
        on_ajouter_clicked();
        break;
    case 1:

        on_reinitialiser_clicked();
        break;
    case 2:
        void on_modifier_clicked();

        break;
    default:
        break;
    }
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Vérifier si la touche pressée est "A"
    if (event->key() == Qt::Key_A) {
        // Appeler la fonction pour ajouter des données
        on_ajouter_clicked();

        // Afficher un message pour indiquer que les données ont été ajoutées
        QMessageBox::information(this, "Ajout réussi", "Les données ont été ajoutées à la table.");
    }
    // Vérifier si la touche pressée est "R" pour Réinitialiser (par exemple)
    else if (event->key() == Qt::Key_R) {
        // Appeler la fonction pour réinitialiser (si nécessaire)
        on_reinitialiser_clicked();
    }

    // Vous pouvez ajouter d'autres touches pour d'autres actions
    // Si aucune touche spécifique n'est pressée, on appelle la méthode parente
    QWidget::keyPressEvent(event);
}




/*void MainWindow::on_exportation_clicked(){





}*/



void MainWindow::on_supprimer_clicked()
{
    // Obtenir l'index de la ligne sélectionnée dans la vue
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();

    // Vérifier si une ligne est bien sélectionnée
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner une ligne à supprimer.");
        return;
    }

    // Récupérer l'index de la première ligne sélectionnée
    QModelIndex index = selection.first();
    int row = index.row();

    // Demander confirmation avant de supprimer
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation de suppression",
                                                              "Êtes-vous sûr de vouloir supprimer cette ligne ?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Supprimer la ligne du modèle
        model->removeRow(row);

        // Rafraîchir la vue
        ui->tableView->reset();

        // Afficher un message de confirmation
        QMessageBox::information(this, "Suppression réussie", "La ligne a été supprimée avec succès.");
    }
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
    ui->ID_EMPLOYE->clear();

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
        ui->ID_EMPLOYE->clear();

        // Optionnel : Si vous avez des connexions de base de données ouvertes, fermez-les ici
        // Par exemple :
        // db.close();

        // Fermer la fenêtre principale après déconnexion
        this->close();  // Cette ligne ferme la fenêtre principale de l'application

        // Si vous avez une fenêtre de connexion, vous pouvez la montrer ici
        // loginWindow->show(); // Afficher la fenêtre de connexion si nécessaire
    }
}





void MainWindow::on_trier_clicked()
{
    // Vérifiez si le proxyModel et le modèle source sont correctement définis
    if (proxyModel->sourceModel()) {
        // Trier par la colonne 1 (Nom), tri croissant
        proxyModel->sort(1, Qt::AscendingOrder);  // 1 pour la colonne "NOM" (index 1)

        // Rafraîchir la vue après le tri
        ui->tableView->reset();

        // Afficher un message pour informer l'utilisateur que le tri a été effectué
        QMessageBox::information(this, "Tri effectué", "Les données ont été triées par nom de prestation.");
    } else {
        // Si le modèle source n'est pas défini, afficher un message d'erreur
        QMessageBox::warning(this, "Erreur", "Le modèle source n'est pas défini.");
    }
}

void MainWindow::on_stat_clicked()
{
    // Créer une fenêtre de statistiques
    QWidget *statWindow = new QWidget();
    statWindow->setWindowTitle("Statistiques des Prestations");
    QVBoxLayout *layout = new QVBoxLayout();

    // Créer une série pour le diagramme en camembert (Pie chart)
    QPieSeries *series = new QPieSeries();

    // Variables pour compter les prestations par catégorie
    int countSOIN = 0;
    int countCONSULTATION = 0;
    int countVACCIN = 0;

    // Parcourir toutes les lignes du modèle pour compter les catégories
    int rowCount = model->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QStandardItem *categorieItem = model->item(i, 2);  // Colonne 2 : CATEGORIE
        QString categorie = categorieItem->text();

        if (categorie == "SOIN") {
            ++countSOIN;
        } else if (categorie == "CONSULTATION") {
            ++countCONSULTATION;
        } else if (categorie == "VACCIN") {
            ++countVACCIN;
        }
    }

    // Ajouter les données au graphique si des prestations existent
    if (countSOIN > 0) {
        series->append("Soin", countSOIN);
    }
    if (countCONSULTATION > 0) {
        series->append("Consultation", countCONSULTATION);
    }
    if (countVACCIN > 0) {
        series->append("Vaccination", countVACCIN);
    }

    // Si aucune prestation n'a été ajoutée pour ces catégories
    if (series->count() == 0) {
        QMessageBox::warning(this, "Aucune donnée", "Aucune prestation n'a été ajoutée pour ces catégories.");
        statWindow->close();
        return;
    }

    // Créer un graphique (QChart) et ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Prestations");

    // Ajouter un graphique à la vue
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Pour une meilleure qualité d'affichage
    layout->addWidget(chartView);

    // Afficher la fenêtre des statistiques
    statWindow->setLayout(layout);
    statWindow->resize(600, 400);
    statWindow->show();
}void MainWindow::rechercher()
{
    // Récupérer le texte du QLineEdit (champ de recherche)
    QString termeRecherche = ui->rechercherr->text();

    // Vérifier si le terme de recherche est vide
    if (termeRecherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche invalide", "Veuillez entrer un terme de recherche.");
        return;
    }

    QAbstractItemModel *model = ui->tableView->model();
    bool found = false;

    // Parcourir toutes les lignes et les colonnes du modèle pour chercher la valeur
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QString cellData = model->data(model->index(row, column)).toString();
            if (cellData.contains(termeRecherche, Qt::CaseInsensitive)) {
                // Créer un index pour la cellule correspondante
                QModelIndex index = model->index(row, column);

                // Sélectionner uniquement cette cellule
                ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select | QItemSelectionModel::Columns);
                found = true;
                break;  // Sortir de la boucle des colonnes si trouvé
            }
        }
        if (found) break;  // Sortir de la boucle des lignes si trouvé
    }

    // Si aucune correspondance n'est trouvée
    if (!found) {
        QMessageBox::information(this, "Aucun résultat", "Aucun résultat trouvé pour : " + termeRecherche);
    }
}



void MainWindow::on_facture_2_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une prestation pour générer la facture.");
        return;
    }

    // Récupérer les informations de la première ligne sélectionnée
    int row = selectedIndexes.first().row();
    QString id = model->data(model->index(row, 0)).toString();
    QString nom = model->data(model->index(row, 1)).toString();
    QString categorie = model->data(model->index(row, 2)).toString();
    QString description = model->data(model->index(row, 3)).toString();
    QString duree = model->data(model->index(row, 4)).toString();
    QString prix = model->data(model->index(row, 5)).toString();
    QString date = model->data(model->index(row, 6)).toString();
    QString id_employe = model->data(model->index(row, 7)).toString();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer la facture", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    printer.setOutputFileName(fileName);

    QPainter painter(&printer);
    QFont font("Arial", 12);  // Taille de police augmentée pour plus de lisibilité
    painter.setFont(font);

    const int margin = 80;  // Marge de page
    int yOffset = margin;   // Position verticale de départ

    // QRect pageRect = printer.pageRect();
    // int pageHeight = pageRect.height();

    // Titre de la facture
    // lezem nbadelha   *********************************************************************
    // /painter.drawText(margin, yOffset, "Facture de Prestation");
    // yOffset += 30;

    // Numéro de la facture
    // static int factureNumber = 1;
    // painter.drawText(margin, yOffset, QString("Numéro de facture : %1").arg(factureNumber));
    //  yOffset += 80;
    // factureNumber++;

    // Dessiner le tableau avec les en-têtes
    const int columnWidth = 550;  // Largeur de chaque colonne
    const int rowHeight = 300;     // Hauteur de chaque ligne
    const int xOffset = margin;   // Décalage horizontal pour la première colonne

    // Dessiner les en-têtes de colonne
    painter.drawText(xOffset, yOffset, "ID");
    painter.drawText(xOffset + columnWidth, yOffset, "Nom");
    painter.drawText(xOffset + 2 * columnWidth, yOffset, "Catégorie");
    painter.drawText(xOffset + 4 * columnWidth, yOffset, "Description");
    painter.drawText(xOffset + 6 * columnWidth, yOffset, "Durée");
    painter.drawText(xOffset + 7 * columnWidth, yOffset, "Prix");
    painter.drawText(xOffset + 13 * columnWidth, yOffset, "Date");
    painter.drawText(xOffset + 16 * columnWidth, yOffset, "id_employe");
    yOffset += rowHeight;

    // Dessiner une ligne horizontale sous les en-têtes
    // thabet star 5at
    painter.drawLine(xOffset, yOffset, xOffset + 7 * columnWidth, yOffset);
    yOffset += 10;

    // Dessiner les données de la facture dans le tableau
    painter.drawText(xOffset, yOffset, id);
    painter.drawText(xOffset + columnWidth, yOffset, nom);
    painter.drawText(xOffset + 2 * columnWidth, yOffset, categorie);
    painter.drawText(xOffset + 4 * columnWidth, yOffset, description);
    painter.drawText(xOffset + 6 * columnWidth, yOffset, duree);
    painter.drawText(xOffset + 7 * columnWidth, yOffset, prix + " Dn");
    painter.drawText(xOffset + 13 * columnWidth, yOffset, date);
    painter.drawText(xOffset + 16 * columnWidth, yOffset, id_employe);

    yOffset += rowHeight;

    // Dessiner une ligne horizontale sous la dernière ligne de données
    painter.drawLine(xOffset, yOffset, xOffset + 7 * columnWidth, yOffset);

    // Vérifier si le contenu dépasse la page et passer à une nouvelle page si nécessaire
    // if (yOffset > pageHeight - margin) {
    //     painter.end();
    //     printer.newPage();
    //     painter.begin(&printer);
    //     yOffset = margin;  // Réinitialiser la position verticale
    //  }

    painter.end();
    QMessageBox::information(this, "Facture générée", "La facture a été générée avec succès.");
}






// temchi l ajouter
/*
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
*/














#include <QDate>
#include <QMessageBox>
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

void MainWindow::on_CALENDRIER_clicked()
{
    // Récupérer la date actuelle
    QDateTime currentDate = QDateTime::currentDateTime();
    QString todayStr = currentDate.toString("yyyy-MM-dd hh:mm:ss"); // Format de la date actuelle

    // Variable pour la période à vérifier (ex: 7 jours à partir d'aujourd'hui)
    int warningPeriod = 7; // Période en jours

    // Parcourir toutes les lignes de la table pour comparer les dates
    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Récupérer la date stockée dans la colonne 6 (ou la colonne de date)
        QStandardItem* dateItem = model->item(row, 6);  // Colonne des dates
        QString storedDateStr = dateItem->text();

        // Convertir la date stockée en QDateTime
        QDateTime storedDate = QDateTime::fromString(storedDateStr, "yyyy-MM-dd hh:mm:ss");

        // Calculer la différence entre la date actuelle et la date stockée
        int daysDifference = currentDate.daysTo(storedDate);

        // Vérifier si la date est proche du jour actuel (par exemple, dans les 7 jours)
        if (daysDifference >= 0 && daysDifference <= warningPeriod) {
            // Si la date est proche, afficher une alerte
            QString alertMessage = QString("Attention! Une date ( %1 ) est proche de la date actuelle.").arg(storedDateStr);
            QMessageBox::information(this, "Alerte de date", alertMessage);
        }
    }
}









#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
void MainWindow::on_exporter_clicked()
{
    // Afficher une boîte de dialogue pour choisir le fichier de destination
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en CSV", "", "Fichiers CSV (*.csv);;Tous les fichiers (*)");

    // Vérifier si l'utilisateur a annulé
    if (filePath.isEmpty())
        return;

    // Ouvrir le fichier en écriture
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour l'écriture.");
        return;
    }

    // Préparer un flux de texte pour écrire dans le fichier
    QTextStream stream(&file);

    // Ajouter les en-têtes manuellement dans l'ordre voulu
    stream << "ID      NOM   CATEGORIE    DESCRIPTION     DUREE   PRIX   DATES       ID_EMPLOYE\n";

    // Obtenir le nombre de lignes et de colonnes du modèle
    int rowCount = model->rowCount();

    // Exporter les données du modèle
    for (int row = 0; row < rowCount; ++row) {
        stream << model->item(row, 0)->text() << "   "; // Colonne ID
        stream << model->item(row, 1)->text() << "    "; // Colonne NOM
        stream << model->item(row, 2)->text() << "   "; // Colonne CATEGORIE
        stream << model->item(row, 3)->text() <<      "          "; // Colonne DESCRIPTION
        stream << model->item(row, 4)->text() <<     "          "; // Colonne DUREE
        stream << model->item(row, 5)->text() << "        "; // Colonne PRIX
        stream << model->item(row, 6)->text() << "         "; // Colonne DATES
        stream << model->item(row, 7)->text() << "         \n"; // Colonne ID_EMPLOYE
    }

    // Fermer le fichier
    file.close();

    // Confirmation de l'exportation
    QMessageBox::information(this, "Succès", "Les données ont été exportées avec succès !");
}





// chrono







void MainWindow::startChronometer()
{
    // Intervalle du chronomètre (en millisecondes, ici 1000 ms = 1 seconde)
    timer->setInterval(1000);

    // Démarrer le chronomètre
    timer->start();

    QMessageBox::information(this, "Chronomètre", "Un chronomètre a été déclenché pour surveiller les dates proches !");
}
#include <QTimer>


void MainWindow::on_PARAMETRE_clicked()
{
    // Récupérer la date actuelle
    QDateTime currentDate = QDateTime::currentDateTime();

    // Variable pour la période à vérifier (ex: 7 jours à partir d'aujourd'hui)
    int warningPeriod = 7; // Période en jours
    bool dateProche = false; // Indicateur pour savoir si une date proche est trouvée

    // Parcourir toutes les lignes de la table pour comparer les dates
    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Récupérer la date stockée dans la colonne 6 (ou la colonne de date)
        QStandardItem *dateItem = model->item(row, 6);  // Colonne des dates
        QString storedDateStr = dateItem->text();

        // Convertir la date stockée en QDateTime
        QDateTime storedDate = QDateTime::fromString(storedDateStr, "yyyy-MM-dd hh:mm:ss");

        // Calculer la différence entre la date actuelle et la date stockée
        int daysDifference = currentDate.daysTo(storedDate);

        // Vérifier si la date est proche du jour actuel (par exemple, dans les 7 jours)
        if (daysDifference >= 0 && daysDifference <= warningPeriod) {
            dateProche = true;  // Une date proche est trouvée
            break;  // Pas besoin de vérifier d'autres dates
        }
    }

    // Si une date proche est détectée, démarrer le chronomètre
    if (dateProche) {
        startChronometer();
    } else {
        QMessageBox::information(this, "Paramètre", "Aucune date proche n'a été détectée.");
    }
}

void MainWindow::onTimerTick()
{
    // Mettre à jour un label avec le temps écoulé
    static int seconds = 0;  // Variable statique pour compter les secondes

    seconds++;  // Incrémenter les secondes à chaque tick
    QString timeText = QString::number(seconds) + " secondes écoulées";

    // Mettre à jour un label sur l'interface graphique (assurez-vous que 'timeLabel' existe dans votre UI)
    ui->timeLabel->setText(timeText);

    // Pour déboguer et voir les ticks dans la console
    qDebug() << "Tick! " << seconds << " secondes écoulées";
}
