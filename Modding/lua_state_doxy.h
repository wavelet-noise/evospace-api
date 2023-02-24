#pragma once
#include "CoreMinimal.h"

/**
 * @brief Vec3 integer
 */
class Vec3i {
  public:
    /**
     * @brief Property. First dim value
     */
    int32 x;

    /**
     * @brief Property. Second dim value
     */
    int32 y;

    /**
     * @brief Property. Third dim value
     */
    int32 z;

    /**
     * @brief Readonly function. Construct Vec3i from 3 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.new(x, y, z)
     * @endcode
     * @param x
     * @param y
     * @param z
     * @return Constructed Vec3i(x, y, z) object
     */
    static Vec3i new(int32 x, int32 y, int32 z);

    /**
     * @brief Readonly property. Construct Vec3i from (0, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.zero
     * @endcode
     * @return Constructed Vec3i(0, 0, 0) object
     */
    static Vec3i zero;

    /**
     * @brief Readonly property. Construct Vec3i from (1, 1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.one
     * @endcode
     * @return Constructed Vec3i(1, 1, 1) object
     */
    static Vec3i one;

    /**
     * @brief Readonly property. Construct Vec3i from up (0, 0, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.up
     * @endcode
     * @return Constructed Vec3i(0, 0, 1) object
     */
    static Vec3i up;

    /**
     * @brief Readonly property. Construct Vec3i from (0, 0, -1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.down
     * @endcode
     * @return Constructed Vec3i(0, 0, -1) object
     */
    static Vec3i down;

    /**
     * @brief Readonly property. Construct Vec3i from (0, 1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.left
     * @endcode
     * @return Constructed Vec3i(0, 1, 0) object
     */
    static Vec3i left;

    /**
     * @brief Readonly property. Construct Vec3i from (0, -1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.right
     * @endcode
     * @return Constructed Vec3i(0, -1, 0) object
     */
    static Vec3i right;

    /**
     * @brief Readonly property. Construct Vec3i from (-1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.back
     * @endcode
     * @return Constructed Vec3i(-1, 0, 0) object
     */
    static Vec3i back;

    /**
     * @brief Static function. Construct Vec3i from (1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.front
     * @endcode
     * @return Constructed Vec3i(1, 0, 0) object
     */
    static Vec3i front;
};

/**
 * @brief Vec3 float
 */
struct Vec3 {
  public:
    /**
     * @brief Property. First dim value
     */
    float x;

    /**
     * @brief Property. Second dim value
     */
    float y;

    /**
     * @brief Property. Third dim value
     */
    float z;

    /**
     * @brief Static function. Construct Vec3 from 3 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec.new(x, y, z)
     * @endcode
     * @param x
     * @param y
     * @param z
     * @return Vec3(x, y, z) object
     */
    static FVector new(float x, float y, float z);
};

/**
 * @brief Vec2 integer
 */
class Vec2i {
  public:
    /**
     * @brief Property. First dim value
     */
    int32 x;

    /**
     * @brief Property. Second dim value
     */
    int32 y;

    /**
     * @brief Static function. Construct Vec2i from 2 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.new(x, y)
     * @endcode
     * @param x
     * @param y
     * @return Constructed Vec3i(x, y) object
     */
    static Vec2i new(int32 x, int32 y);

    /**
     * @brief Readonly property. Construct Vec2i from (0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.zero
     * @endcode
     * @return Constructed Vec2i(0, 0) object
     */
    static Vec2i zero;

    /**
     * @brief Readonly property. Construct Vec3i from (1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.one
     * @endcode
     * @return Constructed Vec2i(1, 1) object
     */
    static Vec2i one;
};

/**
 * @brief Namespace for coordinate system translations
 */
class cs {
  public:
    /**
     * @brief Static function. Convert block position to sector position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.bp2sp()
     * @endcode
     * @param bpos Vec3i block position
     * @return Vec3i sector position
     */
    static Vec3i bp2sp(const Vec3i &bpos);

    /**
     * @brief Static function. Convert world position to sector position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_w2bp()
     * @endcode
     * @param bpos Vec3 world position
     * @return Vec3i block position
     */
    static Vec3i w2bp(const FVector &world);

    /**
     * @brief Static function. Convert block position to world position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_bp2w()
     * @endcode
     * @param bpos Vec3i block position
     * @return Vec3 world position
     */
    static FVector bp2w(const Vec3i &bpos);

    /**
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_w2sp()
     * @endcode
     * @param bpos Vec3i world position
     * @return Vec3i sector position
     */
    static Vec3i w2sp(const FVector &world);
};