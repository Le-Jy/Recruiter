#include "format_numerical_data.hh"

#include <iomanip>

FormatNumericalData::FormatNumericalData(const std::string& prefix,
                                         const std::string& suffix,
                                         int precision,
                                         bool scientific_notation,
                                         bool display_plus)
    : prefix(prefix)
    , suffix(suffix)
    , precision(precision)
    , scientific_notation(scientific_notation)
    , display_plus(display_plus)
{}

std::ostream& FormatNumericalData::formatOs(std::ostream& os) const
{
    if (precision >= 0)
        os << std::setprecision(precision);

    if (scientific_notation)
        os << std::scientific;

    if (display_plus)
        os << std::showpos;

    return os;
}
