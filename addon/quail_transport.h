#ifndef ADDON_QUAIL_TRANSPORT_H_
#define ADDON_QUAIL_TRANSPORT_H_

#include <napi.h>

namespace addon {

class QuailTransport : public Napi::ObjectWrap<QuailTransport> {
  static void InitModule(Napi::Env env, Napi::Object exports);

  QuailTransport(const Napi::CallbackInfo &info);

  // Napi::Value Start(const Napi::CallbackInfo &info);
};
} // namespace addon

#endif /* ADDON_QUAIL_TRANSPORT_H_ */
