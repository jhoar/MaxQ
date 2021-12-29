// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "SpiceTypes.h"
#include "Spice.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

SPICE_API const FSDistance FSDistance::Zero = FSDistance();
SPICE_API const FSDistance FSDistance::OneKm = FSDistance(1.);
SPICE_API const FSSpeed FSSpeed::Zero = FSSpeed();
SPICE_API const FSDistanceVector FSDistanceVector::Zero = FSDistanceVector();
SPICE_API const FSVelocityVector FSVelocityVector::Zero = FSVelocityVector();
SPICE_API const FSStateTransform FSStateTransform::Identity = FSStateTransform();
SPICE_API const FSAngle FSAngle::_0 = FSAngle();
SPICE_API const FSAngle FSAngle::_360 = FSAngle(twopi_c());
SPICE_API const FSEulerAngles FSEulerAngles::Zero = FSEulerAngles();
SPICE_API const FSQuaternion FSQuaternion::Identity = FSQuaternion();
SPICE_API const FSAngularRate FSAngularRate::Zero = FSAngularRate();
SPICE_API const FSAngularVelocity FSAngularVelocity::Zero = FSAngularVelocity();
SPICE_API const FSEulerAngularState FSEulerAngularState::Zero = FSEulerAngularState();
SPICE_API const FSEulerAngularTransform FSEulerAngularTransform::Identity = FSEulerAngularTransform();
SPICE_API const FSComplexScalar FSComplexScalar::Zero = FSComplexScalar();
SPICE_API const FSEphemerisTime FSEphemerisTime::J2000 = FSEphemerisTime();
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::Zero = FSEphemerisPeriod();
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::Day = FSEphemerisPeriod((double) spd_c());
SPICE_API const FSRotationMatrix FSRotationMatrix::Identity = FSRotationMatrix();
SPICE_API const FSDimensionlessVector FSDimensionlessVector::Zero = FSDimensionlessVector();

FSAngle::FSAngle()
{
    // See notes about cachedPi in its declaration
    cachedDpr = 360. / twopi_c();

    degrees = 0.;
}

FSAngle::FSAngle(double __radians)
{
    // See notes about cachedPi in its declaration
    cachedDpr = 360. / twopi_c();

    degrees = __radians * cachedDpr;
}


USpiceTypes::USpiceTypes()
{
}


const char* USpiceTypes::UnitsToChar(ES_Units units)
{
    const char* result;

    switch (units)
    {
    case ES_Units::RADIANS:
        result = "RADIANS";
        break;
    case ES_Units::DEGREES:
        result = "DEGREES";
        break;
    case ES_Units::ARCMINUTES:
        result = "ARCMINUTES";
        break;
    case ES_Units::ARCSECONDS:
        result = "ARCSECONDS";
        break;
    case ES_Units::HOURANGLE:
        result = "HOURANGLE";
        break;
    case ES_Units::MINUTEANGLE:
        result = "MINUTEANGLE";
        break;
    case ES_Units::SECONDANGLE:
        result = "SECONDANGLE";
        break;
    case ES_Units::METERS:
        result = "METERS";
        break;
    case ES_Units::KILOMETERS:
        result = "KILOMETERS";
        break;
    case ES_Units::CENTIMETERS:
        result = "CENTIMETERS";
        break;
    case ES_Units::MILLIMETERS:
        result = "MILLIMETERS";
        break;
    case ES_Units::FEET:
        result = "FEET";
        break;
    case ES_Units::INCHES:
        result = "INCHES";
        break;
    case ES_Units::YARDS:
        result = "YARDS";
        break;
    case ES_Units::STATUTE_MILES:
        result = "STATUTE_MILES";
        break;
    case ES_Units::NAUTICAL_MILES:
        result = "NAUTICAL_MILES";
        break;
    case ES_Units::AU:
        result = "AU";
        break;
    case ES_Units::PARSECS:
        result = "PARSECS";
        break;
    case ES_Units::LIGHTSECS:
        result = "LIGHTSECS";
        break;
    case ES_Units::LIGHTYEARS:
        result = "LIGHTYEARS";
        break;
    case ES_Units::SECONDS:
        result = "SECONDS";
        break;
    case ES_Units::MINUTES:
        result = "MINUTES";
        break;
    case ES_Units::HOURS:
        result = "HOURS";
        break;
    case ES_Units::DAYS:
        result = "DAYS";
        break;
    case ES_Units::JULIAN_YEARS:
        result = "JULIAN_YEARS";
        break;
    case ES_Units::TROPICAL_YEARS:
        result = "TROPICAL_YEARS";
        break;
    case ES_Units::YEARS:
        result = "YEARS";
        break;
    default:
        result = "";
        break;
    }

    return result;
}

