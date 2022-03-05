/***
 * @FilePath     : lfp_version.h
 * @Description  : Description for this file.
 * @Author       : wytaitaislee
 * @Date         : 2022-03-05 17:22:42
 * @LastEditTime : 2022-03-05 17:28:04
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_VERSION_H__
#define __LFP_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define LFP_BASE_MAJOR "V1"
#define LFP_BASE_MINOR "0"
#define LFP_BASE_SUB "0"
#define __LFP_BASE_VERSION(major, minor, sub) (major##.##minor##.##sub)
#define LFP_BASE_VERSION \
  __LFP_BASE_VERSION(LFP_BASE_MAJOR, LFP_BASE_MINOR, LFP_BASE_SUB)

#ifdef __cplusplus
}
#endif

#endif /* end of __LFP_VERSION_H__ */
