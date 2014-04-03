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
    
    NSMutableArray* vehicles;
    NSMutableArray* vehiclesToRemove;

    NSMutableArray* lanes;
    
    double timeRemaining;
    double lastTimestamp;
    
    SystemSoundID screechSoundID;
    SystemSoundID crashSoundID;
    
    CGFloat totalTime;
    
    EWTrafficViewController* viewController;
    
    CEngineBridge* engine;
}

@property (nonatomic,retain) IBOutlet EWTrafficViewController* viewController;
@property (nonatomic) double timeRemaining;

-(void)startGame;
-(void)registerLane:(EWLane*) lane;
-(void) startCarFromLane: (EWLane*) starter;
-(void) togglePause;
-(BOOL) isPaused;
-(EWLane*)laneAtPoint: (CGPoint)point;
-(void) vehicleMoved: (EWVehicle*) vehicle;
-(void) vehicleCrashed;
-(void) updateRemainingTime: (float) remainingTime;
-(void) addVehicleView: (EWVehicle*) vehicle;
-(void) gameOver;
@end
