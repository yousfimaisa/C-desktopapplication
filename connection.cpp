#include "connection.h"
#include "Prestation.h"
Connection::Connection()
{}
bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_PROJECT");//inserer le nom de la source de données
    db.setUserName("maissa");//inserer nom de l'utilisateur
    db.setPassword("oracle");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;
/*
    QSqlQuery query;
    query.prepare("INSERT INTO Prestations (id, description, categorie, prix, date) "
                  "VALUES (:id, :description, :categorie, :prix, :date)");
    query.bindValue(":id", Prestation.getId());
    // ... bind other values ...
    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return false;
    }

*/

    return  test;
}
