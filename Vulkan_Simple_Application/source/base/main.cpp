#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <string>

#include <GLFW/glfw3.h>

const uint32_t WIDTH = 1260;
const uint32_t HEIGHT = 720;
const std::string TITLE = "TRIANGLE";

class Triangle
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

/**
* Privacy function (not exposed)
*/
private:
	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}

/**
* Only private function calls are available
*/
private:
	void createInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Triangle";
		appInfo.pEngineName = "Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		/**
		* 接下来的结构不是可选的，是告诉 Vulkan 驱动程序我们所需要的全局拓展和验证层
		*/
		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;

		/**
		* Vulkan 是一个平台无关的图形 API,因此需要一些拓展来与 window 相接
		* glfw 提供了一个方便的函数，它会返回所需拓展，并将其填写进结构中
		*/
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
		instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;

		instanceCreateInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS)
			throw std::runtime_error("failed to create instance!");
	}

/**
* Member variables
*/
private:
	GLFWwindow* window;
	VkInstance instance;

};

int main()
{
	Triangle triangle;

	try
	{
		triangle.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}