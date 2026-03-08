/**
 * @file ShaderCompiler.cpp
 * @author Spaced Viking
 * @brief Implement functions of ShaderCompiler.h
 *
 * MIT Lizense
 *
 */

#include "ShaderCompiler.h"
#include "ShaderCompiler/include/slang.h"
#include "utils.h"
#include <cstdio>
#include <cstring>
#include <expected>
#include <vector>

using namespace slang;
ShaderCompiler::ShaderCompiler(vkb::DispatchTable *disp) {
  m_disp = disp;
  CreateSession();
}

void ShaderCompiler::EndSession() {
  // TODO: implement me
}

void ShaderCompiler::CreateSession() {
  SlangGlobalSessionDesc desc = {};
  createGlobalSession(&desc, m_globalSession.writeRef());

  // targets
  SessionDesc sessionDesc = {};
  TargetDesc targetDesc = {};
  targetDesc.format = SLANG_SPIRV;
  targetDesc.profile = m_globalSession->findProfile("spirv_1_5");
  targetDesc.flags = 0;
  sessionDesc.targets = &targetDesc;
  sessionDesc.targetCount = 1;
  sessionDesc.compilerOptionEntryCount = 0;

  // macros
  PreprocessorMacroDesc fancyFlag = {"SHADER", "1"};
  sessionDesc.preprocessorMacros = &fancyFlag;
  sessionDesc.preprocessorMacroCount = 1;

  // search paths
  const char *searchPaths[] = {"Shaders/"};
  sessionDesc.searchPathCount = 1;
  sessionDesc.searchPaths = searchPaths;

  m_globalSession->createSession(sessionDesc, m_session.writeRef());
}

std::expected<std::vector<char>, ErrorCode>
ShaderCompiler::CompileShader(std::string name) {
  slang::IModule *slangModule = nullptr;
  {
    Slang::ComPtr<slang::IBlob> diagnosticBlob;
    slangModule =
        m_session->loadModule(name.c_str(), diagnosticBlob.writeRef());

    if (diagnosticBlob != nullptr) {
      printf("%s", (const char *)diagnosticBlob->getBufferPointer());
      return std::unexpected<ErrorCode>(ErrorCode::Error);
    }

    if (!slangModule)
      return std::unexpected<ErrorCode>(ErrorCode::Error);
  }

  Slang::ComPtr<slang::IEntryPoint> entryPoint;
  slangModule->findEntryPointByName("computeMain", entryPoint.writeRef());

  std::vector<slang::IComponentType *> componentTypes;
  componentTypes.push_back(slangModule);
  componentTypes.push_back(entryPoint);

  Slang::ComPtr<slang::IComponentType> composedProgram;
  {
    Slang::ComPtr<slang::IBlob> diagnosticsBlob;
    SlangResult result = m_session->createCompositeComponentType(
        componentTypes.data(), componentTypes.size(),
        composedProgram.writeRef(), diagnosticsBlob.writeRef());
    if (diagnosticsBlob != nullptr) {
      printf("%s", (const char *)diagnosticsBlob->getBufferPointer());
      return std::unexpected<ErrorCode>(ErrorCode::Error);
    }
  }

  Slang::ComPtr<slang::IBlob> spirvCode;
  {
    Slang::ComPtr<slang::IBlob> diagnosticsBlob;
    SlangResult result = composedProgram->getEntryPointCode(
        0, 0, spirvCode.writeRef(), diagnosticsBlob.writeRef());
    if (diagnosticsBlob != nullptr) {
      printf("%s", (const char *)diagnosticsBlob->getBufferPointer());
      return std::unexpected<ErrorCode>(ErrorCode::Error);
    }
  }
  std::vector<char> ret(spirvCode->getBufferSize());
  memcpy(ret.data(), spirvCode->getBufferPointer(), ret.size());
  return ret;
}