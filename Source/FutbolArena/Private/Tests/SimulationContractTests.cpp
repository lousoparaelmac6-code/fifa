#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Simulation/PlayerMotorComponent.h"
#include "Simulation/BallPhysicsComponent.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerMotorLimitsTest,"FutbolArena.Simulation.PlayerMotor.LimitsVelocity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FPlayerMotorLimitsTest::RunTest(const FString& Parameters) {
 UPlayerMotorComponent* M=NewObject<UPlayerMotorComponent>(); M->MaxSpeedMetersPerSecond=8.0f; M->SetDesiredVelocity(FVector(1000,0,0));
 for(int32 I=0;I<600;++I) M->SimulateFixedStep(1.0f/60.0f);
 TestTrue(TEXT("Velocity is clamped"),M->GetMotorState().VelocityMetersPerSecond.Size()<=8.001f);
 TestTrue(TEXT("Motor advances"),M->GetMotorState().PositionMeters.X>0.0); return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBallImpulseLimitTest,"FutbolArena.Simulation.BallPhysics.LimitsKickSpeed",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FBallImpulseLimitTest::RunTest(const FString& Parameters) {
 UBallPhysicsComponent* B=NewObject<UBallPhysicsComponent>(); B->ApplyKickImpulse(FVector(100000,0,0));
 TestTrue(TEXT("Kick speed is clamped"),B->GetBallState().VelocityMetersPerSecond.Size()<=45.001f); return true;
}
#endif
