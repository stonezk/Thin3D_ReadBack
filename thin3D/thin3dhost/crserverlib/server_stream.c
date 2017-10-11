/* Copyright (c) 2001, Stanford University
 * All rights reserved
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

#include "server.h"
#include "cr_unpack.h"
#include "cr_error.h"
#include "cr_endian.h"
#include "cr_mem.h"
#include "server_dispatch.h"

//add szk 
char Terminal_ip[32] = {0};
unsigned long long Terminal_pid = 0;
extern int sockfd_3D;

/**
 * Accept a new client connection, create a new CRClient and add to run queue.
 */
void
crServerAddNewClient(void)
{
    CRClient *newClient = (CRClient *) crCalloc(sizeof(CRClient));

    if (newClient) {
        newClient->spu_id = cr_server.client_spu_id;
        newClient->conn = crNetAcceptClient( cr_server.protocol, NULL,
                                                                                 cr_server.tcpip_port,
                                                                                 cr_server.mtu, 1 );

        newClient->currentCtxInfo = &cr_server.MainContextInfo;

        /* add to array */
        cr_server.clients[cr_server.numClients++] = newClient;

        crServerAddToRunQueue( newClient );
    }
}


/**
 * Check if client is in the run queue.
 */
static GLboolean
FindClientInQueue(CRClient *client)
{
    RunQueue *q = cr_server.run_queue;
    while (q) {
        if (q->client == client) {
            return 1;
        }
        q = q->next;
        if (q == cr_server.run_queue)
            return 0; /* back head */
    }
    return 0;
}


#if 0
static int
PrintQueue(void)
{
    RunQueue *q = cr_server.run_queue;
    int count = 0;
    crDebug("Queue entries:");
    while (q) {
        count++;
        crDebug("Entry: %p  client: %p", q, q->client);
        q = q->next;
        if (q == cr_server.run_queue)
            return count;
    }
    return count;
}
#endif


void crServerAddToRunQueue( CRClient *client )
{
    RunQueue *q = (RunQueue *) crAlloc( sizeof( *q ) );

#ifdef VBOX_WITH_CRHGSMI
    client->conn->pClient = client;
    CRVBOXHGSMI_CMDDATA_CLEANUP(&client->conn->CmdData);
#endif

    /* give this client a unique number if needed */
    if (!client->number) {
        client->number = client->conn->u32ClientID;
    }

    crDebug("[%d]Adding client %p to the run queue", getpid(), client);

    if (FindClientInQueue(client)) {
        crError("[%d]CRServer: client %p already in the queue!", getpid(), client);
    }

    q->client = client;
    q->blocked = 0;

    if (!cr_server.run_queue)
    {
        /* adding to empty queue */
        cr_server.run_queue = q;
        q->next = q;
        q->prev = q;
    }
    else
    {
        /* insert in doubly-linked list */
        q->next = cr_server.run_queue->next;
        cr_server.run_queue->next->prev = q;

        q->prev = cr_server.run_queue;
        cr_server.run_queue->next = q;
    }

	crDebug("[%d]%s end", getpid(), __FUNCTION__);
}

static void crServerCleanupClient(CRClient *client)
{
    int32_t pos;
    CRClient *oldclient = cr_server.curClient;

    cr_server.curClient = client;

    /* Destroy any windows created by the client */
    for (pos = 0; pos<CR_MAX_WINDOWS; pos++) 
    {
        if (client->windowList[pos])
        {
            cr_server.dispatch.WindowDestroy(client->windowList[pos]);
        }
    }

    /* Check if we have context(s) made by this client left, could happen if client side code is lazy */
    for (pos = 0; pos<CR_MAX_CONTEXTS; pos++) 
    {
        if (client->contextList[pos])
        {
            cr_server.dispatch.DestroyContext(client->contextList[pos]);
        }
    }

    cr_server.curClient = oldclient;
}

