#pragma once

#include <vector>
#include <span>

#include <vulkan/vulkan.h>

namespace mvtk
{
	std::vector<VkExtensionProperties> get_extensions() noexcept;
	std::vector<VkLayerProperties> get_layers() noexcept;

	bool validate_required_extensions(std::span<const char* const> extensions) noexcept;
	bool validate_required_layers(std::span<const char* const> layers) noexcept;
}
