/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#define AML_MODULE          SDIO
#define AML_FMT             AML_FMT_M

#include "w2_sdio.h"
#include <linux/mutex.h>
#include "chip_ana_reg.h"
#include "chip_pmu_reg.h"
#include "chip_intf_reg.h"
#include "wifi_intf_addr.h"
#include "wifi_top_addr.h"
#include "wifi_sdio_cfg_addr.h"
#include "sdio_common.h"
#include "sg_common.h"
#include "aml_interface.h"
#include "wifi_w2_shared_mem_cfg.h"
#include "aml_static_buf.h"
#include "aml_log.h"
#include "lmac_msg.h"

uint8_t *g_mmc_misc;
struct aml_hwif_sdio g_hwif_rx_sdio;
struct aml_hif_sdio_ops g_hif_sdio_ops;
extern struct aml_bus_state_detect bus_state_detect;
extern struct aml_sdio_baddr adio_baddr;

extern unsigned char g_wifi_in_insmod;
extern unsigned char *g_func_kmalloc_buf;
static unsigned int tx_buffer_base_addr;
static unsigned int rx_buffer_base_addr;
extern unsigned int chip_id;
extern unsigned char g_sdio_after_porbe;

extern unsigned char wifi_in_insmod;
extern unsigned char wifi_in_rmmod;
extern unsigned char  chip_en_access;
extern unsigned char wifi_sdio_shutdown;
extern struct aml_pm_type g_wifi_pm;
static DEFINE_MUTEX(wifi_bt_sdio_mutex);
static DEFINE_MUTEX(wifi_ipc_mutex);

extern unsigned char (*host_wake_req)(void);
extern int (*host_suspend_req)(struct device *device);
extern int (*host_resume_req)(struct device *device);


static int _aml_sdio_request_byte(unsigned char func_num,
    unsigned char write, unsigned int reg_addr, unsigned char *byte)
{
    int err_ret = 0;
    struct sdio_func * func = aml_priv_to_func(func_num);
    unsigned char *kmalloc_buf = NULL;
    unsigned char len = sizeof(unsigned char);

#if defined(DBG_PRINT_COST_TIME)
    struct timespec now, before;
    getnstimeofday(&before);
#endif /* End of DBG_PRINT_COST_TIME */

    if (!func) {
        AML_ERR("func is NULL!\n");
        return -1;
    }

    if (!byte) {
        AML_ERR("byte is NULL!\n");
        return -1;
    }

    BUG_ON(func->num != func_num);

    AML_BT_WIFI_MUTEX_ON();
    kmalloc_buf =  (unsigned char *)ZMALLOC(len, "sdio_write", GFP_DMA);
    if (kmalloc_buf == NULL)
    {
        AML_ERR("kmalloc buf fail\n");
        AML_BT_WIFI_MUTEX_OFF();
        return SDIOH_API_RC_FAIL;
    }
    memcpy(kmalloc_buf, byte, len);

    AML_PROF_HI(cmd52);
    /* Claim host controller */
    sdio_claim_host(func);
    if (bus_state_detect.bus_err) {
        AML_ERR("sdio bus request byte error \n");

    } else {
        if (write) {
            /* CMD52 Write */
            sdio_writeb(func, *kmalloc_buf, reg_addr, &err_ret);
        }
        else {
            /* CMD52 Read */
            *byte = sdio_readb(func, reg_addr, &err_ret);
        }
    }
    /* Release host controller */
    sdio_release_host(func);
    AML_PROF_LO(cmd52);

#if defined(DBG_PRINT_COST_TIME)
    getnstimeofday(&now);

    AML_INFO("[sdio byte]: len=1 cost=%lds %luus\n",
        now.tv_sec-before.tv_sec, now.tv_nsec/1000 - before.tv_nsec/1000);
#endif /* End of DBG_PRINT_COST_TIME */

    FREE(kmalloc_buf, "sdio_write");
    AML_BT_WIFI_MUTEX_OFF();
    return (err_ret == 0) ? SDIOH_API_RC_SUCCESS : SDIOH_API_RC_FAIL;
}

//cmd52, func 0, for self define domain
int aml_sdio_self_define_domain_func0_write8(int addr, unsigned char data)
{
    int ret = 0;
    bool sdio_bus_block = false;
    unsigned char func_num = 0;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    ret =  _aml_sdio_request_byte(SDIO_FUNC0, SDIO_WRITE, addr, &data);
    return ret;
}

//cmd52
unsigned char aml_sdio_self_define_domain_func0_read8(int addr)
{
    unsigned char sramdata = 0;
    bool sdio_bus_block = false;
    unsigned char func_num = 0;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    _aml_sdio_request_byte(SDIO_FUNC0, SDIO_READ, addr, &sramdata);
    return sramdata;
}

//cmd52, func 1, for self define domain
int aml_sdio_self_define_domain_write8(int addr, unsigned char data)
{
    int ret = 0;
    bool sdio_bus_block = false;
    unsigned char func_num = 1;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    ret =  _aml_sdio_request_byte(SDIO_FUNC1, SDIO_WRITE, addr, &data);
    return ret;
}

//cmd52
unsigned char aml_sdio_self_define_domain_read8(int addr)
{
    unsigned char sramdata = 0;
    bool sdio_bus_block = false;
    unsigned char func_num = 1;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    _aml_sdio_request_byte(SDIO_FUNC1, SDIO_READ, addr, &sramdata);
    return sramdata;
}

extern int _aml_sdio_request_buffer(unsigned char func_num, unsigned int fix_incr, unsigned char write, unsigned int addr, void * buf, unsigned int nbytes);
//cmd53
int aml_sdio_bottom_write(unsigned char func_num, unsigned int addr, void *buf, size_t len, int incr_addr)
{
    void *kmalloc_buf;
    int result;
    bool sdio_bus_block = false;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    BUG_ON(func_num == SDIO_FUNC0);
    BUG_ON(!g_func_kmalloc_buf);

    if (host_wake_req != NULL) {
        if (host_wake_req() == 0) {
            AML_ERR("aml_sdio_bottom_write, host wake fail\n");
            return -1;
        }
    }

    AML_BT_WIFI_MUTEX_ON();
    kmalloc_buf = (unsigned char *)g_func_kmalloc_buf;
    memcpy(kmalloc_buf, buf, len);
    result = _aml_sdio_request_buffer(func_num, incr_addr, SDIO_WRITE, addr, kmalloc_buf, len);
    AML_BT_WIFI_MUTEX_OFF();

    if (result && !bus_state_detect.bus_err && (atomic_read(&g_wifi_pm.is_shut_down) == 0)) {
        if (bus_state_detect.is_drv_load_finished) {
            bus_state_detect.bus_err = 1;
            AML_ERR("sdio bus error(%d), will do reovery later\n", result);
        } else {
            bus_state_detect.bus_err = 2;
            AML_ERR("sdio bus error(%d), sdio reset by timer later\n", result);
         }
    }
    return result;
}

