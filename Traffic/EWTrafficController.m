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
    timeRemaining = 20;
    totalTime = 0;
}

-(void)vehicleMoved: (EWVehicle*) vehicle{
    AudioServicesPlaySystemSound(screechSoundID);
    [engine MoveVehicle: vehicle];
}

-(void)gameOver{
    
    //Game over
    if(!displayLink.paused)
        [self togglePause];
    
    [viewController displayGameOver];
    [NSNumber numberWithFloat: totalTime];
    
    EWAppDelegate* delegate = [[UIApplication sharedApplication] delegate];
    [delegate addHighScore:totalTime];
    
    [delegate stopBackgroundMusic];
}

-(void)registerVehicle:(EWVehicle*) vehicle{
    [vehicles addObject:(vehicle)];
    
    //NSLog(@"Car count %d", [vehicles count]);
}

/*
 //Logic moved to removeVehicles
 -(void)toBeRemoveVehicle:(EWVehicle*) vehicle{
    [vehiclesToRemove addObject: vehicle];
    [vehicle removeFromSuperview];
    
    if([vehicle correctLane])
        timeRemaining = timeRemaining + 2;
}*/

/*-(void)removeVehicles{
    for(EWVehicle* v in vehicles)
    {
        if(v.ToBeRemoved){
            [v removeFromSuperview];
        
            if([v correctLane])
                timeRemaining = timeRemaining + 2;
        
            [vehiclesToRemove addObject:v];
        }
    }
    
    
    for(EWVehicle* v in vehiclesToRemove)
    {
        [vehicles removeObject: v];
    }
    [vehiclesToRemove removeAllObjects];
}*/

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
    //Audio
}

-(EWLane*)laneAtPoint: (CGPoint)point {
    for(EWLane* lane in lanes)
    {
        if(CGRectContainsPoint([lane frame], point))
            return lane;
    }
    
    return nil;
}

-(void) update:(CADisplayLink*)sender{
    /*if(lastTimestamp <=0){
        lastTimestamp = sender.timestamp;
    }
    
    CGFloat deltaTime = sender.timestamp - lastTimestamp;
    totalTime += deltaTime;
    
    timeRemaining -= deltaTime;
    */
    
    //NSLog(@"Time %g", deltaTime);
    
    /*for(EWVehicle* v in vehicles)
    {
        
    CGPoint position = v.center;
        CGFloat speed = v.speed;
        
        if(v.slowed){
            speed *= 0.5;
        }
        
        position.y -= speed * deltaTime;
        
        CGFloat lateralSpeed = 200;
        
        if(v.goalLane != nil) {
            CGPoint goalLanePosition = v.goalLane.center;
            CGFloat deltaX = fabs(goalLanePosition.x - position.x);
            
            if(deltaX < 3)
                position.x = goalLanePosition.x;
            
            if(position.x > goalLanePosition.x)
                position.x -= lateralSpeed * deltaTime;
            else if(position.x < goalLanePosition.x)
                position.x += lateralSpeed * deltaTime;
            
            NSLog(@"\nTrafficController: Goal lane position x: %g, y: %g", goalLanePosition.x, goalLanePosition.y);
        }
        
        v.center = position;
        
        NSLog(@"\nTrafficController: vehicle: %o, x: %g, y: %g", v.Id, v.center.x, v.center.y);
        
        
        [engine UpdatePosition:v deltaTime:deltaTime];
    }*/
    
    [engine Update: 0];
    //[engine UpdatePosition:vehicles deltaTimes:deltaTime];
    
    /*for(EWVehicle* v in vehicles)
    {
        //Check collisions
        for(EWVehicle* otherVehicle in vehicles)
        {
            if(otherVehicle == v) continue;
            
            CGRect myRect = CGRectInset(v.frame, 7,7);
            CGRect other = CGRectInset(otherVehicle.frame, 7,7);
            
            if(CGRectIntersectsRect(myRect, other)) {
                [self vehicle:v collidedWithVehicle:otherVehicle];
                return;
            }
            
        }
    }*/
      
    /*if([engine IsGameOver])
        [self vehicleCrashed];*/
    
    //[self removeVehicles];
    
    
    
    /*if(timeRemaining < 0) {
        //Game over
        if(!displayLink.paused)
            [self togglePause];
        [self gameOver];
    }*/
    
    //lastTimestamp = sender.timestamp;
}

-(void) vehicle:(EWVehicle*) vehicle collidedWithVehicle: (EWVehicle*) otherVehicle {
    
    AudioServicesPlaySystemSound(crashSoundID);
    
    NSLog(@"Vehicle %d collided with %d", vehicle.Id, otherVehicle.Id);
    
    //Game over
    if(!displayLink.paused)
        [self togglePause];
    [self gameOver];
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
    [viewController setTotalScore: totalTime];
    
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
        [self setTotalScore:totalTime];
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
        
        lastTimestamp = CACurrentMediaTime();
    }
    
    NSLog(@"display link state is changed to: %i", displayLink.paused);
}

-(void) startCarFromLane: (EWLane*)starter {
    /*NSString* carType;
    
    int type = random() % 3;
    
    switch(type) {
        case 0:
            carType = @"GreenCar";
            break;
        case 1:
            carType = @"RedCar";
            break;
        case 2:
            carType = @"BlueCar";
            break;
    }*/
    
    //EWVehicle* v = [[EWVehicle alloc] initWithName:carType];
    
#warning Let the engine select the lane etc. This method should probably removed fully
    EWVehicle* v = [engine GetNewVehicle: starter];
    
    //v.goalLane = starter;
    //v.goalTag = type;
    
    /*[viewController.view addSubview:v];
    [self registerVehicle:v];
    
    v.controller = self;*/
    
    //CGPoint position;
    //position.x = starter.center.x;
    //position.y = 480;
    //v.center = position;
    
    //[v release];
}

-(void) addVehicleView:(EWVehicle *)vehicle
{
    [viewController.view addSubview:vehicle];
}


-(void) updateRemainingTime:(float)remainingTime
{
    
    [self.viewController setRemainingTime: remainingTime];//self.timeRemaining];
}


@end
