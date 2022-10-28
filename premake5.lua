workspace "HurmaEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "HurmaEngine/3dParty/GLFW"
include "HurmaEngine/3dParty/GLAD"
include "HurmaEngine/3dParty/ImGui"
	
project "HurmaEngine"
	location "HurmaEngine"
	kind "SharedLib"
	
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
    links
	{
		"GLFW",
        "GLAD",
		"ImGui"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/3dparty/plog/include",
		"%{prj.name}/3dparty/spdlog/include",
        "%{prj.name}/3dparty/GLFW/include",
		"%{prj.name}/3dparty/GLAD/include",
		"%{prj.name}/3dparty/ImGui",
		"%{prj.name}/3dparty/glm",
		"%{prj.name}/3dparty/stb_image",
		"%{prj.name}/src"
	} 
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
	defines 
	{
		"HURMA_BUILD"
	}
	
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/HurmaGame")
	}
	
	filter "configurations:Debug"
		defines "HURMA_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HURMA_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HURMA_DIST"
		optimize "On"
		
project "HurmaGame"
	location "HurmaGame"
	kind "ConsoleApp"
	
	language "C++"
	
	links
	{
		"HurmaEngine"
	}
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"HurmaEngine/src",
		"HurmaEngine/3dparty/glm",
		"HurmaEngine/3dparty/GLAD/include"
	} 

	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "HURMA_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HURMA_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HURMA_DIST"
		optimize "On"
	