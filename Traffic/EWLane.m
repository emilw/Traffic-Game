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
    //srandom(time(NULL));
}

@end
