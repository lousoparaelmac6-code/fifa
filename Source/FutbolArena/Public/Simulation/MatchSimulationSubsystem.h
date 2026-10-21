#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include "MatchSimulationSubsystem.generated.h"
USTRUCT(BlueprintType)
struct FMatchSimulationSnapshot {
 GENERATED_BODY()
 UPROPERTY(BlueprintReadOnly, Category="Simulation") int64 Tick = 0;
 UPROPERTY(BlueprintReadOnly, Category="Simulation") int32 HomeScore = 0;
 UPROPERTY(BlueprintReadOnly, Category="Simulation") int32 AwayScore = 0;
 UPROPERTY(BlueprintReadOnly, Category="Simulation") float MatchSeconds = 0.0f;
};
UCLASS()
class FUTBOLARENA_API UMatchSimulationSubsystem : public UTickableWorldSubsystem {
 GENERATED_BODY()
public:
 virtual void Tick(float DeltaTime) override;
 virtual TStatId GetStatId() const override;
 virtual bool IsTickable() const override { return !IsTemplate(); }
 UFUNCTION(BlueprintCallable, Category="Simulation") void StartSimulation(int32 InSeed = 24301);
 UFUNCTION(BlueprintCallable, Category="Simulation") void StopSimulation();
 UFUNCTION(BlueprintPure, Category="Simulation") FMatchSimulationSnapshot GetSnapshot() const { return Snapshot; }
 UFUNCTION(BlueprintPure, Category="Simulation") float GetInterpolationAlpha() const { return static_cast<float>(Accumulator / FixedStepSeconds); }
private:
 static constexpr double FixedStepSeconds = 1.0 / 60.0;
 static constexpr double MaxFrameContribution = 0.25;
 double Accumulator = 0.0; bool bRunning = false; FRandomStream RandomStream;
 UPROPERTY(VisibleAnywhere, Category="Simulation") FMatchSimulationSnapshot Snapshot;
 void SimulateFixedStep(float StepSeconds); void RecordDiagnostic(const TCHAR* EventName);
};
