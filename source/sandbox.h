#include <nan.h>
#include <vector>
#include <map>

class Sandbox
  : public Nan::ObjectWrap
{
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;
  static void Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);

  static NAN_METHOD(New);
  static NAN_METHOD(SetCode);
  static NAN_METHOD(SetValue);
  static NAN_METHOD(Execute);

  Sandbox();

  v8::Local<v8::String> _code;
  v8::Local<v8::ObjectTemplate> _global;
};
