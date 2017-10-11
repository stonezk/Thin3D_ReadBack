/* Copyright (c) 2001, Stanford University
 * All rights reserved
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

#include "cr_spu.h"
#include "chromium.h"
#include "cr_mem.h"
#include "cr_net.h"
#include "server_dispatch.h"
#include "server.h"
#include "cr_unpack.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include "cr_error.h"

#include <stdlib.h>
//#include <snappy-c.h>
#include <errno.h>
#include <jpeglib.h>
#include <jerror.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#define VBOXCR_LOGFPS
#ifdef VBOXCR_LOGFPS
#include <iprt/timer.h>
#include <iprt/ctype.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define G_TEST_USLEEP_TIME  5000         /*sleep 5000us */
#define G_TEST_HIGH_WATER  50         /*hight water Mbps */
#define G_TEST_LOW_WATER  30         /*LOW water Mbps */
#define G_TEST_SLEEP_HIGH  8         /*OVER HIGH water SLEEP  G_TEST_SLEEP_HIGH*G_TEST_USLEEP_TIME*/
#define G_TEST_SLEEP_LOW  3         /*OVER LOW water SLEEP  G_TEST_SLEEP_HIGH*G_TEST_USLEEP_TIME */
#define G_TEST_WATER_CHECK  10         /*CHECK THE FPS INTERVEL */


extern int errno;
extern char Terminal_ip[];
int sockfd_3D = -1;
int sockfd_Rect = -1;
int node_num = 0;
int Flag_Image = 1;
int terminal_disconnect = 0;
int terminal_connect = 0;
int g_sleep_count = 0;
int g_send_buffer = 1;
uint16_t d3dServerPort = 0;
uint16_t d3dRectPort = 0;
unsigned int image_compression = 85;

Pixel_list * list_tmp = NULL;
Pixel_list * list_head = NULL;

ThreadStatus Pixel_Thread_Status = THREAD_UNEXIST;
ThreadStatus Rect_Thread_Status = THREAD_UNEXIST;

pthread_t pixel_id;
pthread_t rect_id;
pthread_mutex_t send_mutex;
pthread_cond_t pthread_count_cv;
static pthread_mutex_t thread_socket_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pthread_count_rect;
pthread_mutex_t last_pixel_mutex = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t mutex_Rect_3D;

Last_Pixel_Info last_pixel[16] = {0};

//add end

typedef struct VBOXCRFPS
{
    uint64_t mPeriodSum;
    uint64_t *mpaPeriods;
    uint64_t mPrevTime;
    uint64_t mcFrames;
    uint32_t mcPeriods;
    uint32_t miPeriod;

    uint64_t mBytesSum;
    uint32_t *mpaBytes;

    uint64_t mBytesSentSum;
    uint32_t *mpaBytesSent;

    uint64_t mCallsSum;
    uint32_t *mpaCalls;

    uint64_t mOpsSum;
    uint32_t *mpaOps;

    uint64_t mTimeUsedSum;
    uint64_t *mpaTimes;
} VBOXCRFPS, *PVBOXCRFPS;

void vboxCrFpsInit(PVBOXCRFPS pFps, uint32_t cPeriods)
{
    crMemset(pFps, 0, sizeof (*pFps));
    pFps->mcPeriods = cPeriods;
    pFps->mpaPeriods = crCalloc(sizeof (pFps->mpaPeriods[0]) * cPeriods);
    pFps->mpaBytes = crCalloc(sizeof (pFps->mpaBytes[0]) * cPeriods);
    pFps->mpaBytesSent = crCalloc(sizeof (pFps->mpaBytesSent[0]) * cPeriods);
    pFps->mpaCalls = crCalloc(sizeof (pFps->mpaCalls[0]) * cPeriods);
    pFps->mpaOps = crCalloc(sizeof (pFps->mpaOps[0]) * cPeriods);
    pFps->mpaTimes = crCalloc(sizeof (pFps->mpaTimes[0]) * cPeriods);
}

void vboxCrFpsTerm(PVBOXCRFPS pFps)
{
    crFree(pFps->mpaPeriods);
    crFree(pFps->mpaBytes);
    crFree(pFps->mpaCalls);
}

void vboxCrFpsReportFrame(PVBOXCRFPS pFps)
{
    uint64_t cur = RTTimeNanoTS();
    uint64_t curBytes, curBytesSent, curCalls, curOps, curTimeUsed;
    int i;

    curBytes = 0;
    curBytesSent = 0;
    curCalls = 0;
    curOps = 0;
    curTimeUsed = 0;

    for (i = 0; i < cr_server.numClients; i++)
    {
        if (cr_server.clients[i] && cr_server.clients[i]->conn)
        {
            curBytes += cr_server.clients[i]->conn->total_bytes_recv;
            curBytesSent += cr_server.clients[i]->conn->total_bytes_sent;
            curCalls += cr_server.clients[i]->conn->recv_count;
            curOps += cr_server.clients[i]->conn->opcodes_count;
            curTimeUsed += cr_server.clients[i]->timeUsed;
            cr_server.clients[i]->conn->total_bytes_recv = 0;
            cr_server.clients[i]->conn->total_bytes_sent = 0;
            cr_server.clients[i]->conn->recv_count = 0;
            cr_server.clients[i]->conn->opcodes_count = 0;
            cr_server.clients[i]->timeUsed = 0;
        }
    }

    if(pFps->mPrevTime)
    {
        uint64_t curPeriod = cur - pFps->mPrevTime;

        pFps->mPeriodSum += curPeriod - pFps->mpaPeriods[pFps->miPeriod];
        pFps->mpaPeriods[pFps->miPeriod] = curPeriod;

        pFps->mBytesSum += curBytes - pFps->mpaBytes[pFps->miPeriod];
        pFps->mpaBytes[pFps->miPeriod] = curBytes;

        pFps->mBytesSentSum += curBytesSent - pFps->mpaBytesSent[pFps->miPeriod];
        pFps->mpaBytesSent[pFps->miPeriod] = curBytesSent;

        pFps->mCallsSum += curCalls - pFps->mpaCalls[pFps->miPeriod];
        pFps->mpaCalls[pFps->miPeriod] = curCalls;

        pFps->mOpsSum += curOps - pFps->mpaOps[pFps->miPeriod];
        pFps->mpaOps[pFps->miPeriod] = curOps;

        pFps->mTimeUsedSum += curTimeUsed - pFps->mpaTimes[pFps->miPeriod];
        pFps->mpaTimes[pFps->miPeriod] = curTimeUsed;

        ++pFps->miPeriod;
        pFps->miPeriod %= pFps->mcPeriods;
    }
    pFps->mPrevTime = cur;
    ++pFps->mcFrames;
}

