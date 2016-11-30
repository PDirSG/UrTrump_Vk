#ifndef commonH_H
#	define commonH_H

#	if !defined(__linux__)
#		error "This program is not compatible with your system!"
#	else
#		define VK_USE_PLATFORM_XLIB_KHR
#	endif

#	include <vulkan/vulkan.h>

#	include <stdio.h>
#	include <stdlib.h>
#	include <string.h>

#endif
