#ifndef CTRANSLATION_H
#define CTRANSLATION_H

#include <QString>



class   CTranslation
{

public:

    explicit CTranslation();
    explicit CTranslation( const QString& argTxt1, const QString& argTxt2);


    bool    operator ==(const CTranslation& argOther) const;


    void    clear(void);

    const QString& text1(void) const;
    const QString& text2(void) const;



protected:
private:



public:
protected:
private:

    QString m_text1;
    QString m_text2;



};

#endif  /*< CTRANSLATION_H */
