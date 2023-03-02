#include "mvtk/instance.hpp"

#include "mvtk/extension.hpp"
#include "log.hpp"

namespace mvtk
{
	namespace
	{
		VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
			VkDebugUtilsMessageSeverityFlagBitsEXT severity,
			VkDebugUtilsMessageTypeFlagsEXT types,
			const VkDebugUtilsMessengerCallbackDataEXT* pData,
			void* pUser)
		{
			tk::LogLevel level = [severity]()
			{
				switch(severity)
				{
				default: return tk::LogLevel::Trace;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return tk::LogLevel::Info;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return tk::LogLevel::Warn;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return tk::LogLevel::Error;
				}
			}();

			logger().log(level, "[Vulkan] {}", pData->pMessage);
			return VK_FALSE;
		}

		VkDebugUtilsMessengerCreateInfoEXT debug_messenger_create_info()
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			createInfo.pfnUserCallback = debug_callback;

			return createInfo;
		}
	}

	Instance::Instance(const Builder& builder)
	{
		if(!validate_required_extensions(builder.mExtensions))
		{
			throw std::runtime_error("Failed to find all required instance extensions");
		}

		if(!validate_required_layers(builder.mLayers))
		{
			throw std::runtime_error("Failed to final all required instance layers");
		}

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = builder.mApplicationName.data();
		appInfo.applicationVersion = builder.mApplicationVersion;
		appInfo.pEngineName = "mvtk";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkDebugUtilsMessengerCreateInfoEXT messengerInfo = debug_messenger_create_info();

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = builder.mExtensions.size();
		createInfo.ppEnabledExtensionNames = builder.mExtensions.data();
		createInfo.enabledLayerCount = 0;
		createInfo.enabledLayerCount = builder.mLayers.size();
		createInfo.ppEnabledLayerNames = builder.mLayers.data();

		if(builder.mDebug)
		{
			createInfo.pNext = &messengerInfo;
		}

		if(vkCreateInstance(&createInfo, nullptr, &mHandle) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan instance");
		}

		if(!builder.mDebug) return;

		if(getFunction<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT")
			(mHandle, &messengerInfo, nullptr, &mMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to initialize debug messenger");
		}
	}

	Instance::~Instance() noexcept
	{
		if(mMessenger)
		{
			getFunction<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT")(mHandle, mMessenger, nullptr);
		}

		vkDestroyInstance(mHandle, nullptr);
	}

	Instance::Instance(Instance&& other) noexcept
		: mHandle(other.mHandle)
	{}
}