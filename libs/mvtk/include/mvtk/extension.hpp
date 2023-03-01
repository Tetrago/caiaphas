#pragma once

#include <vector>
#include <span>

#include <vulkan/vulkan.h>

namespace mvtk
{
	std::vector<VkExtensionProperties> get_extensions() noexcept;
	bool has_required_extensions(std::span<const char* const> extensions) noexcept;
}
