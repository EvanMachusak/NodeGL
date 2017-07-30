#include <node.h>
#include "NodeGLWindow.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  NodeGLWindow::Init(exports);
}

NODE_MODULE(addon, InitAll)