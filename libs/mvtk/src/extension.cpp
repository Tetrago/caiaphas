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
		return std::all_of(extensions.begin(), extensions.end(), [&](const char* name)
			{
				return std::any_of(available.begin(), available.end(), [&](VkExtensionProperties props)
					{
						return strcmp(props.extensionName, name) == 0;
					});
			});
	}

	bool validate_required_layers(std::span<const char* const> layers) noexcept
	{
		auto available = get_layers();
		return std::all_of(layers.begin(), layers.end(), [&](const char* name)
			{
				return std::any_of(available.begin(), available.end(), [&](VkLayerProperties props)
					{
						return strcmp(props.layerName, name) == 0;
					});
			});
	}
}