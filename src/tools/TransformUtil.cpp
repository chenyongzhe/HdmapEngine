#include"tools/TransformUtil.h"

TransformUtil::TransformUtil(double lat,double lon,double alt){
	gps_origin_ << 0, 0, 0;
    origin_ECEF_ << 0, 0, 0;
    Eigen::Vector3d gps_origin_lat_lon_alt(lat, lon, alt);
    setGpsOrigin(gps_origin_lat_lon_alt);

}



TransformUtil::~TransformUtil(){
	
}


Eigen::Vector3d TransformUtil::WGS84toECEF(const Eigen::Vector3d& gps)

{
  double SEMI_MAJOR_AXIS = 6378137.0;
  //    double RECIPROCAL_OF_FLATTENING = 298.257223563;
  //    double SEMI_MINOR_AXIS = 6356752.3142;
  double FIRST_ECCENTRICITY_SQUARED = 6.69437999014e-3;
  //    double SECOND_ECCENTRICITY_SQUARED = 6.73949674228e-3;

  double lon = gps[0];
  double lat = gps[1];
  double ati = gps[2];

  if (!std::isnan(gps[2]))
    ati = gps[2];

  double rad_lon = lon / 180 * M_PI;
  double rad_lat = lat / 180 * M_PI;

  double sin_lon = sin(rad_lon);
  double cos_lon = cos(rad_lon);
  double sin_lat = sin(rad_lat);
  double cos_lat = cos(rad_lat);

  double chi = sqrt(1.0 - FIRST_ECCENTRICITY_SQUARED * sin_lat * sin_lat);
  double N = SEMI_MAJOR_AXIS / chi + ati;

  // clang-format off
  Eigen::Vector3d ret = Eigen::Vector3d::Zero();
  ret << N * cos_lat * cos_lon,
        N * cos_lat * sin_lon,
        (SEMI_MAJOR_AXIS * (1.0 - FIRST_ECCENTRICITY_SQUARED) / chi + ati) * sin_lat;
  // clang-format on
  return ret;
}


void TransformUtil::setGpsOrigin(const Eigen::Vector3d& gps_origin_lat_lon_alt)
{
  is_set_gps_origin_ = true;
  // latitude, longitude, altitude
  gps_origin_ = gps_origin_lat_lon_alt;  // 39.9680502, 116.3045885,

  Eigen::Vector3d origin_WGS84(gps_origin_[1], gps_origin_[0], gps_origin_[2]);
  origin_ECEF_ = WGS84toECEF(origin_WGS84);
}




bool TransformUtil::gps2xyz(const double& longitude, const double& latitude, const double& altitude,
                            Eigen::Vector3d& xyz)
{
 
  // gps << gps_msg.longitude, gps_msg.latitude, gps_msg.altitude;
  Eigen::Vector3d gps(longitude, latitude, altitude);
  Eigen::Vector3d gps_ECEF = WGS84toECEF(gps);

  //××××××××处理GPS数据
  double rad_lon = gps_origin_[1] / 180 * M_PI;
  double rad_lat = gps_origin_[0] / 180 * M_PI;
  double sin_lon = sin(rad_lon);
  double cos_lon = cos(rad_lon);
  double sin_lat = sin(rad_lat);
  double cos_lat = cos(rad_lat);

  Eigen::Matrix3d rot = Eigen::Matrix3d::Zero();
  // clang-format off
  rot << -sin_lon, cos_lon, 0,
        -sin_lat * cos_lon, -sin_lat * sin_lon, cos_lat,
        cos_lat * cos_lon, cos_lat * sin_lon, sin_lat;
  // clang-format on

  Eigen::Vector3d diff_ECEF = gps_ECEF - origin_ECEF_;
  Eigen::Vector3d xyz_ECEF = rot * diff_ECEF;
  xyz << xyz_ECEF[0], xyz_ECEF[1], xyz_ECEF[2];
  return true;
}

