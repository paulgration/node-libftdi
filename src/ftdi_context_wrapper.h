#ifndef FTDI_CONTEXT_WRAPPER_H
#define FTDI_CONTEXT_WRAPPER_H

#include <ftdi.h>
#include <node.h>
#include <node_object_wrap.h>

class FtdiContextWrapper : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object> exports);
    static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
    struct ftdi_context _ftdic;

  private:
    FtdiContextWrapper();
    ~FtdiContextWrapper();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;
};

#endif
