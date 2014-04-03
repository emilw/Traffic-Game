//
//  EWTrafficController.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWTrafficController.h"
#import "EWVehicle.h"
#import "EWTrafficViewController.h"
#import "EWLane.h"
#import "EWAppDelegate.h"

@implementation EWTrafficController

@synthesize timeRemaining, viewController;

-(void)awakeFromNib{
    engine = [CEngineBridge alloc];
    engine = [engine initWithController: self];
    vehicles = [NSMutableArray arrayWithCapacity:10];
    vehiclesToRemove = [NSMutableArray arrayWithCapacity:10];
    lanes = [NSMutableArray arrayWithCapacity:3];
}

-(void)vehicleMoved: (EWVehicle*) vehicle point: (CGPoint)point{
    AudioServicesPlaySystemSound(screechSoundID);
    [engine MoveVehicle: vehicle to: point];
}

-(void)gameOver{
    //Game over
    if(!displayLink.paused)
        [self togglePause];
    
    [viewController displayGameOver];
    [NSNumber numberWithFloat: [engine GetTotalTime]];
    
    EWAppDelegate* delegate = [[UIApplication sharedApplication] delegate];
    [delegate addHighScore:[engine GetTotalTime]];
    [delegate stopBackgroundMusic];
}

-(void)registerLane:(EWLane*)lane
{
    lane = [engine SyncLaneWithEngine:lane];
    [lanes addObject:(lane)];
}

-(void)startGame{
    
    EWAppDelegate* delegate = [[UIApplication sharedApplication] delegate];
    [delegate playBackgroundMusic];
    
    displayLink = [CADisplayLink displayLinkWithTarget:self selector: @selector(update:)];
    [displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
    
    NSURL* screechURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:@"screech" ofType:@"aif"]];
    NSURL* crashURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:@"crash" ofType:@"aif"]];
    
    AudioServicesCreateSystemSoundID((__bridge CFURLRef) screechURL, &screechSoundID);
    AudioServicesCreateSystemSoundID((__bridge CFURLRef) crashURL, &crashSoundID);
    
    [engine StartGame];
}

-(void) update:(CADisplayLink*)sender{
    [engine Update];
}

-(void) vehicleCrashed
{
    AudioServicesPlaySystemSound(crashSoundID);
    
    [self gameOver];
}

-(BOOL) isPaused{
    return displayLink.paused;
}

-(void)setTotalScore: (float) score{
    [viewController setTotalScore: [engine GetTotalTime]];
}

-(void) togglePause{
    
    displayLink.paused = !displayLink.paused;
    
    if(displayLink.paused)
    {
        for(EWVehicle* v in vehicles)
        {
            v.userInteractionEnabled = NO;
        }
        
        for(EWLane* l in lanes)
        {
            [l stop];
        }
        [self setTotalScore:[engine GetTotalTime]];
    }
    else
    {
        for(EWVehicle* v in vehicles)
        {
            v.userInteractionEnabled = YES;
        }
        
        for(EWLane* l in lanes)
        {
            [l start];
        }
        
        [engine Resume];
        
        //lastTimestamp = CACurrentMediaTime();
    }
    
    NSLog(@"display link state is changed to: %i", displayLink.paused);
}

-(void) startCarFromLane: (EWLane*)starter {
#warning Let the engine select the lane etc. This method should probably removed fully
    EWVehicle* v = [engine GetNewVehicle: starter];
}

-(void) addVehicleView:(EWVehicle *)vehicle
{
    [viewController.view addSubview:vehicle];
}


-(void) updateRemainingTime:(float)remainingTime
{
    [self.viewController setRemainingTime: remainingTime];
}


@end
