#pragma once

#include <string>
#include <cstdint>
#include <span>
#include <vector>
#include <vulkan/vulkan.h>

namespace mvtk
{
	class Instance
	{
	public:
		class Builder
		{
			friend class Instance;
		public:
			Builder(const Builder&) = delete;
			Builder(Builder&&) = delete;

			Builder& name(const std::string& applicationName) noexcept
			{
				mApplicationName = applicationName;
				return *this;
			}

			Builder& version(int major, int minor, int patch) noexcept
			{
				mApplicationVersion = VK_MAKE_VERSION(major, minor, patch);
				return *this;
			}

			Builder& extension(const std::span<const char*>& extensions) noexcept
			{
				mExtensions.insert(mExtensions.end(), extensions.begin(), extensions.end());
				return *this;
			}

			Builder& extension(const char* extension) noexcept
			{
				mExtensions.push_back(extension);
				return *this;
			}

			Instance build()
			{
				return Instance(*this);
			}
		private:
			Builder() noexcept = default;

			std::string mApplicationName;
			int mApplicationVersion = 0;
			std::vector<const char*> mExtensions;
		};

		~Instance() noexcept;

		Instance(const Instance&) = delete;
		Instance& operator=(const Instance&) = delete;
		Instance(Instance&& other) noexcept;
		Instance& operator=(Instance&&) = delete;

		operator VkInstance() const noexcept { return mHandle; }

		static Builder builder() noexcept
		{
			return Builder();
		}
	private:
		Instance(const Builder& builder);

		VkInstance mHandle;
	};
}