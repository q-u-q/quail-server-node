#ifndef ADDON_QUAIL_SERVER_H_
#define ADDON_QUAIL_SERVER_H_

#include <napi.h>

namespace addon {

class QuailServer : public Napi::ObjectWrap<QuailServer> {
public:
  static void InitModule(Napi::Env env, Napi::Object exports);

  QuailServer(const Napi::CallbackInfo &info);

  Napi::Value Start(const Napi::CallbackInfo &info);
};

} // namespace addon

#endif /* ADDON_QUAIL_SERVER_H_ */
