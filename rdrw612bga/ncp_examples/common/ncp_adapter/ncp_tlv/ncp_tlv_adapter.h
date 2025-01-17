/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __NCP_TLV_ADAPTER_H__
#define __NCP_TLV_ADAPTER_H__

#include "ncp_intf_pm.h"
#include "ncp_adapter.h"
#include "fsl_os_abstraction.h"

#ifdef __GNUC__
/** Structure packing begins */
#define NCP_TLV_PACK_START
/** Structure packeing end */
#define NCP_TLV_PACK_END __attribute__((packed))
#else /* !__GNUC__ */
#ifdef PRAGMA_PACK
/** Structure packing begins */
#define NCP_TLV_PACK_START
/** Structure packeing end */
#define NCP_TLV_PACK_END
#else /* !PRAGMA_PACK */
/** Structure packing begins */
#define NCP_TLV_PACK_START __packed
/** Structure packing end */
#define NCP_TLV_PACK_END
#endif /* PRAGMA_PACK */
#endif /* __GNUC__ */

#define TLV_CMD_HEADER_LEN      12
#define TLV_CMD_SIZE_LOW_BYTES  4
#define TLV_CMD_SIZE_HIGH_BYTES 5
#define TLV_CMD_BUF_SIZE        4096
#define NCP_CHKSUM_LEN          4
#define NCP_MAX_CLASS           5



#define NCP_GET_PEER_CHKSUM(tlv, tlv_sz)  (*((uint32_t *)((uint8_t *)tlv + tlv_sz)))
#define NCP_GET_CLASS(tlv)                (((tlv) & 0xff000000) >> 24)

#define ARG_UNUSED(x) (void)(x)

typedef void (*tlv_callback_t)(void *tlv, size_t tlv_sz, int status);


typedef void (*tlv_send_callback_t)(void *arg);
typedef struct _ncp_intf_ops
{
    int (*init)(void *);
    int (*deinit)(void *);
    int (*send)(uint8_t *buf, size_t len, tlv_send_callback_t cb);
    int (*recv)(uint8_t *buf, size_t *len);
    ncp_intf_pm_ops_t *pm_ops;
} ncp_intf_ops_t;

typedef struct _ncp_tlv_adapter
{
    ncp_intf_ops_t *intf_ops;
    tlv_callback_t tlv_handler[NCP_MAX_CLASS];
} ncp_tlv_adapter_t;

/* NCP Debug options */
#ifdef CONFIG_NCP_DEBUG
/* Interface related stats*/
typedef struct _stats_intf
{
    uint32_t tx;
    uint32_t rx;
    uint32_t err;
    uint32_t chkerr;
    uint32_t drop;
    uint32_t lenerr;
    uint32_t ringerr;
} stats_inft_t;

/* NCP Interface stats container */
typedef struct _ncp_stats
{
    stats_inft_t tlvq;
#ifdef CONFIG_NCP_UART
    stats_inft_t uart;
#endif
#ifdef CONFIG_NCP_SPI
    stats_inft_t spi;
#endif
#ifdef CONFIG_NCP_USB
    stats_inft_t usb;
#endif
#ifdef CONFIG_NCP_SDIO
    stats_inft_t sdio;
#endif
} ncp_stats_t;

/* Global variable containing NCP internal statistics */
extern ncp_stats_t ncp_stats;

#define NCP_STATS_INC(x) ++ncp_stats.x
#define NCP_STATS_DEC(x) --ncp_stats.x
#else
#define NCP_STATS_INC(x)
#define NCP_STATS_DEC(x)
#endif /* CONFIG_NCP_DEBUG */


#define NCP_TLV_STATS_INC(x) NCP_STATS_INC(tlvq.x)
#if defined(CONFIG_NCP_DEBUG) && defined(CONFIG_NCP_UART)
#define NCP_UART_STATS_INC(x) NCP_STATS_INC(uart.x)
#else
#define NCP_UART_STATS_INC(x)
#endif

#if defined(CONFIG_NCP_DEBUG) && defined(CONFIG_NCP_SPI)
#define NCP_SPI_STATS_INC(x) NCP_STATS_INC(spi.x)
#else
#define NCP_SPI_STATS_INC(x)
#endif

#if defined(CONFIG_NCP_DEBUG) && defined(CONFIG_NCP_USB)
#define NCP_USB_STATS_INC(x) NCP_STATS_INC(usb.x)
#else
#define NCP_USB_STATS_INC(x)
#endif

#if defined(CONFIG_NCP_DEBUG) && defined(CONFIG_NCP_SDIO)
#define NCP_SDIO_STATS_INC(x) NCP_STATS_INC(sdio.x)
#else
#define NCP_SDIO_STATS_INC(x)
#endif

/* End of NCP debug options */

void ncp_tlv_dispatch(void *tlv, size_t tlv_sz);


/*NCP ADAPTER TX CODE*/

/* NCP ADAPTER TLV TX task function */

/* NCP ADAPTER tlv send */
ncp_status_t ncp_tlv_send(void *tlv_buf, size_t tlv_sz);

/* NCP ADAPTER TX queue element */
typedef NCP_TLV_PACK_START struct
{
    void *priv;
    size_t tlv_sz;
    uint8_t *tlv_buf;
} NCP_TLV_PACK_END ncp_tlv_qelem_t;


#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/* ADAPTER TLV TASK PRIORITY */
#ifdef CONFIG_NCP_WIFI
#define NCP_TLV_TX_TASK_PRIORITY    6
#elif defined(CONFIG_NCP_BLE)      
#define NCP_TLV_TX_TASK_PRIORITY    11
#endif      

/* NCP ADAPTER TX queue max length */
#define NCP_TLV_QUEUE_LENGTH 160
/* NCP ADAPTER TX task stack size */
#define NCP_TLV_TX_TASK_STACK_SIZE 1024
#endif /* __NCP_TLV_ADAPTER_H__ */