static void crServerCleanupByPID(uint64_t pid)
{
    CRClientNode *pNode=cr_server.pCleanupClient, *pNext;

    while (pNode)
    {
        if (pNode->pClient->pid==pid)
        {
            crServerCleanupClient(pNode->pClient);
            crFree(pNode->pClient);
            if (pNode->prev)
            {
                pNode->prev->next=pNode->next;
            }
            else
            {
                cr_server.pCleanupClient=pNode->next;
            }
            if (pNode->next)
            {
                pNode->next->prev = pNode->prev;
            }

            pNext=pNode->next;
            crFree(pNode);
            pNode=pNext;
        }
        else
        {
            pNode=pNode->next;
        }
    }
}

void
crServerDeleteClient( CRClient *client )
{
    int i, j;
    int cleanup=1;

#if 0
    if (crNetNumMessages(client->conn) > 0) {
        crDebug("Delay destroying client: message still pending");
        return;
    }
#endif

    if (!FindClientInQueue(client)) {
        /* this should never happen */
        crError("CRServer: client %p not found in the queue!", client);
    }

    /* remove from clients[] array */
    for (i = 0; i < cr_server.numClients; i++) {
        if (cr_server.clients[i] == client) {
            /* found it */
            for (j = i; j < cr_server.numClients - 1; j++)
                cr_server.clients[j] = cr_server.clients[j + 1];
            cr_server.numClients--;
            break;
        }
    }

    /* check if there're any other guest threads in same process */
    for (i=0; i < cr_server.numClients; i++)
    {
        if (cr_server.clients[i]->pid==client->pid)
        {
            cleanup=0;
            break;
        }
    }

    if (cleanup)
    {
        crServerCleanupClient(client);
    }

    /* remove from the run queue */
    if (cr_server.run_queue)
    {
        RunQueue *q = cr_server.run_queue;
        RunQueue *qStart = cr_server.run_queue; 
        do {
            if (q->client == client)
            {
                /* this test seems a bit excessive */
                if ((q->next == q->prev) && (q->next == q) && (cr_server.run_queue == q))
                {
                    /* We're removing/deleting the only client */
                    CRASSERT(cr_server.numClients == 0);
                    crFree(q);
                    cr_server.run_queue = NULL;
                    cr_server.curClient = NULL;
                    crDebug("[%d]Last client deleted - empty run queue.", getpid());
					//CloseThreadSocket();
                    CleanupPixlesList();
                    CleanupLeftPixels();
                } 
                else
                {
                    /* remove from doubly linked list and free the node */
                    if (cr_server.curClient == q->client)
                        cr_server.curClient = NULL;
                    if (cr_server.run_queue == q)
                        cr_server.run_queue = q->next;
                    q->prev->next = q->next;
                    q->next->prev = q->prev;
                    crFree(q);
                }
                break;
            }
            q = q->next;
        } while (q != qStart);
    }
    
    
    crDebug("[%d]stone go to free client conn\n", getpid());
    

    crNetFreeConnection(client->conn);
    //crDebug("stone end of  free client conn set the connon be NULL\n");
    client->conn = NULL;
    //crDebug("stone end of set the connon be NULL \n");
    /*
    crDebug("stone go to close the socket Deleting client %p pid:%lu tpip:%llu socke3D:%d sendTheard:%d Termiip:%s\n", 
            client, client->pid,
            Terminal_pid,sockfd_3D,send_thread,Terminal_ip);
            */
    /* close the 3D termiral socket */
    /*if (Terminal_pid && client->pid == Terminal_pid)
    {
        int spuwindow = 0;
        if(client->currentMural){
        	spuwindow = client->currentMural->spuWindow;
        }
		CloseThreadSocket(spuwindow);
    }*/
    crDebug("[%d]stone  cleanup:%d \n",getpid(), cleanup);

    if (cleanup)
    {
        crServerCleanupByPID(client->pid);
        crFree(client);
    }
    else
    {
        CRClientNode *pNode = (CRClientNode *)crAlloc(sizeof(CRClientNode));
        if (!pNode)
        {
            crWarning("Not enough memory, forcing client cleanup");
            crServerCleanupClient(client);
            crServerCleanupByPID(client->pid);
            crFree(client);
            return;
        }
        pNode->pClient = client;
        pNode->prev = NULL;
        pNode->next = cr_server.pCleanupClient;
        cr_server.pCleanupClient = pNode;
    }

    if (!cr_server.numClients)
    {
        /* if no clients, the guest driver may be unloaded,
         * and thus the visible regions situation might not be under control anymore,
         * so cleanup the 3D framebuffer data here
         * @todo: what really should happen is that guest driver on unload
         * posts some request to host that would copy the current framebuffer 3D data to the 2D buffer
         * (i.e. to the memory used by the standard IFramebuffer API) */
        HCR_FRAMEBUFFER hFb;
        for (hFb = CrPMgrFbGetFirstEnabled(); hFb; hFb = CrPMgrFbGetNextEnabled(hFb))
        {
            int rc = CrFbUpdateBegin(hFb);
            if (RT_SUCCESS(rc))
            {
                CrFbRegionsClear(hFb);
                CrFbUpdateEnd(hFb);
            }
            else
                WARN(("CrFbUpdateBegin failed %d", rc));
        }
    }
}

