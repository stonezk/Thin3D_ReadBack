# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..

include ${TOP}/arch.mk

#SHARED = 1
LIBRARY = xpcom
LIBRARIES = iprt

FILES += \
    xpcom/reflect/xptcall/src/xptcall \
	nsprpub/pr/src/io/prfdcach  \
        nsprpub/pr/src/io/prmwait  \
        nsprpub/pr/src/io/priometh  \
        nsprpub/pr/src/io/pripv6  \
        nsprpub/pr/src/io/prmapopt  \
        nsprpub/pr/src/io/prlayer  \
        nsprpub/pr/src/io/prlog  \
        nsprpub/pr/src/io/prmmap  \
        nsprpub/pr/src/io/prpolevt  \
        nsprpub/pr/src/io/prprf  \
        nsprpub/pr/src/io/prscanf  \
        nsprpub/pr/src/io/prstdio  \
        nsprpub/pr/src/linking/prlink  \
        nsprpub/pr/src/malloc/prmalloc  \
        nsprpub/pr/src/malloc/prmem  \
        nsprpub/pr/src/md/prosdep  \
        nsprpub/pr/src/memory/prseg  \
        nsprpub/pr/src/memory/prshm  \
        nsprpub/pr/src/memory/prshma  \
        nsprpub/pr/src/misc/pralarm  \
        nsprpub/pr/src/misc/pratom  \
        nsprpub/pr/src/misc/prcountr  \
        nsprpub/pr/src/misc/prdtoa  \
        nsprpub/pr/src/misc/prenv  \
        nsprpub/pr/src/misc/prerr  \
        nsprpub/pr/src/misc/prerror  \
        nsprpub/pr/src/misc/prerrortable  \
        nsprpub/pr/src/misc/prinit  \
        nsprpub/pr/src/misc/prinrval  \
        nsprpub/pr/src/misc/pripc  \
        nsprpub/pr/src/misc/prlog2  \
	nsprpub/pr/src/misc/prlong  \
        nsprpub/pr/src/misc/prnetdb  \
        nsprpub/pr/src/misc/prolock  \
        nsprpub/pr/src/misc/prrng  \
        nsprpub/pr/src/misc/prsystem  \
        nsprpub/pr/src/misc/prtime  \
        nsprpub/pr/src/misc/prthinfo  \
        nsprpub/pr/src/misc/prtpool  \
        nsprpub/pr/src/misc/prtrace  \
        nsprpub/pr/src/threads/prcmon  \
        nsprpub/pr/src/threads/prrwlock  \
        nsprpub/pr/src/threads/prtpd  \
        nsprpub/pr/src/prvrsion  \
        nsprpub/lib/ds/plarena  \
        nsprpub/lib/ds/plhash  \
        nsprpub/lib/libc/src/strlen  \
        nsprpub/lib/libc/src/strcpy  \
        nsprpub/lib/libc/src/strdup  \
        nsprpub/lib/libc/src/strcat  \
        nsprpub/lib/libc/src/strcmp  \
        nsprpub/lib/libc/src/strccmp  \
        nsprpub/lib/libc/src/strchr  \
        nsprpub/lib/libc/src/strpbrk  \
        nsprpub/lib/libc/src/strstr  \
        nsprpub/lib/libc/src/strcstr  \
        nsprpub/lib/libc/src/strtok  \
        nsprpub/lib/libc/src/base64  \
        nsprpub/lib/libc/src/plerror  \
        nsprpub/lib/libc/src/plgetopt \
        nsprpub/pr/src/md/unix/linux

FILES += \
	nsprpub/pr/src/md/unix/unix  \
        nsprpub/pr/src/md/unix/unix_errors  \
        nsprpub/pr/src/md/unix/uxproces  \
        nsprpub/pr/src/md/unix/uxrng  \
        nsprpub/pr/src/md/unix/uxshm  \
        nsprpub/pr/src/md/unix/uxwrap  \
        nsprpub/pr/src/pthreads/ptio  \
        nsprpub/pr/src/pthreads/ptsynch  \
        nsprpub/pr/src/pthreads/ptthread  \
        nsprpub/pr/src/pthreads/ptmisc 

FILES += \
        xpcom/typelib/xpt/src/xpt_arena  \
        xpcom/typelib/xpt/src/xpt_struct  \
        xpcom/typelib/xpt/src/xpt_xdr \
	nsprpub/pr/src/md/unix/os_Linux_x86

