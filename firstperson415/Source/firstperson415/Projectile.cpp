#include "Projectile.h"

#include "Components/DecalComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(
        TEXT("SphereComp")
    );
    CollisionComp->InitSphereRadius(20.0f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionComp->SetNotifyRigidBodyCollision(true);
    CollisionComp->SetGenerateOverlapEvents(false);
    CollisionComp->SetSimulatePhysics(false);
    CollisionComp->BodyInstance.bUseCCD = true;
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

    RootComponent = CollisionComp;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(CollisionComp);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BallMesh->SetGenerateOverlapEvents(false);
    BallMesh->SetSimulatePhysics(false);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
        TEXT("ProjectileComp")
    );
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = 3.0f;

    ProjectileMat = nullptr;
    BaseMat = nullptr;
    DmiMat = nullptr;
    RandColor = FLinearColor::White;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    RandColor = FLinearColor(
        UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f),
        UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f),
        UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f),
        1.0f
    );

    if (ProjectileMat)
    {
        DmiMat = UMaterialInstanceDynamic::Create(ProjectileMat, this);

        if (DmiMat)
        {
            BallMesh->SetMaterial(0, DmiMat);
            DmiMat->SetVectorParameterValue(TEXT("ProjColor"), RandColor);
        }
        else
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Failed to create dynamic material instance for projectile")
            );
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ProjectileMat is null"));
    }
}

void AProjectile::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
        
        Destroy();
    }

    if (OtherActor != nullptr)
    {
        if (colorP)
        {
            UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
                colorP,
                HitComp,
                NAME_None,
                FVector(-20.0, 0.f, 0.f),
                FRotator(0.f),
                EAttachLocation::KeepRelativeOffset,
                true
            );
            if (particleComp)
            {
                particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), RandColor);
            }
            BallMesh->DestroyComponent();
            CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
        }

        float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);

        auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BaseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
        auto MatInstance = Decal->CreateDynamicMaterialInstance();

        MatInstance->SetVectorParameterValue("Color", RandColor);
        MatInstance->SetScalarParameterValue("Frame", frameNum);
    }
}