#ifndef CFILEPARSER_H
#define CFILEPARSER_H

#include <QObject>

class   QTextStream;

#include "CTranslation.h"



class   CFileParser
        :   public  QObject
{
    Q_OBJECT

public:

    explicit CFileParser(QObject *parent = 0);


    QString errorString(void) const;


    bool    loadFile(const QString& argFileName);


    QList<CTranslation> translationsList(void) const;



protected:
private:

    bool    parse(QTextStream* argTextStreamPtr );
    bool    parseLine( const QString& argLine );

    QString fieldClean( const QString& argField);



public:
protected:
private:

    QString             m_lastError;
    QList<CTranslation> m_translationsList;



};

#endif  /*< CFILEPARSER_H */
