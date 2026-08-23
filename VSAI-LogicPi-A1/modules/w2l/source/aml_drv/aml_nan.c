/**
 ******************************************************************************
 *
 * @file aml_nan.c
 *
 * @brief nan function definitions
 *
 * Copyright (C) Amlogic 2024-2034
 *
 ******************************************************************************
 */

#include "aml_sha256_i.h"
#include "aml_nan.h"
#include "aml_wq.h"
#include "aml_iwpriv_cmds.h"

static uint32_t crc32_tab[] = {
    0x00000000L, 0x77073096L, 0xEE0E612CL, 0x990951BAL,
    0x076DC419L, 0x706AF48FL, 0xE963A535L, 0x9E6495A3L,
    0x0EDB8832L, 0x79DCB8A4L, 0xE0D5E91EL, 0x97D2D988L,
    0x09B64C2BL, 0x7EB17CBDL, 0xE7B82D07L, 0x90BF1D91L,
    0x1DB71064L, 0x6AB020F2L, 0xF3B97148L, 0x84BE41DEL,
    0x1ADAD47DL, 0x6DDDE4EBL, 0xF4D4B551L, 0x83D385C7L,
    0x136C9856L, 0x646BA8C0L, 0xFD62F97AL, 0x8A65C9ECL,
    0x14015C4FL, 0x63066CD9L, 0xFA0F3D63L, 0x8D080DF5L,
    0x3B6E20C8L, 0x4C69105EL, 0xD56041E4L, 0xA2677172L,
    0x3C03E4D1L, 0x4B04D447L, 0xD20D85FDL, 0xA50AB56BL,
    0x35B5A8FAL, 0x42B2986CL, 0xDBBBC9D6L, 0xACBCF940L,
    0x32D86CE3L, 0x45DF5C75L, 0xDCD60DCFL, 0xABD13D59L,
    0x26D930ACL, 0x51DE003AL, 0xC8D75180L, 0xBFD06116L,
    0x21B4F4B5L, 0x56B3C423L, 0xCFBA9599L, 0xB8BDA50FL,
    0x2802B89EL, 0x5F058808L, 0xC60CD9B2L, 0xB10BE924L,
    0x2F6F7C87L, 0x58684C11L, 0xC1611DABL, 0xB6662D3DL,
    0x76DC4190L, 0x01DB7106L, 0x98D220BCL, 0xEFD5102AL,
    0x71B18589L, 0x06B6B51FL, 0x9FBFE4A5L, 0xE8B8D433L,
    0x7807C9A2L, 0x0F00F934L, 0x9609A88EL, 0xE10E9818L,
    0x7F6A0DBBL, 0x086D3D2DL, 0x91646C97L, 0xE6635C01L,
    0x6B6B51F4L, 0x1C6C6162L, 0x856530D8L, 0xF262004EL,
    0x6C0695EDL, 0x1B01A57BL, 0x8208F4C1L, 0xF50FC457L,
    0x65B0D9C6L, 0x12B7E950L, 0x8BBEB8EAL, 0xFCB9887CL,
    0x62DD1DDFL, 0x15DA2D49L, 0x8CD37CF3L, 0xFBD44C65L,
    0x4DB26158L, 0x3AB551CEL, 0xA3BC0074L, 0xD4BB30E2L,
    0x4ADFA541L, 0x3DD895D7L, 0xA4D1C46DL, 0xD3D6F4FBL,
    0x4369E96AL, 0x346ED9FCL, 0xAD678846L, 0xDA60B8D0L,
    0x44042D73L, 0x33031DE5L, 0xAA0A4C5FL, 0xDD0D7CC9L,
    0x5005713CL, 0x270241AAL, 0xBE0B1010L, 0xC90C2086L,
    0x5768B525L, 0x206F85B3L, 0xB966D409L, 0xCE61E49FL,
    0x5EDEF90EL, 0x29D9C998L, 0xB0D09822L, 0xC7D7A8B4L,
    0x59B33D17L, 0x2EB40D81L, 0xB7BD5C3BL, 0xC0BA6CADL,
    0xEDB88320L, 0x9ABFB3B6L, 0x03B6E20CL, 0x74B1D29AL,
    0xEAD54739L, 0x9DD277AFL, 0x04DB2615L, 0x73DC1683L,
    0xE3630B12L, 0x94643B84L, 0x0D6D6A3EL, 0x7A6A5AA8L,
    0xE40ECF0BL, 0x9309FF9DL, 0x0A00AE27L, 0x7D079EB1L,
    0xF00F9344L, 0x8708A3D2L, 0x1E01F268L, 0x6906C2FEL,
    0xF762575DL, 0x806567CBL, 0x196C3671L, 0x6E6B06E7L,
    0xFED41B76L, 0x89D32BE0L, 0x10DA7A5AL, 0x67DD4ACCL,
    0xF9B9DF6FL, 0x8EBEEFF9L, 0x17B7BE43L, 0x60B08ED5L,
    0xD6D6A3E8L, 0xA1D1937EL, 0x38D8C2C4L, 0x4FDFF252L,
    0xD1BB67F1L, 0xA6BC5767L, 0x3FB506DDL, 0x48B2364BL,
    0xD80D2BDAL, 0xAF0A1B4CL, 0x36034AF6L, 0x41047A60L,
    0xDF60EFC3L, 0xA867DF55L, 0x316E8EEFL, 0x4669BE79L,
    0xCB61B38CL, 0xBC66831AL, 0x256FD2A0L, 0x5268E236L,
    0xCC0C7795L, 0xBB0B4703L, 0x220216B9L, 0x5505262FL,
    0xC5BA3BBEL, 0xB2BD0B28L, 0x2BB45A92L, 0x5CB36A04L,
    0xC2D7FFA7L, 0xB5D0CF31L, 0x2CD99E8BL, 0x5BDEAE1DL,
    0x9B64C2B0L, 0xEC63F226L, 0x756AA39CL, 0x026D930AL,
    0x9C0906A9L, 0xEB0E363FL, 0x72076785L, 0x05005713L,
    0x95BF4A82L, 0xE2B87A14L, 0x7BB12BAEL, 0x0CB61B38L,
    0x92D28E9BL, 0xE5D5BE0DL, 0x7CDCEFB7L, 0x0BDBDF21L,
    0x86D3D2D4L, 0xF1D4E242L, 0x68DDB3F8L, 0x1FDA836EL,
    0x81BE16CDL, 0xF6B9265BL, 0x6FB077E1L, 0x18B74777L,
    0x88085AE6L, 0xFF0F6A70L, 0x66063BCAL, 0x11010B5CL,
    0x8F659EFFL, 0xF862AE69L, 0x616BFFD3L, 0x166CCF45L,
    0xA00AE278L, 0xD70DD2EEL, 0x4E048354L, 0x3903B3C2L,
    0xA7672661L, 0xD06016F7L, 0x4969474DL, 0x3E6E77DBL,
    0xAED16A4AL, 0xD9D65ADCL, 0x40DF0B66L, 0x37D83BF0L,
    0xA9BCAE53L, 0xDEBB9EC5L, 0x47B2CF7FL, 0x30B5FFE9L,
    0xBDBDF21CL, 0xCABAC28AL, 0x53B39330L, 0x24B4A3A6L,
    0xBAD03605L, 0xCDD70693L, 0x54DE5729L, 0x23D967BFL,
    0xB3667A2EL, 0xC4614AB8L, 0x5D681B02L, 0x2A6F2B94L,
    0xB40BBE37L, 0xC30C8EA1L, 0x5A05DF1BL, 0x2D02EF8DL
};

