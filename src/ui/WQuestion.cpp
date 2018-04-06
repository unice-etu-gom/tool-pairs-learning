#include "WQuestion.h"

#include <stdlib.h>
#include <time.h>

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

#include "core/CDataManager.h"
#include "core/Log.h"



/* ########################################################################## */
/* ########################################################################## */

WQuestion::WQuestion( CDataManager* argManager_p,
                      QWidget*      parent )
    :   QWidget(parent)
    ,   m_textDisplayedID( ETextUndef )
    ,   p_dataManager( argManager_p )
    ,   p_inputLE( NULL )
    ,   p_wordToTranslateL( NULL )
{
    this->_create_ui();
    this->_create_layout();

    this->dataClear();
    this->_create_connections();
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::_create_connections(void)
{
    connect( this->p_dataManager, SIGNAL(translationsListOriginalUpdated()),
             this, SLOT(on_p_dataManager_translationsListOriginalUpdated()) );

    connect( this->p_inputLE, SIGNAL(returnPressed()),
             this, SLOT(on_p_inputLE_returnPressed()) );

    connect( this->p_submitPB, SIGNAL(clicked(bool)),
             this, SLOT(on_p_submitPB_clicked(bool)) );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::_create_layout(void)
{
    QFormLayout*    p_layoutMain    = new QFormLayout();
    p_layoutMain->addRow( "<b>" + trUtf8( "Word to translate :") + "</b>",
                          this->p_wordToTranslateL );
    p_layoutMain->addRow( "<b>" + trUtf8( "Your answer :") + "</b>",
                          this->p_inputLE );
    p_layoutMain->addRow( this->p_submitPB );

    this->setLayout( p_layoutMain );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::_create_ui(void)
{
    this->p_inputLE             = new QLineEdit( this );
    this->p_submitPB            = new QPushButton( trUtf8( "Submit" ), this );
    this->p_wordToTranslateL    = new QLabel("Hello, world !", this);


//    this->p_inputLE->setEnabled( false );
//    this->p_submitPB->setEnabled( false );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::dataClear(void)
{
    this->m_currentTranslation.clear();
    this->p_inputLE->clear();
    this->m_textDisplayedID   = ETextUndef;
    this->p_wordToTranslateL->clear();
    this->setEnabled( false );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::dataLoad(CTranslation argTranslation)
{
    this->m_currentTranslation  = argTranslation;
    this->m_textDisplayedID = (ETextIdentifiers)(rand() % ETextIdentifiersCount);

    switch( this->m_textDisplayedID )
    {
        case    EText1:
            this->p_wordToTranslateL
                    ->setText( this->m_currentTranslation.text1() );
            break;


        case    EText2:
            this->p_wordToTranslateL
                    ->setText( this->m_currentTranslation.text2() );
            break;


        default:
            this->p_wordToTranslateL
                    ->setText( trUtf8("[unknown text identifier]") );
            break;
    }


    this->p_inputLE->clear();
    this->setEnabled( true );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::dataLoadRandom(void)
{
    int lItemsCount     = this->p_dataManager->practiceListCount();
    if( lItemsCount <= 0 )
    {
        int lAns    = QMessageBox::information(
                          this,
                          trUtf8( "No more words ! :)" ),
                          trUtf8( "Practice words list is empty !"
                                  "<BR>Reset it ?"),
                          QMessageBox::Yes,
                          QMessageBox::No );
        if( lAns == QMessageBox::Yes )
        {
            this->p_dataManager->practiceListReset();
            lItemsCount     = this->p_dataManager->practiceListCount();
        }
        else
        {
            this->dataClear();
            return;
        }
    }

    int lItemToSelect   = rand() % lItemsCount;

    this->dataLoad( this->p_dataManager->practiceList().at( lItemToSelect ) );
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::dataReset(void)
{
    this->dataClear();
    this->p_dataManager->practiceListReset();
    this->dataLoadRandom();
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::on_p_dataManager_translationsListOriginalUpdated(void)
{
    LOG_DBG( "Trace point." );


    if( this->p_dataManager->translationsListOrignal().isEmpty() )
    {
        LOG_DBG( "Original list is empty !" );
        this->dataClear();
    }
    else if( this->p_dataManager->practiceList().isEmpty() )
    {
        LOG_DBG( "Practice list is empty !" );
        this->dataReset();
    }
    else
    {
        this->dataLoadRandom();
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::on_p_inputLE_returnPressed()
{
    this->verifyAnswer();
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::on_p_submitPB_clicked(bool)
{
    this->verifyAnswer();
}

/* ########################################################################## */
/* ########################################################################## */

void    WQuestion::verifyAnswer(void)
{
    if( this->p_inputLE->text().isEmpty() )
    {
        return;
    }


    QString lQuestionWord;
    QString lExpectedAnswer;

    switch( this->m_textDisplayedID )
    {
        case    EText1:
            lQuestionWord   = this->m_currentTranslation.text1();
            lExpectedAnswer = this->m_currentTranslation.text2();
            break;


        case    EText2:
            lQuestionWord   = this->m_currentTranslation.text2();
            lExpectedAnswer = this->m_currentTranslation.text1();
            break;


        default:
            LOG_DBG( "Unexpected m_textDisplayedID value of '%d' !",
                     this->m_textDisplayedID );
            exit( EXIT_FAILURE );
            break;
    }

    QRegExp lRegExp( QString::fromUtf8( "[^a-zA-Z\\d\\s]" ) );
    QString lInputText  = this->p_inputLE->text();
    lInputText.remove( lRegExp );
    QString lExpectedClean  = lExpectedAnswer;
    lExpectedClean.remove( lRegExp );


    if( lInputText.toLower() == lExpectedClean.toLower() )
    {
//        QMessageBox::information( this, trUtf8( "Good answer ! :-)" ),
//                                  trUtf8( "You answered correctly !" ) );
        this->p_dataManager
                ->practiceListItemRemove( this->m_currentTranslation );

        emit this->validAnswer();
    }
    else
    {
        QMessageBox::warning( this,
                              trUtf8( "Bad answer ! :-(" ),
                              trUtf8( "You didn't answer correctly !" )
                              + "<br><br>"
                              + trUtf8( "Translation for %1 is %2" )
                              .arg( "<em>" + lQuestionWord + "</em>" )
                              .arg( "<b>" + lExpectedAnswer + "</b>" ) );

        for( int i = 0 ; i < 4 ; ++i )
        {
            this->p_dataManager
                    ->practiceListItemAdd( this->m_currentTranslation );
        }

        emit this->wrongAnswer();
    }

    this->dataLoadRandom();
}

/* ########################################################################## */
/* ########################################################################## */
