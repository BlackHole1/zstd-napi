#ifndef CCTX_H
#define CCTX_H

#include <napi.h>

#include "object_wrap_helper.h"
#include "zstd.h"

class CCtx : public ObjectWrapHelper<CCtx> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  CCtx(const Napi::CallbackInfo& info);
  virtual ~CCtx();

 private:
  static Napi::FunctionReference constructor;
  ZSTD_CCtx* cctx;

  int64_t getCurrentSize() override { return ZSTD_sizeof_CCtx(cctx); }

  Napi::Value wrapCompress(const Napi::CallbackInfo& info);
  Napi::Value wrapCompressUsingCDict(const Napi::CallbackInfo& info);
};

#endif