uint64_t vboxCrFpsGetEveragePeriod(PVBOXCRFPS pFps)
{
    return pFps->mPeriodSum / pFps->mcPeriods;
}

double vboxCrFpsGetFps(PVBOXCRFPS pFps)
{
    return ((double)1000000000.0) / vboxCrFpsGetEveragePeriod(pFps);
}

double vboxCrFpsGetBps(PVBOXCRFPS pFps)
{
    return vboxCrFpsGetFps(pFps) * pFps->mBytesSum / pFps->mcPeriods;
}

double vboxCrFpsGetBpsSent(PVBOXCRFPS pFps)
{
    return vboxCrFpsGetFps(pFps) * pFps->mBytesSentSum / pFps->mcPeriods;
}

double vboxCrFpsGetCps(PVBOXCRFPS pFps)
{
    return vboxCrFpsGetFps(pFps) * pFps->mCallsSum / pFps->mcPeriods;
}

double vboxCrFpsGetOps(PVBOXCRFPS pFps)
{
    return vboxCrFpsGetFps(pFps) * pFps->mOpsSum / pFps->mcPeriods;
}

double vboxCrFpsGetTimeProcPercent(PVBOXCRFPS pFps)
{
    return 100.0*pFps->mTimeUsedSum/pFps->mPeriodSum;
}

uint64_t vboxCrFpsGetNumFrames(PVBOXCRFPS pFps)
{
    return pFps->mcFrames;
}

#endif


void SERVER_DISPATCH_APIENTRY crServerDispatchClear( GLenum mask )
{
	CRMuralInfo *mural = cr_server.curClient->currentMural;
	const RunQueue *q = cr_server.run_queue;

	if (cr_server.only_swap_once)
	{
		/* NOTE: we only do the clear for the _last_ client in the list.
		 * This is because in multi-threaded apps the zeroeth client may
		 * be idle and never call glClear at all.  See threadtest.c
		 * It's pretty likely that the last client will be active.
		 */
		if ((mask & GL_COLOR_BUFFER_BIT) &&
			(cr_server.curClient != cr_server.clients[cr_server.numClients - 1]))
		   return;
	}

	cr_server.head_spu->dispatch_table.Clear( mask );
}

static void __draw_poly(CRPoly *p)
{
	int b;

	cr_server.head_spu->dispatch_table.Begin(GL_POLYGON);
	for (b=0; b<p->npoints; b++)
		cr_server.head_spu->dispatch_table.Vertex2dv(p->points+2*b);
	cr_server.head_spu->dispatch_table.End();
}



int compress_jpeg(void *img, int width, int height, int rand)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    int row_stride;
    char *pbuf = NULL;
    int jpeg_len = 0;
    char filename[16];
    FILE *f;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    //jpeg_mem_dest(&cinfo, &pbuf, &jpeg_len);
    sprintf(filename, "stone%d.jpg", rand);
    f = fopen(filename, "wb");
    if(f == NULL){
        crDebug("stone open file failed!!!");
        return 0;
}
    jpeg_stdio_dest(&cinfo,f);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 4;
    cinfo.in_color_space = JCS_EXT_BGRA;
    //cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, image_compression, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    while(cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose( f );
   /* memcpy(com_buf, pbuf, jpeg_len);
    if(pbuf)
        free(pbuf);
    return jpeg_len;*/
    //crDebug("stone jpeg compress success!!");
    return 0;
}



#define dis3DcrDebug( fmt... )\
{\
    printf("yy debug [%d] %s  %d  \n",getpid(),__FUNCTION__,__LINE__);\
    printf(fmt);\
}


void CleanupPixlesList()
{
	Pixel_list *node_used = NULL;
    pthread_mutex_lock(&send_mutex);
    while(list_head)
    {
        if (list_head->info.buf)
        {
            dis3DFree(list_head->info.buf);
        }
        node_used = list_head;
        list_head = list_head->next;
        node_num --;
		dis3DFree(node_used);
    }
    pthread_mutex_unlock(&send_mutex);
    return ;
}

void CleanupLeftPixels()
{
    int i = 0;
    Last_Pixel_Info *pixel_info = NULL;
    for ( i= 0;i < 16 ;i ++)
    {
    pthread_mutex_lock(&last_pixel_mutex);
	 pixel_info = &(last_pixel[i]);
	if(pixel_info){
		dis3DFree(pixel_info->image);
		dis3DFree(pixel_info->info);
		pixel_info->window = 0;
		crDebug("[%d]##Free Left Pixel:%d", getpid(), i);
	}
	pthread_mutex_unlock(&last_pixel_mutex);
    }
    return ;

}

