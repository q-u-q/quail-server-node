

#include "quail_transport.h"

#include <iostream>

namespace addon {

QuailTransport::QuailTransport(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<QuailTransport>(info) {
}

void QuailTransport::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func = DefineClass(
      env, "QuailTransport",
      {
          InstanceMethod("SetCallback", &QuailTransport::SetCallback),
          InstanceMethod("Send", &QuailTransport::Send),
      });

  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("QuailTransport", func);
}

Napi::Object QuailTransport::NewInstance(Napi::Env env, Napi::Value arg,
                                         quail::QuailTransport *transport) {
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New({arg});

  auto nativeObj = QuailTransport::Unwrap(obj);
  nativeObj->transport_ = transport;

  return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value QuailTransport::SetCallback(const Napi::CallbackInfo &info) {

  if (info.Length() == 1) {

    Napi::Function callback = info[0].As<Napi::Function>();
    this->async_callback_safe_ = Napi::ThreadSafeFunction::New(
        info.Env(), // Environment
        callback,
        "TSFN",         // Resource name
        0,              // Max queue size (0 = unlimited).
        1,              // Initial thread count
        [](Napi::Env) { // Finalizer used to clean threads up
          std::cout << "QuailTransport shit\n";
        });

    transport_->signal_message_.connect(
        [this](uint32_t stream_id, std::string message) {
          std::cout << "stream_id:" << stream_id << " message: " << message
                    << std::endl;
          std::string response = "Dont give a shit";
          // t->Send(stream_id, response);
          // transport_->Send(stream_id, response);
          auto callback_wrapper = [](Napi::Env env, Napi::Function jsCallback,
                                     callback_data *data) {
            auto stream_id = Napi::Number::New(env, data->stream_id);
            auto message = Napi::String::New(env, data->message);

            jsCallback.Call({stream_id, message});

            delete data;
          };

          auto data = new callback_data();
          data->stream_id = stream_id;
          data->message = message;
          this->async_callback_safe_.BlockingCall(data, callback_wrapper);
        });

  } else {
  }

  return info.Env().Undefined();
}

Napi::Value QuailTransport::Send(const Napi::CallbackInfo &info) {

  if (info.Length() == 2) {
    std::cout << "QuailTransport::Send\n";

    uint32_t stream_id = info[0].ToNumber().Uint32Value();
    std::string data = info[1].ToString().Utf8Value();

    transport_->Send(stream_id, data);
  } else {
  }

  return info.Env().Undefined();
}

} // namespace addon