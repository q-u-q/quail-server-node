#ifndef ADDON_QUAIL_SERVER_H_
#define ADDON_QUAIL_SERVER_H_

#include "api/quail_server.h"

#include <napi.h>
#include <thread>

namespace addon {

class QuailServer : public Napi::ObjectWrap<QuailServer> {
public:
  struct callback_data {
    quit::QuailTransport *transport;
  };

  static void Init(Napi::Env env, Napi::Object exports);

  QuailServer(const Napi::CallbackInfo &info);

  Napi::Value Start(const Napi::CallbackInfo &info);

  Napi::Value SetCallback(const Napi::CallbackInfo &info);

  quail::QuailServer server;

  Napi::ThreadSafeFunction async_callback_safe_ = nullptr;

  std::function<void(Napi::Env, Napi::Function, callback_data *)>
      callback_wrapper_;

  std::thread thread_;
};

} // namespace addon

#endif /* ADDON_QUAIL_SERVER_H_ */