DECLCALLBACK(int) Set_Image_Compression_Grade(int grade)
{
	if(grade > 3){
		image_compression = 95;
		crDebug("##Set Jpeg Compression Grade is High(%d)", image_compression);
	}else{
		image_compression = 85;
		crDebug("##Set Jpeg Compression Grade is medium(%d)", image_compression);
	}
    return 0;
}


DECLCALLBACK(int) Terminal_Disconnect( )
{
    terminal_connect =0;
    terminal_disconnect = 1;
    
    pthread_mutex_lock(&send_mutex);
    if( sockfd_3D > 0 &&  Pixel_Thread_Status == THREAD_ACTIVE)
    {
        Pixel_Thread_Status = THREAD_NEED_CLOSE;
        pthread_cond_signal(&pthread_count_cv);
    }else{
		crDebug("[%d]##Pixel Thread Status Abnormal When Terminal Disconnecting##", getpid());
    }
    pthread_mutex_unlock(&send_mutex);

    
    pthread_mutex_lock(&mutex_Rect_3D);
    if( sockfd_Rect > 0 && Rect_Thread_Status == THREAD_ACTIVE)
    {
        Rect_Thread_Status = THREAD_NEED_CLOSE;
        pthread_cond_signal(&pthread_count_rect);

    }
    pthread_mutex_unlock(&mutex_Rect_3D);
    return 0;
}

DECLCALLBACK(int) Terminal_Connect( )
{
    //terminal_disconnect = 0;
    terminal_connect = 1;
    dis3DcrDebug("Terminal_Connect:%d \n",terminal_connect);
    //crServerSendPixesInit();
    return 0;
    
    
}

bool Pixel_Is_Full_Black(unsigned char *image, int width, int height)
{
	int i = 0, j = 0;
	unsigned char *pixel = image;

	width = MIN(width, 10);
	height = MIN(height, 10);
 
	for(i = 0; i < height; i ++){
		for(j = 0; j < width * 4; j ++){
			if(*pixel != 0){
				crDebug("##Test The Pixel isn't full black##");
				return false;
			}
			pixel = pixel + j + i * width * 4;
		}
	}
	return true;
}

typedef void *(*fn_get_ram_ptr)(uint64_t);

static fn_get_ram_ptr fn_qemu_get_ram_ptr = NULL; //qemu_get_ram_ptr

DECLCALLBACK(int) crSetGetRamPtrFunction(fn_get_ram_ptr fn)
{
	crDebug("#zr# : Enter SetCRFunction set func: %p -\n", fn);

	fn_qemu_get_ram_ptr = fn;
	
	return 0;
}

void * GetHwAddrPtr(uint64_t hw_addr)
{
	if (fn_qemu_get_ram_ptr == NULL)
		return NULL;

	return fn_qemu_get_ram_ptr(hw_addr);
}

static bool hasLast = false;
static struct timeval lastCalcTime;
static int64_t renderTime=0;
static int 	renderCount = 0;

static int64_t TimeDiff(struct timeval *p1, struct timeval *p2)
{
	int sec = p2->tv_sec - p1->tv_sec;
	int us = p2->tv_usec - p1->tv_usec;

	return (int64_t)(sec * 1000000) + (int64_t)us;
}

static void CalcRenderTime(int64_t delta)
{
	struct timeval nowTime;
	int64_t diff;
	
	if (!hasLast) {
		hasLast = true;
		gettimeofday(&lastCalcTime, NULL);
		return;
	}

	crDebug("#zr# : CR-CalcRenderTime delta is %llx, count %d\n", delta, renderCount);
	
	gettimeofday(&nowTime, NULL);

	renderTime += delta;
	renderCount++;

	diff = TimeDiff(&lastCalcTime, &nowTime) ;
	if (diff >= 1000000) {
		float t = (float)(renderTime) / 1000000.0f;
		float d = (float)(diff) / 1000000.0f;
		crDebug("#zr## : ----- CR-RenderTime(%f s) is %f, count %d\n", d, t, renderCount);
		
		lastCalcTime = nowTime;
		renderTime = 0;
		renderCount = 0;
	}
}

void Read_Pixels(CRMuralInfo *mural, uint64_t hw_addr)
{
    unsigned char *data_buf = NULL;
    GLint viewport[4];
	int view_x, view_y, view_width, view_height;
    struct timeval tvstart, tvend;
	Rect_Queue *rect_node = NULL;

	//crDebug("#zr# : Enter Read_Pixels -\n");
	
	data_buf = (unsigned char *)GetHwAddrPtr(hw_addr);

	crDebug("#zr# : Read_Pixels %llx, buff: %p\n", hw_addr, data_buf);


    if(node_num > 10){
		crDebug("[%d]##Pixel_List length Beyong 10 And Discard This Pixel And Thread Status:%d",
			getpid(), Pixel_Thread_Status);
		return;
    }
	glGetIntegerv(GL_VIEWPORT, viewport);
    view_x = viewport[0];
    view_y = viewport[1];
    view_width= viewport[2];
    view_height= viewport[3];

	if(view_width> 0 && view_height> 0){
		
		//data_buf = (unsigned char *)malloc(mural->width  * mural->height* 4 + 4);

        if ( NULL == data_buf )
        {
            crDebug("[%d]stone %s malloc data buf error!\n", getpid(), __FUNCTION__);
            return;
        }

		*((int *)(data_buf)) = mural->width;
		*((int *)(data_buf+4)) = mural->height;
		
		gettimeofday(&tvstart, NULL);
        glReadPixels(0, 0, mural->width, mural->height, GL_BGRA, GL_UNSIGNED_BYTE,data_buf + 8);
		gettimeofday(&tvend, NULL);

		CalcRenderTime(TimeDiff(&tvstart, &tvend));

	}
}

