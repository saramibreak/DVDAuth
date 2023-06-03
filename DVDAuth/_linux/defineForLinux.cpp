
void SetLastError(int errcode)
{
	errno = errcode;
}

int GetLastError(void)
{
	return errno;
}

#ifdef __linux__
int CloseHandle(int fd)
{
	int ret = close(fd);
	ret = ret != -1 ? TRUE : FALSE;
	return ret;
}

int DeviceIoControl(int fd, unsigned long ioCtlCode, void* inbuf, unsigned long a, void* b, unsigned long c, unsigned long* d, void* e)
{
	UNREFERENCED_PARAMETER(a);
	UNREFERENCED_PARAMETER(b);
	UNREFERENCED_PARAMETER(c);
	UNREFERENCED_PARAMETER(d);
	UNREFERENCED_PARAMETER(e);
	PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER p = (PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER)inbuf;
	int ret = ioctl(fd, ioCtlCode, &(p->io_hdr));
	memcpy(&(p->SenseData), p->Dummy, 18);
	ret = ret != -1 ? TRUE : FALSE;
	return ret;
}
#elif __MACH__
// https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/WorkingWithSAM/WWS_SAMDevInt/WWS_SAM_DevInt.html#//apple_ref/doc/uid/TP30000387-SW1
IOCFPlugInInterface** plugInInterface;
MMCDeviceInterface** mmcInterface;
SCSITaskDeviceInterface** interface;

SCSITaskInterface** GetSCSITaskInterface(char* path)
{
#if 0
	io_service_t service = IORegistryEntryFromPath(kIOMasterPortDefault, path);
#else
	UNREFERENCED_PARAMETER(path);
	// Create the dictionaries
	CFMutableDictionaryRef matchingDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
	CFMutableDictionaryRef subDict      = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);

	// Create a dictionary with the "SCSITaskDeviceCategory" key = "SCSITaskAuthoringDevice"
	CFDictionarySetValue(subDict, CFSTR(kIOPropertySCSITaskDeviceCategory), CFSTR(kIOPropertySCSITaskAuthoringDevice));

	// Add the dictionary to the main dictionary with the key "IOPropertyMatch" to
	// narrow the search to the above dictionary.
	CFDictionarySetValue(matchingDict, CFSTR(kIOPropertyMatchKey), subDict);

	io_iterator_t iterator = 0;
	IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iterator);

	io_service_t service = 0;
	if (iterator) {
		io_service_t tmp;
		do {
			tmp = IOIteratorNext(iterator);
			if (tmp) {
				io_name_t service_class = "";
				io_string_t service_path = "";
				IORegistryEntryGetPath(tmp, kIOServicePlane, service_path);
				IOObjectGetClass(tmp, service_class);
//				printf("Class: %s\nPath: %s\n", service_class, service_path);
				service = tmp;
			}
		} while (tmp);
		IOObjectRelease(iterator);
	}
	if (!service) {
		return NULL;
	}
#endif
#if 0
	CFStringRef deviceNameFromReg;
	if ((deviceNameFromReg = (CFStringRef)IORegistryEntrySearchCFProperty(
		(io_registry_entry_t)service, kIOServicePlane, CFSTR(kIOBSDNameKey)
		, kCFAllocatorDefault, kIORegistryIterateRecursively)) == NULL) {
		fprintf(stderr, "Failed: IORegistryEntrySearchCFProperty\n");
		return NULL;
	}

	char deviceName[_MAX_FNAME];
	if (CFStringGetCString(deviceNameFromReg, deviceName, sizeof(deviceName), kCFStringEncodingUTF8) == FALSE) {
		fprintf(stderr, "Failed: CFStringGetCString\n");
		return NULL;
	}

	char* unmountCmd;
	const char* cmd = "sudo /usr/sbin/diskutil unmountDisk";
	const char* devNull = "> /dev/null";
	size_t cmdLen = strlen(cmd) + strlen(deviceName) + strlen(devNull) + 3;
	if ((unmountCmd = (char*)malloc(cmdLen)) == NULL) {
		fprintf(stderr, "Failed: malloc\n");
		return NULL;
	}
	snprintf(unmountCmd, cmdLen, "%s %s %s", cmd, deviceName, devNull);
	printf("unmountCmd: %s\n", unmountCmd);
	CFRelease(deviceNameFromReg);

	if (system(unmountCmd) != 0) {
		free(unmountCmd);
		fprintf(stderr, "Failed: system\n");
		return NULL;
	}
	free(unmountCmd);
#endif
	SInt32        score;
	HRESULT       herr;
	kern_return_t err;

	// Create the IOCFPlugIn interface so we can query it.
	if (noErr != (err = IOCreatePlugInInterfaceForService(
		service, kIOMMCDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score))) {
		fprintf(stderr, "Failed: IOCreatePlugInInterfaceForService returned %x\n", err);
		return NULL;
	}
	// Query the interface for the MMCDeviceInterface.
	if (S_OK != (herr = (*plugInInterface)->QueryInterface(
		plugInInterface, CFUUIDGetUUIDBytes(kIOMMCDeviceInterfaceID), (LPVOID*)(&mmcInterface)))) {
		fprintf(stderr, "Failed: QueryInterface returned %x\n", herr);
		return NULL;
	}
	if (NULL == (interface = (*mmcInterface)->GetSCSITaskDeviceInterface(mmcInterface))) {;
		fprintf(stderr, "Failed: GetSCSITaskDeviceInterface returned NULL\n");
		return NULL;
	}
	if (noErr != (err = (*interface)->ObtainExclusiveAccess(interface))) {
		fprintf(stderr, "Failed: ObtainExclusiveAccess returned %x\n", err);
		return NULL;
	}
	// Create a task now that we have exclusive access
	return (*interface)->CreateSCSITask(interface);
}

int CloseHandle(int fd)
{
	int ret = close(fd);
	ret = ret != -1 ? TRUE : FALSE;
	return ret;
}

int CloseHandleTask(SCSITaskInterface** task)
{
	// Release the task interface
	(*task)->Release(task);
	(*interface)->ReleaseExclusiveAccess(interface);

	// Release the SCSITaskDeviceInterface.
	(*interface)->Release(interface);
	(*mmcInterface)->Release(mmcInterface);

	IODestroyPlugInInterface(plugInInterface);
	return 1;
}

int DeviceIoControl(SCSITaskInterface** task, unsigned long aa, void* inbuf, unsigned long a, void* b, unsigned long c, unsigned long* d, void* e)
{
	UNREFERENCED_PARAMETER(aa);
	UNREFERENCED_PARAMETER(a);
	UNREFERENCED_PARAMETER(b);
	UNREFERENCED_PARAMETER(c);
	UNREFERENCED_PARAMETER(d);
	UNREFERENCED_PARAMETER(e);
	PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER p = (PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER)inbuf;
	IOReturn ret = (*task)->ExecuteTaskSync(task, &(p->tmpSenseData), &(p->taskStatus), &(p->transferCount));
	memcpy(&(p->SenseData), &(p->tmpSenseData), 18);
	ret = ret != -1 ? TRUE : FALSE;
	return ret;
}
#endif
