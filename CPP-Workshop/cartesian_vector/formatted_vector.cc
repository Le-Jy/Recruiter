#include "formatted_vector.hh"

#include "state_saver.hh"

FormattedVector::FormattedVector(double x, double y)
    : FormatNumericalData("[ ", " ]", 12, true, true)
    , Vector(x, y)
{}

FormattedVector::FormattedVector(Vector vec)
    : FormatNumericalData("[ ", " ]", 12, true, true)
    , Vector(vec)
{}

std::ostream& operator<<(std::ostream& os, const FormattedVector& formattedVect)
{
    StateSaver stateSaver(os);

    formattedVect.formatOs(os);

    os << formattedVect.prefix;

    os << formattedVect.get_x() << " , " << formattedVect.get_y();

    os << formattedVect.suffix;

    return os;
}