const char* USpiceTypes::_toString(ES_AberrationCorrectionWithNewtonians abcorr)
{
    const char* _abcorr;
    switch (abcorr)
    {
    case ES_AberrationCorrectionWithNewtonians::LT:
        _abcorr = "LT";
        break;
    case ES_AberrationCorrectionWithNewtonians::LT_S:
        _abcorr = "LT+S";
        break;
    case ES_AberrationCorrectionWithNewtonians::CN:
        _abcorr = "CN";
        break;
    case ES_AberrationCorrectionWithNewtonians::CN_S:
        _abcorr = "CN+S";
        break;
    default:
        _abcorr = "NONE";
        break;
    }
    return _abcorr;
}

const char* USpiceTypes::TimeScaleToChar(ES_TimeScale timeScale)
{
    switch (timeScale)
    {
    case ES_TimeScale::TAI:
        return "TAI";
    case ES_TimeScale::TDB:
        return "TDB";
    case ES_TimeScale::TDT:
        return "TDT";
    case ES_TimeScale::ET:
        return "ET";
    case ES_TimeScale::JDTDB:
        return "JDTDB";
    case ES_TimeScale::JDTDT:
        return "JDTDT";
    case ES_TimeScale::JED:
        return "JED";
    }

    return "";
}


FSEulerAngles::FSEulerAngles(const FSDimensionlessVector& value)
{
    angle3 = FSAngle(value.x);
    angle2 = FSAngle(value.y);
    angle1 = FSAngle(value.z);
    axis3 = ES_Axis::X;
    axis2 = ES_Axis::Y;
    axis1 = ES_Axis::Z;
}

void FSEulerAngles::AsDimensionlessVector(FSDimensionlessVector& vector) const
{
    if ((axis3 == ES_Axis::X) && (axis2 == ES_Axis::Y) && (axis1 == ES_Axis::Z))
    {
        // Already ZYX
        vector.x = angle3.AsDouble();
        vector.y = angle2.AsDouble();
        vector.z = angle1.AsDouble();
    }
    else
    {
        // Convert the eulers into ZYX representation
        SpiceDouble _r[3][3];
        SpiceDouble _eulang3 = angle3.AsDouble();
        SpiceDouble _eulang2 = angle2.AsDouble();
        SpiceDouble _eulang1 = angle1.AsDouble();
        SpiceInt _axis3 = (SpiceInt)axis3;
        SpiceInt _axis2 = (SpiceInt)axis2;
        SpiceInt _axis1 = (SpiceInt)axis1;

        eul2m_c(_eulang3, _eulang2, _eulang1, _axis3, _axis2, _axis1, _r);

        _axis3 = (SpiceInt)ES_Axis::X;
        _axis2 = (SpiceInt)ES_Axis::Y;
        _axis1 = (SpiceInt)ES_Axis::Z;

        m2eul_c(_r, _axis3, _axis2, _axis1, &vector.x, &vector.y, &vector.z);
    }
}


double USpiceTypes::Conv_SDistanceToDouble(const FSDistance& value)
{
    return value.AsDouble();
}

FSDistance USpiceTypes::Conv_DoubleToSDistance(double value)
{
    return FSDistance(value);
}