/**
 * Test if the given client is in the middle of a glBegin/End or
 * glNewList/EndList pair.
 * This is used to test if we can advance to the next client.
 * \return GL_TRUE if so, GL_FALSE otherwise.
 */
GLboolean
crServerClientInBeginEnd(const CRClient *client)
{
    if (client->currentCtxInfo
            && client->currentCtxInfo->pContext
            && (client->currentCtxInfo->pContext->lists.currentIndex != 0 ||
             client->currentCtxInfo->pContext->current.inBeginEnd ||
             client->currentCtxInfo->pContext->occlusion.currentQueryObject)) {
        return GL_TRUE;
    }
    else {
        return GL_FALSE;
    }
}

bool Is_End()
{
    RunQueue *tmp = cr_server.run_queue;
	bool n = false;
	while(!n || tmp != cr_server.run_queue){
        n = true;
		if (crNetNumMessages(tmp->client->conn) > 0){
			crDebug("[%d]stone call end() end this conext!! ", getpid());
            return true; 
		}else{
		    tmp = tmp->next;
		}
	}
	return false;
}
/**
 * Find the next client in the run queue that's not blocked and has a
 * waiting message.
 * Check if all clients are blocked (on barriers, semaphores), if so we've
 * deadlocked!
 * If no clients have a waiting message, call crNetRecv to get something
 * if 'block' is true, else return NULL if 'block' if false.
 */
static RunQueue *
getNextClient(GLboolean block)
{
    while (1)
    {
        if (cr_server.run_queue) 
        {
            GLboolean all_blocked = GL_TRUE;
            GLboolean done_something = GL_FALSE;
            RunQueue *start = cr_server.run_queue;

            /* check if this client's connection has gone away */
            if (!cr_server.run_queue->client->conn
                || (cr_server.run_queue->client->conn->type == CR_NO_CONNECTION
                    && crNetNumMessages(cr_server.run_queue->client->conn) == 0)) 
            {
                crServerDeleteClient( cr_server.run_queue->client );
                start = cr_server.run_queue;
            }
 
            if (cr_server.run_queue == NULL) {
                /* empty queue */
                return NULL;
            }

            if (crServerClientInBeginEnd(cr_server.run_queue->client)) {
                /* We _must_ service this client and no other.
                 * If we've got a message waiting on this client's connection we'll
                 * service it.  Else, return NULL.
                 */
                if (crNetNumMessages(cr_server.run_queue->client->conn) > 0){
                    return cr_server.run_queue;
                }else{
                    //add by szk (fix  some model cause 3DMax blow up)
                    if(Is_End()){
                        cr_server.dispatch.End();
                    }
                    return NULL;
                }
            }

            /* loop over entries in run queue, looking for next one that's ready */
            while (!done_something || cr_server.run_queue != start)
            {
                done_something = GL_TRUE;
                if (!cr_server.run_queue->blocked)
                {
                    all_blocked = GL_FALSE;
                }
                if (!cr_server.run_queue->blocked
                        && cr_server.run_queue->client->conn
                        && crNetNumMessages(cr_server.run_queue->client->conn) > 0)
                {
                    /* OK, this client isn't blocked and has a queued message */
                    return cr_server.run_queue;
                }

                // QH: clean the dead connection in run_queue
                if (!cr_server.run_queue->client->conn ||
                     cr_server.run_queue->client->conn->type == CR_NO_CONNECTION)
                {
                    if (cr_server.run_queue == start)
                        done_something = GL_FALSE;
                    
                    crServerDeleteClient(cr_server.run_queue->client);

                    if (!done_something)
                        start = cr_server.run_queue;
                }
                
                if (cr_server.run_queue == NULL){
                    break;
                }
                
                cr_server.run_queue = cr_server.run_queue->next;
            }

            if (all_blocked)
            {
                 /* XXX crError is fatal?  Should this be an info/warning msg? */
                crError( "crserver: DEADLOCK! (numClients=%d, all blocked)",
                                 cr_server.numClients );
                if (cr_server.numClients < (int) cr_server.maxBarrierCount) {
                    crError("Waiting for more clients!!!");
                    while (cr_server.numClients < (int) cr_server.maxBarrierCount) {
                        crNetRecv();
                    }
                }
            }
        }

        if (!block){
             return NULL;
        }

        /* no one had any work, get some! */
        crNetRecv();

    } /* while */

    /* UNREACHED */
    /* return NULL; */
}