static nan_ctx_t s_nan_ctx = {0};
extern char **aml_cmd_char_phrase(char sep, const char *str, int *size);

static int hex2num(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

/**
 * hwaddr_aton2 - Convert ASCII string to MAC address (in any known format)
 * @txt: MAC address as a string (e.g., 00:11:22:33:44:55 or 0011.2233.4455)
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * Returns: Characters used (> 0) on success, -1 on failure
 */
int hwaddr_aton2(const char *txt, u8 *addr)
{
    int i;
    const char *pos = txt;

    for (i = 0; i < 6; i++) {
        int a, b;

        while (*pos == ':' || *pos == '.' || *pos == '-')
            pos++;

        a = hex2num(*pos++);
        if (a < 0)
            return -1;
        b = hex2num(*pos++);
        if (b < 0)
            return -1;
        *addr++ = (a << 4) | b;
    }

    return pos - txt;
}

void nan_util_dump(uint8_t *msg, uint8_t *content, uint32_t len)
{
    uint8_t aucBuf[16];

    AML_INFO("%s, len:%d\n", msg, len);

    while (len >= 16) {
        AML_INFO("%p: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
               content, content[0], content[1], content[2],
               content[3], content[4], content[5],
               content[6], content[7], content[8],
               content[9], content[10], content[11],
               content[12], content[13], content[14],
               content[15]);

        len -= 16;
        content += 16;
    }

    if (len > 0) {
        memset(aucBuf, 0, 16);
        memcpy(aucBuf, content, len);

        AML_INFO("%p: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
               content, aucBuf[0], aucBuf[1], aucBuf[2], aucBuf[3],
               aucBuf[4], aucBuf[5], aucBuf[6], aucBuf[7], aucBuf[8],
               aucBuf[9], aucBuf[10], aucBuf[11], aucBuf[12],
               aucBuf[13], aucBuf[14], aucBuf[15]);
    }
}

uint8_t aml_nan_get_str_item(const char *varbuf, int len, const char *item, char *item_value, int value_len)
{
    unsigned int n;
    int ret = 0;
    unsigned int pos = 0;
    unsigned int index = 0;

    while (pos < len) {
        index = pos;
        ret = 0;

        while ((varbuf[pos] != 0) && (varbuf[pos] != '=')) {
            if (((pos - index) >= strlen(item)) || (varbuf[pos] != item[pos - index])) {
                ret = 1;
                break;
            }
            else {
                pos++;
            }
        }

        pos++;

        if ((ret == 0) && (strlen(item) == pos - index - 1)) {
            do {
                memset(item_value, 0, sizeof(value_len));
                n = 0;
                while ((varbuf[pos] != 0) && (pos < len)) {
                    item_value[n++] = varbuf[pos++];
                }
            }
            while (varbuf[pos++] == ',');
            return 0;
        }
    }

    return 1;
}

uint8_t aml_nan_get_match_filter_item(char *varbuf, int len, char *item, char *item_value)
{
    unsigned int n;
    char tmpbuf[20];
    char *p = item_value;
    int ret = 0;
    unsigned int pos = 0;
    unsigned int index = 0;
    uint8_t match_filter_len = 0;

    while (pos  < len) {
        index = pos;
        ret = 0;

        while ((varbuf[pos] != 0) && (varbuf[pos] != '=')) {
            if (((pos - index) >= strlen(item)) || (varbuf[pos] != item[pos - index])) {
                ret = 1;
                break;
            }
            else {
                pos++;
            }
        }

        pos++;

        if ((ret == 0) && (strlen(item) == pos - index - 1)) {
            while (varbuf[pos] == ',' || (varbuf[pos] == '<') || (varbuf[pos] == '>') || (varbuf[pos] == ' ')) {
                pos++;
                memset(tmpbuf, 0, sizeof(tmpbuf));
                n = 0;
                while ((varbuf[pos] != 0) && (varbuf[pos] != ',') && (varbuf[pos] != '<') && (varbuf[pos] != '>') && (varbuf[pos] != ' ') && (pos < len)) {
                    tmpbuf[n++] = varbuf[pos++];
                    *p++ = (char)simple_strtol(tmpbuf, NULL, 0);
                    match_filter_len++;
                }
            }

            return match_filter_len;
        }
    }

    return 0;
}

bool aml_nan_is_no_filter(match_filter *mf)
{
    return (mf->match_filter_len == 0 ? true : false);
}

void aml_nan_parse_match_filters(match_filter *mf)
{
    uint8_t fbuf[NAN_WIFI_MAX_FILTER_LEN] = {0};
    uint8_t len = 0;
    uint8_t i = 0;
    uint32_t size = NAN_WIFI_MAX_FILTER_LEN;
    uint32_t res = 0;

    AML_INFO("format <Length, Value> pair:");
    if (aml_nan_is_no_filter(mf))
        AML_INFO("No filters!");

    while (i < mf->match_filter_len) {
        len = mf->match_filter[i++];
        memset(fbuf, 0, NAN_WIFI_MAX_FILTER_LEN);
        res = scnprintf(fbuf, size, "<%d", len);
        for (int j = 0; j < len && i < mf->match_filter_len; j++, i++) {
            res += scnprintf(&fbuf[res], size - res, ", %d", mf->match_filter[i]);
        }
        res += scnprintf(&fbuf[res], size - res, ">\n");
        AML_INFO("%s", fbuf);
    }
}

uint32_t aml_nan_bloom_fliter_crc32(uint32_t crc, const void *buf, size_t size)
{
    const uint8_t *p;
    p = buf;
    while (size--)
        crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return crc;
}

uint16_t aml_nan_bloom_fliter_hash(uint8_t hash_idx, uint8_t *mac_addr, uint8_t m)
{
    uint32_t crc32 = 0;
    uint8_t  buf[HASH_STR_LEN] = {0};

    buf[0] = hash_idx;
    memcpy(buf + 1, mac_addr, 6);
    crc32 = aml_nan_bloom_fliter_crc32(0xFFFFFFFF, buf, HASH_STR_LEN);

    return ((crc32 & 0x0000FFFF) % m);
}

void aml_nan_bloom_filter_add(uint8_t *bloom_filter, uint16_t absBit) {
    uint8_t filter_byte = absBit / 8;
    uint8_t filter_bit = absBit % 8;
    bloom_filter[filter_byte] |= 1 << filter_bit;
}

bool aml_nan_bloom_filter_check(uint8_t *mac_addr,
    uint8_t *bloom_filter, uint8_t func_hash_idx, uint8_t bf_len)
{
    uint16_t absBit = 0;
    uint8_t filter_byte = 0;
    uint8_t filter_bit = 0;

    for (uint8_t j = func_hash_idx; j < func_hash_idx + 4; j++) {
        absBit = aml_nan_bloom_fliter_hash(j, mac_addr, bf_len);
        filter_byte = absBit / 8;
        filter_bit = absBit % 8;
        if (!(bloom_filter[filter_byte] & (1 << filter_bit))) {
            return false;
        }
    }

    return true;
}

uint8_t aml_nan_srf_bloom_filter_build(srf_info *srf)
{
    uint8_t func_hash_idx = 0;
    uint16_t absBit = 0;

    switch (srf->srf_bf_idx) {
        case 0:
            func_hash_idx = 0;
            break;
        case 1:
            func_hash_idx = 4;
            break;
        case 2:
            func_hash_idx = 8;
            break;
        case 3:
            func_hash_idx = 12;
            break;
        default:
            AML_INFO("bloom_filter_idx err bf_idx = %d", srf->srf_bf_idx);
            return 1;
    }

    memset(srf->srf_bf, 0, 32);
    for (uint8_t i = 0; i < srf->srf_num_macs; i++) {
        for (uint8_t j = func_hash_idx; j < func_hash_idx + 4; j++) {
            absBit = aml_nan_bloom_fliter_hash(j, &srf->srf_mac_addresses[i][0], srf->srf_bf_len);
            aml_nan_bloom_filter_add(srf->srf_bf, absBit);
        }
    }

    AML_INFO("bloom filter:");
    for (i = 0; i < (srf->srf_bf_len / 8); i++)
        AML_INFO("%02x, ", srf->srf_bf[i]);

    return 0;
}

uint8_t aml_nan_srf_build(srf_info *srf)
{
    uint8_t ret = 0;

    if (!srf->srf_num_macs) {
        return 1;
    }

    if (srf->srf_type == NAN_SRF_ATTR_BLOOM_FILTER) {
        ret = aml_nan_srf_bloom_filter_build(srf);
    }

    return ret;
}

void aml_nan_parse_srf_param(char *varbuf, int len, subscribe_config *subscribe)
{
    uint8_t srf_mac_item[10] = {0};
    uint8_t mac_str[18] = {0};
    char sep = ':';
    int size = 0;
    char **mac_addr;

    aml_get_s8_item(varbuf, len, "srf_type", &subscribe->srf.srf_type);
    aml_get_s8_item(varbuf, len, "srf_include", &subscribe->srf.srf_include);
    aml_get_s8_item(varbuf, len, "srf_bf_len", &subscribe->srf.srf_bf_len);
    aml_get_s8_item(varbuf, len, "srf_bf_idx", &subscribe->srf.srf_bf_idx);
    aml_get_s8_item(varbuf, len, "srf_num_macs", &subscribe->srf.srf_num_macs);

    AML_INFO("srf_type=%d\n", subscribe->srf.srf_type);
    AML_INFO("srf_include=%d\n", subscribe->srf.srf_include);
    AML_INFO("srf_bf_len=%d\n", subscribe->srf.srf_bf_len);
    AML_INFO("srf_bf_idx=%d\n", subscribe->srf.srf_bf_idx);
    AML_INFO("srf_num_macs=%d\n", subscribe->srf.srf_num_macs);

    for (uint8_t i = 0; i < subscribe->srf.srf_num_macs; i++) {
        sprintf(srf_mac_item, "srf_mac%d", i);
        aml_nan_get_str_item(varbuf, len, srf_mac_item, &mac_str[0], 18);
        AML_INFO("SRF MAC=%s", mac_str);
        if (!aml_is_valid_mac_addr(mac_str, 17)) {
            mac_addr = aml_cmd_char_phrase(sep, mac_str, &size);
            if (mac_addr) {
                for (uint8_t j = 0; j < MAC_ADDR_LEN; j++) {
                    subscribe->srf.srf_mac_addresses[i][j] = simple_strtoul(mac_addr[j], NULL, 16);
                    kfree(mac_addr[j]);
                }
                kfree(mac_addr);
                AML_INFO("srf_mac_addresses[%d]: "MACSTR"\n", i, MAC2STR(subscribe->srf.srf_mac_addresses[i]));
            }
        }
    }

    aml_nan_srf_build(&subscribe->srf);
}

unsigned char aml_nan_parse_publish_param(char *varbuf, int len, publish_config *publish)
{
    uint8_t count = 0;
    uint8_t mf_len = 0;

    aml_get_s8_item(varbuf, len, "publish_id", &publish->publish_id);
    aml_get_s8_item(varbuf, len, "publish_type", &publish->publish_type);
    aml_nan_get_str_item(varbuf, len, "service_name", &publish->service_name[0], NAN_WIFI_MAX_SVC_NAME_LEN);
    aml_nan_get_str_item(varbuf, len, "service_specific_info", &publish->service_specific_info[0], NAN_WIFI_MAX_SVC_INFO_LEN);

    AML_INFO("publish_id=%d\n", publish->publish_id);
    AML_INFO("publish_type=%d\n", publish->publish_type);
    AML_INFO("service_name=%s\n", publish->service_name);
    AML_INFO("service_specific_info=%s\n", publish->service_specific_info);
    mf_len = aml_nan_get_match_filter_item(varbuf, len, "match_filter_tx", &publish->match_filter_tx.match_filter[0]);
    if (mf_len) {
        AML_INFO("match_filter_tx - len: %d", mf_len);
        publish->match_filter_tx.match_filter_len = mf_len;
        aml_nan_parse_match_filters(&publish->match_filter_tx);
    }
    mf_len = aml_nan_get_match_filter_item(varbuf, len, "match_filter_rx", &publish->match_filter_rx.match_filter[0]);
    if (mf_len) {
        AML_INFO("match_filter_rx - len: %d", mf_len);
        publish->match_filter_rx.match_filter_len = mf_len;
        aml_nan_parse_match_filters(&publish->match_filter_rx);
    }

    return 0;
}

unsigned char aml_nan_parse_subscribe_param(char *varbuf, int len, subscribe_config *subscribe)
{
    uint8_t count = 0;
    uint8_t mf_len = 0;

    aml_get_s8_item(varbuf, len, "sublish_id", &subscribe->subscribe_id);
    aml_get_s8_item(varbuf, len, "subscribe_type", &subscribe->subscribe_type);
    aml_nan_get_str_item(varbuf, len, "service_name", &subscribe->service_name[0], NAN_WIFI_MAX_SVC_NAME_LEN);
    aml_nan_get_str_item(varbuf, len, "service_specific_info", &subscribe->service_specific_info[0], NAN_WIFI_MAX_SVC_INFO_LEN);

    AML_INFO("subscribe_id=%d\n", subscribe->subscribe_id);
    AML_INFO("subscribe_type=%d\n", subscribe->subscribe_type);
    AML_INFO("service_name=%s\n", subscribe->service_name);
    AML_INFO("service_specific_info=%s\n", subscribe->service_specific_info);
    mf_len = aml_nan_get_match_filter_item(varbuf, len, "match_filter_tx", &subscribe->match_filter_tx.match_filter[0]);
    if (mf_len) {
        AML_INFO("match_filter_tx - len: %d", mf_len);
        subscribe->match_filter_tx.match_filter_len = mf_len;
        aml_nan_parse_match_filters(&subscribe->match_filter_tx);
    }
    mf_len = aml_nan_get_match_filter_item(varbuf, len, "match_filter_rx", &subscribe->match_filter_rx.match_filter[0]);
    if (mf_len) {
        AML_INFO("match_filter_rx - len: %d", mf_len);
        subscribe->match_filter_rx.match_filter_len = mf_len;
        aml_nan_parse_match_filters(&subscribe->match_filter_rx);
    }

    aml_nan_parse_srf_param(varbuf, len, subscribe);

    return 0;
}

int aml_nan_get_publish_param(struct aml_hw *aml_hw, publish_config *pub_conf)
{
    const struct firmware *cfg_fw = NULL;
    int ret = 0, len = 0;

    ret = request_firmware(&cfg_fw, AML_NAN_PUB_PATH, aml_hw->dev);
    if (ret) {
        AML_INFO("failed to get %s (%d)", AML_NAN_PUB_PATH, ret);
        return ret;
    }

    len = aml_process_cali_content((char *)cfg_fw->data, cfg_fw->size);
    aml_nan_parse_publish_param((char *)cfg_fw->data, len, pub_conf);
    release_firmware(cfg_fw);

    return ret;
}

int aml_nan_get_subscribe_param(struct aml_hw *aml_hw, subscribe_config *sub_conf)
{
    const struct firmware *cfg_fw = NULL;
    int ret = 0, len = 0;

    ret = request_firmware(&cfg_fw, AML_NAN_SUB_PATH, aml_hw->dev);
    if (ret != 0) {
        AML_INFO("failed to get %s (%d)", AML_NAN_SUB_PATH, ret);
        return ret;
    }

    len = aml_process_cali_content((char *)cfg_fw->data, cfg_fw->size);
    aml_nan_parse_subscribe_param((char *)cfg_fw->data, len, sub_conf);
    release_firmware(cfg_fw);

    return ret;
}

static void aml_nan_get_service_name_hash(uint8_t service_name_hash[], char svc_name[], int svc_name_len)
{
    char aucServiceName[256] = {0};
    struct sha256_state r_SHA_256_state = {0};
    uint8_t auc_tk[32] = {0};
    uint32_t u4Idx = 0;

    memcpy(aucServiceName, svc_name, svc_name_len);
    for (u4Idx = 0; u4Idx < strlen(aucServiceName); u4Idx++) {
        if ((aucServiceName[u4Idx] >= 'A') &&
            (aucServiceName[u4Idx] <= 'Z'))
            aucServiceName[u4Idx] = aucServiceName[u4Idx] + 32;
    }
    sha256_init(&r_SHA_256_state);
    sha256_process(&r_SHA_256_state, aucServiceName, strlen(aucServiceName));
    sha256_done(&r_SHA_256_state, auc_tk);
    memcpy(service_name_hash, auc_tk, NAN_SERVICE_HASH_LENGTH);
    #ifdef NAN_DEBUG
    nan_util_dump("service hash", auc_tk, NAN_SERVICE_HASH_LENGTH);
    #endif
}

void aml_nan_reset_svc(uint8_t svc_id, bool reset_all)
{
    struct own_svc_info *own_svc = NULL;
    struct peer_svc_info_list *peer_svc = NULL;
    uint8_t idx = 0;

    if (svc_id == 0 && !reset_all) {
        return;
    }

    while (idx < NAN_WIFI_NAN_MAX_SVC_SUPPORTED) {
        own_svc = &s_nan_ctx.own_svc[idx++];
        if (reset_all || (svc_id && own_svc->svc_id == svc_id)) {
            spin_lock_bh(&s_nan_ctx.peer_list_lock);
            while (!list_empty(&own_svc->peer_list)) {
                peer_svc = list_first_entry(&own_svc->peer_list, struct peer_svc_info_list, list);
                if (peer_svc) {
                    list_del(&peer_svc->list);
                    kfree(peer_svc);
                }
            }
            spin_unlock_bh(&s_nan_ctx.peer_list_lock);
            memset(own_svc, 0, sizeof(struct own_svc_info));
        }
    }
}

void aml_nan_init()
{
    spin_lock_init(&s_nan_ctx.peer_list_lock);
    INIT_LIST_HEAD(&(s_nan_ctx.own_svc[0].peer_list));
    INIT_LIST_HEAD(&(s_nan_ctx.own_svc[1].peer_list));
    s_nan_ctx.instance_id = 0;
    s_nan_ctx.nan_svc_num = 0;
    aml_nan_reset_svc(0, true);
}

static void aml_nan_record_own_svc(uint8_t id, uint8_t type,
    const char svc_name[], match_filter *mf_tx, match_filter *mf_rx)
{
    struct own_svc_info *p_svc = NULL;

    for (int i = 0; i < NAN_WIFI_NAN_MAX_SVC_SUPPORTED; i++) {
        if (s_nan_ctx.own_svc[i].svc_id == 0) {
            p_svc = &s_nan_ctx.own_svc[i];
            break;
        }
    }

    if (!p_svc) {
        return;
    }

    p_svc->svc_id = id;
    p_svc->type = type;
    memcpy(p_svc->svc_name, svc_name, NAN_WIFI_MAX_SVC_NAME_LEN);
    if (mf_tx->match_filter_len) {
        p_svc->mf_tx.match_filter_len = mf_tx->match_filter_len;
        memcpy(p_svc->mf_tx.match_filter, mf_tx->match_filter, mf_tx->match_filter_len);
    }
    if (mf_rx->match_filter_len) {
        p_svc->mf_rx.match_filter_len = mf_rx->match_filter_len;
        memcpy(p_svc->mf_rx.match_filter, mf_rx->match_filter, mf_rx->match_filter_len);
        AML_INFO("store rx_mf:\n");
        aml_nan_parse_match_filters(&p_svc->mf_rx);
    }

    INIT_LIST_HEAD(&(p_svc->peer_list));
}

struct own_svc_info *aml_nan_find_own_svc(uint8_t svc_id)
{
    struct own_svc_info *p_svc = NULL;

    if (svc_id == 0) {
        AML_INFO("Service id cannot be 0!");
        return NULL;
    }

    for (int i = 0; i < NAN_WIFI_NAN_MAX_SVC_SUPPORTED; i++) {
        if (s_nan_ctx.own_svc[i].svc_id == svc_id) {
            p_svc = &s_nan_ctx.own_svc[i];
            break;
        }
    }

    return p_svc;
}

struct peer_svc_info_list *aml_nan_find_peer_svc(uint8_t own_svc_id,
    uint8_t peer_svc_id, uint8_t peer_nmi[])
{
    struct peer_svc_info_list *peer_svc = NULL;
    struct peer_svc_info_list *temp = NULL;
    struct own_svc_info *own_svc = NULL;
    int idx = 0;

    if (own_svc_id) {
        own_svc = aml_nan_find_own_svc(own_svc_id);
        if (!own_svc) {
            AML_INFO("Cannot find own service with svc_id %d!", own_svc_id);
            return NULL;
        }
    }

    spin_lock_bh(&s_nan_ctx.peer_list_lock);
    if (!list_empty(&own_svc->peer_list)) {
        list_for_each_entry_safe(peer_svc, temp, &own_svc->peer_list, list) {
            if (peer_svc_id != 0) {
                if (temp->svc_id == peer_svc_id && !memcmp(temp->peer_nmi, peer_nmi, MAC_ADDR_LEN)) {
                    peer_svc = temp;
                    break;
                }
            }
        }
    }
    spin_unlock_bh(&s_nan_ctx.peer_list_lock);

    return peer_svc;
}

bool aml_nan_record_peer_svc(uint8_t own_svc_id, uint8_t peer_svc_id, uint8_t peer_nmi[])
{
    struct own_svc_info *own_svc = NULL;
    struct peer_svc_info_list *peer_svc = NULL;

    own_svc = aml_nan_find_own_svc(own_svc_id);
    if (!own_svc) {
        AML_INFO("Unable to find own service with svc_id %d", own_svc_id);
        return false;
    }
    peer_svc = (struct peer_svc_info *)kzalloc(sizeof(struct peer_svc_info_list), GFP_KERNEL);
    if (!peer_svc) {
        AML_INFO("Allocate Peer Service fail.");
        return false;
    }
    INIT_LIST_HEAD(&peer_svc->list);
    peer_svc->svc_id = peer_svc_id;
    peer_svc->own_svc_id = own_svc_id;
    peer_svc->type = (own_svc->type == NAN_SUBSCRIBE) ? NAN_PUBLISH : NAN_SUBSCRIBE;
    memcpy(peer_svc->peer_nmi, peer_nmi, MAC_ADDR_LEN);

    if (own_svc->num_peer_records >= NAN_MAX_PEERS_RECORD) {
        /* Remove the oldest peer service entry */
        struct peer_svc_info_list *peer_svc_first = NULL;

        spin_lock_bh(&s_nan_ctx.peer_list_lock);
        if (!list_empty(&own_svc->peer_list)) {
            peer_svc_first = list_first_entry(&own_svc->peer_list, struct peer_svc_info_list, list);
            list_del(&peer_svc_first->list);
        }
        spin_unlock_bh(&s_nan_ctx.peer_list_lock);
        kfree(peer_svc_first);
        own_svc->num_peer_records--;
    }
    spin_lock_bh(&s_nan_ctx.peer_list_lock);
    list_add_tail(&peer_svc->list, &own_svc->peer_list);
    spin_unlock_bh(&s_nan_ctx.peer_list_lock);
    own_svc->num_peer_records++;

    return true;
}

uint8_t aml_nan_get_solcoted_pub_cfg(wifi_nan_publish_cfg *publish_req, publish_config *pub_cfg)
{
    if (!publish_req || !pub_cfg) {
        AML_INFO("params error!");
        return 0;
    }

    publish_req->publish_id = pub_cfg->publish_id;
    publish_req->type = pub_cfg->publish_type;
    publish_req->peer_inst_id = pub_cfg->peer_inst_id;
    publish_req->service_name_len = strlen(pub_cfg->service_name);
    memcpy(publish_req->service_name, pub_cfg->service_name, publish_req->service_name_len);
    if (pub_cfg->match_filter_tx.match_filter_len) {
        memcpy(&publish_req->mf, &pub_cfg->match_filter_tx, sizeof(match_filter));
    }
    memcpy(publish_req->service_name_hash, pub_cfg->service_name_hash, NAN_SERVICE_HASH_LENGTH);
    memcpy(publish_req->peer_mac, pub_cfg->peer_mac, MAC_ADDR_LEN);

    return publish_req->publish_id;
}

uint8_t aml_nan_get_unsolcoted_pub_cfg(struct aml_hw *aml_hw,
    wifi_nan_publish_cfg *publish_req, publish_config *pub_cfg)
{
    char aucServiceName[256] = {0};
    struct sha256_state r_SHA_256_state = {0};
    uint8_t auc_tk[32] = {0};
    uint32_t u4Idx = 0;
    int ret = 0;

    if (s_nan_ctx.nan_svc_num >= NAN_WIFI_NAN_MAX_SVC_SUPPORTED) {
        AML_INFO("Exceed max number, publish fail");
        //return 0;
    }

    ret = aml_nan_get_publish_param(aml_hw, pub_cfg);
    if (ret) {
        AML_INFO("get publish config err, publish fail.");
        return 0;
    }

    publish_req->service_name_len = strlen(pub_cfg->service_name);
    if (publish_req->service_name_len > NAN_WIFI_MAX_SVC_NAME_LEN)
        publish_req->svc_info_len = NAN_WIFI_MAX_SVC_NAME_LEN;
    if (!publish_req->service_name_len) {
        AML_INFO("publish service name err, publish fail.");
        return 0;
    } else {
        memcpy(publish_req->service_name, pub_cfg->service_name, strlen(pub_cfg->service_name));
        aml_nan_get_service_name_hash(publish_req->service_name_hash, publish_req->service_name, publish_req->service_name_len);
    }

    publish_req->svc_info_len = strlen(pub_cfg->service_specific_info);
    if (publish_req->svc_info_len > NAN_WIFI_MAX_SVC_INFO_LEN)
        publish_req->svc_info_len = NAN_WIFI_MAX_SVC_INFO_LEN;
    if (publish_req->svc_info_len)
        memcpy(publish_req->svc_info, pub_cfg->service_specific_info, strlen(pub_cfg->service_specific_info));


    publish_req->mf.match_filter_len = pub_cfg->match_filter_tx.match_filter_len;
    if (publish_req->mf.match_filter_len > NAN_WIFI_MAX_FILTER_LEN)
        publish_req->mf.match_filter_len = NAN_WIFI_MAX_FILTER_LEN;
    if (publish_req->mf.match_filter_len)
        memcpy(publish_req->mf.match_filter, pub_cfg->match_filter_tx.match_filter, publish_req->mf.match_filter_len);

    AML_INFO("[publish]svc_name: %s, svc_len: %d, svc_info: %s, svc_info_len: %d",
        publish_req->service_name, publish_req->service_name_len, publish_req->svc_info, publish_req->svc_info_len);

    if (pub_cfg->publish_id == 0) {
        publish_req->publish_id = ++(s_nan_ctx.instance_id);
        publish_req->inst_id = publish_req->publish_id;
    }

    publish_req->type = pub_cfg->publish_type;

    s_nan_ctx.nan_svc_num++;
    if (s_nan_ctx.instance_id == 255)
        s_nan_ctx.instance_id = 0;

    aml_nan_record_own_svc(publish_req->publish_id, NAN_PUBLISH,
        publish_req->service_name, &pub_cfg->match_filter_tx, &pub_cfg->match_filter_rx);

    return publish_req->publish_id;
}

uint8_t aml_nan_get_sub_cfg(struct aml_hw *aml_hw,
    wifi_nan_subscribe_cfg *subscribe_req, subscribe_config *sub_cfg)
{
    char aucServiceName[256] = {0};
    struct sha256_state r_SHA_256_state = {0};
    uint8_t auc_tk[32] = {0};
    uint32_t u4Idx = 0;
    int ret = 0;

    if (s_nan_ctx.nan_svc_num >= NAN_WIFI_NAN_MAX_SVC_SUPPORTED) {
        AML_INFO("Exceed max number, subscribe fail");
        //return 0;
    }

    ret = aml_nan_get_subscribe_param(aml_hw, sub_cfg);
    if (ret) {
        AML_INFO("get subscribe config err, publish fail.");
        return 0;
    }

    subscribe_req->service_name_len = strlen(sub_cfg->service_name);
    if (subscribe_req->service_name_len > NAN_WIFI_MAX_SVC_NAME_LEN)
        subscribe_req->service_name_len = NAN_WIFI_MAX_SVC_NAME_LEN;
    if (!subscribe_req->service_name_len) {
        AML_INFO("subscribe service name err, publish fail.");
        return 0;
    } else {
        memcpy(subscribe_req->service_name, sub_cfg->service_name, strlen(sub_cfg->service_name));
        aml_nan_get_service_name_hash(subscribe_req->service_name_hash, subscribe_req->service_name, subscribe_req->service_name_len);
    }

    subscribe_req->svc_info_len = strlen(sub_cfg->service_specific_info);
    if (subscribe_req->svc_info_len > NAN_WIFI_MAX_SVC_INFO_LEN)
        subscribe_req->svc_info_len = NAN_WIFI_MAX_SVC_INFO_LEN;
    if (subscribe_req->svc_info_len)
        memcpy(subscribe_req->svc_info, sub_cfg->service_specific_info, strlen(sub_cfg->service_specific_info));

    AML_INFO("[subscribe]match_filter_len: %d", sub_cfg->match_filter_tx.match_filter_len);

    subscribe_req->mf.match_filter_len = sub_cfg->match_filter_tx.match_filter_len;
    if (subscribe_req->mf.match_filter_len > NAN_WIFI_MAX_FILTER_LEN)
        subscribe_req->mf.match_filter_len = NAN_WIFI_MAX_FILTER_LEN;
    if (subscribe_req->mf.match_filter_len)
        memcpy(subscribe_req->mf.match_filter, sub_cfg->match_filter_tx.match_filter, subscribe_req->mf.match_filter_len);

    if (sub_cfg->srf.srf_num_macs > 0) {
        memcpy(&subscribe_req->srf, &sub_cfg->srf, sizeof(srf_info));
    }

    AML_INFO("[subscribe]svc_name: %s, svc_len: %d, svc_info: %s, svc_info_len: %d",
        subscribe_req->service_name, subscribe_req->service_name_len, subscribe_req->svc_info, subscribe_req->svc_info_len);

    if (sub_cfg->subscribe_id == 0)
        subscribe_req->subscribe_id = ++(s_nan_ctx.instance_id);

    subscribe_req->type = sub_cfg->subscribe_type;

    s_nan_ctx.nan_svc_num++;
    if (s_nan_ctx.instance_id == 255)
        s_nan_ctx.instance_id = 0;

    aml_nan_record_own_svc(subscribe_req->subscribe_id, NAN_SUBSCRIBE,
        subscribe_req->service_name, &sub_cfg->match_filter_tx, &sub_cfg->match_filter_rx);

    return subscribe_req->subscribe_id;
}

int32_t aml_nan_get_followup_cfg(wifi_nan_followup_cfg *fup_params)
{
    struct peer_svc_info_list *peer_svc = NULL;
    struct own_svc_info *own_svc = NULL;

    peer_svc = aml_nan_find_peer_svc(fup_params->inst_id, fup_params->peer_inst_id, fup_params->peer_mac);
    if (!peer_svc) {
        AML_INFO("[NAN] Cannot send Follow-up, peer service not exist!");
        return AML_FAIL;
    }

    own_svc = aml_nan_find_own_svc(fup_params->inst_id);
    if (!own_svc) {
        AML_INFO("[NAN] Cannot send Follow-up, own service not exist!");
        return AML_FAIL;
    }

    aml_nan_get_service_name_hash(fup_params->service_name_hash, own_svc->svc_name, strlen(own_svc->svc_name));
    fup_params->svc_info_len = strlen(fup_params->svc_info);
    if (fup_params->svc_info_len > NAN_WIFI_MAX_SVC_INFO_LEN)
        fup_params->svc_info_len = NAN_WIFI_MAX_SVC_INFO_LEN;

    return AML_OK;
}

bool aml_nan_is_all_pairs_wildcard(match_filter *mf)
{
    int i = 0;

    while (i < mf->match_filter_len) {
        uint8_t length = mf->match_filter[i++];
        if (length) {
            return false;
        }
    }

    return true;
}

bool aml_nan_compare_no_filters(match_filter *mf1, match_filter *mf2)
{
    if (aml_nan_is_no_filter(mf1)) {
        if (aml_nan_is_all_pairs_wildcard(mf2) || aml_nan_is_no_filter(mf2)) {
            return true;
        } else {
            return false;
        }
    }

    if (aml_nan_is_no_filter(mf2)) {
        return true;
    }
}

void aml_nan_add_match_pair(match_filter *mf, uint8_t length, uint8_t *value)
{
    if (mf->match_filter_len + length + 1 > sizeof(mf->match_filter)) {
        AML_INFO("Error: No space left in the match filter array.\n");
        return;
    }

    mf->match_filter[mf->match_filter_len++] = length;
    for (int i = 0; i < length; i++) {
        mf->match_filter[mf->match_filter_len++] = value[i];
    }
}

uint8_t aml_nan_get_pairs_count(match_filter *mf)
{
    uint8_t pair_len = 0;
    uint8_t count = 0;
    uint8_t i = 0;

    while (i < mf->match_filter_len) {
        count++;
        pair_len = mf->match_filter[i++];
        i += pair_len;
    }

    return count;
}

bool aml_nan_compare_match_filters(match_filter *rx_mf, match_filter *peer_mf, uint8_t type)
{
    uint8_t pair_count1 = 0;
    uint8_t pair_count2 = 0;
    uint8_t pair_len1 = 0;
    uint8_t pair_len2 = 0;
    uint8_t *pair_val1 = NULL;
    uint8_t *pair_val2 = NULL;
    int i = 0;
    int j = 0;

#ifdef NAN_DEBUG
    AML_INFO("peer_mf:\n");
    aml_nan_parse_match_filters(peer_mf);
    AML_INFO("rx_mf:\n");
    aml_nan_parse_match_filters(rx_mf);
#endif

    if (aml_nan_is_no_filter(rx_mf) || aml_nan_is_no_filter(peer_mf)) {
        if (type = NAN_SDA_SERVICE_CONTROL_TYPE_SUBSCRIBE) {
            return aml_nan_compare_no_filters(rx_mf, peer_mf);
        } else if (type = NAN_SDA_SERVICE_CONTROL_TYPE_PUBLISH) {
            return aml_nan_compare_no_filters(peer_mf, rx_mf);
        }
    }

    // compare fliter count
    pair_count1 = aml_nan_get_pairs_count(rx_mf);
    pair_count2 = aml_nan_get_pairs_count(peer_mf);

    if (type == NAN_SDA_SERVICE_CONTROL_TYPE_SUBSCRIBE) { //sub
        if (pair_count1 < pair_count2) {
            return false;
        }
    } else if (type == NAN_SDA_SERVICE_CONTROL_TYPE_PUBLISH) { // pub
        if (pair_count1 > pair_count2) {
            return false;
        }
    }

    while (i < rx_mf->match_filter_len && j < peer_mf->match_filter_len) {
        pair_len1 = rx_mf->match_filter[i++];
        pair_len2 = peer_mf->match_filter[j++];

        if (pair_len1) {
            pair_val1 = &rx_mf->match_filter[i];
            i += pair_len1;
        }

        if (pair_len2) {
            pair_val2 = &peer_mf->match_filter[j];
            j += pair_len2;
        }

        if (!pair_len1 || !pair_len2) {
            continue;
        }

        if (pair_len1 != pair_len2) {
            return false;
        }

        if (memcmp(pair_val1, pair_val2, pair_len1)) {
            return false;
        }
    }

    return true;
}

bool aml_nan_srf_match(struct aml_hw *aml_hw, srf_info *srf)
{
    struct aml_vif *vif;
    bool match_state = false;
    uint8_t i = 0;

    list_for_each_entry(vif, &aml_hw->vifs, list) {
        // Check if NAN interface already exists
        if (AML_VIF_TYPE(vif) == NL80211_IFTYPE_NAN) {
            break;
        }
    }

    if (srf->srf_type == NAN_SRF_ATTR_BLOOM_FILTER) {
        match_state = aml_nan_bloom_filter_check(vif->ndev->dev_addr, srf->srf_bf, srf->srf_bf_idx, srf->srf_bf_len);
        #ifdef NAN_DEBUG
        AML_INFO("bloom filter:");
        for (i = 0; i < (srf->srf_bf_len / 8); i++)
            AML_INFO("%02x, ", srf->srf_bf[i]);
        #endif
    } else if (srf->srf_type == NAN_SRF_ATTR_PARTIAL_MAC_ADDR) {
        for (i = 0; i < srf->srf_num_macs; i++) {
            if (!memcmp(vif->ndev->dev_addr, srf->srf_mac_addresses[i], MAC_ADDR_LEN)) {
                match_state = true;
                break;
            }
        }
    }
    #ifdef NAN_DEBUG
    AML_INFO(">>> match_state = %d, mac_addr = "MACSTR"", match_state, MAC2STR(vif->ndev->dev_addr));
    #endif

    return match_state;
}

static struct own_svc_info *aml_nan_service_match(uint8_t *sid, match_filter *peer_mf, uint8_t type)
{
    uint8_t svc_name_hash[NAN_SERVICE_HASH_LENGTH];
    struct own_svc_info *p_svc = NULL;

    if (sid == NULL) {
        AML_INFO("Service id is NULL!");
        return NULL;
    }

    for (int i = 0; i < NAN_WIFI_NAN_MAX_SVC_SUPPORTED; i++) {
        aml_nan_get_service_name_hash(svc_name_hash, s_nan_ctx.own_svc[i].svc_name,
            strlen(s_nan_ctx.own_svc[i].svc_name));

        if (!memcmp(svc_name_hash, sid, NAN_SERVICE_HASH_LENGTH) && s_nan_ctx.own_svc[i].type == type) {
            p_svc = &s_nan_ctx.own_svc[i];
            break;
        }
    }

    if (p_svc) {
        if (aml_nan_compare_match_filters(&p_svc->mf_rx, peer_mf, type)) {
            return p_svc;
        } else {
            return NULL;
        }
    }

    return p_svc;
}

static int aml_nan_send_follow_up_msg_wq(struct aml_hw *aml_hw, void *data, int len)
{
    wifi_nan_followup_cfg *cfg = (wifi_nan_followup_cfg *)data;

    BUG_ON(len != sizeof(*cfg));

    aml_nan_send_message(aml_hw, cfg);
    return 0;
}

static int aml_nan_send_publish_msg_wq(struct aml_hw *aml_hw, void *data, int len)
{
    publish_config *cfg = (publish_config *)data;

    BUG_ON(len != sizeof(*cfg));

    aml_nan_publish_service(aml_hw, cfg, 0, false);

    return 0;
}

int aml_nan_service_recv(struct aml_hw *aml_hw, struct peer_svc_info *peer_svc)
{
    struct own_svc_info *p_own_svc = NULL;

    switch (peer_svc->type) {
        case NAN_SDA_SERVICE_CONTROL_TYPE_PUBLISH:
            // recv publish service
            // check own subscribe svc is this publish svc, if yes, say hello.
            p_own_svc = aml_nan_service_match(peer_svc->service_name_hash, &peer_svc->mf, NAN_SUBSCRIBE);
            if (p_own_svc) {
                if (!aml_nan_find_peer_svc(p_own_svc->svc_id, peer_svc->svc_id, peer_svc->peer_nmi)) {
                    AML_INFO("Recv publish service matched!");
                    AML_INFO("===Peer service info:=========================");
                    AML_INFO("service id:            "MACSTR"", MAC2STR(peer_svc->service_name_hash));
                    AML_INFO("peer_mac:              "MACSTR"", MAC2STR(peer_svc->peer_nmi));
                    AML_INFO("instance_id:           %d", peer_svc->svc_id);
                    AML_INFO("request_instance_id:   %d", peer_svc->own_svc_id);
                    AML_INFO("peer_svc_info:         %s", peer_svc->peer_svc_info);
                    AML_INFO("peer_match_filter len: %d", peer_svc->mf.match_filter_len);
                    aml_nan_parse_match_filters(&peer_svc->mf);
                    AML_INFO("==============================================\n");

                    aml_nan_record_peer_svc(p_own_svc->svc_id, peer_svc->svc_id, peer_svc->peer_nmi);
                    // say hello
                    wifi_nan_followup_cfg follow_up_conf = {0};
                    follow_up_conf.inst_id = p_own_svc->svc_id;
                    follow_up_conf.peer_inst_id = peer_svc->svc_id;
                    memcpy(follow_up_conf.peer_mac, peer_svc->peer_nmi, MAC_ADDR_LEN);
                    follow_up_conf.svc_info_len = strlen("hello");
                    memcpy(follow_up_conf.svc_info, "hello", strlen("hello"));

                    aml_wq_do_data(aml_nan_send_follow_up_msg_wq,
                                   aml_hw, &follow_up_conf, sizeof(follow_up_conf));
                }
            }
            break;
        case NAN_SDA_SERVICE_CONTROL_TYPE_SUBSCRIBE:
            // recv subscribe service
            p_own_svc = aml_nan_service_match(peer_svc->service_name_hash, &peer_svc->mf, NAN_PUBLISH);
            if (p_own_svc) {
                if (!aml_nan_srf_match(aml_hw, &peer_svc->srf))
                    return 0;

                if (!aml_nan_find_peer_svc(p_own_svc->svc_id, peer_svc->svc_id, peer_svc->peer_nmi)) {
                    AML_INFO("Recv subscribe service matched!");
                    AML_INFO("===Peer service info:=========================");
                    AML_INFO("service id:            "MACSTR"", MAC2STR(peer_svc->service_name_hash));
                    AML_INFO("peer_mac:              "MACSTR"", MAC2STR(peer_svc->peer_nmi));
                    AML_INFO("instance_id:           %d", peer_svc->svc_id);
                    AML_INFO("request_instance_id:   %d", peer_svc->own_svc_id);
                    AML_INFO("peer_svc_info:         %s", peer_svc->peer_svc_info);
                    AML_INFO("peer_match_filter len: %d", peer_svc->mf.match_filter_len);
                    aml_nan_parse_match_filters(&peer_svc->mf);
                    AML_INFO("==============================================\n");

                    aml_nan_record_peer_svc(p_own_svc->svc_id, peer_svc->svc_id, peer_svc->peer_nmi);

                    // SOLICITED publish
                    publish_config pub_cfg = {0};

                    pub_cfg.publish_id = p_own_svc->svc_id;
                    pub_cfg.publish_type = NAN_PUBLISH_SOLICITED;
                    pub_cfg.peer_inst_id = peer_svc->svc_id;
                    memcpy(pub_cfg.service_name, p_own_svc->svc_name, strlen(p_own_svc->svc_name));
                    if (p_own_svc->mf_tx.match_filter_len) {
                        memcpy(&pub_cfg.match_filter_tx, &p_own_svc->mf_tx, sizeof(match_filter));
                    }
                    memcpy(pub_cfg.service_name_hash, peer_svc->service_name_hash, NAN_SERVICE_HASH_LENGTH);
                    memcpy(pub_cfg.peer_mac, peer_svc->peer_nmi, MAC_ADDR_LEN);

                    aml_wq_do_data(aml_nan_send_publish_msg_wq,
                                   aml_hw, &pub_cfg, sizeof(publish_config));
                }
            }
            break;
        case NAN_SDA_SERVICE_CONTROL_TYPE_FOLLOWUP:
            // recv follow up msg
            AML_INFO("===recv follow up service:====================");
            AML_INFO("service id:            "MACSTR"", MAC2STR(peer_svc->service_name_hash));
            AML_INFO("peer_mac:              "MACSTR"", MAC2STR(peer_svc->peer_nmi));
            AML_INFO("instance_id:           %d", peer_svc->svc_id);
            AML_INFO("request_instance_id:   %d", peer_svc->own_svc_id);
            AML_INFO("peer_svc_info:         %s", peer_svc->peer_svc_info);
            AML_INFO("==============================================\n");
            break;
        default:
            break;
    }

    return 0;
}

