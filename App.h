/**
 * @file App.h
 * @author Spaced Viking
 *
 * MIT Lizense
 *
 */

#pragma once
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "VkBootstrap.h"

/**
 * @brief App class holds all vk/glfw contexts and render classes
 *
 * @author Spaced Viking
 * MIT Lizense
 */
class App {
public:
  /**
   * @brief Construct a new App object
   *
   * @param w
   * @param h
   * @param fullScreen
   * @author Spaced Viking
   * MIT Lizense
   */
  App(int w, int h, bool fullScreen);

  /**
   * @brief Destroy the App object and vk/glfw contexts
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  ~App();

  /**
   * @brief Run loop (rendering usw takes place here (or on different threads))
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void Run();

private:
  /**
   * @brief GLFWwindow
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  GLFWwindow *m_window;
  /**
   * @brief VkSurfaceKHR
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  VkSurfaceKHR m_surface;
  /**
   * @brief vkbootstrap Instance
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::Instance m_instance;
  /**
   * @brief vkbootstrap InstanceDispatchTable
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::InstanceDispatchTable m_inst_disp;
  /**
   * @brief vkbootstrap Device
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::Device m_device;
  /**
   * @brief vkbootstrap DispatchTable
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::DispatchTable m_disp;
  /**
   * @brief Swapchain
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::Swapchain m_swapchain;
  /**
   * @brief WorkQueue
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  VkQueue m_queue;

  /**
   * @author Spaced Viking
   * MIT Lizense
   */
  VkPipeline tracePipe;
  /**
   * @author Spaced Viking
   * MIT Lizense
   */
  VkPipelineLayout tracePipeLayout;

  /**
   * @author Spaced Viking
   * MIT Lizense
   */
  VkDescriptorSetLayout traceDescLayout;
  /**
   * @author Spaced Viking
   * MIT Lizense
   */
  VkDescriptorSet traceDesc;
  /**
   * @author Spaced Viking
   * MIT Lizense
   */
  VkDescriptorPool traceDescPool;

  // functions

  /**
   * @brief Create a Window Surface object
   *
   * @param instance
   * @param window
   * @param allocator
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateWindowSurface(VkInstance instance, GLFWwindow *window,
                           VkAllocationCallbacks *allocator = nullptr);

  /**
   * @brief Create a Window object
   *
   * @param window_name
   * @param w
   * @param h
   * @param fullScreen
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateWindow(const char *window_name, int w, int h, bool fullScreen);
  /**
   * @brief Create a Device object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateDevice();
  /**
   * @brief Create a Queues object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateQueues();
  /**
   * @brief Create a Swapchain object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateSwapchain();
  /**
   * @brief Create a Descriptors object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateDescriptors();
  /**
   * @brief Create a Trace Pipeline object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateTracePipeline();
  /**
   * @brief Create a Command Pool object
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateCommandPool();

  /**
   * @brief Destroys the window
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void DestroyWindow();
};