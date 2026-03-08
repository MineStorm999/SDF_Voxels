#include "App.h"
#include <cstdlib>
#include <iostream>

void App::CreateWindowSurface(VkInstance instance, GLFWwindow *window,
                              VkAllocationCallbacks *allocator) {
  m_surface = VK_NULL_HANDLE;
  VkResult err =
      glfwCreateWindowSurface(instance, window, allocator, &m_surface);
  if (err) {
    const char *error_msg;
    int ret = glfwGetError(&error_msg);
    if (ret != 0) {
      std::cout << ret << " ";
      if (error_msg != nullptr)
        std::cout << error_msg;
      std::cout << "\n";
    }
    m_surface = VK_NULL_HANDLE;
  }
}

void App::CreateWindow(const char *window_name, int w, int h, bool fullScreen) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_MAXIMIZED, fullScreen ? GLFW_TRUE : GLFW_FALSE);

  m_window = glfwCreateWindow(1024, 1024, window_name, NULL, NULL);
}

void App::DestroyWindow() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void App::CreateSwapchain() {

  vkb::SwapchainBuilder swapchain_builder{m_device};
  auto swap_ret = swapchain_builder.set_old_swapchain(m_swapchain).build();
  if (!swap_ret) {
    std::cout << swap_ret.error().message() << " " << swap_ret.vk_result()
              << "\n";
    return;
  }
  vkb::destroy_swapchain(m_swapchain);
  m_swapchain = swap_ret.value();
}

void App::CreateDevice() {
  vkb::InstanceBuilder instance_builder;
  auto instance_ret =
      instance_builder.use_default_debug_messenger()
          .request_validation_layers()
          .set_headless() // Skip vk-bootstrap trying to create WSI for you
          .build();
  if (!instance_ret) {
    std::cout << instance_ret.error().message() << "\n";
    return;
  }
  m_instance = instance_ret.value();

  m_inst_disp = m_instance.make_table();

  vkb::PhysicalDeviceSelector phys_device_selector(m_instance);
  auto phys_device_ret = phys_device_selector.select();
  if (!phys_device_ret) {
    std::cout << phys_device_ret.error().message() << "\n";
    if (phys_device_ret.error() ==
        vkb::PhysicalDeviceError::no_suitable_device) {
      const auto &detailed_reasons = phys_device_ret.detailed_failure_reasons();
      if (!detailed_reasons.empty()) {
        std::cerr << "GPU Selection failure reasons:\n";
        for (const std::string &reason : detailed_reasons) {
          std::cerr << reason << "\n";
        }
      }
    }
    return;
  }
  vkb::PhysicalDevice physical_device = phys_device_ret.value();

  vkb::DeviceBuilder device_builder{physical_device};
  auto device_ret = device_builder.build();
  if (!device_ret) {
    std::cout << device_ret.error().message() << "\n";
    return;
  }
  m_device = device_ret.value();

  m_disp = m_device.make_table();
}

void App::Run() {
  while (true) {
  }
}

void App::CreateQueues() {
  // Compute can be done on a Grahpics queue
  // See require_dedicated_compute_queue() if want a dedicated compute queue
  auto gq = m_device.get_queue(vkb::QueueType::graphics);
  if (!gq.has_value()) {
    std::cout << "failed to get queue: " << gq.error().message() << "\n";
    exit(-666);
  }
  m_queue = gq.value();
}

App::App(int w, int h, bool fullScreen) {
  CreateDevice();
  CreateQueues();
  CreateDescriptors();
  CreateTracePipeline();
  CreateCommandPool();
}