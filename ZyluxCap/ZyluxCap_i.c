/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 23 13:48:30 2000
 */
/* Compiler settings for C:\Code\Zylux\ZyluxCap\ZyluxCap.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_ZyluxCap = {0xF0CB6024,0x7876,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};


const IID DIID_IZyluxCap = {0xF0CB6025,0x7876,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};


const CLSID CLSID_ZyluxCap = {0xF0CB6023,0x7876,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};


const IID DIID_IZyluxForm = {0xEEF10E19,0xC379,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};


const CLSID CLSID_ZyluxForm = {0xEEF10E1B,0xC379,0x11D2,{0x88,0xA4,0x00,0x10,0x4B,0xF1,0x94,0xE2}};


const IID IID_IZyluxNotify = {0x32FD1680,0x348C,0x41cf,{0xBE,0x53,0xB0,0x14,0x8C,0xAE,0xC0,0xBA}};


#ifdef __cplusplus
}
#endif

