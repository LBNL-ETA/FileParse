#pragma once

namespace Helper
{
    struct CMAValues
    {
        double conductivity{0};
        double filmCoefficient{0};

        CMAValues() = default;
        CMAValues(double conductivity, double film) :
            conductivity(conductivity), filmCoefficient(film)
        {}

        // Equality operator
        bool operator==(const CMAValues & other) const
        {
            return conductivity == other.conductivity && filmCoefficient == other.filmCoefficient;
        }
    };
}   // namespace Helper