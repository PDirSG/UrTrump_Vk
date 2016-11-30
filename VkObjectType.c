const char *VkGetObjectTypeString(VkDebugReportObjectTypeEXT objectType)
{
	switch(objectType)
	{
		case VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT: 
			return "VkInstance";
		case VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT: 
			return "VkPhysicalDevice";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT:
			return "VkDevice";
		case VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT:
			return "VkQueue";
		case VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT:
			return "VkSemaphore";
		case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT:
			return "VkCommandBuffer";
		case VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT:
			return "VkFence";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT:
			return "VkDeviceMemory";
		case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT:
			return "VkBuffer";
		case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT:
			return "VkImage";
		case VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT:
			return "VkEvent";
		case VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT: 
			return "VkQueryPool";
		case VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT: 
			return "VkBufferView";
		case VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT:
			return "VkImageView";
		case VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT:
			return "VkShaderModule";
		case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT:
			return "VkPipelineCache";
		case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT:
			return "VkPipelineLayout";
		case VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT:
			return "VkRenderPass";
		case VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT:
			return "VkPipeline";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT: 
			return "VkDescriptorSetLayout";
		case VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT: 
			return "VkSampler";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT: 
			return "VkDescriptorPool";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT: 
			return "VkDescriptorSet";
		case VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT: 
			return "VkFramebuffer";
		case VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT: 
			return "VkCommandPool";
		case VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT: 
			return "VkSurfaceKHR";
		case VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT: 
			return "VkSwapchainKHR";
		case VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_EXT: 
			return "VkDebugReportCallbackEXT";
		default:
			return "Unknown";
	}
}
