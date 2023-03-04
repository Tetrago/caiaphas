#include "mvtk/physical_device.hpp"

#include <algorithm>
#include <cstdint>

#include "mvtk/instance.hpp"

namespace mvtk
{
	PhysicalDevice read_physical_device(VkPhysicalDevice handle) noexcept
	{
		PhysicalDevice device{};
		device.handle = handle;
		vkGetPhysicalDeviceFeatures(handle, &device.features);
		vkGetPhysicalDeviceProperties(handle, &device.properties);

		return device;
	}

	std::vector<PhysicalDevice> get_physical_devices(const Instance& instance) noexcept
	{
		uint32_t count;
		vkEnumeratePhysicalDevices(instance, &count, nullptr);
		std::vector<VkPhysicalDevice> devices(count);
		vkEnumeratePhysicalDevices(instance, &count, devices.data());
		
		std::vector<PhysicalDevice> vec(count);
		std::transform(devices.begin(), devices.end(), vec.begin(), read_physical_device);

		return vec;
	}

	PhysicalDeviceSelector::PhysicalDeviceSelector(const std::vector<PhysicalDevice>& devices) noexcept
	{
		mDevices.resize(devices.size());
		std::transform(devices.begin(), devices.end(), mDevices.begin(), [](const PhysicalDevice& device)
			{
				return std::make_tuple(0, device);
			});
	}

	PhysicalDeviceSelector& PhysicalDeviceSelector::requireDiscrete() noexcept
	{
		std::remove_if(mDevices.begin(), mDevices.end(), [](const std::tuple<int, PhysicalDevice>& tuple)
			{
				return std::get<1>(tuple).properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
			});

		return *this;
	}

	std::optional<PhysicalDevice> PhysicalDeviceSelector::select() noexcept
	{
		return mDevices.empty() ? std::nullopt : std::optional(std::get<1>(mDevices[0]));
	}
}