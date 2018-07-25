#ifndef USERDB_H
#define USERDB_H
#include <QDebug>

class UserDb: public QObject
{
public:
    UserDb();
    void run();
};

#endif // USERDB_H