typedef struct CR_SERVER_PENDING_MSG
{
    RTLISTNODE Node;
    uint32_t cbMsg;
    CRMessage Msg;
} CR_SERVER_PENDING_MSG;

static int crServerPendMsg(CRConnection *conn, const CRMessage *msg, int cbMsg)
{
    CR_SERVER_PENDING_MSG *pMsg;

    if (!cbMsg)
    {
        WARN(("cbMsg is null!"));
        return VERR_INVALID_PARAMETER;
    }

    pMsg = (CR_SERVER_PENDING_MSG*)RTMemAlloc(cbMsg + RT_OFFSETOF(CR_SERVER_PENDING_MSG, Msg));
    if (!pMsg)
    {
        WARN(("RTMemAlloc failed"));
        return VERR_NO_MEMORY;
    }

    pMsg->cbMsg = cbMsg;

    memcpy(&pMsg->Msg, msg, cbMsg);

    RTListAppend(&conn->PendingMsgList, &pMsg->Node);

    return VINF_SUCCESS;
}

/*int crServerPendSaveState(PSSMHANDLE pSSM)
{
    int i, rc;

    for (i = 0; i < cr_server.numClients; i++)
    {
        CR_SERVER_PENDING_MSG *pIter;
        CRClient *pClient = cr_server.clients[i];
        CRConnection *pConn;
        if (!pClient || !pClient->conn)
        {
            WARN(("invalid client state"));
            continue;
        }

        pConn = pClient->conn;

        if (RTListIsEmpty(&pConn->PendingMsgList))
            continue;

        CRASSERT(pConn->u32ClientID);

        rc = SSMR3PutU32(pSSM, pConn->u32ClientID);
        AssertRCReturn(rc, rc);

        RTListForEach(&pConn->PendingMsgList, pIter, CR_SERVER_PENDING_MSG, Node)
        {
            CRASSERT(pIter->cbMsg);

            rc = SSMR3PutU32(pSSM, pIter->cbMsg);
            AssertRCReturn(rc, rc);

            rc = SSMR3PutMem(pSSM, &pIter->Msg, pIter->cbMsg);
            AssertRCReturn(rc, rc);
        }

        rc = SSMR3PutU32(pSSM, 0);
        AssertRCReturn(rc, rc);
    }

    rc = SSMR3PutU32(pSSM, 0);
    AssertRCReturn(rc, rc);

    return VINF_SUCCESS;
}*/

