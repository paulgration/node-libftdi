#include "ftdi_context_wrapper.h"

using namespace v8;

Persistent<Function> FtdiContextWrapper::constructor;

FtdiContextWrapper::FtdiContextWrapper() {
  ftdi_init(&_ftdic);
}

FtdiContextWrapper::~FtdiContextWrapper() {
  ftdi_free(&_ftdic);
}

void FtdiContextWrapper::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "FtdiContextWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(isolate, tpl->GetFunction());
}

void FtdiContextWrapper::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* obj = new FtdiContextWrapper();
  obj->Wrap(args.This());

  args.GetReturnValue().Set(args.This());
}

void FtdiContextWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance();

  args.GetReturnValue().Set(instance);
}
