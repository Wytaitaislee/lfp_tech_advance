/***
 * @FilePath     : lfp_errcode.h
 * @Description  : global errcode rules.
 * @Author       : wytaitaislee
 * @Date         : 2022-04-10 15:04:16
 * @LastEditTime : 2022-04-10 15:09:22
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

/*+-----+-----------------------------------+-----------------------+-------------------------+
|  Bit  |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|9|8|7|6|5|4|3|2|1|0|
| Field |            category               |        module         |         mask            |
*/

#define MASK_START (0)
#define MASK_END (11)
#define MODULE_START (MASK_END)
#define MODULE_END (19)
#define CATEGORY_START (MODULE_END)
#define CATEGORY_END (31)

#define LFP_FIELD_MAX(var, start, end) \
    ((var) & ((~(1 << (end))) & (~(1 << (start)))))

#define LFP_ERRCODE_SAFE_CA(ca) LFP_FIELD_MAX(CATEGORY_START, CATEGORY_END)
#define LFP_ERRCODE_SAFE_MD(md) LFP_FIELD_MAX(MODULE_START, MODULE_END)
#define LFP_ERRCODE_SAFE(mk) LFP_FIELD_MAX(MASK_START, MASK_END)

#define LFP_ERRCODE_BASE(ca, md, mk) \
    (LFP_INT32)((LFP_ERRCODE_SAFE_CA(ca) | LFP_ERRCODE_SAFE_MD(md) | LFP_ERRCODE_SAFE(mk)))