/**
 * Copyright (c) 2016 DeepCortex GmbH <legal@eventql.io>
 * Authors:
 *   - Paul Asmuth <paul@eventql.io>
 *   - Laura Schlimmer <laura@eventql.io>
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
#pragma once
#include <eventql/util/stdtypes.h>
#include <eventql/util/option.h>
#include <eventql/sql/svalue.h>
#include <eventql/sql/qtree/TableExpressionNode.h>
#include <eventql/sql/qtree/ValueExpressionNode.h>
#include <eventql/sql/qtree/SelectListNode.h>

#include "eventql/eventql.h"

namespace csql {

enum class JoinType {
  CARTESIAN, INNER, OUTER
};

enum class JoinConjunctionType : uint8_t {
  EQUAL_TO,
  NOT_EQUAL_TO,
  LESS_THAN,
  LESS_THAN_OR_EQUAL_TO,
  GREATER_THAN,
  GREATER_THAN_OR_EQUAL_TO
};

/**
 * Describes a "join conjunction", i.e.a predicate expression that implies a
 * logical relation (equal/less than/greather than) between columns (or
 * projections of columns) of the two input tables of the join.
 */
struct JoinConjunction {
  JoinConjunctionType type;
  RefPtr<ValueExpressionNode> base_table_expr;
  RefPtr<ValueExpressionNode> joined_table_expr;

  bool operator==(const JoinConjunction& other) const;
  bool operator!=(const JoinConjunction& other) const;
};

class JoinNode : public TableExpressionNode {
public:

  struct InputColumnRef {
    String column;
    size_t table_idx;
    size_t column_idx;
    SType type;
  };

  static const uint8_t kHasWhereExprFlag = 1;
  static const uint8_t kHasJoinExprFlag = 2;

  JoinNode(
      JoinType join_type,
      RefPtr<QueryTreeNode> base_table,
      RefPtr<QueryTreeNode> joined_table);

  JoinNode(
      JoinType join_type,
      RefPtr<QueryTreeNode> base_table,
      RefPtr<QueryTreeNode> joined_table,
      Vector<RefPtr<SelectListNode>> select_list,
      Option<RefPtr<ValueExpressionNode>> where_expr,
      Option<RefPtr<ValueExpressionNode>> join_expr);

  JoinNode(const JoinNode& other);

  JoinType joinType() const;
  void setJoinType(JoinType type);

  RefPtr<QueryTreeNode> baseTable() const;
  RefPtr<QueryTreeNode> joinedTable() const;

  Vector<RefPtr<SelectListNode>> selectList() const;
  void addSelectList(RefPtr<SelectListNode> sl);

  Vector<String> getResultColumns() const override;

  Vector<QualifiedColumn> getAvailableColumns() const override;

  const Vector<InputColumnRef>& inputColumnMap() const;

  size_t getComputedColumnIndex(
      const String& column_name,
      bool allow_add = false) override;

  size_t getNumComputedColumns() const override;

  SType getColumnType(size_t idx) const override;

  size_t getInputColumnIndex(
      const String& column_name,
      bool allow_add = false);

  SType getInputColumnType(size_t idx) const;

  std::pair<size_t, SType> getInputColumnInfo(
      const String& column_name,
      bool allow_add = false);

  Option<RefPtr<ValueExpressionNode>> whereExpression() const;
  void setWhereExpression(RefPtr<ValueExpressionNode> expr);

  Option<RefPtr<ValueExpressionNode>> joinCondition() const;
  void setJoinCondition(RefPtr<ValueExpressionNode> expr);

  RefPtr<QueryTreeNode> deepCopy() const override;

  String toString() const override;

  static void encode(
      QueryTreeCoder* coder,
      const JoinNode& node,
      OutputStream* os);

  static RefPtr<QueryTreeNode> decode(
      QueryTreeCoder* coder,
      InputStream* is);

protected:


  JoinType join_type_;
  RefPtr<QueryTreeNode> base_table_;
  RefPtr<QueryTreeNode> joined_table_;
  Vector<InputColumnRef> input_map_;
  Vector<String> column_names_;
  Vector<RefPtr<SelectListNode>> select_list_;
  Option<RefPtr<ValueExpressionNode>> where_expr_;
  Option<RefPtr<ValueExpressionNode>> join_cond_;
};

} // namespace csql
