/**
 * Copyright 2011-2023 sarami
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "execScsiCmdforFileSystem.h"

extern VOID OutputLastErrorNumAndString(LPCTSTR pszFuncName, LONG lLineNum);

BOOL ScsiPassThroughDirect(
	PDEVICE pDevice,
	LPVOID lpCdb,
	BYTE byCdbLength,
	LPVOID pvBuffer,
	INT nDataDirection,
	DWORD dwBufferLength,
	LPBYTE byScsiStatus,
	LPCTSTR pszFuncName,
	LONG lLineNum
) {
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb = {};
#ifdef _WIN32
	swb.Sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	swb.Sptd.PathId = pDevice->address.PathId;
	swb.Sptd.TargetId = pDevice->address.TargetId;
	swb.Sptd.Lun = pDevice->address.Lun;
	swb.Sptd.CdbLength = byCdbLength;
	swb.Sptd.SenseInfoLength = SENSE_BUFFER_SIZE;
	swb.Sptd.DataIn = (UCHAR)nDataDirection;
	swb.Sptd.DataTransferLength = dwBufferLength;
	swb.Sptd.TimeOutValue = pDevice->dwTimeOutValue;
	swb.Sptd.DataBuffer = pvBuffer;
	swb.Sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, SenseData);
	memcpy(swb.Sptd.Cdb, lpCdb, byCdbLength);
#elif __linux__
	swb.io_hdr.interface_id = 'S';
	swb.io_hdr.dxfer_direction = nDataDirection;
	swb.io_hdr.cmd_len = byCdbLength;
	swb.io_hdr.mx_sb_len = sizeof(swb.Dummy);
	swb.io_hdr.dxfer_len = (unsigned int)dwBufferLength;
	swb.io_hdr.dxferp = pvBuffer;
	swb.io_hdr.cmdp = (unsigned char *)lpCdb;
	swb.io_hdr.sbp = swb.Dummy;
	swb.io_hdr.timeout = (unsigned int)pDevice->dwTimeOutValue;
//	swb.io_hdr.flags = SG_FLAG_DIRECT_IO;
#elif __MACH__
	UNREFERENCED_PARAMETER(nDataDirection);
	// https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/WorkingWithSAM/WWS_SAMDevInt/WWS_SAM_DevInt.html#//apple_ref/doc/uid/TP30000387-SW1
    IOReturn         err  = 0;
    IOVirtualRange* range = NULL;
	// Allocate a virtual range for the buffer. If we had more than 1 scatter-gather entry,
	// we would allocate more than 1 IOVirtualRange.
	if (NULL == (range = (IOVirtualRange*)malloc(sizeof(IOVirtualRange)))) {
		fprintf(stderr, "*********** ERROR Malloc'ing IOVirtualRange ***********\n\n");
		return FALSE;
	}
	// Set up the range. The address is just the buffer's address. The length is our request size.
	range->address = (IOVirtualAddress)pvBuffer;
	range->length  = dwBufferLength;

	SCSICommandDescriptorBlock cdb;
	memcpy(&cdb, lpCdb, byCdbLength);

	// Set the actual CDB in the task
	if (kIOReturnSuccess != (err = (*pDevice->hDevice)->SetCommandDescriptorBlock(pDevice->hDevice, cdb, byCdbLength))) {
		fprintf(stderr, "*********** ERROR Setting CDB ***********\n\n");
		return FALSE;
	}
	// Set the scatter-gather entry in the task
	if (kIOReturnSuccess != (err = (*pDevice->hDevice)->SetScatterGatherEntries(
		pDevice->hDevice, range, 1, dwBufferLength, kSCSIDataTransfer_FromTargetToInitiator))) {
		fprintf(stderr, "*********** ERROR Setting SG Entries ***********\n\n");
		return FALSE;
	}
	// Set the timeout in the task
	if (kIOReturnSuccess != (err = (*pDevice->hDevice)->SetTimeoutDuration(pDevice->hDevice, 10000))) {
		fprintf(stderr, "*********** ERROR Setting Timeout ***********\n\n");
		return FALSE;
	}
#endif
	DWORD dwLength = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
	DWORD dwReturned = 0;
	BOOL bRet = TRUE;
	BOOL bNoSense = FALSE;
	SetLastError(NO_ERROR);
	if (!DeviceIoControl(pDevice->hDevice, IOCTL_SCSI_PASS_THROUGH_DIRECT,
		&swb, dwLength, &swb, dwLength, &dwReturned, NULL)) {
		OutputLastErrorNumAndString(pszFuncName, lLineNum);
		bRet = FALSE;
	}
	else {
		if (swb.SenseData.SenseKey == SCSI_SENSE_NO_SENSE &&
			swb.SenseData.AdditionalSenseCode == SCSI_ADSENSE_NO_SENSE &&
			swb.SenseData.AdditionalSenseCodeQualifier == 0x00) {
			bNoSense = TRUE;
		}
#ifdef _WIN32
		if (swb.Sptd.ScsiStatus >= SCSISTAT_CHECK_CONDITION && !bNoSense) {
			INT nLBA = 0;
			if (swb.Sptd.Cdb[0] == 0xa8 ||
				swb.Sptd.Cdb[0] == 0xad ||
				swb.Sptd.Cdb[0] == 0xbe ||
				swb.Sptd.Cdb[0] == 0xd8) {
				nLBA = (swb.Sptd.Cdb[2] << 24)
					+ (swb.Sptd.Cdb[3] << 16)
					+ (swb.Sptd.Cdb[4] << 8)
					+ swb.Sptd.Cdb[5];
			}
			OutputErrorString(
				"\rLBA[%06d, %#07x]: [F:%s][L:%ld]\n\tOpcode: %#02x\n"
				, nLBA, nLBA, pszFuncName, lLineNum, swb.Sptd.Cdb[0]);
//			OutputScsiStatus(swb.Sptd.ScsiStatus);
#elif __linux__
		if (swb.io_hdr.status >= SCSISTAT_CHECK_CONDITION && !bNoSense) {
			INT nLBA = 0;
			if (swb.io_hdr.cmdp[0] == 0xa8 ||
				swb.io_hdr.cmdp[0] == 0xad ||
				swb.io_hdr.cmdp[0] == 0xbe ||
				swb.io_hdr.cmdp[0] == 0xd8) {
				nLBA = (swb.io_hdr.cmdp[2] << 24)
					+ (swb.io_hdr.cmdp[3] << 16)
					+ (swb.io_hdr.cmdp[4] << 8)
					+ swb.io_hdr.cmdp[5];
			}
			OutputErrorString(
				"\rLBA[%06d, %#07x]: [F:%s][L:%ld]\n\tOpcode: %#02x\n"
				, nLBA, (UINT)nLBA, pszFuncName, lLineNum, swb.io_hdr.cmdp[0]);
//			OutputScsiStatus(swb.io_hdr.status);
#elif __MACH__
		if (swb.taskStatus >= SCSISTAT_CHECK_CONDITION && !bNoSense) {
#endif
//			OutputSenseData(&swb.SenseData);
		}
	}
	if (bNoSense) {
		*byScsiStatus = SCSISTAT_GOOD;
	}
	else {
#ifdef _WIN32
		*byScsiStatus = swb.Sptd.ScsiStatus;
#elif __linux__
		*byScsiStatus = swb.io_hdr.status;
#elif __MACH__
		*byScsiStatus = swb.taskStatus;
		FreeAndNull(range);
#endif
	}
	return bRet;
}

BOOL ExecReadCD(
	PDEVICE pDevice,
	LPBYTE lpCmd,
	INT nLBA,
	LPBYTE lpBuf,
	DWORD dwBufSize,
	LPCSTR pszFuncName,
	LONG lLineNum
) {
	REVERSE_BYTES(&lpCmd[2], &nLBA);
#ifdef _WIN32
	INT direction = SCSI_IOCTL_DATA_IN;
#else
	INT direction = SG_DXFER_FROM_DEV;
#endif
	BYTE byScsiStatus = 0;
	if (!ScsiPassThroughDirect(pDevice, lpCmd, CDB12GENERIC_LENGTH
		, lpBuf, direction, dwBufSize, &byScsiStatus, pszFuncName, lLineNum)
		|| byScsiStatus >= SCSISTAT_CHECK_CONDITION) {
		OutputErrorString(
			"lpCmd: %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n"
			"dwBufSize: %lu\n"
			, lpCmd[0], lpCmd[1], lpCmd[2], lpCmd[3], lpCmd[4], lpCmd[5]
			, lpCmd[6], lpCmd[7], lpCmd[8], lpCmd[9], lpCmd[10], lpCmd[11]
			, dwBufSize
		);
		return FALSE;
	}
	return TRUE;
}

BOOL ExecReadDisc(
	PDEVICE pDevice,
	LPBYTE pCdb,
	INT nLBA,
	LPBYTE lpBuf,
	BYTE byTransferLen,
	LPCSTR pszFuncName,
	LONG lLineNum
) {
	if (!ExecReadCD(pDevice, pCdb, nLBA, lpBuf,
		(DWORD)(DISC_RAW_READ_SIZE * byTransferLen), pszFuncName, lLineNum)) {
		return FALSE;
	}
	return TRUE;
}

WORD GetSizeOrWordForVolDesc(
	LPBYTE lpBuf
) {
	WORD val = MAKEWORD(lpBuf[0], lpBuf[1]);
	if (val == 0) {
		val = MAKEWORD(lpBuf[3], lpBuf[2]);
	}
	return val;
}

UINT GetSizeOrUintForVolDesc(
	LPBYTE lpBuf,
	UINT uiMax
) {
	UINT val = MAKEUINT(MAKEWORD(lpBuf[0], lpBuf[1]),
		MAKEWORD(lpBuf[2], lpBuf[3]));
	if (val == 0 || val >= uiMax) {
		val = MAKEUINT(MAKEWORD(lpBuf[7], lpBuf[6]),
			MAKEWORD(lpBuf[5], lpBuf[4]));
	}
	return val;
}

UINT PadSizeForVolDesc(
	UINT uiSize
) {
	INT nPadding = DISC_RAW_READ_SIZE - (INT)uiSize;
	// uiSize isn't 2048 byte
	if (nPadding != 0) {
		// uiSize is smaller than 2048 byte
		if (nPadding > 0) {
			// Generally, directory size is per 2048 byte
			// Exception:
			//  Codename - Outbreak (Europe) (Sold Out Software)
			//  Commandos - Behind Enemy Lines (Europe) (Sold Out Software)
			// and more
			uiSize += nPadding;
		}
		// uiSize is larger than 2048 byte
		else {
			nPadding = (INT)uiSize % DISC_RAW_READ_SIZE;
			// uiSize isn't 4096, 6144, 8192 etc byte
			if (nPadding != 0) {
				nPadding = DISC_RAW_READ_SIZE - nPadding;
				uiSize += nPadding;
			}
		}
	}
	return uiSize;
}

VOID SetCommandForTransferLength(
	LPBYTE pCdb,
	DWORD dwSize,
	LPBYTE lpTransferLen,
	LPBYTE lpRoopLen
) {
	*lpTransferLen = (BYTE)(dwSize / DISC_RAW_READ_SIZE);
	// Generally, directory size is per 2048 byte
	// Exception:
	//  Codename - Outbreak (Europe) (Sold Out Software)
	//  Commandos - Behind Enemy Lines (Europe) (Sold Out Software)
	// and more
	if (dwSize % DISC_RAW_READ_SIZE != 0) {
		(*lpTransferLen)++;
	}
	// 0xa8
	pCdb[9] = *lpTransferLen;
	*lpRoopLen = *lpTransferLen;
}

VOID ManageEndOfDirectoryRecord(
	LPINT nSectorNum,
	BYTE byTransferLen,
	UINT uiZeroPaddingNum,
	LPBYTE lpDirRec,
	LPUINT nOfs
) {
	if (*nSectorNum < byTransferLen) {
		UINT j = 0;
		for (; j < uiZeroPaddingNum; j++) {
			if (lpDirRec[j] != 0) {
				break;
			}
		}
		if (j == uiZeroPaddingNum) {
			*nOfs += uiZeroPaddingNum;
			(*nSectorNum)++;
			return;
		}
	}
	else {
		return;
	}
}

VOID OutputFsDirectoryRecord(
	LPBYTE lpBuf,
	LPSTR fname
) {
	for (INT n = 0; n < lpBuf[32]; n++) {
#ifndef _WIN32
		if (lpBuf[33 + n] == 0) continue;
#endif
		fname[n] = (CHAR)lpBuf[33 + n];
	}
}

BOOL ReadDirectoryRecordDetail(
	PDEVICE pDevice,
	LPBYTE pCdb,
	INT nLBA,
	LPBYTE lpBuf,
	BYTE byTransferLen,
	INT nDirPosNum,
	UINT uiLogicalBlkCoef,
	INT nOffset,
	PDIRECTORY_RECORD pDirRec,
	PVOB pVOB
) {
	if (!ExecReadDisc(pDevice, pCdb, nLBA + nOffset
		, lpBuf, byTransferLen, __FUNCTION__, __LINE__)) {
		return FALSE;
	}
	BYTE byRoop = byTransferLen;
	UINT uiOfs = 0;
	for (INT nSectorNum = 0; nSectorNum < byRoop;) {
		if (*(lpBuf + uiOfs) == 0) {
			break;
		}
		for (;;) {
			CHAR szCurDirName[MAX_FNAME_FOR_VOLUME] = {};
			LPBYTE lpDirRec = lpBuf + uiOfs;
			if (lpDirRec[0] >= MIN_LEN_DR) {
				UINT uiExtentPos = GetSizeOrUintForVolDesc(lpDirRec + 2, 0xffffffff) / uiLogicalBlkCoef;
				UINT uiDataLen = GetSizeOrUintForVolDesc(lpDirRec + 10, 0xffffffff);
				OutputFsDirectoryRecord(lpDirRec, szCurDirName);
				if (strstr(szCurDirName, ".VOB")) {
					strncpy(pVOB[pVOB->idx].fname, szCurDirName, MAX_FNAME_FOR_VOLUME);
					pVOB[pVOB->idx].lba = (INT)uiExtentPos;
					pVOB->idx++;
				}
				UINT uiPaddingSize = 0;
				INT nDirOfs = 33 + lpDirRec[32];
				if (lpDirRec[32] % 2 == 0) {
					nDirOfs++;
				}
				if (nDirOfs < lpDirRec[0]) {
					for (; nDirOfs + uiPaddingSize < lpDirRec[0];) {
						// Incorrect directory record length
						// The Shooting Love: XII Stag & Trizeal [DVD] (Japan)
						// 0170 :                          3C 00 91 A4 3D 00 00 3D   1.......<...=..=
						// 0180 : A4 91 24 72 01 00 00 01  72 24 6A 03 10 01 31 2C   ..$r....r$j...1,
						// 0190 : 24 00 00 00 01 00 00 01  03 00 3B 31 00 00 00 00   $.........;1....
						// 01A0 : 00 00 3C 00 C0 A4 3D 00  00 3D A4 C0 A4 16 08 00   ..<...=..=......
						// 01B0 : 00 08 16 A4
						if (lpDirRec[nDirOfs + uiPaddingSize] > MIN_LEN_DR &&
							lpDirRec[nDirOfs + uiPaddingSize + 2] == lpDirRec[nDirOfs + uiPaddingSize + 9] &&
							lpDirRec[nDirOfs + uiPaddingSize + 3] == lpDirRec[nDirOfs + uiPaddingSize + 8] &&
							lpDirRec[nDirOfs + uiPaddingSize + 4] == lpDirRec[nDirOfs + uiPaddingSize + 7] &&
							lpDirRec[nDirOfs + uiPaddingSize + 5] == lpDirRec[nDirOfs + uiPaddingSize + 6] &&
							lpDirRec[nDirOfs + uiPaddingSize + 10] == lpDirRec[nDirOfs + uiPaddingSize + 17] &&
							lpDirRec[nDirOfs + uiPaddingSize + 11] == lpDirRec[nDirOfs + uiPaddingSize + 16] &&
							lpDirRec[nDirOfs + uiPaddingSize + 12] == lpDirRec[nDirOfs + uiPaddingSize + 15] &&
							lpDirRec[nDirOfs + uiPaddingSize + 13] == lpDirRec[nDirOfs + uiPaddingSize + 14]) {
							if (!(lpDirRec[nDirOfs + uiPaddingSize + 2] == 0 && lpDirRec[nDirOfs + uiPaddingSize + 3] == 0 &&
								lpDirRec[nDirOfs + uiPaddingSize + 4] == 0 && lpDirRec[nDirOfs + uiPaddingSize + 5] == 0) &&
								!(lpDirRec[nDirOfs + uiPaddingSize + 10] == 0 && lpDirRec[nDirOfs + uiPaddingSize + 11] == 0 &&
								lpDirRec[nDirOfs + uiPaddingSize + 12] == 0 && lpDirRec[nDirOfs + uiPaddingSize + 13] == 0)) {
								break;
							}
						}
						uiPaddingSize++;
					}
					uiOfs += nDirOfs + uiPaddingSize;
				}
				else {
					uiOfs += lpDirRec[0];
				}

				if ((lpDirRec[25] & 0x02)
					&& !(lpDirRec[32] == 1 && szCurDirName[0] == 0)
					&& !(lpDirRec[32] == 1 && szCurDirName[0] == 1)) {
					// not upper and current directory 
					for (INT i = 1; i < nDirPosNum; i++) {
						if (uiExtentPos == pDirRec[i].uiPosOfDir &&
							!_strnicmp(szCurDirName, pDirRec[i].szDirName, MAX_FNAME_FOR_VOLUME)) {
							pDirRec[i].uiDirSize = PadSizeForVolDesc(uiDataLen);
							break;
						}
					}
				}
				if (uiOfs == (UINT)(DISC_RAW_READ_SIZE * (nSectorNum + 1))) {
					nSectorNum++;
					break;
				}
			}
			else {
				UINT uiZeroPaddingNum = DISC_RAW_READ_SIZE * (nSectorNum + 1) - uiOfs;
				if (uiZeroPaddingNum > MIN_LEN_DR) {
					BYTE byNextLenDR = lpDirRec[MIN_LEN_DR];
					if (byNextLenDR >= MIN_LEN_DR) {
						// Amiga Tools 4 : The second of Direcory Record (0x22 - 0x43) is corrupt...
						// ========== LBA[040915, 0x09fd3]: Main Channel ==========
						//        +0 +1 +2 +3 +4 +5 +6 +7  +8 +9 +A +B +C +D +E +F
						// 0000 : 22 00 D3 9F 00 00 00 00  9F D3 00 08 00 00 00 00   "...............
						// 0010 : 08 00 60 02 1D 17 18 2C  00 02 00 00 01 00 00 01   ..`....,........
						// 0020 : 01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00   ................
						// 0030 : 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00   ................
						// 0040 : 00 00 01 01 2E 00 09 A0  00 00 00 00 A0 09 D8 01   ................
						OutputErrorString(
							"Direcory Record is corrupt. Skip reading from %d to %d byte.\n"
							, uiOfs, uiOfs + MIN_LEN_DR - 1);
						uiOfs += MIN_LEN_DR;
						break;
					}
					else {
						ManageEndOfDirectoryRecord(&nSectorNum, byRoop, uiZeroPaddingNum, lpDirRec, &uiOfs);
						break;
					}
				}
				else {
					ManageEndOfDirectoryRecord(&nSectorNum, byRoop, uiZeroPaddingNum, lpDirRec, &uiOfs);
					break;
				}
			}
		}
	}
	return TRUE;
}

BOOL ReadDirectoryRecord(
	PDEVICE pDevice,
	LPBYTE pCdb,
	LPBYTE lpBuf,
	UINT uiLogicalBlkCoef,
	UINT uiRootDataLen,
	INT nSectorOfs,
	PDIRECTORY_RECORD pDirRec,
	INT nDirPosNum,
	PVOB pVOB
) {
	BYTE byTransferLen = 1;
	BYTE byRoop = byTransferLen;
	// for CD-I
	if (uiRootDataLen == 0) {
		if (!ExecReadDisc(pDevice, pCdb
			, (INT)pDirRec[0].uiPosOfDir + nSectorOfs, lpBuf, byTransferLen, __FUNCTION__, __LINE__)) {
			return FALSE;
		}
		uiRootDataLen =
			PadSizeForVolDesc(GetSizeOrUintForVolDesc(lpBuf + 10, 0));
	}
	pDirRec[0].uiDirSize = uiRootDataLen;

	for (INT nDirRecIdx = 0; nDirRecIdx < nDirPosNum; nDirRecIdx++) {
		INT nLBA = (INT)pDirRec[nDirRecIdx].uiPosOfDir;
		if (pDirRec[nDirRecIdx].uiDirSize > pDevice->dwMaxTransferLength) {
			// [FMT] Psychic Detective Series Vol. 4 - Orgel (Japan) (v1.0)
			// [FMT] Psychic Detective Series Vol. 5 - Nightmare (Japan)
			// [IBM - PC compatible] Maria 2 - Jutai Kokuchi no Nazo (Japan) (Disc 1)
			// [IBM - PC compatible] PC Game Best Series Vol. 42 - J.B. Harold Series - Kiss of Murder - Satsui no Kuchizuke (Japan)
			// [SS] Madou Monogatari (Japan)
			// and more
			DWORD additionalTransferLen = pDirRec[nDirRecIdx].uiDirSize / pDevice->dwMaxTransferLength;
			SetCommandForTransferLength(pCdb, pDevice->dwMaxTransferLength, &byTransferLen, &byRoop);

			for (DWORD n = 0; n < additionalTransferLen; n++) {
				if (!ReadDirectoryRecordDetail(pDevice, pCdb, nLBA
					, lpBuf, byTransferLen, nDirPosNum, uiLogicalBlkCoef, nSectorOfs, pDirRec, pVOB)) {
					continue;
				}
				nLBA += byRoop;
			}
			DWORD dwLastTblSize = pDirRec[nDirRecIdx].uiDirSize % pDevice->dwMaxTransferLength;
			if (dwLastTblSize != 0) {
				SetCommandForTransferLength(pCdb, dwLastTblSize, &byTransferLen, &byRoop);

				if (!ReadDirectoryRecordDetail(pDevice, pCdb, nLBA
					, lpBuf, byTransferLen, nDirPosNum, uiLogicalBlkCoef, nSectorOfs, pDirRec, pVOB)) {
					continue;
				}
			}
		}
		else {
			if (pDirRec[nDirRecIdx].uiDirSize == 0 || byTransferLen == 0) {
				OutputErrorString("Directory Record is invalid\n");
				return FALSE;
			}
			SetCommandForTransferLength(pCdb, pDirRec[nDirRecIdx].uiDirSize, &byTransferLen, &byRoop);

			if (!ReadDirectoryRecordDetail(pDevice, pCdb, nLBA
				, lpBuf, byTransferLen, nDirPosNum, uiLogicalBlkCoef, nSectorOfs, pDirRec, pVOB)) {
				continue;
			}
		}
	}
	return TRUE;
}

BOOL OutputFsPathTableRecord(
	LPBYTE lpBuf,
	UINT uiLogicalBlkCoef,
	UINT uiPathTblSize,
	BOOL bPathType,
	PDIRECTORY_RECORD pDirRec,
	LPINT nDirPosNum
) {
	for (UINT i = 0; i < uiPathTblSize;) {
		if (*nDirPosNum > DIRECTORY_RECORD_SIZE) {
			OutputErrorString("Directory Record is over %d\n", DIRECTORY_RECORD_SIZE);
			return FALSE;
		}
		pDirRec[*nDirPosNum].uiDirNameLen = lpBuf[i];
		if (bPathType == lType) {
			pDirRec[*nDirPosNum].uiPosOfDir = MAKEUINT(MAKEWORD(lpBuf[2 + i], lpBuf[3 + i]),
				MAKEWORD(lpBuf[4 + i], lpBuf[5 + i])) / uiLogicalBlkCoef;
		}
		else {
			pDirRec[*nDirPosNum].uiPosOfDir = MAKEUINT(MAKEWORD(lpBuf[5 + i], lpBuf[4 + i]),
				MAKEWORD(lpBuf[3 + i], lpBuf[2 + i])) / uiLogicalBlkCoef;
		}
		if (pDirRec[*nDirPosNum].uiDirNameLen > 0) {
			if (bPathType == lType) {
				pDirRec[*nDirPosNum].uiNumOfUpperDir = MAKEWORD(lpBuf[6 + i], lpBuf[7 + i]);
			}
			else {
				pDirRec[*nDirPosNum].uiNumOfUpperDir = MAKEWORD(lpBuf[7 + i], lpBuf[6 + i]);
			}
			for (size_t n = 0; n < pDirRec[*nDirPosNum].uiDirNameLen; n++) {
#ifndef _WIN32
				if (lpBuf[8 + i + n] == 0) continue;
#endif
				pDirRec[*nDirPosNum].szDirName[n] = (CHAR)lpBuf[8 + i + n];
			}

			i += 8 + pDirRec[*nDirPosNum].uiDirNameLen;
			if ((i % 2) != 0) {
				i++;
			}
			*nDirPosNum = *nDirPosNum + 1;
		}
		else {
			break;
		}
	}
	return TRUE;
}

BOOL ReadPathTableRecord(
	PDEVICE pDevice,
	LPBYTE pCdb,
	UINT uiLogicalBlkCoef,
	UINT uiPathTblSize,
	UINT uiPathTblPos,
	BOOL bPathType,
	INT nSectorOfs,
	PDIRECTORY_RECORD pDirRec,
	LPINT nDirPosNum
) {
	BYTE byTransferLen = 1;
	BYTE byRoop = byTransferLen;
	DWORD dwBufSize = DISC_RAW_READ_SIZE - (uiPathTblSize % DISC_RAW_READ_SIZE) + uiPathTblSize;
	SetCommandForTransferLength(pCdb, uiPathTblSize, &byTransferLen, &byRoop);

	LPBYTE lpBuf = (LPBYTE)calloc(dwBufSize, sizeof(BYTE));
	if (!lpBuf) {
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
		return FALSE;
	}

	BOOL bRet = TRUE;
	try {
		if (uiPathTblSize > pDevice->dwMaxTransferLength) {
			DWORD uiAdditionalTransferLen = uiPathTblSize / pDevice->dwMaxTransferLength;
			SetCommandForTransferLength(pCdb, pDevice->dwMaxTransferLength, &byTransferLen, &byRoop);

			for (DWORD n = 0; n < uiAdditionalTransferLen; n++) {
				if (!ExecReadDisc(pDevice, pCdb
					, (INT)uiPathTblPos + nSectorOfs, lpBuf + pDevice->dwMaxTransferLength * n, byTransferLen, __FUNCTION__, __LINE__)) {
					throw FALSE;
				}
				uiPathTblPos += byTransferLen;
			}
			DWORD dwLastPathTblSize = uiPathTblSize % pDevice->dwMaxTransferLength;
			SetCommandForTransferLength(pCdb, dwLastPathTblSize, &byTransferLen, &byRoop);
			DWORD dwBufOfs = pDevice->dwMaxTransferLength * uiAdditionalTransferLen;

			if (!ExecReadDisc(pDevice, pCdb
				, (INT)uiPathTblPos + nSectorOfs, lpBuf + dwBufOfs, byTransferLen, __FUNCTION__, __LINE__)) {
				throw FALSE;
			}
			if (!OutputFsPathTableRecord(lpBuf, uiLogicalBlkCoef, uiPathTblSize, bPathType, pDirRec, nDirPosNum)) {
				throw FALSE;
			}
		}
		else {
			if (!ExecReadDisc(pDevice, pCdb
				, (INT)uiPathTblPos + nSectorOfs, lpBuf, byTransferLen, __FUNCTION__, __LINE__)) {
				throw FALSE;
			}
			if (!OutputFsPathTableRecord(lpBuf, uiLogicalBlkCoef, uiPathTblSize, bPathType, pDirRec, nDirPosNum)) {
				throw FALSE;
			}
		}
	}
	catch (BOOL ret) {
		bRet = ret;
	}
	FreeAndNull(lpBuf);
	return bRet;
}

BOOL ReadVolumeDescriptor(
	PDEVICE pDevice,
	LPBYTE pCdb,
	LPBYTE lpBuf,
	INT nPVD,
	INT nSectorOfs,
	LPBOOL lpReadVD,
	PVOLUME_DESCRIPTOR pVolDesc,
	BYTE byTransferLen
) {
	INT nTmpLBA = nPVD;
	for (;;) {
		if (!ExecReadDisc(pDevice, pCdb, nTmpLBA + nSectorOfs
			, lpBuf, byTransferLen, __FUNCTION__, __LINE__)) {
			break;
		}
		if (!strncmp((LPCH)&lpBuf[1], "CD001", 5)) {
			if (nTmpLBA == nPVD) {
				WORD wLogicalBlkSize = GetSizeOrWordForVolDesc(lpBuf + 128);
				pVolDesc->ISO_9660.uiLogicalBlkCoef = (BYTE)(DISC_RAW_READ_SIZE / wLogicalBlkSize);
				pVolDesc->ISO_9660.uiPathTblSize =
					GetSizeOrUintForVolDesc(lpBuf + 132, 0);
				pVolDesc->ISO_9660.uiPathTblPos = MAKEUINT(MAKEWORD(lpBuf[140], lpBuf[141]),
					MAKEWORD(lpBuf[142], lpBuf[143])) / pVolDesc->ISO_9660.uiLogicalBlkCoef;
				pVolDesc->bPathType = lType;
				if (pVolDesc->ISO_9660.uiPathTblPos == 0) {
					pVolDesc->ISO_9660.uiPathTblPos = MAKEUINT(MAKEWORD(lpBuf[151], lpBuf[150]),
						MAKEWORD(lpBuf[149], lpBuf[148]));
					pVolDesc->bPathType = mType;
				}
				pVolDesc->ISO_9660.uiRootDataLen =
					GetSizeOrUintForVolDesc(lpBuf + 166, 0);
				if (pVolDesc->ISO_9660.uiRootDataLen > 0) {
					pVolDesc->ISO_9660.uiRootDataLen = PadSizeForVolDesc(pVolDesc->ISO_9660.uiRootDataLen);
				}
				*lpReadVD = TRUE;
			}
			nTmpLBA++;
		}
		else {
			break;
		}
	}
	return TRUE;
}

BOOL ReadDVDForFileSystem(
	PDEVICE pDevice,
	CDB::_READ12* cdb,
	LPBYTE lpBuf,
	PVOB pVOB
) {
	BOOL bPVD = FALSE;
	VOLUME_DESCRIPTOR volDesc;
	DWORD dwTransferLen = 1;
	REVERSE_BYTES(&cdb->TransferLength, &dwTransferLen);

	if (!ReadVolumeDescriptor(pDevice
		, (LPBYTE)cdb, lpBuf, 16, 0, &bPVD, &volDesc, (BYTE)dwTransferLen)) {
		return FALSE;
	}
	if (bPVD) {
		PDIRECTORY_RECORD pDirRec = (PDIRECTORY_RECORD)calloc(DIRECTORY_RECORD_SIZE, sizeof(DIRECTORY_RECORD));
		if (!pDirRec) {
			OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
			return FALSE;
		}
		INT nDirPosNum = 0;
		if (!ReadPathTableRecord(pDevice, (LPBYTE)cdb
			, volDesc.ISO_9660.uiLogicalBlkCoef, volDesc.ISO_9660.uiPathTblSize
			, volDesc.ISO_9660.uiPathTblPos, volDesc.bPathType, 0, pDirRec, &nDirPosNum)) {
			FreeAndNull(pDirRec);
			return FALSE;
		}
		if (!ReadDirectoryRecord(pDevice, (LPBYTE)cdb, lpBuf
			, volDesc.ISO_9660.uiLogicalBlkCoef, volDesc.ISO_9660.uiRootDataLen, 0, pDirRec, nDirPosNum, pVOB)) {
			FreeAndNull(pDirRec);
			return FALSE;
		}
		FreeAndNull(pDirRec);
	}
	return TRUE;
}