FILES += \
	xpcom/string/src/nsAString \
        xpcom/string/src/nsDependentSubstring \
        xpcom/string/src/nsObsoleteAStringThunk \
        xpcom/string/src/nsPrintfCString \
        xpcom/string/src/nsPromiseFlatString \
        xpcom/string/src/nsReadableUtils \
        xpcom/string/src/nsSubstring \
        xpcom/string/src/nsSubstringTuple \
        xpcom/string/src/nsString \
        xpcom/string/src/nsStringComparator \
        xpcom/string/src/nsStringObsolete \
	xpcom/base/nsAllocator \
        xpcom/base/nsConsoleMessage \
        xpcom/base/nsConsoleService \
        xpcom/base/nsDebugImpl \
        xpcom/base/nsErrorService \
        xpcom/base/nsExceptionService \
        xpcom/base/nsID \
        xpcom/base/nsMemoryImpl \
        xpcom/base/nsTraceRefcntImpl \
        xpcom/base/nsStackFrameUnix \
	xpcom/ds/pldhash  \
        xpcom/ds/nsAtomTable \
        xpcom/ds/nsAtomService \
        xpcom/ds/nsByteBuffer \
        xpcom/ds/nsCheapSets \
        xpcom/ds/nsCRT \
        xpcom/ds/nsDeque \
        xpcom/ds/nsEmptyEnumerator \
        xpcom/ds/nsEnumeratorUtils \
        xpcom/ds/nsFixedSizeAllocator \
        xpcom/ds/nsHashSets \
        xpcom/ds/nsHashtable \
        xpcom/ds/nsObserverList \
        xpcom/ds/nsObserverService \
        xpcom/ds/nsProperties \
        xpcom/ds/nsPersistentProperties \
        xpcom/ds/nsQuickSort \
        xpcom/ds/nsRecyclingAllocator \
        xpcom/ds/nsStaticNameTable \
        xpcom/ds/nsStringEnumerator \
        xpcom/ds/nsSupportsArray \
        xpcom/ds/nsSupportsArrayEnumerator \
        xpcom/ds/nsSupportsPrimitives \
        xpcom/ds/nsTHashtable \
        xpcom/ds/nsUnicharBuffer \
        xpcom/ds/nsVariant \
        xpcom/ds/nsVoidArray \
        xpcom/ds/nsTextFormatter \
        xpcom/ds/nsTimelineService \
	xpcom/ds/nsValueArray \
        xpcom/ds/nsCOMArray \
        xpcom/ds/nsArray \
        xpcom/ds/nsArrayEnumerator \
	xpcom/io/nsAppFileLocationProvider \
        xpcom/io/nsBinaryStream \
        xpcom/io/nsByteArrayInputStream \
        xpcom/io/nsDirectoryService \
        xpcom/io/nsEscape \
        xpcom/io/nsFastLoadFile \
        xpcom/io/nsFastLoadService \
        xpcom/io/nsInputStreamTee \
        xpcom/io/nsLinebreakConverter \
        xpcom/io/nsLocalFileCommon \
        xpcom/io/nsMultiplexInputStream \
        xpcom/io/nsPipe3 \
        xpcom/io/nsStreamUtils \
        xpcom/io/nsScriptableInputStream \
        xpcom/io/nsSegmentedBuffer \
        xpcom/io/SpecialSystemDirectory \
        xpcom/io/nsStorageStream \
        xpcom/io/nsStringStream \
        xpcom/io/nsUnicharInputStream \
        xpcom/io/nsNativeCharsetUtils \
	xpcom/io/nsLocalFileUnix \
	xpcom/components/nsCategoryManager \
        xpcom/components/nsComponentManager \
        xpcom/components/nsComponentManagerObsolete \
        xpcom/components/nsNativeComponentLoader \
        xpcom/components/nsServiceManagerObsolete \
        xpcom/components/xcDll \
        xpcom/components/nsStaticComponentLoader \
	xpcom/threads/plevent  \
        xpcom/threads/nsAutoLock \
        xpcom/threads/nsEnvironment \
        xpcom/threads/nsEventQueue \
        xpcom/threads/nsEventQueueService \
        xpcom/threads/nsThread \
        xpcom/threads/nsTimerImpl \
        xpcom/threads/nsProcessCommon \
        xpcom/threads/TimerThread \
	xpcom/reflect/xptinfo/src/xptiFile \
        xpcom/reflect/xptinfo/src/xptiInterfaceInfo \
        xpcom/reflect/xptinfo/src/xptiInterfaceInfoManager \
        xpcom/reflect/xptinfo/src/xptiManifest \
        xpcom/reflect/xptinfo/src/xptiMisc \
        xpcom/reflect/xptinfo/src/xptiTypelibGuts \
        xpcom/reflect/xptinfo/src/xptiWorkingSet \
        xpcom/reflect/xptinfo/src/xptiZipItem \
        xpcom/reflect/xptinfo/src/xptiZipLoader \
	xpcom/reflect/xptcall/src/md/unix/xptcinvoke_x86_64_linux \
        xpcom/reflect/xptcall/src/md/unix/xptcstubs_x86_64_linux \
	xpcom/proxy/src/nsProxyEvent \
	xpcom/proxy/src/nsProxyEventClass \
	xpcom/proxy/src/nsProxyEventObject \
	xpcom/proxy/src/nsProxyObjectManager \
	xpcom/proxy/src/nsProxyRelease \
	xpcom/glue/nsCOMPtr \
        xpcom/glue/nsComponentManagerUtils \
        xpcom/glue/nsDebug \
        xpcom/glue/nsGenericFactory \
        xpcom/glue/nsIInterfaceRequestorUtils \
        xpcom/glue/nsMemory \
        xpcom/glue/nsTraceRefcnt \
        xpcom/glue/nsWeakReference \
	xpcom/build/nsXPComInit \
        xpcom/build/nsStringAPI \
	ipc/ipcd/shared/src/ipcLog \
        ipc/ipcd/shared/src/ipcConfig \
        ipc/ipcd/shared/src/ipcMessage \
        ipc/ipcd/shared/src/ipcMessagePrimitives \
        ipc/ipcd/shared/src/ipcStringList \
        ipc/ipcd/shared/src/ipcIDList \
        ipc/ipcd/shared/src/ipcm \
	ipc/ipcd/client/src/ipcdclient \
        ipc/ipcd/client/src/ipcService \
        ipc/ipcd/client/src/ipcModuleFactory \
        ipc/ipcd/extensions/dconnect/src/ipcDConnectService\
    \
        ipc/ipcd/util/src/ipcMessageReader \
        ipc/ipcd/util/src/ipcMessageWriter \
    \
        ipc/ipcd/extensions/lock/src/ipcLockProtocol \
        ipc/ipcd/extensions/lock/src/ipcLockService \
    \
        ipc/ipcd/extensions/transmngr/src/tmTransactionService \
    \
        ipc/ipcd/extensions/transmngr/common/tmTransaction \
        ipc/ipcd/extensions/transmngr/common/tmVector \
	ipc/ipcd/client/src/ipcConnectionUnix \
	ipc/ipcd/daemon/src/ipcd \
        ipc/ipcd/daemon/src/ipcClient \
        ipc/ipcd/daemon/src/ipcModuleReg \
        ipc/ipcd/daemon/src/ipcCommandModule \
	ipc/ipcd/daemon/src/ipcdUnix \
		

