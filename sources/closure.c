/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdlib.h>
#include "closure.h"

#define _STR(x)     #x
#define STR(x)      _STR(x)

const char *Closure_version(void) {
    return STR(CLOSURE_VERSION_MAJOR) "."
           STR(CLOSURE_VERSION_MINOR) "."
           STR(CLOSURE_VERSION_PATCH)
           CLOSURE_VERSION_SUFFIX;
}

struct Closure {
    Closure_CallFn call;
    Closure_DeleteFn delete;
    Option environment;
};

OptionOf(struct Closure *)
Closure_new(Option environment, Closure_CallFn callFn, Closure_DeleteFn deleteFn) {
    assert(callFn);
    assert(deleteFn);
    struct Closure *self = malloc(sizeof(*self));
    if (self) {
        self->call = callFn;
        self->delete = deleteFn;
        self->environment = environment;
        return Option_some(self);
    }
    return None;
}

Result Closure_call(struct Closure *const closure) {
    assert(closure);
    assert(closure->call);
    assert(closure->delete);
    return Closure_callWith(closure, None);
}

Result Closure_callWith(struct Closure *const closure, Option arguments) {
    assert(closure);
    assert(closure->call);
    assert(closure->delete);
    return closure->call(closure->environment, arguments);
}

void Closure_delete(struct Closure *closure) {
    if (closure) {
        assert(closure->call);
        assert(closure->delete);
        closure->delete(closure->environment);
        free(closure);
    }
}