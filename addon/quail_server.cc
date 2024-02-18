
#include "quail_server.h"

#include <iostream>

namespace addon {

void QuailServer::InitModule(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env, "QuailServer",
                  {
                      InstanceMethod("Start", &QuailServer::Start),
                  });

  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("QuailServer", func);
}

QuailServer::QuailServer(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QuailServer>(info) {

}

Napi::Value QuailServer::Start(const Napi::CallbackInfo &info) {
  std::cout << "start";
  
  if (info.Length() == 2) {
    std::string cert = info[0].ToString().Utf8Value();
    std::string key = info[1].ToString().Utf8Value();

  } else {

  }

  return info.Env().Undefined();
}

} // namespace addon