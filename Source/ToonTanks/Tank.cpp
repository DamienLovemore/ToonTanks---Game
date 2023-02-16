// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Connector"));

    //The object that will follow the root must be a child of the camera connector.
    //(Keeps following the other separated by a distance)
    this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    this->FollowCamera->SetupAttachment(this->SpringArm);
}