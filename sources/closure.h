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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <option/option.h>
#include <result/result.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define CLOSURE_VERSION_MAJOR       0
#define CLOSURE_VERSION_MINOR       1
#define CLOSURE_VERSION_PATCH       0
#define CLOSURE_VERSION_SUFFIX      ""
#define CLOSURE_VERSION_IS_RELEASE  0
#define CLOSURE_VERSION_HEX         0x000100

/**
 * @return The semantic versioning string of the package.
 */
extern const char *
Closure_version(void)
__attribute__((__warn_unused_result__));

typedef Result (*Closure_CallFn)(Option, Option);
typedef void (*Closure_DeleteFn)(Option);

struct Closure;

extern OptionOf(struct Closure *)
Closure_new(Option environment, Closure_CallFn callFn, Closure_DeleteFn deleteFn)
__attribute__((__warn_unused_result__, __nonnull__(2, 3)));

extern Result
Closure_call(struct Closure *closure)
__attribute__((__nonnull__));

extern Result
Closure_callWith(struct Closure *closure, Option arguments)
__attribute__((__nonnull__(1)));

extern void
Closure_delete(struct Closure *closure);

#ifdef __cplusplus
}
#endif
