
#include <napi.h>

#include "quail_server.h"
#include "quail_transport.h"

Napi::Value initEnv(const Napi::CallbackInfo& info) {

  int level = info[0].ToNumber();
  // SetEnv(level);


  return info.Env().Undefined();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  // exports.Set(Napi::String::New(env, "initEnv"),
  //             Napi::Function::New(env, initEnv));

  addon::QuailServer::Init(env, exports);
  addon::QuailTransport::Init(env, exports);

  return exports;
}

NODE_API_MODULE(addon, InitAll)