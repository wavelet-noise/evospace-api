#pragma once
/**
 * @class FColor
 * @brief Represents a color using four 8-bit channels (RGBA).
 *
 * FColor stores color components as unsigned 8-bit integers, each ranging from
 * 0 to 255. This class provides basic functionality to manipulate colors, such
 * as reading and setting individual color channels.
 */
class FColor {
  public:
    uint8 R; /**< Red color component */
    uint8 G; /**< Green color component */
    uint8 B; /**< Blue color component */
    uint8 A; /**< Alpha (transparency) component */

    /**
     * @brief red A predefined red color (255, 0, 0).
     **/
    static FColor red;
    /**
     * @brief green A predefined green color (0, 255, 0).
     **/
    static FColor green;
    /**
     * @brief blue A predefined blue color (0, 0, 255).
     **/
    static FColor blue;
    /**
     * @brief yellow A predefined yellow color (255, 255, 0).
     **/
    static FColor yellow;
    /**
     * @brief cyan A predefined cyan color (0, 255, 255).
     **/
    static FColor cyan;
    /**
     * @brief magenta A predefined magenta color (255, 0, 255).
     **/
    static FColor magenta;
    /**
     * @brief white A predefined white color (255, 255, 255).
     * */
    static FColor white;
    /**
     * @brief black A predefined black color (0, 0, 0).
     **/
    static FColor black;
    /**
     * @brief gray A predefined gray color (128, 128, 128).
     **/
    static FColor gray;
    /**
     * @brief transparent A predefined transparent color (0, 0, 0, 0).
     **/
    static FColor transparent;
};

/**
 * @class FQuat
 * @brief Represents a quaternion for 3D rotations.
 *
 * FQuat is a class representing a unit quaternion, used for 3D rotations.
 * It provides various operations to manipulate and transform quaternions.
 */
class FQuat {
  public:
    float X; /**< X component of the quaternion */
    float Y; /**< Y component of the quaternion */
    float Z; /**< Z component of the quaternion */
    float W; /**< W component of the quaternion */

    /**
     * @brief Get the forward vector of the quaternion.
     * @return FVector representing the forward direction of the quaternion.
     */
    FVector GetForwardVector() const;

    /**
     * @brief Get the right vector of the quaternion.
     * @return FVector representing the right direction of the quaternion.
     */
    FVector GetRightVector() const;

    /**
     * @brief Get the up vector of the quaternion.
     * @return FVector representing the up direction of the quaternion.
     */
    FVector GetUpVector() const;
};

/**
 * @class FTransform
 * @brief Represents a 3D transformation, including translation, rotation, and
 * scale.
 *
 * FTransform is a class that stores a 3D transformation, including translation
 * (position), rotation (orientation), and scale. It provides various operations
 * to manipulate and transform objects in 3D space.
 */
class FTransform {
  public:
    FVector
        Translation; /**< Translation (position) component of the transform */
    FQuat Rotation;  /**< Rotation (orientation) component of the transform as a
                        quaternion */
    FVector Scale;   /**< Scale component of the transform */

    /**
     * @brief Get the forward vector of the transform.
     * @return FVector representing the forward direction of the transform.
     */
    FVector GetForwardVector() const;

    /**
     * @brief Get the right vector of the transform.
     * @return FVector representing the right direction of the transform.
     */
    FVector GetRightVector() const;

    /**
     * @brief Get the up vector of the transform.
     * @return FVector representing the up direction of the transform.
     */
    FVector GetUpVector() const;

    /**
     * @brief Transform a position vector by this transform.
     * @param Position The position vector to transform.
     * @return FVector representing the transformed position.
     */
    FVector TransformPosition(const FVector &Position) const;

    /**
     * @brief Inverse transform a position vector by this transform.
     * @param Position The position vector to inverse transform.
     * @return FVector representing the inverse transformed position.
     */
    FVector InverseTransformPosition(const FVector &Position) const;

    /**
     * @brief Set the location (translation) of the transform.
     * @param Location FVector representing the new location.
     */
    void SetLocation(const FVector &Location);

    /**
     * @brief Set the rotation (orientation) of the transform.
     * @param Rotation FQuat representing the new rotation as a quaternion.
     */
    void SetRotation(const FQuat &Rotation);

    /**
     * @brief Set the scale of the transform.
     * @param Scale FVector representing the new scale.
     */
    void SetScale3D(const FVector &Scale);

    /**
     * @brief Get the location (translation) of the transform.
     * @return FVector representing the location of the transform.
     */
    FVector GetLocation() const;

    /**
     * @brief Get the rotation (orientation) of the transform.
     * @return FQuat representing the rotation of the transform as a quaternion.
     */
    FQuat GetRotation() const;

    /**
     * @brief Get the scale of the transform.
     * @return FVector representing the scale of the transform.
     */
    FVector GetScale3D() const;
};