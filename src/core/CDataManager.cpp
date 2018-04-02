#include "CDataManager.h"

#include <QString>

#include "CFileParser.h"
#include "Log.h"


/* ########################################################################## */
/* ########################################################################## */

CDataManager::CDataManager(QObject *parent) : QObject(parent)
{

}

/* ########################################################################## */
/* ########################################################################## */

void    CDataManager::clearAll(void)
{
    this->m_practiceList.clear();
    this->m_translationsListOriginal.clear();

    emit this->translationsListOriginalUpdated();
}

/* ########################################################################## */
/* ########################################################################## */

bool    CDataManager::importFromFilesCSV( const QStringList &argFilesList,
                                          QString& argErrorString )
{
    QList<CTranslation> lTranslationsList;
    bool                retVal              = true;


    foreach (QString lFile, argFilesList)
    {
        CFileParser lFileParser( this );
        if( ! lFileParser.loadFile( lFile ) )
        {
            argErrorString  = trUtf8("Error while loading file '%1' : %2" )
                              .arg( lFile )
                              .arg( lFileParser.errorString() );

            LOG_DBG( "%s", argErrorString.toStdString().c_str() );
            retVal  = false;
            break;
        }

        lTranslationsList.append( lFileParser.translationsList() );
    }


    if( retVal )
    {
        this->m_translationsListOriginal.append( lTranslationsList );
        this->practiceListReset();

        emit this->translationsListOriginalUpdated();
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

QList<CTranslation> CDataManager::practiceList(void) const
{
    return this->m_practiceList;
}

/* ########################################################################## */
/* ########################################################################## */

int CDataManager::practiceListCount(void) const
{
    return this->m_practiceList.count();
}

/* ########################################################################## */
/* ########################################################################## */

void    CDataManager::practiceListItemAdd(const CTranslation &argItemToAdd)
{
    this->m_practiceList.append( argItemToAdd );
}

/* ########################################################################## */
/* ########################################################################## */

void    CDataManager::practiceListItemRemove(const CTranslation &argItemToRemove)
{
    for( int i = 0 ; i < this->m_practiceList.count() ; ++i )
    {
        if( this->m_practiceList.at( i ) == argItemToRemove )
        {
            this->m_practiceList.removeAt( i );
            break;
        }
    }
}

/* ########################################################################## */
/* ########################################################################## */

void CDataManager::practiceListReset()
{
    this->m_practiceList.clear();
    for( int i = 0 ; i < 2 ; ++i )
    {
        this->m_practiceList.append( this->translationsListOrignal() );
    }
}

/* ########################################################################## */
/* ########################################################################## */

QList<CTranslation> CDataManager::translationsListOrignal() const
{
    return this->m_translationsListOriginal;
}

/* ########################################################################## */
/* ########################################################################## */