int crServerGetRenderingFps()
{
    static VBOXCRFPS Fps;
    static bool bFpsInited = false;
    
    if (!bFpsInited)
    {
      vboxCrFpsInit(&Fps, 64 /* cPeriods */);
      bFpsInited = true;
    }
    vboxCrFpsReportFrame(&Fps);

    if (!(vboxCrFpsGetNumFrames(&Fps) % G_TEST_WATER_CHECK))
    {
        double curfps = vboxCrFpsGetFps(&Fps);
        double curbps = vboxCrFpsGetBps(&Fps);
        double  curMbps =  curbps/(1024*1024);
        if (G_TEST_HIGH_WATER < curfps)
        {
            g_sleep_count = G_TEST_SLEEP_HIGH; 
        }
        else if(G_TEST_LOW_WATER < curfps )
        {
            g_sleep_count = G_TEST_SLEEP_LOW; 
        }
        else
        {
            g_sleep_count = 0;
        }
        crDebug("[%d]stone yy fps: %f, rec Mbps: %.1f, g_sleep_count:%d !\n", 
              getpid(), curfps, curMbps,g_sleep_count);
    }

}

#define crServerRenderingDelay(){\
    int j;\
    for(j = g_sleep_count;j>0;j--)\
    {\
        usleep(G_TEST_USLEEP_TIME);\
    }\
}

int  crServerPixelsProcess(CRMuralInfo *mural, uint64_t hw_addr)
{
    if (!terminal_connect){
        g_sleep_count = G_TEST_SLEEP_HIGH;
    }else{
        crServerGetRenderingFps();
    }
    
    if (terminal_connect && sockfd_3D > 0 && Pixel_Thread_Status == THREAD_ACTIVE)
    {
        Read_Pixels(mural, hw_addr);
    }else{
		crDebug("[%d]Error:Status Abnormal terminal_connect:%d, sockfd_3D:%d, Thread_Status:%d",
			getpid(), terminal_connect, sockfd_3D, Pixel_Thread_Status);
    }
}


static void socketInitKeepalive(int socket)
{
    if (socket < 0)
        return;
    
    int keepalive = 1;
    int keepidle = 10;      // 如该连接在60秒内没有任何数据往来,则进行探测
    int keepinterval = 10;   // 探测时发包的时间间隔为10 秒
    int keepcount = 6;      // 探测尝试的次数.如果第1次探测包就收到响应了,则后5次的不再发.

    if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, 
        (void *)&keepalive , sizeof(keepalive)) == -1) {
        dis3DcrDebug("keepalive setsockopt failed, %s", strerror(errno));
    }

    if (setsockopt(socket, SOL_TCP, TCP_KEEPIDLE, 
        (void *)&keepidle , sizeof(keepidle)) == -1) {
        dis3DcrDebug("keepidle setsockopt failed, %s", strerror(errno));
    }

    if (setsockopt(socket, SOL_TCP, TCP_KEEPINTVL, 
        (void *)&keepinterval , sizeof(keepinterval)) == -1) {
        dis3DcrDebug("keepintvl setsockopt failed, %s", strerror(errno));
    }

    if (setsockopt(socket, SOL_TCP, TCP_KEEPCNT, 
        (void *)&keepcount , sizeof(keepcount)) == -1) {
        dis3DcrDebug("keepcnt setsockopt failed, %s", strerror(errno));
    }

}

void crSendMuxInit()
{
    //yy  debug  the read pixels before
    static bool m = 1;
    if(m){
        pthread_mutex_init(&send_mutex, NULL);
        pthread_cond_init(&pthread_count_cv, NULL);
        m = 0;
    }
}


/* @brief 获取可用的端口
 *
 * @param port : 输出，返回可用的端口号
 *
 * @return 若成功则返回true，否则放回false
 */
bool getAvaliablePort(unsigned short * port)
{
    bool result = true;
    struct sockaddr_in addr;
    int  sock = -1;
    int  ret = 0;
    struct sockaddr_in connAddr;
    socklen_t len = sizeof(connAddr);
    // 1. 创建一个socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 创建一个sockaddr，并将它的端口号设为0
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 0;        // 若port指定为0,则调用bind时，系统会为其指定一个可用的端口号

    // 3. 绑定
    ret = bind(sock, (struct sockaddr *)&addr, sizeof addr);

    if (0 != ret) {
        result = false;
        goto END;
    }

    // 4. 利用getsockname获取
    
    ret = getsockname(sock, (struct sockaddr *)&connAddr, &len);

    if (0 != ret){
        result = false;
        goto END;
    }

    *port = ntohs(connAddr.sin_port); // 获取端口号

END:
    if ( 0 != close(sock) )
        result = false;
    return result;
}


