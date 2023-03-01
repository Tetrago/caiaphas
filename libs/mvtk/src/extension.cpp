#include "mvtk/extension.hpp"

#include <cstdint>

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

	bool has_required_extensions(std::span<const char* const> extensions) noexcept
	{
		auto available = get_extensions();

		for(const char* ext : extensions)
		{
			for(VkExtensionProperties props : available)
			{
				if(strcmp(ext, props.extensionName) != 0) continue;
				goto next;
			}

			return false;
		next:;
		}

		return true;
	}
}