//
//  EngineBridge.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "CEngineBridge.h"
#import "CEngine.h"
#import "EWVehicle.h"
#import "CVehicle.h"
#import "CLane.h"
#import "EWLane.h"
#import <vector>
#import "CEnginePlugin.h"
#import "EWTrafficController.h"
#import "SharedEnum.h"


struct CEngineBridgeImpl : CEngine, CEnginePlugin
{
    CEngineBridgeImpl(void (*printOutFunc) (string), void* fascadeObject): CEngine(printOutFunc, this), CEnginePlugin(fascadeObject)
    {
        self = (__bridge id)_fascadeObject;
    };
    
    NSMutableArray* vehicles;
    id self;
    //CEngineBridgeImpl(): CEngine(){};
    void PreUpdateVehicle(CVehicle *vehicle)
    {
        //Nothing to do before the vehicle is being updated
    }
    
    void PostUpdateVehicle(CVehicle* vehicle)
    {
        //id self = (__bridge id)_fascadeObject;
        [self UpdatePosition:vehicle->getID()];
        
        [self UpdateRemainingTime: this->GetRemainingTime()];
    }
    
    void GameOver(GameOverReason reason)
    {
        //[(__bridge id)_fascadeObject ItsGameOver];
        if(reason == GameOverReason::CRASH)
            [self GameOverVehicleCrashed];
        else
            [self GameOverTimeIsUp];
    }
    
    void PostNewVehicle(CVehicle* vehicle)
    {
        //[self NewVe]
    }
    
    virtual void PostRemoveVehicle(int id)
    {
        [self RemoveVehicle:id];
    }
    
};

@implementation CEngineBridge

/*void CEngineBridgeImpl::PreUpdateVehicle(CVehicle *vehicle)
{
    cout << "Dude from wrapper";
}*/


-(void) StartGame
{
    _cEngine->StartGame();
}

-(EWLane*) SyncLaneWithEngine:(EWLane *)inputLane
{
    CLane* lane = _cEngine->GetNewLane((Color)inputLane.tag);
    inputLane.Id = lane->getID();
    
    lane->Position->setX(inputLane.center.x);
    lane->Position->setY(inputLane.center.y);
    
    return inputLane;
}

-(void) UpdatePosition:(NSMutableArray *)vehicles deltaTimes: (CGFloat) deltaTime
{
    vector<CVehicle> internalVehicles = _cEngine->GetAllVehicles();
    
    vector<CVehicle>::iterator it = internalVehicles.begin();
    
    for(;it != internalVehicles.end(); it++)
    {
        //bool found = true;
        for(EWVehicle* vehicle in vehicles)
        {
            if(vehicle.Id == it->getID())
            {
                
                vehicle.ToBeRemoved = it->IsToBeRemoved();
                //it->Position->setX(vehicle.center.x);
                //it->Position->setY(vehicle.center.y);
#warning try to move everything to GetAllVehicles and to try to get the MoveMethod to handle the update of X
                //_cEngine->GetVehiclesCurrentPosition(&*it, deltaTime);
                
                /*CGPoint position;
                position.x = it->Position->getX();
                position.y = it->Position->getY();
                vehicle.center = position;*/
                vehicle.center = GetCGPointFromPosition(it->Position);
                break;
            }
        }
    }
    
}

CGPoint GetCGPointFromPosition(CPosition* cPosition)
{
    CGPoint position;
    position.x = cPosition->getX();
    position.y = cPosition->getY();
    return position;

}

-(void) MoveVehicle:(EWVehicle *)vehicle
{
    CVehicle* internalVehicle = _cEngine->GetVehicle(vehicle.Id);
    CLane* goalLane = _cEngine->GetLane(vehicle.goalLane.Id);
#warning Change this to be a intersect check with any of the existing lanes
    internalVehicle->CurrentLane = goalLane;
    internalVehicle->Move(vehicle.center.x, vehicle.center.y);
    //_cEngine->MoveVehicle(vehicle.center.x, vehicle.center.y, internalVehicle);
}

//Updates all
-(void)Update: (float) deltaTime{
    _cEngine->GetAllVehicles();
}

-(void)UpdatePosition:(int)id
{
    
    NSLog(@"Updating position for vehicle with id: %d", id);
    
    CVehicle* internalVehicle = _cEngine->GetVehicle(id);
    
    EWVehicle* vehicle = [_vehicleDictionary objectForKey:@(id)];
    
    vehicle.center = GetCGPointFromPosition(internalVehicle->Position);
}

-(void) GetNewVehicle
{
}

-(EWVehicle*) GetNewVehicle: (EWLane*) lane
{
    CLane* internalLane = _cEngine->GetLane(lane.Id);
    CVehicle* vehicle = _cEngine->GetNewVehicle(internalLane);
    
    string carImage;
    switch(vehicle->Color) {
        case GREEN:
            carImage = "GreenCar";
            break;
        case 1:
            carImage = "RedCar";
            break;
        case 2:
            carImage = "BlueCar";
            break;
    }

    
    
    EWVehicle* v = [[EWVehicle alloc]
                    initWithName: getNSString(carImage.c_str())
                    id:vehicle->getID()];
    
    //v.goalTag = vehicle->getType();
    //v.goalLane = lane;
    
    NSLog(@"Size height: %g, width: %g", v.frame.size.height, v.frame.size.width);
    
    CGPoint position;
    position.x = vehicle->Position->getX();
    position.y = vehicle->Position->getY();
    v.center = position;
    
    [_controller addVehicleView:v];
    //[self registerVehicle:v];
    
    v.controller = _controller;
    
    [_vehicleDictionary setObject:v forKey:@(v.Id)];
    
    return v;
}

EWLane* mapFromCLane(CLane* lane, EWLane* toLane)
{
    return toLane;
}

void writeSomething()
{
    NSLog(@"NSLog: Testing the method");
}

-(void)WriteSomething {
    NSLog(@"Objective C method from C++");
}

- (id) initWithController:(EWTrafficController *)controller
{
    _controller = controller;
    self = [super init];
    _cEngine = new CEngineBridgeImpl(logFunction, (__bridge void*)(self));
    _vehicleDictionary = [[NSMutableDictionary alloc] initWithCapacity:10];
    return self;
}

void logFunction(string message)
{
    message = "\n" + message + "\n";
    NSLog(getNSString(&message));
}

-(NSString*)getValue
{
    return @"Dude from C++";
}

NSString* getNSString(const char* value)
{
    NSString* result = [[NSString alloc] initWithUTF8String:value];
    return result;
}

NSString* getNSString(string* value)
{
    return getNSString(value->c_str());
}

-(void) GameOverVehicleCrashed
{
    [_controller vehicleCrashed];
}

-(void) GameOverTimeIsUp
{
    [_controller gameOver];
}

-(BOOL) IsGameOver
{
    return _cEngine->IsGameOver();
}

-(void) UpdateRemainingTime:(float)timeLeft
{
    [_controller updateRemainingTime:timeLeft];
}

-(void) RemoveVehicle:(int)id
{
    EWVehicle* vehicle = [_vehicleDictionary objectForKey:@(id)];
    [vehicle removeFromSuperview];
    
    if([vehicle correctLane])
        _controller.timeRemaining = _controller.timeRemaining + 2;
    
    [_vehicleDictionary removeObjectForKey:@(id)];
}

@end