int crGet3dInfoPorts( )
{
    bool ret = false;
    ret = getAvaliablePort(&d3dServerPort);
    if ( false == ret )
    {
        dis3DcrDebug("stone yy get 3d info server port error!\n");
        return -1;
    }
    ret = getAvaliablePort(&d3dRectPort);
    if ( false == ret )
    {
        dis3DcrDebug("stone yy get 3d info rect port error!\n");
        return -1;
    }
    dis3DcrDebug("stone yy get 3d info ports ok sport:%d rport:%d!\n",
        d3dServerPort, d3dRectPort);
    return 0;

}
int crServerSendSocketInit()
{
    struct sockaddr_in server_addr;
    int listen_fd;
    int on = 1;
    int send_len = 0;
    socklen_t      optlen = sizeof(send_len); 
    bool    ret = false;
    struct timeval timeout={20,0};//20s
    ret = getAvaliablePort(&d3dServerPort);
    if ( false == ret || 0 >= d3dServerPort)
    {
        //dis3DcrDebug("stone yy get 3d info server port:%d error!\n",d3dServerPort);
        crDebug("##[%d]Get TCP Port For Send Thread Failed##", getpid());
        return -1;
    }

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0){
        //dis3DcrDebug("stone create socket failed!!!"); 
        crDebug("[%d]##Create Socket For Send Thread Failed##", getpid());
        return -1;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(d3dServerPort);
    
    if((setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) == -1) {  
        crDebug("[%d]Send Thread: setsockopt failed: %s", getpid(), strerror(errno));  
        return -1; 
    }
    if ((getsockopt(listen_fd,SOL_SOCKET,SO_SNDBUF,&send_len,&optlen)) == -1 )
    {
        send_len = 16384;
    }
    g_send_buffer = send_len;

    if (setsockopt(listen_fd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout)) == -1)
    {  
        crDebug("[%d]Send Thread: setsockopt SEND TIME OUT failed: %s", getpid(), strerror(errno));  
        return -1; 
    }
    
    socketInitKeepalive(listen_fd);
    
    if(-1 == bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        crDebug(" stone bind failed the errno:%s(errno %d)!!!", strerror(errno), errno);
        return -1;
    }   
    if((listen(listen_fd, 10)) == -1)
    {
        crDebug(" stone listen failed the errno:%s(errno %d)", strerror(errno), errno);
        listen_fd = 0;
        return -1;
    }
    return listen_fd;
}



int crServerRectSocketInit()
{
    struct sockaddr_in server_addr;
    int listen_fd;
    int on = 1;
    int send_len = 0;
    socklen_t      optlen = sizeof(send_len); 
    bool    ret = false;
    struct timeval timeout={20,0};//20s
    
    ret = getAvaliablePort(&d3dRectPort);
    if ( false == ret || 0 >= d3dRectPort)
    {
        dis3DcrDebug("stone yy get 3d info rect port:%d error!\n",d3dRectPort);
        return -1;
    }

       
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0){
        dis3DcrDebug("stone create socket failed!!!"); 
        return -1;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(d3dRectPort);
    
    if((setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) == -1) {  
        dis3DcrDebug("stone setsockopt failed: %s", strerror(errno));  
        return -1; 
    }
    
    if (setsockopt(listen_fd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout)) == -1)
    {  
        crDebug("[%d]Rect Thread: setsockopt SEND TIME OUT failed: %s", getpid(), strerror(errno));  
        return -1; 
    }
    
    socketInitKeepalive(listen_fd);
    
    if(-1 == bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        dis3DcrDebug(" stone bind failed the errno:%s(errno %d)!!!", strerror(errno), errno);
        return -1;
    }   
    if((listen(listen_fd, 10)) == -1)
    {
        dis3DcrDebug(" stone listen failed the errno:%s(errno %d)", strerror(errno), errno);
        listen_fd = 0;
        return -1;
    }
    return listen_fd;
}

Pixel_list *GetPixelFromList()
{
	Pixel_list *pixel = NULL;
	pthread_mutex_lock(&send_mutex);
    while(NULL == list_head && Pixel_Thread_Status == THREAD_ACTIVE){
    	pthread_cond_wait(&pthread_count_cv, &send_mutex);
		
    }
	if(list_head){
		pixel = list_head;
		//pixel->next = NULL;
		list_head = list_head->next;
		node_num --;
		pixel->next = NULL;
	}
    pthread_mutex_unlock(&send_mutex);
	return pixel;
}

char *Pixel_Compression(char *pixels, MessagePixel *msg, char *filename)
{
	int random;
	int com_len;
	int num = 0, tmp = 0, y = 0;
	char *com_buf = NULL;
	FILE *file = NULL;
	//char filename[32] = {0};

	random = rand() & 0xFFFFFF;
	msg->com_len = compress_jpeg(pixels, msg->width, msg->height, random);
	dis3DFree(pixels);
	sprintf(filename, "stone%d.jpg", random);
    file = fopen(filename, "r");
	if(file == NULL){ 
		crDebug("[%d]##%s: Open jpg Image Failed and error:%s(errno:%d)##",
			getpid(), __FUNCTION__, strerror(errno), errno);
        return NULL; 
    }else{
       fseek(file, 0, SEEK_END);
       com_len = ftell(file);
       com_buf =(char *) calloc(1,com_len);   //can calloc when init
       if ( NULL == com_buf ){
			crDebug("[%d]##%s Malloc Mem Failed##", getpid(), __FUNCTION__);
			fclose(file);
            return NULL;
       }
       fseek(file, 0, SEEK_SET);
       while(num < com_len){
           y = com_len - num;
           tmp = fread(com_buf , sizeof(char), y, file);
           num += tmp;
       }
       fclose(file);
    }
    msg->com_len = com_len;
	return com_buf;
}

char *Handle_Pixel_Reverse(char *data_buf, int Flag, int width, int height)
{
	char *pixels = NULL;
	int tmp = 0;
	if(!Flag){
        pixels = data_buf;
    }else{
        pixels = (char *)malloc(width * height * 4 + 4);
        if ( NULL != pixels ){
            for(tmp = 0; tmp < height; tmp++){
                memcpy(pixels + tmp * width * 4, data_buf + (height - tmp - 1) * width * 4, width * 4);
            }
            //free(data_buf);
            //data_buf = NULL;
            dis3DFree(data_buf);
         }else{
         	crDebug("[%d]##%s:Malloc Mem Failed##", getpid(), __FUNCTION__);
			return NULL;
         }
     }
	return pixels;
}

