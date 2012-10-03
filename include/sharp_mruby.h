#pragma once

#include "mruby.h"
#include "mruby/compile.h"

using namespace System;
using namespace System::Runtime::InteropServices;

public ref class MRuby
{
private:
    mrb_state *mrb;
    mrbc_context *ctx;

public:
    MRuby();
    ~MRuby();
    !MRuby();

    void ExecString(String ^s);
};

