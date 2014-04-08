//
//  EngineBridge.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWVehicle.h"

@interface CEngineBridge: NSObject
{
    struct CEngineBridgeImpl* _cEngine;
    NSMutableDictionary* _vehicleDictionary;
    EWTrafficController* _controller;
}

-(id)initWithController: (EWTrafficController*) controller screenWidth: (float) screenWidth screenHeight: (float) screenHeight;
-(EWLane*)SyncLaneWithEngine: (EWLane*) lane;
-(void)UpdatePosition: (int) id;

//To keep
-(void)StartGame;
-(void)Update;
-(void)MoveVehicle: (EWVehicle*) vehicle to: (CGPoint) point;

-(void) GetNewVehicle: (int) Id carImage: (const char*) carImage x: (float) x y: (float) y;
-(void) RemoveVehicle: (int) id;

-(void)UpdateRemainingTime: (float) timeLeft;
-(float) GetTotalTime;

-(BOOL)IsGameOver;
-(void)GameOverVehicleCrashed;
-(void)GameOverTimeIsUp;
-(BOOL) IsPaused;
-(void) Pause;
-(void) Resume;

@property NSMutableArray* Vehicles;

@end
