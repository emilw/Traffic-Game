//
//  EngineBridge.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWVehicle.h"
//#import "EWTrafficController.h"
//#import "CEnginePlugin.h"
//#import "CEnginePlugin.h"

@interface CEngineBridge: NSObject
{
    struct CEngineBridgeImpl* _cEngine;
    NSMutableDictionary* _vehicleDictionary;
    EWTrafficController* _controller;
}

NSString* getValue();
-(id)initWithController: (EWTrafficController*) controller;
-(NSString*)getValue;
-(EWLane*)SyncLaneWithEngine: (EWLane*) lane;
-(void)UpdatePosition: (int) id;
-(void)WriteSomething;
-(void)UpdatePosition: (NSMutableArray*) vehicles deltaTimes: (CGFloat) deltaTime;

//To keep
-(void)StartGame;
-(EWVehicle*)GetNewVehicle: (EWLane*) lane;
-(void)Update: (float) deltaTime;
-(void)MoveVehicle: (EWVehicle*) vehicle;
-(BOOL)IsGameOver;
-(void)GameOverVehicleCrashed;
-(void)GameOverTimeIsUp;
-(void)UpdateRemainingTime: (float) timeLeft;
-(void) GetNewVehicle;
-(void) RemoveVehicle: (int) id;

@property NSMutableArray* Vehicles;

@end