int aml_sdio_bottom_read(unsigned char func_num, int addr, void *buf, size_t len, int incr_addr)
{
    unsigned char *kmalloc_buf = NULL;
    int result;
    int align_len = 0;
    bool sdio_bus_block = false;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num,addr);
    if (sdio_bus_block)
    {
       return 0;
    }

    func_num &= 0xf;
    BUG_ON(func_num == SDIO_FUNC0);
    BUG_ON(!g_func_kmalloc_buf);

    if (host_wake_req != NULL) {
        if (host_wake_req() == 0) {
            AML_ERR("aml_sdio_bottom_read, host wake fail\n");
            return -1;
        }
    }

    AML_BT_WIFI_MUTEX_ON();
    /* read block mode */
    if (func_num != SDIO_FUNC0) {
        if (incr_addr == SDIO_OPMODE_INCREMENT) {
            struct sdio_func * func = aml_priv_to_func(func_num);
            align_len = sdio_align_size(func, len);
            kmalloc_buf = (unsigned char *)g_func_kmalloc_buf;
        }
        else
            kmalloc_buf = (unsigned char *)g_func_kmalloc_buf;
    } else {
        kmalloc_buf = (unsigned char *)buf;
    }

    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail buf %px SDIO_FUNC %d\n", buf, func_num);
        AML_BT_WIFI_MUTEX_OFF();
        return SDIOH_API_RC_FAIL;
    }

    result = _aml_sdio_request_buffer(func_num, incr_addr, SDIO_READ, addr, kmalloc_buf, len);

    if (kmalloc_buf != buf) {
        memcpy(buf, kmalloc_buf, len);
    }

    AML_BT_WIFI_MUTEX_OFF();
    if (result && !bus_state_detect.bus_err && (atomic_read(&g_wifi_pm.is_shut_down) == 0)) {
        if (bus_state_detect.is_drv_load_finished) {
            bus_state_detect.bus_err = 1;
            AML_ERR("sdio bus error(%d), will do reovery later\n", result);
        } else {
            bus_state_detect.bus_err = 2;
            AML_ERR("sdio bus error(%d), sdio reset by timer later\n", result);
         }
    }

    return result;
}

//func 1, cmd52, self define domain
int aml_sdio_self_define_domain_write32(unsigned long sram_addr, unsigned long sramdata)
{
    if (sram_addr == RG_SCFG_FUNC2_BADDR_A)
        adio_baddr.func2_baddr = sramdata;
    else if (sram_addr == RG_SCFG_FUNC3_BADDR_A)
        adio_baddr.func3_baddr = sramdata;
    else if (sram_addr == RG_SCFG_FUNC4_BADDR_A)
        adio_baddr.func4_baddr = sramdata;
    else if (sram_addr == RG_SCFG_FUNC5_BADDR_A)
        adio_baddr.func5_baddr = sramdata;
    else if (sram_addr == RG_SCFG_FUNC6_BADDR_A)
        adio_baddr.func6_baddr = sramdata;
    else if (sram_addr == RG_SCFG_FUNC7_BADDR_A)
        adio_baddr.func7_baddr = sramdata;

    return aml_sdio_bottom_write(SDIO_FUNC1, sram_addr&SDIO_ADDR_MASK,
        (unsigned char *)&sramdata,  sizeof(unsigned long), SDIO_OPMODE_INCREMENT);
}

unsigned long  aml_sdio_self_define_domain_read32(unsigned long sram_addr)
{
    unsigned long sramdata = 0;

    aml_sdio_bottom_read(SDIO_FUNC1, sram_addr&SDIO_ADDR_MASK, &sramdata, 4, SDIO_OPMODE_INCREMENT);
    return sramdata;
}

//func2, for random ram
void aml_sdio_random_word_write(unsigned int addr, unsigned int data)
{
    unsigned int len = sizeof(unsigned int);

    AML_WIFI_IPC_MUTEX_ON();
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC2_BADDR_A, (unsigned long)(addr) & 0xfffe0000);
    aml_sdio_bottom_write(SDIO_FUNC2, (SYS_TYPE)addr & SDIO_ADDR_MASK,
        (unsigned char *)&data, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
    AML_WIFI_IPC_MUTEX_OFF();
}

unsigned int aml_sdio_random_word_read(unsigned int addr)
{
    unsigned int regdata = 0;
    unsigned int len = sizeof(unsigned int);

    AML_WIFI_IPC_MUTEX_ON();
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC2_BADDR_A, (unsigned long)(addr) & 0xfffe0000);
    aml_sdio_bottom_read(SDIO_FUNC2, (SYS_TYPE)addr & SDIO_ADDR_MASK,
        (unsigned char*)&regdata, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    AML_WIFI_IPC_MUTEX_OFF();

    return regdata;
}

void aml_sdio_random_ram_write(unsigned char *buf, unsigned char *addr, size_t len)
{
    AML_WIFI_IPC_MUTEX_ON();

    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC2_BADDR_A, (unsigned long)(addr) & 0xfffe0000);
    aml_sdio_bottom_write(SDIO_FUNC2, ((SYS_TYPE)addr & SDIO_ADDR_MASK),
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    AML_WIFI_IPC_MUTEX_OFF();
}

void aml_sdio_random_ram_read(unsigned char* buf, unsigned char* addr, size_t len)
{
    AML_WIFI_IPC_MUTEX_ON();

    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC2_BADDR_A, (unsigned long)(addr) & 0xfffe0000);
    aml_sdio_bottom_read(SDIO_FUNC2, (SYS_TYPE)addr & SDIO_ADDR_MASK,
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    AML_WIFI_IPC_MUTEX_OFF();
}

