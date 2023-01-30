#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <iostream>

#include "Window.h"

//debug message
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator);

//how many frames should be processed concurrently
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

struct t_QueueFamilyIndices {
	/* std::optional is a wrapper that contains no value until you assign something to it.
	At any point you can query if it contains a value or not by calling its has_value() member function */
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct t_SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Texture;
class Mesh;
class Model;
struct VerticesAndIndices;

class Application {
public:
	void Run();

	static VkDevice* GetDevice();
	static VkPhysicalDevice* GetPhysicalDevice();

	static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	static void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	static VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	static VkCommandBuffer BeginSingleTimeCommands();
	static void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

	void SetFrameBufferResized(bool input);
	VkSurfaceKHR& GetSurface();
	VkInstance& GetInstance();
	static Window& GetWindow();

private:
#pragma region Variables

	static inline Window window;

	static VkDevice mdevice;
	static VkPhysicalDevice physicalDevice;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	static VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	std::vector<VkDescriptorSetLayout> descriptorSetLayout;
	VkPipelineLayout pipelineLayout;

	VkPipeline graphicsPipelineDepthTest;
	VkPipeline graphicsPipelineNoDepthTest;

	static VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	//to signal that an image has been acquired from the swapchain and is ready for rendering
	std::vector<VkSemaphore> imageAvailableSemaphores;

	//to signal that rendering has finished and presentation can happen
	std::vector<VkSemaphore> renderFinishedSemaphores;

	//fence to make sure only one frame is rendering at a time
	std::vector<VkFence> inFlightFences;

	//To use the right objects every frame, we need to keep track of the current frame
	uint32_t currentFrame = 0;

	bool framebufferResized = false;

	//depth
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	//global uniform
	std::vector<VkBuffer> uniformBuffersGlobal;
	std::vector<VkDeviceMemory> uniformBuffersGlobalMemory;
	std::vector<void*> uniformBuffersGlobalMapped;

	VkDescriptorPool descriptorPoolGlobal;
	std::vector<VkDescriptorSet> descriptorSetsGlobal;

#pragma endregion

#pragma region Functions

	//my functions
	void BindMesh(Mesh* mesh, VkCommandBuffer& commandBuffer);
	void InitMesh(Model* model);

	void UpdateGameObjects(VkCommandBuffer& commandBuffer);
	void UpdateDeltaTime();

	void LoadModel(VerticesAndIndices* verticesAndIndices, std::string modelPath);

	void InitGameObjects();

	void UpdateSkyBox(VkCommandBuffer& commandBuffer);

	void UpdateGlobalUniform(VkCommandBuffer& commandBuffer);
	void CreateUniformBufferGlobal();

	//init =============================================================================================

	void InitVulkan();

	//create an instance. The instance is the connection between your application and the Vulkan library
	void CreateInstance();

	//create surface to present rendered images to
	void CreateSurface();

	//The swap chain is essentially a queue of images that are waiting to be presented to the screen
	void CreateSwapChain();

	//creates a basic image view for every image in the swap chain
	void CreateImageViews();

	/* specify how many colorand depth buffers there will be,
	* how many samples to use for each of them and how their contents should be handled throughout the rendering operations*/
	void CreateRenderPass();

	//create a framebuffer for all of the images in the swap chain and use the one that corresponds to the retrieved image at drawing time
	void CreateFramebuffers();

	//Command pools manage the memory that is used to store the buffers and command buffers are allocated from them
	void CreateCommandPool();

	//take a buffer with the bytecode as parameter and create a VkShaderModule from it
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	//create the semaphores
	void CreateSyncObjects();
	void SetupDebugMessenger();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateDescriptorSetLayout();
	void CreateDescriptorSetLayoutGlobal();
	void CreateGraphicsPipeline();
	static void CreateDescriptorPoolTexture(Mesh* mesh);
	void CreateDescriptorSetsTexture(Mesh* mesh, Texture* texture);
	void CreateCommandBuffers();
	void CreateDepthResources();

	//buffers ==============================================================================================

	void CreateVertexBuffer(Mesh* model);
	void CreateIndexBuffer(Mesh* model);
	void CreateUniformBufferModel(Mesh* mesh);

	//main =================================================================================================

	void ProcessInput();
	void MainLoop();
	void DrawFrame();

	//cleanup =================================================================================================

	void Cleanup();
	void CleanupSwapChain() const;

	//functions to find the right settings for the best possible swap chain ===================================

	//color depth
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	//conditions for "swapping" images to the screen
	static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	//resolution of images in swap chain
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	//other ==================================================================================================

	//writes the commands we want to execute into a command buffer
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	//return the required list of extensions based on whether validation layers are enabled or not
	std::vector<const char*> GetRequiredExtensions();

	/*It is possible for the window surface to change such that the swap chain is no longer compatible with it.
	* One of the reasons that could cause this to happen is the size of the window changing.
	* We have to catch these events and recreate the swap chain*/
	void RecreateSwapChain();

	//copy the contents from one buffer to another
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	int RateDeviceSuitability(VkPhysicalDevice device);
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	t_SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	t_QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	bool CheckValidationLayerSupport();

	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat FindDepthFormat();
	bool HasStencilComponent(VkFormat format);

	// read all of the bytes from the specified file and return them in a byte array
	static std::vector<char> ReadFile(const std::string& filename);

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
#pragma endregion
};