double USpiceTypes::Conv_SSpeedToDouble(
    const FSSpeed& value
)
{
    return value.AsDouble();
}

FSSpeed USpiceTypes::Conv_DoubleToSSpeed(
    double value
)
{
    return FSSpeed(value);
}

double USpiceTypes::Conv_SAngleToDouble(
    const FSAngle& value
)
{
    return value.AsDouble();
}

FSAngle USpiceTypes::Conv_DoubleToSAngle(
    double value
)
{
    return FSAngle(value);
}

double USpiceTypes::Conv_SAngularRateToDouble(
    const FSAngularRate& value
)
{
    return value.AsDouble();
}

FSAngularRate USpiceTypes::Conv_DoubleToSAngularRate(
    double value
)
{
    return FSAngularRate(value);
}

double USpiceTypes::Conv_SEphemerisTimeToDouble(
    const FSEphemerisTime& value
)
{
    return value.AsDouble();
}

FSEphemerisTime USpiceTypes::Conv_DoubleToSEphemerisTime(
    double value
)
{
    return FSEphemerisTime(value);
}

double USpiceTypes::Conv_SEphemerisPeriodToDouble(
    const FSEphemerisPeriod& value
)
{
    return value.AsDouble();
}

FSEphemerisPeriod USpiceTypes::Conv_DoubleToSEphemerisPeriod(
    double value
)
{
    return FSEphemerisPeriod(value);
}

double USpiceTypes::Conv_SMassConstantToDouble(
    const FSMassConstant& value
)
{
    return value.AsDouble();
}

FSMassConstant USpiceTypes::Conv_DoubleToSMassConstant(
    double value
)
{
    return FSMassConstant(value);
}

FSDimensionlessVector USpiceTypes::USpiceTypes::Conv_SVelocityVectorToSDimensionlessVector(
    const FSVelocityVector& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}


FSVelocityVector USpiceTypes::Conv_SDimensionlessVectorToSVelocityVector(
    const FSDimensionlessVector& value
)
{
    return FSVelocityVector(value);
}


