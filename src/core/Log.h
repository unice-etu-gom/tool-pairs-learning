#ifndef LOG_H
#define LOG_H

#include <QDebug>
#include <QString>


#define M_STR_POSITION_IN_CODE  (   QString( "%1 +%2 (%3) : " )        \
                                    .arg(__FILE__).arg(__LINE__)        \
                                    .arg(__FUNCTION__).toStdString()    )


#define LOG_DBG(format,...)                     \
                qDebug( "DEBUG:: %s" format,             \
                M_STR_POSITION_IN_CODE.c_str(), \
                ##__VA_ARGS__ )


#endif  /*< LOG_H */
