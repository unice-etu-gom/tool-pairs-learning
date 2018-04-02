#include "MainWindow.h"

#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include "core/CDataManager.h"
#include "core/Log.h"

#include "WQuestion.h"


/* ########################################################################## */
/* ########################################################################## */

MainWindow::MainWindow(QWidget *parent)
    :   QMainWindow(parent)
    ,   m_answersValidCount( 0 )
    ,   m_answersWrongCount( 0 )
    ,   p_answerValidL( NULL )
    ,   p_answerWrongL( NULL )
    ,   p_dataManager( new CDataManager( this ) )
    ,   p_wQuestion( NULL )
{
    this->setMinimumWidth( 600 );

    this->_createUi();
    this->_create_layout();
    this->_createUi_menus();

    this->_create_connections();

    this->ui_updateCounters();
}

/* ########################################################################## */
/* ########################################################################## */

MainWindow::~MainWindow()
{
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::_create_connections(void)
{
    connect( this->p_wQuestion, SIGNAL(validAnswer()),
             this, SLOT(on_p_wQuestion_validAnswer()) );

    connect( this->p_wQuestion, SIGNAL(wrongAnswer()),
             this, SLOT(on_p_wQuestion_wrongAnswer()) );
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::_create_layout(void)
{
    this->setCentralWidget( this->p_wQuestion );
    this->statusBar()->addWidget( new QLabel( trUtf8( "Valid answers :" ),
                                              this ) );
    this->statusBar()->addWidget( this->p_answerValidL );
    this->statusBar()->addWidget( new QLabel( " | ", this ) );
    this->statusBar()->addWidget( new QLabel( trUtf8( "Wrong answers :" ),
                                              this ) );
    this->statusBar()->addWidget( this->p_answerWrongL );
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::_createUi(void)
{
    this->p_answerValidL    = new QLabel( this );
    this->p_answerWrongL    = new QLabel( this );
    this->p_wQuestion       = new WQuestion( this->p_dataManager, this );
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::_createUi_menus(void)
{
    QMenuBar*   p_menuBar   = this->menuBar();

    QMenu*  p_menuFile  = p_menuBar->addMenu( trUtf8( "File" ) );

    p_menuFile->addAction( trUtf8( "Load files..." ),
                           this,
                           SLOT(on_p_menuFile_loadFiles()) )
            ->setShortcut( QKeySequence( trUtf8( "Ctrl+O" ) ) );

    p_menuFile->addAction( trUtf8( "Reset data" ),
                           this,
                           SLOT(on_p_menuFile_resetData()) )
            ->setToolTip( trUtf8( "Clears data and resets the \"practice\" list"
                                  " to its original state.") );

    p_menuFile->addAction( trUtf8( "Clear all data" ),
                           this,
                           SLOT(on_p_menuFile_clearAll()) )
            ->setToolTip( trUtf8( "Clears all data and removes everything from"
                                  " the \"known words\" list.") );
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::dataReset(void)
{
    this->p_dataManager->practiceListReset();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::importFilesFromDialog()
{
    QStringList lFilesList
            = QFileDialog::getOpenFileNames(
                  this,
                  trUtf8("Select CSV files to import..."),
                  QString(),
                  "CSV files(*.csv);;All files (*)" );


#ifdef  DEBUG
    foreach( QString lFile, lFilesList )
    {
        LOG_DBG( "Fichier sélectionné : '%s'",
                 lFile.toStdString().c_str() );
    }
#endif

    QString lErrorString;

    if( ! this->p_dataManager->importFromFilesCSV( lFilesList, lErrorString ) )
    {
        QMessageBox::warning( this,
                              trUtf8("File import error"),
                              lErrorString );
    }


}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::on_p_menuFile_clearAll(void)
{
    this->p_dataManager->clearAll();
    this->dataReset();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::on_p_menuFile_loadFiles(void)
{
    this->importFilesFromDialog();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::on_p_menuFile_resetData(void)
{
    this->dataReset();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::on_p_wQuestion_validAnswer(void)
{
    ++this->m_answersValidCount;
    this->ui_updateCounters();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::on_p_wQuestion_wrongAnswer(void)
{
    ++this->m_answersWrongCount;
    this->ui_updateCounters();
}

/* ########################################################################## */
/* ########################################################################## */

void    MainWindow::ui_updateCounters(void)
{
    this->p_answerValidL->setNum( this->m_answersValidCount );
    this->p_answerWrongL->setNum( this->m_answersWrongCount );
}

/* ########################################################################## */
/* ########################################################################## */
