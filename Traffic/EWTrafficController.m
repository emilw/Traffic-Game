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
    
    /*UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
                        rootViewController].view;*/
    CGRect originalFrame = [[UIScreen mainScreen] bounds];
    /*CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];*/
    
    //CGFloat screenScale = [[UIScreen mainScreen] scale];
    
    //viewController.view.bounds.size.height;
    
    engine = [engine initWithController: self screenWidth:originalFrame.size.width screenHeight:originalFrame.size.height];
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
    [engine SyncLaneWithEngine:lane];
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
    return [engine IsPaused];
    //return displayLink.paused;
}

-(void)setTotalScore: (float) score{
    [viewController setTotalScore: [engine GetTotalTime]];
}

-(void) togglePause{
    
    displayLink.paused = !displayLink.paused;
    
    if(displayLink.paused)
    {
        [engine Pause];
        
        [self setTotalScore:[engine GetTotalTime]];
    }
    else
    {
        [engine Resume];
    }
    
    NSLog(@"display link state is changed to: %i", displayLink.paused);
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
