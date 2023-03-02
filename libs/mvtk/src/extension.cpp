#include "mvtk/extension.hpp"

#include <cstdint>

#include "log.hpp"

namespace mvtk
{
	std::vector<VkExtensionProperties> get_extensions() noexcept
	{
		uint32_t count;
		vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
		std::vector<VkExtensionProperties> extensions(count);
		vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());

		return extensions;
	}

	std::vector<VkLayerProperties> get_layers() noexcept
	{
		uint32_t count;
		vkEnumerateInstanceLayerProperties(&count, nullptr);
		std::vector<VkLayerProperties> layers(count);
		vkEnumerateInstanceLayerProperties(&count, layers.data());

		return layers;
	}

	bool validate_required_extensions(std::span<const char* const> extensions) noexcept
	{
		auto available = get_extensions();

		for(const char* ext : extensions)
		{
			for(VkExtensionProperties props : available)
			{
				if(strcmp(ext, props.extensionName) != 0) continue;
				goto next;
			}

			logger().warn("Failed to location extension \"{}\"", ext);
			return false;

		next:
			logger().trace("Located extension \"{}\"", ext);
		}

		return true;
	}

	bool validate_required_layers(std::span<const char* const> layers) noexcept
	{
		auto available = get_layers();

		for(const char* layer : layers)
		{
			for(VkLayerProperties props : available)
			{
				if(strcmp(layer, props.layerName) != 0) continue;
				goto next;
			}

			logger().warn("Failed to location layer \"{}\"", layer);
			return false;

		next:
			logger().trace("Located extension \"{}\"", layer);
		}
	}
}