#include "Simulation/PlayerMotorComponent.h"
UPlayerMotorComponent::UPlayerMotorComponent(){ PrimaryComponentTick.bCanEverTick=false; }
void UPlayerMotorComponent::SetDesiredVelocity(const FVector& InDesiredVelocityMetersPerSecond) { DesiredVelocity=InDesiredVelocityMetersPerSecond.GetClampedToMaxSize(MaxSpeedMetersPerSecond); }
void UPlayerMotorComponent::SimulateFixedStep(float StepSeconds) {
 if (StepSeconds<=0.0f) return;
 const FVector Error=DesiredVelocity-State.VelocityMetersPerSecond;
 State.VelocityMetersPerSecond+=Error.GetClampedToMaxSize(MaxAccelerationMetersPerSecondSquared*StepSeconds);
 State.VelocityMetersPerSecond=State.VelocityMetersPerSecond.GetClampedToMaxSize(MaxSpeedMetersPerSecond);
 State.PositionMeters+=State.VelocityMetersPerSecond*StepSeconds;
 const FVector Horizontal(State.VelocityMetersPerSecond.X,State.VelocityMetersPerSecond.Y,0.0);
 if (!Horizontal.IsNearlyZero()) State.BodyYawDegrees=FMath::FixedTurn(State.BodyYawDegrees,Horizontal.Rotation().Yaw,MaxYawRateDegreesPerSecond*StepSeconds);
}
