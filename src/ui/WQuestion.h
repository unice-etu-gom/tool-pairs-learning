#ifndef WQUESTION_H
#define WQUESTION_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

#include "core/CTranslation.h"

class CDataManager;


class   WQuestion
        :   public  QWidget
{
    Q_OBJECT

public:

    explicit WQuestion(CDataManager* argManager_p, QWidget *parent = 0);



protected:
private:

    void    _create_ui(void);
    void    _create_layout(void);
    void    _create_connections(void);

    void    dataReset(void);
    void    dataClear(void);
    void    dataLoad(CTranslation argTranslation);
    void    dataLoadRandom(void);

    void    verifyAnswer(void);

    Q_SIGNAL    void    validAnswer(void);
    Q_SIGNAL    void    wrongAnswer(void);

    Q_SLOT  void    on_p_dataManager_translationsListOriginalUpdated(void);
    Q_SLOT  void    on_p_inputLE_returnPressed(void);
    Q_SLOT  void    on_p_submitPB_clicked(bool);



public:
protected:
private:

    enum    ETextIdentifiers
    {
        ETextUndef  = -1,
        EText1,
        EText2,

        ETextIdentifiersCount
    } m_textDisplayedID;

    CTranslation    m_currentTranslation;

    CDataManager*   p_dataManager;
    QLineEdit*      p_inputLE;
    QPushButton*    p_submitPB;
    QLabel*         p_wordToTranslateL;



};

#endif  /*< WQUESTION_H */
