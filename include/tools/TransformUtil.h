#ifndef _TRANSFORMUTIL_H_
#define _TRANSFORMUTIL_H_
#include <math.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
//uws84 到东北天坐标转换
class TransformUtil
{

private:
   bool is_set_gps_origin_= false;
   Eigen::Vector3d gps_origin_;
   Eigen::Vector3d origin_ECEF_;

	
public:
	TransformUtil(double lat,double lon,double alt);
	~TransformUtil();
	bool gps2xyz(const double& longitude, const double& latitude, const double& altitude,Eigen::Vector3d& xyz);
	void setGpsOrigin(const Eigen::Vector3d& gps_origin_lat_lon_alt);
    Eigen::Vector3d WGS84toECEF(const Eigen::Vector3d& gps);
};
#endif