#include "pixshot.h"
#include "commons/commons.h"

#include <QSharedMemory>

#define NORMAL_RUN 0
#define ABNORMAL_RUN -1

/**
 * The main function
 *
 * @brief qMain
 * @param argc the argument count
 * @param argv the argument list
 * @return run status
 */
int main(int argc, char *argv[])
{
    PixShot *pixshotInstance = new PixShot(argc, argv);
    pixshotInstance->init();

    if(pixshotInstance->exec() == NORMAL_RUN)
    {
        return NORMAL_RUN;
    }
    else
    {
        return ABNORMAL_RUN;
    }
}
