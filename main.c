#ifndef _VK_DEBUG_
#	define _VK_DEBUG_
#endif

#include "headers.h"

void destroy_window(void)
{
	//..
}

_Bool initialize_window(void)
{
	//...

	return 1;	
}

int main(void)
{	
	if(initializeVulkan() != 1)
	{
		return EXIT_FAILURE;
	}

	//...

	return EXIT_SUCCESS;
}