bool Send_Image_To_Terminal(Msg3DPixelData *msgpix, char *com_buf)
{
    int tmp = 0, num = 0, y = 0;
	int sendLen = 0;
	int oneImgTims = 0;
    //Msg3DPixelData pixelData;
	tmp = send(sockfd_3D, msgpix, sizeof(Msg3DPixelData), 0);
	if(tmp > 0){
    	tmp = 0;
    	y = msgpix->msg.com_len;
        while(y > 0){
        	if ( y >= g_send_buffer){
            	tmp = g_send_buffer;
            }else{
                tmp = y;
            }
            num = send(sockfd_3D, com_buf + sendLen, tmp, 0);
            if ( num < 0 || num == 0){
				crDebug("[%d]%s:Send Image Data To Terminal Failed And Return Value:%d, errno:%d %s ",
					getpid(), __FUNCTION__, num, errno,strerror(errno));
                if ( errno == EAGAIN )
                {
                    crDebug("[%d]%s:Send Image Data To Terminal time out  And Return Value:%d, errno:%d %s ",
                                        getpid(), __FUNCTION__, num, errno,strerror(errno));

                }
				//dis3DFree(com_buf);
            	//dis3DcrDebug("[%d]Send_Pixels:stone send data failed the num %d the errno %d!!!\n", getpid(), num, errno);
            	return false;
            }
            y -= num;	
            sendLen += num;
            oneImgTims ++;
        } 
		return true;
	}else{
		crDebug("[%d]##%s:Send Image Head To Terminal Failed And Return Value:%d, errno:%d %s ",
			getpid(), __FUNCTION__, num, errno,strerror(errno));
		return false;
	}
}

void Free_Image( Msg3DPixelData *msg, char *image)
{
	int windowid = msg->msg.windowid;
	pthread_mutex_lock(&last_pixel_mutex);
	dis3DFree(last_pixel[windowid].info);
	dis3DFree(last_pixel[windowid].image);
	last_pixel[windowid].info = msg;
	last_pixel[windowid].image = image;
	pthread_mutex_unlock(&last_pixel_mutex);
}

bool Send_Left_Image_To_Terminal()
{
	Last_Pixel_Info pixel_info;
	bool result = false;
    int  ret  = -1;
	int i = 0;
	for(i = 0; i < 16; i++){
		pthread_mutex_lock(&last_pixel_mutex);
		pixel_info = last_pixel[i];
		if(pixel_info.info && pixel_info.image){
			crDebug("[%d]##Send Left Image To Terminal##", getpid());
			CRMuralInfo *mural = (CRMuralInfo *) crHashtableSearch(cr_server.muralTable, pixel_info.window);
			if(sockfd_Rect > 0 && mural && mural->cVisibleRects > 0){
        		ret = Send_Rect_Tcp(sockfd_Rect, mural->cVisibleRects, mural->pVisibleRects, mural, pixel_info.window, 0, 0);
    		}else{
				crDebug("[%d]##Error:Rect Thread Socket Abnormal rect socket:%d mural:%p rects:%d##", 
                    getpid(),sockfd_Rect,mural,mural->cVisibleRects);
    		}
			if(ret > 0 && !Send_Image_To_Terminal(pixel_info.info, pixel_info.image)){
				crDebug("[%d]##Send Left Image:%d To Terminal Failed##", getpid(), i);
			}
		}
		pthread_mutex_unlock(&last_pixel_mutex);
	}
}

void * crServerSendThread( void  )
{
	struct sockaddr_in client_addr;
    socklen_t clientaddr_len;
    int listen_fd, conn_fd;
	int Flag;
    char *data_buf = NULL;
    char *pixels = NULL;
	char *image = NULL;
    char filename[32] = {0};
	Pixel_list *pixel_elem = NULL;
    Msg3DPixelData * msgPixelData  = NULL;
    struct timeval tvstart, tvend;
	
	clientaddr_len = sizeof(client_addr);
	listen_fd =  crServerSendSocketInit();
    if ( listen_fd < 0 )
    {
        crDebug("[%d]##Send Thread: Listen Failed##", getpid());
		pthread_mutex_lock(&send_mutex);
		Pixel_Thread_Status = THREAD_UNEXIST;
		pthread_mutex_unlock(&send_mutex);
        return NULL;
    }

	while(1)
	{
		crDebug("[%d]##Send Thread:Start Accept.........", getpid());
        conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        if(conn_fd == -1){
			crDebug("[%d]##Send Thread:Accept Failed the errno:%s(errno %d)", getpid(), strerror(errno), errno);
            break;     //continue;
        }else{
        	crDebug("[%d]##Send Thread:Accept Client Success##", getpid());
        	sockfd_3D = conn_fd;
        }
		pthread_mutex_lock(&send_mutex);
		Pixel_Thread_Status = THREAD_ACTIVE;
		pthread_mutex_unlock(&send_mutex);
        Send_Left_Image_To_Terminal();
		while(1)
		{
            
           
			pixel_elem = GetPixelFromList();
			if(Pixel_Thread_Status == THREAD_ACTIVE){
                if (NULL == pixel_elem)
                {
                    crDebug("[%d]%s %d ##Send Thread:GetPixelFromList is NULL", getpid(),__FUNCTION__,__LINE__);
                    continue;
                }
				msgPixelData = (Msg3DPixelData *)malloc(sizeof(Msg3DPixelData));
                if ( NULL == msgPixelData)
                {
				    crDebug("[%d]##Malloc Mem For Msg3DPixelData Failed##", getpid());
					dis3DFree(pixel_elem);
					continue;
				}
                msgPixelData->head.msg_type = CR_3D_MSG_IMG;
                msgPixelData->head.msg_len = sizeof(MessagePixel);
				msgPixelData->msg.format = GL_RGBA;
                msgPixelData->msg.type = GL_UNSIGNED_BYTE;
				msgPixelData->msg.x = pixel_elem->info.x;
        		msgPixelData->msg.y = pixel_elem->info.y;
        		msgPixelData->msg.width = pixel_elem->info.width;
        		msgPixelData->msg.height = pixel_elem->info.height;
    			msgPixelData->msg.windowid = pixel_elem->info.cRects;
				msgPixelData->msg.msg_len = (msgPixelData->msg.width) *(msgPixelData->msg.height) * 4;
        		data_buf = pixel_elem->info.buf;
        		Flag = pixel_elem->info.flag_image;
                
				/*Handle Pixel's upside down*/
				pixels = Handle_Pixel_Reverse(data_buf, Flag, msgPixelData->msg.width,msgPixelData->msg.height);
				if(pixels){
					/* Pixel Jpeg Compression */
                    //gettimeofday(&tvstart, NULL);
					image = Pixel_Compression(pixels, &(msgPixelData->msg), filename);
                    //gettimeofday(&tvend, NULL);
                    //crDebug("[%d]stone the Pixel_Compression() use time is %d, ms:%d",
                    //            getpid(), tvend.tv_sec - tvstart.tv_sec, (tvend.tv_usec - tvstart.tv_usec)/1000);
					if(image){
						/* Send Pixel Head To Terminal */
						if(!Send_Image_To_Terminal(msgPixelData, image)){
							pthread_mutex_lock(&send_mutex);
							Pixel_Thread_Status = THREAD_NEED_CLOSE;
							pthread_mutex_unlock(&send_mutex);
							Free_Image(msgPixelData, image);
							goto ReAccept;
						}
                        Free_Image(msgPixelData, image);
					}else{
						crDebug("[%d]##%s:Jpeg Compression Pixel Failed##", getpid(), __FUNCTION__);
					}
				}
                
				if( '\0' != filename[0]){
					remove(filename);
                    memset( filename, 0 ,31);
				}
				
				dis3DFree(pixel_elem);
			}else{
				crDebug("[%d]##%s:Thread Status Abnormal And Close Server Socket##",getpid(), __FUNCTION__);
                goto ReAccept;
			}	
		}
		ReAccept:
			if( '\0' != filename[0])
			{
    			remove(filename);
                memset( filename, 0 ,31);
			}
			dis3DFree(pixel_elem);
			close(sockfd_3D);
            sockfd_3D = -1;
            pthread_mutex_lock(&send_mutex);
            Pixel_Thread_Status = THREAD_UNEXIST;
            pthread_mutex_unlock(&send_mutex);
	}
    if (listen_fd > 0)
    {
        close(listen_fd);
    }
}


