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
#include <memory.h>
#include <closure.h>
#include <alligator/alligator.h>
#include "adder.h"

/*
 * AdderEnvironment
 */
struct AdderEnvironment {
    const int x;
};

static struct AdderEnvironment *AdderEnvironment_new(int x);

static void AdderEnvironment_delete(struct AdderEnvironment *self);

/*
 * AdderArguments
 */
struct AdderArguments {
    int y;
};

#define AdderArguments_bake(Y) \
    Option_some(&(struct AdderArguments) {.y=(Y)})

/*
 * AdderResult
 */
struct AdderResult {
    int value;
};

static struct AdderResult *AdderResult_new(int value);

/*
 * AdderClosure
 */
struct AdderClosure {
    struct Closure *closure;
};

static Result AdderClosure_callImpl(Option environment, Option arguments);

static void AdderClosure_deleteImpl(Option environment);

/*
 * IMPLEMENTATION
 */

/*
 * AdderEnvironment
 */
struct AdderEnvironment *AdderEnvironment_new(int x) {
    struct AdderEnvironment *self = Option_unwrap(Alligator_malloc(sizeof(*self)));
    struct AdderEnvironment init = {.x=x};
    memcpy(self, &init, sizeof(*self));
    return self;
}

void AdderEnvironment_delete(struct AdderEnvironment *self) {
    Alligator_free(self);
}

/*
 * AdderResult
 */
struct AdderResult *AdderResult_new(int value) {
    struct AdderResult *self = Option_unwrap(Alligator_malloc(sizeof(*self)));
    self->value = value;
    return self;
}

int AdderResult_get(const struct AdderResult *self) {
    assert(self);
    return self->value;
}

void AdderResult_delete(struct AdderResult *self) {
    Alligator_free(self);
}

/*
 * AdderClosure
 */
struct AdderClosure *AdderClosure_new(int x) {
    struct AdderEnvironment *environment = AdderEnvironment_new(x);
    struct Closure *closure = Closure_new(Option_some(environment), AdderClosure_callImpl, AdderClosure_deleteImpl);
    struct AdderClosure *self = Option_unwrap(Alligator_malloc(sizeof(*self)));
    self->closure = closure;
    return self;
}

ResultOf(struct AdderResult *, OutOfMemory) AdderClosure_call(struct AdderClosure *self, int y) {
    assert(self);
    return Closure_callWith(self->closure, AdderArguments_bake(y));
}

void AdderClosure_delete(struct AdderClosure *self) {
    if (self) {
        Closure_delete(self->closure);
    }
    Alligator_free(self);
}

Result AdderClosure_callImpl(Option environment, Option arguments) {
    assert(Option_isSome(environment));
    assert(Option_isSome(arguments));
    struct AdderEnvironment *adderEnvironment = Option_unwrap(environment);
    struct AdderArguments *adderArguments = Option_unwrap(arguments);
    return Result_ok(AdderResult_new(adderEnvironment->x + adderArguments->y));
}

void AdderClosure_deleteImpl(Option environment) {
    if (Option_isSome(environment)) {
        AdderEnvironment_delete(Option_unwrap(environment));
    }
}
