//
//  EWLane.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-10.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>

@class EWTrafficController;

@interface EWLane : UIView
{
    NSTimer* carStartTimer;
    EWTrafficController* controller;
    int Id;
}

@property (nonatomic, retain) IBOutlet EWTrafficController* controller;
@property (nonatomic) int Id;

-(void)start;
-(void)stop;

@end
