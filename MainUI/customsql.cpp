#include "customsql.h"

CustomSql::CustomSql()
{

}

bool CustomSql::connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(dbName);

    if(!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This app needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);

        return false;
    }

    return true;
}

int CustomSql::sqlRowMaxCount(const QString &dbTable)
{
    QString select_max_sql = QString("select count(*) from %1").arg(dbTable);
    QSqlQuery sql_query;

    sql_query.prepare(select_max_sql);

    if(!sql_query.exec())
        return -1;
    else
    {
        while(sql_query.next()) {
            return sql_query.value(0).toInt();
        }
        return -2;
    }
}

QVariantList CustomSql::sqlRowData(const QString &dbTable, const QString &rowname)
{
    QString select_max_sql = QString("select %1 from %2").arg(rowname).arg(dbTable);
    QSqlQuery sql_query;
    QVariantList sql_query_data;

    sql_query.prepare(select_max_sql);

    if(sql_query.exec())
    {
        while(sql_query.next())
            sql_query_data.append(sql_query.value(0));
    }

    return sql_query_data;
}

QVariantList CustomSql::sqlcolumnData(const QString &dbTable, int bandid)
{
    QString select_max_sql = QString("select * from %1 where id = %2").arg(dbTable).arg(bandid);
    QSqlQuery sql_query;
    QVariantList sql_query_data;

    int columnmax = 0;

    if(dbTable == "NRBandInfo")
        columnmax = 24;
    else if(dbTable == "LTEBandInfo")
        columnmax = 14;
    else
        columnmax = 12;

    sql_query.prepare(select_max_sql);

    if(sql_query.exec())
    {
        while(sql_query.next())
            for (int i = 0; i< columnmax; i++ )
                sql_query_data.append(sql_query.value(i));
    }

    return sql_query_data;
}

int CustomSql::sqlcolumnID(const QString &dbTable, const QString &rowname)
{
    QString select_max_sql = QString("select id from %1 where Band_Name = '%2'").arg(dbTable).arg(rowname);
    QSqlQuery sql_query;
    QVariantList sql_query_data;

    int id = -1;

    sql_query.prepare(select_max_sql);

    if(sql_query.exec())
    {
        while(sql_query.next())
            id = sql_query.value(0).toInt();
    }

    return id;
}
