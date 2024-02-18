
#include <napi.h>

#include "quail_server.h"

Napi::Value initEnv(const Napi::CallbackInfo& info) {

  int level = info[0].ToNumber();
  // SetEnv(level);


  return info.Env().Undefined();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  // exports.Set(Napi::String::New(env, "initEnv"),
  //             Napi::Function::New(env, initEnv));

  addon::QuailServer::InitModule(env, exports);

  return exports;
}

NODE_API_MODULE(addon, InitAll)