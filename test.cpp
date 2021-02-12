#include "napi.h"
#include <iostream>
#include <atomic>
using namespace Napi;

static std::atomic<size_t> allocated_buffers(0);

Value getAllocate(const CallbackInfo &info) {
    return Napi::Number::New(info.Env(), allocated_buffers.load());
}
Value doGet(const CallbackInfo &info) {
    size_t size = 200;

    if (info.Length() > 0 && info[0].IsNumber())
        size = info[0].ToNumber().Int64Value();

    uint8_t *data = new uint8_t[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = (uint8_t)i;
        
    auto obj = Napi::Object::New(info.Env());
    allocated_buffers++;
    std::cerr << "Allocated buffer of " << size << " bytes at " << (void*)data << " (total " << allocated_buffers << ")\n";
    obj["obj"] = Napi::Buffer<uint8_t>::New(info.Env(), data, size,
         [](Napi::Env env, uint8_t *d, uint8_t *hint) {
             allocated_buffers--;
             std::cerr << "Releasing buffer at " << (void*) d << ", hint is " << (void*) hint << " (total " << allocated_buffers << ")\n";
             delete[] hint;
         }, data);
    return obj;
}
Object Init(Env env, Napi::Object exports) {
    exports["get"] = Function::New(env, doGet, "get");
    exports["allocated"] = Function::New(env, getAllocate, "allocated");
    return exports;
}

// register module
NODE_API_MODULE(testNapi, Init);