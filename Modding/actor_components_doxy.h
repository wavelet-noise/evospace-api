
#pragma once

/**
 * @brief Static mesh component
 */
class UStaticMeshComponent {

    /**
     * @brief Set the static mesh for the component.
     * @param StaticMesh UStaticMesh pointer representing the new static mesh.
     */
    void SetStaticMesh(UStaticMesh* StaticMesh);

    /**
     * @brief Get the static mesh of the component.
     * @return UStaticMesh pointer representing the current static mesh.
     */
    UStaticMesh* GetStaticMesh() const;

    /**
     * @brief Set the material for the component at the specified index.
     * @param ElementIndex int32 representing the material index.
     * @param Material UMaterialInterface pointer representing the new material.
     */
    void SetMaterial(int32 ElementIndex, UMaterialInterface* Material);

    /**
     * @brief Get the material of the component at the specified index.
     * @param ElementIndex int32 representing the material index.
     * @return UMaterialInterface pointer representing the current material.
     */
    UMaterialInterface* GetMaterial(int32 ElementIndex) const;

    /**
     * @brief Set the relative location (translation) of the component.
     * @param NewLocation FVector representing the new relative location.
     */
    void SetRelativeLocation(const FVector& NewLocation);

    /**
     * @brief Get the relative location (translation) of the component.
     * @return FVector representing the relative location of the component.
     */
    FVector GetRelativeLocation() const;

    /**
     * @brief Set the relative rotation (orientation) of the component.
     * @param NewRotation FRotator representing the new relative rotation.
     */
    void SetRelativeRotation(const FRotator& NewRotation);

    /**
     * @brief Get the relative rotation (orientation) of the component.
     * @return FRotator representing the relative rotation of the component.
     */
    FRotator GetRelativeRotation() const;

    /**
     * @brief Set the relative scale of the component.
     * @param NewScale FVector representing the new relative scale.
     */
    void SetRelativeScale3D(const FVector& NewScale);

    /**
     * @brief Get the relative scale of the component.
     * @return FVector representing the relative scale of the component.
     */
    FVector GetRelativeScale3D() const;
};
