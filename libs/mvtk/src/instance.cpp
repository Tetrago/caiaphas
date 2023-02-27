#include "mvtk/instance.hpp"

#include <stdexcept>

namespace mvtk
{
	Instance::Instance(const Builder& builder)
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = builder.mApplicationName.c_str();
		appInfo.applicationVersion = builder.mApplicationVersion;
		appInfo.pEngineName = "mvtk";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = builder.mExtensions.size();
		createInfo.ppEnabledExtensionNames = builder.mExtensions.data();
		createInfo.enabledLayerCount = 0;

		if(vkCreateInstance(&createInfo, nullptr, &mHandle) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan instance");
		}
	}

	Instance::~Instance() noexcept
	{
		vkDestroyInstance(mHandle, nullptr);
	}

	Instance::Instance(Instance&& other) noexcept
		: mHandle(other.mHandle)
	{}
}