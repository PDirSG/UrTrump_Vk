struct Application
{ VkResult Result;
	VkInstance 
	  Instance;

#ifdef _VK_DEBUG_
	VkDebugReportCallbackEXT
	  DebugReportCallback;
#endif
	VkSurfaceKHR 
	  Surface;
	
	//...
} Game;

#include \
	 "Utility/VkResult.c"

#define __Log(message) \
	printf("%s \n", message)
#define VkLog(message) \
	printf("%s: %s \n", message, VkGetResultString(Game.Result))

uint32_t InstanceExtensionCount;
const char **InstanceExtensions;

#define RequiredInstanceExtensionCount \
		InstanceExtensionCount
const char **RequiredInstanceExtensions;

_Bool VkGetInstanceExtensions(void)
{
	Game.Result = vkEnumerateInstanceExtensionProperties(NULL, &InstanceExtensionCount, NULL);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate intance extension count");
		return 0;
	}

	VkExtensionProperties *InstanceExtensionProperties;
	{
		InstanceExtensions = malloc(InstanceExtensionCount * sizeof(const char *));

		if(InstanceExtensions == NULL)
		{
			__Log("Error: Memory allocation failed for InstanceExtensions");
			return 0;
		}

		InstanceExtensionProperties = malloc(InstanceExtensionCount * sizeof(VkExtensionProperties));

		if(InstanceExtensionProperties == NULL)
		{
			__Log("Error: Memory allocation failed for InstanceExtensionProperties");
		 	free(InstanceExtensions);

			return 0;
		}
	}

	Game.Result = vkEnumerateInstanceExtensionProperties(NULL, &InstanceExtensionCount, InstanceExtensionProperties);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate intance extensions");
		free(InstanceExtensionProperties);
	  	free(InstanceExtensions);

		return 0;
	}

	for(uint32_t I = 0; I < InstanceExtensionCount; I++)
	{
		InstanceExtensions[I] =	strdup(InstanceExtensionProperties[I].extensionName);
	}
   	free(InstanceExtensionProperties);

	return 1;
}

_Bool VkGetRequiredInstanceExtensions(void)
{
	if(VkGetInstanceExtensions() == 0)
		return 0;

#if defined(_VK_DEBUG_)
	_Bool ExtensionNotExists[3] = {VK_TRUE, VK_TRUE, VK_TRUE};
#elif !defined(_VK_DEBUG_)
  	_Bool ExtensionNotExists[2] = {VK_TRUE, VK_TRUE};
#endif
	for(uint32_t I = 0; I < InstanceExtensionCount; I++)
	{
		if(ExtensionNotExists[0])
		{
			if(strcmp(VK_KHR_SURFACE_EXTENSION_NAME, InstanceExtensions[I]) == 0)
			{
				ExtensionNotExists[0] = VK_FALSE;
				continue;
			}
		}
		else if(ExtensionNotExists[1])
		{
		 	if(strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, InstanceExtensions[I]) == 0)
			{
				ExtensionNotExists[1] = VK_FALSE;
				continue;
			}
		}
#ifdef _VK_DEBUG_
		else if(ExtensionNotExists[2])
		{
			if(strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, InstanceExtensions[I]) == 0)
			{
				ExtensionNotExists[2] = VK_FALSE;
				continue;
			}
		}
#endif
		else
		{
			break;
		}	
	}
	free(InstanceExtensions);

#if defined(_VK_DEBUG_)
    if(ExtensionNotExists[0] || ExtensionNotExists[1] || ExtensionNotExists[2])
#elif !defined(_VK_DEBUG_)
    if(ExtensionNotExists[0] || ExtensionNotExists[1])
#endif
	{
		__Log("Error: Failed to find required instance extensions for application");
		return 0;
	}

#if defined(_VK_DEBUG_)
    RequiredInstanceExtensions = malloc(3 * sizeof(const char *));
#elif !defined(_VK_DEBUG_)
    RequiredInstanceExtensions = malloc(2 * sizeof(const char *));
#endif

	if(RequiredInstanceExtensions != NULL)
	{
		RequiredInstanceExtensions[0] = VK_KHR_SURFACE_EXTENSION_NAME; RequiredInstanceExtensions[1] = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
#if defined(_VK_DEBUG_)
		RequiredInstanceExtensions[2] = 
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

		RequiredInstanceExtensionCount = 3;
#elif !defined(_VK_DEBUG_)
		RequiredInstanceExtensionCount = 2;
#endif
	}
	else
	{
		__Log("Error: Memory allocation failed for RequiredInstanceExtensions");
		return 0;
	}

	return 1;
}

uint32_t InstanceLayerCount;
#ifdef _VK_DEBUG_
const char **InstanceLayers;
#endif

#define OptionalInstanceLayerCount \
		InstanceLayerCount
const char **OptionalInstanceLayers;

