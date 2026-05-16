/*
 * Copyright (c) 2026-present Fei Han
 * PeriSci is licensed under Mulan PSL v2.
 *
 * You can use this software according to the terms and conditions of
 * the Mulan PSL v2.
 *
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *     http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 */

#pragma once

#include <vector>

namespace perisci::core
{

  class DenseMatrix
  {
  public:
    DenseMatrix() = default;
    explicit DenseMatrix(int size);

    int size() const;

    double& operator()(int row, int col);
    double operator()(int row, int col) const;

    std::vector<double> multiply(const std::vector<double>& x) const;

  private:
    int size_ = 0;
    std::vector<double> values_;
  };

  double dot(const std::vector<double>& a, const std::vector<double>& b);
  double norm(const std::vector<double>& a);
  std::vector<double> subtract(const std::vector<double>& a, const std::vector<double>& b);

} // namespace perisci::core
