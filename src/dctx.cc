#include "dctx.h"

#include "zstd_util.h"

using namespace Napi;

Napi::FunctionReference DCtx::constructor;

Napi::Object DCtx::Init(Napi::Env env, Napi::Object exports) {
  Function func =
      DefineClass(env, "DCtx",
                  {
                      InstanceMethod("decompress", &DCtx::wrapDecompress),
                  });
  constructor = Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("DCtx", func);
  return exports;
}

DCtx::DCtx(const Napi::CallbackInfo& info) : Napi::ObjectWrap<DCtx>(info) {
  dctx = ZSTD_createDCtx();
}

DCtx::~DCtx() {
  ZSTD_freeDCtx(dctx);
  dctx = nullptr;
}

Napi::Value DCtx::wrapDecompress(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() != 2)
    throw TypeError::New(env, "Wrong arguments");
  Buffer<char> dstBuf = info[0].As<Buffer<char>>();
  Buffer<char> srcBuf = info[1].As<Buffer<char>>();

  size_t result = ZSTD_decompressDCtx(dctx, dstBuf.Data(), dstBuf.ByteLength(),
                                      srcBuf.Data(), srcBuf.ByteLength());
  return convertZstdResult(env, result);
}
