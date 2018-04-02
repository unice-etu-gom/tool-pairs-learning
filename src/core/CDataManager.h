#ifndef CDATAMANAGER_H
#define CDATAMANAGER_H

#include <QObject>

#include <QStringList>

#include "CTranslation.h"



class   CDataManager
        :   public  QObject
{
    Q_OBJECT

public:

    explicit CDataManager(QObject *parent = 0);


    bool    importFromFilesCSV( const QStringList&  argFilesList,
                                QString&            argErrorString );


    void    clearAll(void);


    QList<CTranslation> translationsListOrignal(void) const;


    QList<CTranslation> practiceList(void) const;
    int                 practiceListCount(void) const;
    void                practiceListReset(void);

    void            practiceListItemAdd(const CTranslation& argItemToAdd);
    void            practiceListItemRemove(const CTranslation& argItemToRemove);


    Q_SIGNAL    void    translationsListOriginalUpdated(void);



protected:
private:



public:
protected:
private:

    QList<CTranslation> m_practiceList;
    QList<CTranslation> m_translationsListOriginal;



};

#endif  /*< CDATAMANAGER_H */
