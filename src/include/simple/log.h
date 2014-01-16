/*
 * Copyright (c) 2014, Julien Bernard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#include <cstdarg>
#include <cstdlib>

namespace simple {

  namespace log {

    enum class Level : int {
      DEBUG   = 0,
      INFO    = 1,
      WARNING = 2,
      ERROR   = 3,
      FATAL   = 4,
    };

    void set_current_level(Level level);

    void log(Level level, const char *fmt, va_list ap);

    inline
    void debug(const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::DEBUG, fmt, ap);
      va_end(ap);
    }

    inline
    void info(const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::INFO, fmt, ap);
      va_end(ap);
    }

    inline
    void warning(const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::WARNING, fmt, ap);
      va_end(ap);
    }

    inline
    void error(const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::ERROR, fmt, ap);
      va_end(ap);
    }

    inline
    void fatal(const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::FATAL, fmt, ap);
      va_end(ap);

      std::abort();
    }


  }

}

#endif // SIMPLE_LOG_H
