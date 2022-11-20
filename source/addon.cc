#include "sandbox.h"

NAN_MODULE_INIT(Init) {
  Sandbox::Initialize(target);
}

NODE_MODULE(sandbox, Init)
