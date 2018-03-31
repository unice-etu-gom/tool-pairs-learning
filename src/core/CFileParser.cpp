#include "CFileParser.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

#include "Log.h"


/* ########################################################################## */
/* ########################################################################## */

static const QString    C_FIELD_SEPARATOR   = ";";

/* ########################################################################## */
/* ########################################################################## */

CFileParser::CFileParser(QObject *parent)
    :   QObject(parent)
{
}

/* ########################################################################## */
/* ########################################################################## */

QString CFileParser::errorString() const
{
    return this->m_lastError;
}

/* ########################################################################## */
/* ########################################################################## */

QString CFileParser::fieldClean(const QString &argField)
{
    QString retVal  = argField;

    retVal  = retVal.remove( QRegExp( "^ *" ) );
    retVal  = retVal.remove( QRegExp( " *$" ) );

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool CFileParser::loadFile(const QString &argFileName)
{
    QFile   lFile;
    bool    retVal  = true;


    lFile.setFileName( argFileName );


    if( ! lFile.open( QFile::ReadOnly ) )
    {
        this->m_lastError   = lFile.errorString();
        retVal  = false;
    }

    else if( ! this->parse( new QTextStream( &lFile ) ) )
    {
        retVal  = false;
    }



    if( lFile.isOpen() )
    {
        lFile.close();
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CFileParser::parse(QTextStream *argTextStreamPtr)
{
    QString lLine;
    bool    retVal  = true;


    do
    {
        lLine   = argTextStreamPtr->readLine().toUtf8();
        if( ! lLine.isNull() )
        {
            LOG_DBG( "Reading line : '%s'",
                     lLine.toStdString().c_str() );

            this->parseLine( lLine );
        }
    } while( ! argTextStreamPtr->atEnd() );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CFileParser::parseLine(const QString &argLine)
{
    QStringList lFields = argLine.split( C_FIELD_SEPARATOR );
    bool        retVal  = true;

    if( lFields.count() != 2 )
    {
        this->m_lastError
                = QString( "Bad fields count of %1 for line '%2'" )
                .arg( lFields.count() ).arg( argLine );
        retVal  = false;
    }
    else
    {
        CTranslation    lTranslation( this->fieldClean( lFields.at( 0 ) ),
                                      this->fieldClean( lFields.at( 1 ) ) );
        this->m_translationsList.append( lTranslation );
    }



    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

QList<CTranslation> CFileParser::translationsList(void) const
{
    return this->m_translationsList;
}

/* ########################################################################## */
/* ########################################################################## */
