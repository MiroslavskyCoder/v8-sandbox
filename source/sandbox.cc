#include "sandbox.h"

#include <iostream>
#include <memory>

Nan::Persistent<v8::FunctionTemplate> Sandbox::constructor;

void Sandbox::Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
  Nan::HandleScope scope;

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Sandbox::New);

  constructor.Reset(ctor);

  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Sandbox").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "setCode", SetCode);
  Nan::SetPrototypeMethod(ctor, "setValue", SetValue);
  Nan::SetPrototypeMethod(ctor, "execute", Execute);

  v8::Local<v8::Context> ctx = Nan::GetCurrentContext();
  Nan::Set(target, Nan::New("Sandbox").ToLocalChecked(), ctor->GetFunction(ctx).ToLocalChecked());
}

Sandbox::Sandbox() {}

NAN_METHOD(Sandbox::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  Sandbox* kSandbox = new Sandbox;

  kSandbox->_global = v8::ObjectTemplate::New(isolate);
  if (info[0]->IsString()) {
    kSandbox->_code = Nan::To<v8::String>(info[0]).ToLocalChecked();
  } else {
    kSandbox->_code = Nan::New<v8::String>("").ToLocalChecked();
  }

  kSandbox->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Sandbox::SetCode) {
  Sandbox *kSandbox = Nan::ObjectWrap::Unwrap<Sandbox>(info.This());

  if (info[0]->IsString()) {
    kSandbox->_code = Nan::To<v8::String>(info[0]).ToLocalChecked();
  }

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Sandbox::SetValue) {
  Sandbox *kSandbox = Nan::ObjectWrap::Unwrap<Sandbox>(info.This());

  if (!info[0]->IsString()) {
    Nan::ThrowError(
      Nan::New<v8::String>("Specify a string type key").ToLocalChecked()
    );
    return;
  }

  if (!info[1]->IsValue()) {
    Nan::ThrowError(
      Nan::New<v8::String>("Invalid key value").ToLocalChecked()
    );
    return;
  }

  kSandbox->_global->Set(
    Nan::To<v8::String>(info[0]).ToLocalChecked(),
    info[1]
  );
}

NAN_METHOD(Sandbox::Execute) {
  Sandbox *kSandbox = Nan::ObjectWrap::Unwrap<Sandbox>(info.This());

  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, kSandbox->_global);
  v8::Local<v8::Script> script = v8::Script::Compile(context, kSandbox->_code).ToLocalChecked();
  v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

  info.GetReturnValue().Set(result);
}