

#include "quail_transport.h"

#include <iostream>

namespace addon {

QuailTransport::QuailTransport(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QuailTransport>(info) {
  std::cout << "foo Transport\n";
}

Napi::Object QuailTransport::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New({arg});
  return scope.Escape(napi_value(obj)).ToObject();
}

} // namespace addon