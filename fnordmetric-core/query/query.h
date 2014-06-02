/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * Licensed under the MIT license (see LICENSE).
 */
#ifndef _FNORDMETRIC_QUERY_QUERY_H
#define _FNORDMETRIC_QUERY_QUERY_H
#include <stdlib.h>
#include <string>

namespace fnordmetric {
namespace query {

class Query {
public:
  explicit Query(const std::string& query_string);
  Query(const Query& copy) = delete;
  Query& operator=(const Query& copy) = delete;
  Query(Query&& move);
};

}
}
#endif
