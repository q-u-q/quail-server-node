
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

    server.signal_transport_.connect([](quit::QuitTransport* t) {
      std::cout << "Transport" << std::endl;
      // std::string data("foo");
      // sleep(1);
      // t->session_->SendOrQueueDatagram(data);
      t->signal_message_.connect([t](uint32_t stream_id, std::string message) {
        std::cout << "stream_id:" << stream_id << " message: " << message << std::endl;
        std::string response = "Dont give a shit";
        t->Send(stream_id, response);
      });
    });
    server.Start(cert, key);
  } else {

  }

  return info.Env().Undefined();
}

} // namespace addon