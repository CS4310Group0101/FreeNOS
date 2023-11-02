#ifndef _BIN_RENICE_RENICE_H
#define _BIN_RENICE_RENICE_H

#include <POSIXApplication.h>

class Renice : public POSIXApplication {
public:
    Renice(int argc, char **argv);
    virtual ~Renice();

    virtual Result exec();
};

#endif /* _BIN_RENICE_RENICE_H */