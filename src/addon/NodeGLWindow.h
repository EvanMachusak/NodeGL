#ifndef NODEGLWINDOW_H
#define NODEGLWINDOW_H

#include <nan.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Example top-level functions. These functions demonstrate how to return various js types.
// Implementations are in functions.cc

NAN_METHOD(nothing);
NAN_METHOD(aString);
NAN_METHOD(aBoolean);
NAN_METHOD(aNumber);
NAN_METHOD(anObject);
NAN_METHOD(anArray);
NAN_METHOD(callback);

// Example with node ObjectWrap
// Based on https://nodejs.org/api/addons.html#addons_wrapping_c_objects but using NAN
class NodeGLWindow : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);

  private:
    explicit NodeGLWindow(double value = 0);
    ~NodeGLWindow();

    static NAN_METHOD(New);
    static NAN_METHOD(PlusOne);
    static NAN_METHOD(Show);
    static NAN_GETTER(IsShowing);
    static Nan::Persistent<v8::Function> constructor;
    double value_;
    GLFWwindow *window;
    bool windowShowing;
};

#endif