//func3 for sram
void aml_sdio_sram_word_write(unsigned int addr, unsigned int data)
{
    unsigned int len = sizeof(unsigned int);
    aml_sdio_bottom_write(SDIO_FUNC3, (SYS_TYPE)addr % MAC_SRAM_BASE,
        (unsigned char *)&data, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

unsigned int aml_sdio_sram_word_read(unsigned int addr)
{
    unsigned int regdata = 0;
    unsigned int len = sizeof(unsigned int);

    aml_sdio_bottom_read(SDIO_FUNC3, (SYS_TYPE)addr % MAC_SRAM_BASE,
        (unsigned char*)&regdata, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    return regdata;
}

void aml_sdio_sram_write(unsigned char *buf, unsigned char *addr, size_t len)
{
    aml_sdio_bottom_write(SDIO_FUNC3, (SYS_TYPE)addr % MAC_SRAM_BASE,
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

void aml_sdio_sram_read(unsigned char* buf, unsigned char* addr, size_t len)
{
    aml_sdio_bottom_read(SDIO_FUNC3, (SYS_TYPE)addr % MAC_SRAM_BASE,
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

//sdio func4 for tx buffer write/read
void aml_sdio_func4_set_base_addr(unsigned int addr, size_t len)
{
    if ((addr % tx_buffer_base_addr) >= SRAM_MAX_LEN || addr < tx_buffer_base_addr
        || ((addr % tx_buffer_base_addr) < SRAM_MAX_LEN && ((addr + len) % tx_buffer_base_addr) >= SRAM_MAX_LEN)) {
        tx_buffer_base_addr = addr;
        aml_sdio_self_define_domain_write32(RG_SCFG_FUNC4_BADDR_A, tx_buffer_base_addr);
    }
}

void aml_sdio_tx_buffer_write(unsigned char *buf, unsigned char *addr, size_t len)
{
    AML_WIFI_IPC_MUTEX_ON();

    aml_sdio_func4_set_base_addr((unsigned long)addr, len);
    aml_sdio_bottom_write(SDIO_FUNC4, ((SYS_TYPE)addr % tx_buffer_base_addr),
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    AML_WIFI_IPC_MUTEX_OFF();
}

void aml_sdio_tx_buffer_read(unsigned char* buf, unsigned char* addr, size_t len)
{
    AML_WIFI_IPC_MUTEX_ON();

    aml_sdio_func4_set_base_addr((unsigned long)addr, len);
    aml_sdio_bottom_read(SDIO_FUNC4, ((SYS_TYPE)addr % tx_buffer_base_addr),
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));

    AML_WIFI_IPC_MUTEX_OFF();
}

//sdio func5 for rx desc
int aml_sdio_desc_read(void* buf, u32 addr, size_t len)
{
    return aml_sdio_bottom_read(SDIO_FUNC5, addr - RG_WIFI_IF_FW2HST_IRQ_CFG, buf, len,
            (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

//sdio func6 for rx buffer
static int aml_sdio_rx_buffer_read(void *buf, u32 addr, unsigned int len, unsigned int unused)
{
    int received = 0;
    int ret = -1;

    /* NB: the caller should check rx buffer boundary more strictly (with "real" rx buffer end) */
    BUG_ON(addr < RXBUF_START_ADDR);
    BUG_ON((addr + len) >= 0x60080000);
    while (len) {
        unsigned int read_len = len > SDIO_READ_MAX ? SDIO_READ_MAX : len;
        u32 addr_lo = (addr - RXBUF_START_ADDR) & SDIO_ADDR_MASK;
        u32 base = addr - addr_lo;

        if (base != rx_buffer_base_addr) {
            rx_buffer_base_addr = base;
            aml_sdio_self_define_domain_write32(RG_SCFG_FUNC6_BADDR_A, base);
        }
        ret = aml_sdio_bottom_read(SDIO_FUNC6, addr_lo, buf, read_len, SDIO_OPMODE_INCREMENT);
        if (ret)
            break;

        len -= read_len;
        buf += read_len;
        addr += read_len;
        received += read_len;
    }
    return received ? : ret;
}

//sdio func7 for bt
void aml_bt_sdio_read_sram(unsigned char *buf, unsigned char *addr, SYS_TYPE len)
{
    if (bus_state_detect.bus_err) {
        AML_ERR(" sdio bus is recovery ongoing, can not read/write\n");
        return;
    }
#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        AML_ERR("bus suspend (%d) ongoing, do not read/write now!\n",
            atomic_read(&g_wifi_pm.bus_suspend_cnt));
        return;
    }
#endif

    aml_sdio_bottom_read(SDIO_FUNC7, ((SYS_TYPE)addr & SDIO_ADDR_MASK),
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

void aml_bt_sdio_write_sram(unsigned char *buf, unsigned char *addr, SYS_TYPE len)
{

    if (bus_state_detect.bus_err) {
        AML_ERR("sdio bus is recovery ongoing, can not read/write\n");
        return;
    }
#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        AML_ERR("bus suspend (%d) ongoing, do not read/write now!\n",
            atomic_read(&g_wifi_pm.bus_suspend_cnt));
        return;
    }
#endif

    aml_sdio_bottom_write(SDIO_FUNC7, ((SYS_TYPE)addr & SDIO_ADDR_MASK),
        buf, len, (len > 8 ? SDIO_OPMODE_INCREMENT : SDIO_OPMODE_FIXED));
}

unsigned int aml_bt_hi_read_word(unsigned int addr)
{
    unsigned int regdata = 0;
    unsigned int reg_tmp;
    /*
     * make sure function 5 section address-mapping feature is disabled,
     * when this feature is disabled,
     * all 128k space in one sdio-function use only
     * one address-mapping: 32-bit AHB Address = BaseAddr + cmdRegAddr
     */

    if (bus_state_detect.bus_err) {
        AML_ERR("sdio bus is recovery ongoing, can not read/write\n");
        return regdata;
    }
#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        AML_ERR("bus suspend (%d) ongoing, do not read/write now!\n",
            atomic_read(&g_wifi_pm.bus_suspend_cnt));
        return regdata;
    }
#endif

    reg_tmp = aml_sdio_self_define_domain_read32( RG_SDIO_IF_MISC_CTRL);

    if (!(reg_tmp & BIT(25))) {
        reg_tmp |= BIT(25);
        aml_sdio_self_define_domain_write32( RG_SDIO_IF_MISC_CTRL, reg_tmp);
    }

    /*config msb 15 bit address in BaseAddr Register*/
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC7_BADDR_A,addr & 0xfffe0000);
    /* coverity[overrun-buffer-val] */
    aml_bt_sdio_read_sram((unsigned char*)(SYS_TYPE)&regdata,
        /*sdio cmd 52/53 can only take 17 bit address*/
        (unsigned char*)(SYS_TYPE)(addr & 0x1ffff), sizeof(unsigned int));

    return regdata;
}

void aml_bt_hi_write_word(unsigned int addr,unsigned int data)
{
    unsigned int reg_tmp;

    if (bus_state_detect.bus_err) {
        AML_ERR("sdio bus is recovery ongoing, can not read/write\n");
        return;
    }
#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        AML_ERR("bus suspend (%d) ongoing, do not read/write now!\n",
            atomic_read(&g_wifi_pm.bus_suspend_cnt));
        return;
    }
#endif
    /*
     * make sure function 5 section address-mapping feature is disabled,
     * when this feature is disabled,
     * all 128k space in one sdio-function use only
     * one address-mapping: 32-bit AHB Address = BaseAddr + cmdRegAddr
     */
    reg_tmp = aml_sdio_self_define_domain_read32( RG_SDIO_IF_MISC_CTRL);

    if (!(reg_tmp & BIT(25))) {
        reg_tmp |= BIT(25);
        aml_sdio_self_define_domain_write32( RG_SDIO_IF_MISC_CTRL, reg_tmp);
    }
    /*config msb 15 bit address in BaseAddr Register*/
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC7_BADDR_A, addr & 0xfffe0000);
    /* coverity[overrun-buffer-val] */
    aml_bt_sdio_write_sram((unsigned char *)&data,
        /*sdio cmd 52/53 can only take 17 bit address*/
        (unsigned char*)(SYS_TYPE)(addr & 0x1ffff), sizeof(unsigned int));
}

unsigned int aml_sdio_read_word(unsigned int addr)
{
    unsigned int regdata = 0;

    // for bt access always on reg
    if (((addr & 0x00f00000) == 0x00f00000) || ((addr & 0x00f00000) == 0x00b00000)
        || ((addr & 0x00f00000) == 0x00d00000) || ((addr & 0x00f00000) == 0x00900000)
        || ((addr & 0x00f00000) == 0x00200000) || ((addr & 0x00f00000) == 0x00300000)
        || ((addr & 0x00f00000) == 0x00400000)) {
        regdata = aml_bt_hi_read_word(addr);
    }

    return regdata;
}

void aml_sdio_write_word(unsigned int addr, unsigned int data)
{
    // for bt access always on reg
    if (((addr & 0x00f00000) == 0x00f00000) || ((addr & 0x00f00000) == 0x00b00000)
        || ((addr & 0x00f00000) == 0x00d00000) || ((addr & 0x00f00000) == 0x00900000)
        || ((addr & 0x00f00000) == 0x00200000) || ((addr & 0x00f00000) == 0x00300000)
        || ((addr & 0x00f00000) == 0x00400000)) {
        aml_bt_hi_write_word(addr, data);
    }
}

void aml_sdio_scat_complete (struct amlw_hif_scatter_req * scat_req)
{
    BUG_ON(!scat_req);

    if (!scat_req) {
        AML_ERR("scar_req is NULL!\n");
        return;
    }

    scat_req->free = true;
    scat_req->scat_count = 0;
    scat_req->len = 0;
    scat_req->addr = 0;
    memset(scat_req->sgentries, 0, MAX_SG_ENTRIES * sizeof(struct scatterlist));
}

int aml_sdio_scat_req_rw(struct amlw_hif_scatter_req *scat_req)
{
    struct aml_hwif_sdio *hif_sdio = &g_hwif_sdio;
    struct sdio_func *func = NULL;
    struct mmc_host *host = NULL;

    unsigned int blk_size, blk_num;
    unsigned int max_blk_count, max_req_size;
    unsigned int func_num;

    struct scatterlist *sg;
    int sg_count, sgitem_count;
    int ttl_len, pkt_offset, ttl_page_num;

    struct mmc_request mmc_req;
    struct mmc_command mmc_cmd = {0};
    struct mmc_data mmc_dat = {0};
    //unsigned int reg_data = 0;

    int result = SDIOH_API_RC_FAIL;
    bool sdio_bus_block = false;

    BUG_ON(!scat_req);

    if (scat_req->req & HIF_WRITE)
        func_num = SDIO_FUNC4;
    else
        func_num = SDIO_FUNC6;

    sdio_bus_block = aml_sdio_block_bus_opt(func_num, 0);
    if (sdio_bus_block)
       return result;

    func = hif_sdio->sdio_func_if[func_num];
    host = func->card->host;

    blk_size = func->cur_blksize;
    max_blk_count = MIN(host->max_blk_count, SDIO_MAX_BLK_CNT); //host->max_blk_count: 511
    max_req_size = MIN(max_blk_count * blk_size, host->max_req_size); //host->max_req_size: 0x20000

    /* fill SG entries */
    sg = scat_req->sgentries;
    pkt_offset = 0;	    // reminder
    sgitem_count = 0; // count of scatterlist

    while (sgitem_count < scat_req->scat_count)
    {
        ttl_len = 0;
        sg_count = 0;
        ttl_page_num = 0;

        sg_init_table(sg, MAXSG_SIZE);

        /* assemble SG list */
        while ((sgitem_count < scat_req->scat_count) && (ttl_len < max_req_size))
        {
            int packet_len = 0;
            int sg_data_size = 0;
            unsigned char *pdata = NULL;

            if (sg_count >= MAXSG_SIZE)
                break;

            /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
            packet_len = scat_req->scat_list[sgitem_count].len;
            /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
            pdata = scat_req->scat_list[sgitem_count].packet;

            // sg len must be aligned with block size
            sg_data_size = ALIGN(packet_len, blk_size);
            if (sg_data_size > (max_req_size - ttl_len))
            {
                AML_INFO(" setup scat-data: sg_data_size %d, remain %d \n", sg_data_size, max_req_size - ttl_len);
                break;
            }

            sg_set_buf(&scat_req->sgentries[sg_count], pdata, sg_data_size);
            sg_count++;
            ttl_len += sg_data_size;

            ttl_page_num += scat_req->scat_list[sgitem_count].page_num;
            sgitem_count++;

            //AML_INFO("setup scat-data: offset: %d: ttl: %d, datalen:%d\n",
            //pkt_offset, ttl_len, sg_data_size);

        }

        if ((ttl_len == 0) || (ttl_len % blk_size != 0))
        {
            AML_INFO(" setup scat-data:  ttl_len %d \n", ttl_len);
            return result;
        }

        memset(&mmc_req, 0, sizeof(struct mmc_request));
        memset(&mmc_cmd, 0, sizeof(struct mmc_command));
        memset(&mmc_dat, 0, sizeof(struct mmc_data));

        /* set scatter-gather table for request */
        blk_num = ttl_len / blk_size;
        mmc_dat.flags = (scat_req->req & HIF_WRITE) ? MMC_DATA_WRITE : MMC_DATA_READ;
        mmc_dat.sg = scat_req->sgentries;
        mmc_dat.sg_len = sg_count;
        mmc_dat.blksz = blk_size;
        mmc_dat.blocks = blk_num;

        mmc_cmd.opcode = SD_IO_RW_EXTENDED;
        /* coverity[overflow_const]*/
        mmc_cmd.arg = (scat_req->req & HIF_WRITE) ? 1 << 31 : 0;
        mmc_cmd.arg |= (func_num & 0x7) << 28;
        /* block basic */
        mmc_cmd.arg |= 1 << 27;
        /* 0, fix address */
        mmc_cmd.arg |= SDIO_OPMODE_FIXED << 26;
        mmc_cmd.arg |= (scat_req->addr & 0x1ffff)<< 9;
        mmc_cmd.arg |= mmc_dat.blocks & 0x1ff;
        mmc_cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

        mmc_req.cmd = &mmc_cmd;
        mmc_req.data = &mmc_dat;

        AML_PROF_CNT(cmd53_tx, blk_num);
        sdio_claim_host(func);
        mmc_set_data_timeout(&mmc_dat, func->card);
        mmc_wait_for_req(func->card->host, &mmc_req);

        if (mmc_cmd.error || mmc_dat.error)
        {
            AML_ERR("ERROR CMD53 %s cmd_error = %d data_error=%d\n", (scat_req->req & HIF_WRITE) ? "write" : "read", mmc_cmd.error, mmc_dat.error);
            bus_state_detect.bus_err = 1;
        }

        sdio_release_host(func);
        AML_PROF_CNT(cmd53_tx, 0);

        // AML_INFO("setup scat-data: (%s) ====addr: 0x%X, (blksz: %d, blocks: %d) , (ttl:%d,sg:%d,scat_count:%d,ttl_page:%d)====\n",
            // (scat_req->req & HIF_WRITE) ? "wr" : "rd", scat_req->addr,
            // mmc_dat.blksz, mmc_dat.blocks, ttl_len,
            // sg_count, scat_req->scat_count, ttl_page_num);

        if (bus_state_detect.bus_err)
            break;
    }

    result = mmc_cmd.error ? mmc_cmd.error : mmc_dat.error;

    scat_req->result = result;

    if (scat_req->result)
        AML_ERR("Scatter write request failed:%d, req 0x%08x\n", scat_req->result, scat_req->req);

    if (scat_req->req & HIF_ASYNCHRONOUS)
        aml_sdio_scat_complete(scat_req);

    return result;
}


EXPORT_SYMBOL(g_mmc_misc);
int aml_sdio_scat_req_rx_read(struct amlw_hif_scatter_req *scat_req)
{
    uint32_t func_num = SDIO_FUNC6;
    struct sdio_func *func = aml_priv_to_func(func_num);
    struct mmc_host *host = func->card->host;
    struct mmc_misc *mmc_misc = (struct mmc_misc *)g_mmc_misc;

    uint8_t *pdata = NULL;
    int result = SDIOH_API_RC_SUCCESS;
    uint32_t blk_size = func->cur_blksize;
    uint32_t max_blk_count = MIN(host->max_blk_count, SDIO_MAX_BLK_CNT);
    uint32_t max_req_size = MIN(max_blk_count * blk_size, host->max_req_size);
    uint32_t i = 0, sg_count = 0, packet_len = 0, packet_addr = 0;

    BUG_ON(!scat_req);

    memset(mmc_misc, 0, sizeof(struct mmc_misc) * scat_req->scat_count);

    sg_init_table(scat_req->sgentries, MAXSG_SIZE);

    while (sg_count < scat_req->scat_count) {

        if (sg_count >= MAXSG_SIZE) {
            AML_ERR("error sg_count: %d\n", sg_count);
            result = SDIOH_API_RC_FAIL;
            break;
        }

        /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
        pdata = scat_req->scat_list[sg_count].packet;
        /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
        packet_len = scat_req->scat_list[sg_count].len;
        packet_addr = scat_req->scat_list[sg_count].page_num;

        if ((packet_len == 0) || (packet_len % blk_size != 0) || (packet_len > max_req_size)) {
            AML_ERR(" error packet_len: %d\n", packet_len);
            result = SDIOH_API_RC_FAIL;
            break;
        }

        sg_set_buf(&scat_req->sgentries[sg_count], pdata, packet_len);

        mmc_misc[sg_count].mmc_dat.flags = MMC_DATA_READ;
        mmc_misc[sg_count].mmc_dat.sg = &scat_req->sgentries[sg_count];
        mmc_misc[sg_count].mmc_dat.sg_len = 1;
        mmc_misc[sg_count].mmc_dat.blksz = blk_size;
        mmc_misc[sg_count].mmc_dat.blocks = packet_len / blk_size;

        mmc_misc[sg_count].mmc_cmd.opcode = SD_IO_RW_EXTENDED;
        mmc_misc[sg_count].mmc_cmd.arg |= (func_num & 0x7) << 28;
        mmc_misc[sg_count].mmc_cmd.arg |= 1 << 27;
        mmc_misc[sg_count].mmc_cmd.arg |= SDIO_OPMODE_FIXED << 26;
        mmc_misc[sg_count].mmc_cmd.arg |= (packet_addr & 0x1FFFF) << 9;
        mmc_misc[sg_count].mmc_cmd.arg |= mmc_misc[sg_count].mmc_dat.blocks & 0x1FF;
        mmc_misc[sg_count].mmc_cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

        mmc_misc[sg_count].mmc_req.cmd = &mmc_misc[sg_count].mmc_cmd;
        mmc_misc[sg_count].mmc_req.data = &mmc_misc[sg_count].mmc_dat;

        sg_count++;
    }

    sdio_claim_host(func);
    mmc_set_data_timeout(&mmc_misc[i].mmc_dat, func->card);
    for (i = 0; i < sg_count; i++) {
        mmc_wait_for_req(func->card->host, &mmc_misc[i].mmc_req);

        if (mmc_misc[i].mmc_cmd.error || mmc_misc[i].mmc_dat.error) {
            AML_ERR("mmc_cmd error: %d; mmc_data error: %d\n", mmc_misc[i].mmc_cmd.error, mmc_misc[i].mmc_dat.error);
            result = mmc_misc[i].mmc_cmd.error ? mmc_misc[i].mmc_cmd.error : mmc_misc[i].mmc_dat.error;
            break;
        }
    }
    sdio_release_host(func);

    scat_req->free = true;
    scat_req->scat_count = 0;
    scat_req->len = 0;
    scat_req->addr = 0;
    memset(scat_req->sgentries, 0, MAX_SG_ENTRIES * sizeof(struct scatterlist));

    return result;
}

struct amlw_hif_scatter_req *aml_sdio_scatter_req_get(struct aml_hwif_sdio *hif_sdio)
{
    struct amlw_hif_scatter_req *scat_req = NULL;

    BUG_ON(!hif_sdio);

    scat_req = hif_sdio->scat_req;

    if (scat_req->free)
    {
        scat_req->free = false;
    }
    else if (scat_req->scat_count != 0) // get scat_req, but not build scatter list
    {
        scat_req = NULL;
    }

    return scat_req;
}

static int amlw_sdio_alloc_prep_scat_req(struct aml_hwif_sdio *hif_sdio)
{
    struct amlw_hif_scatter_req * scat_req = NULL;

    if (!hif_sdio) {
        AML_ERR("hif_sdio is NULL!\n");
        return 1;
    }

    /* allocate the scatter request */
    scat_req = ZMALLOC(sizeof(struct amlw_hif_scatter_req), "sdio_write", GFP_KERNEL | GFP_DMA);
    if (scat_req == NULL)
    {
        AML_ERR("[sdio sg alloc_scat_req]: no mem\n");
        return 1;
    }

    scat_req->free = true;
    hif_sdio->scat_req = scat_req;

    return 0;
}

int aml_sdio_enable_scatter(struct aml_hwif_sdio *hif_sdio)
{
    int ret;

    BUG_ON(!hif_sdio);

    if (hif_sdio->scatter_enabled)
        return 0;

    // TODO : getting hw_config to configure scatter number;

    hif_sdio->scatter_enabled = true;

    ret = amlw_sdio_alloc_prep_scat_req(hif_sdio);
    return ret;
}

int aml_sdio_scat_rw(struct scatterlist *sg_list, unsigned int sg_num, unsigned int blkcnt,
        unsigned char func_num, unsigned int addr, unsigned char write)
{
    struct mmc_request mmc_req;
    struct mmc_command mmc_cmd;
    struct mmc_data    mmc_dat;
    struct sdio_func *func = aml_priv_to_func(func_num);
    int ret = 0;

    AML_BT_WIFI_MUTEX_ON();
    memset(&mmc_req, 0, sizeof(struct mmc_request));
    memset(&mmc_cmd, 0, sizeof(struct mmc_command));
    memset(&mmc_dat, 0, sizeof(struct mmc_data));

    mmc_dat.sg     = sg_list;
    mmc_dat.sg_len = sg_num;
    mmc_dat.blksz  = FUNC4_BLKSIZE;
    mmc_dat.blocks = blkcnt;
    mmc_dat.flags  = write ? MMC_DATA_WRITE : MMC_DATA_READ;

    mmc_cmd.opcode = SD_IO_RW_EXTENDED;
    /* coverity[overflow_const]*/
    mmc_cmd.arg    = write ? 1 << 31 : 0;
    mmc_cmd.arg   |= (func_num & 0x7) << 28;
    mmc_cmd.arg   |= 1 << 27;	/* block basic */
    mmc_cmd.arg   |= 0 << 26;	/* 1 << 26;*/   	/*0 fix address */
    mmc_cmd.arg   |= (addr & 0x1ffff)<< 9;
    mmc_cmd.arg   |= blkcnt & 0x1ff;
    mmc_cmd.flags  = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

    mmc_req.cmd = &mmc_cmd;
    mmc_req.data = &mmc_dat;

    sdio_claim_host(func);
    mmc_set_data_timeout(&mmc_dat, func->card);
    mmc_wait_for_req(func->card->host, &mmc_req);
    sdio_release_host(func);

    if (mmc_cmd.error || mmc_dat.error) {
        AML_ERR("ERROR CMD53 %s cmd_error = %d data_error=%d\n",
               write ? "write" : "read", mmc_cmd.error, mmc_dat.error);
        ret  = mmc_cmd.error;
    }

    AML_BT_WIFI_MUTEX_OFF();
    return ret;
}

void aml_sdio_cleanup_scatter(struct aml_hwif_sdio *hif_sdio)
{
    AML_FN_ENTRY();

    BUG_ON(!hif_sdio);

    if (!hif_sdio->scatter_enabled)
        return;

    hif_sdio->scatter_enabled = false;

    /* empty the free list */
    FREE(hif_sdio->scat_req, "sdio_write");
    AML_FN_EXIT();

    return;
}

extern int aml_sdio_suspend(unsigned int suspend_enable);

void aml_sdio_init_w2_ops(void)
{
    struct aml_hif_sdio_ops* ops = &g_hif_sdio_ops;
    //cmd52 func0 operation func, read/write self define domain reg, no need to set base addr
    ops->hi_self_define_domain_func0_write8 = aml_sdio_self_define_domain_func0_write8;
    ops->hi_self_define_domain_func0_read8 = aml_sdio_self_define_domain_func0_read8;

    //cmd52 func1 operation func, read/write self define domain reg, no need to set base addr
    ops->hi_self_define_domain_write8 = aml_sdio_self_define_domain_write8;
    ops->hi_self_define_domain_read8 = aml_sdio_self_define_domain_read8;
    ops->hi_self_define_domain_write32 = aml_sdio_self_define_domain_write32;
    ops->hi_self_define_domain_read32 = aml_sdio_self_define_domain_read32;

    //func2 operation func, need to set base addr firstly
    ops->hi_random_word_write = aml_sdio_random_word_write;
    ops->hi_random_word_read = aml_sdio_random_word_read;
    ops->hi_random_ram_write = aml_sdio_random_ram_write;
    ops->hi_random_ram_read = aml_sdio_random_ram_read;

    //func3 sram operation func
    ops->hi_sram_word_write = aml_sdio_sram_word_write;
    ops->hi_sram_word_read = aml_sdio_sram_word_read;
    ops->hi_sram_write = aml_sdio_sram_write;
    ops->hi_sram_read = aml_sdio_sram_read;

    //func4 tx buffer
    ops->hi_tx_buffer_write = aml_sdio_tx_buffer_write;
    ops->hi_tx_buffer_read = aml_sdio_tx_buffer_read;

    //func5 rx desc
    ops->hi_desc_read = aml_sdio_desc_read;

    //func6, rx buffer read func
    ops->hi_rx_buffer_read = aml_sdio_rx_buffer_read;

    //for scatter list
    ops->hi_enable_scat = aml_sdio_enable_scatter;
    ops->hi_cleanup_scat = aml_sdio_cleanup_scatter;
    ops->hi_get_scatreq = aml_sdio_scatter_req_get;
    ops->hi_send_frame = aml_sdio_scat_req_rw;
    ops->hi_recv_frame = aml_sdio_scat_req_rx_read;

    //sdio func7 for bt
    ops->bt_hi_write_sram = aml_bt_sdio_write_sram;
    ops->bt_hi_read_sram = aml_bt_sdio_read_sram;
    ops->bt_hi_write_word = aml_bt_hi_write_word;
    ops->bt_hi_read_word = aml_bt_hi_read_word;

    //for suspend & resume
    ops->hif_suspend = aml_sdio_suspend;
    g_sdio_after_porbe = 1;

    // check and wake firstly.
    host_wake_req = NULL;
    host_suspend_req = NULL;
}

void aml_sdio_init_base_addr(void)
{
    g_func_kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_BUS, PREALLOC_BUF_BUS_SIZE);
    if (!g_func_kmalloc_buf) {
         AML_ERR(">>>sdio kmalloc failed!");
    }

    //func3, config sram base addr
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC3_BADDR_A, MAC_SRAM_BASE);

    //func4, config tx buffer base addr
    tx_buffer_base_addr = (TXBUF_START_ADDR);
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC4_BADDR_A, tx_buffer_base_addr);

    //func5, rxdesc base addr
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC5_BADDR_A, RG_WIFI_IF_FW2HST_IRQ_CFG);

    //func6, rx buffer base addr
    rx_buffer_base_addr = (RXBUF_START_ADDR);
    aml_sdio_self_define_domain_write32(RG_SCFG_FUNC6_BADDR_A, rx_buffer_base_addr);
}



