#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;

class CDataManager;
class WQuestion;



class   MainWindow
        :   public  QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();



protected:
private:

    void    _createUi(void);
    void    _createUi_menus(void);
    void    _create_layout(void);
    void    _create_connections(void);

    void    importFilesFromDialog(void);
    void    dataReset(void);

    void    ui_updateCounters(void);

    Q_SLOT  void    on_p_menuFile_loadFiles(void);
    Q_SLOT  void    on_p_menuFile_resetData(void);
    Q_SLOT  void    on_p_menuFile_clearAll(void);
    Q_SLOT  void    on_p_wQuestion_validAnswer(void);
    Q_SLOT  void    on_p_wQuestion_wrongAnswer(void);



public:
protected:
private:

    int             m_answersValidCount;
    int             m_answersWrongCount;

    QLabel*         p_answerValidL;
    QLabel*         p_answerWrongL;
    CDataManager*   p_dataManager;
    WQuestion*      p_wQuestion;



};

#endif  /*< MAINWINDOW_H */