/*int crServerPendLoadState(PSSMHANDLE pSSM, uint32_t u32Version)
{
    int rc;
    uint32_t u32;
    CRClient *pClient;

    if (u32Version < SHCROGL_SSM_VERSION_WITH_PEND_CMD_INFO)
        return VINF_SUCCESS;

    rc = SSMR3GetU32(pSSM, &u32);
    AssertRCReturn(rc, rc);

    if (!u32)
        return VINF_SUCCESS;

    do {
        rc = crVBoxServerClientGet(u32, &pClient);
        AssertRCReturn(rc, rc);

        for(;;)
        {
            CR_SERVER_PENDING_MSG *pMsg;

            rc = SSMR3GetU32(pSSM, &u32);
            AssertRCReturn(rc, rc);

            if (!u32)
                break;

            pMsg = (CR_SERVER_PENDING_MSG*)RTMemAlloc(u32 + RT_OFFSETOF(CR_SERVER_PENDING_MSG, Msg));
            if (!pMsg)
            {
                WARN(("RTMemAlloc failed"));
                return VERR_NO_MEMORY;
            }

            pMsg->cbMsg = u32;
            rc = SSMR3GetMem(pSSM, &pMsg->Msg, u32);
            AssertRCReturn(rc, rc);

            RTListAppend(&pClient->conn->PendingMsgList, &pMsg->Node);
        }

        rc = SSMR3GetU32(pSSM, &u32);
        AssertRCReturn(rc, rc);
    } while (u32);

    rc = SSMR3GetU32(pSSM, &u32);
    AssertRCReturn(rc, rc);

    return VINF_SUCCESS;
}*/

static void crServerPendProcess(CRConnection *conn)
{
    CR_SERVER_PENDING_MSG *pIter, *pNext;

    cr_server.fProcessingPendedCommands = GL_TRUE;

    RTListForEachSafe(&conn->PendingMsgList, pIter, pNext, CR_SERVER_PENDING_MSG, Node)
    {
        CRMessage *msg = &pIter->Msg;
        const CRMessageOpcodes *msg_opcodes;
        int opcodeBytes;
        const char *data_ptr;

        RTListNodeRemove(&pIter->Node);

        CRASSERT(msg->header.type == CR_MESSAGE_OPCODES);

        msg_opcodes = (const CRMessageOpcodes *) msg;
        opcodeBytes = (msg_opcodes->numOpcodes + 3) & ~0x03;

        data_ptr = (const char *) msg_opcodes + sizeof (CRMessageOpcodes) + opcodeBytes;

        crUnpack(data_ptr,                 /* first command's operands */
                 data_ptr - 1,             /* first command's opcode */
                 msg_opcodes->numOpcodes,  /* how many opcodes */
                 &(cr_server.dispatch));   /* the CR dispatch table */

        RTMemFree(pIter);
    }

    cr_server.fProcessingPendedCommands = GL_FALSE;
}

/**
 * This function takes the given message (which should be a buffer of
 * rendering commands) and executes it.
 */