void crServerSendThredInit()
{
    crSendMuxInit();
	if(pthread_create(&pixel_id, NULL, (void *)crServerSendThread, NULL) < 0){
		crDebug("[%d]##Create Send Pixel pthread Failed##", getpid());  
	}else{
        pthread_mutex_lock(&send_mutex);
		Pixel_Thread_Status = THREAD_ACTIVE;
        pthread_mutex_unlock(&send_mutex);
		crDebug("[%d]##Create Send Pixel Thread Success##", getpid());
	}
}

void crRectMuxInit()
{
    //yy  debug  the read pixels before
    static bool rectMux = 1;
    if(rectMux){
        pthread_mutex_init(&mutex_Rect_3D, NULL);
        pthread_cond_init(&pthread_count_rect, NULL);
        rectMux = 0;
    }
}

void * crServerRectThread( void  )
{
    struct sockaddr_in client_addr;
    socklen_t clientaddr_len;
    int listen_fd, conn_fd;
    int   sendBufLen = 0;
    
    clientaddr_len = sizeof(client_addr);
    listen_fd =  crServerRectSocketInit();
    if ( listen_fd < 0 )
    {
        crDebug("[%d]##%s:Rect Thread:Listen Client Failed##", getpid(), __FUNCTION__);
		pthread_mutex_lock(&mutex_Rect_3D);
		Rect_Thread_Status = THREAD_UNEXIST;
        pthread_mutex_unlock(&mutex_Rect_3D);
        return NULL;
    }

    while(1)
    {
        crDebug("##[%d]Rect Thread:Start Accept......", getpid());
        conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        if(conn_fd == -1){
            crDebug("[%d]Rect Thread:accept failed the errno:%s(errno %d)", getpid(), strerror(errno), errno);
            break;      //continue;
        }else{
        	crDebug("[%d]##Rect Thread Accept Client Success##", getpid());
        	sockfd_Rect = conn_fd;
        }
        
        pthread_mutex_lock(&mutex_Rect_3D);
		Rect_Thread_Status = THREAD_ACTIVE;
        while (Rect_Thread_Status == THREAD_ACTIVE) 
        {
            pthread_cond_wait(&pthread_count_rect, &mutex_Rect_3D);
			if(Rect_Thread_Status == THREAD_NEED_CLOSE){
				crDebug("[%d]##Rect Thread Status:CLOSE And Close Server Socket##", getpid());
				break;
			}
        }
        pthread_mutex_unlock(&mutex_Rect_3D);
   Re_Accept:     
        pthread_mutex_lock(&mutex_Rect_3D);
        close(sockfd_Rect);
        sockfd_Rect = -1;
        Rect_Thread_Status = THREAD_UNEXIST;
        pthread_mutex_unlock(&mutex_Rect_3D);
    	crDebug("[%d]##Rect Thread:Restart Accept Client##"); 
    }
    close(listen_fd); 
    return NULL;
}

void crServerRectThredInit()
{
    crDebug("[%d]##Rect Thread Init##", getpid());
    crRectMuxInit();
	if(pthread_create(&rect_id, NULL, (void *)crServerRectThread, NULL) < 0){
		crDebug("[%d]##Create Send Rect Thread Failed##", getpid());  
	}else{
        pthread_mutex_lock(&mutex_Rect_3D);
		Rect_Thread_Status = THREAD_ACTIVE;
		//rect_thread = 0;
        pthread_mutex_unlock(&mutex_Rect_3D);
	 }
}

