#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BallPhysicsComponent.generated.h"
USTRUCT(BlueprintType)
struct FBallSimulationState {
 GENERATED_BODY()
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Ball") FVector PositionMeters=FVector::ZeroVector;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Ball") FVector VelocityMetersPerSecond=FVector::ZeroVector;
 UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Ball") FVector SpinRadiansPerSecond=FVector::ZeroVector;
};
UCLASS(ClassGroup=(Football),meta=(BlueprintSpawnableComponent))
class FUTBOLARENA_API UBallPhysicsComponent : public UActorComponent {
 GENERATED_BODY()
public:
 UBallPhysicsComponent();
 UFUNCTION(BlueprintCallable,Category="Ball") void ApplyKickImpulse(const FVector& ImpulseNewtonSeconds);
 UFUNCTION(BlueprintPure,Category="Ball") FBallSimulationState GetBallState() const { return State; }
 void SimulateFixedStep(float StepSeconds);
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ball|Tuning",meta=(ClampMin="0.01")) float MassKilograms=0.43f;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ball|Tuning",meta=(ClampMin="0.0")) float GroundRollingDeceleration=0.35f;
 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ball|Tuning",meta=(ClampMin="0.0")) float MaxSpeedMetersPerSecond=45.0f;
private: UPROPERTY(VisibleAnywhere,Category="Ball") FBallSimulationState State;
};
