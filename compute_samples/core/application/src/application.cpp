/*
 * Copyright(c) 2018 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "application/application.hpp"

#include "version/version.hpp"
#include "logging/logging.hpp"

namespace compute_samples {
Application::Status Application::run(std::vector<std::string> &command_line) {
  try {
    LOG_INFO << "Version: " << get_version_string();

#ifndef _WIN32
#define PUTENV putenv
#else
#define PUTENV _putenv
#endif
    char set_default_vendor[] = "BOOST_COMPUTE_DEFAULT_VENDOR=Intel";
    char set_default_device[] = "BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=GPU";
    PUTENV(set_default_vendor);
    PUTENV(set_default_device);

    return run_implementation(command_line);
  } catch (const std::exception &e) {
    LOG_FATAL << e.what();
    return Status::ERROR;
  }
}
} // namespace compute_samples
