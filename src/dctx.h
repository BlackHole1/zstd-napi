#ifndef DCTX_H
#define DCTX_H

#include <napi.h>

#include "object_wrap_helper.h"
#include "zstd.h"

class DCtx : public ObjectWrapHelper<DCtx> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  DCtx(const Napi::CallbackInfo& info);
  virtual ~DCtx();

 private:
  static Napi::FunctionReference constructor;
  ZSTD_DCtx* dctx;

  int64_t getCurrentSize() { return ZSTD_sizeof_DCtx(dctx); }

  Napi::Value wrapDecompress(const Napi::CallbackInfo& info);
  Napi::Value wrapDecompressUsingDDict(const Napi::CallbackInfo& info);
};

#endif