#include "cdict.h"

#include "util.h"

using namespace Napi;

void CDict::Init(Napi::Env env, Napi::Object exports) {
  Function func = DefineClass(env, "CDict", {});
  exports.Set("CDict", func);
}

CDict::CDict(const Napi::CallbackInfo& info) : ObjectWrapHelper<CDict>(info) {
  WRAP_CONSTRUCTOR_BEGIN;
  Napi::Env env = info.Env();
  if (info.Length() != 2)
    throw TypeError::New(env, "Wrong arguments");
  Uint8Array dictBuf = info[0].As<Uint8Array>();
  int32_t level = info[1].ToNumber();

  cdict = ZSTD_createCDict(dictBuf.Data(), dictBuf.ByteLength(), level);
  adjustMemory(env);
  WRAP_CONSTRUCTOR_END;
}

CDict::~CDict() {
  ZSTD_freeCDict(cdict);
  cdict = nullptr;
}
