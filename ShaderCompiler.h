#include "ShaderCompiler/include/slang-com-ptr.h"
#include "ShaderCompiler/include/slang.h"

#include "VkBootstrap.h"
#include "utils.h"
#include <expected>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

/**
 * @brief Compiles shader from slang module into vk pipelines
 *
 * @author Spaced Viking
 * MIT Lizense
 */
class ShaderCompiler {
public:
  /**
   * @brief Construct a new Shader Compiler object
   *
   * @param disp
   * @author Spaced Viking
   * MIT Lizense
   */
  ShaderCompiler(vkb::DispatchTable *disp);

  /**
   * @brief Ends the slang session
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void EndSession();

  /**
   * @brief Compiles the shader and returns the spirv code
   *
   * @param name name of the slang module
   * @return Slang::ComPtr<slang::IBlob> ErrorCode::Error = sth is
   * wrong
   * @author Spaced Viking
   * MIT Lizense
   */
  std::expected<std::vector<char>, ErrorCode> CompileShader(std::string name);

private:
  /**
   * @brief Global slang session
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  Slang::ComPtr<slang::IGlobalSession> m_globalSession;
  /**
   * @brief Slang Session
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  Slang::ComPtr<slang::ISession> m_session;

  /**
   * @brief vk-bootstrap dispatch table
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  vkb::DispatchTable *m_disp;

  /**
   * @brief Create the slang Session
   *
   * @author Spaced Viking
   * MIT Lizense
   */
  void CreateSession();
};