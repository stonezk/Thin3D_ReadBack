#ifndef CR_ERRORSPU_H
#define CR_ERRORSPU_H

#include "cr_spu.h"

extern int crErrorSPULoad( char **name, char **super, SPUInitFuncPtr *init,
             SPUSelfDispatchFuncPtr *self, SPUCleanupFuncPtr *cleanup,
             SPUOptionsPtr *options, int *flags );


#endif /* CR_ERRORSPU_H */

