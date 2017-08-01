#include "NodeGLWindow.h"
#include <iostream>
#include <v8.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

NAN_METHOD(nothing)
{
}

NAN_METHOD(aString)
{
  info.GetReturnValue().Set(Nan::New("This is a thing.").ToLocalChecked());
}

NAN_METHOD(aBoolean)
{
  info.GetReturnValue().Set(false);
}

NAN_METHOD(aNumber)
{
  info.GetReturnValue().Set(1.75);
}

NAN_METHOD(anObject)
{
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("key").ToLocalChecked(), Nan::New("value").ToLocalChecked());
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(anArray)
{
  v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
  Nan::Set(arr, 0, Nan::New(1));
  Nan::Set(arr, 1, Nan::New(2));
  Nan::Set(arr, 2, Nan::New(3));
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(callback)
{
  v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 0, 0);
}

// Wrapper Impl

Nan::Persistent<v8::Function> NodeGLWindow::constructor;

NAN_MODULE_INIT(NodeGLWindow::Init)
{
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  v8::Local<v8::ObjectTemplate> proto = tpl->PrototypeTemplate();
  tpl->SetClassName(Nan::New("NodeGLWindow").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);
  Nan::SetPrototypeMethod(tpl, "show", Show);
  Nan::SetAccessor(proto, Nan::New("isShowing").ToLocalChecked(), IsShowing);  

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("NodeGLWindow").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NodeGLWindow::NodeGLWindow(double value) : value_(value)
{
}

NodeGLWindow::~NodeGLWindow()
{
}

NAN_METHOD(NodeGLWindow::New)
{
  if (info.IsConstructCall())
  {
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    NodeGLWindow *obj = new NodeGLWindow(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else
  {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    Nan::MaybeLocal<v8::Object> maybeInstance = Nan::NewInstance(cons, argc, argv);
    info.GetReturnValue().Set(maybeInstance.ToLocalChecked());
  }
}

NAN_METHOD(NodeGLWindow::PlusOne)
{
  NodeGLWindow *obj = Nan::ObjectWrap::Unwrap<NodeGLWindow>(info.This());
  obj->value_ += 1;
  info.GetReturnValue().Set(obj->value_);
}

NAN_GETTER(NodeGLWindow::IsShowing)
{
  NodeGLWindow *obj = Nan::ObjectWrap::Unwrap<NodeGLWindow>(info.This());
  info.GetReturnValue().Set(obj->windowShowing);
}

NAN_METHOD(NodeGLWindow::Show)
{
  NodeGLWindow *obj = Nan::ObjectWrap::Unwrap<NodeGLWindow>(info.This());
  if (obj->window == NULL)
  {
    if (!glfwInit())
    {
      Nan::ThrowError(Nan::New("GLFW failed to initialize").ToLocalChecked());
    }
    else
    {
      int width = 800, height = 600;
      const char *title = "NodeGL";
      const int argc = info.Length(); 
      if (argc > 0 && info[0]->IsInt32())
        width = info[0]->Int32Value();
      if (argc > 1 && info[1]->IsInt32())
        height = info[1]->Int32Value();
      if (argc > 2 && info[2]->IsString()) {
        v8::Local<v8::String> str = v8::Local<v8::String>::Cast(info[2]); 
        v8::String::Utf8Value utfValue(str); 
        title = *utfValue;
      }
      GLFWwindow* wnd = glfwCreateWindow(width, height, title, NULL, NULL);
      if (wnd == NULL)
      {
        glfwTerminate();
        Nan::ThrowError(Nan::New("GLFW failed to create a window").ToLocalChecked());
      }
      else
      {
        obj->window = wnd;
        glfwMakeContextCurrent(wnd); // Initialize GLEW
        glewExperimental = true;        // Needed in core profile
        if (glewInit() != GLEW_OK)
        {
          Nan::ThrowError(Nan::New("Failed to initialize GLEW").ToLocalChecked());
        }
        else
        {
          obj->windowShowing = true;
          glfwSetInputMode(wnd, GLFW_STICKY_KEYS, GL_TRUE);
          do
          {
            // Draw nothing, see you in tutorial 2 !
            // Swap buffers
            glfwSwapBuffers(wnd);
            glfwPollEvents();

          } // Check if the ESC key was pressed or the window was closed
          while (glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                 glfwWindowShouldClose(wnd) == 0);
          obj->windowShowing = false;
        }
      }
    }
  }
}