_Bool VkGetOptionalInstanceLayers(void)
{
#if defined(_VK_DEBUG_)
	Game.Result = vkEnumerateInstanceLayerProperties(&InstanceLayerCount, NULL);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate instance layer count");

		free(RequiredInstanceExtensions);
		return 0;
	}

	VkLayerProperties *InstanceLayerProperties;
	{
		InstanceLayers = malloc(InstanceLayerCount * sizeof(const char *));

		if(InstanceLayers == NULL)
		{
			__Log("Error: Memory allocation failed for InstanceLayers");

			free(RequiredInstanceExtensions);
			return 0;
		}

		InstanceLayerProperties = malloc(InstanceLayerCount * sizeof(VkLayerProperties));

		if(InstanceLayerProperties == NULL)
		{
			__Log("Error: Memory allocation failed for LayerProperties");
			free(InstanceLayers);

			free(RequiredInstanceExtensions);
			return 0;
		}
	}

	Game.Result = vkEnumerateInstanceLayerProperties(&InstanceLayerCount, InstanceLayerProperties);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate instance layers");
		free(InstanceLayerProperties);
		free(InstanceLayers);

		free(RequiredInstanceExtensions);
		return 0;
	}

	for(uint32_t I = 0; I < InstanceLayerCount; I++)
	{
		InstanceLayers[I] = strdup(InstanceLayerProperties[I].layerName);
	}
	free(InstanceLayerProperties);

	_Bool ValidationLayerNotExists 
			= VK_TRUE;
	for(uint32_t I = 0; I < InstanceLayerCount; I++)
	{
		if(strcmp(InstanceLayers[I], "VK_LAYER_LUNARG_standard_validation"))
	   	{
			ValidationLayerNotExists = VK_FALSE;
			break;
		}
	}
	free(InstanceLayers);

	if(ValidationLayerNotExists)
	{
		__Log("Error: Failed to find required instance layer for validation");

		free(RequiredInstanceExtensions);
		return 0;
	}

	OptionalInstanceLayers = malloc(1 * sizeof(const char *));

	if(OptionalInstanceLayers != NULL)
	{
		*(OptionalInstanceLayers) = "VK_LAYER_LUNARG_standard_validation"; OptionalInstanceLayerCount = 1;
	}
	else
	{
		__Log("Error: Memory allocation failed for OptionalInstanceLayers");

		free(RequiredInstanceExtensions);
		return 0;
	}

#elif !defined(_VK_DEBUG_)
	OptionalInstanceLayerCount = 0; OptionalInstanceLayers = NULL;
#endif

	return 1;
}

VkApplicationInfo ApplicationInfo;
VkInstanceCreateInfo InstanceCreateInfo;

void setApplicationInfo(void)
{
    ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ApplicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
}
_Bool setInstanceCreateInfo(void)
{setApplicationInfo();

    InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;

	{
		if(VkGetRequiredInstanceExtensions() != 1 || VkGetOptionalInstanceLayers() != 1)
			return 0;

		InstanceCreateInfo.enabledExtensionCount = RequiredInstanceExtensionCount;
    		InstanceCreateInfo.ppEnabledExtensionNames = RequiredInstanceExtensions;

    		InstanceCreateInfo.enabledLayerCount = OptionalInstanceLayerCount;
    		InstanceCreateInfo.ppEnabledLayerNames = OptionalInstanceLayers;
	}

    return 1;
}

#ifdef _VK_DEBUG_

PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallback;

void destroyDebugReportCallback(void)
{
	vkDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(Game.Instance, "vkDestroyDebugReportCallbackEXT");

	if(vkDestroyDebugReportCallback)
	{
		vkDestroyDebugReportCallback(Game.Instance, Game.DebugReportCallback, NULL);
	}
	else
	{
		__Log("Non-fatal error: Failed to load required extension function for destroying debug report callback");
	}
}

#include \
     "Utility/VkObjectType.c"

uint32_t debugReportCallback
	(
	VkDebugReportFlagsEXT flags,

	VkDebugReportObjectTypeEXT objectType, 
		uint64_t object,

	size_t location, int32_t messageCode, const char *layerPrefix,
		const char *message, 
		
	void *userData
	)
{
	if(flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		puts("Error: ");
	if(flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) 
		puts("Warning: "); 	
	if(flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)  
		puts("Performance warning: ");

	printf("Generated for a/an \"%s\" object, handle for that object is %lu - Layer prefix: %s, location: %lu, message code: %d, message: %s - Triggered by \"%s\" \n", 
		VkGetObjectTypeString(objectType), object, layerPrefix, location, messageCode, message, "Validation layer");

	return VK_FALSE;
}

PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallback;

_Bool initializeDebugReportCallback(void)
{
	vkCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(Game.Instance, "vkCreateDebugReportCallbackEXT");

	if(!vkCreateDebugReportCallback)
	{
	    __Log("Error: Failed to load required extension function for initializing debug report callback");

	    vkDestroyInstance(Game.Instance, NULL);
 	    return 0;
	}

	VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfo; DebugReportCallbackCreateInfo.sType = 
		VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	
	DebugReportCallbackCreateInfo.flags =
		VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

	DebugReportCallbackCreateInfo.pfnCallback = 
       &debugReportCallback; 
	Game.Result = vkCreateDebugReportCallback(Game.Instance, &DebugReportCallbackCreateInfo, NULL, &Game.DebugReportCallback);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to create debug report callback");

		vkDestroyInstance(Game.Instance, NULL);
		return 0;
	}

	return 1;
}