/*set_wifi_bt_sdio_driver_bit() is used to determine whether to unregister sdio power driver.
  *Only when g_sdio_wifi_bt_alive is 0, then call aml_sdio_exit().
*/


EXPORT_SYMBOL(g_hwif_rx_sdio);
EXPORT_SYMBOL(g_hif_sdio_ops);



void aml_sdio_calibration(void)
{
    struct aml_hif_sdio_ops* hif_ops = &g_hif_sdio_ops;
    int err;
    unsigned char i, j, k, l;
    unsigned char step;

    step = 4;
    hif_ops->hi_self_define_domain_write8(0x2c0, 0);
    for (i = 0; i < 32; i += step) {
        hif_ops->hi_self_define_domain_write8(0x2c2, i);

        for (j = 0; j < 32; j += step) {
            hif_ops->hi_self_define_domain_write8(0x2c3, j);

            for (k = 0; k < 32; k += step) {
                hif_ops->hi_self_define_domain_write8(0x2c4, k);

                for (l = 0; l < 32; l += step) {
                    hif_ops->hi_self_define_domain_write8(0x2c5, l);

                    //msleep(3000);
                    err = hif_ops->hi_self_define_domain_write32(RG_SCFG_FUNC2_BADDR_A, l);

                    if (err) {
                        //msleep(3000);
                        hif_ops->hi_self_define_domain_write8(SDIO_CCCR_IOABORT, 0x1);
                        //AML_INFO(" error: i:%d, j:%d, k:%d, l:%d\n", i, j, k, l);

                    } else {
                        AML_ERR(" right, use this config: i:%d, j:%d, k:%d, l:%d\n", i, j, k, l);
                        return;
                    }
                }
            }
        }
    }
    AML_ERR("error: i:%d; j:%d, k:%d, l:%d\n", i, j, k, l);

    hif_ops->hi_self_define_domain_write8(0x2c2, 0);
    hif_ops->hi_self_define_domain_write8(0x2c3, 0);
    hif_ops->hi_self_define_domain_write8(0x2c4, 0);
    hif_ops->hi_self_define_domain_write8(0x2c5, 0);
}

