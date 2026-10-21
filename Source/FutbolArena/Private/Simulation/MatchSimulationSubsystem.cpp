#include "Simulation/MatchSimulationSubsystem.h"
void UMatchSimulationSubsystem::StartSimulation(int32 InSeed) {
 Accumulator=0.0; Snapshot=FMatchSimulationSnapshot{}; RandomStream.Initialize(InSeed); bRunning=true;
 RecordDiagnostic(TEXT("simulation_started"));
}
void UMatchSimulationSubsystem::StopSimulation() { bRunning=false; RecordDiagnostic(TEXT("simulation_stopped")); }
void UMatchSimulationSubsystem::Tick(float DeltaTime) {
 if (!bRunning || DeltaTime<=0.0f) return;
 Accumulator += FMath::Min(static_cast<double>(DeltaTime),MaxFrameContribution);
 while (Accumulator>=FixedStepSeconds) { SimulateFixedStep(static_cast<float>(FixedStepSeconds)); Accumulator-=FixedStepSeconds; }
}
void UMatchSimulationSubsystem::SimulateFixedStep(float StepSeconds) {
 ++Snapshot.Tick; Snapshot.MatchSeconds+=StepSeconds;
 // Orden pendiente: decisiones -> motores/balón -> contactos -> reglas -> telemetría.
}
TStatId UMatchSimulationSubsystem::GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(UMatchSimulationSubsystem,STATGROUP_Tickables); }
void UMatchSimulationSubsystem::RecordDiagnostic(const TCHAR* EventName) {
 UE_LOG(LogTemp,Verbose,TEXT("[MatchSimulation] event=%s tick=%lld time=%.3f"),EventName,Snapshot.Tick,Snapshot.MatchSeconds);
}
