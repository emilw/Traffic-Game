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

struct CEngineBridgeImpl : CEngine
{
    CEngineBridgeImpl(void (*printOutFunc) (string)): CEngine(printOutFunc){};
    CEngineBridgeImpl(): CEngine(){};
};

@implementation CEngineBridge

-(NSMutableArray*) getVehicles
{
    /*vector<CVehicle> vehicles = _cEngine->GetAllVehicles();
    
    NSMutableArray* result = [NSMutableArray init];
    
    vector<CVehicle>::iterator it = vehicles.begin();
    
    for(;it != vehicles.end(); it++)
    {
  //      EWVehicle vehicle = [EWVehicle init];
    //    vehicle->Id = 123124;
        
      //  [result addObject:[EWVehicle init]
    }
    return result;*/
    
    return [NSMutableArray new];
}

-(EWLane*) SyncLaneWithEngine:(EWLane *)inputLane
{
    CLane* lane = _cEngine->GetNewLane();
    inputLane.Id = lane->getID();
    
    lane->Position->setX(inputLane.center.x);
    lane->Position->setY(inputLane.center.y);
    
    return inputLane;
}

-(void) UpdatePosition:(NSMutableArray *)vehicles deltaTimes: (CGFloat) deltaTime
{
    vector<CVehicle> internalVehicles = _cEngine->GetAllVehicles(deltaTime);
    
    vector<CVehicle>::iterator it = internalVehicles.begin();
    
    for(;it != internalVehicles.end(); it++)
    {
        for(EWVehicle* vehicle in vehicles)
        {
            if(vehicle.Id == it->getID())
            {
                CGPoint position;
                position.x = it->Position->getX();
                position.y = it->Position->getY();
                vehicle.center = position;
                break;
            }
        }
    }
    
}

-(void) MoveVehicle:(EWVehicle *)vehicle
{
    CVehicle* internalVehicle = _cEngine->GetVehicle(vehicle.Id);
    
    _cEngine->MoveVehicle(vehicle.center.x, vehicle.center.y, internalVehicle);
}

-(EWVehicle*)UpdatePosition:(EWVehicle *)vehicle deltaTime:(CGFloat)deltaTime
{
    
    CVehicle* internalVehicle = _cEngine->GetVehicle(vehicle.Id);
    CPosition* newPosition = _cEngine->GetVehiclesCurrentPosition(internalVehicle, deltaTime);
    CGPoint position;
    position.x = newPosition->getX();
    position.y = newPosition->getY();
    
    vehicle.center = position;
    
    return vehicle;
}

-(EWVehicle*) GetNewVehicle: (EWLane*) lane
{
    CLane* internalLane = _cEngine->GetLane(lane.Id);
    CVehicle* vehicle = _cEngine->GetNewVehicle(internalLane);
    
    EWVehicle* v = [[EWVehicle alloc]
                    initWithName: getNSString(vehicle->getCarType())
                    id:vehicle->getID()];
    
    v.goalTag = vehicle->getType();
    v.goalLane = lane;
    
    CGPoint position;
    position.x = vehicle->Position->getX();
    position.y = vehicle->Position->getY();
    v.center = position;
    
    /*CGPoint position;
    position.x = lane.center.x;
    position.y = 480;
    v.center = position;*/
    
    
    //vehicle->Position->setY(position.y);
    //vehicle->Position->setX(position.x);
    
    //_cEngine->ExecuteMethod(writeSomething);
    
    //NSLog(@"Number of vehicles %d", _cEngine->GetNumberOfVehicles());
    
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

- (id) init
{
    self = [super init];
    _cEngine = new CEngineBridgeImpl(logFunction);
    //_cEngine = new CEngineBridgeImpl();
    return self;
}

void logFunction(string message)
{
    message = "NSLog:" + message + "\n";
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

@end