void wifi_cpu_clk_switch(unsigned int clk_cfg)
{
    struct aml_hif_sdio_ops *hif_ops = &g_hif_sdio_ops;
    hif_ops->hi_random_word_write(RG_INTF_CPU_CLK, clk_cfg);

    AML_INFO("cpu_clk_reg=0x%08x\n", hif_ops->hi_random_word_read(RG_INTF_CPU_CLK));
}

#ifdef ICCM_CHECK
extern unsigned char buf_iccm_rd[ICCM_BUFFER_RD_LEN];
#endif

unsigned char aml_download_wifi_fw_img(char *firmware_filename)
{
    unsigned int offset_base = 0;
    size_t databyte = 0;
    int i = 0, err = 0;
    unsigned int offset = 0;
    //unsigned int rom_len = 0;
    unsigned int tmp_val = 0;
    unsigned int len = ICCM_RAM_LEN;
    char tmp_buf[9] = {0};
    unsigned char *src = NULL;
    unsigned char *kmalloc_buf = NULL;
    const struct firmware *fw = NULL;
    struct aml_hif_sdio_ops *hif_ops = &g_hif_sdio_ops;
    struct sdio_func *func = aml_priv_to_func(SDIO_FUNC7);
    unsigned int fw_info_len = 0;
    unsigned char fw_branch_len = 0;
    unsigned char fw_author_len = 0;
    unsigned char fw_date_len = 0;

    AML_FN_ENTRY();
    err = request_firmware(&fw, firmware_filename, &func->dev);
    if (err) {
        AML_ERR("request firmware fail!\n");
        return err;
    }

    src = (unsigned char *)fw->data + (offset / 4) * BYTE_IN_LINE;
    kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len);
    if (!kmalloc_buf) {
        AML_ERR("kmalloc buf fail\n");
        release_firmware(fw);
        return -ENOMEM;
    }

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

