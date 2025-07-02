workspace "Vulkan_SA"
	architecture "x64"

	configurations {
		"DebugX64",
		"ReleaseX64"
	}

VULKAN_SDK = os.getenv("Vulkan_SDK")

outdir = "%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{prj.name}/third_party/glfw"

project "Vulkan_Simple_Application"
	location "Vulkan_Simple_Application"
	kind "ConsoleApp"
	cppdialect "C++17"

	targetdir ("binaries/" .. outdir)
	objdir ("intermediation/" .. outdir)

	files
	{
		"%{prj.name}/source/base/**.cpp",
		"%{prj.name}/source/base/**.h",
		"%{prj.name}/third_party/glm/glm/**.hpp",
		"%{prj.name}/third_party/glm/glm/**.inl",
		"%{prj.name}/third_party/stb_image/**.h",
		"%{prj.name}/third_party/stb_image/**.cpp",
	}

	includedirs 
	{
		"%{VULKAN_SDK}/Include",
		"%{IncludeDir.GLFW}/include",
		"Vulkan_Simple_Application/third_party"
	}

	links
	{
		"vulkan-1.lib",
		"glfw3.lib",
	}

	libdirs
	{
		"%{VULKAN_SDK}/Lib",
		"%{IncludeDir.GLFW}/lib-vc2022",
	}

	defines
	{
		"GLFW_INCLUDE_VULKAN",
	}