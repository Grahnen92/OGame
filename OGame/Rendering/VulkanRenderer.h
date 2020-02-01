#pragma once

#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstring>

#include <stdexcept>

#include <functional>
#include <algorithm>

#include <vector>
#include <array>
#include <set>


#include <fstream>

#include <chrono>

#include "Ogame/Game/Camera.h"

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

//struct TmpVertex {
//	glm::vec3 pos;
//	glm::vec3 color;
//
//	static VkVertexInputBindingDescription getBindingDescription() {
//		VkVertexInputBindingDescription bindingDescription = {};
//
//		bindingDescription.binding = 0;
//		bindingDescription.stride = sizeof(TmpVertex);
//		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//
//		return bindingDescription;
//	}
//
//	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
//		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
//
//		attributeDescriptions[0].binding = 0;
//		attributeDescriptions[0].location = 0;
//		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
//		attributeDescriptions[0].offset = offsetof(TmpVertex, pos);
//
//		attributeDescriptions[1].binding = 0;
//		attributeDescriptions[1].location = 1;
//		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//		attributeDescriptions[1].offset = offsetof(TmpVertex, color);
//
//		return attributeDescriptions;
//	}
//
//};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

struct vpUniformBufferObject
{
	glm::mat4 viewProj;
};
struct mUniformBufferObject
{
	glm::mat4 model;
};

//struct CameraPushConstants {
//	glm::mat4 view;
//	glm::mat4 proj;
//};

//const std::vector<TmpVertex> vertices = {
//	{ { -0.5f, -0.5f, 0.f },{ 1.0f, 0.0f, 0.0f } },
//	{ { 0.5f, -0.5f, 0.f },{ 0.0f, 1.0f, 0.0f } },
//	{ { 0.5f, 0.5f, 0.f },{ 0.0f, 0.0f, 1.0f } },
//	{ { -0.5f, 0.5f, 0.f },{ 1.0f, 1.0f, 1.0f } },
//
//	{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
//	{ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
//	{ { 0.5f, 0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f } },
//	{ { -0.5f, 0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f } }
//};
//
//const std::vector<uint16_t> indices = {
//	0, 1, 2, 2, 3, 0,
//	4, 5, 6, 6, 7, 4
//};
class VulkanRenderer {
public:

	~VulkanRenderer();

	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	void init()
	{
		initWindow();
		initVulkan();
		initCamera();
	}

	//Getters ======================================================================================================================================
	GLFWwindow* getWindow() { return window; }
	VkExtent2D* getSwapChainExtent() { return &swapChainExtent; }
	float getAspectRatio() { return swapChainExtent.width / (float)swapChainExtent.height; }
	VkDevice* getDevice() { return &device; }
	VkPhysicalDevice* getPhysicalDevice() { return &physicalDevice; }
	VkCommandPool* getCommandPool() { return &commandPool; }
	VkQueue* getGraphicsQueue(){ return &graphicsQueue;}
	std::vector<VkFramebuffer>* getSwapChainFrameBuffers() { return &swapChainFramebuffers; }
	VkRenderPass* getRenderPass() { return &renderPass; }
	VkPipeline* getGraphicsPipeline() { return &graphicsPipeline; }
	VkPipelineLayout* getPipeLineLayout() { return &pipelineLayout; }
	VkDescriptorSet* getDescriptorSet() { return &descriptorSet; }
	VkDescriptorSetLayout* getvpDescriptorSetLayout() { return &vpDescriptorSetLayout; }
	VkDescriptorSetLayout* getmDescriptorSetLayout() { return &mDescriptorSetLayout; }
	VkDescriptorPool* getDescriptorPool() { return &descriptorPool; }

	//Renderering ======================================================================================================================================
	void mainLoop();
	void updateCamera(class GameState* state);
	void updateUniformBuffer();
	void drawFrame();
	void recordCommandBuffer(std::vector<class VkRenderTask*>& renderObjects);


private:

	static void onWindowResized(GLFWwindow* window, int width, int height) {
		if (width == 0 || height == 0) return;

		VulkanRenderer* app = reinterpret_cast<VulkanRenderer*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}

	void recreateSwapChain();

	//Cleanup ============================================================================================================================

public:
	void cleanup();
private:
	void cleanupSwapChain();

	//Initialization ========================================================================================================================================
public:

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
	void initWindow();
	void initVulkan();
	void initCamera();

	void createInstance();

	void createLogicalDevice();
	//CREATE SURFACE FOR WINDOWS
	void createSurface();

	//GET REQUIRED EXTENSIONS =========================================
	std::vector<const char*> getRequiredExtensions();

	void createSwapChain();
	void createImageViews();

	void createFramebuffers();

	void createDepthResources();

	VkFormat findDepthFormat();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	bool hasStencilComponent(VkFormat format) {
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	void createCommandPool();
	void createCommandBuffers();

	void createSemaphores();

	void createRenderPass();

	void createDescriptorSetLayouts();

	void createGraphicsPipeline();

	VkShaderModule createShaderModule(const std::vector<char>& code);

	static std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	// Validation layers and callback =========================================
	bool checkValidationLayerSupport();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {

		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}

	void setupDebugCallback();

	static VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	//GETTING SUITABLE GPU =================================
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void createVertexBuffer();
	void createIndexBuffer();

	void createUniformBuffer();

	void createDescriptorPool();
	void createvpDescriptorSet();

private:
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif



	VkInstance instance;

	VkDebugReportCallbackEXT callback;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkSurfaceKHR surface;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;
	VkDescriptorSetLayout vpDescriptorSetLayout;
	VkDescriptorSetLayout mDescriptorSetLayout;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;

	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	const int WIDTH = 800;
	const int HEIGHT = 600;

	GLFWwindow* window;

	Camera* active_camera;

};

#endif 