#ifdef EFUSE_ENABLE
    efuse_init();
    AML_INFO("called efuse init\n");
#endif

    AML_INFO("img len 0x%x, start download fw\n", len);
    do {
        databyte = (len > SRAM_MAX_LEN) ? SRAM_MAX_LEN : len;

        hif_ops->hi_random_ram_write(kmalloc_buf + offset_base,
            (unsigned char *)(SYS_TYPE)(MAC_ICCM_AHB_BASE + offset_base + ICCM_ROM_LEN), databyte);

        offset_base += databyte;
        len -= databyte;
    } while(len > 0);

#ifdef ICCM_CHECK
    offset_base =0;
    len = ICCM_CHECK_LEN;

    //host iccm ram read
    do {
        databyte = (len > SRAM_MAX_LEN) ? SRAM_MAX_LEN : len;

        hif_ops->hi_random_ram_read(buf_iccm_rd + offset_base,
            (unsigned char*)(SYS_TYPE)(MAC_ICCM_AHB_BASE + offset_base + ICCM_ROM_LEN), databyte);

        offset_base += databyte;
        len -= databyte;
    } while(len > 0);

    if (memcmp(buf_iccm_rd, kmalloc_buf, ICCM_CHECK_LEN)) {
        AML_ERR("Host HAL: write ICCM ERROR!!!! \n");
        release_firmware(fw);
        return false;

    } else {
        AML_INFO("Host HAL: write ICCM SUCCESS!!!! \n");
    }
