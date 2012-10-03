#include "sharp_mruby.h"

#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/compile.h"
#include "mruby/dump.h"
#include "mruby/compile.h"

MRuby::MRuby()
{
    mrb = mrb_open();
    ctx = mrbc_context_new(mrb);
}

MRuby::~MRuby()
{
    this->!MRuby();
}

MRuby::!MRuby()
{
    if (ctx != NULL) {
        mrbc_context_free(mrb, ctx);
    }
    if (mrb != NULL) {
        mrb_close(mrb);
    }
}

void MRuby::ExecString(String^ s)
{
    IntPtr ptr;
    mrb_value ret;
    mrb_value output;

    ptr = Marshal::StringToHGlobalAnsi(s);

    ret = mrb_load_string(mrb, (char *)ptr.ToPointer());

    Marshal::FreeHGlobal(ptr);

    if (mrb->exc) {
        if (!mrb_undef_p(ret)) {
            output = mrb_obj_value(mrb->exc);

            output = mrb_funcall(mrb, output, "inspect", 0);
            fwrite(RSTRING_PTR(output), RSTRING_LEN(output), 1, stdout);
        }
    }
}