#endif

void destroySurface(void)
{
	vkDestroySurfaceKHR(Game.Instance, Game.Surface, NULL);
}

_Bool initialize_window(void); 
	Display *_Display; Window _Window;

_Bool initializeSurface(void)
{
	if(initialize_window() != 1)
	{
#ifdef _VK_DEBUG_
		destroyDebugReportCallback();
#endif		
		vkDestroyInstance(Game.Instance, NULL);

		return 0;
	}
	
	VkXlibSurfaceCreateInfoKHR XlibSurfaceCreateInfo;	
	XlibSurfaceCreateInfo.sType = 
	  VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;

	XlibSurfaceCreateInfo.dpy
		= _Display; 
	XlibSurfaceCreateInfo.window
		= _Window; 

	Game.Result = vkCreateXlibSurfaceKHR(Game.Instance, &XlibSurfaceCreateInfo, NULL, &Game.Surface);	
	
	if(Game.Result != 0)
	{
		VkLog("Error: Failed to create window surface");

#ifdef _VK_DEBUG_
		destroyDebugReportCallback();
#endif
		vkDestroyInstance(Game.Instance, NULL);

		return 0;
	}

	return 1;
}

void destroyInstance(void)
{
	destroySurface();
#ifdef _VK_DEBUG_
	destroyDebugReportCallback();
#endif
	vkDestroyInstance(Game.Instance, NULL);
}

_Bool initializeInstance(void)
{
	if(setInstanceCreateInfo() != 1)
		return 0;

	Game.Result = vkCreateInstance(&InstanceCreateInfo, NULL, &Game.Instance);

#ifdef _VK_DEBUG_
	free(OptionalInstanceLayers);
#endif
	free(RequiredInstanceExtensions);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to create instance");
		return 0;
	}

#ifdef _VK_DEBUG_
	if(initializeDebugReportCallback() != 1)
	{
		return 0;
	}
#endif

	if(initializeSurface() != 1)
	{
		return 0;
	}

	return 1;
}

void destroyDevice(void)
{
	//...
}

//...

_Bool deviceIsSuitable(VkPhysicalDevice PhysicalDevice)
{
	//...
}

_Bool initializeDevice(void)
{
	uint32_t 
		PhysicalDeviceCount;

	Game.Result = vkEnumeratePhysicalDevices(Game.Instance, &PhysicalDeviceCount, NULL);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate physical device count");

		destroyInstance();
		return 0;
	}

	if(PhysicalDeviceCount == 0)
	{
		__Log("Error: You do not have any physical devices with Vulkan support");

		destroyInstance();
		return 0;
	}

	VkPhysicalDevice *PhysicalDevices;
	{	
		PhysicalDevices = malloc(PhysicalDeviceCount * sizeof(VkPhysicalDevice));

		if(PhysicalDevices == NULL)
		{
			__Log("Error: Memory allocation failed for PhysicalDevices");

			destroyInstance();
			return 0;
		}
	}

	Game.Result = vkEnumeratePhysicalDevices(Game.Instance, &PhysicalDeviceCount, PhysicalDevices);

	if(Game.Result != 0)
	{
		VkLog("Error: Failed to enumerate physical devices");
		free(PhysicalDevices);

		destroyInstance();
		return 0;
	}

	VkPhysicalDevice * SuitablePhysicalDevices = NULL; 
	VkPhysicalDevice *_SuitablePhysicalDevices;

	uint32_t 
		SuitablePhysicalDeviceCount = 0;

	for(uint32_t I = 0; I < PhysicalDeviceCount; I++)
	{
		if(deviceIsSuitable(PhysicalDevices[I]))
		{
			SuitablePhysicalDeviceCount++; _SuitablePhysicalDevices = realloc(SuitablePhysicalDevices, SuitablePhysicalDeviceCount * sizeof(VkPhysicalDevice));

			if(_SuitablePhysicalDevices != NULL)
			{
				SuitablePhysicalDevices = _SuitablePhysicalDevices; SuitablePhysicalDevices[SuitablePhysicalDeviceCount - 1] = PhysicalDevices[I];
			}
			else
			{
				__Log("Error: Memory reallocation failed for SuitablePhysicalDevices");
				free(SuitablePhysicalDevices);
				free(	     PhysicalDevices);

				destroyInstance();		
				return 0;
			}
		}
	}
	free(PhysicalDevices);

	if(SuitablePhysicalDeviceCount == 0)
	{
		__Log("Error: No suitable physical device found");

		destroyInstance();
		return 0;
	}

	uint32_t SelectedPhysicalDevice;

	if(SuitablePhysicalDeviceCount == 1)
		SelectedPhysicalDevice = 0;
	else
	{
		//Give output and take input from user. Accoring to this input select the device.
	}

	//...

	return 1;
}

_Bool initializeVulkan(void)
{
	if(initializeInstance() != 1 || initializeDevice() != 1)  
		return 0;

	//...

	return 1;
}