#LIB_DEFS = iprt.def

FLAGS = -DIN_RING3 -DRT_OS_LINUX -I/usr/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include/ \
	-I/usr/include/libIDL-2.0 -Ixpcom/typelib/xpt/public/ \
	-Insprpub/pr/include/ -Insprpub/pr/include/obsolete/ -Iinclude \
	-Iinclude/nsprpub -Insprpub/pr/include/private/ \
	-Iinclude/string/ -Iinclude/xpcom -Iinclude/ipcd \
	-Ixpcom/build -Ixpcom/ds -Ixpcom/reflect/xptcall/src \
	-Ixpcom/io -Ixpcom/base -Ixpcom/components -Ixpcom/doc \
    -Ixpcom/libxpt -Ixpcom/MoreFiles -Ixpcom/glue -Ixpcom/obsolete \
    -Ixpcom/proxy/src -Ixpcom/reflect -Ixpcom/sample -Ixpcom/string \
    -Ixpcom/stub -Ixpcom/threads -Ixpcom/tools -Ixpcom/typelib \
	-Iipc/ipcd/shared/src -Iipc/ipcd/client/src \
	-Iipc/ipcd/extensions/lock/src -Iipc/ipcd/extensions/transmngr/src/ \
	-Iipc/ipcd/extensions/transmngr/common -Iipc/ipcd/extensions/dconnect/src \
	-DVBOX -D_NSPR_BUILD_ -DHAVE_LIBDL \
	-DHAVE_LCHOWN=1 \
	-DHAVE_STRERROR=1 \
	-DFORCE_PR_LOG \
    -DVBOX_USE_IPRT_IN_NSPR \
    -DLINUX=1 \
	-D_POSIX_SOURCE=1 \
	-D_BSD_SOURCE=1 \
	-D_SVID_SOURCE=1 \
	-D_REENTRANT=1 \
	-D_LARGEFILE64_SOURCE=1 \
	-DHAVE_FCNTL_FILE_LOCKING=1 \
	-DHAVE_CVAR_BUILT_ON_SEM \
	-D_PR_PTHREADS \
    -D_IMPL_NS_COM -DEXPORT_XPTI_API \
    -D_IMPL_NS_BASE -DEXPORT_XPT_API \
    -DEXPORT_XPTC_API \
    -DBUILD_DCONNECT="1" \
    -DXP_UNIX \
    -D__USE_GNU \
	-DMOZ_USER_DIR=\".mozilla\" \
	-DMOZ_DLL_SUFFIX=\".so\"
    
CFLAGS += $(FLAGS)
CXXFLAGS += $(FLAGS)

ifeq ($(ARCH), WIN_NT)
LDFLAGS += user32.lib ws2_32.lib
else
ifeq ($(ARCH),FreeBSD)
LDFLAGS += -lpthread
else
ifeq ($(ARCH), OSF1)
LDFLAGS += -lpthread
else
ifndef IRIX_64BIT
LDFLAGS += -ldl -lpthread
else
LDFLAGS += -lpthread
endif
endif
endif
endif

include ${TOP}/cr.mk
