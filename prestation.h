#ifndef PRESTATION_H
#define PRESTATION_H

#include <QString>
#include <QDateTime>

class Prestation
{
public:
    Prestation();
    Prestation(int ID, const QString& NOM, const QString& CATEGORIE, double PRIX, const QString& DUREE);

    int getID() const;
    QString getNOM() const;
    QString getDESCRIPTION() const;
    QString getCATEGORIE() const;
    double getPRIX() const;
    QString getDUREE() const;

    void setNOM(const QString& NOM);
    void setCATEGORIE(const QString& CATEGORIE);
    void setDESCRIPTION(const QString& DESCRIPTION);
    void setPRIX(double PRIX);
    void setDUREE(const QString& DUREE);

    bool supprimer(int id);

private:
    int ID;
    QString NOM;
    QString DESCRIPTION;
    QString CATEGORIE;
    double PRIX;
    QString DUREE;
};

#endif // PRESTATION_H
