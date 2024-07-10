#pragma once
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>
#include "image.h"
#include <deque>
#include <functional>
#include "swapchain.h"

/**
 * @brief Holds all the state used in one
 *  rendering/presentation operation.
 * 
 */
class Frame {
public:

    /**
     * @brief Construct a new Frame object
     * 
     * @param image swapchain image to render to
     * @param logicalDevice vulkan device
     * @param deletionQueue deletionQueue
     * @param swapchainFormat swapchain image format
     */
    Frame(vk::DispatchLoaderDynamic& dl,
        vk::Device& logicalDevice,
        std::deque<std::function<void(vk::Device)>>& deviceDeletionQueue,
        vk::CommandBuffer commandBuffer,
        Swapchain& swapchain,
        std::vector<vk::ShaderEXT>& shaders,
        vk::Queue& queue);

    /**
    * @brief Record the command buffer
    */
    void acquire_image_and_record_draw_commands();

    /**
    * @brief Submit render and present operations
    */
    void render_and_present();

    /**
    * @brief for recording drawing commands
    * 
    */
    vk::CommandBuffer commandBuffer;

    /**
    * @brief signalled upon successful image aquisition from swapchain
    *
    */
    vk::Semaphore imageAquiredSemaphore;

    /**
    * @brief signalled upon successful render of an image
    */
    vk::Semaphore renderFinishedSemaphore;

    /**
    * @brief signalled upon successful render of an image
    */
    vk::Fence renderFinishedFence;

    /**
    * @brief the image index in the swapchain to ultimately present to
    */
    uint32_t imageIndex;

    /**
    * @brief the swapchain to render to
    */
    Swapchain& swapchain;

    /**
    * @brief the shaders
    */
    std::vector<vk::ShaderEXT>& shaders;

    /**
    * @brief the vulkan device
    */
    vk::Device& logicalDevice;

private:

    /**
    * @brief title says it all
    *
    */
    void annoying_boilerplate_that_dynamic_rendering_was_meant_to_spare_us();

    vk::RenderingInfoKHR renderingInfo = {};

    vk::RenderingAttachmentInfoKHR colorAttachment = {};

    vk::DispatchLoaderDynamic& dl;

    vk::Queue& queue;

};