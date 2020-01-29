#ifndef DDICT_H
#define DDICT_H

#include <napi.h>

#include "object_wrap_helper.h"
#include "zstd.h"

class DDict : public ObjectWrapHelper<DDict> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  DDict(const Napi::CallbackInfo& info);
  virtual ~DDict();

 private:
  friend class DCtx;
  static Napi::FunctionReference constructor;
  ZSTD_DDict* ddict;

  int64_t getCurrentSize() { return ZSTD_sizeof_DDict(ddict); }

  Napi::Value wrapGetDictID(const Napi::CallbackInfo& info);
};

#endif