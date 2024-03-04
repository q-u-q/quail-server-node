
#include "quail_server.h"

#include <iostream>
#include <thread>

#include "napi.h"
#include "quail_transport.h"

namespace addon {

void QuailServer::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env, "QuailServer",
                  {
                      InstanceMethod("Start", &QuailServer::Start),
                      InstanceMethod("SetCallback", &QuailServer::SetCallback),
                  });

  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("QuailServer", func);
}

QuailServer::QuailServer(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QuailServer>(info) {

  this->Ref();

  callback_wrapper_ = [](Napi::Env env, Napi::Function jsCallback,
                         callback_data *data) {
    auto arg = Napi::Number::New(env, 1);
    auto transport = QuailTransport::NewInstance(env, arg, data->transport);
    jsCallback.Call({transport});

    delete data;
  };
}

Napi::Value QuailServer::Start(const Napi::CallbackInfo &info) {

  if (info.Length() == 2) {
    std::string cert = info[0].ToString().Utf8Value();
    std::string key = info[1].ToString().Utf8Value();

    thread_ = std::thread([this, cert, key] {
      std::string cert_copy = std::move(cert);
      std::string key_copy = std::move(key);

      server.On("/echo",[this](quail::QuailTransport *t) {
        // std::string data("foo");
        // sleep(1);
        // t->session_->SendOrQueueDatagram(data);

        auto data = new callback_data();
        data->transport = t;
        this->async_callback_safe_.BlockingCall(data, callback_wrapper_);

        // t->signal_message_.connect(
        //     [t](uint32_t stream_id, std::string message) {
        //       std::cout << "stream_id:" << stream_id << " message: " <<
        //       message
        //                 << std::endl;
        //       std::string response = "Dont give a shit";
        //       t->Send(stream_id, response);
        //     });
      });
      server.Start(cert_copy, key_copy);
    });

  } else {
  }

  return info.Env().Undefined();
}

Napi::Value QuailServer::SetCallback(const Napi::CallbackInfo &info) {

  if (info.Length() == 1) {

    Napi::Function callback = info[0].As<Napi::Function>();
    this->async_callback_safe_ = Napi::ThreadSafeFunction::New(
        info.Env(), // Environment
        callback,
        "TSFN",         // Resource name
        0,              // Max queue size (0 = unlimited).
        1,              // Initial thread count
        [](Napi::Env) { // Finalizer used to clean threads up
          std::cout << "shit\n";
        });
  } else {
  }

  return info.Env().Undefined();
}

} // namespace addon