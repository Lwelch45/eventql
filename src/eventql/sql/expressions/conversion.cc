/**
 * Copyright (c) 2016 DeepCortex GmbH <legal@eventql.io>
 * Authors:
 *   - Paul Asmuth <paul@eventql.io>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License ("the license") as
 * published by the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * In accordance with Section 7(e) of the license, the licensing of the Program
 * under the license does not imply a trademark license. Therefore any rights,
 * title and interest in our trademarks remain entirely with us.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You can be released from the requirements of the license by purchasing a
 * commercial license. Buying such a license is mandatory as soon as you develop
 * commercial activities involving this program without disclosing the source
 * code of your own applications
 */
#include <eventql/sql/expressions/conversion.h>

namespace csql {
namespace expressions {

void to_nil_uint64_call(sql_txn* ctx, VMStack* stack) {
  popUInt64(stack);
  pushNil(stack);
}

const SFunction to_nil_uint64(
    { SType::UINT64 },
    SType::NIL,
    &to_nil_uint64_call);

void to_nil_int64_call(sql_txn* ctx, VMStack* stack) {
  popInt64(stack);
  pushNil(stack);
}

const SFunction to_nil_int64(
    { SType::INT64 },
    SType::NIL,
    &to_nil_int64_call);

void to_nil_float64_call(sql_txn* ctx, VMStack* stack) {
  popFloat64(stack);
  pushNil(stack);
}

const SFunction to_nil_float64(
    { SType::FLOAT64 },
    SType::NIL,
    &to_nil_float64_call);

void to_nil_bool_call(sql_txn* ctx, VMStack* stack) {
  popBool(stack);
  pushNil(stack);
}

const SFunction to_nil_bool(
    { SType::BOOL },
    SType::NIL,
    &to_nil_bool_call);

void to_nil_string_call(sql_txn* ctx, VMStack* stack) {
  const char* _1;
  size_t _2;
  popString(stack, &_1, &_2);
  pushNil(stack);
}

const SFunction to_nil_string(
    { SType::BOOL },
    SType::NIL,
    &to_nil_string_call);

void to_nil_timestamp64_call(sql_txn* ctx, VMStack* stack) {
  popTimestamp64(stack);
  pushNil(stack);
}

const SFunction to_nil_timestamp64(
    { SType::TIMESTAMP64 },
    SType::NIL,
    &to_nil_timestamp64_call);


/**
 * to_int64(uint64) -> int64
 * to_int64(timestamp64) -> int64
 */
void to_int64_uint64_call(sql_txn* ctx, VMStack* stack) {
  auto value = popUInt64(stack);
  pushInt64(stack, value);
}

const SFunction to_int64_uint64(
    { SType::UINT64 },
    SType::INT64,
    &to_int64_uint64_call);

const SFunction to_int64_timestamp64(
    { SType::TIMESTAMP64 },
    SType::INT64,
    &to_int64_uint64_call);


/**
 * to_int64(float64) -> int64
 */
void to_int64_float64_call(sql_txn* ctx, VMStack* stack) {
  auto value = popFloat64(stack);
  pushInt64(stack, value);
}

const SFunction to_int64_float64(
    { SType::FLOAT64 },
    SType::INT64,
    &to_int64_float64_call);


/**
 * to_int64(bool) -> int64
 */
void to_int64_bool_call(sql_txn* ctx, VMStack* stack) {
  auto value = popBool(stack);
  pushInt64(stack, value);
}

const SFunction to_int64_bool(
    { SType::BOOL },
    SType::INT64,
    &to_int64_bool_call);


/**
 * to_string(uint64) -> string
 * to_string(timestamp64) -> string
 */
void to_string_nil_call(sql_txn* ctx, VMStack* stack) {
  popNil(stack);
  pushString(stack, "NULL");
}

const SFunction to_string_nil(
    { SType::NIL },
    SType::STRING,
    &to_string_nil_call);

/**
 * to_string(uint64) -> string
 * to_string(timestamp64) -> string
 */
void to_string_uint64_call(sql_txn* ctx, VMStack* stack) {
  auto str = sql_tostring(SType::UINT64, stack->top);
  popUInt64(stack);
  pushString(stack, str);
}

const SFunction to_string_uint64(
    { SType::UINT64 },
    SType::STRING,
    &to_string_uint64_call);

const SFunction to_string_timestamp64(
    { SType::TIMESTAMP64 },
    SType::STRING,
    &to_string_uint64_call);


/**
 * to_string(int64) -> string
 */
void to_string_int64_call(sql_txn* ctx, VMStack* stack) {
  auto str = sql_tostring(SType::INT64, stack->top);
  popInt64(stack);
  pushString(stack, str);
}

const SFunction to_string_int64(
    { SType::INT64 },
    SType::STRING,
    &to_string_int64_call);


/**
 * to_string(float64) -> string
 */
void to_string_float64_call(sql_txn* ctx, VMStack* stack) {
  auto str = sql_tostring(SType::FLOAT64, stack->top);
  popFloat64(stack);
  pushString(stack, str);
}

const SFunction to_string_float64(
    { SType::FLOAT64 },
    SType::STRING,
    &to_string_float64_call);


/**
 * to_string(bool) -> string
 */
void to_string_bool_call(sql_txn* ctx, VMStack* stack) {
  auto str = sql_tostring(SType::BOOL, stack->top);
  popBool(stack);
  pushString(stack, str);
}

const SFunction to_string_bool(
    { SType::BOOL },
    SType::STRING,
    &to_string_bool_call);


/**
 * to_timestamp64(int64) -> timestamp64
 */
void to_timestamp64_int64_call(sql_txn* ctx, VMStack* stack) {
  auto value = popInt64(stack);
  pushTimestamp64(stack, value);
}

const SFunction to_timestamp64_int64(
    { SType::INT64 },
    SType::TIMESTAMP64,
    &to_timestamp64_int64_call);


/**
 * to_float64(int64) -> timestamp64
 */
void to_timestamp64_float64_call(sql_txn* ctx, VMStack* stack) {
  auto value = popFloat64(stack);
  pushTimestamp64(stack, value);
}

const SFunction to_timestamp64_float64(
    { SType::FLOAT64 },
    SType::TIMESTAMP64,
    &to_timestamp64_float64_call);


} // namespace expressions
} // namespace csql

