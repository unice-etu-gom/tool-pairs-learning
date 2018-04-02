#include <stdlib.h>
#include <time.h>

#include <QApplication>

#include "core/CFileParser.h"
#include "core/Log.h"
#include "ui/MainWindow.h"

/* ########################################################################## */
/* ########################################################################## */

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);


#if 0
    CFileParser lFileParser;
    if( ! lFileParser.loadFile( "../../data/03_01.csv" ) )
    {
        LOG_DBG( "An error occured while parsing file : %s",
                 lFileParser.errorString().toStdString().c_str() );
    }
    else
    {
        foreach( CTranslation lTranslation, lFileParser.translationsList() )
        {
            LOG_DBG( "+-- CTranslation item : " );
            LOG_DBG( "    +-- '%s'",lTranslation.text1().toStdString().c_str());
            LOG_DBG( "    +-- '%s'",lTranslation.text2().toStdString().c_str());
        }
    }
#else
    MainWindow w;
    w.show();

    return a.exec();
#endif
}

/* ########################################################################## */
/* ########################################################################## */
