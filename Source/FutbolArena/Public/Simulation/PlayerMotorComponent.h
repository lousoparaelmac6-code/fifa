#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMotorComponent.generated.h"
USTRUCT(BlueprintType)
struct FPlayerMotorState {
 GENERATED_BODY()
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Motor") FVector PositionMeters=FVector::ZeroVector;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Motor") FVector VelocityMetersPerSecond=FVector::ZeroVector;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Motor") float BodyYawDegrees=0.0f;
};
UCLASS(ClassGroup=(Football),meta=(BlueprintSpawnableComponent))
class FUTBOLARENA_API UPlayerMotorComponent : public UActorComponent {
 GENERATED_BODY()
public:
 UPlayerMotorComponent();
 UFUNCTION(BlueprintCallable,Category="Motor") void SetDesiredVelocity(const FVector& DesiredVelocityMetersPerSecond);
 UFUNCTION(BlueprintPure,Category="Motor") FPlayerMotorState GetMotorState() const { return State; }
 void SimulateFixedStep(float StepSeconds);
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Motor|Tuning",meta=(ClampMin="0.0")) float MaxAccelerationMetersPerSecondSquared=5.0f;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Motor|Tuning",meta=(ClampMin="0.0")) float MaxSpeedMetersPerSecond=8.0f;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Motor|Tuning",meta=(ClampMin="0.0")) float MaxYawRateDegreesPerSecond=240.0f;
private:
 UPROPERTY(VisibleAnywhere,Category="Motor") FPlayerMotorState State; FVector DesiredVelocity=FVector::ZeroVector;
};