#endif

    /* Starting download DCCM */
    src = (unsigned char *)fw->data + (ICCM_ALL_LEN / 4) * BYTE_IN_LINE;
    len = DCCM_ALL_LEN;
    offset_base = 0;

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    AML_INFO("dccm img len 0x%x, start download dccm\n", len);
    do {
        databyte = (len > SRAM_MAX_LEN) ? SRAM_MAX_LEN : len;

        hif_ops->hi_random_ram_write(kmalloc_buf + offset_base,
            (unsigned char*)(SYS_TYPE)(MAC_DCCM_AHB_BASE + offset_base), databyte);

        offset_base += databyte;
        len -= databyte;
    } while(len > 0);


#if 1
    len = DCCM_CHECK_LEN;
    offset_base = 0;

    //host iccm ram read
    do {
        databyte = (len > SRAM_MAX_LEN) ? SRAM_MAX_LEN : len;

        hif_ops->hi_random_ram_read(buf_iccm_rd + offset_base,
            (unsigned char*)(SYS_TYPE)(MAC_DCCM_AHB_BASE + offset_base), databyte);

        offset_base += databyte;
        len -= databyte;
    } while(len > 0);

    if (memcmp(buf_iccm_rd, kmalloc_buf, DCCM_CHECK_LEN)) {
        AML_ERR("Host HAL: write DCCM ERROR!!!! \n");
        release_firmware(fw);
        return false;

    } else {
        AML_INFO("Host HAL: write DCCM SUCCESS!!!! \n");
    }
