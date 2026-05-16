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

#include <perisci/core/linear_algebra.hpp>

#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace perisci::core
{

  DenseMatrix::DenseMatrix(const int size) : size_(size)
  {
    if (size < 0)
    {
      throw std::runtime_error("DenseMatrix size must be non-negative.");
    }
    values_.assign(static_cast<std::size_t>(size) * static_cast<std::size_t>(size), 0.0);
  }

  int DenseMatrix::size() const
  {
    return size_;
  }

  double& DenseMatrix::operator()(const int row, const int col)
  {
    return values_[static_cast<std::size_t>(row) * static_cast<std::size_t>(size_) +
                   static_cast<std::size_t>(col)];
  }

  double DenseMatrix::operator()(const int row, const int col) const
  {
    return values_[static_cast<std::size_t>(row) * static_cast<std::size_t>(size_) +
                   static_cast<std::size_t>(col)];
  }

  std::vector<double> DenseMatrix::multiply(const std::vector<double>& x) const
  {
    if (static_cast<int>(x.size()) != size_)
    {
      throw std::runtime_error("DenseMatrix::multiply dimension mismatch.");
    }

    std::vector<double> y(static_cast<std::size_t>(size_), 0.0);
    for (int row = 0; row < size_; ++row)
    {
      double sum = 0.0;
      for (int col = 0; col < size_; ++col)
      {
        sum += (*this)(row, col) * x[static_cast<std::size_t>(col)];
      }
      y[static_cast<std::size_t>(row)] = sum;
    }
    return y;
  }

  double dot(const std::vector<double>& a, const std::vector<double>& b)
  {
    if (a.size() != b.size())
    {
      throw std::runtime_error("dot dimension mismatch.");
    }

    double value = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i)
    {
      value += a[i] * b[i];
    }
    return value;
  }

  double norm(const std::vector<double>& a)
  {
    return std::sqrt(dot(a, a));
  }

  std::vector<double> subtract(const std::vector<double>& a, const std::vector<double>& b)
  {
    if (a.size() != b.size())
    {
      throw std::runtime_error("subtract dimension mismatch.");
    }

    std::vector<double> value(a.size(), 0.0);
    for (std::size_t i = 0; i < a.size(); ++i)
    {
      value[i] = a[i] - b[i];
    }
    return value;
  }

} // namespace perisci::core