void crServer3DThredInit()
{
    if ( -1 == crGet3dInfoPorts())  
    {
        dis3DcrDebug("stone crGet3dInfoPorts failed: %s", strerror(errno));  
        return -1; 
    }
    crServerSendThredInit();
    crServerRectThredInit();

}

void SERVER_DISPATCH_APIENTRY
crServerDispatchSwapBuffers( GLint window, GLint flags, GLint phyLowAddr, GLint phyHighAddr)
{
  CRMuralInfo *mural;
  CRContext *ctx;
  int j = g_sleep_count;
  uint64_t hw_addr = ((uint64_t)phyLowAddr) | ((uint64_t)phyHighAddr<<32);
  

#ifdef VBOXCR_LOGFPS
  static VBOXCRFPS Fps;
  static bool bFpsInited = false;
    
  if (!bFpsInited)
  {
      vboxCrFpsInit(&Fps, 64 /* cPeriods */);
      bFpsInited = true;
  }
  vboxCrFpsReportFrame(&Fps);
  if(!(vboxCrFpsGetNumFrames(&Fps) % 31))
  {
      double fps = vboxCrFpsGetFps(&Fps);
      double bps = vboxCrFpsGetBps(&Fps);
      double bpsSent = vboxCrFpsGetBpsSent(&Fps);
      double cps = vboxCrFpsGetCps(&Fps);
      double ops = vboxCrFpsGetOps(&Fps);
      double tup = vboxCrFpsGetTimeProcPercent(&Fps);
      crDebug("[%d]fps: %f, rec Mbps: %.1f, send Mbps: %.1f, cps: %.1f, ops: %.0f, host %.1f%%", 
              getpid(), fps, bps/(1024.0*1024.0), bpsSent/(1024.0*1024.0), cps, ops, tup);
  }

#endif
    //printf("stone crServerDispatchSwapBuffers in  in !! send_thread:%d \n",send_thread);

	if (hw_addr== 0)
	{
		crDebug("#zr# : Error crServerDispatchSwapBuffers phy_addr : %x-%x, hw64addr:%llx", phyLowAddr, phyHighAddr, hw_addr);
	}
	
	mural = (CRMuralInfo *) crHashtableSearch(cr_server.muralTable, window);
	if (!mural) {
		crDebug("##In SwapBuffer() The Mural Is NULL##");
		 return;
	}


	if (cr_server.only_swap_once)
	{
		/* NOTE: we only do the clear for the _last_ client in the list.
		 * This is because in multi-threaded apps the zeroeth client may
		 * be idle and never call glClear at all.  See threadtest.c
		 * It's pretty likely that the last client will be active.
		 */
		if (cr_server.curClient != cr_server.clients[cr_server.numClients - 1])
		{
			crDebug("In SwapBuffer() And return##");
			return;
		}
	}


	/* Check if using a file network */
	if (!cr_server.clients[0]->conn->actual_network && window == MAGIC_OFFSET)
		window = 0;

	ctx = crStateGetCurrent();

	CRASSERT(cr_server.curClient && cr_server.curClient->currentMural == mural);

    if (ctx->framebufferobject.drawFB
            || (ctx->buffer.drawBuffer != GL_FRONT && ctx->buffer.drawBuffer != GL_FRONT_LEFT))
        mural->bFbDraw = GL_FALSE;

    CR_SERVER_DUMP_SWAPBUFFERS_ENTER();

	if (hw_addr != 0) {
		crServerPixelsProcess(mural, hw_addr);
	}
	
	
    if (crServerIsRedirectedToFBO())
    {
        crServerMuralFBOSwapBuffers(mural);
        crServerPresentFBO(mural);
        
        //crServerPixelsProcess(mural);
        
    }
    else
    {
	    crDebug("[%d]stone call SwapBuffers in crServerDispatchSwapBuffers", getpid());
        cr_server.head_spu->dispatch_table.SwapBuffers( mural->spuWindow, flags, phyLowAddr, phyHighAddr);
    }
    
    
    CR_SERVER_DUMP_SWAPBUFFERS_LEAVE();
}

void SERVER_DISPATCH_APIENTRY
crServerDispatchFlush(void)
{
    CRContext *ctx = crStateGetCurrent();
    cr_server.head_spu->dispatch_table.Flush();

    if (cr_server.curClient && cr_server.curClient->currentMural)
    {
        CRMuralInfo *mural = cr_server.curClient->currentMural;
        if (mural->bFbDraw)
        {
            if (crServerIsRedirectedToFBO()){
                crServerPresentFBO(mural);
                
                //crServerPixelsProcess(mural);
             }
        }

        if (ctx->framebufferobject.drawFB
                || (ctx->buffer.drawBuffer != GL_FRONT && ctx->buffer.drawBuffer != GL_FRONT_LEFT))
            mural->bFbDraw = GL_FALSE;
    }
}

void SERVER_DISPATCH_APIENTRY
crServerDispatchFinish(void)
{
    CRContext *ctx = crStateGetCurrent();

    cr_server.head_spu->dispatch_table.Finish();

    if (cr_server.curClient && cr_server.curClient->currentMural)
    {
        CRMuralInfo *mural = cr_server.curClient->currentMural;
        if (mural->bFbDraw)
        {
            if (crServerIsRedirectedToFBO()){
                crServerPresentFBO(mural);
                
                //crServerPixelsProcess(mural);
            }
        }

        if (ctx->framebufferobject.drawFB
                || (ctx->buffer.drawBuffer != GL_FRONT && ctx->buffer.drawBuffer != GL_FRONT_LEFT))
            mural->bFbDraw = GL_FALSE;
    }
}