static void
crServerDispatchMessage(CRConnection *conn, CRMessage *msg, int cbMsg)
{
    const CRMessageOpcodes *msg_opcodes;
    int opcodeBytes;
    const char *data_ptr;
#ifdef VBOX_WITH_CRHGSMI
    PCRVBOXHGSMI_CMDDATA pCmdData = NULL;
#endif
    CR_UNPACK_BUFFER_TYPE enmType;
    bool fUnpack = true;

    if (msg->header.type == CR_MESSAGE_REDIR_PTR)
    {
#ifdef VBOX_WITH_CRHGSMI
        pCmdData = &msg->redirptr.CmdData;
#endif
        msg = (CRMessage *) msg->redirptr.pMessage;
    }

    CRASSERT(msg->header.type == CR_MESSAGE_OPCODES);

    msg_opcodes = (const CRMessageOpcodes *) msg;
    opcodeBytes = (msg_opcodes->numOpcodes + 3) & ~0x03;

#ifdef VBOXCR_LOGFPS
    CRASSERT(cr_server.curClient && cr_server.curClient->conn && cr_server.curClient->conn->id == msg->header.conn_id);
    cr_server.curClient->conn->opcodes_count += msg_opcodes->numOpcodes;
#endif

    data_ptr = (const char *) msg_opcodes + sizeof(CRMessageOpcodes) + opcodeBytes;

    enmType = crUnpackGetBufferType(data_ptr - 1,             /* first command's opcode */
                msg_opcodes->numOpcodes  /* how many opcodes */);
    switch (enmType)
    {
        case CR_UNPACK_BUFFER_TYPE_GENERIC:
        {
            if (RTListIsEmpty(&conn->PendingMsgList))
                break;

            if (RT_SUCCESS(crServerPendMsg(conn, msg, cbMsg)))
            {
                fUnpack = false;
                break;
            }

            WARN(("crServerPendMsg failed"));
            crServerPendProcess(conn);
            break;
        }
        case CR_UNPACK_BUFFER_TYPE_CMDBLOCK_BEGIN:
        {
            if (RTListIsEmpty(&conn->PendingMsgList))
            {
                if (RT_SUCCESS(crServerPendMsg(conn, msg, cbMsg)))
                {
                    Assert(!RTListIsEmpty(&conn->PendingMsgList));
                    fUnpack = false;
                    break;
                }
                else
                    WARN(("crServerPendMsg failed"));
            }
            else
                WARN(("Pend List is NOT empty, drain the current list, and ignore this command"));

            crServerPendProcess(conn);
            break;
        }
        case CR_UNPACK_BUFFER_TYPE_CMDBLOCK_FLUSH: /* just flush for now */
        {
            CrPMgrClearRegionsGlobal(); /* clear regions to ensure we don't do MakeCurrent and friends */
            crServerPendProcess(conn);
            Assert(RTListIsEmpty(&conn->PendingMsgList));
            break;
        }
        case CR_UNPACK_BUFFER_TYPE_CMDBLOCK_END:
        {
            CRASSERT(!RTListIsEmpty(&conn->PendingMsgList));
            crServerPendProcess(conn);
            Assert(RTListIsEmpty(&conn->PendingMsgList));
            break;
        }
        default:
            WARN(("unsupported buffer type"));
            break;
    }

    if (fUnpack)
    {
        crUnpack(data_ptr,                 /* first command's operands */
                 data_ptr - 1,             /* first command's opcode */
                 msg_opcodes->numOpcodes,  /* how many opcodes */
                 &(cr_server.dispatch));   /* the CR dispatch table */
    }

#ifdef VBOX_WITH_CRHGSMI
    if (pCmdData)
    {
        int rc = VINF_SUCCESS;
        CRVBOXHGSMI_CMDDATA_ASSERT_CONSISTENT(pCmdData);
        if (CRVBOXHGSMI_CMDDATA_IS_SETWB(pCmdData))
        {
            uint32_t cbWriteback = pCmdData->cbWriteback;
            rc = crVBoxServerInternalClientRead(conn->pClient, (uint8_t*)pCmdData->pWriteback, &cbWriteback);
            Assert(rc == VINF_SUCCESS || rc == VERR_BUFFER_OVERFLOW);
            *pCmdData->pcbWriteback = cbWriteback;
        }
        VBOXCRHGSMI_CMD_CHECK_COMPLETE(pCmdData, rc);
    }
#endif
}


/**
 * Set the clients pid
 * QH
*/
void crServerSetPid(CRClient *client, unsigned long long pid)
{
    client->pid = pid;
}


typedef enum
{
  CLIENT_GONE = 1, /* the client has disconnected */
  CLIENT_NEXT = 2, /* we can advance to next client */
  CLIENT_MORE = 3  /* we need to keep servicing current client */
} ClientStatus;


/**
 * Process incoming/pending message for the given client (queue entry).
 * \return CLIENT_GONE if this client has gone away/exited,
 *         CLIENT_NEXT if we can advance to the next client
 *         CLIENT_MORE if we have to process more messages for this client. 
 */
