#include "Simulation/BallPhysicsComponent.h"
UBallPhysicsComponent::UBallPhysicsComponent(){ PrimaryComponentTick.bCanEverTick=false; }
void UBallPhysicsComponent::ApplyKickImpulse(const FVector& ImpulseNewtonSeconds) {
 State.VelocityMetersPerSecond+=ImpulseNewtonSeconds/FMath::Max(MassKilograms,0.01f);
 State.VelocityMetersPerSecond=State.VelocityMetersPerSecond.GetClampedToMaxSize(MaxSpeedMetersPerSecond);
}
void UBallPhysicsComponent::SimulateFixedStep(float StepSeconds) {
 if (StepSeconds<=0.0f) return;
 State.VelocityMetersPerSecond.Z-=9.81f*StepSeconds; State.PositionMeters+=State.VelocityMetersPerSecond*StepSeconds;
 // Prototipo de suelo; faltan contactos calibrados con jugadores y postes.
 if (State.PositionMeters.Z<0.0f) {
  State.PositionMeters.Z=0.0f;
  if (State.VelocityMetersPerSecond.Z<0.0f) State.VelocityMetersPerSecond.Z*=-0.45f;
  FVector H(State.VelocityMetersPerSecond.X,State.VelocityMetersPerSecond.Y,0.0); const float S=H.Size();
  if (S>UE_KINDA_SMALL_NUMBER) { H*=FMath::Max(0.0f,S-GroundRollingDeceleration*StepSeconds)/S; State.VelocityMetersPerSecond.X=H.X; State.VelocityMetersPerSecond.Y=H.Y; }
 }
}
