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

//Struct to wrap the engine, due to lazyness the CEnginePlugin is used as a base here allso to avoid adding new files
struct CEngineBridgeImpl : CEngine, CEnginePlugin
{
    NSMutableArray* vehicles;
    id self;
    
    CEngineBridgeImpl(void (*printOutFunc) (string), void* fascadeObject): CEngine(printOutFunc, this), CEnginePlugin(fascadeObject)
    {
        self = (__bridge id)_fascadeObject;
    };
    
    void PreUpdateVehicle(CVehicle *vehicle)
    {
        //Nothing to do before the vehicle is being updated
    }
    
    void PostUpdateVehicle(CVehicle* vehicle)
    {
        [self UpdatePosition:vehicle->getID()];
        [self UpdateRemainingTime: this->GetRemainingTime()];
    }
    
    void GameOver(GameOverReason reason)
    {
        if(reason == GameOverReason::CRASH)
            [self GameOverVehicleCrashed];
        else
            [self GameOverTimeIsUp];
    }
    
    void PostNewVehicle(CVehicle* vehicle)
    {
        [self GetNewVehicle:vehicle->getID() carImage:vehicle->getCarType().c_str() x:vehicle->Position->getX() y:vehicle->Position->getY()];
    }
    
    virtual void PostRemoveVehicle(int id)
    {
        [self RemoveVehicle:id];
    }
    
};

@implementation CEngineBridge

#pragma region Callback_Methods
//Callbacks from extension methods
-(void)UpdatePosition:(int)id
{
    
    NSLog(@"Updating position for vehicle with id: %d", id);
    
    CVehicle* internalVehicle = _cEngine->GetVehicle(id);
    
    EWVehicle* vehicle = [_vehicleDictionary objectForKey:@(id)];
    
    vehicle.center = GetCGPointFromPosition(internalVehicle->Position);
}

-(void) GetNewVehicle:(int)Id carImage:(const char*)carImage x:(float)x y:(float)y
{
    
    NSLog(@"In getNew vehicle");
    EWVehicle* v = [[EWVehicle alloc] initWithName: getNSString(carImage) id:Id];
    
    CGPoint position;
    position.x = x;
    position.y = y;
    v.center = position;
    
    [_controller addVehicleView:v];
    
    v.controller = _controller;
    
    [_vehicleDictionary setObject:v forKey:@(v.Id)];
}

-(void) GameOverVehicleCrashed
{
    [_controller vehicleCrashed];
}

-(void) GameOverTimeIsUp
{
    [_controller gameOver];
}

-(void) RemoveVehicle:(int)id
{
    EWVehicle* vehicle = [_vehicleDictionary objectForKey:@(id)];
    [vehicle removeFromSuperview];
    
    [_vehicleDictionary removeObjectForKey:@(id)];
}

-(void) UpdateRemainingTime:(float)timeLeft
{
    [_controller updateRemainingTime:timeLeft];
}

#pragma endregion Callback_Methods


#pragma region API_Methods
//Call methods from controllers
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

CGPoint GetCGPointFromPosition(CPosition* cPosition)
{
    CGPoint position;
    position.x = cPosition->getX();
    position.y = cPosition->getY();
    return position;

}

-(void) MoveVehicle:(EWVehicle *)vehicle to:(CGPoint)point
{
    CVehicle* internalVehicle = _cEngine->GetVehicle(vehicle.Id);
    _cEngine->MoveVehicle(point.x, point.y, internalVehicle);
}

//Updates all
-(void)Update{
    _cEngine->GetAllVehicles();
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

-(BOOL) IsGameOver
{
    return _cEngine->IsGameOver();
}

-(float) GetTotalTime
{
    return _cEngine->GetTotalTime();
}

-(void) Pause
{
    _cEngine->Pause();
    
    for(id key in _vehicleDictionary)
    {
        EWVehicle* v = [_vehicleDictionary objectForKey:key];
        v.userInteractionEnabled = NO;
    }
}

-(BOOL) IsPaused
{
    return _cEngine->IsPaused();
}

-(void) Resume
{
    _cEngine->Resume();
    
    for(id key in _vehicleDictionary)
    {
        EWVehicle* v = [_vehicleDictionary objectForKey:key];
        v.userInteractionEnabled = YES;
    }
}

#pragma endregion API_Methods

#pragma region Helpers
NSString* getNSString(const char* value)
{
    NSString* result = [[NSString alloc] initWithUTF8String:value];
    return result;
}

NSString* getNSString(string* value)
{
    return getNSString(value->c_str());
}

#pragma endregion Helpers



@end

