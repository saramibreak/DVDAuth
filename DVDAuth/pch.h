#ifndef PCH_H
#define PCH_H

#pragma warning(disable:4710 4711 5045)
#pragma warning(push)
#pragma warning(disable:4668 4820 5039)
#include <windows.h>
#include <stdio.h>
// SPTI(needs Windows Driver Kit(wdk))
#include <ntddcdvd.h> // inc\api
#include <ntddscsi.h>
#define _NTSCSI_USER_MODE_
#include <scsi.h>
#undef _NTSCSI_USER_MODE_
#pragma warning(pop)

#endif //PCH_H
