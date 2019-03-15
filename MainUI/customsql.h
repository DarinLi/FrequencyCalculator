#ifndef CUSTOMSQL_H
#define CUSTOMSQL_H

#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QString>
#include <QVariantList>
#include <QMessageBox>

#include <QObject>

class CustomSql
{
public:
    CustomSql();

    static bool connect(const QString &);
    static int sqlRowMaxCount(const QString &);
    static QVariantList sqlRowData(const QString &, const QString &);
    static QVariantList sqlcolumnData(const QString &, int);
    static int sqlcolumnID(const QString &, const QString &);
};

#endif // CUSTOMSQL_H
