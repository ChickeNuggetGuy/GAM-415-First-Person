#include "Projectile.h"

#include "Components/DecalComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Projectile OnHit fired"));

    if (BaseMat)
    {
        const float FrameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);

        const FRotator DecalRotation =
            Hit.ImpactNormal.Rotation() + FRotator(-90.0f, 0.0f, 0.0f);

        UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
            GetWorld(),
            BaseMat,
            FVector(32.0f, 32.0f, 32.0f),
            Hit.ImpactPoint,
            Hit.ImpactNormal.Rotation(),
            10.0f
        );
        if (Decal)
        {
            UMaterialInstanceDynamic* MatInstance =
                Decal->CreateDynamicMaterialInstance();

            if (MatInstance)
            {
                MatInstance->SetVectorParameterValue(TEXT("color"), RandColor);
                MatInstance->SetScalarParameterValue(TEXT("Frame"), FrameNum);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn decal"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BaseMat is null"));
    }

    if ((OtherActor != nullptr) && (OtherActor != this) &&
        (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(
            GetVelocity() * 100.0f,
            GetActorLocation()
        );
    }

    Destroy();
}