FSDimensionlessVector USpiceTypes::Conv_SEulerAnglesToSDimensionlessVector(
    const FSEulerAngles& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSEulerAngles USpiceTypes::Conv_SDimensionlessVectorToSEulerAngles(
    const FSDimensionlessVector& value
)
{
    return FSEulerAngles(value);
}


FSDimensionlessVector USpiceTypes::Conv_SAngularVelocityToSDimensionlessVector(
    const FSAngularVelocity& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSAngularVelocity USpiceTypes::Conv_SDimensionlessVectorToSAngularVelocity(
    const FSDimensionlessVector& value
)
{
    return FSAngularVelocity(value);
}


FSDimensionlessVector USpiceTypes::Conv_SDistanceVectorToSDimensionlessVector(
    const FSDistanceVector& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSDistanceVector USpiceTypes::Conv_SDimensionlessVectorToSDistanceVector(
    const FSDimensionlessVector& value
)
{
    return FSDistanceVector(value);
}

FSRotationMatrix USpiceTypes::Conv_SQuaternionToSRotationMatrix(const FSQuaternion& value)
{
    FSRotationMatrix result;
    USpice::q2m(value, result);
    return result;
}

FSQuaternion USpiceTypes::Conv_SRotationMatrixToSQuaternion(const FSRotationMatrix& value)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    FSQuaternion result;
    
    USpice::m2q(ResultCode, ErrorMessage, value, result);
    
    return ResultCode == ES_ResultCode::Success ? result : FSQuaternion::Identity;
}

// Operators that lean on SPICE's CSPICE implementations instead of implement themselves...
FSRotationMatrix operator*(const FSRotationMatrix& lhs, const FSRotationMatrix& rhs)
{
    FSRotationMatrix result;
    USpice::mxm(lhs, rhs, result);
    return result;
}

FSRotationMatrix USpiceTypes::Multiply_SRotationMatrixSRotationMatrix(const FSRotationMatrix& A, const FSRotationMatrix& B)
{
    return A * B;
}


FSDimensionlessVector operator*(const FSRotationMatrix& lhs, const FSDimensionlessVector& rhs)
{
    FSDimensionlessVector result;
    USpice::mxv(lhs, rhs, result);
    return result;
}

FSDimensionlessVector USpiceTypes::MultiplyVec_SRotationMatrixSDimensionlessVector(const FSRotationMatrix& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDistanceVector operator*(const FSRotationMatrix& lhs, const FSDistanceVector& rhs)
{
    FSDistanceVector result;
    USpice::mxv_distance(lhs, rhs, result);
    return result;
}

FSDistanceVector USpiceTypes::MultiplyDist_SRotationMatrixSDistanceVector(const FSRotationMatrix& A, const FSDistanceVector& B)
{
    return A * B;
}


FSVelocityVector operator*(const FSRotationMatrix& lhs, const FSVelocityVector& rhs)
{
    FSVelocityVector result;
    USpice::mxv_velocity(lhs, rhs, result);
    return result;
}

FSVelocityVector USpiceTypes::MultiplyVel_SRotationMatrixVelocityVector(const FSRotationMatrix& A, const FSVelocityVector& B)
{
    return A * B;
}



FSQuaternion operator*(const FSQuaternion& lhs, const FSQuaternion& rhs)
{
    FSQuaternion result;
    USpice::qxq(lhs, rhs, result);
    return result;
}

FSQuaternion USpiceTypes::Multiply_SQuaternionSQuaternion(const FSQuaternion& A, const FSQuaternion& B)
{
    return A * B;
}


/* Addition (A + B) */
FSEphemerisTime USpiceTypes::Add_SEphemerisTimeSEphemerisPeriod(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return A + B;
}

/* Addition (A + B) */
FSEphemerisTime USpiceTypes::Add_SEphemerisPeriodSEphemerisTime(const FSEphemerisPeriod& A, const FSEphemerisTime& B)
{
    return A + B;
}


/* Addition (A + B) */
FSEphemerisPeriod USpiceTypes::Add_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A + B;
}

/* Subtraction (A - B) */
FSEphemerisPeriod USpiceTypes::Subtract_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A - B;
}

/* Multiplication (A * B) */
FSEphemerisPeriod USpiceTypes::Multiply_DoubleSEphemerisPeriod(double A, const FSEphemerisPeriod& B)
{
    return A * B;
}

/* Multiplication (A * B) */
FSEphemerisPeriod USpiceTypes::Multiply_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A * B;
}


/* Division (A / B) */
FSEphemerisPeriod USpiceTypes::Divide_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A / B;
}

/* Modulo (A % B) */
FSEphemerisPeriod USpiceTypes::Modulus_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A % B;
}

double USpiceTypes::Ratio_SEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A / B;
}


/* Ratio (A / B) */
double USpiceTypes::Ratio_SDistance(const FSDistance& A, const FSDistance& B)
{
    return A / B;
}

FSDistance USpiceTypes::Divide_SDistanceDouble(const FSDistance& A, double B)
{
    return A / B;
}

/* Subtraction (A - B) */
FSDistance USpiceTypes::Subtract_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A - B;
}

FSDistance USpiceTypes::Add_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A + B;
}

/* Multiplication (A * B) */
FSDistance USpiceTypes::Multiply_DoubleSDistance(double A, const FSDistance& B)
{
    return A * B;
}

/* Multiplication (A * B) */
FSDistance USpiceTypes::Multiply_SDistanceDouble(const FSDistance& A, double B)
{
    return A * B;
}


/* Multiplication (A * B) */
FSDistanceVector USpiceTypes::Multiply_SDistanceVectorDouble(const FSDistanceVector& A, double B)
{
    return A * B;
}

/* Multiplication (A * B) */
FSDistanceVector USpiceTypes::Multiply_DoubleSDistanceVector(double A, const FSDistanceVector& B)
{
    return A * B;
}

