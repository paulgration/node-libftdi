#include <ftdi.h>
#include "ftdi_context_wrapper.h"
#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>
#include <v8.h>

using namespace v8;

void create_context(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  FtdiContextWrapper::NewInstance(args);
}

void ftdi_usb_open_desc(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  int vendor = args[1]->NumberValue();
  int product = args[2]->NumberValue();
  char *description = NULL;
  char *serial = NULL;

  String::Utf8Value d(args[3]->ToString());
  if (args[3]->IsString()) {
    description = *d;
  }

  String::Utf8Value s(args[4]->ToString());
  if (args[4]->IsString()) {
    serial = *s;
  }

  int ret = ftdi_usb_open_desc(&ctx->_ftdic, vendor, product, description,
    serial);

  args.GetReturnValue().Set(ret);
}

void ftdi_set_bitmode(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  int mask = args[1]->NumberValue();
  int mode = args[2]->NumberValue();

  int ret = ftdi_set_bitmode(&ctx->_ftdic, mask, mode);

  args.GetReturnValue().Set(ret);
}

void ftdi_set_baudrate(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  int baudrate = args[1]->NumberValue();

  int ret = ftdi_set_baudrate(&ctx->_ftdic, baudrate);

  args.GetReturnValue().Set(ret);
}

void ftdi_get_error_string(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  const char* ret = ftdi_get_error_string(&ctx->_ftdic);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, ret));
}

void ftdi_read_data(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  unsigned char* buf = (unsigned char*) node::Buffer::Data(args[1]);
  size_t len = node::Buffer::Length(args[1]);
  int size = (int) len;

  int ret = ftdi_read_data(&ctx->_ftdic, buf, size);

  args.GetReturnValue().Set(ret);
}

void ftdi_write_data(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  unsigned char* buf = (unsigned char*) node::Buffer::Data(args[1]);
  int size = args[2]->NumberValue();

  int ret = ftdi_write_data(&ctx->_ftdic, buf, size);

  args.GetReturnValue().Set(ret);
}

void ftdi_usb_purge_tx_buffer(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  FtdiContextWrapper* ctx = node::ObjectWrap::Unwrap<FtdiContextWrapper>(
    args[0]->ToObject());
  int ret = ftdi_usb_purge_tx_buffer(&ctx->_ftdic);

  args.GetReturnValue().Set(ret);
}

void InitAll(Handle<Object> exports) {
  FtdiContextWrapper::Init(exports);
  NODE_SET_METHOD(exports, "create_context", create_context);
  NODE_SET_METHOD(exports, "ftdi_usb_open_desc", ftdi_usb_open_desc);
  NODE_SET_METHOD(exports, "ftdi_set_bitmode", ftdi_set_bitmode);
  NODE_SET_METHOD(exports, "ftdi_set_baudrate", ftdi_set_baudrate);
  NODE_SET_METHOD(exports, "ftdi_get_error_string", ftdi_get_error_string);
  NODE_SET_METHOD(exports, "ftdi_read_data", ftdi_read_data);
  NODE_SET_METHOD(exports, "ftdi_write_data", ftdi_write_data);
  NODE_SET_METHOD(exports, "ftdi_usb_purge_tx_buffer",
    ftdi_usb_purge_tx_buffer);
}

NODE_MODULE(libftdi, InitAll)
