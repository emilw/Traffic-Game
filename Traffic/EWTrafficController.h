//
//  EWTrafficController.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EWLane.h"
#import <AudioToolbox/AudioToolbox.h>
#import "CEngineBridge.h"
@class EWTrafficViewController;

@interface EWTrafficController : NSObject
{
    CADisplayLink* displayLink;
    
    SystemSoundID screechSoundID;
    SystemSoundID crashSoundID;
    
    
    EWTrafficViewController* viewController;
    
    CEngineBridge* engine;
}

@property (nonatomic,retain) IBOutlet EWTrafficViewController* viewController;
@property (nonatomic) double timeRemaining;

-(void)startGame;
-(void)registerLane:(EWLane*) lane;

-(void) togglePause;
-(BOOL) isPaused;
-(void) vehicleMoved: (EWVehicle*) vehicle point: (CGPoint) point;
-(void) vehicleCrashed;

-(void) updateRemainingTime: (float) remainingTime;
-(void) addVehicleView: (EWVehicle*) vehicle;

-(void) gameOver;
@end