/* Subtraction (A - B) */
FSDistanceVector USpiceTypes::Subtract_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A - B;
}

/* Addition (A + B) */
FSDistanceVector USpiceTypes::Add_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A + B;
}


FSDimensionlessVector USpiceTypes::Ratio_SDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A / B;
}

FSDistanceVector USpiceTypes::Divide_SDistanceVectorSDimensionlessVector(const FSDistanceVector& A, const FSDimensionlessVector& B)
{
    return A / B;
}


bool USpiceTypes::Greater_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds > B.seconds;
}

bool USpiceTypes::Less_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds < B.seconds;
}


FSSpeed USpiceTypes::Multiply_SSpeedDouble(const FSSpeed& A, double B)
{
    return A * B;
}

FSSpeed USpiceTypes::Multiply_DoubleSSpeed(double A, const FSSpeed& B)
{
    return A * B;
}

FSSpeed USpiceTypes::Divide_SSpeedDouble(FSSpeed A, double B)
{
    return A * B;
}

double USpiceTypes::Ratio_SSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A / B;
}

FSSpeed USpiceTypes::Subtract_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A - B;
}

FSSpeed USpiceTypes::Add_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A + B;
}

FSVelocityVector USpiceTypes::Multiply_SVelocityVectorDouble(const FSVelocityVector& A, double B)
{
    return A * B;
}

FSVelocityVector USpiceTypes::Multiply_DoubleSVelocityVector(double A, const FSVelocityVector& B)
{
    return A * B;
}

FSVelocityVector USpiceTypes::Divide_SVelocityVectorDouble(const FSVelocityVector& A, double B)
{
    return A / B;
}

FSDimensionlessVector USpiceTypes::Ratio_SVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A / B;
}


FSVelocityVector USpiceTypes::Subtract_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A - B;
}

FSVelocityVector USpiceTypes::Add_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A + B;
}

FSAngle USpiceTypes::Multiply_SAngleDouble(const FSAngle& A, double B)
{
    return A * B;
}

FSAngle USpiceTypes::Divide_SAngleDouble(const FSAngle A, double B)
{
    return A / B;
}

double USpiceTypes::Ratio_SAngle(const FSAngle& A, const FSAngle& B)
{
    return A / B;
}


FSAngle USpiceTypes::Subtract_SAngleSAngle(const FSAngle& A, const FSAngle& B)
{
    return A - B;
}


FSAngle USpiceTypes::Add_SAngleSAngle(const FSAngle& A, const FSAngle& B)
{
    return A + B;
}



/* -----------------------------------------------------------------------------------------
 * 
 * UE / SPICE Spatial Data transforms..
 * 
 * Any time we pass coordinate system data across the SPICE/UE boundary we have to
 * convert between the two coordinate systems... That's what Swizzle/Swazzle does.
 * 
 */

FVector USpiceTypes::Conv_SDimensionlessToVector(
    FSDimensionlessVector value
)
{
    return Swizzle(value);
}


FVector USpiceTypes::Conv_SDistanceVectorToVector(
    const FSDistanceVector& value
)
{
    return Swizzle(value);
}


FVector USpiceTypes::Conv_SVelocityVectorToVector(
    const FSVelocityVector& value
)
{
    return Swizzle(value);
}

FSDimensionlessVector USpiceTypes::Conv_VectorToSDimensionless(
    const FVector& value
)
{
    FSDimensionlessVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FSDistanceVector USpiceTypes::Conv_VectorToSDistanceVector(
    const FVector& value
)
{
    FSDistanceVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FSVelocityVector USpiceTypes::Conv_VectorToSVelocityVector(
    const FVector& value
)
{
    FSVelocityVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FQuat USpiceTypes::Conv_SQuaternionToQuat(
    const FSQuaternion& value
)
{
    return Swazzle(value);
}


FSQuaternion USpiceTypes::Conv_QuatToSQuaternion(
    const FQuat& value
)
{
    return Swazzle(value);
}

/* 
 * -----------------------------------------------------------------------------------------
 */


