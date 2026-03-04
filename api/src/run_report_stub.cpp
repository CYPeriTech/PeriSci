#include "perisci/api/run_report.hpp"

#include <sstream>

namespace perisci::api
{

  std::string run_report_to_json(const RunReport& r)
  {
    std::ostringstream os;

    os << "{";

    os << "\"mesh_cells\":" << r.mesh_cells << ",";
    os << "\"dof_count\":" << r.dof_count << ",";

    os << "\"matrix_rows\":" << r.matrix_rows << ",";
    os << "\"matrix_nnz\":" << r.matrix_nnz << ",";

    os << "\"solver_iterations\":" << r.solver_iterations << ",";

    os << "\"residual_initial\":" << r.residual_initial << ",";
    os << "\"residual_final\":" << r.residual_final << ",";

    os << "\"residual_curve\":[";
    for (std::size_t i = 0; i < r.residual_curve.size(); ++i)
    {
      os << r.residual_curve[i];
      if (i + 1 < r.residual_curve.size())
        os << ",";
    }
    os << "]";

    os << "}";

    return os.str();
  }

} // namespace perisci::api
