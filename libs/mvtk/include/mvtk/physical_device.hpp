#pragma once

#include <optional>
#include <vector>
#include <tuple>
#include <vulkan/vulkan.h>

namespace mvtk
{
	class Instance;

	struct PhysicalDevice
	{
		VkPhysicalDevice handle;
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceProperties properties;
	};

	PhysicalDevice read_physical_device(VkPhysicalDevice handle) noexcept;
	std::vector<PhysicalDevice> get_physical_devices(const Instance& instance) noexcept;


	class PhysicalDeviceSelector
	{
		friend PhysicalDeviceSelector physical_device_selector(const Instance&) noexcept;
	public:
		~PhysicalDeviceSelector() noexcept = default;

		PhysicalDeviceSelector(const PhysicalDeviceSelector&) = delete;
		PhysicalDeviceSelector& operator=(const PhysicalDeviceSelector&) = delete;

		PhysicalDeviceSelector& requireDiscrete() noexcept;

		std::optional<PhysicalDevice> select() noexcept;
	private:
		PhysicalDeviceSelector(const std::vector<PhysicalDevice>& devices) noexcept;

		std::vector<std::tuple<int, PhysicalDevice>> mDevices;
	};

	inline PhysicalDeviceSelector physical_device_selector(const Instance& instance) noexcept
	{
		return PhysicalDeviceSelector(get_physical_devices(instance));
	}
}