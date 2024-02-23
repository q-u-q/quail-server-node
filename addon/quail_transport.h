#ifndef ADDON_QUAIL_TRANSPORT_H_
#define ADDON_QUAIL_TRANSPORT_H_

#include <napi.h>

#include "api/quail_transport.h"

namespace addon {

class QuailTransport : public Napi::ObjectWrap<QuailTransport> {
public:
  struct callback_data {
    uint32_t stream_id;
    std::string message;
  };

  static void Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg,
                                  quit::QuailTransport *transport);

  QuailTransport(const Napi::CallbackInfo &info);

  Napi::Value SetCallback(const Napi::CallbackInfo &info);
  Napi::Value Send(const Napi::CallbackInfo &info);

  Napi::ThreadSafeFunction async_callback_safe_ = nullptr;

  quit::QuailTransport *transport_;
};
} // namespace addon

#endif /* ADDON_QUAIL_TRANSPORT_H_ */
