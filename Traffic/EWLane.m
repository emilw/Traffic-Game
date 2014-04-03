//
//  EWLane.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWLane.h"
#import "EWTrafficController.h"
//#import "EWVehicle.h"

@implementation EWLane

@synthesize controller,Id;


-(void)awakeFromNib {
    [controller registerLane:self];
    srandom(time(NULL));
    [self start];
}

-(void) start {
    //Original
    //long newStartTime = random() % 200 + (self.tag*100);
    long newStartTime = random() % 200;
    
    carStartTimer = [NSTimer scheduledTimerWithTimeInterval:newStartTime/1000.0 target: self selector:@selector(startTimerFired:) userInfo:nil repeats:YES];
    //[controller startCarFromLane:self];
}

- (void) startTimerFired: (NSTimer*)timer{
    long newStartTime = random() % 1500 + 1000;
    [timer setFireDate:[NSDate dateWithTimeIntervalSinceNow:newStartTime/1000.0]];
    //[timer setFireDate:[NSDate dateWithTimeIntervalSinceNow:newStartTime/1.0]];
    
    
    [controller startCarFromLane:self];
    
    //NSLog(@"newStartTime %ld", newStartTime);
    
    //NSLog(@"Starting new car");
}

-(void)stop {
    [carStartTimer invalidate];
    carStartTimer = nil;
}

@end