static ClientStatus
crServerServiceClient(const RunQueue *qEntry)
{
    CRMessage *msg;
    CRConnection *conn;
    struct sockaddr_in  * sockin;

    struct timeval tvstart,tvend;
    gettimeofday(&tvstart,NULL);
    /* set current client pointer */
    cr_server.curClient = qEntry->client;

    conn = cr_server.run_queue->client->conn;

    /* service current client as long as we can */
    while (conn && conn->type != CR_NO_CONNECTION &&
                 crNetNumMessages(conn) > 0) {
        unsigned int len;

        
        //crDebug("%d messages on %p", crNetNumMessages(conn), (void *) conn);
        

        /* Don't use GetMessage, because we want to do our own crNetRecv() calls
         * here ourself.
         * Note that crNetPeekMessage() DOES remove the message from the queue
         * if there is one.
         */
        len = crNetPeekMessage( conn, &msg );
        CRASSERT(len > 0);

        /* QH
        */
        if (msg->header.type == CR_MESSAGE_SET_PID)
        {
            CRMessageSetPid * msgSetPid = (CRMessageSetPid *)msg;
            unsigned long long pid = msgSetPid->pid;
            if (conn->swap)
            {
                #ifdef WINDOWS
                pid = 
                #endif
                SWAP64(pid);
            }
            crDebug("[%d]stone go to set Terminal_ip:%s\n", getpid(), Terminal_ip);
            sockin = (struct sockaddr_in *)(&(conn->remoteaddr));
            crDebug("[%d]stone the terminal ip is %s, PID:%llu ntohsport:%d  ntohlip:%x  port:%d ip:%x\n", 
                getpid(), ((CRMessageSetPid *)msg)->terminal_ip,((CRMessageSetPid *)msg)->pid,
                ntohs(sockin->sin_port),ntohl(sockin->sin_addr.s_addr),
                sockin->sin_port,sockin->sin_addr.s_addr);    
            memcpy(Terminal_ip, ((CRMessageSetPid *)msg)->terminal_ip, 16);
            Terminal_pid  = ((CRMessageSetPid *)msg)->pid;
            crServerSetPid(cr_server.curClient, ((CRMessageSetPid *)msg)->pid);
            crNetFree(conn, msg);
            continue;
        }
        
        if (msg->header.type != CR_MESSAGE_OPCODES
            && msg->header.type != CR_MESSAGE_REDIR_PTR) {
            crError( "SPU %d sent me CRAP (type=0x%x)",
                             cr_server.curClient->spu_id, msg->header.type );
        }

        /* Do the context switch here.  No sense in switching before we
         * really have any work to process.  This is a no-op if we're
         * not really switching contexts.
         *
         * XXX This isn't entirely sound.  The crStateMakeCurrent() call
         * will compute the state difference and dispatch it using
         * the head SPU's dispatch table.
         *
         * This is a problem if this is the first buffer coming in,
         * and the head SPU hasn't had a chance to do a MakeCurrent()
         * yet (likely because the MakeCurrent() command is in the
         * buffer itself).
         *
         * At best, in this case, the functions are no-ops, and
         * are essentially ignored by the SPU.  In the typical
         * case, things aren't too bad; if the SPU just calls
         * crState*() functions to update local state, everything
         * will work just fine.
         *
         * In the worst (but unusual) case where a nontrivial
         * SPU is at the head of a crserver's SPU chain (say,
         * in a multiple-tiered "tilesort" arrangement, as
         * seen in the "multitilesort.conf" configuration), the
         * SPU may rely on state set during the MakeCurrent() that
         * may not be present yet, because no MakeCurrent() has
         * yet been dispatched.
         *
         * This headache will have to be revisited in the future;
         * for now, SPUs that could head a crserver's SPU chain
         * will have to detect the case that their functions are
         * being called outside of a MakeCurrent(), and will have
         * to handle the situation gracefully.  (This is currently
         * the case with the "tilesort" SPU.)
         */

#if 0
        crStateMakeCurrent( cr_server.curClient->currentCtx );
#else
        /* Check if the current window is the one that the client wants to
         * draw into.  If not, dispatch a MakeCurrent to activate the proper
         * window.
         */
        if (cr_server.curClient) {
             int clientWindow = cr_server.curClient->currentWindow;
             int clientContext = cr_server.curClient->currentContextNumber;
             CRContextInfo *clientCtxInfo = cr_server.curClient->currentCtxInfo;
             if (clientCtxInfo != cr_server.currentCtxInfo
                     || clientWindow != cr_server.currentWindow
                     || cr_server.bForceMakeCurrentOnClientSwitch) {
                 //crDebug("cr_server.currentWindow %p, clientContext %p", cr_server.currentWindow, clientContext);
                 crServerDispatchMakeCurrent(clientWindow, 0, clientContext);

				 //crDebug("clientWindow %p", clientWindow);
                 CRASSERT(cr_server.currentWindow == clientWindow);
                 
             }
        }
#endif

        /* Force scissor, viewport and projection matrix update in
         * crServerSetOutputBounds().
         */
        cr_server.currentSerialNo = 0;

        /* Commands get dispatched here */
        crServerDispatchMessage( conn, msg, len );

        crNetFree( conn, msg );

        if (qEntry->blocked) {
            /* Note/assert: we should not be inside a glBegin/End or glNewList/
             * glEndList pair at this time!
             */
            CRASSERT(0);
            return CLIENT_NEXT;
        }

    } /* while */

    /*
     * Check if client/connection is gone
     */
    if (!conn || conn->type == CR_NO_CONNECTION) {
        crDebug("[%d]Delete client %p at %d in crServerServiceClient()", getpid(), cr_server.run_queue->client, __LINE__);
        crServerDeleteClient( cr_server.run_queue->client );
        return CLIENT_GONE;
    }

    /*
     * Determine if we can advance to next client.
     * If we're currently inside a glBegin/End primitive or building a display
     * list we can't service another client until we're done with the
     * primitive/list.
     */
    if (crServerClientInBeginEnd(cr_server.curClient)) {
        /* The next message has to come from the current client's connection. */
        CRASSERT(!qEntry->blocked);
        /*if((tvend.tv_usec-tvstart.tv_usec) < 0)
            crDebug("the render one time is:%d,%d",(tvend.tv_sec-tvstart.tv_sec),(tvstart.tv_usec - tvend.tv_usec)/1000);
        else
            crDebug("the render one time is:%d,%d",(tvend.tv_sec-tvstart.tv_sec),(tvend.tv_usec-tvstart.tv_usec)/1000);*/
        //crDebug("[%d]stone return CLIENT_MORE and the conn is %d", getpid(), cr_server.curClient->conn->tcp_socket); 
        return CLIENT_MORE;
    }
    else {
        /* get next client */
        return CLIENT_NEXT;
    }
}



