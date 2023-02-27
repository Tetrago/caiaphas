#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <vulkan/vulkan.h>

namespace mvtk
{
	using InstanceExtensionRequesterFn = uint32_t(*)(const char***);

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

			Builder& extension(InstanceExtensionRequesterFn fn) noexcept
			{
				const char** extensions;
				uint32_t count = fn(&extensions);

				for(int i = 0; i < count; ++i)
				{
					mExtensions.push_back(extensions[i]);
				}

				return *this;
			}

			Instance build()
			{
				return Instance(*this);
			}
		private:
			Builder() noexcept = default;

			std::string mApplicationName = "";
			int mApplicationVersion = 0;
			std::vector<const char*> mExtensions{};
		};

		~Instance() noexcept;

		Instance(const Instance&) = delete;
		Instance& operator=(const Instance&) = delete;
		Instance(Instance&& other) noexcept;
		Instance& operator=(Instance&&) = delete;

		operator VkInstance() const noexcept { return mHandle; }

		static Builder&& builder() noexcept
		{
			return Builder();
		}
	private:
		Instance(const Builder& builder);

		VkInstance mHandle;
	};
}