#endif

    memset(kmalloc_buf, 0, len);
    offset = ICCM_ALL_LEN - WIFI_SUSPEND_CODE_LEN - WIFI_CMD_CODE_LEN;
    len = WIFI_SUSPEND_CODE_LEN;
    src = (unsigned char *)fw->data + (offset / 4) * BYTE_IN_LINE;

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    AML_INFO("save rf fw :%08x!\n", *(unsigned int *)&kmalloc_buf[0]);

    src = (unsigned char *)fw->data + ((ICCM_ALL_LEN + DCCM_ALL_LEN) / 4) * BYTE_IN_LINE;
    kmalloc_buf += len;
    len += (HOST_CMD_COUNT * HOST_CMD_SIZE) + 8;

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            AML_INFO("download fail, i:%d, len:%d\n", i, len);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    kmalloc_buf += len - 4;
    fw_info_len = *(unsigned int *)kmalloc_buf;
    fw_branch_len = (fw_info_len >> 8) & 0xff;
    fw_author_len = (fw_info_len >> 16) & 0xff;
    fw_date_len = (fw_info_len >> 24) & 0xff;
    //AML_INFO("fw_info_len:%02x, fw_branch_len:%02x, fw_author_len:%02x, fw_date_len:%02x\n",
    //    fw_info_len, fw_branch_len, fw_author_len, fw_date_len);

    fw_info_len = fw_branch_len + fw_author_len + fw_date_len + 2;
    src = (unsigned char *)fw->data + ((ICCM_ALL_LEN + DCCM_ALL_LEN + len) / 4) * BYTE_IN_LINE;
    kmalloc_buf += 4;
    strncpy(kmalloc_buf, (char *)src, fw_info_len);

    release_firmware(fw);
    AML_INFO("Download fw finished len:%d, fw_info_len:%d, fw_info:%s\n", len, fw_info_len, kmalloc_buf);

    return true;
}

unsigned char aml_sdio_download_suspend_or_rf_fw(unsigned char fw_type, unsigned int fw_download_timeout)
{
    unsigned int len = WIFI_SUSPEND_CODE_LEN;
    unsigned char *kmalloc_buf = NULL;
    unsigned int base_addr = WIFI_SUSPEND_CODE_ADDR;
    struct aml_hif_sdio_ops *hif_ops = &g_hif_sdio_ops;

    kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len);
    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail\n");
        return -ENOMEM;
    }

    if (fw_type)
        kmalloc_buf += len;

    //test kmalloc buf content
    AML_INFO("start fw:%d download, data:%08x, timeout:%d\n", fw_type, *(unsigned int *)&kmalloc_buf[0], fw_download_timeout);
    hif_ops->hi_random_ram_write(kmalloc_buf, (unsigned char*)(SYS_TYPE)base_addr, len);

#if 0
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
    hif_ops->hi_random_ram_read(buf_iccm_rd, (unsigned char*)(SYS_TYPE)base_addr, len);
    if (memcmp(buf_iccm_rd, kmalloc_buf, len - 8)) {
        if (fw_type) {
            AML_ERR("suspend fw download fail!\n");
        } else {
            AML_ERR("rf fw download fail!\n");
        }
        //return -1;
    } else {
        if (fw_type) {
            AML_INFO("suspend fw download success!\n");
        } else {
            AML_INFO("rf fw download success!\n");
        }
    }
#endif

    return 0;
}

unsigned char aml_sdio_download_host_cmd_fw(unsigned char cmd_index)
{
    unsigned int len = HOST_CMD_SIZE;
    unsigned char *kmalloc_buf = NULL;
    unsigned int base_addr = HOST_CMD_CODE_ADDR;
    struct aml_hif_sdio_ops *hif_ops = &g_hif_sdio_ops;

    kmalloc_buf = ((unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len) + (2 * WIFI_SUSPEND_CODE_LEN));
    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail\n");
        return 0;
    }

    kmalloc_buf += cmd_index * len;

    //test kmalloc buf content
    //AML_INFO("start host cmd download, kmalloc buf:%08x, data:%08x, cmd_index:%d\n",
    //    kmalloc_buf, *(unsigned int *)&kmalloc_buf[0], cmd_index);
    hif_ops->hi_random_ram_write(kmalloc_buf, (unsigned char*)(SYS_TYPE)base_addr, len);

#if 0
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
    hif_ops->hi_random_ram_read(buf_iccm_rd, (unsigned char*)(SYS_TYPE)base_addr, len);
    if (memcmp(buf_iccm_rd, kmalloc_buf, len - 8)) {
        AML_ERR("host cmd download fail!\n");
        //return -1;
    } else {
        AML_INFO("host cmd download success!\n");
    }
#endif

    return 0;
}


EXPORT_SYMBOL(aml_sdio_calibration);
EXPORT_SYMBOL(aml_download_wifi_fw_img);
EXPORT_SYMBOL(aml_sdio_download_suspend_or_rf_fw);
EXPORT_SYMBOL(aml_sdio_download_host_cmd_fw);