/**
 * Check if any of the clients need servicing.
 * If so, service one client and return.
 * Else, just return.
 */
void
crServerServiceClients(void)
{
    RunQueue *q;

    q = getNextClient(GL_FALSE); /* don't block */
    while (q) 
    {
        ClientStatus stat = crServerServiceClient(q);
        if (stat == CLIENT_NEXT && cr_server.run_queue->next) {
            /* advance to next client */
            cr_server.run_queue = cr_server.run_queue->next;
        }
        q = getNextClient(GL_FALSE);
    }
}




/**
 * Main crserver loop.  Service connections from all connected clients.
 * XXX add a config option to specify whether the crserver
 * should exit when there's no more clients.
 */
int
crServerSerializeRemoteStreams(void)
{
    /*MSG msg;*/

    if (cr_server.run_queue)
    {
        crNetRecv();
        crServerServiceClients();
        /*if (PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
        {
            if (msg.message == WM_QUIT)
            {
                PostQuitMessage((int)msg.wParam);
                break;
            }
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }*/
        return 1;
    }

    return 0;
}


/**
 * This will be called by the network layer when it's received a new message.
 */
int
crServerRecv( CRConnection *conn, CRMessage *msg, unsigned int len )
{
    CRMessage *pRealMsg;
    (void) len;

    pRealMsg = (msg->header.type!=CR_MESSAGE_REDIR_PTR) ? msg : (CRMessage*) msg->redirptr.pMessage;

    switch( pRealMsg->header.type )
    {
        /* Called when using multiple threads */
        case CR_MESSAGE_NEWCLIENT:
			crDebug("[%d]%s : CR_MESSAGE_NEWCLIENT %d", getpid(), __FUNCTION__, CR_MESSAGE_NEWCLIENT);
            crServerAddNewClient();
            return 1; /* msg handled */
        default:
			//crDebug("%s : msg %x", __FUNCTION__, pRealMsg->header.type);
            //crWarning( "Why is the crserver getting a message of type 0x%x?",
                //msg->header.type ); 
            ;
    }
    return 0; /* not handled */
}
