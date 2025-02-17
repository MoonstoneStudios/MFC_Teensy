/// @brief Error codes for RSX. 
/// @note Arduino does not support exceptions and try/catch. We must validate and anticipate errors.
enum ErrorCodes {

    RSX_NO_ERRROR = 0,
    RSX_IMU_I2C_NOT_CONN = 1,
    RSX_IMU_I2C_NO_LONGER_CONNECTED = 2,
    RSX_JETSON_I2C_NOT_CONN = 4,
    RSX_LIDAR_USB_NOT_CONN = 8,

};