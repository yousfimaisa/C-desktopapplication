#include "prestation.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

Prestation::Prestation() {}

Prestation::Prestation(int ID, const QString& NOM, const QString& CATEGORIE, double PRIX, const QString& DUREE)
    : ID(ID), NOM(NOM), CATEGORIE(CATEGORIE), DESCRIPTION(""), PRIX(PRIX), DUREE(DUREE) {}

int Prestation::getID() const {
    return ID;
}

QString Prestation::getNOM() const {
    return NOM;
}

QString Prestation::getDESCRIPTION() const {
    return DESCRIPTION;
}

QString Prestation::getCATEGORIE() const {
    return CATEGORIE;
}

double Prestation::getPRIX() const {
    return PRIX;
}

QString Prestation::getDUREE() const {
    return DUREE;
}

void Prestation::setNOM(const QString& NOM) {
    this->NOM = NOM;
}

void Prestation::setCATEGORIE(const QString& CATEGORIE) {
    this->CATEGORIE = CATEGORIE;
}

void Prestation::setDESCRIPTION(const QString& DESCRIPTION) {
    this->DESCRIPTION = DESCRIPTION;
}

void Prestation::setPRIX(double PRIX) {
    this->PRIX = PRIX;
}

void Prestation::setDUREE(const QString& DUREE) {
    this->DUREE = DUREE;
}
/*
bool Prestation::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Prestations WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true; // Deletion successful
    } else {
        qDebug() << "Error deleting prestation:" << query.lastError().text();
        return false; // Deletion failed
    }
}
*/
