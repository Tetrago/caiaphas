#pragma once

#include <vector>
#include <span>

#include <vulkan/vulkan.h>

namespace mvtk
{
	/**
	 * Retrieves all available instance extensions supported by the current environment.
	 * 
	 * Does not depend on the initialization of any other Vulkan objects, and can be called
	 * at any time.
	 *
	 * @return Vector of all usable extensions.
	 */
	std::vector<VkExtensionProperties> get_extensions() noexcept;

	/**
	 * Retrieves all available instance layers supported by the current environment.
	 * 
	 * Does not depend on the initialization of any other Vulkan objects, and can be called
	 * at any time. Given that device level layers are no longer supported, there is no other
	 * alternative function.
	 * 
	 * @return Vector of all usable layers.
	 */
	std::vector<VkLayerProperties> get_layers() noexcept;

	/**
	 * Checks to make sure that the requested instance extensions are supported.
	 * 
	 * Retrieves the available instance extensions supported by the current environment and checks
	 * that every extension requested is present.
	 *
	 * @param[in] extensions Span of the names of all extensions required.
	 * 
	 * @return Whether or not all requested extensions are present.
	 * 
	 * @see get_extensions()
	 */
	bool validate_required_extensions(std::span<const char* const> extensions) noexcept;

	/**
	 * Checks to make sure that the requested instance layers are supported.
	 * 
	 * Retrieves the available instance layers supported by the current environment and checks
	 * that every layer requested is present.
	 *
	 * @param[in] layers Span of the names of all extensions required.
	 * 
	 * @return Whether or not all requested layers are present.
	 * 
	 * @see get_layers()
	 */
	bool validate_required_layers(std::span<const char* const> layers) noexcept;
}
